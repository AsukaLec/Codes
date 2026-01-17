package lesson10;


import java.sql.*;
import java.util.*;
import java.io.*;
import java.util.concurrent.*;
import java.lang.reflect.*;
import java.nio.file.*;

/**
 * 编写一个DbUtil类，实现用连接池来管理数据库的连接。
 * （要求数据库连接参数存在在外表properties文件中以方便修改）
 */
public class DbUtil {
    private static final BlockingQueue<Connection> pool;
    private static final List<Connection> realConns = new ArrayList<>();
    private static final Properties props = new Properties();
    private static final int poolSize;

    static {
        BlockingQueue<Connection> tmpPool = new LinkedBlockingQueue<>();
        int size = 5;
        try {
            // 先尝试从 classpath 加载 db.properties，再尝试当前工作目录下的 db.properties
            InputStream in = Thread.currentThread().getContextClassLoader().getResourceAsStream("db.properties");
            if (in == null) {
                Path p = Path.of("db.properties");
                if (Files.exists(p)) in = new FileInputStream(p.toFile());
            }
            if (in == null) throw new RuntimeException("未找到 db.properties 配置文件（classpath 或 当前目录）");
            props.load(in);

            String driver = props.getProperty("db.driver");
            String url = props.getProperty("db.url");
            String user = props.getProperty("db.user");
            String password = props.getProperty("db.password");
            String poolSizeStr = props.getProperty("db.poolSize");

            if (driver != null && !driver.isBlank()) Class.forName(driver);
            if (poolSizeStr != null) size = Integer.parseInt(poolSizeStr);

            for (int i = 0; i < size; i++) {
                Connection real = DriverManager.getConnection(url, user, password);
                Connection proxy = createProxy(real);
                realConns.add(real);
                tmpPool.offer(proxy);
            }
        } catch (Exception e) {
            throw new RuntimeException("初始化数据库连接池失败", e);
        }
        pool = tmpPool;
        poolSize = size;
    }

    // 从池中获取连接（返回的是代理 Connection，调用 close() 会把连接归还到池）
    public static Connection getConnection() throws SQLException, InterruptedException {
        Connection conn = pool.take();
        return conn;
    }

    // 手动归还（通常不需要，代理的 close 已处理）
    public static void releaseConnection(Connection proxyConn) {
        if (proxyConn != null) {
            pool.offer(proxyConn);
        }
    }

    // 关闭连接池并释放真实连接资源
    public static void shutdown() {
        try {
            // 清空池中的代理引用
            pool.clear();
            for (Connection real : realConns) {
                try {
                    if (!real.isClosed()) real.close();
                } catch (SQLException ignored) {}
            }
            realConns.clear();
        } finally {
            // no-op
        }
    }

    // 创建代理，拦截 close 方法将连接归还到池中
    private static Connection createProxy(Connection real) {
        return (Connection) Proxy.newProxyInstance(
                Connection.class.getClassLoader(),
                new Class[]{Connection.class},
                new ConnectionHandler(real)
        );
    }
    // 连接代理处理器
    private static class ConnectionHandler implements InvocationHandler {
        private final Connection real;
        private boolean closed = false;

        ConnectionHandler(Connection real) {
            this.real = real;
        }

        @Override
        public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
            String name = method.getName();
            if ("close".equals(name)) {
                // 归还到池（如果池已满则真正关闭）
                if (closed) return null;
                closed = true;
                if (pool.size() < poolSize) {
                    // 将同一个代理对象放回池以便下一次 getConnection 拿到同一 proxy
                    pool.offer((Connection) proxy);
                } else {
                    try { real.close(); } catch (SQLException ignored) {}
                }
                return null;
            } else if ("isClosed".equals(name)) {
                return closed;
            }
            return method.invoke(real, args);
        }
    }
}
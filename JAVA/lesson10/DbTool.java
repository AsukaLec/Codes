package lesson10;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

/**
 * 编写一个名字为 DbTool的类，该类用了提供获取数据库连接和关闭数据库连接的静态方法
 */
public class DbTool {
    private static final String URL = "jdbc:mysql://localhost:3306/your_database"; // 修改为你的数据库 URL:端口/数据库名
    private static final String USER = "root";
    private static final String PASSWORD = "password";
    private static String DRIVER = "com.mysql.cj.jdbc.Driver"; // 根据数据库类型修改驱动类名

    // 静态代码块，加载数据库驱动
    static {
        try {
            Class.forName(DRIVER);
        } catch (ClassNotFoundException e) {
            throw new RuntimeException("数据库驱动加载失败", e);
        }
    }

    // 获取数据库连接
    public static Connection getConnection() {
        try {
            return DriverManager.getConnection(URL, USER, PASSWORD);
        } catch (SQLException e) {
            throw new RuntimeException("获取数据库连接失败", e);
        }
    }

    // 关闭数据库连接及其他资源
    public static void close (AutoCloseable... resources) {
        for (AutoCloseable resource : resources) {
            if (resource != null) {
                try {
                    resource.close();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }
    }

}

package lesson10;
import java.sql.*;

/**
 * 编写一个名字为 TestJDBC类，
 * 使用DbTool 及Statement 及PrepareStatement类实现数据的增，删，改，查功能（数据库和数据自己编）
 */
public class TestJDBC {
    public static void main(String[] args) {
        try (Connection conn = DbTool.getConnection()) {
            // 建表
            try (Statement stmt = conn.createStatement()) {
                stmt.executeUpdate("CREATE TABLE IF NOT EXISTS users (id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(50), email VARCHAR(100), age INT)");
            }

            // 使用 Statement 插入
            try (Statement stmt = conn.createStatement()) {
                stmt.executeUpdate("INSERT INTO users(name,email,age) VALUES('Alice','alice@example.com',30)");
            }

            // 使用 PreparedStatement 插入
            try (PreparedStatement ps = conn.prepareStatement("INSERT INTO users(name,email,age) VALUES(?,?,?)")) {
                ps.setString(1, "Bob");
                ps.setString(2, "bob@example.com");
                ps.setInt(3, 25);
                ps.executeUpdate();
            }

            // 查询
            try (PreparedStatement ps = conn.prepareStatement("SELECT id,name,email,age FROM users");
                 ResultSet rs = ps.executeQuery()) {
                while (rs.next()) {
                    System.out.printf("%d: %s <%s> age=%d%n", rs.getInt("id"), rs.getString("name"), rs.getString("email"), rs.getInt("age"));
                }
            }

            // 更新
            try (PreparedStatement ps = conn.prepareStatement("UPDATE users SET age=? WHERE name=?")) {
                ps.setInt(1, 31);
                ps.setString(2, "Alice");
                System.out.println("updated=" + ps.executeUpdate());
            }

            // 删除
            try (PreparedStatement ps = conn.prepareStatement("DELETE FROM users WHERE name=?")) {
                ps.setString(1, "Bob");
                System.out.println("deleted=" + ps.executeUpdate());
            }

        } catch (SQLException | RuntimeException e) {
            e.printStackTrace();
        } finally {
            // 清理：删除表（可选）
            try (Connection c = DbTool.getConnection(); Statement s = c.createStatement()) {
                s.executeUpdate("DROP TABLE IF EXISTS users");
            } catch (Exception ignored) {}
        }
    }
}
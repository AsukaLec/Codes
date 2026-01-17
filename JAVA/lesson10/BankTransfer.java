package lesson10;

import java.math.BigDecimal;
import java.sql.*;
import java.util.Scanner;

/**
 * 编写一个事务，实现银行转账功能（假设已经登录成功），再控制台输入 转入帐号和金额，实现转账功能
 */
public class BankTransfer {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("转入帐号(id): ");
        int toId = sc.nextInt(); // 假设输入的目标账号 id
        System.out.print("金额: "); 
        BigDecimal amount = sc.nextBigDecimal(); // 假设输入的转账金额
        int fromId = 1; // 假设已登录，使用固定源账号 id=1

        // 开始转账事务
        try (Connection conn = DbTool.getConnection()) {
            conn.setAutoCommit(false);

            // 确保表和示例账户存在
            try (Statement s = conn.createStatement()) {
                s.executeUpdate("CREATE TABLE IF NOT EXISTS accounts (id INT PRIMARY KEY, name VARCHAR(50), balance DECIMAL(19,4))");
            }
            ensureAccount(conn, fromId, "Alice", new BigDecimal("1000.00"));
            ensureAccount(conn, toId, "Target", new BigDecimal("100.00"));

            try {
                // 锁定并读取两账户（使用 SELECT ... FOR UPDATE）
                BigDecimal fromBalance = selectBalanceForUpdate(conn, fromId);
                BigDecimal toBalance = selectBalanceForUpdate(conn, toId);

                if (fromBalance.compareTo(amount) < 0) {
                    throw new RuntimeException("余额不足，当前余额: " + fromBalance);
                }

                // 执行更新
                updateBalance(conn, fromId, fromBalance.subtract(amount));
                updateBalance(conn, toId, toBalance.add(amount));

                conn.commit();
                System.out.println("转账成功: 从 " + fromId + " 到 " + toId + " 金额 " + amount);
            } catch (Exception e) {
                conn.rollback();
                throw e;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        sc.close();
    }

    /** 确保账户存在 */ 
    private static void ensureAccount(Connection conn, int id, String name, BigDecimal initBalance) throws SQLException {
        try (PreparedStatement ps = conn.prepareStatement("SELECT id FROM accounts WHERE id = ?")) {
            ps.setInt(1, id);
            try (ResultSet rs = ps.executeQuery()) {
                if (!rs.next()) {
                    try (PreparedStatement ins = conn.prepareStatement("INSERT INTO accounts(id,name,balance) VALUES(?,?,?)")) {
                        ins.setInt(1, id);
                        ins.setString(2, name);
                        ins.setBigDecimal(3, initBalance);
                        ins.executeUpdate();
                    }
                }
            }
        }
    }

    /** 查询并锁定账户余额 */
    private static BigDecimal selectBalanceForUpdate(Connection conn, int id) throws SQLException {
        try (PreparedStatement ps = conn.prepareStatement("SELECT balance FROM accounts WHERE id = ? FOR UPDATE")) {
            ps.setInt(1, id);
            try (ResultSet rs = ps.executeQuery()) {
                if (!rs.next()) throw new RuntimeException("账号不存在: " + id);
                return rs.getBigDecimal("balance");
            }
        }
    }

    /** 更新账户余额 */
    private static void updateBalance(Connection conn, int id, BigDecimal newBalance) throws SQLException {
        try (PreparedStatement ps = conn.prepareStatement("UPDATE accounts SET balance = ? WHERE id = ?")) {
            ps.setBigDecimal(1, newBalance);
            ps.setInt(2, id);
            ps.executeUpdate();
        }
    }
}
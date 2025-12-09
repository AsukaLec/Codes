package lesson02;

import java.time.LocalDate;
import java.time.temporal.WeekFields;
import java.util.Scanner;

/**
 * 功能：
 * 1. 循环读入 18 位身份证号码并校验合法性；
 * 2. 合法时输出：年龄、出生年中的第几周、出生至今共经过了多少周；
 * 3. 不合法时提示并重新输入。
 */
public class idcardcheck111 {

    private static final Scanner SC = new Scanner(System.in);

    public static void main(String[] args) {
        while (true) {
            System.out.print("请输入 18 位身份证号码：");
            String id = SC.nextLine().trim();
            if (isValidId(id)) {
                handleId(id);
                break;          // 处理完退出
            }
            System.out.println("号码不合法，请重新输入！");
        }
    }

    /* ---------- 校验 ---------- */
    private static boolean isValidId(String id) {
        if (id == null || !id.matches("\\d{17}[\\dXx]")) {
            return false;
        }
        // 校验出生日期
        try {
            birthDateFromId(id);
        } catch (Exception e) {
            return false;
        }
        // 校验位
        return checkBit(id);
    }

    /* 提取出生日期 */
    private static LocalDate birthDateFromId(String id) {
        int year  = Integer.parseInt(id.substring(6, 10));
        int month = Integer.parseInt(id.substring(10, 12));
        int day   = Integer.parseInt(id.substring(12, 14));
        return LocalDate.of(year, month, day);
    }

    /* 18 位身份证校验位验证 */
    private static boolean checkBit(String id) {
        final int[] WEIGHT = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
        final char[] CODE  = {'1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2'};
        int sum = 0;
        for (int i = 0; i < 17; i++) {
            sum += (id.charAt(i) - '0') * WEIGHT[i];
        }
        char expect = CODE[sum % 11];
        char actual = Character.toUpperCase(id.charAt(17));
        return expect == actual;
    }

    /* ---------- 业务处理 ---------- */
    private static void handleId(String id) {
        LocalDate birth = birthDateFromId(id);
        LocalDate today = LocalDate.now();

        int age = today.getYear() - birth.getYear();
        if (today.isBefore(birth.plusYears(age))) {   // 今年生日未到
            age--;
        }

        // 出生年中的第几周（采用 ISO 周规则，周一为每周第一天）
        int weekOfYear = birth.get(WeekFields.ISO.weekOfWeekBasedYear());

        // 出生至今完整周数
        long weeksBetween = java.time.temporal.ChronoUnit.WEEKS.between(birth, today);

        System.out.printf("年龄：%d 岁%n", age);
        System.out.printf("出生日期：%s，是当年的第 %d 周%n", birth, weekOfYear);
        System.out.printf("从出生到今天已过去 %d 周%n", weeksBetween);
    }
}


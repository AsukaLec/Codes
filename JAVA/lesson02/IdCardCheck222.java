package lesson02;

import java.time.LocalDate;
import java.time.temporal.WeekFields;
import java.util.Scanner;

public class IdCardCheck222 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while (true) {
            System.out.print("请输入 18 位身份证号码：");
            String id = sc.nextLine().trim();

            if (!id.matches("\\d{17}[\\dXx]")) {
                System.out.println("号码不合法，请重新输入！");
                continue;
            }

            int year  = Integer.parseInt(id.substring(6, 10));
            int month = Integer.parseInt(id.substring(10, 12));
            int day   = Integer.parseInt(id.substring(12, 14));
            LocalDate birth;
            try {
                birth = LocalDate.of(year, month, day);
            } catch (Exception e) {
                System.out.println("号码不合法，请重新输入！");
                continue;
            }

            int[] weight = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
            char[] code  = {'1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2'};
            int sum = 0;
            for (int i = 0; i < 17; i++) {
                sum += (id.charAt(i) - '0') * weight[i];
            }
            char expect = code[sum % 11];
            char actual = Character.toUpperCase(id.charAt(17));
            if (expect != actual) {
                System.out.println("号码不合法，请重新输入！");
                continue;
            }

            LocalDate today = LocalDate.now();
            int age = today.getYear() - birth.getYear();
            if (today.isBefore(birth.plusYears(age))) age--;

            int weekOfYear = birth.get(WeekFields.ISO.weekOfWeekBasedYear());
            long weeksBetween = java.time.temporal.ChronoUnit.WEEKS.between(birth, today);

            System.out.printf("年龄：%d 岁%n", age);
            System.out.printf("出生日期：%s，是当年的第 %d 周%n", birth, weekOfYear);
            System.out.printf("从出生到今天已过去 %d 周%n", weeksBetween);
            break;
        }
        sc.close();
    }
}

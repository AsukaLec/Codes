package lesson02;

import java.time.DayOfWeek;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.util.Scanner;

/**
 * 功能：
 * 1. 读入生产日期（yyyy-MM-dd）；
 * 2. 读入保质期（天）；
 * 3. 计算并输出“离过期最近的前一个周六”促销日。
 */
public class forsale111 {
 
    private static final DateTimeFormatter FMT = DateTimeFormatter.ofPattern("yyyy-MM-dd");
    private static final Scanner SC = new Scanner(System.in);

    public static void main(String[] args) {
        LocalDate produceDate = readProduceDate();
        int shelfDays = readShelfDays();
        LocalDate expireDate = produceDate.plusDays(shelfDays);

        // 找到 <= expireDate 的最后一个周六
        LocalDate saturday = expireDate;
        while (saturday.getDayOfWeek() != DayOfWeek.SATURDAY) {
            saturday = saturday.minusDays(1);
        }

        System.out.println("促销处理日（过期前最近周六）：" + saturday.format(FMT));
    }

    /* ---------- 工具 ---------- */
    private static LocalDate readProduceDate() {
        while (true) {
            System.out.print("请输入生产日期（格式 yyyy-MM-dd）：");
            String txt = SC.nextLine().trim();
            try {
                return LocalDate.parse(txt, FMT);
            } catch (DateTimeParseException e) {
                System.out.println("格式错误，请重新输入！");
            }
        }
    }

    private static int readShelfDays() {
        while (true) {
            System.out.print("请输入保质期（天）：");
            String txt = SC.nextLine().trim();
            try {
                int days = Integer.parseInt(txt);
                if (days > 0) return days;
            } catch (NumberFormatException ignored) { }
            System.out.println("必须为正整数，请重新输入！");
        }
    }
}

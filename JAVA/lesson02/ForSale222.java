package lesson02;

import java.time.DayOfWeek;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.Scanner;

public class ForSale222 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        DateTimeFormatter fmt = DateTimeFormatter.ofPattern("yyyy-MM-dd");

        System.out.print("请输入生产日期（格式 yyyy-MM-dd): ");
        LocalDate produceDate = LocalDate.parse(sc.nextLine().trim(), fmt);

        System.out.print("请输入保质期：");
        int shelfDays = Integer.parseInt(sc.nextLine().trim());

        LocalDate expireDate = produceDate.plusDays(shelfDays);
        LocalDate saturday = expireDate;
        while (saturday.getDayOfWeek() != DayOfWeek.SATURDAY) {
            saturday = saturday.minusDays(1);
        }

        System.out.println("促销处理日：" + saturday.format(fmt));
        sc.close();
    }
}

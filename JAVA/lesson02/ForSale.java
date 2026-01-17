package lesson02;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.Scanner;

/**
 * 在lesson02中设计一个类ForSale.java，实现以下功能
 * 1）程序运行时提示用户输入代表 产品的生产日期的字符串格式为 ：yyyy-mm-dd : 如:2008-08-08
 * 2）用户回车确认输入后，提示用户输入产品的保质期以天为单位。如: 180
 * 3）计算输出离产品过期日期最近的前一个星期六的日期（促销处理日），在控制台输出；
 */
public class ForSale {

    public static void main(String[] args) throws ParseException {
        Scanner sc = new Scanner(System.in);
        SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd");

        System.out.print("请输入生产日期（格式 yyyyMMdd): ");
        Date produceDate = sdf.parse(sc.nextLine().trim());

        System.out.print("请输入保质期（天）：");
        int shelfDays = Integer.parseInt(sc.nextLine().trim());

        Calendar cal = Calendar.getInstance();
        cal.setTime(produceDate);
        cal.add(Calendar.DAY_OF_YEAR, shelfDays);
        Date expireDate = cal.getTime();

        cal.set(Calendar.DAY_OF_WEEK, Calendar.SATURDAY);
        cal.add(Calendar.DAY_OF_YEAR, -7);
        Date promoDate = cal.getTime();

        System.out.println("产品过期日：" + sdf.format(expireDate));
        System.out.println("促销处理日（过期前最近周六）：" + sdf.format(promoDate));

        sc.close();
    }
}

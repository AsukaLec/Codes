package lesson02;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.Scanner;

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

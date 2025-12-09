package lesson02;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.Scanner;

/**
 * 功能：身份证号合法性校验 + 年龄 + 出生年第几周 + 已存活周数
 */
public class idCardCheck {

    public static void main(String[] args) throws ParseException{
        Scanner sc = new Scanner(System.in);
        SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd");

        while (true) {
            System.out.print("请输入18位身份证号码：");
            String id = sc.next();

            if (!id.matches("\\d{17}[\\dXx]")) {
                System.out.println("格式错误！必须17位数字 + 1位数字或X/x");
                continue;
            }

            String birthStr = id.substring(6, 14);
            Date birth = sdf.parse(birthStr);

            if (!checkCode(id)) {
                System.out.println("校验位错误！");
                continue;
            }

            Calendar birthCal = Calendar.getInstance();
            birthCal.setTime(birth);
            Calendar now = Calendar.getInstance();

            int age = now.get(Calendar.YEAR) - birthCal.get(Calendar.YEAR);
            if (now.get(Calendar.DAY_OF_YEAR) < birthCal.get(Calendar.DAY_OF_YEAR)) {
                age--;
            }

            int weekOfYear = birthCal.get(Calendar.WEEK_OF_YEAR);

            int weeksBetween = 0;
            while(birthCal.get(Calendar.YEAR) < now.get(Calendar.YEAR)   ) {
                if(birthCal.get(Calendar.DAY_OF_WEEK) == Calendar.SUNDAY) weeksBetween++;
                birthCal.add(Calendar.DAY_OF_YEAR, 1);
            } while (birthCal.get(Calendar.DAY_OF_YEAR) <= now.get(Calendar.DAY_OF_YEAR)) {
                if(birthCal.get(Calendar.DAY_OF_WEEK) == Calendar.SUNDAY) weeksBetween++;
                birthCal.add(Calendar.DAY_OF_YEAR, 1);
            }

            System.out.println(birthCal.get(Calendar.YEAR));

            System.out.println("年龄：" + age);
            System.out.println("出生在那一年第 " + weekOfYear + " 周");
            System.out.println("从出生到现在已经经历了 " + weeksBetween + " 周");
            break;
        }
        sc.close();
    }

    /** 18位身份证校验位验证 */
    private static boolean checkCode(String id) {
        int[] w = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
        char[] check = {'1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2'};
        int sum = 0;
        for (int i = 0; i < 17; i++) {
            sum += (id.charAt(i) - '0') * w[i];
        }
        int mod = sum % 11;
        return Character.toUpperCase(id.charAt(17)) == check[mod];
    }
}

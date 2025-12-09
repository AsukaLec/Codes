package lesson05;
import java.text.DecimalFormat;
import java.util.Scanner;
/*
 * 1 、分别编写名字为TestPackageClass和MyException类，
 * 实现一下功能：在控制台串中输入一串字符，并判断，
 * 如果是整数字符串，则转换成Integer对象，
 * 如果是浮点数字符串则转换成Double对象，并格式化为 $#....#.##（不用四舍五入输出进度到小数点后面两位，），
 * 如果是非数字，则抛出显式抛出自定义异常类MyException，异常信息是“输入了数据无法实现数字格式转换";
 */
class MyException extends Exception {
    public MyException(String message) {
        super(message);
    }
}

public class TestPackageClass {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("输入一串字符：");
        String input = sc.nextLine();

        try {
            if (input.matches("-?\\d+")) {
                Integer integer = Integer.parseInt(input);
                System.out.println("Integer = " + integer);
            } else if (input.matches("-?\\d+\\.\\d+")) {
                Double db = Double.parseDouble(input);
                DecimalFormat df = new DecimalFormat("0.00");
                String formatted = df.format(db);
                System.out.println("转换结果是：Double = " + formatted);
            } else {
                sc.close();
                throw new MyException("输入了数据无法实现数字格式转换");
            }
        } catch (MyException e) {
            System.out.println(e.getMessage());
        }
        sc.close();
    }
}

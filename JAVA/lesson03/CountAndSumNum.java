package lesson03;
import java.util.Scanner;

/** 
 * 在lesson03中，编写一个类CountAndSumNum,求 a+aa+aaa+aaa...a的值。 
 * a是由键盘输入的0-9的整数， 叠加的次数也由用户输入。 
 * 例如，请输入一个0-9的数，（输入3） 请输入叠加次数: （输入3）则计算 3+33+333 的值。
 */
public class CountAndSumNum {
    public static void main(String[] args) {
        @SuppressWarnings("resource")
        Scanner scanner = new Scanner(System.in);  

        System.out.print("请输入一个0~9的数: ");
        int num = scanner.nextInt();

        System.out.print("请输入叠加次数: ");
        int times = scanner.nextInt();
        times --;


        long ans = 0;
        for (int i = 1; times >= 0 ; i ++) {
            ans += num * Math.pow(10, times--) * i;
        }

        System.out.println("结果为: " + ans);
    }
}

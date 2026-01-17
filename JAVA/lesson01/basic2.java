package lesson01;
import java.util.Scanner;

/**
 * 编写java程序，从键盘输入一个整数n，
 * 分别使用for循环和while循环语句计算 1+1/2!+1/3!+......+1/n!;
 */

public class basic2 {
    public static void main(String[] args) {
        @SuppressWarnings("resource")
        Scanner scanner = new Scanner(System.in);
        
        int n = scanner.nextInt();

        double ans1 = 0.0;
        double cur1 = 1.0;

        for (int i = 1; i <= n; i++) {
            cur1 *= i;
            ans1 += 1 / cur1;
        }
        System.out.println("使用for循环计算得出: " + ans1);

        double ans2 = 0.0;
        double cur2 = 1.0;
        int times = 1;
        while (n -- > 0) { 
            cur2 *= times;
            ans2 += 1 / cur2;
            times ++;
        }

        System.out.println("使用for循环计算得出: " + ans2);
    }
}

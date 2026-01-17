package lesson01;
import java.util.Scanner;

/** 
 * 编写java程序，从键盘输入一个整数x，判断是技术还是偶数，
 * 输出判断结果。使出格式为： X为（奇/偶）数
 */
public class basic1 {
    public static void main(String[] var0) {
        @SuppressWarnings("resource")
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        
        int ans = n & 1;
        if (ans == 1) System.out.println(n + "是奇数");
        else System.out.println(n + "是偶数");
    }
}

package lesson01;
import java.util.Scanner;
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

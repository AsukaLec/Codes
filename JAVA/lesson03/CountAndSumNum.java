package lesson03;
import java.util.Scanner;

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

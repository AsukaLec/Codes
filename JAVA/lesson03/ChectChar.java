package lesson03;
import java.util.Scanner;

public class ChectChar {
    public static void main(String[] args) {
        System.out.print("请输入一个五位数: ");
        @SuppressWarnings("resource")
        Scanner scanner = new Scanner(System.in);  
        String str0 = scanner.nextLine();

        while (str0.length() != 5) {
            System.out.print("输入错误，请重新输入一个五位数: ");
            str0 = scanner.nextLine();
        }

        if (str0.charAt(0) == str0.charAt(4) && str0.charAt(1) == str0.charAt(3)) {
            System.out.println("这是一个回文数");
        } else {
            System.out.println("这不是一个回文数");
        }

    }
}

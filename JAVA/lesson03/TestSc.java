package lesson03;
import java.util.Scanner;

public class TestSc {
    public static void main(String[] args) {
        @SuppressWarnings("resource")
        Scanner scanner = new Scanner(System.in);

        System.out.print("请输入一段英文字母: ");
        String str0 = scanner.nextLine();
        System.out.println("输入的英文字母串为: " + str0);
        
        System.out.print("输入要统计出现次数的英文字符: ");

        char ch = scanner.nextLine().charAt(0);
        int cnt = 0;
        for (int i = 0; i < str0.length(); i ++) {
            if (str0.charAt(i) == ch) {
                cnt ++;
            }
        }
        System.out.println("字符 " + ch + " 出现的次数为: " + cnt);
        
    }
}

package lesson03;
import java.util.Scanner;

/**
 * 在lesson03中设计一个名字为ChectChar类，使其 有接受两次从键盘输入信息的功能。
 * 提示输入，并接受第一次接受从键盘输入任意一段英文字母。
 * 按回车后，提示第二次输入入任意一个字母。
 * 判断第二次输入的字母在 第一次输入的字符串中出现多少次，并输出结果。
 */
public class ChectChar {
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

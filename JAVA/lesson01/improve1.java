package lesson01;
import java.util.Scanner;
public class improve1 {
    public static void main(String[] args) {
        @SuppressWarnings("resource")
        Scanner scanner = new Scanner(System.in);
        double price = scanner.nextDouble();
        int items = scanner.nextInt();
        double total = scanner.nextDouble();

        // System.out.println(price + " " + items + " " + total);

        if (price > 5 ||price * items > 600.0) {
            double ans = price * items;
            ans *= 0.9;
            System.out.println("应收金额: " + ans);
            double left = total - ans;
            System.out.println("找零: " + left);
        } else if (price > 10 || price * items > 1000) {
            double ans = price * items;
            ans *= 0.85;
            System.out.println("应收金额: " + ans);
            double left = total - ans;
            System.out.println("找零: " + left);
        } else {
            double ans = price * items;
            System.out.println("应收金额: " + ans);
            double left = total - ans;
            System.out.println("找零: " + left);
        }
    }
}

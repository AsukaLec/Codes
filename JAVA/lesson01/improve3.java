// package lesson01;

// public class improve3 {
//     public static void main(String[] args) {
//         for (int l = 1; l <= 9; l ++) {
//             for (int r = 1; r <= l; r ++) {
//                 if (l * r >= 10) System.out.print(l + "*" + r + "=" + l * r + "  ");
//                 else System.out.print(l + "*" + r + "=" + l * r + "   ");
                
//             }
//             System.out.println();
//         }
//     }
// }


package lesson01;
import java.util.Scanner;

public class improve3 {
    public static void main(String[] args) {
        @SuppressWarnings("resource")
        Scanner sc = new Scanner(System.in);
        //int 中国 = 111;
        int n = 1;
        while(n != 0) {
            n = sc.nextInt();
            printMultiplicationTable(n);
        }
    }

    static void printMultiplicationTable(int n) {
        StringBuilder sb = new StringBuilder();
        for (int i = 1; i <= n; i++) {
            sb.setLength(0);
            for (int j = 1; j <= i; j++) {
                sb.append(String.format("%d*%d=%2d", i, j, i * j));
            }
            System.out.println(sb.toString().trim());
        }
    }
}
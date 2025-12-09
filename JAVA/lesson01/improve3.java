package lesson01;

public class improve3 {
    public static void main(String[] args) {
        for (int l = 1; l <= 9; l ++) {
            for (int r = 1; r <= l; r ++) {
                if (l * r >= 10) System.out.print(l + "*" + r + "=" + l * r + "  ");
                else System.out.print(l + "*" + r + "=" + l * r + "   ");
                
            }
            System.out.println();
        }
    }
}

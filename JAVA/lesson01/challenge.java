package lesson01;

public class challenge {
    public static void main(String[] args) {
        for (int l = 8, r = 10; l >= 0; l --, r ++) {
            for (int i = 1; i <= l; i ++) System.out.print("  ");
            for (int j = 0; j < r - l - 1; j ++) System.out.print("* ");
            for (int k = r ; k <= 18; k ++) System.out.print("  ");
            System.out.println();
        } 
        for (int l = 0, r = 16; l < 8; l ++, r --) {
            System.out.print("  ");
            for (int i = 0; i < l; i ++) System.out.print("  ");
            for (int j = 0; j < r - l - 1; j ++) System.out.print("* ");
            for (int k = r ; k < 16; k ++) System.out.print("  ");
            System.out.println();
        }

        System.out.println();
        
        for (int l = 8, r = 10; l >= 0; l --, r ++) {
            for (int i = 1; i <= l; i ++) System.out.print("  ");
            System.out.print("* ");
            for (int j = 0; j < r - l - 3; j ++) System.out.print("  ");
            if (l != 8) System.out.print("* ");
            for (int k = r ; k <= 18; k ++) System.out.print("  ");
            System.out.println();
        } 
        for (int l = 0, r = 16; l < 8; l ++, r --) {
            System.out.print("  ");
            for (int i = 0; i < l; i ++) System.out.print("  ");
            System.out.print("* ");
            for (int j = 0; j < r - l - 3; j ++) System.out.print("  ");
            if (l != 7) System.out.print("* ");
            for (int k = r ; k < 16; k ++) System.out.print("  ");
            System.out.println();
        }
    }
}

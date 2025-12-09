package lesson03;
import java.util.Random;
import java.util.Arrays;

public class task01 {
    public static void main(String[] args) {
        int[] array0 = new int[10];
        Random rand = new Random();

        //task a
        for (int i = 0; i < array0.length; i++) {
            array0[i] = rand.nextInt(100); 
        }
        System.out.print("随机生成的10位数组为: ");
        for (int x : array0) {
            System.out.print(x + " ");
        }
        System.out.println();


        //task b
        //本方法中若出现多个最大值或最小值，只删除第一个出现的最大值或最小值
        int max_index = 0, min_index = 0;
        for (int i = 1; i < array0.length; i++) {
            if (array0[i] > array0[max_index]) {
                max_index = i;
            }
            if (array0[i] < array0[min_index]) {
                min_index = i;
            }
        }

        int[] array1 = new int[array0.length - 2];
        int index1 = 0;
        for (int i = 0; i < array0.length - 2; i ++) {
            if (index1 == max_index || index1 == min_index) {
                index1++;
            }
            array1[i] = array0[index1++];
        }

        System.out.print("删除最大值和最小值后的数组为: ");
        for (int x : array1) {
            System.out.print(x + " ");
        }
        System.out.println();

        //task c
        int head = 0, end = array1.length + 2, mid = array1.length / 2 + 1;
        int [] array2 = new int[array1.length + 3];
        int index2 = 0;
        for (int i = 0; i < array1.length + 3; i ++) {
            if (i == head || i == mid || i == end) {
                int x = rand.nextInt(100);
                array2[i] = x;
            } else {
                array2[i] = array1[index2++];
            }
        }

        System.out.print("插入三个随机数后的数组为: ");
        for (int x : array2) {
            System.out.print(x + " ");
        }
        System.out.println();


        //task d
        Arrays.sort(array2);
        System.out.print("排序后的数组为: ");
        for (int x : array2) {
            System.out.print(x + " ");
        }
        System.out.println();

        int index3 = rand.nextInt(array2.length + 1);
        int delta = array2[index3] - array2[index3 - 1];
        int x = rand.nextInt(delta) + array2[index3 - 1];
        int[] array3 = new int[array2.length + 1];
        int index4 = 0;
        for (int i = 0; i < array3.length; i ++) {
            if(i == index3) {
                array3[i] = x;
            } else {
                array3[i] = array2[index4++];
            }
        }

        System.out.print("插入随机数并保证升序的数组为: ");
        for (int x1 : array3) {
            System.out.print( x1  + " ");
        }

    }   
}

package lesson05;
import java.util.Random;

/* 
 * 4.编写一个类TestArray，定义一个一维的整型数组，
 * 使用两种循环遍历数组。
 * 输出数组中最大值的元素。
 * 然后对数组排序，
 * 分别在数组头，中间和末尾 位置插入一个元素。
 */

public class TestArray {
    public static void main(String[] args) {
        Random r = new Random();
        int size = 10;

        int [] array = new int[size];
        for (int i = 0; i < 10; i ++) array[i] = r.nextInt(100);

        //输出数组中最大的元素
        int max = Integer.MIN_VALUE;
        for (int i = 0; i < size; i ++) if (array[i] >= max) max = array[i];
        System.out.println("普通遍历下，最大值为：" + max);

        max = Integer.MIN_VALUE;
        for (int x : array) if (x >= max) max = x;
        System.out.println("强遍历下，最大值为：" + max);

        //对数组进行排序 （升序)
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - 1 - i; j++) {
                if (array[j] > array[j + 1]) {
                    int temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
        for(int x : array) System.out.print( x + " ");
        System.out.println();

        //分别在数组头，中间和末尾 位置插入一个元素。
        int [] array1 = new int[size + 3];
        array1[0] = r. nextInt(100);

        for (int i = 0; i < size/2 ; i ++) {
            array1[i + 1] = array[i];
        }

        array1[size/2 + 1] = r.nextInt(100);
        for (int i = size/2 ; i < size; i ++) {
            array1[i + 2] = array[i];
        }

        array1[size + 2] = r.nextInt(100);

        // size += 3;
        // for (int i = 0; i < size - 1; i++) {
        //     for (int j = 0; j < size - 1 - i; j++) {
        //         if (array1[j] > array1[j + 1]) {
        //             int temp = array1[j];
        //             array1[j] = array1[j + 1];
        //             array1[j + 1] = temp;
        //         }
        //     }
        // }
        System.out.print("插入元素后的数组：");
        for(int x : array1) System.out.print( x + " ");
    }
}

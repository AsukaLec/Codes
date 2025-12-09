package lesson05;
import java.util.Random;
import java.util.Scanner;
/*
 * 2 .编写一个类，该类有一个名字为 getRandomNum的方法 ，
 * 该方法可以返回若干个指定范围内的随机数。
 * 编写一个测试类，通过键盘输入 返回随机数的个数和范围，打印输出返回的随机数。
 * 比如输入 10 20 ，则可以返回10个20以内的不同的随机数。（应用：比如以学号抽奖，不能重复中奖，每次抽出来数字一定属于某个同学的学号）
 */
class GetNum {
    public void getRandomNum(int total, int limit) {
        Random r = new Random();
        int [] arr = new int[limit + 1];
        while(total > 0) {
            int cur = r.nextInt(limit);
            if (arr[cur + 1] == 0 && cur > 0) {
                System.out.print(cur);
                System.out.print(" ");
                arr[cur + 1] += 1;
                total -= 1;
            }
        }
    }
}


public class RandNumTest {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("输入总数以及上限：");
        int total = sc.nextInt(); int limit = sc.nextInt();
        if (total > limit) {
            System.out.println("数据不合法 请重新输入");
            sc.close();
            return;
        }
        GetNum a = new GetNum();
        a.getRandomNum(total, limit);
        sc.close();
    }
}

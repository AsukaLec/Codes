package lesson05;
/* 3 . 编写一个掷色子猜大小的游戏： 每个色子有六个面，分别代表 1 -6 点。每次产生三个色子，三个点数的和>=10 为大，否则为小。 
 * 程序启动时在控制台显示 用户当前的总分，
 * 然后提示用户输入 押注的 分数，用户按回车后提示用户猜大小，
 * 然后程序根据色子点数和用户输入的结果进行判断。
 * 每一次执行完后输出色子点数，用户的输赢和剩余的分数。
 * 当用户的输入的分数是负数或大于总分，提示用户用户输入有误，
 * 如果用户输入exit，则程序退出。
 * 程序还要保证如果用户输入的分数 >1000,用户一定输。 
*/

import java.util.Scanner;
import java.util.Random;

public class GuessPointGame {
    public static void main(String[] args) {
        
        Scanner sc = new Scanner(System.in);
        Random r = new Random();

        int total = 5000; // 初始值

        System.out.println("输入你要押注的分数或输入exit退出程序");

        String a = sc.next();
        while(!a.equals("exit")) {

            try {
                int point = Integer.parseInt(a);


                if (point < 0 || point > total) {
                    System.out.println("押注为负数或大于总分，输入不合法，请重新输入");
                } else if(point > 1000) {
                    System.out.println("输入你的猜想（大 或 小）");
                    total -= 1000;
                    System.out.println("你猜错了");
                    System.out.println("当前总分为：" + total);                    
                } else if(point < 1000 &&point <= total){
                    System.out.println("输入你的猜想（大 或 小）");
                    String guess = sc.next();
                    int cur = 0;
                    for (int i = 3; i > 0; i--) {cur += r.nextInt(6) + 1;}
                    if ((cur >= 10 && guess.equals("大")) || (cur < 10 && guess.equals("小") )) {
                        System.out.println("你猜对了");
                        total += point;
                        System.out.println("当前总分为：" + total);
                    } else {
                        System.out.println("你猜错了");
                        total -= point;
                        System.out.println("当前总分为：" + total);                    
                    }                    
                }
            } catch (Exception e) {
                System.out.println("输入不合法: " + e.getMessage());
            }

            System.out.println("输入你要押注的分数或输入exit退出程序");
            a = sc.next();
        }
        
        System.out.println("程序已退出");
        sc.close();
    }
}

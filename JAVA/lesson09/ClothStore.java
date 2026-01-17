package lesson09;

import java.util.*;
import java.time.*;
import java.time.format.DateTimeFormatter;

/**
 * 顾客进服装店的购物过程包含三个环节，选衣服，试衣服，结账离开。
 * 其中选衣服环节和试衣服环节需要的时间为 1-5秒不等（随机），结账离开环节5秒，该店只有一间试衣间（不能两人同时使用）。   
 * 请编写一个程序模拟每隔一段时间有一个个顾客进店购买的过程。程序执行过程中，输出每个顾客所处的环节信息。 
 * 比如，顾客1在试衣服，顾客2，在选衣服，顾客2在试衣服。  
 * 提示，用线程调度
 */
public class ClothStore {
    private static final Random RANDOM = new Random();
    private static final int MAX_TRY_CLOTH_TIME = 5; // 最大试衣时间，单位秒
    private static final int CHECKOUT_TIME = 5; // 结账时间，单位秒
    private static final Object FITTING_ROOM_LOCK = new Object(); // 试衣间锁
    private static final DateTimeFormatter TIME_FORMATTER = DateTimeFormatter.ofPattern("HH:mm:ss");
    

    public static void main(String[] args) {
        int customerId = 1;
        while (true) {
            Customer customer = new Customer(customerId++);
            customer.start();
            try {
                int customerInterval = RANDOM.nextInt(4000, 10000); // 新顾客进店的间隔时间，1-2秒
                Thread.sleep(customerInterval); // 每隔2秒有一个新顾客进店
            } catch (InterruptedException e) {
                System.out.println("主线程被中断，停止接待新顾客");
                break;
            }
        }
    }

    static class Customer extends Thread {
        private final int customerId;
        public Customer(int customerId) {
            this.customerId = customerId;
        }

        @Override
        public void run() {
            try {
                log("进入服装店，欢迎光临~");
                int selectClothTime = RANDOM.nextInt(1, MAX_TRY_CLOTH_TIME + 1);
                Thread.sleep(selectClothTime * 1000);
                log("选衣服完成，排队试衣服");

                // 试衣服环节，使用试衣间锁
                synchronized (FITTING_ROOM_LOCK) {
                    log("进入试衣间，开始试衣服");
                    int tryClothTime = RANDOM.nextInt(1, MAX_TRY_CLOTH_TIME + 1);
                    Thread.sleep(tryClothTime * 1000);
                    log("试衣服完成，离开试衣间。" + "试衣服时间：" + tryClothTime + "秒");
                }

                log("准备结账");
                Thread.sleep(CHECKOUT_TIME * 1000);
                log("结账完成，离开服装店，期待下次光临~");
            } catch (InterruptedException e) {
                log("购物过程被中断");
            }
        }

        private void log(String message) {
            String time = LocalTime.now().format(TIME_FORMATTER);
            System.out.println("[" + time + "] 顾客" + customerId + ": " + message);
        }
    }
}

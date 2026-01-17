package lesson09;
import java.util.*;
import java.util.concurrent.Semaphore;
import java.time.*;
import java.time.format.DateTimeFormatter;

/**
 * 提高题: 如果有2个试衣间，同一时间只能容纳5个乘客进店购物，选衣服和试衣服的时间都是随机的，请编程模拟
 * 顾客进服装店的购物过程包含三个环节，选衣服，试衣服，结账离开。
 * 其中选衣服环节和试衣服环节需要的时间为 1-5秒不等（随机），结账离开环节5秒，该店只有一间试衣间（不能两人同时使用）。   
 * 请编写一个程序模拟每隔一段时间有一个个顾客进店购买的过程。程序执行过程中，输出每个顾客所处的环节信息。 
 * 比如，顾客1在试衣服，顾客2，在选衣服，顾客2在试衣服。  
 * 提示，用线程调度
 */

public class ClothStorePro {
    private static final Random RANDOM = new Random();
    private static final int MAX_TRY_CLOTH_TIME = 5; // 最大试衣时间，单位秒
    private static final int CHECKOUT_TIME = 5; // 结账时间，单位
    private static final Semaphore DRESSING_ROOM = new Semaphore(2); // 2 间试衣间
    private static final DateTimeFormatter TIME_FORMATTER = DateTimeFormatter.ofPattern("HH:mm:ss");
    private static final int MAX_CUSTOMERS_IN_STORE = 5; // 店内最大顾客数
    private static final Object STORE_CAPACITY_LOCK = new Object(); // 店内容量锁
    private static int currentCustomersInStore = 0; // 当前店内顾客数

    public static void main(String[] args) {
        int customerId = 1;
        while (true) {
            Customer customer = new Customer(customerId++);
            customer.start();
            try {
                int customerInterval = RANDOM.nextInt(1000, 3000); // 新顾客进店的间隔时间，1-2秒
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
                // 控制店内最大顾客数
                synchronized (STORE_CAPACITY_LOCK) {
                    while (currentCustomersInStore >= MAX_CUSTOMERS_IN_STORE) {
                        STORE_CAPACITY_LOCK.wait(); // 等待有空位
                    }
                    currentCustomersInStore++;
                }

                log("进入服装店，欢迎光临~");
                int selectClothTime = RANDOM.nextInt(1, MAX_TRY_CLOTH_TIME + 1);
                Thread.sleep(selectClothTime * 1000);
                log("选好衣服，排队试衣服");

                // 试衣服环节，使用试衣间锁
                synchronized (DRESSING_ROOM) {
                    log("进入试衣间，开始试衣服");
                    int tryClothTime = RANDOM.nextInt(1, MAX_TRY_CLOTH_TIME + 1);
                    Thread.sleep(tryClothTime * 1000);
                    log("试衣服完成，" + "试衣时间：" + tryClothTime + "秒");
                }

                log("准备结账");
                Thread.sleep(CHECKOUT_TIME * 1000);
                log("结账完成，离开服装店,期待下次光临~");

            } catch (InterruptedException e) {
                log("购物过程中被中断，离开服装店。");
            } finally {
                // 离开店铺，释放位置
                synchronized (STORE_CAPACITY_LOCK) {
                    currentCustomersInStore--;
                    STORE_CAPACITY_LOCK.notifyAll(); // 通知等待的顾客
                }
            }
        }

        private void log(String message) {
            String time = LocalTime.now().format(TIME_FORMATTER);
            System.out.println("[" + time + "] 顾客" + customerId + ": " + message);
        }
    }
}

package lesson09;

/** 
 * 编写一个ThreadTest类，分别通过继承Thread类和实现Runnable接口，两种方式实现两个线程。
 * 两个线程执行的任务是实现同一个变量 count 的累操作，
 * count从1增加到10，每增加1， 在控制台输出 " 执行累加操作的线程的线程名+count 变量的值，输出后该线程 休眠1秒。
 * 在主方法中测试线程操作的相关方法（包括 sleep，interrupt，join）
 */
public class ThreadTest {

    private static int count = 0;
    private static int MAX_COUNT = 20;
    private static final Object LOCK = new Object(); // 锁对象

    static class CountThread extends Thread {
        @Override
        public void run() {
            while (true) {
                // 使用类对象作为锁，确保两个线程对 count 变量的操作是同步的
                synchronized (LOCK) {
                    if (count >= MAX_COUNT) {
                        break;
                    }
                    count++;
                    System.out.println("执行累加操作的线程的线程名: " + Thread.currentThread().getName() + ", count 变量的值: " + count);
                }

                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    System.out.println(Thread.currentThread().getName() + " 被中断");
                    break;
                }
            }
        }
    }

    static class CountRunnable implements Runnable {
        @Override
        public void run() {
            while (true) {
                // 使用类对象作为锁，确保两个线程对 count 变量的操作是同步的
                synchronized (LOCK) {
                    if (count >= MAX_COUNT) {
                        break;
                    }
                    count++;
                    System.out.println("执行累加操作的线程的线程名: " + Thread.currentThread().getName() + ", count 变量的值: " + count);
                }

                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    System.out.println(Thread.currentThread().getName() + " 被中断");
                    break;
                }
            }
        }
    }

    public static void main(String[] args) {
        Thread thread1 = new CountThread();
        Thread thread2 = new Thread(new CountRunnable());

        thread1.start();
        thread2.start();

        thread1.interrupt(); // 中断第一个线程作为测试
        //thread2.interrupt(); // 中断第二个线程作为测试

        try {
            thread1.join();
            thread2.join();
        } catch (InterruptedException e) {
            System.out.println("主线程被中断");
        }

        System.out.println("所有线程执行完毕，最终 count 变量的值: " + count);
    }
}
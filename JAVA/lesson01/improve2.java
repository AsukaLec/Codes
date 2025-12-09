package lesson01;
import java.util.Scanner;
import java.util.Random;

public class improve2 {
    public static void main(String[] args) {
        double account = 0.0;
        int pass = 114514; // 默认密码；可改
        int wrongtimes = 0;

                            
        @SuppressWarnings("resource")
        Scanner scanner = new Scanner(System.in);
        Random random = new Random();//用于随机生成在线支付的金额
        System.out.println("欢迎使用ATM" + "\n" + "请输入密码: ");
        
        int password = scanner.nextInt();
        while(wrongtimes < 3 && password != pass) {
            System.out.println("密码错误， 你还有" + (3 - ++wrongtimes) + "次机会");
            password = scanner.nextInt();
        }
        if (wrongtimes == 3 && password != pass) {
            System.out.println("密码错误3次, 你的银行卡由银行保存\n 欢迎下次光临");
            System.exit(0);
        }
        wrongtimes = 0;
    
        System.out.println("请选择 操作: 1: 存款; 2: 取款; 3: 查询余额; 4: 在线支付; 0: 退出");
        int op = scanner.nextInt();
        while( op != 0) {
            switch (op) {
                case 1:
                    System.out.println("请输入存款金额: ");
                    double cur1 = scanner.nextDouble();
                    account += cur1;
                    System.out.println("存款操作成功， 当前账号余额为: " + account);
                    break;
                case 2:
                    System.out.println("请输入存款金额: ");
                    double cur2 = scanner.nextDouble();
                    account -= cur2;
                    System.out.println("存款操作成功， 当前账号余额为: " + account);
                    break;
                case 3:
                    System.out.println("当前账号余额为: " + account);
                    break;
                case 4:
                    double price = random.nextDouble() + random.nextInt(100) + 1;
                    System.out.println("本次在线支付金额为: " + price);
                    
                    System.out.println("请输入支付密码: ");
                    password = scanner.nextInt();
                    while(wrongtimes < 3 && password != pass) {
                        System.out.println("密码错误， 你还有" + (3 - ++wrongtimes) + "次机会");
                        password = scanner.nextInt();
                    }
                    if (wrongtimes == 3 && password != pass) {
                        System.out.println("密码错误3次, 你的银行卡由银行保存\n 欢迎下次光临");
                        System.exit(0);
                    }  
                    wrongtimes = 0;

                    account -= price;

                    System.out.println("在线支付操作成功， 当前账号余额为: " + account);
                    break;
            }
            op = scanner.nextInt();
        }
        System.out.println("欢迎下次光临!");
    }
}

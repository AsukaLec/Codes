package lesson04;

import java.util.Scanner;
import java.util.Random;

/**
 * 编写一个程序模拟银行ATM交易系统：

    要求 ：

    银联卡功能： 验证密码，查账余额，取钱，存钱，计算利息（按日计息，余额变动当日计息）

    工行卡：除银联卡功能外，还支持在线支付，

    农行卡：除支持银联卡功能外，还支持微信支付

    广发卡：除支持银联卡功能外，同时支持微信支付和在线支付

    ATM机：支持所有银行卡，插入不同功能的银行卡，功能菜单不一样

    要求 : ATM机 适配所有的银行卡，发行一张新的银联卡，已有的atm机也能适配。
            新的ATM机要拓展新的功能，不要修改已有的功能代码。
 */
public class ATM { 
    public static void main(String[] args) {
        @SuppressWarnings("resource")
        Scanner sc = new Scanner(System.in);

        System.out.println("欢迎光临银联ATM机!");
        System.out.println("请输入银行卡类型(1-工行卡, 2-农行卡, 3-广发卡, 4-其他卡): "); // 可新增卡类型
        int cardType = sc.nextInt();
        System.out.print("请输入密码: ");
        String password = sc.next();

        switch (cardType) { // 可加入卡类型
            case 1:
                ICBCCard ICBC_Card = new ICBCCard(password);
                System.out.println("请选择: 1-验证密码, 2-查账余额, 3-取钱, 4-存钱, 5-计算利息, 6-在线支付, 0-退出");
                int choice_of_ICBC = sc.nextInt();
                while (choice_of_ICBC != 0) {
                        switch (choice_of_ICBC) {
                            case 1:
                                System.out.print("请输入密码: ");
                                String pwd = sc.next();
                                if (ICBC_Card.verifyPassword(pwd)) {
                                    System.out.println("密码验证成功!");
                                } else {
                                    System.out.println("密码验证失败!");
                                }
                                break;
                            case 2:
                                System.out.println("当前余额: " + ICBC_Card.getBalance() + "元");
                                break;
                            case 3:
                                System.out.print("请输入密码: ");
                                pwd = sc.next();
                                if (ICBC_Card.verifyPassword(pwd)) {
                                    System.out.println("密码验证成功!");
                                    System.out.println("请输入取款金额: ");
                                    double withdrawAmount = sc.nextDouble();
                                    ICBC_Card.withdraw(withdrawAmount);
                                    System.out.println("当前账号余额: " + ICBC_Card.getBalance() + "元");
                                } else {
                                    System.out.println("密码验证失败!请重新验证");
                                }
                                break;
                            case 4:
                                System.out.println("请输入存款金额: ");
                                double depositAmount = sc.nextDouble();
                                ICBC_Card.deposit(depositAmount);
                                break;
                            case 5:
                                System.out.println("请输入存款天数: ");
                                int days = sc.nextInt();
                                double interest = ICBC_Card.caculateInterst(days);
                                System.out.println("利息: " + interest + "元");
                                break;
                            case 6:
                                System.out.print("请输入密码: ");
                                pwd = sc.next();
                                if (ICBC_Card.verifyPassword(pwd)) {
                                    System.out.println("密码验证成功!");
                                    System.out.println("请输入在线支付金额: ");
                                    double onlineAmount = sc.nextDouble();
                                    ICBC_Card.onlinePayment(onlineAmount);
                                    System.out.println("当前账号余额: " + ICBC_Card.getBalance() + "元");
                                } else {
                                    System.out.println("密码验证失败!请重新验证");
                                }
                                break;
                            default:
                                System.out.println("无效选择，请重新选择.");
                        }
                        System.out.println();
                        System.out.println("请选择: 1-验证密码, 2-查账余额, 3-取钱, 4-存钱, 5-计算利息, 6-在线支付, 0-退出");
                        choice_of_ICBC = sc.nextInt();
                }
                System.out.println("欢迎下次光临！再见！");
                break;
        
            case 2:
                ABCCard ABC_Card = new ABCCard(password);
                System.out.println("请选择: 1-验证密码, 2-查账余额, 3-取钱, 4-存钱, 5-计算利息, 6-微信支付, 0-退出");
                int choice_of_ABC = sc.nextInt();
                while (choice_of_ABC != 0) {
                        switch (choice_of_ABC) {
                            case 1:
                                System.out.print("请输入密码: ");
                                String pwd = sc.next();
                                if (ABC_Card.verifyPassword(pwd)) {
                                    System.out.println("密码验证成功!");
                                } else {
                                    System.out.println("密码验证失败!");
                                }
                                break;
                            case 2:
                                System.out.println("当前余额: " + ABC_Card.getBalance() + "元");
                                break;
                            case 3:
                                System.out.print("请输入密码: ");
                                pwd = sc.next();
                                if (ABC_Card.verifyPassword(pwd)) {
                                    System.out.println("密码验证成功!");
                                    System.out.println("请输入取款金额: ");
                                    double withdrawAmount = sc.nextDouble();
                                    ABC_Card.withdraw(withdrawAmount);
                                    System.out.println("当前账号余额: " + ABC_Card.getBalance() + "元");
                                } else {
                                    System.out.println("密码验证失败!请重新验证");
                                }
                                break;
                            case 4:
                                System.out.println("请输入存款金额: ");
                                double depositAmount = sc.nextDouble();
                                ABC_Card.deposit(depositAmount);
                                break;
                            case 5:
                                System.out.println("请输入存款天数: ");
                                int days = sc.nextInt();
                                double interest = ABC_Card.caculateInterst(days);
                                System.out.println("利息: " + interest + "元");
                                break;
                            case 6:
                                System.out.print("请输入密码: ");
                                pwd = sc.next();
                                if (ABC_Card.verifyPassword(pwd)) {
                                    System.out.println("密码验证成功!");
                                    System.out.println("请输入微信支付金额: ");
                                    double wechatPayment = sc.nextDouble();
                                    ABC_Card.wechatPayment(wechatPayment);
                                    System.out.println("当前账号余额: " + ABC_Card.getBalance() + "元");
                                } else {
                                    System.out.println("密码验证失败!请重新验证");
                                }
                                break;
                            default:
                                System.out.println("无效选择，请重新选择.");
                        }
                        System.out.println();
                        System.out.println("请选择: 1-验证密码, 2-查账余额, 3-取钱, 4-存钱, 5-计算利息, 6-在线支付, 0-退出");
                        choice_of_ABC = sc.nextInt();
                }
                System.out.println("欢迎下次光临！再见！");
                break;

            case 3:
                GFCard GF_Card = new GFCard(password);
                System.out.println("请选择: 1-验证密码, 2-查账余额, 3-取钱, 4-存钱, 5-计算利息, 6-在线支付, 7-微信支付, 0-退出");
                int choice_of_GFC = sc.nextInt();
                while (choice_of_GFC != 0) {
                        switch (choice_of_GFC) {
                            case 1:
                                System.out.print("请输入密码: ");
                                String pwd = sc.next();
                                if (GF_Card.verifyPassword(pwd)) {
                                    System.out.println("密码验证成功!");
                                } else {
                                    System.out.println("密码验证失败!");
                                }
                                break;
                            case 2:
                                System.out.println("当前账号余额: " + GF_Card.getBalance() + "元");
                                break;
                            case 3:
                                System.out.print("请输入密码: ");
                                pwd = sc.next();
                                if (GF_Card.verifyPassword(pwd)) {
                                    System.out.println("密码验证成功!");
                                    System.out.println("请输入取款金额: ");
                                    double withdrawAmount = sc.nextDouble();
                                    GF_Card.withdraw(withdrawAmount);
                                    System.out.println("当前账号余额: " + GF_Card.getBalance() + "元");
                                } else {
                                    System.out.println("密码验证失败!请重新验证");
                                }
                                break;
                            case 4:
                                System.out.println("请输入存款金额: ");
                                double depositAmount = sc.nextDouble();
                                GF_Card.deposit(depositAmount);
                                break;
                            case 5:
                                System.out.println("请输入存款天数: ");
                                int days = sc.nextInt();
                                double interest = GF_Card.caculateInterst(days);
                                System.out.println("利息: " + interest + "元");
                                break;
                            case 6:
                                System.out.print("请输入密码: ");
                                pwd = sc.next();
                                if (GF_Card.verifyPassword(pwd)) {
                                    System.out.println("密码验证成功!");
                                    System.out.println("请输入在线支付金额: ");
                                    double wechatPayment = sc.nextDouble();
                                    GF_Card.wechatPayment(wechatPayment);
                                    System.out.println("当前账号余额: " + GF_Card.getBalance() + "元");                                    
                                } else {
                                    System.out.println("密码验证失败!请重新验证");
                                }
                                break;
                            case 7:
                                System.out.print("请输入密码: ");
                                pwd = sc.next();
                                if (GF_Card.verifyPassword(pwd)) {
                                    System.out.println("密码验证成功!");
                                    System.out.println("请输入微信支付金额: ");
                                    double wechatPayment = sc.nextDouble();
                                    GF_Card.wechatPayment(wechatPayment);
                                    System.out.println("当前账号余额: " + GF_Card.getBalance() + "元");                                    
                                } else {
                                    System.out.println("密码验证失败!请重新验证");
                                }
                                break;
                            default:
                                System.out.println("无效选择，请重新选择.");
                        }
                        System.out.println();
                        System.out.println("请选择: 1-验证密码, 2-查账余额, 3-取钱, 4-存钱, 5-计算利息, 6-在线支付, 7-微信支付, 0-退出");
                        choice_of_GFC = sc.nextInt();
                }
                System.out.println("欢迎下次光临！再见！");
                break;
                
                //新增卡类型
        }   
    }
}


/**银联卡父类 */
class UnionPayCard {
    String _cardname;
    private String _password = "12345678"; // defult password
    private double _balance;
    double _interestRate = 0.0001;

    public UnionPayCard(String cardname, String password) {
        Random rand = new Random();
        _cardname = cardname;
        _password = password;
        _balance = rand.nextDouble()*10000 + 1000.0;
        _balance = Math.round(_balance * 100.0) / 100.0;
    }

    public boolean verifyPassword(String password) {
        return _password.equals(password);
    }

    public void setPassword(String oldPassword, String newPassword) {
        if( !verifyPassword(oldPassword) ) {
            System.out.println("旧密码错误，修改密码失败！");
            return;
        }
        _password = newPassword;
    } 

    public double getBalance() {
        return _balance;
    }

    public void chengeBalance(double amount) {
        _balance += amount;
    }

    public void deposit(double amount) {
        _balance += amount;
        System.out.println("存款" + amount + "元成功! 当前账号余额为: " + _balance + "元");
    }

    public boolean withdraw(double amount) {
        if( amount > _balance) {
            System.out.println("余额不足，取款失败！");
            return false;
        } else {
            _balance -= amount;
            System.out.println("取款" + amount + "元成功");
            return true;
        }
    }

    public void setInterestRate(double rate) {
        _interestRate = rate;
    }

    public double caculateInterst (int days) {
        return _balance * _interestRate * days;
    }
}

class ICBCCard extends UnionPayCard {
    public ICBCCard(String password) {
        super("银联工行卡", password);
    }

    public boolean onlinePayment(double amount) {
        if( amount > this.getBalance()) {
            System.out.println("余额不足，在线支付失败！");
            return false;
        } else {
            this.chengeBalance(-amount);
            System.out.println("在线支付" + amount + "元成功");
            return true;
        }
    }
}

class ABCCard extends UnionPayCard {
    public ABCCard(String password) {
        super("银联农行卡", password);
    }

    public boolean wechatPayment(double amount) {
        if( amount > this.getBalance()) {
            System.out.println("余额不足，微信支付失败！");
            return false;
        } else {
            this.chengeBalance(-amount);
            System.out.println("微信支付" + amount + "元成功");
            return true;
        }
    }
}

class GFCard extends UnionPayCard {
    public GFCard(String password) {
        super("银联广发卡", password);
    }

    public boolean onlinePayment(double amount) {
        if( amount > this.getBalance()) {
            System.out.println("余额不足，在线支付失败！");
            return false;
        } else {
            this.chengeBalance(-amount);
            System.out.println("在线支付" + amount + "元成功");
            return true;
        }
    }

    public boolean wechatPayment(double amount) {
        if( amount > this.getBalance()) {
            System.out.println("余额不足，微信支付失败！");
            return false;
        } else {
            this.chengeBalance(-amount);
            System.out.println("微信支付" + amount + "元成功");
            return true;
        }
    }
}


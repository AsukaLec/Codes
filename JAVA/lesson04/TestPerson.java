package lesson04;

import java.util.Scanner;
/*
Penson 类（属性:name ，gender，age；方法:say（））

Father类 （属性:name ，gender，age ；方法 : say （）:chinese，drive（）:car）

Son类（属性:name ，gender，age ；方法: say（）:English,Chinese，drive（）:airplane，）

编写完成以上类，实现继承关系。

编写一个测试类 TestPerson，在测试类中实现多态-，Person 根据用户输入 （1 代表fathen，2代表son） 调用相应对象的方法。
 */

public class TestPerson {
    public static void main(String[] args) {
        @SuppressWarnings("resource")
        Scanner scanner = new Scanner(System.in);
        while(true) {
            System.out.println();
            System.out.print("请输入一个数字 (1代表father, 2代表son, 3代表推出): ");

            int choice = scanner.nextInt(); // 1代表father, 2代表son
            Person p;
            if (choice == 1) {
            p = new Fatehr();
            System.out.println(p.say());
            System.out.println(((Fatehr) p).drive());
            } else if (choice == 2) {
            p = new Son();
            System.out.println(p.say());
            System.out.println((p).drive());
            } else if (choice == 3) {
                System.out.println("Exiting the program.");
                break;
            } else {
            System.out.println("Invalid choice.");
            }
        }

    }
}

class Person {
    String name, gender;
    int age;
    
    public String say() {
        return ("I'm a Person.");
    }
    public String drive() {
        return ("I can drive something.");
    }
}

class Fatehr extends Person {
    String name, gender;
    int age;

    public String say() {
        return ("I'm a Father. I can speak Chinese.");
    }
    public String drive() {
        return ("I can drive a car.");
    }
}

class Son extends Person {
    String name, gender;
    int age;

    public String say() {
        return ("I'm a Son. I can speak English and Chinese.");
    }
    public String drive() {
        return ("I can drive an airplane.");
    }
}


package lesson04;
import java.util.Scanner;
/** 
某租赁公司 为了满足不同客户的需求，准备了 有以下几种交通工具，

这些交通工具都具有一个共同属性 载客量：personCapacity;
有两个共同的方法 显示载客量 ： showCapacity（）；显示功能：showfunction（）
它们能满足不同情况下的交通需求：
轿车 能 跑 （run），
飞机 能 跑（run） 也能飞（fly）；
轮船 能 游 （swim）
水上飞机 能 飞（fly） 也能 游（swim）
水陆两用飞机 能 跑（run） 能 飞（fly） 也能游（swim）

请使编写程序，实现交通工具类，方便用户选择该交通工具时，能输出它的载客量和功能。

在测试类中 测试通过

编码码要求体现面向对象的编程思想：封装，继承和多态
*/

public class TestForTransportation {
    public static void main(String[] args) {
        @SuppressWarnings("resource")
        Scanner scanner = new Scanner(System.in);
        System.out.println("1 standfor Car, 2 standfor Plane, 3 standfor Ship, 4 standfor Seaplane, 5 standfor AmphibiousPlane");
        while(true) {
            System.out.println();
             System.out.print("Choose a traffic tool to see its capacity and function: ");

            int choice = scanner.nextInt(); // 1代表Car, 2代表Plane, 3代表Ship, 4代表Seaplane, 5代表AmphibiousPlane
            Transportations t;
            if (choice == 1) {
                t = new Car();
                System.out.println(t.showCapacity());
                System.out.println(t.showFunction());
            } else if (choice == 2) {
                t = new Plane();
                System.out.println(t.showCapacity());
                System.out.println(t.showFunction());
            } else if (choice == 3) {
                t = new Ship();
                System.out.println(t.showCapacity());
                System.out.println(t.showFunction());
            } else if (choice == 4) {
                t = new Seaplane();
                System.out.println(t.showCapacity());
                System.out.println(t.showFunction());
            } else if (choice == 5) {
                t = new AmphibiousPlane();
                System.out.println(t.showCapacity());
                System.out.println(t.showFunction());
            } else {
                System.out.println("Invalid choice.");
            }
        }
    }
}

class Transportations {
    int _personCapacity = 114514;
    public String showCapacity() {
        return ("This tool can carry " + _personCapacity + " people.");
    }
    public String showFunction() {
        return ("This tool has some functions.");
    }
}

class Car extends Transportations {
    int _personCapacity = 5;
    public String showCapacity() {
        return ("This car can carry " + _personCapacity + " people.");
    }
    public String showFunction() {
        return ("This car can run.");
    }
}

class Plane extends Transportations {
    int _personCapacity = 150;
    public String showCapacity() {
        return ("This plane can carry " + _personCapacity + " people.");
    }
}

class Ship extends Transportations {
    int _personCapacity = 300;
    public String showCapacity() {
        return ("This ship can carry " + _personCapacity + " people.");
    }
    public String showFunction() {
        return ("This ship can swim.");
    }
}

class Seaplane extends Plane {
    int _personCapacity = 12;
    public String showCapacity() {
        return ("This seaplane can carry " + _personCapacity + " people.");
    }
    public String showFunction() {
        return ("This seaplane can fly and swim.");
    }
}

class AmphibiousPlane extends Seaplane {
    int _personCapacity = 8;
    public String showCapacity() {
        return ("This amphibious plane can carry " + _personCapacity + " people.");
    }
    public String showFunction() {
        return ("This amphibious plane can run, fly and swim.");
    }
}

package lesson04;
import java.util.Scanner;
/**
类的设计应用：
计算机组装店有很多品牌的计算机配件，包括处理器（CPU）、主板(mainBoard)、内存(Ram)、……等。 每种配件都多个厂家（company）、型号（type）、价格（price）等至少三个基本信息。
按下图所示的类的关系和要求编写适当的类，实现相关的功能。

1、假设每种配件有两个厂家，每个厂家产品有两个型号，每个型号价格不同

2、程序运行时逐个显示不同配件的型号，提供 配件型号选择菜单（如输入1，代表选择型号1，输入2，代码选择型号2）

3、根据选择的配件型号，创造出一个Computer实例，

4、 创建实例完成时，输出总价格

5、调用Conputer实例的showDetail()方法，输出输出配件的详细信息。

根据类图完成类的设置，并在Test类的main方法中测试你的程序 
*/
public class TestForComputer {
    
    public static void main(String[] args) {
        @SuppressWarnings("resource")
        Scanner scanner = new Scanner(System.in);

        CPU cpu1 = new CPU("Intel", "i7-13700K", 3199.0, "3.4GHz");
        CPU cpu2 = new CPU("AMD", "Ryzen 9 7900X", 3299.0, "4.7GHz");
        Ram ram1 = new Ram("Corsair", "Vengeance LPX 16GB", 599.0, "16GB");
        Ram ram2 = new Ram("G.Skill", "Trident Z RGB 32GB", 1299.0, "32GB");
        mainBoard mb1 = new mainBoard("ASUS", "ROG STRIX Z790-E", 2999.0, "ATX");
        mainBoard mb2 = new mainBoard("MSI", "MAG B650 TOMAHAWK WIFI", 2199.0, "ATX");
        GraphicCard gc1 = new GraphicCard("NVIDIA", "GeForce RTX 4070 Ti", 4999.0, "12GB");
        GraphicCard gc2 = new GraphicCard("AMD", "Radeon RX 7900 XT", 4499.0, "20GB");
        HDD hdd1 = new HDD("Samsung", "970 EVO Plus 1TB", 1299.0, "1TB");
        HDD hdd2 = new HDD("Western Digital", "Blue SN570 1TB", 999.0, "1TB");

        CPU cpu; Ram ram; mainBoard mb; GraphicCard gc; HDD hdd;

        System.out.println("Welcome to the Computer DIY Store!");
        System.out.println("Choose your favorite components and assemble your own PC: ");

        System.out.println(cpu1.getCpu());
        System.out.println(cpu2.getCpu());
        System.out.print("Select CPU (1 or 2): ");
        int cpuChoice = scanner.nextInt();
        if (cpuChoice == 1) {
            cpu = cpu1;
        } else {
            cpu = cpu2;
        } System.out.println();

        System.out.println(ram1.getRam());
        System.out.println(ram2.getRam());
        System.out.print("Select RAM (1 or 2): ");
        int ramChoice = scanner.nextInt();
        if (ramChoice == 1) {
            ram = ram1;
        } else {
            ram = ram2;
        }System.out.println();

        System.out.println(mb1.getMb());
        System.out.println(mb2.getMb());
        System.out.print("Select MainBoard (1 or 2): ");
        int mbChoice = scanner.nextInt();
        if (mbChoice == 1) {
            mb = mb1;
        } else {
            mb = mb2;
        }System.out.println();

        System.out.println(gc1.getGc());
        System.out.println(gc2.getGc());
        System.out.print("Select GraphicCard (1 or 2): ");
        int gcChoice = scanner.nextInt();
        if (gcChoice == 1) {
            gc = gc1;
        } else {
            gc = gc2;
        }System.out.println();

        System.out.println(hdd1.getHdd());
        System.out.println(hdd2.getHdd());
        System.out.print("Select HDD (1 or 2): ");
        int hddChoice = scanner.nextInt();
        if (hddChoice == 1) {
            hdd = hdd1;
        } else {
            hdd = hdd2;
        }System.out.println();

        Computer myComputer = new Computer(cpu, ram, mb, gc, hdd);
        System.out.println("Total Price: " + myComputer.getSumPrice());
        System.out.println("Assembled Computer Details: [Producer: " + myComputer._producer + ", Name: " + myComputer._name + ", Type: " + myComputer._type + ", Price:" + myComputer.getSumPrice() + "]");
        System.out.println("Aeccesory Parts: ");
        myComputer.showDetail();
    }   
}

class Hardware {
    String _company, _type;
    double _price;

    public Hardware(String company, String type, double price) {
        _company = company;
        _type = type;
        _price = price;
    }
    public String getCompany() {
        return _company;
    }
    public void setCompany(String company) {
        _company = company;
    }
    public String getType() {
        return _type;
    }
    public void setType(String type) {
        _type = type;
    }
    public double getPrice() {
        return _price;
    }
    public void setPrice(double price) {
        _price = price;
    }
}

class HDD extends Hardware {
    String _name = "HDD";
    String _storage;
    
    public HDD(String company, String type, double price, String storage) { //硬盘可能不止一块 
        super(company, type, price);
        _storage = storage;
    }
    public String getHdd(){
        return ("HDD: [Producer: " + getCompany() + ", Name: " + _name + ", Type: " + getType() + ", Price: " + getPrice() + ", Storage: " + _storage + "]");
    }
}

class CPU extends Hardware {
    String _name = "CPU";
    String _frequency;
    
    public CPU(String company, String type, double price, String frequency) {
        super(company, type, price);
        _frequency = frequency;
    }

    public String getCpu(){
        return ("CPU: [Producer: " + getCompany() + ", Name: " + _name + ", Type: " + getType() + ", Price: " + getPrice() + ", Frequency: " + _frequency + "]");
    }
}

class Ram extends Hardware {
    String _name = "Ram";
    String _capacity;
    
    public Ram(String company, String type, double price, String capacity) { 
        super(company, type, price);
        _capacity = capacity;
    }
    public String getRam(){
        return ("Ram: [Producer: " + getCompany() + ", Name: " + _name + ", Type: " + getType() + ", Price: " + getPrice() + ", Capacity: " + _capacity + "]");
    }
}

class mainBoard extends Hardware {
    String _name = "mainBoard";
    String _size;
    
    public mainBoard(String company, String type, double price, String size) {
        super(company, type, price);
        _size = size;
    }
    public String getMb(){
        return ("MainBoard: [Producer: " + getCompany() + ", Name: " + _name + ", Type: " + getType() + ", Price: " + getPrice() + ", Size: " + _size + "]");
    }
}   

class GraphicCard extends Hardware {
    String _name = "GraphicCard";
    String _memory;
    
    public GraphicCard(String company, String type, double price, String memory) {
        super(company, type, price);
        _memory = memory;
    }
    public String getGc(){
        return ("GraphicCard: [Producer: " + getCompany() + ", Name: " + _name + ", Type: " + getType() + ", Price: " + getPrice() + ", Memory: " + _memory + "]");
    }
}

class Computer {
    CPU cpu;
    Ram ram;
    mainBoard mb;
    GraphicCard gc;
    HDD hdd;
    String _producer = "DIY";
    String _name = "Assembled Computer";
    String _type = "NULL";

    public Computer(CPU cpu, Ram ram, mainBoard mb, GraphicCard gc, HDD hdd) {
        this.cpu = cpu;
        this.ram = ram;
        this.mb = mb;
        this.gc = gc;
        this.hdd = hdd;
    }
    
    public double getSumPrice() {
        return cpu.getPrice() + ram.getPrice() + mb.getPrice() + gc.getPrice() + hdd.getPrice();
    }

    public String getHdd(){
        return ("HDD: [Producer: " + hdd.getCompany() + ", Name: " + hdd._name + ", Type: " + hdd.getType() + ", Price: " + hdd.getPrice() + ", Storage: " + hdd._storage + "]");
    }

    public String getRam(){
        return ("Ram: [Producer: " + ram.getCompany() + ", Name: " + ram._name + ", Type: " + ram.getType() + ", Price: " + ram.getPrice() + ", Capacity: " + ram._capacity + "]");
    }
    public String getMb(){
        return ("MainBoard: [Producer: " + mb.getCompany() + ", Name: " + mb._name + ", Type: " + mb.getType() + ", Price: " + mb.getPrice() + ", Size: " + mb._size + "]");
    }
    public String getGc(){
        return ("GraphicCard: [Producer: " + gc.getCompany() + ", Name: " + gc._name + ", Type: " + gc.getType() + ", Price: " + gc.getPrice() + ", Memory: " + gc._memory + "]");
    }
    public String getCpu(){
        return ("CPU: [Producer: " + cpu.getCompany() + ", Name: " + cpu._name + ", Type: " + cpu.getType() + ", Price: " + cpu.getPrice() + ", Frequency: " + cpu._frequency + "]");
    }

    public void showDetail() {
        System.out.println(getHdd());
        System.out.println(getRam());
        System.out.println(getMb());
        System.out.println(getGc());
        System.out.println(getCpu());
    }
}
package lesson07;

import java.util.ArrayList;
import java.util.List;

public class Employee { // 员工类
	private String name; // 姓名
	private int age; // 年龄
	private double salary; // 工资
	private String sex; // 性别
	private String dept; // 部门

	// 构造方法
	public Employee(String name, int age, double salary, String sex, String dept) {
		this.name = name;
		this.age = age;
		this.salary = salary;
		this.sex = sex;
		this.dept = dept;
	}

	// 重写此方法，方便打印输出员工信息
	public String toString() {
		return "name=" + name + ", age=" + age + ", salary=" + salary + ", sex=" + sex + ", dept=" + dept;
	}

	// 以下是员工属性的getter方法
	public String getName() {
		return name;
	}

	public int getAge() {
		return age;
	}

	public double getSalary() {
		return salary;
	}

	public String getSex() {
		return sex;
	}

	public String getDept() {
		return dept;
	}

	static List<Employee> getEmpList() { // 提供数据初始化方法
		List<Employee> list = new ArrayList<Employee>();
		// 添加员工数据
		list.add(new Employee("老张", 40, 9000, "男", "运营部"));
		list.add(new Employee("小刘", 24, 5000, "女", "开发部"));
		list.add(new Employee("大刚", 32, 7500, "男", "销售部"));
		list.add(new Employee("翠花", 28, 5500, "女", "销售部"));
		list.add(new Employee("小马", 21, 3000, "男", "开发部"));
		list.add(new Employee("老王", 35, 6000, "女", "人事部"));
		list.add(new Employee("小王", 21, 3000, "女", "人事部"));
		return list;
	}
}

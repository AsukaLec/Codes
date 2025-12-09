package lesson07;

import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;
/**
 * 1、lambda表达式基础：
 * 编写一个名字为 Sortable 的函数式接口，接口的方法定义为 int[] sort(int arr[]）.
 * 使用lambda表达式创建实现Sortable接口的对象s，s的应用java.util.Arrays类的提供排序方法对数组[,7,1,3,5,44,23,78,99,21]进行排序。
 * 
 * 2、计算阶乘： 通过Function接口创建匿名方法，该方法返回一个整数的阶乘
 * 
 * 3、结合课本P259-275 中 Stream相关内容使用课本中的数据集和流处理知识完成以下操作：
 * 3.1  统计男员工的总人数
 * 3.2 找出所有薪酬大于5000元的女工
 * 3.3 找出大于平均年龄的员工
 * 3.4  排序：先按性别（女性在前），性别相同则按年龄（从小到大），年龄相同则按薪水（从大到小
 * 
 * 
 * 4. 使用附件中Employee类文件的获取雇员集合，运用Stream的相关知识，
 * 按部门统计不同性别员工的平均工资。 
 */

public class assignment1 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        //task 1 :     
        int[] arr = {7,1,3,5,44,23,78,99,21};
        
        Sortable s = (a) -> {
            Arrays.sort(a);
            return a;
        };

        // Sortable s = new Sortable() {
        //     @Override
        //     public int[] sort(int[] arr) {
        //         Arrays.sort(arr);   // 同样的实现
        //         return arr;
        //     }
        // };

        int[] sortedArr = s.sort(arr);
        System.out.println("Sorted array: " + Arrays.toString(sortedArr));
        System.out.println();

        
        //task2
        System.out.print("please input a number: ");
        long x = sc.nextInt();
        System.out.print("its factorial: ");

		Function<Long,Long> fn = n ->{
			long sum =1L;
			for(int i=2;i<=n;i++) {
				sum *=i;
			}
			return sum;
		};		
		System.out.println(fn.apply(x));


        //task 3
        System.out.println();
        System.out.println(" Stream 实现统计：");	
        
        List<Employee> list = Employee.getEmpList();
        //3.1 
        long malecount = list.stream().filter(e-> e.getSex().equals("男")).count();
        System.out.println("男员工总人数： " + malecount);
        System.out.println();

        //3.2
        System.out.println("所有薪酬大于5000元的女工");
        List<Employee> felist = list.stream().filter(e-> e.getSalary()> 5000 && e.getSex().equals("女")).toList();
        for (Employee worker : felist) {
            System.out.println(worker.toString());
        }
        System.out.println();

        //3.3
        System.out.println("大于平均年龄的员工");
        double avg = list.stream().collect(Collectors.averagingDouble(e-> e.getAge()));
        List<Employee> wlist = list.stream().filter(e-> e.getAge() > avg).toList();
        wlist.forEach(e-> System.out.println(e.toString()));
        System.out.println();

        //3.4 排序：先按性别（女性在前），性别相同则按年龄（从小到大），年龄相同则按薪水（从大到小
        System.out.println("排序结果： ");
        List<Employee> sorted = list.stream().sorted((e1, e2) -> {
            double n = e1.getSex().compareTo(e2.getSex());
            //性别相同
            if (n == 0) {
                n = e1.getAge()-e2.getAge();
                //年龄相同
                if(n == 0) {n = e2.getSalary() - e1.getSalary(); return (n>0)?1:-1;}
                return (n>0)?1:-1;
            }
            return (n>0)?1:-1;
        }).toList();

        sorted.forEach(e -> System.out.println(e.toString()));

        //4 按部门统计不同性别员工的平均工资。
        Map<String,Map<String,Double>> map = list.stream().collect(Collectors.groupingBy(e->e.getDept(),Collectors.groupingBy(e->e.getSex(),Collectors.averagingDouble(e->e.getSalary()))));
        map.keySet().forEach(
            key ->{ 
                System.out.println(key+":");
                map.get(key).keySet().forEach(
                        key2->{
                            System.out.println("  "+key2+":"+ map.get(key).get(key2));    						  
                        });
            });

        sc.close();
    }

    
    @FunctionalInterface
    public interface Sortable {
        int[] sort(int arr[]);
    }

}






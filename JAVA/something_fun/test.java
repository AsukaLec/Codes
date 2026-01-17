package something_fun;


public class test{

  public static void main(String args[]){
      // String aaa = "wdnmd";
      // String bbb = aaa.replace(aaa, "wdnmd111");
      // System.out.println(bbb);
      String a = "Aababajjadjfj";
      a = a.toLowerCase();
      System.out.println(a);

      String s = "package lesson07;\r\n" + //
                "\r\n" + //
                "import java.util.*;\r\n" + //
                "import java.util.function.Function;\r\n" + //
                "import java.util.stream.Collectors;\r\n" + //
                "/**\r\n" + //
                " * 1、lambda表达式基础：\r\n" + //
                " * 编写一个名字为 Sortable 的函数式接口，接口的方法定义为 int[] sort(int arr[]）.\r\n" + //
                " * 使用lambda表达式创建实现Sortable接口的对象s，s的应用java.util.Arrays类的提供排序方法对数组[,7,1,3,5,44,23,78,99,21]进行排序。\r\n" + //
                " * \r\n" + //
                " * 2、计算阶乘： 通过Function接口创建匿名方法，该方法返回一个整数的阶乘\r\n" + //
                " * \r\n" + //
                " * 3、结合课本P259-275 中 Stream相关内容使用课本中的数据集和流处理知识完成以下操作：\r\n" + //
                " * 3.1  统计男员工的总人数\r\n" + //
                " * 3.2 找出所有薪酬大于5000元的女工\r\n" + //
                " * 3.3 找出大于平均年龄的员工\r\n" + //
                " * 3.4  排序：先按性别（女性在前），性别相同则按年龄（从小到大），年龄相同则按薪水（从大到小\r\n" + //
                " * \r\n" + //
                " * \r\n" + //
                " * 4. 使用附件中Employee类文件的获取雇员集合，运用Stream的相关知识，\r\n" + //
                " * 按部门统计不同性别员工的平均工资。 \r\n" + //
                " */\r\n" + //
                "\r\n" + //
                "public class assignment1 {\r\n" + //
                "    public static void main(String[] args) {\r\n" + //
                "        Scanner sc = new Scanner(System.in);\r\n" + //
                "\r\n" + //
                "        //task 1 :     \r\n" + //
                "        int[] arr = {7,1,3,5,44,23,78,99,21};\r\n" + //
                "        \r\n" + //
                "        Sortable s = (a) -> {\r\n" + //
                "            Arrays.sort(a);\r\n" + //
                "            return a;\r\n" + //
                "        };\r\n" + //
                "\r\n" + //
                "        // Sortable s = new Sortable() {\r\n" + //
                "        //     @Override\r\n" + //
                "        //     public int[] sort(int[] arr) {\r\n" + //
                "        //         Arrays.sort(arr);   // 同样的实现\r\n" + //
                "        //         return arr;\r\n" + //
                "        //     }\r\n" + //
                "        // };\r\n" + //
                "\r\n" + //
                "        int[] sortedArr = s.sort(arr);\r\n" + //
                "        System.out.println(\"Sorted array: \" + Arrays.toString(sortedArr));\r\n" + //
                "        System.out.println();\r\n" + //
                "\r\n" + //
                "        \r\n" + //
                "        //task2\r\n" + //
                "        System.out.print(\"please input a number: \");\r\n" + //
                "        long x = sc.nextInt();\r\n" + //
                "        System.out.print(\"its factorial: \");\r\n" + //
                "\r\n" + //
                "\t\tFunction<Long,Long> fn = n ->{\r\n" + //
                "\t\t\tlong sum =1L;\r\n" + //
                "\t\t\tfor(int i=2;i<=n;i++) {\r\n" + //
                "\t\t\t\tsum *=i;\r\n" + //
                "\t\t\t}\r\n" + //
                "\t\t\treturn sum;\r\n" + //
                "\t\t};\t\t\r\n" + //
                "\t\tSystem.out.println(fn.apply(x));\r\n" + //
                "\r\n" + //
                "\r\n" + //
                "        //task 3\r\n" + //
                "        System.out.println();\r\n" + //
                "        System.out.println(\" Stream 实现统计：\");\t\r\n" + //
                "        \r\n" + //
                "        List<Employee> list = Employee.getEmpList();\r\n" + //
                "        //3.1 \r\n" + //
                "        long malecount = list.stream().filter(e-> e.getSex().equals(\"男\")).count();\r\n" + //
                "        System.out.println(\"男员工总人数： \" + malecount);\r\n" + //
                "        System.out.println();\r\n" + //
                "\r\n" + //
                "        //3.2\r\n" + //
                "        System.out.println(\"所有薪酬大于5000元的女工\");\r\n" + //
                "        List<Employee> felist = list.stream().filter(e-> e.getSalary()> 5000 && e.getSex().equals(\"女\")).toList();\r\n" + //
                "        for (Employee worker : felist) {\r\n" + //
                "            System.out.println(worker.toString());\r\n" + //
                "        }\r\n" + //
                "        System.out.println();\r\n" + //
                "\r\n" + //
                "        //3.3\r\n" + //
                "        System.out.println(\"大于平均年龄的员工\");\r\n" + //
                "        double avg = list.stream().collect(Collectors.averagingDouble(e-> e.getAge()));\r\n" + //
                "        List<Employee> wlist = list.stream().filter(e-> e.getAge() > avg).toList();\r\n" + //
                "        wlist.forEach(e-> System.out.println(e.toString()));\r\n" + //
                "        System.out.println();\r\n" + //
                "\r\n" + //
                "        //3.4 排序：先按性别（女性在前），性别相同则按年龄（从小到大），年龄相同则按薪水（从大到小\r\n" + //
                "        System.out.println(\"排序结果： \");\r\n" + //
                "        List<Employee> sorted = list.stream().sorted((e1, e2) -> {\r\n" + //
                "            double n = e1.getSex().compareTo(e2.getSex());\r\n" + //
                "            //性别相同\r\n" + //
                "            if (n == 0) {\r\n" + //
                "                n = e1.getAge()-e2.getAge();\r\n" + //
                "                //年龄相同\r\n" + //
                "                if(n == 0) {n = e2.getSalary() - e1.getSalary(); return (n>0)?1:-1;}\r\n" + //
                "                return (n>0)?1:-1;\r\n" + //
                "            }\r\n" + //
                "            return (n>0)?1:-1;\r\n" + //
                "        }).toList();\r\n" + //
                "\r\n" + //
                "        sorted.forEach(e -> System.out.println(e.toString()));\r\n" + //
                "\r\n" + //
                "        //4 按部门统计不同性别员工的平均工资。\r\n" + //
                "        Map<String,Map<String,Double>> map = list.stream().collect(Collectors.groupingBy(e->e.getDept(),Collectors.groupingBy(e->e.getSex(),Collectors.averagingDouble(e->e.getSalary()))));\r\n" + //
                "        map.keySet().forEach(\r\n" + //
                "            key ->{ \r\n" + //
                "                System.out.println(key+\":\");\r\n" + //
                "                map.get(key).keySet().forEach(\r\n" + //
                "                        key2->{\r\n" + //
                "                            System.out.println(\"  \"+key2+\":\"+ map.get(key).get(key2));    \t\t\t\t\t\t  \r\n" + //
                "                        });\r\n" + //
                "            });\r\n" + //
                "\r\n" + //
                "        sc.close();\r\n" + //
                "    }\r\n" + //
                "\r\n" + //
                "    @FunctionalInterface\r\n" + //
                "    public interface Sortable {\r\n" + //
                "        int[] sort(int arr[]);\r\n" + //
                "    }\r\n" + //
                "}";
                System.out.println(s);
  }

}
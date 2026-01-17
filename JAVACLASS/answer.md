以下是这份Java试题的参考答案：

---

Java程序设计试题参考答案

一、选择题答案（每题2分，共50分）
1. B  
2. B  
3. C  
4. B  
5. B  
6. C  
7. B  
8. C  
9. D  
10. A（注：Comparable和Comparator都用于排序，Comparable是对象自身可比较）  
11. C  
12. D  
13. C  
14. C  
15. A  
16. D  
17. C  
18. C  
19. C  
20. A  
21. B  
22. C  
23. C  
24. C  
25. B

---

二、判断题答案（每题1分，共10分）
1. ×（private方法不能被继承，更不能被重写）  
2. √  
3. ×（类型可以自动推断，不必显式声明）  
4. √  
5. ×（StringBuilder是非线程安全的）  
6. √  
7. √  
8. ×（锁定的是类的Class对象，即全局锁）  
9. √  
10. √

---

三、简答题答案（每题5分，共20分）

1. ArrayList和LinkedList的区别及使用场景

区别：
- 底层结构：ArrayList基于动态数组实现，LinkedList基于双向链表实现
- 访问效率：ArrayList随机访问快（O(1)），LinkedList随机访问慢（O(n)）
- 增删效率：ArrayList中间插入删除慢（需要移动元素），LinkedList插入删除快（仅需修改指针）
- 内存占用：ArrayList内存连续，LinkedList每个节点额外存储前后指针，内存开销更大

使用场景：
- ArrayList：适合频繁查询、遍历，增删操作较少的场景
- LinkedList：适合频繁在头尾或中间插入删除，查询操作较少的场景

---

2. Java多态概念及方法重写实现

多态概念：多态指同一个方法调用，由于对象不同会产生不同的行为。它通过继承和方法重写实现，允许父类引用指向子类对象，运行时动态绑定具体实现。

实现方式：

```java
// 父类
class Animal {
    public void makeSound() {
        System.out.println("动物叫声");
    }
}

// 子类重写
class Dog extends Animal {
    @Override
    public void makeSound() {
        System.out.println("汪汪");
    }
}

// 多态体现
Animal animal = new Dog();  // 父类引用指向子类对象
animal.makeSound();  // 实际调用Dog类的makeSound()，输出"汪汪"
```

---

3. 创建线程的两种方式及优缺点

方式一：继承Thread类
- 实现：定义类继承Thread，重写run()方法，创建对象后调用start()
- 优点：编写简单，直接使用this获取当前线程
- 缺点：Java单继承限制，无法再继承其他类；多个线程无法共享资源

方式二：实现Runnable接口
- 实现：定义类实现Runnable接口，实现run()方法，创建Thread对象时传入Runnable实现类
- 优点：避免单继承限制，可以继承其他类；多个线程可共享同一Runnable对象，方便资源共享
- 缺点：编程稍微复杂，获取当前线程需用Thread.currentThread()

推荐使用：优先选择实现Runnable接口，更灵活且符合面向对象设计原则

---

4. JDBC访问数据库步骤及Statement与PreparedStatement区别

基本步骤：
1. 加载数据库驱动：`Class.forName("驱动类名")`
2. 建立数据库连接：`DriverManager.getConnection(url, user, pwd)`
3. 创建Statement对象：`connection.createStatement()`
4. 执行SQL语句：`executeQuery()`或`executeUpdate()`
5. 处理结果集：遍历ResultSet
6. 关闭资源：按ResultSet→Statement→Connection顺序关闭

Statement vs PreparedStatement区别：
- 预编译：PreparedStatement会预编译SQL，执行效率高；Statement每次执行都需编译
- 防止SQL注入：PreparedStatement使用参数化查询，安全性高；Statement拼接字符串易被注入
- 可读性：PreparedStatement使用占位符，代码更清晰易维护
- 性能：PreparedStatement支持批量操作，性能更优

---

四、问答题答案（每题10分，共20分）

1. TCP和UDP协议区别及Java实现

区别对比：

特性	TCP	UDP	
连接方式	面向连接（三次握手）	无连接	
可靠性	可靠传输，保证数据完整有序	不可靠，可能丢失、乱序	
速度	较慢，有确认重传机制	较快，无确认机制	
数据形式	字节流（无边界）	数据报（有边界）	
适用场景	文件传输、邮件、网页浏览	视频直播、在线游戏、DNS查询	
资源消耗	较多	较少	

Java核心类：
- TCP：`ServerSocket`（服务器端）、`Socket`（客户端）
- UDP：`DatagramSocket`（发送/接收端）、`DatagramPacket`（数据包）

TCP通信完整过程：
1. 服务器启动：创建ServerSocket，绑定端口（如8888），调用accept()进入监听状态
2. 客户端请求：创建Socket，指定服务器IP和端口，发起连接请求
3. 三次握手：
   - 客户端发送SYN包
   - 服务器回复SYN+ACK包
   - 客户端发送ACK包，连接建立
4. 数据传输：服务器accept()返回Socket对象，双方通过输入输出流进行数据交互
5. 连接关闭：通信结束后，客户端和服务器分别关闭Socket，四次挥手释放连接

---

2. Java集合框架系统阐述

三大接口特点：
- List接口：有序集合，元素可重复，可通过索引访问
- Set接口：无序集合，元素不可重复，注重唯一性
- Map接口：键值对集合，键唯一，值可重复，通过键找值

常用实现类：
- List：`ArrayList`（数组实现，查询快）、`LinkedList`（链表实现，增删快）
- Set：`HashSet`（哈希表实现，无序）、`TreeSet`（红黑树实现，可排序）
- Map：`HashMap`（哈希表，无序）、`TreeMap`（红黑树，按键排序）、`LinkedHashMap`（保持插入顺序）

Comparable vs Comparator：
- Comparable：内部比较器，由实体类实现`compareTo()`方法，定义"自然排序"，且只能有一种排序方式
  
```java
  class Person implements Comparable<Person> {
      public int compareTo(Person p) {
          return this.age - p.age; // 按年龄排序
      }
  }
  ```

- Comparator：外部比较器，单独实现`compare()`方法，可定义多种排序策略，不影响实体类
  
```java
  Comparator<Person> nameComparator = (p1, p2) -> p1.getName().compareTo(p2.getName());
  ```

Lambda表达式应用示例：

```java
List<String> list = Arrays.asList("apple", "orange", "banana");

// 排序（简化为Lambda）
list.sort((s1, s2) -> s1.length() - s2.length());

// 遍历
list.forEach(s -> System.out.println(s));
// 或方法引用
list.forEach(System.out::println);

// Map遍历
Map<Integer, String> map = new HashMap<>();
map.forEach((k, v) -> System.out.println(k + " = " + v));
```

Lambda优势：代码简洁、可读性强、函数式编程风格，特别适合集合的遍历、过滤、映射等操作

---
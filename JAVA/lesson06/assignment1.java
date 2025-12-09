package lesson06;
import java.util.*;
/**
 *设计一个User类，保护三个基本私有属性 : String id; String name;String gender;以及三个属性的setter与getter方法，重写类的toStrng方法，toString方法输出对象的属性。
 *使用for循环创建 50个User对象，创建用户对象时，使用 "emp"+r.nextInt(100) 产生用户的id，gender和name随意，分别把用户存入到 ArrayList ,HashSet,以及map中，要求id作为用户的唯一性标识存入到集合中（即同一个集合和map中不能存在相同id的用户）
 *分别使用 迭代器 和for循环机增强for循环，输出集合中用户的属性信息。
 *2. 给题1中的User增加一个 年龄属性，数据类型为int,定义一个treeSet，创建20个年龄在0-100岁的用户，存入集合，并且要求集合中的元素按年龄从大到小排序。
 *3.从键盘输入一个任意字符的英文字符串，统计每个字母出现的次数。在控制台输出统计结果！
 */
public class assignment1 {
    public static void main(String[] args) {
        Random r = new Random();
        List<User> list1 = new ArrayList<>();
        Set<User> set1 = new HashSet<>();
        Map<String, User> map1 = new HashMap<>();
        Scanner sc = new Scanner(System.in);

        String[] first_names = {"Alexander", "Benjamin", "Catherine", "Daniel", "Elizabeth", "Frederick", "Gabriella", "Harrison",
                                "Isabella", "Jackson", "Katherine", "Liam", "Madeline", "Nathaniel", "Olivia", "Patrick",
                                "Quinn", "Rebecca", "Sebastian", "Theresa", "Ulysses", "Victoria", "William", "Xavier",
                                "Yvonne", "Zachary", "Aiden", "Brianna", "Christopher", "Delilah", "Ethan", "Fiona",
                                "George", "Hannah", "Ian", "Julia", "Kevin", "Lauren", "Matthew", "Natalie",
                                "Owen", "Penelope", "Ryan", "Samantha", "Tyler", "Uma", "Vincent", "Whitney",
                                "Zoe", "Adam", "Brittany", "Charles", "Diana", "Edward", "Florence", "Gregory",
                                "Heidi", "Isaac", "Jennifer", "Kenneth", "Linda", "Michael", "Nicole", "Oscar",
                                "Pamela", "Quentin", "Rachel", "Stephen", "Tina", "Ulrich", "Veronica", "Walter",
                                "Xena", "Yolanda", "Zane"};
        String[] Last_names  = {"Anderson", "Bennett", "Crawford", "Davidson", "Ellington", "Fitzgerald", "Gallagher", "Henderson",
                                "Ingram", "Jennings", "Kennedy", "Lancaster", "Mitchell", "Nicholson", "O'Brien", "Patterson",
                                "Quincy", "Richardson", "Sullivan", "Thompson", "Underwood", "Villanueva", "Washington", "Xiong",
                                "Young", "Zimmerman", "Adams", "Bailey", "Cooper", "Dawson", "Edwards", "Freeman",
                                "Gibson", "Hamilton", "Jacobs", "Klein", "Lawson", "Morgan", "Nelson", "Ortiz",
                                "Powell", "Reyes", "Scott", "Tucker", "Valdez", "Wheeler", "Yates", "Barnes",
                                "Coleman", "Duncan", "Fisher", "Jordan", "Marshall", "Palmer", "Romero", "Stevens",
                                "Wade", "Bishop", "Chambers", "Dixon", "Fleming", "Goodman", "Holmes", "Kramer",
                                "Lyons", "Newman", "Perkins", "Rowe", "Sharp", "Walton", "Brewer", "Conrad",
                                "Dodson", "Forbes", "Guthrie", "Hampton", "Kirby", "McLean", "Olsen", "Pratt",
                                "Roth", "Shepard", "Whitaker"};
        String[] genders     = {"male", "female"};

        int target = 50;
        ////使用for循环创建 50个User对象，创建用户对象时，使用 "emp"+r.nextInt(100) 产生用户的id，gender和name随意，分别把用户存入到 ArrayList ,HashSet,以及map中，要求id作为用户的唯一性标识存入到集合中（即同一个集合和map中不能存在相同id的用户）
        while(target > 0){
            User u = new User("emp" + r.nextInt(100), first_names[r.nextInt(75)] + " " + Last_names[r.nextInt(83)], genders[r.nextInt(1)]);
            if (!set1.contains(u)){
                list1.add(u); set1.add(u); map1.put(u.id_Getter(),u);
            } 
            target --;
        }
        
        //分别使用 迭代器 和for循环机增强for循环，输出集合中用户的属性信息。
        System.out.println("增强遍历set");
        for(User u : set1) System.out.println(u);

        System.out.println("迭代器遍历set");
        for (Iterator<User> it = set1.iterator(); it.hasNext(); ) {
            System.out.println(it.next());
        }

        System.out.println("普通for循环遍历set");
        User[] arr = set1.toArray(new User[set1.size()]);
        for (int i = 0; i < arr.length; i++) {
            System.out.println(arr[i]);
        }


        System.out.println();
        //2. 给题1中的User增加一个 年龄属性，数据类型为int,定义一个treeSet，创建20个年龄在0-100岁的用户，存入集合，并且要求集合中的元素按年龄从大到小排序。
        TreeSet<User> set2 = new TreeSet<>(Comparator.comparingInt(u -> u.age_Getter()));
        target = 20;
        while(target > 0) {
            User u = new User(r.nextInt(100), "emp" + r.nextInt(100), first_names[r.nextInt(75)] + " " + Last_names[r.nextInt(83)], genders[r.nextInt(1)]);
            if(!set2.contains(u)) set2.add(u);
            target --;
        }
        System.out.println("TreeSet 遍历");
        for(User u : set2) System.out.println(u);


        System.out.println();
        //3.从键盘输入一个任意字符的英文字符串，统计每个字母出现的次数。在控制台输出统计结果！
        Map<Character,Integer> chMap = new HashMap<>();

        String cur;
        System.out.print("输入一行英文字符串 区分大小写：");
        cur = sc.nextLine();

        for (char ch : cur.toCharArray()){
                if(chMap.containsKey(ch)) {
                    int cur_times = chMap.get(ch); cur_times++;
                    chMap.replace(ch, cur_times);
                } else {
                    chMap.put(ch, 1);
                }
        }
        System.out.println();
        
        for (Map.Entry<Character, Integer> x: chMap.entrySet()) {
            Character k = x.getKey();
            int v = x.getValue();
            System.out.println("字母 " + k + " 出现了 " + v + " 次");
        }

        sc.close();
    }
    
}

class User {
    private String _id, _name, _gender;
    private int _age;

    User() {}
    User(String id, String name, String gender) {
        _id = id; _name = name; _gender = gender; _age = -1;
    }
    User(int age, String id, String name, String gender) {
        _age = age; _id = id; _name = name; _gender = gender;
    }

    public void id_Setter(String temp){_id = temp;}
    public void name_Setter(String temp){_name = temp;}
    public void gender_Setter(String temp){_gender = temp;}
    public void age_Setter(int temp) {_age = temp;}
    public String id_Getter(){return _id;}
    public String name_Getter(){return _name;}
    public String gender_Getter(){return _gender;}
    public int age_Getter(){return _age;}
    
    @Override
    public String toString() {
    return "User{id = '" + _id + "', name = '" + _name + "', gender = '" + _gender +  "', age = " + _age + "}";
    }

    @Override
    public boolean equals(Object other){
        if (this == other) return true; // 地址相同时
        if (other == null || !(other instanceof User)) return false; // this != null, other 可能为 空 或者类型与this不同
        User Other = (User) other;
        return Objects.equals(_id, Other._id);
    }
    
    @Override
    public int hashCode() {return Objects.hash(_id);}  //重写equals就要重写hashCode

}
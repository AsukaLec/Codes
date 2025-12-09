package lesson07;

 import java.util.function.Function;

public class test {
    public static void main(String[] args) {
        convert("18", s -> Integer.parseInt(s));
        convert(20, integer -> String.valueOf(integer + 18));
        convert("245", s -> Integer.parseInt(s), integer -> String.valueOf(integer + 18));
    }   
    //定义一个方法，把一个字符串转换成int类型，在控制台输出
    private static void convert(String s, Function<String, Integer> fun) {
        // fun = new Function<String, Integer>() {
        //     public Integer apply(String s) {
        //     return Integer.parseInt(s);
        //     }
        // }
        int i = fun.apply(s);
        System.out.println(i);
    }
    //定义一个方法，把int类型数据加上一个整数之后，转换为字符串在控制台输出
    private static void convert(int i, Function<Integer, String> fun) {
        String s = fun.apply(i);
        System.out.println(s);
    }   
    //定义一个方法，把一个字符串转换int类型，把int类型的数据加上一个整数后，转换成字符串在控制台输出
    private static void convert(String s, Function<String, Integer> fun1, Function<Integer, String> fun2) {
        String s1 = fun2.apply(fun1.apply(s));
        System.out.println(s1);
    }
}

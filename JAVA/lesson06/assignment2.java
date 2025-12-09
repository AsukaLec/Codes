package lesson06;

import java.util.*;
/**
 * 1、创建一个成绩类*Score，包含 编号，语文成绩，数学成绩，英语成绩，总分 5个属性。
 * 该对象实现Comparable接口，排序规则如下：
 * 先按总分排序，总分相同，按语文成绩排序，语文成绩相同按数学成绩排序，数学成绩相同按英语成绩排序，英语成绩相同，按编号字符顺序。
 * 随机生成100个 编号不同，各科分数在0-100直接的随机数的成绩对象。
 * 2、把成绩对象存入到TreeSet集合中，排序要求： 
 * 先按总分排序，总分相同，按数学成绩排序，数学成绩相同按语文成绩排序，语文成绩相同按英语成绩排序，英语成绩相同，按编号字符顺序。
 */
public class assignment2 {
    public static void main(String[] args) {
        Random r = new Random();
        Set<Score> ranking = new TreeSet<>(Comparator
                .comparingInt(Score::getTotal)
                .thenComparingInt(Score::getMath)
                .thenComparingInt(Score::getChinese)
                .thenComparingInt(Score::getEnglish)
                .thenComparing(Score::getId));

        int target = 100;
        while (target > 0) {
            Score u = new Score(""+ r.nextInt(101), r.nextInt(100), r.nextInt(100), r.nextInt(100));
            target --;
            if(!ranking.contains(u)) ranking.add(u);
        }

        for(Score u : ranking) System.out.println(u);
        
    }
}



class Score implements Comparable<Score>{
    private String _id;
    private int _Zhscore, _Masocre, _Ensocre, _total;

    Score(){}
    Score(String id, int Zhscore, int Masocre, int Ensocre){_id = id; _Zhscore = Zhscore; _Masocre = Masocre; _Ensocre = Ensocre; _total = Zhscore + Masocre + Ensocre;}
    
    @Override
    public String toString() {
        return "Score{id = '" + _id + "', 语文成绩 = " + _Zhscore + ", 数学成绩 = " + _Masocre + ", 英语成绩 = " + _Ensocre + ", 总分 = " + _total + "}";
    }

    @Override
    public int compareTo (Score other) {
        int c = Integer.compare(_total, other._total);
        if(c != 0) return c;
        c = Integer.compare(_Zhscore, other._Zhscore);
        if(c != 0) return c;
        c = Integer.compare(_Masocre, other._Masocre);
        if(c != 0) return c;
        c = Integer.compare(_Ensocre, other._Ensocre);
        if(c != 0) return c;
        return _id.compareTo(other._id);
    }
    // 负整数：当前对象“小于”参数对象
    // 零：两者“相等”
    // 正整数：当前对象“大于”参数对象

    public int getTotal () {return _total;}
    public int getChinese () {return _Zhscore;}
    public int getMath () {return _Masocre;}
    public int getEnglish () {return _Ensocre;}
    public String getId () {return _id;}

    @Override
    public boolean equals(Object other){
        if (this == other) return true; // 地址相同时
        if (other == null || !(other instanceof Score)) return false; // this != null, other 可能为 空 或者类型与this不同
        Score Other = (Score) other;
        return Objects.equals(_id, Other._id);
    }
    
    @Override
    public int hashCode() {return Objects.hash(_id);}  //重写equals就要重写hashCode
}
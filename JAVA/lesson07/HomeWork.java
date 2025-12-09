package lesson07;

import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.function.Function;
import java.util.stream.Collectors;

//定义接口
 interface Sortable {	
	int[] sort(int[] intArr);
	

}
//
public class HomeWork {
  
	public static void main(String[] args) {
		
		//自定义接口数组排序 ---------------------------------
		int[] intArr = {7,1,3,5,44,23,78,99,21};
		Sortable s = arr ->{
			              Arrays.sort(arr);
			              return arr;
		                  };
		                  
		intArr =(s.sort(intArr));
		
		System.out.println("自定义接口数组排序结果：");
		for(int n:intArr) {
			System.out.print(" "+n);
		}
		
		
		//"Function 接口算阶乘”-----------------------------"
		System.out.println("");
		System.out.print ("Function 接口算阶乘 结果：");
		Function<Long,Long> fn = n ->{
			long sum =1L;
			for(int i=2;i<=n;i++) {
				sum *=i;
			}
			return sum;
		};		
		System.out.println(fn.apply(5L));//应用
		
		//Stream 实现统计：------------------------------
		System.out.println();
	   System.out.println(" Stream 实现统计：");	
       List<Employee> list = Employee.getEmpList();
       //统计男员工的人数：-------
         long count =  list.stream().filter(e-> e.getSex().equals("男")).count();
         System.out.println("男员工人数："+count);
         
         //所有薪酬大于=5000元的女工-------------------
        System.out.println("所有薪酬大于5000元的女工:"); 
         List<Employee> fList = list.stream().filter(e->e.getSalary()>5000).filter(e-> e.getSex().equals("女")).toList();
		 fList.forEach(e->System.out.println(e.getName()+" :"+e.getSex()));
		 
		 //找出大于平均年龄的员工-------------
		 System.out.println("找出大于平均年龄的员工:");
		 List<Employee> bigAgeList =list.stream().filter(e->e.getAge()>list.parallelStream().collect(Collectors.averagingDouble(ee->ee.getAge()))).toList();
		 bigAgeList.forEach(e->System.out.println(e.getName()+" :"+e.getAge()));
		 
		 //排序：先按性别（女性在前），性别相同则按年龄（从小到大），年龄相同则按薪水（从大到小）
		 List<Employee> sortList = list.parallelStream()		                     
		                      .sorted((e1,e2)->{
		                    	  int n =e1.getSex().compareTo(e2.getSex());//0 ,正,负
		                    	  if(n==0) {//性别相同
		                    		  n=e1.getAge()-e2.getAge();	//0 ,正,负	                    	  
		                    		  if(n==0) { //  0 年龄相同
		                    			  double d = e1.getSalary()-e2.getSalary();
				                    	  if(d==0)return 0; //薪水相同
			                    	      else  return (d>0)?-1:1; //
		                    	      }else {
		                    		      return (n>0)?1:-1;
		                    	      }
		                    	  }else {
		                    		 return (n>0)?1:-1;
		                    	  }
		                      }).toList(); 
		   System.out.println("排序结果：");
		   sortList.forEach(System.out::println);   
		   //	//求不同部门不同性平均工资：
		   
		   System.out.println("//求不同部门不同性平均工资：");
			  Map<String,Map<String,Double>> map =	list.stream().collect(Collectors.groupingBy(e->e.getDept(),Collectors.groupingBy(e->e.getSex(),Collectors.averagingDouble(e->e.getSalary()))));
		       map.keySet().forEach(
		    		   key ->{ 
		    			   System.out.println(key+":");
		    			   map.get(key).keySet().forEach(
		    					   key2->{
		    						   System.out.println("  "+key2+":"+ map.get(key).get(key2));    						  
		    					   });
		    		   });
		 
	}
}

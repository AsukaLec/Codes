package lesson04;

public class TestMT {

	public static void main(String[] args) {		
		   A a1 = new A();  
		   A a2 = new B();  
		   B b  = new B();  
		   C c  = new C();  
		   D d  = new D(); 
		   //
		   System.out.println(a1.show(b)); //      A A
		   System.out.println(a1.show(c));  //     A A 
		   System.out.println(a1.show(d)); //      A D
		   //
		   System.out.println(a2.show(b));  //     B B ** B A
		   System.out.println(a2.show(c)); //      B B ** B A
		   System.out.println(a2.show(d));  //     A D
		   //
		   System.out.println(b.show(b));  //      B B 
		   System.out.println(b.show(c));  //      B B
		   System.out.println(b.show(d));  //      B B ** A D
	}

}

class A {  
    public String show(D obj)
       {  
           return ("A and D");  
       }   
    public String show(A obj){    
           return ("A and A");  
       }   
}   
class B extends A{               
    public String show(B obj){   
           return ("B and B");    
    }  
    public String show(A obj){  
           return ("B and A");  
    }   
}  
class C extends B{}    
class D extends B{}    


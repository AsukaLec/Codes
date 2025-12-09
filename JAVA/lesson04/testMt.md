``` java

public class TestMT {

	public static void main(String[] args) {		
		   A a1 = new A();  // 引用类型 A，对象类型 A
		   A a2 = new B();  // 引用类型 A，对象类型 B（多态）
		   B b  = new B();  // 引用类型 B，对象类型 B
		   C c  = new C();  // 引用类型 C，对象类型 C（C 继承 B，B 继承 A）
		   D d  = new D();  // 引用类型 D，对象类型 D（D 继承 B，B 继承 A）
		   //
		   System.out.println(a1.show(b)); //  ①    A A
		   System.out.println(a1.show(c));  // ②    A A 
		   System.out.println(a1.show(d)); //  ③    A D
		   //
		   System.out.println(a2.show(b));  // ④    B B ** B A
		   System.out.println(a2.show(c)); //  ⑤    B B ** B A
		   System.out.println(a2.show(d));  // ⑥    A D
		   //
		   System.out.println(b.show(b));  //  ⑦    B B 
		   System.out.println(b.show(c));  //  ⑧    B B
		   System.out.println(b.show(d));  //  ⑨	B B ** A D
	}

}

class A {  
    public String show(D obj){  
           return ("A and D");  
       }   
    public String show(A obj){    
           return ("A and A");  
       }   
}   
class B extends A{               //继承
    public String show(B obj){   //  B类独有的方法，与类B内其它方法构成重载
           return ("B and B");    
    }  
    public String show(A obj){  
           return ("B and A");  
    }   
}  
class C extends B{}     //继承
class D extends B{}     //继承

```

这段代码考察的是 Java 方法调用的绑定机制，特别是 重载（overload）与重写（override） 的区分，以及 编译时类型 vs 运行时类型 的决定作用。

---

✅ 核心规则回顾

机制	绑定时机	决定因素	
重载（overload）	编译期	引用类型（左边）	
重写（override）	运行期	对象类型（右边）	

<mark>引用 向上/向下转型 重载</mark>

---

✅ 类结构图（继承链）

```
A
└── B
    ├── C
    └── D
```

---

✅ 方法表（每个类有哪些方法）

类	方法	
A	`show(D)`、`show(A)`	
B	继承 `show(D)`、`show(A)`，新增 `show(B)`，重写 `show(A)` → 变成 `B and A`	

---

✅ 新建实例
`A a2 = new B()`
`a2` 是 `A` 类型的引用， 但是实际对象是 `B` 所以说其方法有 `A` 内的 `show(D obj)` 以及 `show(A obj)`, 但是在 `B` 对象中， `show(A obj)` 被重写了， 所以 `a2` 只有方法 
``` java
    public String show(D obj){  
           return ("A and D");  
       }   

    public String show(A obj){  
           return ("B and A");  
    }   
```

---

✅ 逐行分析

① `a1.show(b)` → `A and A`
- `a1` 是 `A` 类型，编译时看 `A` 类的方法。
- `b` 是 `B` 类型，向上转型为 A，匹配 `show(A obj)`。
- 没有重写，所以运行时也调 `A.show(A)` → `A and A`

② `a1.show(c)` → `A and A`
- `c` 是 `C` 类型，继承自 `B`，向上转型为 A，匹配 `show(A obj)`。
→ `A and A`

③ `a1.show(d)` → `A and D`
- `d` 是 `D` 类型，精确匹配 `show(D obj)`。
→ `A and D`

---

④ `a2.show(b)` → `B and A`
- `a2` 是 `A` 类型引用，指向 B 对象。
- 编译时看 `A` 类方法，匹配 `show(A obj)`。
- 运行时，B 重写了 show(A) → 调用 `B.show(A)` → `B and A`

⑤ `a2.show(c)` → `B and A`
- `c` 是 `C` 类型，向上转型为 `A`，匹配 `show(A obj)`。
- 运行时调用 `B.show(A)` → `B and A`

⑥ `a2.show(d)` → `A and D`
- `d` 是 `D` 类型，匹配 `show(D obj)`。
- B 没有重写 show(D)，所以调用 `A.show(D)` → `A and D`

---

⑦ `b.show(b)` → `B and B`
- `b` 是 `B` 类型引用，精确匹配 `show(B obj)`。
→ `B and B`

⑧ `b.show(c)` → `B and B`
- `c` 是 `C` 类型，向上转型为 B，匹配 `show(B obj)`。
→ `B and B`

!!! : 第九个看 上面 方法表
⑨ `b.show(d)` → `A and D`
- `d` 是 `D` 类型，没有匹配 `show(D)` 在 B 中，但 A 中有。
- 编译时看 `B` 类，继承自 A，找到 `show(D)`。
→ `A and D`

---

✅ 总结口诀（记忆用）

> 重载看左边，重写看右边；

精确匹配优先，向上转型其次。

---

✅ 附：运行结果对照表

编号	表达式	结果	解释	
①	`a1.show(b)`	A and A	编译时匹配 `show(A)`，无重写	
②	`a1.show(c)`	A and A	同上	
③	`a1.show(d)`	A and D	精确匹配 `show(D)`	
④	`a2.show(b)`	B and A	编译时 `show(A)`，运行时 `B` 重写	
⑤	`a2.show(c)`	B and A	同上	
⑥	`a2.show(d)`	A and D	未重写 `show(D)`，用父类	
⑦	`b.show(b)`	B and B	精确匹配 `show(B)`	
⑧	`b.show(c)`	B and B	`C` 是 `B` 的子类，匹配 `show(B)`	
⑨	`b.show(d)`	A and D	继承自 `A` 的 `show(D)`	

---

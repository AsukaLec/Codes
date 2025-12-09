[TOC]
# <center> 第四章 指令系统
## 零、Intro
**冯.诺依曼结构机器对指令规定：**
用二进制表示，和数据一起存放在主存中
由两部分组成：操作码和操作数（或其地址码）
Operation Code:  defines the operation type
Operands:  indicate operation source and destination

**一条指令必须明显或隐含包含的信息有哪些？**
1. *操作码：指定操作类型*
  - (操作码长度：固定／可变)
 
2. *源操作数参照：一个或多个源操作数所在的地址*
  - (操作数来源：主(虚)存/寄存器/I/O端口/指令本身)
 
3. *结果值参照：产生的结果存放何处（目的操作数）*
  - (结果地址：主(虚)存/寄存器/I/O端口)
 
4. *下一条指令地址：下条指令存放何处*
  - (下条指令地址 ：主(虚)存)
  - (正常情况隐含在PC中，改变顺序时由指令给出)

**一条指令中应该有几个地址码字段？**
| 指令类型 | 特点 | 示例场景 | 指令形式 |
| --- | --- | --- | --- |
| 零地址指令 | 无需操作数，或操作数为默认 | 空操作、停机、堆栈、累加器 | `OP` |
| 一地址指令 | 地址既是操作数地址，也是结果地址 | 单目运算（取反、取负）、双目运算（另一操作数默认） | `OP A1` |
| 二地址指令（最常用） | 分别存放双目运算两个操作数，其中一个地址作为结果地址 | 一般双目运算 | `OP A1, A2` |
| 三地址指令（RISC风格） | 分别作为双目运算两个源操作数地址和一个结果地址 | RISC架构运算 | `OP A1, A2, A3` |
| 多地址指令 | 用于成批数据处理 | 向量/矩阵等运算的SIMD指令 | （视具体指令集而定） |

**从指令执行周期看指令设计涉及的问题**
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/4.0 从指令执行周期看指令设计涉及的问题.png" width="600"/>
  </div>
</div>

**指令格式的设计**
1. *指令格式的选择应遵循的几条基本原则*
- 应尽量短
- 要有足够的操作码位数
- 指令编码必须有唯一的解释，否则是不合法的指令
- 指令字长应是字节的整数倍
- 合理地选择地址字段的个数
- 指令尽量规整
2. *与指令集设计相关的重要方面*
- 操作码的全部组成：操作码个数 / 种类 / 复杂度
- LD/ST/INC/BRN 四种指令已足够编制任何可计算程序，但程序会很长
- 数据类型：对哪几种数据类型完成操作
- 指令格式：指令长度 / 地址码个数 / 各字段长度
- 通用寄存器：个数 / 功能 / 长度
- 寻址方式：操作数地址的指定方式
- 下条指令的地址如何确定：顺序，PC+1；条件转移；无条件转移；……

一般通过对操作码进行不同的编码来定义不同的含义，操作码相同时，再由功能码定义不同的含义!


## 一、指令系统的设计
### 1. 操作数类型 & 存储
**操作数是指令处理的对象，与高级语言数据类型对应，有以下基本类型：**
- 指针（地址） ：无符号整数，用来参加运算确定主（虚）存位置
- 数值数据：
  - 定点数（整数）：二进制补码
  - 浮点数（实数）：IEEE 754
  - 十进制数：用NBCD码表示，压缩/非压缩（汇编程序设计时用）
- 位、位串、字符和字符串 ：用来表示文本、声音和图像等
  - 4 bits is a nibble（一个十六进制数字）
  - 8 bits is a byte
  - 16 bits is a half-word (若一个字为32位)
  - 32 bits is a word (若一个字为32位)
- 逻辑(布尔)数据: 按位操作（0-假／1-真）sss

**存放在寄存器或内存单元**

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/4.1.1 IA-32 & MIPS Data Type.png" width="500"/>
  </div>
</div>

### 2. 寻址方式
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/4.1.2 寻址方式及其优缺点.png" width="500"/>
  </div>
</div>

**指令或操作数地址的指定方式。即：根据地址找到指令或操作数的方法。**

**1. 立即寻址**
在指令中直接给出操作数本身，此时该操作数被称为立即数

**2. 直接寻址**
指令中给出的是操作数的有效地址，该地址被称为直接地址或绝对地址

**3. 间接寻址**
指令中给出的是操作数的间接地址，这个地址存储的内容是操作数的有效地址。
虽然需要多次寻址，但是灵活性高，可以动态更改有效地址

**4. 寄存器寻址**
指令中的地址码是操作数所在寄存器编号
优点：
- 寄存器数量少，编号比存储地址短，指令长度短
- 操作数已在CPU中，不用访存，执行速度快

**5. 寄存器间接寻址**
指令中给出的地址码是一个寄存器编号，该寄存器中存放的是操作数的有效地址

**6. 偏移寻址**
相对寻址，基址寻址，变址寻址
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/4.1.2 偏移寻址.png" width="500"/>
  </div>
</div>

- **相对寻址**
  <mark>CPU内部有一个程序计数器 PC (指令指针寄存器IP)，每执行一条指令其值自动加1，**（这个是以字为单位的，换算成地址需要乘4哦）** 指向下一条欲执行指令的指令地址。这种程序顺序执行的过程我们称为指令的顺序寻址。PC 就是用来做指令追踪<mark>
  
  指令地址码给出一个偏移量(带符号数)，基准地址隐含由PC给出。
  即：EA=(PC)+A              （ex. MIPS’s instruction:  Beq）
  可用来实现程序(公共子程序)的浮动 或 指定转移目标地址<mark>
  *注意：当前PC的值可以是正在执行指令的地址或下条指令的地址*

  tips: 给定了转移指令的地址和转移目标地址 且增量pc相同，可以知道偏移量是多少吗？
  <mark>不可</mark>, 因为不知道机器是按字编址还是按字节编址（字其实代表cpu处理的最大宽度，32位机器一个字等于4字节），位移量是指指令条数还是单元数。知道这些才能推测。
  最简单的就是按字节编址且偏移量为单元数，直接计算就好
- **基址寻址**
  指令地址码给出一个偏移量，基准地址明显或隐含由基址寄存器B给出。即：EA=(B)+A   （ex. MIPS’s instructions:  lw / sw）
  可用来实现多道程序重定位 或 过程调用中参数的访问<mark>
- **变址寻址**
  指令地址码给出一个基准地址，而偏移量(无符号数)明显或隐含由变址寄存器 I 给出。即：EA=(I)+A
  可为循环重复操作提供一种高效机制，如实现对线性表的方便操作<mark>


<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/4.1.2 存储器操作数的寻址方式.png" width="500"/>
  </div>
</div>

### 3. 例子1 ：MIPS中的循环处理 
``` cpp
for  (i=0;i<N,i++)	
        g = g +A[i];
```
假设变量` i `存在 `$7` 寄存器 `g` 存在 `$8` 寄存器 数组的首地址存在`$9`寄存器
\$9 里放的是 数组首地址 &A[0]（基址）
\$7 里放的是 字节偏移 i（因为每个 int 占 4 字节，代码里 i 每次加 4）
注意寄存器中存的始终是地址
``` cpp
      add $7, $0, $0    ; i=0          //把0写入寄存器7 >> i = 0（$0恒为0）
Loop: add $10, $7, $9   ; $10=&A[i]    // $10  得到第  i  字节处的地址。
      lw  $6, 0($10)    ; $6=A[i]      // lw  rt, offset(rs)   #  rt = Memory[rs + offset] 
      add $8, $8, $6    ; g= g+A[i]    // 
      addi $7, $7, 4    ; i=i+1        // 每次跳过 4 字节，即跳到下一个  int  元素
      bne  $7, $2, Loop                // # if (i != limit) goto Loop
      //  $2  在 MIPS 调用约定里就是参数寄存器  a0 。
      // 在这段循环代码中，它存的是循环结束条件的“总字节数”，也就是：
      // 数组 A 所占的字节数（必须是 4 的倍数）
```

### 4. 指令格式
- 代码长度更重要时：采用变长指令字、变长操作码
- 性能更重要时：采用定长指令字、定长操作码
  -  变长指令字和变长操作码使机器代码更紧凑；定长指令字和定长操作码便于快速访问和译码。

- 是否可以有定长指令字、变长操作码？定长操作码、变长指令字呢？
  - 指令长度是否可变与操作码长度是否可变没有绝对关系，但通常是 ：“定长操作码不一定是定长指令字”、 “变长操作码一般是变长指令字”。

#### Type 1 定长操作码编码
**操作码长度固定，译码方便，指令执行速度快，但有信息冗余**
eg. IBM360/370采用: ８位定长操作码，最多可有256条指令 只提供了183条指令，有73种编码为冗余信息
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/4.1.4.1 IBM370指令格式.png" width="500"/>
  </div>
</div>

OP的前两位用于指定4种不同的指令格式 ： 00-RR, 01-RX, 10-RS or SI, 11-SS

- RR 的两个操作数和结果都在寄存器中
- 寄存器-存储器型 
  - RX 二地址指令，第一个操作数和结果存放在 R1，另一个操作数在存储器中，有效地址 EA = (X)+(B)+D
   - RS 三地址指令，R1 存放结果， R3 存放一个源操作数，另一个源操作数的有效地址 EA = (B) + D
- SI 存储器-立即数型 结果和其中一个操作数的地址共用一个存储单元
- SS 存储区-存储器型 两个操作数都是存储器中的内容，L为字符串长度，用于字符串处理



#### Type 2 扩展操作码编码
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/4.1.4.2 PDP-11.png" width="500"/>
  </div>
  <div style="text-align:center;">
    <img src="photos/4.1.4.2 扩展操作码编码.png" width="500"/>
  </div>
</div>

### 5. 标志信息的生成和使用
**条件测试方式**
条件转移指令通常根据Condition Codes (条件码 CC/ 状态位 / 标志位)转移
eg: ZF OF SF CF
通过执行算术指令或显式地由比较和测试指令来设置CC

```cpp 
ex: sub r1, r2, r3; //r2和r3相减, 结果在r1中，并生成标志位ZF、CF等
    bz label;	   //标志位ZF=1时转到label处执行；否则顺序执行
```

存放：
标志可存标志寄存器/条件码寄存器/状态寄存器/程序状态字寄存器
也可由指定的通用寄存器来存放状态位
```cpp
Ex: cmp r1, r2, r3;  //比较r2和r3, 标志位存储在r1中
    bgt r1, label;   //判断r1是否大于0，是则转移到label处
```
bgt的条件:
无符号数：ZF=0^CF=0
带符号整数：ZF=0^SF≡OF

可以将两条指令合成一条指令，即：计算并转移
```cpp
Ex: bgt r1, r2, label; //如果r1>r2，则转移到label处执行；否则顺序执行
```

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/4.1.5 标志信息.png" width="400"/>
  </div>
  <div style="text-align:center;">
    <img src="photos/4.1.5 IA-32中的条件转移指令.png" width="400"/>
  </div>  
</div>

### 6. 指令风格
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/4.1.6 按操作数位置指定风格.png" width="400"/>
    <div><strong>按操作数位置指定风格</strong></div>
  </div>
  <div style="text-align:center;">
    <img src="photos/4.1.6 按指令格式的复杂度.png" width="400"/>
    <div><strong>按指令格式的复杂度</strong></div>
  </div>  
</div>

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/4.1.6 指令风格比较.png" width="400"/>
  </div>    
</div>

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/4.1.6 CISC.png" width="400"/>
  </div>  
  <div style="text-align:center;">
    <img src="photos/4.1.6 RISC.png" width="400"/>
  </div>  
</div>

### 7. 异常&中断
程序执行过程中CPU会遇到一些特殊情况，使正在执行的程序被“中断”
CPU中止原来正在执行的程序，转到处理异常情况或特殊事件的程序去执行，结束后再返回到原被中止的程序处（断点）继续执行。

程序执行被 “中断” 的事件有两类
- 内部异常：在CPU执行某指令时内部发生的意外事件或特殊事件
  - 故障(fault)：执行某条指令时发生的异常事件，如溢出、缺页、越界、越权、越级、非法指令、除数为0、堆/栈溢出、访问超时等。
  - 自陷(trap)：执行预先设置的指令，如断点、单步、系统调用等。
  - 终止(abort)：指令执行过程中出现了硬件故障，如访存校验错等。
- 外部中断：在CPU外部发生的特殊事件，通过“中断请求”信号向CPU请求处理。如实时钟、控制台、打印机缺纸、外设准备好、采样计时到、DMA传输结束等。

异常/中断处理分两个阶段
检测和响应：由硬件完成
具体的处理过程由软件（操作系统）执行程序完成


## 二、程序的机器级表示
### 1. MIPS指令中的数据的表示
MIPS中提供了32个32位**通用**寄存器，寄存器编号占5位
| 名称 | 编号 | 功能 |
| --- | --- | --- |
| zero | 0 | 恒为0 |
| at | 1 | 为汇编程序保留 |
| v0~v1 | 2~3 | 过程调用返回值 |
| a0~a3 | 4~7 | 过程调用参数 | 
| t0~t7 | 8~15 | 临时变量，在被调用过程无需保存 | 
| s0~s7 | 16~23 | 在被调用过程需保存 | 
| t8~t9 | 24~25 | 临时变量，在调用过程无需保存 | 
| k0~k1 | 26~27 | 为OS保留 | 
| gp | 28 | 全局指针 | 
| sp | 29 | 栈指针 | 
| fp | 30 | 帧指针 | 
| ra | 31 | 过程调用返回地址 | 

寄存器的汇编表示 \$a0 或 \$4
还有32个**单精度浮点寄存器** \$f0~\$f31 可以配对成16个64位寄存器
还有两个**乘商寄存器** ``Hi `` ``Lo`` 在乘法计算时联合起来存放64位乘积 除法时余数放在`Hi` 商在 `Lo`
程序计数器 `PC` 指出下条指令的地址

MIPS中的存储器按字节编址，对于存储器数据，其操作数有效地址位32位置，通过一个32位寄存器的内容加16位偏移量得到，16位偏移量是带符号整数，故可访问的地址空间大小为 $2^{31}$。采用大端方式存放数据，数据要求按字边界对齐，只能通过lad/store指令访问存储器数据。

对于立即操作数，指令中给出的位数是16位，指令执行时，需要将其进行符号扩展或0扩展，变成32位操作数后才能参加运算。

### 2. MIPS 指令格式
**所有指令都是32位宽，须按字地址对齐，字地址为4的倍数**

<div style="display:flex; gap:em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/4.2.2 R.png" width="500"/>
  </div>  
  <div style="text-align:center;">
    <img src="photos/4.2.2 I.png" width="500"/>
  </div>  
  <div style="text-align:center;">
    <img src="photos/4.2.2 J.png" width="500"/>
  </div>  
</div>

- R-Type 两个操作数和结果都在寄存器的运算指令。如：sub rd, rs, rt
  - OP 操作码
  - rs 第一个源操作数寄存器
  - rt 第二个源操作数寄存器
  - rd 结果寄存器
  - shamt 移位指令的位移量
  - func R-Type指令的OP字段是特定的“000000”，具体操作由func字段给定。例如：func=“100000”时，表示“加法”运算。
  
- I-Type
  - 运算指令：一个寄存器、一个立即数。如：ori  rt, rs, imm16
  - LOAD和STORE指令。如：lw rt, rs, imm16
  - 条件分支指令。如：beq rs, rt, imm16
  - immediate：立即数或load/store指令和分支指令的偏移地址
  
- J-Type 无条件跳转指令。如：j  target
  - target address：无条件转移地址的低26位。将PC高4位拼上26位直接地址，最后添2个“0”就是32位目标地址。
  - **为何最后两位要添“0”？** 指令按字地址对齐，所以每条指令的地址都是4的倍数（最后两位为0）。

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/4.2.2 OP字段的含义.png" width="500"/>
  </div> 
  <div style="text-align:center;">
    <img src="photos/4.2.2 R-型指令的解码.png" width="500"/>
  </div>  
</div>

### 3. MIPS 指令寻址方式
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/4.2.3 R型寻址方式.png" width="300"/>
    <div><strong> R-Type 寄存器寻址 </strong></div>
  </div> 
</div>
R型指令即 RR型指令，操作数和结果都放在寄存器(rigister)里面

$\quad$

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/4.2.3 I型寻址方式.png" width="500"/>
    <div><strong> I-Type  </strong></div>
  </div> 
</div>
I型指令是立即数型指令
有四种寻址方式，寄存器寻址，相对寻址，基址或变址寻址

$\quad$

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/4.2.3 J型寻址方式.png" width="500"/>
    <div><strong> J-Type  </strong></div>
  </div> 
</div>
J型为变通的直接寻址

**一个例子 汇编形式与指令的对应**
若从存储器取来一条指令为`00AF8020H`，则对应的汇编形式是什么？
32位指令代码：`0000  0000 1010 1111 1000 0000 0010 0000` 

op `000000` rs`00101` rt`01111` rd`10000` shamt`00000` func`100000`
1. 根据R-Type指令解码表，知是 “add”操作（非移位操作)
2. rs、rt、rd的十进制值分别为5、15、16，从MIPS寄存器功能表知: rs、rt、rd分别为：\$a1、\$t7、\$s0

结果如下
`add   $s0 ，$a1，$t7` 功能：\$a1 + \$t7 → \$s0
这个过程称为“反汇编”，可用来破解他人的二进制代码（可执行程序）.

汇编的过程就是这个过程反过来

### 4. MIPS R-type指令实现电路的执行过程
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/4.2.3 流程图.png" width="500"/>
  </div> 
</div>
  
1. Preparation (1：准备阶段)
   - 装入指令寄存器（IR-Instruction Register）
   - 以下相应字段送控制逻辑
      - op field (OP字段)
      - func field (func字段) 
      - shmt field (shmt字段)
   - 以下相应字段送寄存器堆
     - 第一操作数寄存器编号
     - 第二操作数寄存器编号
     - 存放结果的目标寄存器编号

2. Execution(2：执行阶段)
  - 寄存器号被送选择器
  - 对应选择器输出被激活
    - 被选寄存器的输出送到数据线
  - 控制逻辑提供：
    - ALU操作码
    - 写信号 等
  - 结果被写回目标寄存器

 
### 5. MIPS寄存器的功能定义和两种汇编表示 
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/4.2.5 MIPS寄存器的功能定义和两种汇编表示 .png" width="500"/>
  </div> 
</div>

### 6. MIPS汇编语言示例
<div style="display:flex; gap:em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/4.2.6 MIPS汇编语言示例表.png" width="600"/>
    <div><strong>MIPS汇编语言示例表 </strong></div>
  </div> 
  <div style="text-align:center;">
    <img src="photos/4.2.6 MIPS机器代码示例列表.png" width="600"/>
    <div><strong>MIPS机器代码示例列表 </strong></div>
  </div> 
</div>

 注意了 这里面的offset不一样
>在  beq / bne / bgez  等 分支 里，offset 字段确实表示
>“相对于下一条指令，要跳过多少个 4-字节的指令字”；
>硬件把它左移 2 位变成字节地址。 
>在  lw / sw / lb / sb  等 加载/存储 里，offset 就是
>“字节偏移量”，与指令条数无关，绝不左移。

<div style="display:flex; gap:em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/4.2.6 MIPS arithmetic and logic instructions.png" width="600"/>
  </div> 
  <div style="text-align:center;">
    <img src="photos/4.2.6 MIPS data transfer instructions.png" width="600"/>
  </div> 
</div>

$\quad$

<div style="display:flex; gap:em; justify-content:;">
  <div style="text-align:center;">
    <img src="photos/4.2.6 MIPS的call，return， jump，branch和compare指令.png" width="500"/>
  </div> 
</div>

**常数的表示**
指令中如何取得常数?
- 若程序装入时，常数已在内存中，则需用load指令读入寄存器
- 在指令中用一个“立即数”来使用常数

  - 例1：i=i+4;     Assuming variable i ~ \$1
    则：   addi  \$1, \$1, 4

  - 例2：if (i<20) …. ;     Assuming variable i ~ \$1
    则：   slti  \$3, \$1, 20		; if  (i<20) \$3=1 else \$3=0

- 如果常数的值用16位无法表示，怎么办？
- 用lui指令把高16位送到寄存器的高16位，再把低16位加到该寄存器中。
  - 例3：将“0000 0000 0011 1101 0000 0000 0000 1000”送 \$3中
    则：   lui  \$3, 61
          addi \$3, \$3, 8

**文本字符串**
<div style="display:flex; gap:em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/4.2.6 文本字符串.png" width="500"/>
  </div> 
</div>

### 7. 不同结构下的代码表示
#### 1. 算术运算
eg1. f = (g + h) - (i + j)
假设 f, g, h, i, j 分别存在 \$1, \$2, \$3, \$4, \$5 寄存器中
```cpp
add $7, $2, $3
add $8, $4, $5
sub $1, $7, $8

```
注意
E.g.   f= (g+65000) - (i+50) 16位立即数：-32768~32767
指令设计时必须考虑这种情况！MIPS有一条专门的处理指令！

#### 2. Base register 基址寄存器
假设 A 是一个包含 100 个字（word）的数组, 在编译器中，将变量  g  和  h  分别与寄存器  \$1  和  \$2  关联，并假设数组  A  的基地址存储在寄存器  \$3  中。要将表达式  $g = h + A[8]$  翻译成对应的汇编代码:

经典的错误，标准的0分
```cpp
lw $4, 8($3) 		;$4 <-- A[8]
add $1, $2, $4
```
因为各数组元素是字，并按字节编址，故各占4个单元。

正确样例 $A[12] = h+A[8]$
```cpp
lw $4, 32($3) // 32 = 4 * 8  //32 即为偏移量， $3 即为基址寄存器
add $1, $2, $4
sw $1, 48($3) // store word // sw rt, offset(base)
```
**问题：如果在一个循环体内执行：g = h + A[i] ，则能否用基址寻址方式？**
不行，因为循环体内指令不能变，故首地址A不变，只能把下标 i 放在变址寄存器中，每循环一次下标加1，所以，不能用基址方式而应该用变址方式。

#### 3. Index register 变址寄存器
假设数组 A 包含 100 个字（word），编译器将变量 g 和 i 分别与寄存器 \$1 和 \$5 关联。假设数组的基地址存储在寄存器 \$3 中。现在，我们要将表达式  $g = g + A[i]$  翻译成对应的汇编代码

```cpp
addi  $6, $0, 4     ; $6 = 4
mult  $5, $6        ; Hi,Lo = i*4
mflo  $7            ; $7 = i*4, assuming i is small

add $4, $3, $7      ; $4 <-- address of  A[i]（即A+i*4）
lw  $4, 0($4) 
add $1, $1, $4
addi $5, $5, 1

```
1. `addi $6, $0, 4`：将立即数 4 加到寄存器 `$0`（始终为 0）中，结果存入寄存器 `$6`。这一步是为了得到乘数 4，因为每个数组元素占用 4 字节。

2. `mult $5, $6`：将寄存器 `$5`（变量 `i`）和寄存器 `$6`（值为 4）相乘。结果存储在 MIPS 的特殊寄存器 `Hi` 和 `Lo` 中，其中 `Lo` 存储乘积的低 32 位。

3. `mflo $7`：将乘法结果的低 32 位从 `Lo` 寄存器移动到寄存器 `$7`。这里假设 `i` 的值足够小，使得乘积不会超过 32 位。

4. `add $4, $3, $7`：将数组 `A` 的基地址（寄存器 `$3`）和偏移量（寄存器 `$7`，即 `i*4`）相加，得到数组元素 `A[i]` 的地址，并将结果存入寄存器 `$4`。

5. `lw $4, 0($4)`：从寄存器 `$4` 指向的地址（即 `A[i]` 的地址）加载一个字到寄存器 `$4` 中。

6. `add $1, $1, $4`：将寄存器 `$4`（现在包含 `A[i]` 的值）中的值加到寄存器 `$1`（变量 `g`）中，并将结果存回寄存器 `$1`。这一步实现了 `g = g + A[i]`。

7. `addi $5, $5, 1`：将寄存器 `$5`（变量 `i`）的值加 1。这一步通常用于循环或递增索引，但在这个特定的代码片段中，它可能是多余的，除非 `i` 需要在后续操作中递增。
8. 
**问题：若循环执行 g=g+A[i]，怎样使循环体内指令条数减少并缩短时间？**
用\$5做变址器，初值为0，每次\$5加4 或 左移2位，而不用乘法指令

#### 4. if-then-else & = 判断
tips : 
bne: branch if not equal
beq branch if equal

**eg1**
if (i = = j) 
       f = g+h ; 
else 
       f = g-h ;
Assuming variables i, j, f, g, h, ~ \$1, \$2, \$3, \$4, \$5
```cpp
      bne $1, $2, else              ; i!=j, jump to else       
      add $3, $4, $5        
      j   exit                      ; jump to exit
else:	sub $3, $4, $5
exit:
```

**eg2**
if (a < b) f = g+h ; else f = g-h ;
Assuming variables a, b, f, g, h, ~ \$1, \$2, \$3, \$4, \$5
```cpp
  slt   $6, $1, $2                ; if a<b, $6=1, else $6=0
  beq $6, $zero, else             ; $6=0, jump to else       
  add $3, $4, $5        
  j   exit                        ; jump to exit
else:	sub $3, $4, $5
exit:
```

#### 5. loop循环
Assuming variables g, h, i, j  ~ \$1, \$2, \$3, \$4 and base address
of array is in \$5 
translate:
```cpp
Loop: g = g +A[i];
      i = i+ j;
      if (i != h) go to Loop:
```
answer

```cpp
Loop: add $7, $3, $3            ; i*2          
      add $7, $7, $7            ; i*4 \\ 也可用移位来实现乘法
      add $7, $7, $5
      lw $6, 0($7)              ; $6=A[i] \$3中是i，\$7中是i*4
      add $1, $1, $6            ; g= g+A[i]
      add $3, $3, $4
      bne $3, $2, Loop
```

### 8. 过程调用
#### 0. leadin 
<div style="display:flex; gap:em; justify-content:;">
  <div style="text-align:center;">
    <img src="photos/4.2.8.0 过程调用leadin.png" width="500"/>
  </div> 
</div>

1. 调用指令是一种无条件转移指令，在MIPS中称为 `jump and link` 指令，采用J 型指令
   - 保存下条指令地址到32号寄存器
   - 跳转到指定地址处执行 
2. 返回指令也是一种无条件转移指令，称为 `jump register` 指令 采用 R型格式
   - 跳转到寄存器的指定的地址处执行

#### 1. 过程调用
过程调用的执行步骤（假定过程P调用过程Q）：
1. P 将入口参数放到Q能访问到的地方           
2. P 将返回地址存到特定的地方                
3. Q 为 P 保存现场，并为自己的局部变量分配空间
4. 执行过程 Q
5. Q 将返回结果放到 P 能访问到的地方
6. Q 取出返回地址，将控制转移到 P

可以看出，在以上过程中，需要为入口参数、返回地址、调用过程执行时用到的寄存器、被调用的过程中的局部变量、过程返回时的结果等数据找到存放空间
可是显然，没有足够多的寄存器来存放这些数据
所以衍生出了一个专门的存储区域用来保存这些数据，这个存储区域就是栈
<div style="display:flex; gap:em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/4.2.8.1 虚拟空间地址.png" width="500"/>
  </div> 
  <div style="text-align:center;">
    <img src="photos/4.2.8.1 MIPS程序和数据的存储器分配.png" width="500"/>
  </div> 
</div>

**过程P调用过程Q，则MIPS程序中对过程调用时寄存器的使用规定如下**
1. `$a0~$a3` 用于传递前4个非浮点数入口参数。若入口参数超过4个，则其余参数保存到栈中
2. `$v0~$v1` 用于传递从Q返回的非福点数返回参数
3. `$ra` 用于存放返回地址，又调用指令(jal)自动将返回地址送入 `$ra ($31)`
4. `$s0~$s7` 在过程P中原来的值从过程Q返回后可被P继续使用，因此，若在过程Q中使用这些寄存器，则必须先将其内容保存到栈后才能使用，并在返回P前恢复，因此其被称为**保存寄存器**
5. `$t0~$t9` 的值从过程Q返回后在P中不再需要使用，若需要由P自己保存，因此，在过程Q中不需要对其内容保存，可以自由使用，因此其被称为**临时寄存器**
6. `$a0~$a3` 的值从过程Q返回后在P中也不再需要使用，若需要，也有P自己保存，因此Q不需要为P对齐内容进行保存



#### 2. 栈 和 栈帧
**栈**
MIPS中栈的实现
- 用栈指针寄存器\$sp来指示栈顶元素
- 每个元素的长度为32位，即：一个字(4个字节)
- “入栈” 和“出栈” 操作用 sw / lw 指令来实现，需用add / sub指令调整\$sp的值，不能像x86那样自动进行栈指针的调整 （有些处理器有专门的push/pop指令，能自动调整栈指针。如x86）
- 栈生长方向
    从高→低地址“增长”，而取数/存数的方向是低→高地址（大端方式）
    每入栈1字，\$sp- 4→\$sp ;  每出栈1字，\$sp+4 →\$sp
<div style="display:flex; gap:em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/4.2.8.2 stack.png" width="500"/>
  </div>
</div>

tips 再往下加就是往低地址加哦，记得更新\$sp

**栈帧**
- 各过程有自己的栈区，称为栈帧（Stack frame），即过程的帧（procedure frame）
- **栈由若干栈帧组成**
- 用专门的帧指针寄存器指定起始位置
- 当前栈帧范围在帧指针(\$fp)和栈指针(\$sp)之间
- 若当前栈帧没有局部变量，大多数编译器不设置帧指针，以减少开销
- 程序执行时，栈指针可移动，帧指针不变。所以过程内对栈信息的访问可通过帧指针进行
- 复杂局部变量一定分配在栈帧中
- 将`$sp - 4` 作为 `$fp` 的初始值，这样帧指针总是指向当前栈帧前一个字或者当前栈帧第一个字的起始位置

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/4.2.8.2 栈帧.png" width="200"/>
  </div>
  <div style="text-align:center;">
    <img src="photos/4.2.8.2 IA-32中P调用caller，caller调用add.png" width="350"/>
  </div>
</div>

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/4.2.8.2 过程调用时MIPS中的栈和栈帧的变化 .png" width="500"/>
  </div>
</div>

**MIPS过程调用协议**

!!! : 哪来这么多事？究其原因在于寄存器是通用的。临时寄存器的值默认只调用一次，所以在被调用程序中，如果使用到保存寄存器，就要对其进行恢复，这样调用程序才能继续用

在程序执行过程中，每调用一次过程，都会在栈中生成一个对应的新栈帧，而在执行返回指令前对应的栈帧在栈中都已被释放。栈帧的生成和释放方式可以有多种，但不管采用什么方式，调用过程和被调用过程都必须遵循一定的步骤。
以下步骤是大多数MIPS 系统上采用的过程调用协议。
1. **调用过程** P 在过程调用前的执行步骤
   - 若P在返回后还要用到\$a0 ~\$a3 和\$t0~\$t9中某些寄存器，则需将这些寄存器压到当前栈帧
   - 将前4个参数送到\$a0 ~ $a3，其他参数压到当前栈帧。
   - 执行jal 指令，该指令将返回地址保存到\$ra（\$31）中，并将控制转移到被调用过程。

2. **被调用过程** Q 中的执行步骤
由三段组成：开始段、本体段（过程体）和结尾段。本体段进行具体处理。
- 开始段主要进行栈帧生成，寄存器保存和局部变量空间申请，其处理步骤如下。
（1）通过调整栈指针\$sp 来申请栈帧，即将\$sp 的值减去栈帧大小。
（2） 若Q需调用其他过程，则将返回地址寄存器\$ra 和帧指针\$fp 压入当前栈帧。
（3）设置帧指针\$fp，其值为当前栈指针\$sp 加栈帧大小。
（4）若Q中用到\$s0~\$s7中的某些寄存器，则需将这些寄存器压人当前栈帧。
（5）若Q中的局部变量发生寄存器溢出（即寄存器不够分配），则局部变量在Q的栈帧中分配空间。若有像数组和结构之类的复杂类型局部变量，则在当前栈帧中分配空间。

由此可见，栈帧大小应至少等于上述步骤中用到的存储单元的总和。

- 结尾段主要进行寄存器恢复、栈帧释放，并返回到调用程序。其处理步骤如下。
（1）若保存了\$s0~\$s7中某些寄存器值，则将这些值从当前栈帧中恢复到寄存器。
（2）若保存了返回地址和帧指针，则将它们分别恢复到寄存器\$ra 和\$fp中。
（3）调整栈指针\$sp 以释放栈帧，即将\$sp 的值加栈帧大小，或将\$fp 的值送\$sp。
（4）用返回指令jr \$ra将控制权返还给调用过程。

### 9. 例子们(这里面更多是函数套函数的情况)

<mark>Eg1. Swap</mark>

```c
void swap (int v[], int k) {
  int temp;
  temp = v[k];
  v[k] = v[k + 1];
  v[k + 1 ] = temp;
}
```
汇编表示如下 参数v和k应该在\$a0和\$a1
```cpp
swap: sll  $t1, $a1, 2      # k << 2, multiply k by 4 转换成bits
      add  $t1, $t1, $a0    # address of v[k]
      lw   $t0, 0($t1)      # load v[k]
      lw   $t2, 4($t1)      # load v[k + 1]
      sw   $t2, 0($t1)      # store v[k + 1] into v[k]
      sw   $t0, 4($t1)      # store old v[k] into v[k + 1]
      jr   $31              # return to caller
```

解析:
**首先,swap不是主程序,而是一个被调用过程,但其不再调用其他过程,所以是一个叶子过程(不再调用其他过程的过程)**
按照调用协议, swap过程的调用过程已将 v(数组的首地址), k 分别放在 \$a0, \$a1 中, 
假定在swap过程体中先使用临时寄存器\$t0 ~ \$t9 不够再用 \$a0 ~ \$a7, 即 **局部变量 temp 分配在\$t0中**

按照以上协议,开始段无需保存任何寄存器的值,也无需在栈中分配局部变量.因为swap是叶子过程,**所以也不用保存返回地址和帧指针**,故其栈帧为空,结尾段直接返回即可

*或者这样写*
如果  swap  是一个真正的子函数，调用者假定这些寄存器不会被破坏，而你直接改写，会导致调用者后续值错误。
```cpp
swap:	
addi	$sp,$sp, –12	; 栈增长3个
sw	$31, 8($sp)	; 返回地址入栈	
sw	$s2, 4($sp)  	; 保留寄存器$s2入栈
sw	$s3, 0($sp) 	; 保留寄存器$s3入栈

    sll	$s2, $a1, 2  	      ; mulitply k by 4	
    addu $s2, $s2, $a0        ; address of v[k]	
    lw	$t0, 0($s2)	      ; load v[k]	
    lw	$s3, 4($s2)	      ; load v[k+1]	
    sw	$s3, 0($s2)	      ; store v[k+1] into v[k]	
    sw	$t0, 4($s2)	      ; store old v[k] into v[k+1]

lw $s3, 0($sp)       ; 恢复$s3
lw $s2, 4($sp)       ; 恢复$s2
lw $31, 8($sp)       ; 恢复$31（$ra）
addi  $sp,$sp, 12    ; 退栈 	
jr  $31              ; 从swap返回到调用过程
```
如果将所有内部寄存器都用临时寄存器 (如$t1等)，则叶子过程swap的栈帧为空，且上述没有缩进指令都可去掉 （就是第一个示例那样子）

调用的时候如何使用？
```
  jal  swap --- jump and link (跳转并链接)
        $31 = PC+4    # $31=$ra
        goto swap
```
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/4.2.9 调用程序过程.png" width="200"/>
  </div>
</div>

<mark>Eg2. set_array</mark>

```cpp
void set_array(int num) {
  int i, array[10];
  for (i = 0; i  < 10; i ++) {
    arrar[i] = compare (num, i);
  }   
}

int compare (int a, int b) {
  if ( sub (a, b) >= 0) return 1;
  else  return 0;
}      

int sub (int a, int b) {
  return a - b;
}

```
- 过程set_array的入口参数为num，没有返回参数，有一个局部数组。
假定局部变量 i 分配在临时寄存器\$t2中，这样无需在栈帧中为 i 分配空间，也无需在栈帧中保存\$t2。

- 被调用过程为compare，因此，set_array的栈帧中除了保留所用的保存寄存器外，必须保留返回地址（Why: **因为  set_array  里又调用了  compare ，这句  jal compare  会冲掉  $ra （返回地址），所以  set_array  必须在栈帧里先把  \$ra  存起来，否则将来自己“回不去”。**），并给局部数组预留4×10=40个字节的空间。）
- **（是否保存\$fp要看具体情况，如果确保后面都不用到\$fp，则可以不保存，但为了保证\$fp的值不被后面的过程覆盖，通常情况下，应该保存\$fp的值**

- 从过程体来看，从compare返回后还需要用到数组基地址，故将其分配在\$s1中。需将\$s1保存在栈帧中（Why: **因为  \$s1  被用作“数组基址”且生命周期跨过了  jal compare ，而  \$s  寄存器属于 callee-saved，所以调用者（set_array）必须自己负责把它先存栈里，否则从 compare 回来后值可能已被破坏。**），另外加上返回地址\$ra、帧指针\$fp、局部数组， set_array的栈帧空间最少为3×4+40=52B。 
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/4.2.9 过程调用举例.png" width="450"/>
  </div>
</div>

```cpp
set-array:    addi   $sp, $sp, –52	 # generate stack frame
              sw     $ra, 48 ($sp)	 # save $ra on stack
              sw     $fp, 44($sp)	 # save $fp on stack
              sw     $s1, 40($sp)	 # save $s1 on stack
              addi   $fp, $sp, 48	 # set $fp
              move   $s1, $sp	         # $s1=base address of array 
              move   $t0, $a0	         # $t0=num 
              move   $t2, $zero	         # i=0
 for-loop:    slti   $t1, $t2, 10      	 # if i<10 $t1=1 else $t1= 0
              beq    $t1, $zero, exit1   # if $t1= 0, jump to exit1
              move   $a0, $t0	         # $a0=num 
              move   $a1, $t2	         # $a1=i
              jal    compare 	         # call compare
              sll    $t1, $t2, 2       	 # i×4 
              add    $t1, $s1, $t1	 # $t1=array[i]		
              sw     $v0, 0($t1)	 # store result to array[i]
              addi   $t2, $t2, 1	 # i=i+1
              j      for-loop
    exit1:    lw     $ra, 48($sp)	 # restore $ra 
              lw     $fp, 44($sp)	 # restore $fp
              lw     $s1, 40($sp)        # restore $s1 
              addi   $sp, $sp, 52	 # free stack frame
              jr     $ra		 # return to caller
```

```cpp
compare:  addi     $sp, $sp, –8
          sw       $ra, 4($sp)
          sw       $fp, 0($sp)		# save $fp on stack
          addi     $fp, $sp, 4		# set $fp
          jal      sub
          slt      $t1, $v0, $zero 	# if $v0<0 $t1=1 else $t1= 0
          beq      $t1, $zero, else 	# if $t1= 0, jump to else
          move     $v0, $zero        	# return 0
          j        exit2   
else:     ori      $v0, $zer0,          # return 1
exit2:    lw       $fp, 0($sp)
          lw       $ra, 4($sp)
          addi     $sp, $sp, 8
          jr       $ra

sub:      sub      $v0, $a0, $a1        
          jr       $ra
```
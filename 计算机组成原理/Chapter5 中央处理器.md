[TOC]

# <center> 第五章 中央处理器

## 一、数据通路概述与MIPS指令系统
### 1、 CPU的功能及其与计算机性能的关系
**CPU执行指令的过程**
1. 取指令：从存储器中取出指令，放入指令寄存器（IR）中 // PC + 4(不一定，看字长是多少) → PC
2. 译码指令：根据指令的操作码，确定指令的类型
3. 执行指令：根据指令的类型，进行相应的操作
4. 进行主存地址运算：计算出主存地址
5. 取操作数：从寄存器堆或主存中取出操作数
6. 执行运算：进行算术或逻辑运算
7. 存储结果：将运算结果存入寄存器堆或主存中

以上每一步都需要进行异常检测，若有异常(CPU内部发生的)，自动切换到异常处理程序；若有中断(CPU外部事件引起的)请求，则在当前指令执行完后，转到中断处理程序。

>Q: 取指令一定要在最开始做吗？A: 不一定，可以在执行指令的同时取下一条指令，提高效率。
>Q: PC + 4 一定要在译码前做吗？A: 不一定，可以在取指令后立即进行。
>Q：译码必须在指令执行前做吗？A：必须，因为需要根据指令类型决定执行什么操作。

**CPU的实现与计算机性能的关系**
1. CPU时钟频率：时钟频率越高，CPU执行指令的速度越快
2. CPI（Cycles Per Instruction，每条指令的平均时钟周期数）：CPI越低，CPU执行指令的速度越快
3. 指令集设计：指令集设计合理，可以减少CPI，提高CPU性能

前两个主要影响因素与CPU的硬件实现有关，第三个因素与指令集设计有关。

**每条指令的功能又以下四种基本操作的组合实现**
1. 读取某一主存单元的内容，并将其装入某个寄存器（取指， 取数）
2. 把一个数据从某个寄存器存入给定的主存单元中（存结果）
3. 把一个数据从某个寄存器送到另一个寄存器或者ALU（取数，存结果）
4. 进行算术或逻辑运算（PC+1，计算地址，运算）

>操作功能可形式化描述
>操作功能可形式化描述
>描述语言称为寄存器传送语言RTL (Register Transfer Language)
>本章所用的RTL规定如下：
>1. 用R[r]表示寄存器r的内容；
>2. 用M[addr]表示主存单元addr的内容；
>3. 传送方向用“←”表示，传送源在右，传送目的在左；
>4. 程序计数器PC直接用PC表示其内容。

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/5.1.1 CPU基本组成原理图.png " width="600"/>
  </div>
</div>

### 2、数据通路的位置
计算机的五大组成部分： Control DataPath构成CPU + Memory + I/O

**什么是数据通路(DataPath)?**
指令执行过程中，数据所经过的路径，包括路径中的部件。它是指令的执行部件。

**控制器的功能**  
对指令进行译码，生成指令对应的控制信号，控制数据通路的动作。能对执行部件发出控制信号，是指令的控制部件。

### 3、数据通路设计概述
#### 1. 数据通路的功能和实现
**数据通路的基本结构**
1. 由两类元件组成：
  - 时序逻辑元件（存储元件）：寄存器堆、主存
  - 组合逻辑元件（操作元件）：算术逻辑单元ALU、多路选择器MUX、移位器等
2. 元件间的连接方式
  - 总线连接方式：各元件通过总线相连，节省连接线，但传输速度较慢
  - 分散连接方式：各元件通过专用连接线相连，传输速度快，但连接线较多
3. 数据通路如何构成？
  - 由“操作元件”和“存储元件”通过总线方式或分散方式连接而成
4. 数据通路的功能
  - 进行数据存储、处理、传送

**操作元件和状态元件**
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/5.1.3.1 操作元件.png " width="500"/>
  </div>
  <div style="text-align:center;">
    <img src="photos/5.1.3.1 状态元件.png " width="500"/>
  </div>
</div>

$\quad$

**存储元件中何时状态被改变？**
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/5.1.3.1 存储元件中何时状态被改变.png " width="400"/>
  </div>
</div>

**寄存器**
<div style="display:flex; gap:2em; justify-content:;">
  <div style="text-align:center;">
    <img src="photos/5.1.3.1 寄存器.png " width="200"/>
  </div>
</div>

>有一个**写使能**（Write Enable-WE）信号
> - 0: 时钟边沿到来时，输出不变
> - 1: 时钟边沿到来时，输出开始变为输入
> 
>若每个时钟边沿都写入，则不需WE信号

**寄存器组**
<div style="display:flex; gap:2em; justify-content:;">
  <div style="text-align:center;">
    <img src="photos/5.1.3.1 寄存器组.png " width="200"/>
  </div>
</div>

>- **两个读口**（组合逻辑操作）：`busA`和`busB`分别由`RA`和`RB`给出地址。地址`RA`或`RB`有效后，经一个“取数时间(AccessTime)”，`busA`和`busB`有效。 
>- **一个写口**（时序逻辑操作）：写使能为1的情况下，时钟边沿到来时，`busW`传来的值开始被写入`RW`指定的寄存器中。

**寄存器内部结构**
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/5.1.3.1 寄存器内部结构.png " width="500"/>
  </div>  
</div>

**理想存储器**
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/5.1.3.1 理想寄存器.png " width="400"/>
  </div>  
</div>

>Data Out：32位读出数据
>Data In： 32位写入数据
>Address：读写公用一个32位地址

>读操作（组合逻辑操作）：地址Address有效后，经一个“取数时间AccessTime”，Data Out上数据有效。
>写操作（时序逻辑操作） ：写使能为1的情况下，时钟Clk边沿到来时，Data In传来的值开始被写入Address指定的存储单元中。


#### 2. 数据通路的定时
**同步系统**
>1. 所有存储元件由同一时钟信号控制，所有动作有专门时序信号来定时
>2. 所有存储元件在时钟边沿同时更新，由时序信号规定何时发出什么动作

例如，指令执行过程每一步都有控制信号控制，由定时信号确定控制信号何时发出、作用时间多长

**时序信号**
>同步系统中用于同步控制的定时信号，如时钟信号

**指令周期**
>完成一条指令所需的时间，通常分为若干个时钟周期（多周期CPU）或一个时钟周期（单周期CPU）

**早期计算机的三级时序信号**
> 机器周期 节拍 脉冲
> 指令周期可分为取指令、读操作数、执行并写结果等多个基本工作周期，称为机器周期。
> 机器周期有取指令、存储器读、存储器写、中断响应等不同类型
> 每个机器周期又可分为若干个节拍，每个节拍由一个脉冲信号来定时，通常一个机器周期分为三个节拍，称为三级时序信号。

<div style="display:flex; gap:2em; justify-content:;">
  <div style="text-align:center;">
    <img src="photos/5.1.3.2 三级时序.png " width="400"/>
  </div>
</div>

$\quad$

**现代计算机的时钟周期**
<div style="display:flex; gap:2em; justify-content:;">
  <div style="text-align:center;">
    <img src="photos/5.1.3.2 现代计算机的时钟周期.png " width="400"/>
  </div>
</div>

#### 3. 总线型数据通路
**早期累加器型指令系统数据通路**
MBR、 IBR 、 MAR 、 MDR 全称分别是 Memory Buffer Register、Instruction Buffer Register 、 Memory Address Register、 Memory Data Register，
中文意思是 存储器缓冲寄存器、指令缓冲寄存器、存储器地址寄存器、存储器数据寄存器。
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/5.1.3.3 早期.png " width="500"/>
  </div>  
</div>

**单总线和三总线数据通路**
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/5.1.3.3 单总线数据通路.png " width="500"/>
    <div><strong>单总线数据通路</strong></div>
  </div>
  <div style="text-align:center;">
    <img src="photos/5.1.3.3 三总线数据通路.png " width="500"/>
    <div><strong>三总线数据通路</strong></div>  
  </div>
</div>

### 4、MIPS指令指令系统简介
#### 1. MIPS指令格式
**寄存器数据指定**
> 寄存器编号占5位，一个寄存器组最多有32个寄存器
> GPR: General Purpose Register 通用寄存器： 有32个32位寄存器 R0~R31 r0恒为0
> FPR: Floating Point Register 浮点寄存器： 有32个32位寄存器 F0~F31
> HI、LO、PC、CPC等特殊寄存器（无编号）

**存储器数据指定**
32位字长，字地址编址, 32位地址，寻址空间4GB（2^32字节）
只能通过load/store指令访问存储器数据

大端方式
数据要求字对齐, 即地址必须是4的倍数
> 例如： lw $t0, 100($s0) // $t0 = M[$s0 + sign_ext(100)]

数据地址通过一个32位寄存器内容加上一个16位**有符号**立即数偏移量（**符号扩展成32位**）计算得出
> 例如： A是一个32位地址, A_upper = A[31:16], A_lower = A[15:0]
>  lui  \$t0, A_upper_adjusted
>  sw   \$s0, A_lower(\$t0)
> 其中 A_upper_adjusted = A_upper + (A_lower < 0 ? 1 : 0)
> 究其原因，在sw时是因为16位有符号立即数的符号扩展可能会影响高16位的值。

\[\quad\]

**三种指令格式**
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/5.1.4.1 MIPS指令格式.png " width="600"/>
  </div>  
  <div style="text-align:center;">
    <img src="photos/5.1.4.1 MIPS指令字段含义.png " width="600"/>
  </div>
</div>

后见 Chapter4.2 程序的机器级表示 详细介绍

## 二、单周期MIPS处理器的数据通路设计
### 1. 选取MIPS指令子集作为CPU设计目标
需要实现的指令
> **R型指令：**
> add rd, rs, rt
> sub rd, rs, rt
> ori rd, rs, imm16 
> **I型指令：**
> lw rt, imm16(rs)
> sw rt, imm16(rs)
> beq rs, rt, imm16
> **J型指令：**
> j target26

**设计指令的步骤**
> 第一步：分析每条指令的功能，并用RTL(Register Transfer Language)来表示。
> 第二步：根据指令的功能给出所需的元件，并考虑如何将他们互连。
> 第三步：确定每个元件所需控制信号的取值。
> 第四步：汇总所有指令所涉及到的控制信号，生成一张反映指令与控制信号之间关系的表。
> 第五步：根据表得到每个控制信号的逻辑表达式，据此设计控制器电路。

eg. 
```cpp
// 指令功能的RTL表示
add rd , rs, rt
    M[PC] ← IR
    R[rd] ← R[rs] + R[rt]
    PC ← PC + 4

lw rt , imm16 (rs)
    M[PC] ← IR
    ALUOut ← R[rs] + sign_ext(imm16)
    R[rt] ← M[ALUOut]
    PC ← PC + 4
```

\[\quad\]
\[\quad\]

**取指令部件**
```cpp
M[PC] ← IR
PC ← PC + 4
//Branch and Jump指令也需要取指令部件, PC更新为转移目标地址 
```
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/5.2.1 取指令部件.png " width="500"/>
  </div>
</div>



### 2. 综合所有指令的数据通路


## 三、 单周期控制器的设计

## 四、多周期MIPS处理器的数据通路设计

## 五、 微程序控制器的设计与异常处理

```


 






































11
```
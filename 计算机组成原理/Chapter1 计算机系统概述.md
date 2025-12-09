[TOC]
# <center> 第一章 计算机系统概述
## 1. 计算机系统的组成以及计算机层次结构
<p align="center">
<img src="photos\1.1 典型硬件组成.png" width="70%" height="100%">
<p align="center">
  <strong>典型硬件组成</strong>
</p>

<p align="center">
<img src="photos\1.1 源文件到可执行文件.png" width="70%" height="100%">
<p align="center">
  <strong>源文件到可执行文件</strong>
</p>


<p align="center">
<img src="photos\1.1 Hello程序流动.png" width="70%" height="100%">
<p align="center">
  <strong>Hello程序流动</strong>
</p>

<p align="center">
<img src="photos\1.1 层次之间的转换.png" width="70%" height="100%">
<p align="center">
  <strong>层次之间的转换</strong>
</p>

<p align="center">
<img src="photos\1.1 计算机系统的不同用户.png" width="70%" height="100%">
<p align="center">
  <strong>计算机系统的不同用户</strong>
</p>

<p align="center">
<img src="photos\1.1 ISA和计算机组成（微结构）之间的关系.png" width="70%" height="100%">
<p align="center">
  <strong>ISA和计算机组成（微结构）之间的关系</strong>
</p>

---

## 2. 计算机性能评价
**在这里主要考虑 CPU 时间， 以下是一些必要的概念和参数**
  - 时钟周期
  - 时钟频率(时钟周期的倒数)
  - CPI : 执行一条指令需要的时钟周期数。对于不同的指令，CPI也不尽相同。对于一个程序或机器来说，综合CPI指该程序或机器运行所有指令执行所需的平均时钟周期数。

$$
    用户 CPU 时间 = 程序总时钟周期数 \times 时钟周期 \\
    程序总时钟周期数 = 程序总指令条数 \times CPI \\
    程序总时钟周期数 = \sum_{i = 1}^{n} CPI_i \times C_i  
$$

eg1.
>程序P在机器A上运行需10 s， 机器A的时钟频率为400MHz。 现在要设计一台机器B，希望该程序在B上运行只需6 s. 
机器B时钟频率的提高导致了其CPI的增加，使得程序P在机器B上时钟周期数是在机器A上的1.2倍。机器B的时钟频率达到A的多少倍才能使程序P在B上执行速度是A上的10/6=1.67倍？
```
Answer:
     CPU时间A = 时钟周期数A / 时钟频率A
     时钟周期数A = 10 sec x 400MHz = 4000M个
     时钟频率B = 时钟周期数B / CPU时间B = 1.2 x 4000M / 6 sec = 800 MHz
```

eg2.
>假设计算机M 的指令集中包含A、B、C 三类指令，其CPI分别为1、2、4。程序
P在M上被编译成两个不同的目标代码序列 P1 和 P2, P1 所含A B.C三类指令的条数分别为8、2、2，P2所含A B.C三类指令的条数分别2、5、3。 请问，哪个代码序列执行速度快？它们的CPI分别是多少？
```
    P1 的 CPI = (8 + 4 + 8) / 12 
    P2 的 CPI = (2 + 10 + 12) / 10
    注： P1 的 总时钟数更少 故其执行速度更快。 所以计算机的速度不能看单一的评价标准
```

**用指令执行速度进行性能评估**
Million Instructions Per Second  （定点指令执行速度）
$$
MIPS	= Instruction Count / Second \times 1/10^6
= Clock Rate / CPI \times 1/10^6
$$
局限性：
因为每条指令执行时间不同，所以MIPS总是一个平均值。
- 不同机器的指令集不同
- 程序由不同的指令混合而成
- 指令使用的频度动态变化
- Peak MIPS: （不实用）

**用基准程序进行性能评估**
测试程序集
SPEC (Systems Performance Evaluation Committee) 

可用以下两种平均值来评价：
Arithmetic mean(算术平均)：求和后除n
Geometric mean(几何平均)：求积后开根号n
根据算术平均执行时间能得到总平均执行时间
根据几何平均执行时间不能得到程序总的执行时间
执行时间的规格化（测试机器相对于参考机器的性能）：
time on reference machine ÷ time on measured machine 
平均规格化执行时间不能用算术平均计算，而应该用几何平均
program A going from 2s to 1s as important as program B going from 2000s to 1000s. 
（算术平均值不能反映这一点！）         

**Amdahl 定律**
<p align="center">
<img src="photos\1.2 Amdahl定律1.png" width="70%" height="100%">
<img src="photos\1.2 Amdahl定律2.png" width="70%" height="100%">
</p>

---

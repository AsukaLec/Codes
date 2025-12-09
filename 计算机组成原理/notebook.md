[TOC]
# <center> 计算机组成原理
## <center> 第一章 计算机系统概述
### 1. 计算机系统的组成以及计算机层次结构
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

### 2. 计算机性能评价
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

## <center> 第二章 数据的机器级表示

### 一、 数值数据的表示

#### 1. 进位计数制
用一个下标表示数的基（ radix / base）
或用后缀B-二进制（H-十六进制（前缀0x-）、O-八进制） 
$11001_2 = 25_{10}、11001B= 25$

**<mark> i. 二、八、十六进制数的相互转换**
- 八进制数转换成二进制数
$(13.724)_8=(  001\quad 011\quad .\quad 111\quad  010\quad  100  )_2=(1011.1110101)_2$
- 十六进制数转换成二进制数
$(2B.5E)_{16} = (00101011\quad . \quad 01011110)_2 = (101011.0101111)_2  $
- 二进制数转换成八进制数  
$(0.10101)_2 = (  000\quad . \quad101\quad  010  )_2 = ( 0.52)_8 $ 
- 二进制数转换成十六进制数
$(11001.11)_2 = (  0001\quad  1001\quad . \quad 1100  )_2 = ( 19.C )_{16}$

**<mark> ii. R进制数 => 十进制数**
按“权”展开 (a power of R)
$$(10101.01)_2=1\times 2^4+1\times  2^2+1\times 2^0+1\times 2^{-2}=(21.25)_{10} \\
(307.6)_8=3\times 8^2+7\times 8^0+6\times 8^{-1}=(199.75)_{10} \\
(3A. 1)_{16}=3\times 16^1+10\times 16^0+1\times 16^{-1}=(58.0625)_{10}$$

**<mark> iii. 十进制数 => R进制数**
    整数部分和小数部分分别转换
① 整数(integral part)----“除基取余，上右下左”
② 小数(fractional part)----“乘基取整，上左下右”
<p align="center">
<img src="photos\2.1.1.3 进制转换.png" width="70%" height="100%">
</p>

---

#### 2. 如何用二进制编码（正负号）
原码表示
<p align="center">
<img src="photos\2.1.2 原码.png" width="50%" height="100%">
</p>

**i. 补码 : 实现 + 与 - 的统一**
补码的定义    假定补码有n位，则：
定点整数：$[X]_补 = 2^n + X （-2^n ≤ X ＜ 2^n ，mod 2^n）$

eg. $ -3 \equiv 9 (mod 12) $
结论1：一个负数的补码等于模减该负数的绝对值。
结论2：对于某一确定的模，数x减去小于模的数y，总可以用数x加上-y的补码来代替。
```
9828 - 1928 = 9828 + (10e4 - 1928)
          = 9828+8072
          = 10e4 + 7900  
          = 7900（mod 10e4）
```

```
0111 1111 - 0100 0000 = 0111 1111 + (2^8- 0100 0000)
                      = 0111 1111 + 1100 0000 
                      = 1 0011 1111 (mod 2^8)
                      = 0011 1111   
```
<mark>结论1： 一个负数的补码等于对应正数补码的“各位取反、末位加1”
```
1 = 0001
1 - 2 = 0001 + (1 0000 - 0010) 
      = 0001 + 1110
      = 1111
  - 1 = 1111
```
<p align="center">
<img src="photos\2.1.2.1 补码.png" width="50%" height="100%">
</p>

**求真值？**
先看第一位（符号位）判断正负，整数其余位正常用，负数取反+1再算

**ii. 移码**
<p align="center">
<img src="photos\2.1.2.2 移码.png" width="60%" height="100%">
</p>

**iii. 无符号数**
<p align="center">
<img src = "photos\2.1.2.3 无符号整数.png" width = 60% height = 100%>
</p>
<mark>MIPS规定：无符号数运算溢出时，不产生“溢出异常”


**iv. 有符号整数**
<p align="center">
<img src = "photos\2.1.2.4 有符号整数.png" width = 60% height = 100%>
</p>

#### 3. 浮点数表示（小数点的表示）
**浮点数表示范围**
<p align="center">
<img src = "photos\2.1.3 浮点数构成.png" width = 60% height = 100%>
</p>

**浮点数的构成**
<p align="center">
<img src = "photos\2.1.3 浮点数的表示.png" width = 60% height = 100%>
</p>

#### 4. IEEE 754 Floating Point Standard
前置知识:规格化数与非规格化数
若浮点数的基数为2，则尾数规格化的浮点数的形式应为
$\pm 0.1bbbbbbb...b \times 2^E$
<mark>尾数部分的真值要大于或等于 $1/R， R$ 为 基数</mark>
<p align="center">
<img src = "photos\2.1.4 浮点数.png" width = 60% height = 100%>
</p>
<p align="center">
  <strong>浮点数</strong>
</p>

<p align="center">
<img src = "photos\2.1.4 特殊.png" width = 60% height = 100%>
</p>
<p align="center">
  <strong>特殊情况</strong>
</p>

<mark>二进制浮点数向十进制转换</mark>
eg.
```
1  0111 1101  110 0000 0000 0000 0000 0000
```
$(-1)^S \times (1 + Significand) \times 2^{(Exponent-127)}$

Exponent:
    • $0111 1101_{two} = 125_{ten}$
    • $Bias adjustment: 125 - 127 = -2$
Significand:
$$        
    1 + 1 \times  2 ^{- 1}+ 1 \times  2 ^{- 2} + 0 \times  2^{-3} + 0 \times  2^{-4}   + 0 \times  2^{-5} +...\\        
    = 1 + 2 ^{- 1} + 2 ^{- 2} = 1 + 0.5 + 0.25 = 1.75
$$
Represents: $-1.75_{ten} \times 2^{-2} = - 0.4375$

<mark>十进制浮点数向二进制转换</mark>

eg. -12.75 
转换整数部分:
$           12 = 8 + 4 = 1100_2$
转换小数部分:
$           .75 = .5 + .25 = .11_2$
整合并规格化:
$           1100.11 = 1.10011 \times 2^3$
转换指数: 
$127 + 3 = 128 + 2 = 1000 \quad0010_2$
答案:
$1 \qquad  1000 \quad 0010 \qquad 100\quad 1100\quad 0000\quad 0000 \quad 0000\quad 0000$

**异常**
<p align="center">
<img src = "photos\2.1.4 异常1.png" width = 60% height = 100%>
<img src = "photos\2.1.4 异常2.png" width = 60% height = 100%>
</p>

**<mark>关于 IEEE 754 的问题**

- **可表示的数值范围是什么？**

  单精度浮点数的最大值：约  $3.4 \times 10^{38}$  
  双精度浮点数的最大值：约  $1.8 \times 10^{308}$

- **类型转换的正确性**

  将整数转为浮点数再转回整数，对于双精度浮点数，结果正确；但转为单精度时不一定正确。  
  将浮点数转为整数再转回浮点数，无论是单精度还是双精度，结果都不一定正确。

- **浮点数加法结合律**

  浮点数加法不满足结合律。例如：  
   $x = -1.5 \times 10^{38}$， $y = 1.5 \times 10^{38}$， $z = 1.0$  
   $(x + y) + z = 1.0$，而  $x + (y + z) = 0.0$


#### 5. 十进制数的表示(decimal)
1. **ASCII码**
**前分隔数字串**
符号位单独用一个字节表示，位于数字串之前。
正号用“+”的ASCII码(2BH)表示；负号用“-”的ASCII码(2DH)表示
例：十进制数+236表示为: 2B 32 33 36H
           0010 1011 0011 0010 0011 0011 0011 0110B
          十进制数-2369表示为: 2D 32 33 36 39H
           0010 1101 0011 0010 0011 0011 0011 0110 0011 1001B
**后嵌入数字串**
符号位嵌入最低位数字的ASCII码高4位中。比前分隔方式省一个字节。
正数不变；负数高4位变为0111.
例：十进制数+236表示为: 32 33 36H
           0011 0010 0011 0011 0011 0110B
          十进制数-2369表示为: 32 33 36 79H
           0011 0010 0011 0011 0011 0110 0111 1001B
缺点：占空间大，且需转换成二进制数或BCD码才能计算。

2. **BCD码**
编码思想:  每个十进数位至少有4位二进制表示。而4位二进制位可组合成16种状态，去掉10种状态后还有6种冗余状态。
编码方案
1． 十进制有权码
每个十进制数位的4个二进制位（称为基2码）都有一个确定的权。8421码是最常用的十进制有权码。也称自然BCD（NBCD）码。
2． 十进制无权码
每个十进制数位的4个基2码没有确定的权。在无权码方案中，用的较多的是余3码和格雷码。
3．其他编码方案  （5中取2码、独热码等）
符号位的表示：
 “+”：1100 ； “-”：1101
例：+236=(1100 0010 0011 0110)8421    (占2个字节)
    -2369=(1101 <mark>0000</mark> 0010 0011 0110 1001)8421    (占3个字节)
补零！！！

### 二、非数值数据、数据排列
#### 1. 逻辑值
<p align="center">
<img src = "photos\2.2.1 逻辑值.png" width = 60% height = 100%>
</p>

#### 2. 西文字符
<p align="center">
<img src = "photos\2.2.2 西文字符.png" width = 60% height = 100%>
</p>
#### 3. 汉字
汉字是表意文字，一个字就是一个方块图形。
汉字数量巨大，总数超过6万字。

**有以下几种汉字代码：**
- 输入码：对汉字用相应按键进行编码表示，用于输入
- 内码：用于在系统中进行存储、查找、传送等处理
- 字模点阵或轮廓描述: 描述汉字字模点阵或轮廓，用于显示/打印

>Q：西文字符常用的内码是什么？
A: ASCII码！
对于汉字内码的选择，必须考虑以下几个因素：
① 不能有二义性，即不能和ASCII码有相同的编码。
② 尽量与汉字在字库中的位置有关，便于汉字查找和处理。
③ 编码应尽量短。
国标码（国标交换码）
      1981年我国颁布了《信息交换用汉字编码字符集·基本集》(GB2312—80)。该标准选出6763个常用汉字，为每个汉字规定了标准代码，以供汉字信息在不同计算机系统间交换使用
可在汉字国标码的基础上产生汉字机内码

**GB2312-80字符集**
**由三部分组成：**
① 字母、数字和各种符号，包括英文、俄文、日文平假名与片假名、罗马字母、汉语拼音等共687个
② 一级常用汉字，共3755个，按汉语拼音排列
③ 二级常用汉字，共3008个 ，不太常用，按偏旁部首排列
**汉字的区位码**
码表由94行、94列组成，行号为区号，列号为位号，各占7位
指出汉字在码表中的位置，共14位，区号在左、位号在右
**汉字的国标码**
每个汉字的区号和位号各自加上32（20H），得到其“国标码”
国标码中区号和位号各占7位。在计算机内部，为方便处理与存储，前面添一个0，构成一个字节

**汉字内码**（区位码→国标码→内码）
至少需2个字节才能表示一个汉字内码，这由由汉字的总数决定！
可在GB2312国标码的基础上产生汉字内码
为与ASCII码区别，将国标码的两个字节的第一位置“1”后得到一种汉字内码
   例如，汉字“大”在码表中位于第20行、第83列。因此区位码为0010100 1010011，国标码为00110100 01110011，即3473H。前面的34H和字符“4”的ACSII码相同，后面的73H和字符“s”的ACSII码相同，将每个字节的最高位各设为“1”后，就得到其内码：B4F3H (1011 0100 1111 0011B)，因而不会和ASCII码混淆。

**国际字符集**
>国际字符集的必要性
不同地区使用不同字符集内码，如中文GB2312 / Big5、日文Shift-JIS / EUC-JP等。在安装中文系统的计算机中打开日文文件，会出现乱码。
为使所有国际字符都能互换，必须创建一种涵盖全部字符的多字符集。
国际多字符集
通过对各种地区性字符集规定使用范围来唯一定义各字符的编码。
国际标准ISO/IEC 10646提出了一种包括全世界现代书面语言文字所使用的所有字符的标准编码，有4个字节编码(UCS-4)和2字节编码(UCS-2) 。
我国（包括香港、台湾地区）与日本、韩国联合制订了一个统一的汉字字符集（CJK编码），共收集了上述不同国家和地区共约2万多汉字及符号，采用2字节编码 (即：UCS-2) ，已被批准为国家标准(GB13000 )。
Windows操作系统(中文版)已采用中西文统一编码，收集了中、日、韩三国常用的约2万汉字，称为“Unicode”，采用2字节编码，与UCS-2一致 。  

**汉字的字模点阵码和轮廓描述**
为便于打印、显示汉字，汉字字形必须预先存在机内
- 字库 (font)：所有汉字形状的描述信息集合
- 不同字体 (如宋体、仿宋、楷体、黑体等) 对应不同字库
- 从字库中找到字形描述信息，然后送设备输出

问题：如何知道到哪里找相应的字形信息？
汉字内码与其在字库中的位置有关！！

字形主要有两种描述方法：
- 字模点阵描述（图像方式）
- 轮廓描述（图形方式）
  - 直线向量轮廓
  - 曲线轮廓（True Type字形）
  
#### 4. 数据的基本宽度

比特（bit）是计算机中处理、存储、传输信息的最小单位
二进制信息的计量单位是“字节”(Byte)，也称“位组”
现代计算机中，存储器按字节编址
字节是最小可寻址单位 (addressable unit ) 
如果以字节为一个排列单位，则LSB表示最低有效字节，MSB表示最高有效字节


除比特和字节外，还经常使用“字”(word)作为单位
“字”和 “字长”的概念不同 
>“字长”指定点运算数据通路的宽度。
（数据通路指CPU内部数据流经的路径以及路径上的部件，主要是CPU内部进行数据运算、存储和传送的部件，这些部件的宽度基本上要一致，才能相互匹配。因此，”字长”等于CPU内部总线的宽度、运算器的位数、通用寄存器的宽度等。 ）
“字”表示被处理信息的单位，用来度量数据类型的宽度。
字和字长的宽度可以一样，也可不同。
  例如，x86体系结构定义“字”的宽度为16位，但从386开始字长就是32位了。

**数据度量单位**
存储二进制信息时的度量单位要比字节或字大得多
容量经常使用的单位有：
    “千字节”(KB)，1KB=2e10字节=1024B
    “兆字节”(MB)，1MB=2e20字节=1024KB
    “千兆字节”(GB)，1GB=2e30字节=1024MB
    “兆兆字节”(TB)，1TB=2e40字节=1024GB
  通信中的带宽使用的单位有：
    “千比特/秒”(kb/s)，1kbps=10e3 b/s=1000 bps
    “兆比特/秒”(Mb/s)，1Mbps=10e6 b/s =1000 kbps
    “千兆比特/秒”(Gb/s)，1Gbps=10e9 b/s =1000 Mbps
    “兆兆比特/秒”(Tb/s)，1Tbps=10e12 b/s =1000 Gbps

#### 5. 数据的存储排列
<p align="center">
<img src = "photos\2.2.5 数据的存储方式.png" width = 60% height = 100%>
<img src = "photos\2.2.5 大小端存取方式.png" width = 60% height = 100%>
</p>

---

**字节交换**
<p align="center">
<img src = "photos\2.2.5 字节交换.png" width = 60% height = 100%>
</p>

**Alignment(对齐)**
<div style="display:flex; gap:em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos\2.2.5 对齐1.png" width="400"/>
  </div>
  <div style="text-align:center;">
    <img src="photos\2.2.5 对齐2.png" width="400"/>
  </div>
  <div style="text-align:center;">
    <img src="photos\2.2.5 对齐3.png" width="420"/>
  </div>
</div>

---

## <center> 第三章 运算方法和运算部件
### 一、基本运算部件
#### 1. 半加器和全加器

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos\3.1.1全加器.jpg" width="300"/>
    <div><strong>1 位全加器逻辑图</strong></div>
  </div>
  <div style="text-align:center;">
    <img src="photos\3.1.1半加器.jpg" width="300"/>
    <div><strong>1 位半加器逻辑图</strong></div>
  </div>
  <div style="text-align:center;">
    <img src="photos\3.1.1八位加法器.jpg" width="320"/>
    <div><strong>8 位全加器逻辑图</strong></div>
  </div>
</div>

输入为加数、被加数和低位进位`Cin`，输出为和`F`、进位`Cout` 
化简后 有

  

$$
F = A \oplus B \oplus Cin \\
Cout = A \cdot B + A \cdot Cin + B \cdot Cin
$$


<div style="display:flex; gap:3em; justify-content:center;">
<div style="text-align:center;">
  <img src="photos/3.1.1 全加器逻辑符号.png" width="180"/>
  <div><strong>8 位全加器逻辑图</strong></div>
</div>
<div style="text-align:center;">
  <img src="photos/3.1.1 全加器逻辑电路.png" width="240"/>
  <div><strong>全加器逻辑电路</strong></div>
</div>
</div>

#### 2. 串行加法器
<mark>串行进位加法器采用串行逐级传递进位，电路延迟与位数成正比关系。</mark>

<div style="display:flex; gap:5em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.1.2 逻辑图.png" width="300"/>
    <div><strong>8 位全加器逻辑图</strong></div>
  </div>
  <div style="text-align:center;">
    <img src="photos/3.1.2 串行加法器.png" width="300"/>
    <div><strong>串行加法器</strong></div>
  </div>
</div>

>在此，我们需要引入一个概念：门延迟

<mark>假定与/或门延迟为1ty，异或门3ty</mark>

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.1.2 与门.jpg" width="330"/>
  </div>
  <div style="text-align:center;">
    <img src="photos/3.1.2 或门.jpg" width="300"/>
  </div>
  <div style="text-align:center;">
    <img src="photos/3.1.2 异或门.jpg" width="330"/>
  </div>
</div>

即是说 `Sum`延迟为`6ty`；`Carryout`延迟为`2ty`。
假设有`n`个串行加法器，总的进位门延迟为 `2n` 级的门延迟
总的和延迟为 `2n + 1` 级门延迟

但事实上，我们可以通过优化使得进位独立进行并同时生成

#### 3. 并行进位加法器(CLA 全先行进位加法器)
对于一个四位的加法器，其进位`c1,c2,c3,c4`的产生条件如下：
$$
\begin{align*}
C_1 &= X_1Y_1 + (X_1 + Y_1)C_0 \\
C_2 &= X_2Y_2 + (X_2 + Y_2)C_1 \\
    &= X_2Y_2 + (X_2 + Y_2)X_1Y_1 + (X_2 + Y_2)(X_1 + Y_1)C_0 \\
C_3 &= X_3Y_3 + (X_3 + Y_3)C_2 \\
    &= X_3Y_3 + (X_3 + Y_3)[X_2Y_2 + (X_2 + Y_2)X_1Y_1 + (X_2 + Y_2)(X_1 + Y_1)C_0] \\
    &= X_3Y_3 + (X_3 + Y_3)X_2Y_2 + (X_3 + Y_3)(X_2 + Y_2)X_1Y_1 + (X_3 + Y_3)(X_2 + Y_2)(X_1 + Y_1)C_0 \\
C_4 &= X_4Y_4 + (X_4 + Y_4)C_3 \\
    &= X_4Y_4 + (X_4 + Y_4)[X_3Y_3 + (X_3 + Y_3)X_2Y_2 + (X_3 + Y_3)(X_2 + Y_2)X_1Y_1 + (X_3 + Y_3)(X_2 + Y_2)(X_1 + Y_1)C_0] \\
    &= X_4Y_4 + (X_4 + Y_4)X_3Y_3 + (X_4 + Y_4)(X_3 + Y_3)X_2Y_2 + (X_4 + Y_4)(X_3 + Y_3)(X_2 + Y_2)X_1Y_1 + (X_4 + Y_4)(X_3 + Y_3)(X_2 + Y_2)(X_1 + Y_1)C_0
\end{align*}
$$ 

因此可以定义两个辅助函数：

$$
\begin{align*}
\left.
\begin{aligned}
P_i &= X_i + Y_i \\
G_i &= X_iY_i
\end{aligned}
\right\}
\end{align*}
$$ 

这里面`Pi`可以看作是进位传递函数，代表当`Xi,Yi`有一个为1时，若低位有进位传递则一定会被传递到高位
`Gi`称为进位生成函数，若`Xi,Yi`均为1，则一定会生成一个向高位的进位

$$
\begin{align*}
\left.
\begin{aligned}
C_1 &= G_1 + P_1C_0 \\
C_2 &= G_2 + P_2G_1 + P_2P_1C_0 \\
C_3 &= G_3 + P_3G_2 + P_3P_2G_1 + P_3P_2P_1C_0 \\
C_4 &= G_4 + P_4G_3 + P_4P_3G_2 + P_4P_3P_2G_1 + P_4P_3P_2P_1C_0
\end{aligned}
\right\}
\end{align*}
$$ 
可以看出，每一位上的进位只与原始输入的进位`C0`以及每一位的输入有关，即是说，可以同步地运算出每一位的进位。

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.1.3 4位CLU.png" width="300"/>
    <div><strong>4位CLU</strong></div>      
  </div>
  <div style="text-align:center;">
    <img src="photos/3.1.3 4位CLA.png" width="370"/>
    <div><strong>4位CLA</strong></div>      
  </div>
</div>

CLU: carry lookahead unit 先行进位部件(实现上述逻辑表达即可)
CLA: carry lookahead addder 全先行进位加法器

**门延迟**
从`Xi,Yi`到`Pi,Gi`需要1级门延迟，生成所有的进位需要2级门延迟，所以在进位上的门延迟就是3级门延迟。生成`sum`需要三级门延迟，按照运算过程相加就是6级门延迟
无论对于多少位的CLA，门延迟理论上都相同。

那么，代价是什么呢？
可以观察到，生成`Ci`位进位需要连接`i + 1`个端口。这需要在硬件上和功耗上做出牺牲。
所以，一般采用分组的办法，采用组内并行，组间串行的方式(一般4位一组)，或者组内组间都并行。

**局部（单级）先行进位加法器**
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.1.3 局部先行进位加法器.png" width="500"/>
    <div><strong>局部先行进位加法器</strong></div>      
  </div>
</div>

关键路径: $(A_{7-0}、B_{7-0}、C_0) → C_8→ C_{16} → C_{24} →(R_{31-24})$
所有和数产生的延迟为`3 + 2 + 2 + 5 = 12ty` （当`Pi=Xi+Yi` ）

**多级先行进位加法器**
组内并行，组间并行的方式
假设一个四位的加法器：


$$
\begin{aligned}
C_1 &= G_0 + P_0C_0 \\
C_2 &= G_1 + P_1C_1 = G_1 + P_1G_0 + P_1P_0C_0 \\
C_3 &= G_2 + P_2C_2 = G_2 + P_2G_1 + P_2P_1G_0 + P_2P_1P_0C_0 \\
C_4 &= G_3 + P_3C_3 = G_3 + P_3G_2 + P_3P_2G_1 + P_3P_2P_1G_0 + P_3P_2P_1P_0C_0 \\
G_3^* &= G_3 + P_3G_2 + P_3P_2G_1 + P_3P_2P_1G_0 \\
P_3^* &= P_3P_2P_1P_0
\end{aligned}
$$ 
所以，可得：
$$
C_4 = G_3^* + P_3^*C_0
$$
把实现上述逻辑的电路称为4位BCLU(Block CLU)
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.1.3 多级先行进位加法器.png" width="400"/>
    <div><strong>多级先行进位加法器</strong></div>      
  </div>
</div>

下见实例：
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.1.3 异或门优化.jpg" width="300"/>
    <div><strong>异或门优化</strong></div>      
  </div>
</div>
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.1.3 8位加法器pro.jpg" width="800"/>
    <div><strong>8位加法器pro</strong></div>      
  </div>
  <div style="text-align:center;">
    <img src="photos/3.1.3 8位加法器pro1.jpg" width="900"/>
    <div><strong>8位加法器pro</strong></div>      
  </div>
</div>

在这个例子中，采用了`4 + 4`的方法，实现了一个低延迟的8位加法器，主要优化了异或门（和部分），假设异或门的延迟为3，目前方法的延迟为2

#### 4. 进位选择加法器

#### 5. n位带标志加法器
  
n位加法器无法用于两个n位带符号整数（补码）相加，无法判断是否溢出

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.1.5 带标志加法器符号.png" width="500"/>     
  </div>
  <div style="text-align:center;">
    <img src="photos/3.1.5 带标志加法器的逻辑电路.png" width="800"/>    
  </div>
</div>

名词解释：
1. $OF$(Overflow Flag, 溢出标志): $OF = C_n\oplus C_{n-1}$
2. $SF$(Sign Flag, 符号标志): 指示运算结果的符号。在有符号数的运算中，如果结果的最高位（符号位）为1，则SF为1，表示结果为负 $SF = F_{n - 1}$
3. $ZF$(Zero Flag， 零标志)：，指示运算结果是否为零。如果结果为零，ZF为1
4. $CF$(Carry Flag，进位/结尾标志)：$CF = C_{out} \oplus C_{in}$

#### 6.算数逻辑部件(ALU)
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.1.6 ALU符号.png" width="200"/>     
  </div>
  <div style="text-align:center;">
    <img src="photos/3.1.6 ALU结构.png" width="400"/>    
    <div><strong>ALU结构（举例）</strong></div>  
  </div>
</div>

`ALUop`的位数决定了操作个数的上限
TIPS: `MUX` 多路选择器

### 二、定点数运算

#### 1. 定点数加减运算
##### 1. 补码加减运算
``` CPP
int x=9, y=-6, z1, z2;
z1=x+y;
z2=x-y; 
```
在实际程序运行中，`x`,`y`的机器码均为二者的补码
根据补码的定义，$[X]_补 = 2^n + X (-2^n \leq X < 2^n)$
所以，`Z1`的机器码$[X+Y]_补 = [X]_补 + [Y]_补$
`Z2`的机器码$[X-Y]_补 = [X]_补 - [Y]_补 = [X]_补 + [-Y]_补$

<mark> $[-Y]_补 = \overline{[Y]_补} + 1 $ </mark>
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.2.1.1 整数加减运算部件.png" width="600"/>     
  </div>
</div>

>当Sub为1时，做减法
当Sub为0时，做加法

可以通过标志信息来区区分符号整数运算结果和无符号整数运算结果
1. $ZF$: 无论有无符号都有意义 $ZF = 1$即表示 $F$ 为0
2. $SF$：指示正负；对于无符号数运算，没有意义
3. $CF$：表示无符号数加减运算时的进错位。加法时，$CF = 1$代表无符号数加法溢出；减法时则代表有借位，不够减。对于带符号整数运算没有意义。
4. $OF$：表示带符号整数运算时发生了溢出，对于无符号整数运算没有意义

<mark>$CF$ 和 $OF$ 的生成</mark>

1. $CF$ : 其生成与最高位进位 $CarryOut$ 有关。当加法时，$CarryOut = 1$ 代表有额外的进位，此时 $CF$ 和 $CarryOut$ 同号。减法时，代表 $a + (~b) + 1$ 溢出， 刚好代表了 $a \geqslant b$，所以，减法时$CF$ 和 $CarryOut$ 异号。 $CF = C_{out} \oplus C_{in}$
  
``` cpp
//减法有借位
  0x3 - 0x7          3 - 7
  0011b
- 0111b
硬件实际做：0011b + 1001b (7 的 4 位补码)
        1 1100b      ← 最高位产生进位 1
CF = 1（3<7，必须借位）

//减法无借位
  0xA - 0x6          10 - 6
  1010b
- 0110b
硬件实际做：1010b + 1010b (6 的 4 位补码)
        1 0100b      ← 最高位产生进位 1
但 CPU 对减法规定：CF = ~carry_from_msb
此处 carry_from_msb=1，故 CF=0（10≥6，没有借位）

//加法有进位
  0x9 + 0x8          9 + 8
  1001b
+ 1000b
---------
1 0001b              ← 5 位结果，最高位进位 1
CF = 1（无符号 9+8=17 ≥16，超出 4 位）

//加法无进位
  0x5 + 0x6          5 + 6
  0101b
+ 0110b
---------
  1011b              ← 4 位即可容纳
CF = 0（结果 11 <16）

```
2.  $OF$ : $OF = C_n\oplus C_{n-1}$
``` cpp
//两个正数加法溢出（负数）
  5 + 4 = 9
  0101
+ 0100
-------
  1001        ; 结果 −7，错了！

进位链：  C3=0  C2=1
OF = 0 ⊕ 1 = 1   → 溢出

//两个负数加法溢出（正数）  

  (−5) + (−4) = −9
  1011
+ 1100
-------
1 0111        ; 低 4 位 0111 = +7，错了！

进位链：  C3=1  C2=0
OF = 1 ⊕ 0 = 1   → 溢出

//两个正数加法无溢出

  3 + 2 = 5
  0011
+ 0010
-------
  0101

进位链：  C3=0  C2=0
OF = 0 ⊕ 0 = 0   → 无溢出


//两个负数加法无溢出
  (−3) + 5 = 2
  1101
+ 0101
-------
1 0010

进位链：  C3=1  C2=1
OF = 1 ⊕ 1 = 0   → 无溢出
```
例子：
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.2.1.1 整数加法.png" width="390"/>
    <div><strong>整数加法</strong></div>      
  </div>
  <div style="text-align:center;">
    <img src="photos/3.2.1.1 整数减法.png" width="400"/>    
    <div><strong>整数减法</strong></div>  
  </div>
</div>

---

##### 2. 原码加减运算
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.2.1.2 原码加减运算1.png" width="390"/>
    <div><strong>原码加减运算</strong></div>      
  </div>
  <div style="text-align:center;">
    <img src="photos/3.2.1.2 原码加减运算2.png" width="400"/>    
    <div><strong>原码加减运算</strong></div>  
  </div>
</div>

##### 3. 移码加减运算
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.2.1.3 移码加减运算1.png" width="390"/>
    <div><strong>移码加减运算</strong></div>      
  </div>
  <div style="text-align:center;">
    <img src="photos/3.2.1.3 移码加减运算2.png" width="400"/>    
    <div><strong>移码加减运算</strong></div>  
  </div>
</div>

##### 4. 总结
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.2.1.4 例子.png" width="500"/>      
  </div>
  <div style="text-align:center;">
    <img src="photos/3.1.5 带标志加法器的逻辑电路.png" width="600"/>    
  </div>
</div>

1. $OF$(Overflow Flag, 溢出标志): $OF = C_n\oplus C_{n-1}$ 。表示带符号整数运算时发生了溢出，对于无符号整数运算没有意义
2. $SF$(Sign Flag, 符号标志): 指示运算结果的符号。在有符号数的运算中，如果结果的最高位（符号位）为1，则SF为1，表示结果为负 $SF = F_{n - 1}$，对于无符号数运算，没有意义
3. $CF$(Carry Flag，进位/结尾标志)：$CF = C_{out} \oplus C_{in}$  表示无符号数加减运算时的进错位。加法时，$CF = 1$代表无符号数加法溢出；减法时则代表有借位，不够减。对于带符号整数运算没有意义。

- SIGctr = 1：当 `SIGctr` 为 1 时，`less` 的值由 `OF`（溢出标志）和 `SF`（符号标志）的异或结果决定。这种情况通常用于有符号数的比较。
- SIGctr = 0：当 `SIGctr` 为 0 时，`less` 的值由 `SUBctr` 和 `CF`（进位标志）的异或结果决定。这种情况通常用于无符号数的比较。
---

``` markdown
实例 1：有符号数比较（SIGctr = 1）

假设我们有两个 4 位有符号数：

- `A = 0101`（+5）
- `B = 0010`（+2）

执行 `A - B` 操作：


  0101
- 0010
------
  0011


结果：`0011`（+3）

- SF（符号标志）：结果为 0011，最高位为 0，表示正数，所以 `SF = 0`。
- OF（溢出标志）：两个正数相减，结果仍为正数，没有溢出，所以 `OF = 0`。
- less：`OF ⊕ SF = 0 ⊕ 0 = 0`，表示 `A` 不小于 `B`。

---

实例 2：有符号数比较（SIGctr = 1）

假设我们有两个 4 位有符号数：

- `A = 1001`（-7）
- `B = 0100`（+4）

执行 `A - B` 操作：


  1001    1001
- 0100  + 1100 
------  ------
  0101  1 0101


结果：`0101`（+5）

- SF（符号标志）：结果为 0101，最高位为 0，表示正数，所以 `SF = 0`。
- OF（溢出标志）：一个负数减去一个正数，结果为正数，发生了溢出，所以 `OF = 1`。
- less：`OF ⊕ SF = 1 ⊕ 0 = 1`，表示 `A` 小于 `B`。

---

实例 3：无符号数比较（SIGctr = 0）

假设我们有两个 4 位无符号数：

- `A = 0101`（5）
- `B = 0010`（2）

执行 `A - B` 操作：


  0101
- 0010
------
  0011


结果：`0011`（3）

- CF（进位标志）：没有借位，所以 `CF = 0`。
- SUBctr：假设 `SUBctr` 为 0（具体值取决于系统实现）。
- less：`SUBctr ⊕ CF = 0 ⊕ 0 = 0`，表示 `A` 不小于 `B`。

---

实例 4：无符号数比较（SIGctr = 0）

假设我们有两个 4 位无符号数：

- `A = 0010`（2）
- `B = 0101`（5）

执行 `A - B` 操作：


  0010
- 0101
------
  1101


结果：`1101`（13）

- CF（进位标志）：发生了借位，所以 `CF = 1`。
- SUBctr：假设 `SUBctr` 为 0。
- less：`SUBctr ⊕ CF = 0 ⊕ 1 = 1`，表示 `A` 小于 `B`。

---

通过以上实例，我们可以看到：

- 有符号数比较：`less` 的生成依赖于 `OF` 和 `SF` 的异或结果，用于判断两个有符号数的大小关系。
- 无符号数比较：`less` 的生成依赖于 `SUBctr` 和 `CF` 的异或结果，用于判断两个无符号数的大小关系。
```


---

#### 2. 定点数乘除运算
##### 0. 乘法lead in
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.2.2.0 无符号整数乘法.png" width="500"/>      
  </div>
  <div style="text-align:center;">
    <img src="photos/3.2.2.0 无符号整数乘法1.png" width="500">    
  </div>
</div>

tips: 左移对应 `*2` 移`n`位加`2n`次即可

上述思想可写成如下数学推导过程：

$$
\begin{aligned}
X \times Y &= X \times (0.y_1 y_2 \ldots y_n) \\
&= X y_1 2^{-1} + X y_2 2^{-2} + \ldots + X y_{n-1} 2^{-(n-1)} + X y_n 2^{-n} \\
&= 2^{-n} X y_n + 2^{-(n-1)} X y_{n-1} + \ldots + 2^{-2} X y_2 + 2^{-1} X y_1 \\
&= 2^{-1}\Bigl(2^{-1}\bigl(2^{-1}\ldots 2^{-1}(2^{-1}(0 + X y_n) + X y_{n-1}) + \ldots + X y_2\bigr) + X y_1\Bigr) \\
&\quad\quad\quad\quad\quad\quad\quad n\text{个 }2^{-1}
\end{aligned}
$$

上述推导过程具有明显的递归性质，因此无符号数乘法可归结为循环计算下列算式：

设  
$$
\boxed{P_0 = 0} 
$$

每步乘积  
$$
\begin{aligned}
P_1 &= 2^{-1}(P_0 + X y_n) \\
P_2 &= 2^{-1}(P_1 + X y_{n-1}) \\
&\;\;\vdots \\
P_n &= 2^{-1}(P_{n-1} + X y_1)
\end{aligned}
$$

递推公式  
$$
\boxed{P_{i+1} = 2^{-1}\bigl(P_i + X y_{n-i}\bigr) \quad (i = 0,1,2,\ldots,n-1)}
$$

最终乘积  
$$
\boxed{P_n = X \times Y}
$$

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.2.2.0 32位乘法器.png" width="500"/>      
  </div>
</div>

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.2.2.0 乘法演示.png" width="500"/>      
  </div>
</div>

```markdown
### 无符号整数乘法运算过程详解

#### 1. 初始化
- **部分积** P = `0000`
- **进位** C = `0`
- **乘数** R = `1101`（y 的二进制）
- **被乘数** x = `1110`（14）

#### 2. 迭代步骤（共 4 步，对应乘数 4 位）

**第 1 步**  
- R 最低位为 1，执行 P = P + x  
  → P = `0000` + `1110` = `1110`  
- 拼接 C、P、R 得 `011101101`，逻辑右移 1 位  
  → C = `0`，P = `0111`，R = `0110`

**第 2 步**  
- R 最低位为 0，不加 x  
  → P 保持 `0111`  
- 拼接得 `001110110`，逻辑右移 1 位  
  → C = `0`，P = `0011`，R = `1011`

**第 3 步**  
- R 最低位为 1，执行 P = P + x  
  → P = `0011` + `1110` = `(1)0001`（产生进位）  
- 拼接得 `100011011`，逻辑右移 1 位  
  → C = `0`，P = `1000`，R = `1101`

**第 4 步**  
- R 最低位为 1，执行 P = P + x  
  → P = `1000` + `1110` = `(1)0110`（产生进位）  
- 拼接得 `101101101`，逻辑右移 1 位  
  → C = `0`，P = `1011`，R = `0110`

#### 3. 最终结果
- **双倍字长结果**：`10001110`（182）
- **低 4 位**：`0110`（6）
- **高 4 位**：`1011`（11）

#### 4. 验证
- x = 14，y = 13
- x * y = 182
- 二进制：`10001110`

#### 5. 溢出说明
- 若只保留 4 位，结果为 `0110`（6），与真实结果 182 不符。
- 高 4 位 `1011` 不为全 0，说明结果超出 4 位表示范围，发生溢出。
```

--- 

##### 1. 原码乘法运算
**原码一位乘法**
- 用于浮点数尾数乘运算
- 符号与数值分开处理：积符异或得到，数值用无符号乘法运算
具体见上

**原码两位乘法**
原来的一位乘法速度较慢，事实上如果对乘数的每两位取值情况进行判断，使每步求出对应于该两位的部分积，则可将速度提高一倍。
具体数学的推导如下：

$$
\begin{aligned}
Y_{i-1}Y_i &= 00, P_{i+1} = 2^{-2}(P_i + 0) \\
Y_{i-1}Y_i &= 01, P_{i+1} = 2^{-2}(P_i + X) \\
Y_{i-1}Y_i &= 10, P_{i+1} = 2^{-2}(P_i + 2X) \\
Y_{i-1}Y_i &= 11, P_{i+1} = 2^{-2}(P_i + 3X)
\end{aligned}
$$
特别的，对于`+3X`的情况，可以用`4X - X`代替。故在本次运算中只执行一次`-X`，`+4X`延迟到下一次运行
可用一个触发器`T`记录是否需要下次执行`+X`

$$
\boxed{Y_{i-1}Y_i = 11, P_{i+1} = 2^{-2}(P_i + 3X) = 2^{-2}(P_i - X) + X }
$$

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.2.2.1 原码两位乘法操作表.png" width="500"/>      
  </div>
</div>

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.2.2.1 2位乘法过程.png" width="500"/>      
    <div><strong>注意为什么要模8哦</strong></div>
  </div>
</div>

eg.
```markdown
# 原码两位乘法演算示例（6 位数值，3 位符号）

## 已知
- [X]原 = 0.111001  
- [Y]原 = 0.100111  
- 数值部分：6 位  
- 采用 **3 位符号位** 的模 8 补码，防止双位右移后符号出错  

预计算（均为 **无符号数值**）：
- |X|  = 111001₂  
- 2|X| = 1110010₂ → 取低 6 位 110010₂，再补 3 位符号 → **001 110010**  
- [−|X|]补（模 8） = **111 000111**  

---

## 寄存器格式
| 寄存器 | 位数 | 用途 |
|--------|------|------|
| P      | 9 位 | 3 符号 + 6 数值，部分积 |
| Y      | 6 位 | 剩余乘数 |
| T      | 1 位 | 辅助位，初始 0 |

---

## 初始

P = 000 000000   (9 位)
Y = 100111
T = 0

---

## 第 1 步  查看位 y₅y₄T = 1 0 0
规则 100 → **加 2|X|**  

        000 000000   (P)
      + 001 110010   (2|X|)
      -------------
        001 110010

右移 **2 位**（算术右移，符号扩展）：

P = 000 011100
Y = 101001
T = 0

---

## 第 2 步  查看位 y₃y₂T = 1 0 1
规则 101 → **加 [−|X|]补**  

        000 011100
      + 111 000111   ([−|X|]补)
      -------------
      1 000 100011   (丢弃溢出位)
        000 100011   (模 8 补码结果)

右移 2 位：


P = 000 001000
Y = 111010
T = 1

---

## 第 3 步  查看位 y₁y₀T = 0 1 1
规则 011 → **加 2|X|**  

        000 001000
      + 001 110010
      -------------
        001 111010

右移 2 位：

P = 000 011101
Y = 101110
T = 0

---

## 结束
- 高 6 位数值：011101（来自 P 的低 6 位）  
- 低 6 位数值：101110（来自 Y）  
- 合并得 12 位数值：**011101 101110**  

符号：0 ⊕ 0 = 0  
最终结果：

[X × Y]原 = 0.011101101110

```

---

##### 2. Booth's 算法
将符号位和数值为合在一起参加运算，直接得出用补码表示的乘积，将正数和负数同等对待

设：$ [x]_{\text{补}}, [y]_{\text{补}}$ 都是偶数位定点整数， $ [x]_{\text{补}} = X_{n-1} \cdots X_1 X_0, [y]_{\text{补}} = Y_{n-1} \cdots Y_1 Y_0 $，根据补码定义，可得到真值 \( y \) 的计算公式如下：

>$$
\begin{aligned}
y &= -Y_{n-1} 2^{n-1} + \sum_{i=0}^{n-2} Y_i 2^i \\
&= -Y_{n-1} 2^{n-1} + Y_{n-2} 2^{n-2} + \cdots + Y_1 2^1 + Y_0 2^0 \\
&= -Y_{n-1} 2^{n-1} + Y_{n-2} 2^{n-1} - Y_{n-2} 2^{n-2} + \cdots + Y_1 2^2 - Y_1 2^1 + Y_0 2^1 - Y_0 2^0 \\
&= (Y_{n-2} - Y_{n-1}) 2^{n-1} + (Y_{n-3} - Y_{n-2}) 2^{n-2} + \cdots + (Y_0 - Y_1) 2^1 + (0 - Y_0) 2^0 \\
&= \sum_{i=0}^{n-1} (Y_{i-1} - Y_i) 2^i
\end{aligned}
>$$

这里假设 \( Y_{-1} = 0 \)。因此，

$$
[x \times y]_{\text{补}} = \left[ x \times \sum_{i=0}^{n-1} (Y_i - Y_{i+1}) 2^i \right]_{\text{补}} 
$$

不考虑小数点位置：
$$
\left[ x \times \sum_{i=0}^{n-1} (Y_i - Y_{i+1}) 2^{-(n - i)} \right]_{\text{补}} 
$$

展开后，得:
$$
[P_{i + 1}]_补 = [2^{-1}(P_i + (Y_{i - 1} - Y_i) \times x)]_补 \tag{i = 0, 1, 2, ..., n - 1}
$$

根据这个式子，可知，在求出 $[P_i]_补$ 后，只需要知道 $Y_{i - 1}, Y_i$ 就可以求出 $[P_{i + 1}]_补$

>$$\begin{aligned}
Y_iY_{i - 1} &= 01, [P_{i + 1}]_补 = [2^{-1}(P_i + x)]_补\\
Y_iY_{i - 1} &= 10, [P_{i + 1}]_补 = [2^{-1}(P_i - x)]_补\\
Y_iY_{i - 1} &= 11, [P_{i + 1}]_补 = [2^{-1}(P_i + 0)]_补\\
Y_iY_{i - 1} &= 00, [P_{i + 1}]_补 = [2^{-1}(P_i + 0)]_补
\end{aligned}
>$$

在处理连续的`1`或`0`时，因为直接跳过了，所以很快
eg.
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.2.2.2 布斯算法举例.png" width="500"/>      
    <div><strong>注意没有符号位</strong></div>
  </div>
</div>

---

##### 3. 补码乘法运算
**补码一位乘法**
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.2.2.3 补码乘法运算1.png" width="500"/>      
  </div>
  <div style="text-align:center;">
    <img src="photos/3.2.2.3 补码乘法运算2.png  " width="500"/>      
  </div>  
</div>

直接用布斯算法就好了

**补码两位乘法** 改进布斯算法(MBA)
字长总是是8得倍数
$$
\begin{aligned}
[P_{i+1}]_{\text{补}} &= 2^{-1} \left( [P_i]_{\text{补}} + (y_{i-1} - y_i) [X]_{\text{补}} \right) \\
[P_{i+2}]_{\text{补}} &= 2^{-1} \left( [P_{i+1}]_{\text{补}} + (y_i - y_{i+1}) [X]_{\text{补}} \right) \\
&= 2^{-1} \left( 2^{-1} \left( [P_i]_{\text{补}} + (y_{i-1} - y_i) [X]_{\text{补}} \right) + (y_i - y_{i+1}) [X]_{\text{补}} \right) \\
&= 2^{-2} \left( [P_i]_{\text{补}} + (y_{i-1} + y_i - 2y_{i+1}) [X]_{\text{补}} \right)
\end{aligned}
$$ 

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.2.2.3 补码两位乘法.png" width="300"/>      
  </div>  
</div>

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.2.2.3 补码两位乘法举例.png" width="500"/>      
  </div>  
</div>


##### 4. 快速乘法器
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.2.2.4 流水线式.png" width="400"/>      
  </div>  
  <div style="text-align:center;">
    <img src="photos/3.2.2.4 阵列乘法器.png" width="420"/>      
  </div>  
</div>

##### 5. 除法lead in

手算除法的基本要点
- 被除数与除数相减，够减则上商为1；不够减则上商为0。
-  每次得到的差为中间余数，将除数右移后与上次的中间余数比较。用中间余数减除数，够减则上商为1；不够减则上商为0。
- 重复执行第②步，直到求得的商的位数足够为止。

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.2.2.5 定点除法运算.png" width="400"/>      
  </div>
  <div style="text-align:center;">
    <img src="photos/3.2.2.5 无符号数除法算法的硬件实现.png" width="400"/>      
  </div>  
</div>

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.2.2.5 带符号除法.png" width="400"/>      
  </div>
</div>
两个n位，即为单精度除法，被除数为n位，即为双精度

##### 6. 原码恢复余数除法
假定被除数  $X$ 为  $2n$ 位，除数  $Y$ 和商  $Q$ 都为  $n$ 位， $X$、 $Y$ 和  $Q$ 分别表示为： $X = X_{2n-1}X_{2n-2}\cdots X_nX_{n-1}\cdots X_0$， $Y = Y_{n-1}Y_{n-2}\cdots Y_0$， $Q = Q_{n-1}Q_{n-2}\cdots Q_0$，则恢复余数除法的算法步骤如下。

**第1步**， $R_1 = X - Y$，若  $R_1 < 0$，则上商  $Q_n = 0$，同时恢复余数，即  $R_1 = R_1 + Y$；若  $R_1 \geq 0$，则上商  $Q_n = 1$。这里求得的商  $Q_n$ 是商的第  $n$ 位数值。显然，若  $Q_n = 1$，则商将会有  $n+1$ 位数。这对于以下不同的情况，意味着不同的结果:

- 对于无符号整数除法来说，如果被除数为  $2n$ 位，则商有可能会超出  $n$ 位无符号整数范围，所以，若  $Q_n = 1$，则发生溢出。
- 对于原码定点小数除法来说，若  $Q_n = 1$，则相除结果的数值从小数部分溢出到了整数部分，按道理两个定点小数相除，结果也应是定点小数，故应当作溢出处理；但浮点数尾数溢出时，可通过右规来消除，最终只要阶码不溢出，结果仍然正确。所以，这种情况下，保留最高位的商  $Q_n = 1$，继续执行下去。

**第2步**，若已求得第  $i$ 位的中间余数为  $R_i$，则第  $i+1$ 位的中间余数为  $R_{i+1} = 2R_i - Y$。若  $R_{i+1} < 0$，则上商  $Q_{n-i-1} = 0$，同时恢复余数，即  $R_{i+1} = R_{i+1} + Y$；若  $R_{i+1} \geq 0$，则上商  $Q_{n-i-1} = 1$。

**第3步**，循环执行第2步  $n$ 次，直到求出所有  $n$ 位商  $Q_{n-1}\cdots Q_0$ 为止。最终商在  $Q$ 寄存器中，余数在  $R$ 寄存器中。

例: 已知  $[x]_{\text{原}} = 0.1011$， $[y]_{\text{原}} = 1.1101$，用恢复余数法计算  $[x/y]$。

解：分符号位和数值位两部分进行。

商的符号位： $0 \oplus 1 = 1$。
商的数值位采用恢复余数法。减法操作用补码加法实现，是否够减通过由中间余数的符号来判断，所以中间余数要加一位符号位。因此，最先计算出  $[x]_{\text{补}} = 0.1011$， $[y]_{\text{补}} = 1.1011$， $[-y]_{\text{补}} = 1.0101$
因为是原码定点小数，所以在低位扩展0，$[x]_{\text{补}} [y]_{\text{补}}$ 以 $X, Y$ 代替
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.2.2.6 恢复余数除法.jpg" width="400"/>      
  </div>
  <div style="text-align:center;">
    <img src="photos/3.2.2.6 恢复余数除法1.png" width="500"/>      
  </div>
</div>

商的最高位为0，说明没有溢出，商的数值部分为1101。所以，
 $ [x/y]_{\text{原}} = 1.1101 $ （最高位为符号位），余数为$0.0111×2^{-4}$。

##### 7. 原码不恢复余数除法

在恢复余数除法运算中，当中间余数与除数相减结果为负时，要多做一次$+Y$操作，因而降低了算法执行速度，又使控制线路变得复杂。在计算机中很少采用恢复余数除法，而普遍采用不恢复余数除法。其实现原理如下。首先, 第$i$次余数为$R_i=2R_{i-1}-Y$。根据下次中间余数的计算方法，有以下两种不同情况：

- 若$R_i ≥ 0$，则上商1，不需恢复余数，直接左移一位后试商，得下次余数$R_{i+1}$，即$R_{i+1} = 2R_i - Y$；
- 若$R_i < 0$，则上商0，且需恢复余数后左移一位再试商，得下次余数$R_{i+1}$，即$R_{i+1} = 2(R_i + Y) - Y = 2R_i + Y$。

当第i次中间余数为负时，可以跳过恢复余数这一步，直接求第i+1次中间余数。这种算法称为不恢复余数法。从上述推导可以发现，不恢复余数法的算法要点就是6个字：“正、1、减、负、0、加”。其含义就是：若中间余数为正数，则上商为1，下次做减法；若中间余数为负数，则上商为0，下次做加法。这样运算中每次循环内的步骤都是规整的，差别仅在做加法还是减法，所以，这种方法也称为“加减交替法”。采用这种方法有一点要注意，即如果在最后一步上商为0，则必须恢复余数，把试商时减掉的除数加回去。

例 已知
 $ [x]_{\text{原}} = 0.1011 $ ，$ [y]_{\text{原}} = 1.1101 $ ，用不恢复余数法计算$ [x/y]_{\text{原}} $ 

解：分符号位和数值位两部分进行。

商的符号位：$0 \oplus 1 = 1$。

商的数值位采用不恢复余数法。减法操作用补码加法实现，是否够减通过中间余数的符号来判断，所以中间余数要加一位符号位。先计算出 $ X = [x]_{\text{补}} = 0.1011 $ ，$ Y = [y]_{\text{补}} = 1.0101 $ ，$ -Y = [-y]_{\text{补}} = 1.0011 $

运算过程如下：
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.2.2.7 不恢复余数除法.jpg" width="400"/>      
  </div>
  <div style="text-align:center;">
    <img src="photos/3.2.2.7 不恢复余数除法1.png" width="400"/>      
  </div>
</div>

商的最高位是0，说明没有溢出，商的数值部分为 $1101$ ,所以 $[x/y]_原 = 1.1101$, 余数为 $0.0111 \times 2^{-4}$

##### 8. 溢出
!!! : 这里都是定点小数，第一位商1就会让本来的符号位变成整数1，这显然是不希望发生的：
- 5 位字长：1 位符号 + 4 位小数  
- 数值范围：−(1−2^(−4)) … +(1−2^(−4)) = −0.9375 … +0.9375  
- 所有位权：
  符号位：−1
  后 4 位：2^(−1)、2^(−2)、2^(−3)、2^(−4)

给定
x = 0 1111  → +0.9375
y = 1 1101  → −0.8125  
符号异或：0 ⊕ 1 = 1 → 结果负。
只需算 |x| / |y| = 0.9375 / 0.8125 = 1.1538…
显然 ≥1，已超出小数允许范围 → 必定溢出。

---
A = 0.1111 0000
B = 0.1101 0000
−B 的 4 位补码 = 1.0011

---
一、恢复余数法（定点小数版）
R = 0.0000 0000
Q = 0000          （4 位小数位）

迭代	动作	R（高 4 位）	Q	备注	
1.	初始	0000	0000		
2.	左移	0001	0000		
	R−B	0001+10011=0110 (正)	0001	商 1	
3.	左移	1100	0010		
	R−B	1100+10011=0101 (正)	0011	商 1	
4.	左移	1010	0110		
	R−B	1010+10011=0011 (正)	0111	商 1	
5.	左移	0110	1110		
	R−B	0110+10011=1111 (负)	1110	恢复：+B → 0110	

最终 4 位小数商 = 0.1110 (0.875)

加上符号：结果 = 1.1110 (= −0.875)

---

溢出判定
真实商 1.1538… 的整数位为 1，但机器只允许小数位 <1；
在第四步 商寄存器最高位向符号位产生进位 1，却无处存放 →
硬件溢出标志 OF = 1（小数上溢）。
符号：1
小数位：1110
机器输出：1.1110（−0.875），同时 <mark>触发溢出指示</mark>。

##### 9. 补码除法运算lead in
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.2.2.9 补码除法1.png" width="400"/>      
  </div>
  <div style="text-align:center;">
    <img src="photos/3.2.2.9 补码除法2.png" width="400"/>      
  </div>
</div>

---

##### 10. 补码恢复余数除法
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.2.2.10 补码恢复余数除法1.png" width="400"/>      
  </div>
  <div style="text-align:center;">
    <img src="photos/3.2.2.10 补码恢复余数除法2.png" width="400"/>      
  </div>
</div>

---

##### 11. 补码不恢复余数除法
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.2.2.11 补码不恢复余数除法1.png" width="400"/>      
  </div>
  <div style="text-align:center;">
    <img src="photos/3.2.2.11 补码不恢复余数除法2.png" width="400"/>      
  </div>
</div>


### 三、整数运算
#### 1. 乘除运算溢出处理
假定两个n位无符号整数 $x_u$ 和 $y_u$ 对应的机器数为 $X_u$ 和 $Y_u$，$ p_u = x_u \times y_u $ ，$p_u$ 为n位无符号整数且对应的机器数为 $P_u$ ；
两个n位带符号整数 $x_s$ 和 $y_s$ 对应的机器数为 $X_s$ 和 $Y_s$ ，$p_s=x_s \times y_s，p_s$ 为n位带符号整数且对应的机器数为 $P_s$。
 
若 $X_u=X_s$ 且 $Y_u=Y_s$ ，则 $P_u=P_s$。
由此，可以可用无符号乘来实现带符号乘，但高n位无法得到，故不能判断溢出。
$X*Y$ 的高n位可以用来判断溢出，规则如下：
- 无符号：若高n位全0，则不溢出，否则溢出
- 带符号：若高n位全0或全1且等于低n位的最高位，则不溢出。

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.3.1 溢出处理.png" width="600"/>      
  </div>
</div>

1. 溢出的定义
- 无符号溢出：结果超过了 `n` 位无符号整数能表示的最大值（`2^n - 1`），高位被丢弃。
- 有符号溢出：结果超过了 `n` 位有符号整数能表示的范围（`-2^(n-1)` 到 `2^(n-1)-1`），符号位错误或数值错误。

2. 乘法位数
- 两个 `n` 位数相乘，最多需要 `2n` 位 才能完整保存结果。
- 但在实际计算机中，乘法结果通常截断为 `n` 位（例如两个 4 位相乘，结果只保留低 4 位），这可能导致溢出。

| 乘法类型 | 运算        | 真实结果 | 是否溢出 | 原因                             |
|----------|-------------|----------|----------|----------------------------------|
| 无符号   | 6 × 10      | 60       | ✅       | 结果 > 15，保留低4位后失真       |
| 有符号   | 6 × -6      | -36      | ✅       | 结果 < -8，保留低4位后失真       |
| 无符号   | 8 × 2       | 16       | ✅       | 结果 > 15，保留低4位后为0        |
| 有符号   | -8 × 2      | -16      | ✅       | 结果 < -8，保留低4位后为0        |
| 无符号   | 13 × 14     | 182      | ✅       | 结果 > 15，保留低4位后为6        |
| 有符号   | -3 × -2     | 6        | ❌       | 结果在 [-8, 7] 范围内            |
| 无符号   | 2 × 12      | 24       | ✅       | 结果 > 15，保留低4位后为8        |
| 有符号   | 2 × -4      | -8       | ❌       | 结果在 [-8, 7] 范围内            |

##### 1. 无符号整数乘的溢出判断
对于 `n` 位无符号整数 `x` 和 `y` 的乘法运算，若取 `2n` 位乘积中的低 `n` 位为结果，则相当于取模` 2^n`。若丢弃的高 `n` 位乘积为非 `0`，则发生溢出。例如, `0110` 与 `1010` 相乘得到的 `8` 位乘积为 `0011 1100`，高 `4` 位为非 `0`，因而发生了溢出；说明低 `4` 位 `1100` 不是正确的乘积。

无符号整数乘运算可用如下公式表示，式中 `p` 是指取低 `n` 位乘积时对应的值。
$$
p = \begin{cases}
(x \times y) \mod 2^n, & (x \times y <  2^n) 正常 \\
x \times y,             & (x \times y \geqslant溢出
\end{cases}
$$

如果无符号数乘法指令能够将高 `n` 位保存到一个寄存器，则编译器可以根据该寄存器的内容采用相应的比较指令来进行溢出判断。例如，在 `MIPS` 架构中，无符号数乘法指令 `multu` 会将两个 `32` 位无符号数相乘得到的 `64` 位乘积置于两个 `32` 位内部寄存器 `Hi` 和 `Lo` 中，编译器可以根据 `Hi` 寄存器是否为全 `0` 来进行溢出判断。在 `RISC-V` 架构中，无符号整数相乘得到的高 `n` 位乘积可用乘法指令 `mulhu` 得到；编译器根据该指令得到的结果是否为 `0`，来判断 `mul` 指令的执行结果是否发生无符号整数乘溢出。

##### 2. 带符号整数乘的溢出判断
补码乘法器实现带符号整数运算时，得到的结果是 `2n` 位乘积的补码表示。例如， `x = 6，y = -6`，得到乘积的 `2n` 位补码表示为 `1101 1100`。

对于带符号整数相乘，可以通过乘积的高 `n` 位和低 `n` 位之间的关系进行溢出判断。判断规则是：若高 `n` 位中每一位都与低 `n` 位的最高位相同，则不溢出；否则溢出。例如，`x = -8，y = 2`，得到 `8` 位乘积为 `1111 0000`，高 `4` 位全 `1`，与低 `4` 位的最高位不同，因而发生了溢出，说明低 `4` 位 `0000` 不是正确的乘积。对于序号为 `6` 的情况，`x = -3，y = -2`，得到 `8` 位乘积为 `0000 0110`，高 `4` 位全 `0`，与低 `4` 位的最高位相同，因而没有发生溢出，说明低 `4` 位 `0110` 是正确的乘积。

如果带符号整数乘法指令能够将高 `n` 位保存到一个寄存器中，则编译器可以根据该寄存器的内容与低 n 位的关系进行溢出判断。例如，在 `MIPS` 架构中，带符号整数乘法指令 `mult` 会将两个 `32` 位带符号整数相乘，得到的 `64` 位乘积置于两个 `32` 位内部寄存器 `Hi` 和 `Lo` 中，因此，编译器可以根据 `Hi` 寄存器中的每一位是否等于 `Lo` 寄存器中的第一位来进行溢出判断。在 `RISC-V` 架构中，带符号整数相乘得到的高 `n` 位乘积可用专门的指令 `mulh` 得到，编译器根据该指令得到的结果中的每一位是否等于 `mul` 指令得到的结果中的第一位，来判断是否发生带符号整数乘溢出。

有些指令系统中乘法指令并不保留高 `n` 位，也不生成溢出标志 `OF`，此时，编译器就无法进行溢出判断，甚至有些编译器根本不会考虑溢出判断处理。这种情况下，程序可能在发生溢出的情况下得到错误的结果。例如，在 `C` 程序中，若 `x` 和 `y` 为 `int` 型，`x = 65535`，机器数为 `0000 FFFFH`，则 `y = x × x = -131071`，`y` 的机器数为 `FFFE 0001H`，因而出现 `x² < 0` 的奇怪结论。

如果要保证程序不会因编译器没有处理溢出而发生错误，那么，程序员就需要在程序中加入进行溢出判断的语句。无论是带符号整数还是无符号整数，都可根据两个乘数 `x、y` 与结果 `p = x × y` 的关系来判断是否溢出。判断规则为：若满足 `x ≠ 0` 且 `p / x = y`，则没有发生溢出；否则溢出。

例如，`x = 2，y = 12，p = 8`，显然 `8 / 2 ≠ 12`，因此，发生了溢出。`x = 2，y = -4，p = -8`，显然 `2 ≠ 0` 且 `-8 / 2 = -4`，因此，没有发生溢出。

##### 3. 整数除法的溢出判断
对于整数除法，只有当 `-2147483648 / -1` 时会发生溢出，其他情况下，因为商的绝对值不可能比被除数的绝对值更大，因而肯定不会发生溢出。但是，在不能整除时需要进行舍入，通常按照朝 `0` 方向舍入，即正数商取比自身小的最接近整数，负数商取比自身大的最接近整数。除数不能为 `0`，否则根据 `C` 语言标准，其结果是未定义的。

#### 2. 常量的乘除运算
由于运算部件硬件的限制，乘法比移位和加法慢得多，而除法又比乘法慢得多，所以在处理变量和常数之间的乘除运算时，常常用移位和加减组合运算代替乘除运算。
>如 $x \times 20 = (x << 4) + (x << 2)$
无论带不带符号，即使乘积溢出，利用这种组合方式计算的结果和直接相乘的结果是一样的。

而对于除法，就比较特殊了：
在处理一个变量和2的幂次形式的整数相除时，常用右移实现。无符号整数用逻辑右移`高位补零，低位移出`，带符号整数用算数右移`高位补符号，低位移出`。整数相除得到的结果为整数，不能整除，<mark>朝0舍入</mark> 如 `7 / 3 = 2; - 7 / 3 = - 2`

- 对于无符号整数，移位后得到的商只可能变小不会变大，所以无论是否整除，与直接相除得到的商完全一样
- 对于带符号整数，符号为 0 时与无符号整数相同，符号为 1 时则需区分：
  - 若低位移出的全是 0 ，则能够整除，移位后得到的商和直接相除得到的商完全一样。
  - 若低位移出的不是全 0 ，则代表不能整除。移出的非 0 数相当于把商中小数点后面的值舍去。一个补码表示的负数舍去小数部分的值后变得更小，转换为真值后会得到更小的负数商，舍入的方向是朝 $ - \infty $ 方向舍入。
- 如何校正？ 对于带符号整数除运算 $x / 2 ^ k$ , 若 $x < 0$ 则在右移之前先将 $x$ 加上偏移量 $2^k - 1$ ， 然后再右移 $k$ 位 
  
eg1.
> -3 / 2
> 1101(-3) + 0001(1) = 1110(-2)
> 1110 >> 1 = 1111(-1)

eg2.
已知 32 位变量 $x$ 的机器数为 `8000 0005H` ，回答以下问题：
1. $x$ 类型为 `unsigned int` 时， $x / 2$ 和 $x >> 1$ 的值？ $2 \times x $和 $x << 1$ 的值？ $2 \times x $和 $x << 1$ 的结果是否溢出？
2. $x$ 类型为 `int` 时， $x / 2$ 和 $x >> 1$ 的值？ 如何用右移操作实现 $x/2$？ $2 \times x $和 $x << 1$ 的值？ $2 \times x $和 $x << 1$ 的结果是否溢出？

> 1. 真值 1000 0000 0000 0000 0000 0000 0000 0101B = $2^{31} + 5$
> $x / 2$ = $(2^{31} + 5)/2(mod 2^{32}) = 2^{30} + 2$
> $x >> 1 =$ 01000 0000 0000 0000 0000 0000 0000 010B $= 2^{30} + 2$
> $2 \times x = (2^{31} + 5)\times 2(mod 2^{32}) = 10$ 溢出
> $x << 1 =$ 0000 0000 0000 0000 0000 0000 0000 1010B $= 10$ 无符号整数左移时移出的是非 0 ，溢出
> 
> 2. 真值 - 0111 1111 1111 1111 1111 1111 1111 1011B = $-(2^{31} - 5)$
> $x / 2$ = $- (2^{31} - 5)/2(mod 2^{32}) = -2^{30} + 3$
> $x >> 1 = $ 1100 0000 0000 0000 0000 0000 0000 0010B 
> 真值 -011 1111 1111 1111 1111 1111 1111 1110B = $-(2^{30} - 1 - 1) = -2^{30} + 2$
> 纠偏 (1000 0000 0000 0000 0000 0000 0000 0101 + 1) >> 1 = 1100 0000 0000 0000 0000 0000 0000 0011B = $-(2^{30} - 1 - 2) = -2^{30} + 3$
> $2 \times x = -(2^{31} - 5)\times 2(mod 2^{32}) = 10$ 溢出
> $x << 1 =$ 0000 0000 0000 0000 0000 0000 0000 1010B $= 10$ 带符号整数移位后符号发生变化，溢出

### 四、 浮点数运算
#### 1. 浮点数加减运算
对于浮点数的运算，需要考虑 对阶、尾数相减、规格化、舍入和溢出判断五个步骤：
> 设 两个规格化浮点数 $x = M_x \times 2^{E_x}, y = M_y \times 2^{E_y}$, 设 $E_x \leqslant E_y$, 则有
> $x + y = (M_x \times 2^{E_x -E_y} + M_y) \times 2^{E_y}$ 
> $x - y = (M_x \times 2^{E_x -E_y} - M_y) \times 2^{E_y}$ 

##### 1. 对阶
对阶的目的是使 \( x \) 和 \( y \) 的阶码相等，以使尾数可以相加减。
对阶的原则是：
> - 小阶向大阶看齐，阶小的那个数的尾数右移，右移的位数等于两个阶的差的绝对值。
> - 大多数机器采用 IEEE 754 标准来表示浮点数，因此，对阶时需要进行移码减法运算，并且尾数右移时按照原码小数方式右移，符号位不参加移位，数值位要将隐含的一位 1 右移到小数部分，空出位补 0。为了保证运算的精度，尾数右移时，低位移出的位不要丢掉，应保留并参加尾数部分的运算。

可以通过计算两个阶的差的补码来判断两个阶的大小。对于 IEEE 754 单精度格式来说，其计算公式如下：
> $$
> \begin{aligned}
> [E_x - E_y]_{\text{补}} &= 256 + E_x - E_y = 256 + 127 + E_x - (127 + E_y) \\
> &= 256 + [E_x]_{\text{移}} - [E_y]_{\text{移}} \\
> &= [E_x]_移 + [-[E_y]_移]_{\text{补}}  (mod \quad  256 )
> \end{aligned}
> $$

假设有两个浮点数 \( x \) 和 \( y \)，其 IEEE 754 单精度表示如下：

- \( x \) 的阶码（移码）为 \([E_x]{\text{移}} = 01111010_2 = 122_{10}\)
- \( y \) 的阶码（移码）为 \([E_y]{\text{移}} = 01111100_2 = 124_{10}\)

我们需要对这两个数进行对阶，使它们的阶码相等，以便进行尾数的加减运算。

**步骤 1：计算阶码的差值**

首先，我们需要计算两个阶码的差值，以确定哪个数的阶码更小，需要右移。
\[
[E_x - E_y]_{\text{补}} = [E_x]_{\text{移}} + [-[E_y]_{\text{移}}]_{\text{补}} \mod 256
\]

我们需要计算 \([-[E_y]_{\text{移}}]_{\text{补}}\)。首先，求 \([E_y]_{\text{移}}\) 的相反数的补码：

- \([E_y]_{\text{移}} = 124_{10} = 01111100_2\)
- \(-[E_y]_{\text{移}} = -124_{10}\)
- \([- [E_y]_{\text{移}}]_{\text{补}} = 10000100_2 = 132_{10}\)

现在，计算 \([E_x - E_y]_{\text{补}}\)：

\[
[E_x - E_y]_{\text{补}} = [E_x]_{\text{移}} + [-[E_y]_{\text{移}}]_{\text{补}} = 122 + 132 = 254 \mod 256 = 254_{10}
\]

将 \(254_{10}\) 转换为二进制：`11111110`

**步骤 2：判断阶码的大小**

根据计算出的 \([E_x - E_y]{\text{补}} = 11111110_2\)：

- 最高位（符号位）为 `1`，表示 \(E_x < E_y\)。
- 其余位表示差值的绝对值。这里，\(|E_x - E_y| = 254 - 256 = -2\)（因为用补码表示，所以 \(254_{10}\) 表示 \(-2_{10}\)）。

因此，\(E_x\) 比 \(E_y\) 小 2，需要将 \(x\) 的尾数右移 2 位。

**步骤 3：对阶操作**

由于 \(E_x < E_y\)，根据对阶原则，小阶向大阶看齐，因此：

- 保持 \(y\) 的阶码不变，\(E_y = 124_{10}\)。
- 将 \(x\) 的阶码调整为 \(124_{10}\)，即 \(E_x' = E_y = 124_{10}\)。
- 将 \(x\) 的尾数右移 \(|E_x - E_y| = 2\) 位。

假设 \(x\) 的尾数（包括隐含的最高位 1）为 `1.10110000000000000000000`（23 位小数部分），右移 2 位后变为：

`0.01101100000000000000000`<mark>（右移 2 位，空出的位补 0）</mark>

##### 2. 尾数加减
对阶后两个浮点数的阶码相等，此时，可以进行对阶后的尾数相加减。
因为 IEEE 754 采用定点原码小数表示尾数，所以，尾数加减实际上是定点原码小数的加减运算。
因为 IEEE 754 浮点数尾数中有一个隐藏位，所以，在进行尾数加减时，必须把隐藏位还原到尾数部分。此外，对阶过程中在尾数右移时保留的附加位也要参加尾数加减运算。

##### 3. 尾数规格化
对于 IEEE754 规格下的浮点数运算，会有以下两种结果
$$
\begin{aligned}
1.bb\dots b + 1.bb\dots b &= \pm 1b.bb\dots b \\
1.bb\dots b - 1.bb\dots b &= \pm 0.00\dots 01b\dots b
\end{aligned}
$$
对于第一种情况，需要进行右规：尾数右移一位，阶码加一（最后一位移出时需要考虑舍入）
对于第二种情况，需要进行左规：数值位逐次左移，阶码逐次减一直到第一位1移到小数点左边

##### 4. 尾数的舍入处理
在对阶和尾数右规时，一般将低位移出的位保留下来并参与中间过程的运算，最后再进行舍入

##### 5. 溢出判断
- 右规前先判断阶码是否全为1，若是则不右规，直接置结果为指数上溢；否则，阶码加一，然后判断阶码是否全为1来确定是否指数上溢
- 左规前先判断阶码是否全为0，若是则不左规，直接置结果为指数下溢，否则，阶码减一，然后判断阶码是否全为0来确定是否指数下溢

##### 6. 逻辑结构
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.4.1.6 浮点数加减运算部件的逻辑结构.png" width="800"/>      
  </div>
</div>

主要部件有一个大 ALU 和二个小 ALU，分别执行尾数加减和指数相减。每一步动作都由控制逻辑进行控制。

第一步，由控制逻辑控制小 ALU 实现指数相减的操作，得到阶差被送到控制逻辑。

第二步，由控制逻辑根据阶差的符号和绝对值来确定如何进行对阶。控制信号①确定结果的指数是 $E_x$，还是 $E_y$，控制信号②和③确定是对$M_x$，还是对$M_y$进行右移，控制信号④确定右移多少位。

第三步，由控制逻辑控制用对阶后的尾数在大 ALU 中进行加减，运算结果被送到控制逻辑，用于产生用于规格化的控制信号。

第四步，根据大ALU运算结果进行规格化。控制信号⑤和⑥确定是对大 ALU 的运算结果进行规格化还是对舍入结果进行规格化，控制信号⑦确定尾数是左移还是右移，控制信号⑧确定阶码是增加还是减少。规格化后的结果被送到含人部件和控制逻辑。


第五步，由控制信号⑨规格化后的结果进行舍入，并将其含人部件的结果再次送到控制逻辑，以确定含人后是否还是规格化形式。若不是，则需继续进行一次规格化。

从上述执行过程来看，浮点运算可以用流水线形式进行。目前 CPU 中的浮点运算大多采用流水线执行方式。只要将图 3.16 所示的逻辑结构稍作调整就可以实现流水线方式的浮点运算。

由于浮点加减运算中需要对阶并最终进行含入，因而可能导致“大数吃小数”的问题，使得浮点数运算不能满足加法结合律。
eg.
> 设 $x, y$ 均为单精度浮点数， $x = -1.5 \times 10^{30}, y = 1.5 \times 10^{30}, z = 1.0$
> $(x+y)+z = (-1.5 \times 10^{30}  + 1.5 \times 10^{30}) + 1.0 = 1.0$
> $x+(y+z) = -1.5 \times 10^{30}  + (1.5 \times 10^{30} + 1.0) = 0.0$

##### 7. 实例
$x,y$均为 $float$ 类型变量，$x = 10.5, y = - 120.625$ 给出 $x+y$ 的计算过程
$x = 10.5 = 1010.1B = 1.0101B \times 2^3$ `0 1000 0010 010 1000 0000 0000 0000 0000`
$y = -120.625 = -111 1000.101B = -1.11100010B \times 2^6 $ `1 1000 0101 111 0001 0100 0000 0000 0000`

1. 对阶：$[E_x]_移 = $ 1000 0010, $[E_y]_移 = $ 1000 0101. 
$[E_x - E_y]_补 = [E_x]_移 + [-[E_y]_移]_补 =$ `1000 0010 + 0111 1011` $=$ `1111 1101`
$[E_x - E_y]_补 = -11B = -3$
所以对 $x$ 的尾数右移3位，对阶后，$x$ 的阶码 `1000 0101` 尾数为 `0. 001 0 1010 0000 0000 0000 0000 00`其中从左到右第一个1为隐藏位，最后面的三个0为保留的附加位.
2. 尾数相加：
    $$
    \begin{aligned}
        &0.0010\  1010\  0000\  0000\  0000\  000 \ 0\  00 \\
       - &1.1110\  0010\  1000\  0000\  0000\  000 \\
        =  &1.1011\  1000\  1000\  0000\  0000\  000 \  0\  00
    \end{aligned}
    $$
3. 尾数规格化：结果已规格化
4. 舍入： 对于此案例 舍去最后三个0 
$x + y = -1.1011\  1000\  1 B\times 2^6 = -11011\  10.001B = -110.125$



#### 2. 浮点运算的精度和舍入
**Q1 保留多少附加位才能保证运算的精度？**
IEEE 754 规定，浮点数运算的中间结果右边必须至少保留 `2` 位附加位
- 附加的第一位：保护位（guard）
- 附加的第二位：舍入位（round）
- 附加的第三位（可选）：粘位（sticky）舍入位的右边有任何非0数字，sticky置为1，否则置为0。

**Q2 最终如何对保留的附加位进行舍入？**
1. 就近舍入到偶数
这是 IEEE 754 标准采用的默认舍入方式。当结果是两个可表示数的非中间值时，实际上是“0 舍 1 入”方式；当结果正好在两个可表示数中间时，根据“就近舍入”的原则**无法操作**。此时结果强迫为偶数。

> 使用粘位可以减少运算结果正好在两个可表示数中间的情况。举一个十进制的例子。假设计算 \(1.24 \times 10^4 + 5.03 \times 10^1\)**（假定科学记数法的精度保留两位小数）**
> **若只使用保护位和舍入位而不使用粘位**，即仅保留两位附加位，则结果为 \(1.2400 \times 10^4 + 0.0050 \times 10^4 = 1.2450 \times 10^4\)。这个结果位于两个相邻可表示数 \(1.24 \times 10^4\) 和 \(1.25 \times 10^4\) 的中间，采用就近舍入到偶数时，结果为 \(1.24 \times 10^4\)；
> **若同时使用保护位、舍入位和粘位**，则结果为 \(1.24000 \times 10^4 + 0.00503 \times 10^4 = 1.24503 \times 10^4\)。这个结果就不在 \(1.24 \times 10^4\) 和 \(1.25 \times 10^4\) 的中间，而更接近于 \(1.25 \times 10^4\)，采用就近舍入方式，结果为 \(1.25 \times 10^4\)。显然，后者更精确。

2. 朝+∞方向舍入
总是取数轴上右边的最近可表示数，也称为正向舍入或朝上舍入。

3. 朝−∞方向舍入
总是取数轴上左边的最近可表示数，也称为负向舍入或朝下舍入。

4. 朝 0 方向舍入
直接截取所需位数，丢弃后面所有位，也称为截断、截断或恒舍法。这种舍入处理最简单。对正数或负数来说，都是取数轴上更靠近原点的那个可表示数，是一种趋向原点的舍入，因此，又称为趋向 0 舍入。

eg. 保留三位小数
|原始数字|2.052 40| 2.052 50| 2.052 60| -2.053 40| -2.053 50| -2.053 60|
| --- | --- | --- | --- | --- | --- | --- |
|**就近舍入到偶数**| 2.052| 2.052| 2.053| -2.053| -2.054| -2.054|
|**朝+∞方向舍入**| 2.053| 2.053| 2.053| -2.053| -2.053| -2.053|
|**朝−∞方向舍入**| 2.052| 2.052| 2.052| -2.054| -2.054| -2.054|
|**朝 0 方向舍入**| 2.052| 2.052| 2.052| -2.053| -2.053| -2.053|

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.4.2 密度.jpg" width="700"/>      
  </div>
</div>

#### 3. 浮点数乘除运算
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos/3.4.3 浮点数乘除法.png" width="700"/>      
  </div>
</div>


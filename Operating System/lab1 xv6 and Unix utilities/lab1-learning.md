[TOC]

# 1.1 进程和内存
## a. Sleep
!!! : 调用内核函数
``` c
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char const *argv[])
{
  printf("sleep: start\n");
  
  // 1. 检查参数数量：argv[0]是"sleep"，argv[1]是数字
  if (argc != 2) { //参数错误
    fprintf(2, "usage: sleep <time>\n");
    exit(1);
  }

  printf("sleep: sleeping for %d ticks\n", atoi(argv[1]));

  sleep(atoi(argv[1]));

  printf("sleep: woke up\n");

  exit(0);
}
```

如果想每隔一秒打印一次
``` c
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char const *argv[])
{
  if (argc != 2) {
    fprintf(2, "usage: sleep <total_ticks>\n");
    exit(1);
  }

  int total_ticks = atoi(argv[1]);
  int interval = 10; // 假设 10 ticks 为 1 秒
  int elapsed = 0;

  printf("CharlesOS: Start sleeping (Total: %d ticks)\n", total_ticks);

  // 核心循环逻辑
  while (elapsed < total_ticks) {
    // 计算本次应该睡多久（防止最后一次超出总时长）
    int remaining = total_ticks - elapsed;
    int sleep_now = (remaining < interval) ? remaining : interval;

    sleep(sleep_now);
    elapsed += sleep_now;

    printf("CharlesOS: Process [%d/%d] second elapsed...\n", elapsed / 10, total_ticks / 10);
  }

  printf("CharlesOS: Woke up! Task finished.\n");
  exit(0);
}
```

---
---

## b. PIDtest and fork()
!!! : 进程间控制 fork wait sleep
```c
#include "kernel/types.h"
#include "user/user.h"


int main(int argc, char const *argv[]) {
    int pid = fork();
    if (pid > 0) {
        sleep(5); //
        printf("parent: child = %d\n", pid);
        pid = wait((int *) 0); // 等待子进程结束，回收资源
        printf("parent: child %d is done\n", pid);
    } else if (pid == 0) {
        //sleep(20);
        printf("child: pid = %d\n", getpid());
        exit(0);
    } else {
        printf("fork failed\n");
    }
    exit(0);
}
```

**当父进程调用 wait 时，内核会执行以下逻辑：**

- 扫描进程表：内核会查看所有进程，寻找那些“父进程 PID”等于当前进程 PID 的子进程。

- 检查状态：
    - 如果没有子进程：wait 会立刻**返回 -1**（表示报错，你根本没孩子，等谁呢？）。

    - 如果有子进程且已经结束（ZOMBIE 状态）：内核会把这个“僵尸”的遗物（退出状态、PID）交给父进程，然后彻底销毁这个子进程，释放它的进程号和资源。**wait 返回该子进程的 PID**。

    - 如果有子进程但都在运行：**父进程会进入 SLEEPING 状态。内核会把它挂起，直到它的某个孩子调用了 exit，内核才会叫醒父进程。**

```c
int main(int argc, char const *argv[]) {
    //int pid = fork();
    int pid = 5;
    if (pid > 0) {
        sleep(5);
        printf("parent: child = %d\n", pid);
        pid = wait((int *) 0); // 等待子进程结束，回收资源
        printf("parent: child %d is done\n", pid);
    } else if (pid == 0) {
        //sleep(20);
        printf("child: pid = %d\n", getpid());
        exit(0);
    } else {
        printf("fork failed\n");
    }
    exit(0);
}
```
可以看到，这个代码下的输出就不是一开始我们所希望的了，因为根本就没有子进程
```bash
$ pidtest
parent: child = 5
parent: child -1 is done
```

尽管最初子进程与父进程有着相同的内存内容，但是二者在运行中拥有不同的内存空间和寄存器：在一个进程中改变变量不会影响到另一个进程。例如当wait的返回值存入父进程的变量pid中时，并不会影响子进程中的pid，子进程中pid仍然为0。


实际上，当 `int pid = fork()` 时，父进程会自动创建一个子进程，从这一行的下一行开始运行，父进程和子进程会同时执行后续的代码。 **父进程的`pid`在程序运行开始时会被赋值为子进程的PID，而子进程的`pid`会被赋值为0。** 因此，父进程和子进程会根据`pid`的值来执行不同的代码路径。

但是，在`fork`后，两个进程会同时执行后续的代码，这可能会导致输出的顺序不确定。父进程可能先打印它的消息，也可能是子进程先打印它的消息，这取决于操作系统如何调度这两个进程。`sleep`一下就可以解决这个问题。

``` c
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char const *argv[]) {
    // 记录 main 程序刚开始运行时的原始 PID
    int root_pid = getpid();
    printf("--- CharlesOS: Process Tree Test Start (Root PID: %d) ---\n", root_pid);

    int fork_return_value = fork();

    if (fork_return_value > 0) {
        // 【父进程】执行区域
        sleep(5); 
        printf("\n[PARENT NODE]\n");
        printf("  - My Actual PID (getpid): %d\n", getpid());
        printf("  - Fork Return Value (Child's PID): %d\n", fork_return_value);
        
        int wait_pid = wait((int *) 0);
        printf("  - Wait() returned: %d (Successfully reaped child)\n", wait_pid);

    } else if (fork_return_value == 0) {
        // 【子进程】执行区域
        printf("\n[CHILD NODE]\n");
        printf("  - My Actual PID (getpid): %d\n", getpid());
        printf("  - Fork Return Value: %d\n", fork_return_value);
        printf("  - My Parent should be: %d\n", root_pid);
        
        exit(0);
    } else {
        printf("Fork failed!\n");
    }

    exit(0);
}
```

芝士运行结果
``` bash
$ pidtest
--- CharlesOS: Process Tree Test Start (Root PID: 3) ---

[CHILD NODE]
  - My Actual PID (getpid): 4
  - Fork Return Value: 0
  - My Parent should be: 3

[PARENT NODE]
  - My Actual PID (getpid): 3
  - Fork Return Value （Child's PID): 4
  - Wait() returned: 4 (Successfully reaped child)
```

---
---

## c. exec
### exec 是在干嘛？
如果说 fork 是克隆一个分身，那么 exec 就是让这个分身换上新戏服，并背诵新的台词。

进程没死，灵魂换了：进程的 PID（身份证）不变，但它的大脑（内存里的代码和数据）被完全抹除，换成了新的程序（比如 ls 或 sh）。

ELF 格式：这相当于一份“装修说明书”。exec 读取这份说明书，告诉操作系统：“请把磁盘上这个文件的第 X 块内存加载到内存地址 A，把数据加载到地址 B，然后把 CPU 的指针跳到入口点 C 开始运行”。

| 特征 | fork() | exec() |
| :--- | :--- | :--- |
| 比喻 | 克隆一个分身 | 换上新戏服，背诵新台词 |
| 内存变化 | 父子进程内存相同（复制） | 进程内存完全替换 |
| PID 变化 | 父子进程 PID 不同 | 进程 PID 不变 |
|程序运行 | 父子进程继续执行 fork 后的代码 | 进程从新程序的入口点开始执行 |

先来一个简单的例子：
```c
//testsleep.c
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    char *agrs[] = {"sleep", "50", 0};   
    exec("sleep", agrs);
    exit(0);
}
```
这里的`sleep`就是前面写过的那个程序，exec 会把当前进程的内存替换成 sleep 程序的内存，然后从 sleep 的入口点开始执行。也就是说，这个程序一运行就变成了 sleep 程序，sleep 程序会睡 50 个时钟节拍，然后退出。
**至于为什么 exec 的参数是一个字符串数组呢？** 这是因为 exec 需要传递给新程序一些参数（就像命令行参数一样）。这个字符串数组的第一个元素通常是程序的名字（虽然不强制），后面是程序需要的参数，最后以一个 NULL 指针结束。

你说exec里面想在控制台传参？可以的~
```c
int main(int argc, char *argv[]) {
    char *agrs[] = {"sleep", argv[1], 0};   
    exec("sleep", agrs);
    exit(0);
}
```
这是不是很像一个shell了？我们在命令行输入 `$ testsleep 30`，这个程序就会把 `argv[1]` 的值（也就是 "30"）传递给 sleep 程序，让它睡 30 个时钟节拍。


**然后再结合一下之前写的 pidtest 程序，看看 exec 和 fork 的配合使用：**

tips: echo 程序的功能就是把它接收到的参数在控制台打印出来
```bash
$ echo Hello CharlesOS
Hello CharlesOS
```
```c
// exectest.c
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int pid = fork();

    if (pid == 0) {
        // 子进程：此时它还是 main 函数的副本
        // 我们用 exec 把它变成 "echo" 命令
        char *args[] = {"echo", "Hello", "CharlesOS", 0};
        
        printf("Child: 即将变身为 echo 程序...\n");
        
        // exec 成功后，下面的 printf 永远不会被执行
        exec("echo", args);
            
        // 如果 exec 返回了，说明出错了
        printf("exec 失败了！\n");
        exit(1);
    } else {
        // 父进程：等子进程执行完
        wait((int *) 0);
        printf("Parent: 子进程已经运行完毕。\n");
    }
    exit(0);
}
```
运行结果：
```bash
$ exectest
Child: 即将变身为 echo 程序...
Hello CharlesOS damn~
Parent: 子进程已经运行完毕。
```

### 为什么 printf 没运行？
在运行exectest.c时，子进程原本正在读第 15 行。

执行 exec 前：子进程内存里装的是 exectest 的代码。

执行 exec 时：内核直接冲进子进程的内存，把 exectest 的代码全部擦除，像格式化硬盘一样。

执行 exec 后：内核把磁盘上 echo 的代码填进去。

重点来了： 此时，原本写着 printf("exec 失败了！\n"); 的那块内存地址，现在可能变成了 echo 程序里的一段无关指令或者干脆是空白。子进程已经不记得自己曾经是 exectest 了，它醒来后的第一反应是运行 echo 的第一行代码。

所以，只有当 exec 失败（比如找不到 echo 文件）时，内核才会放弃替换，让原来的程序继续往下走，这时你才会看到那句报错。

---

xv6的shell使用上述调用为用户运行程序。shell的主要结构很简单，请参见`main`(***user/sh.c:145***)。主循环使用`getcmd`函数从用户的输入中读取一行，然后调用`fork`创建一个shell进程的副本。父进程调用`wait`，子进程执行命令。例如：当用户向shell输入`echo hello`时，`runcmd`(***user/sh.c:58***) 将以`echo hello`为参数被调用来执行实际命令。对于“`echo hello`”，它将调用`exec`(***user/sh.c:78***)。如果`exec`成功，那么子进程将从`echo`而不是`runcmd`执行命令，在某刻`echo`会调用`exit`，这将导致父进程从`main`(***user/sh.c:78***)中的`wait`返回。

Xv6 隐式地分配大多数用户空间内存:`fork`分配父内存的子副本所需的内存，`exec`分配足够的内存来保存可执行文件。在运行时需要更多内存的进程(可能是`malloc`)可以调用 `sbrk(n)`将其数据内存增加n个字节; `sbrk`返回新内存的位置。

---
---
---


# 1.2 I/O和文件描述符
## a. 文件描述符

**Everything is a file.**

> 文件描述符是一个小整数(small integer)，表示进程可以读取或写入的由内核管理的对象。进程可以通过打开一个文件、目录、设备，或创建一个管道，或复制一个已存在的描述符来获得一个文件描述符。为了简单起见，我们通常将文件描述符所指的对象称为“文件”；**文件描述符接口将文件、管道和设备之间的差异抽象出来，使它们看起来都像字节流。我们将输入和输出称为 I/O**。
> 在内部，xv6内核使用文件描述符作为每个进程表的索引，这样每个进程都有一个从零开始的文件描述符的私有空间。**按照惯例，进程从文件描述符0读取（标准输入），将输出写入文件描述符1（标准输出），并将错误消息写入文件描述符2（标准错误）。** 正如我们将看到的，shell利用这个约定来实现I/O重定向和管道。shell确保它始终有三个打开的文件描述符（user/sh.c:151），这是控制台的默认文件描述符。

### 到底什么是文件描述符(File Descriptor, FD)？

简单来说，文件描述符就是一个**非负整数**（比如 0, 1, 2, 3...）。

你可以把它想象成一个 **“索引号”** 或 **“挂钩”**：
- **内核**手里有一张表（进程文件表），记录了当前进程打开的所有资源（文件、设备等）。
- **你（用户程序）** 不需要知道这个文件在硬盘的哪个扇区，也不需要知道显示器的驱动怎么写。
- 你只需要拿着这个**数字**（FD），跟内核说：“请往 `1` 号钩子挂着的东西里写个 'Hello'”。

```c
// redirex.c
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h" // 包含 O_CREATE, O_WRONLY 等标志位

int main(void) {
    int pid = fork();

    if (pid == 0) {
        // --- 子进程的“调包计” ---
        
        // 1. 关掉标准输出（原本指向屏幕的 1 号钩子）
        close(1); 

        // 2. 打开（或创建）一个文件
        // 内核会自动分配【最小的空闲 FD】，因为刚关了 1，所以现在 1 是空着的
        // 于是这个文件就占领了 1 号位置！
        open("output.txt", O_CREATE | O_WRONLY);

        // 3. 现在执行一个原本要打印到屏幕的程序
        char *args[] = {"echo", "Hello_CharlesOS_File!", 0};
        
        // echo 内部只会往 FD 1 写东西，它根本不知道 1 已经被换成了文件
        exec("echo", args);
        
        exit(1);
    } else {
        // 父进程等孩子干完坏事
        wait(0);
        printf("Parent: 子进程已完成重定向任务。\n");
        printf("Parent: 请在 CharlesOS 里输入 'cat output.txt' 查看结果！\n");
    }

    exit(0);
}
```
结果
```bash
$ redirex
Parent: 子进程已完成重定向任务。
Parent: 请在 CharlesOS 里输入 'cat output.txt' 查看结果！
$ cat output.txt 
Hello_CharlesOS_File!
```
**What  happened? We NEED 2 KNOW!**

这段代码的核心在于 **FD 表的动态分配规则**：
> **内核永远把当前最小的、没被占用的数字分配给新打开的文件。**
1. **初始状态**：子进程继承了父进程的 FD 表：`0(stdin)`、`1(stdout/屏幕)`、`2(stderr)`。
2. **`close(1)`**：此时 FD 表里的 `1` 号位空出来了。
3. **`open("output.txt", ...)`**：内核一看，哟，`0` 被占了，`1` 是空着的，太好了！于是 `output.txt` 拿到了 **FD 1**。
4. **`exec("echo", ...)`**：`echo` 程序启动。它只认死理：**“我的任务就是把参数往 FD 1 里面塞”**。

结果就是：`echo` 以为自己在往屏幕说话，其实所有文字都顺着 1 号钩子溜进了 `output.txt`。

<mark> **注意到，这似乎可以实现任意的 I/O 重定向了！** </mark> 
你可以把 `0` 号钩子重定向到一个文件，这样程序就会从文件里读数据；你也可以把 `2` 号钩子重定向到一个文件，这样错误信息就不会显示在屏幕上了。

比如说，在`clsoe(1)`之后
```bash
$ ls
...
...
output.txt 2 26 22 #类型，索引节点，大小
```

然而，在删掉这句后，其他程序原封不动
```bash
$ redirex
Hello_CharlesOS_File! #直接打印在屏幕上了
Parent: 子进程已完成重定向任务。
Parent: 请在 CharlesOS 里输入 'cat output.txt' 查看结果！

$ ls
...
...
output.txt 2 26 0 #注意到，大小变小了
```

当然，直接写入`txt`等文件而不依赖重定向也是可以
```c
// directwrite.c
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main() {
    // 1. 直接打开一个文件，它会拿到一个新 FD（比如 3）
    int fd = open("my_log.txt", O_CREATE | O_WRONLY);
    
    // 2. 往这个新 FD 里写东西
    write(fd, "Writing directly to file!\n", 26);
    
    // 3. 往 FD 1 写东西（依然在终端输出）
    printf("This still goes to the screen.\n");
    
    // 4. 记得关掉它
    close(fd);
    
    exit(0);
}
```
结果
```bash
$ directwrite
This still goes to the screen.
$ cat my_log.txt
Writing directly to file!
```

**Let's go further~**
注意到，`close(1)` 之后，就没有办法向屏幕输出了，该如何解决呢？

首先要说明`xv6`管理`FD`的机制，当`open(...,....)`被调用时，内核会扫描当前进程的`FD`表，找到第一个空闲的位置（也就是没有被占用的最小整数），然后把新打开的文件的相关信息（比如文件类型、位置等）记录在这个位置上，并返回这个位置的索引作为新的`FD`。

tips：启动时，`console`设备会被打开，并占用`FD 0`、`FD 1`和`FD 2`，分别对应stdin、stdout和stderr。

先说说方法一：
```c
// 假设前面把标准输出（FD 1）关掉了
//就是说现在 FD1 绑定在别的文件上了

close(1);
// 重新打开控制台设备，它会自动拿到最小的 FD 1
open("console", O_RDWR); 
printf("通过重新打开 console 文件，屏幕恢复了。\n");
```

方法二
`dup()` 备份
```c
// duptest.c
#include "kernel/types.h"
#include "user/user.h"

int main() {
    // 1. 备份：把原本指向屏幕的 1 号 FD 复制一份
    // 此时 tmp_fd 可能是 3，它也指向屏幕
    int tmp_fd = dup(1); 

    printf("屏幕：现在还能看到我。\n");

    // 2. 关掉标准输出
    close(1);
    printf("这行字永远不会出现在屏幕上，因为 1 被关了。\n");

    // 3. 恢复：把备份的 3 号钩子“克隆”回 1 号位置
    // dup2(old, new) 在高级系统里很常见，但在 xv6 里
    // 我们通常先确保 1 是空的，然后执行 dup(tmp_fd)
    dup(tmp_fd); 

    printf("屏幕：我又回来了！\n");

    // 4. 别忘了关掉备份的临时钩子
    close(tmp_fd);

    exit(0);
}
```

`dup` 系统调用的核心逻辑只有一句话：**让一个新的 FD 指向与旧 FD 相同的“文件资源”。**
当你调用 `new_fd = dup(old_fd)` 时：
- **内核动作**：在当前进程的 FD 表里，找一个**最小的空闲数字**。
- **关联关系**：把这个新数字指向 `old_fd` 对应的那个底层文件（或是控制台、管道）。
- **引用计数**：内核会把那个底层文件的“引用计数”加 1。这意味着，你必须把 `old_fd` 和 `new_fd` **都 `close` 掉**，这个文件才会真正关闭。

**偏移量是共享的！**
tips: As for fork, that's the same
这是 `dup` 最容易被忽略的特性：通过 `dup` 复制出来的两个 FD，**共享同一个文件偏移量指针**。

- 如果你在 `fd1` 里读了 10 个字节，`fd2` 的读取位置也会跟着往后跳 10 个字节。
- 这和重新 `open` 两次同一个文件是不一样的（两次 `open` 会有两个独立的偏移量，互相覆盖）。
```c
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main() {
    int fd1 = open("double_write.txt", O_CREATE | O_WRONLY);
    int fd2 = dup(fd1); // 复制钩子

    printf("fd1 是 %d, fd2 是 %d\n", fd1, fd2);

    write(fd1, "Hello from fd1\n", 15); 
    write(fd2, "Hello from fd2\n", 15);

    // 两个钩子共享同一个“文件偏移量”
    // 所以结果是两行字按顺序排好，而不是互相覆盖！

    close(fd1);
    close(fd2);
    exit(0);
}
```
所以这两个输出不会重叠

---

> read和write系统调用以字节为单位读取或写入已打开的以文件描述符命名的文件。read(fd，buf，n)从文件描述符fd读取最多n字节，将它们复制到buf，并返回读取的字节数，引用文件的每个文件描述符都有一个与之关联的偏移量。**`read`从当前文件偏移量开始读取数据，然后将该偏移量前进所读取的字节数**：（也就是说）后续读取将返回第一次读取返回的字节之后的字节。当没有更多的字节可读时，read返回0来表示文件的结束。

> 系统调用`write(fd，buf，n)`将buf中的n字节写入文件描述符，并返回写入的字节数。只有发生错误时才会写入小于n字节的数据。与读一样，`write`在当前文件偏移量处写入数据，然后将该偏移量向前推进写入的字节数：每个`write`从上一个偏移量停止的地方开始写入。

```c
// readwrite.c
#include "kernel/types.h"
#include "user/user.h"

int main() {
    char buf[512];
    int n;

    // 从 0 号 FD（标准输入/键盘）读取
    // 写入 1 号 FD（标准输出/屏幕）
    while((n = read(0, buf, sizeof(buf))) > 0) {
        // read(0, buf, sizeof(buf))    
        // 0：从标准输入读取
        // buf：把读到的数据放在这个缓冲区里
        // sizeof(buf)：告诉内核最多读多少字节（这里是 512） 告诉内核你准备好了一个 512 字节的空间来存放输入的数据，超过了这个长度，内核就不会往里写了，避免了缓冲区溢出的问题。
        // return n：实际读到的字节数，可能小于 sizeof(buf)，比如你输入了 "Hello\n"，它可能只读了 6 个字节（包括换行符）

        write(1, buf, n); //参数 n 告诉内核你想把刚才读到的 n 个字节写到标准输出（屏幕）上，而不是整个 512 字节的缓冲区。这样就不会输出多余的垃圾数据了。
    }

    exit(0);
}
// 这个程序会把你在键盘上输入的内容原封不动地输出到屏幕上，直到你按 Ctrl+D（EOF）结束输入。
```
这实际上是一个非常经典的“cat”程序的简化版本，功能就是把标准输入的数据直接复制到标准输出。
``` c
// cat.c
char buf[512];
int n;
for (;;) {
    n = read(0, buf, sizeof buf);
    if (n == 0)
        break;
    if (n < 0) {
        fprintf(2, "read error\n");
        exit(1);
    }
    if (write(1, buf, n) != n) { 
        //注意，这段判断语句需要运行时才能知道结果，因为它要比较 write 实际写入的字节数和 n 是否相等。
        //也就是说，write在返回输出的字节之前，已经把内容打印到屏幕上了
        fprintf(2, "write error\n");
        exit(1);
    }
}
```
---
> 代码片段中需要注意的重要一点是，`cat`不知道它是从文件、控制台还是管道读取。同样也不知道它是打印到控制台、文件还是其他什么地方。文件描述符的使用以及文件描述符0是输入而文件描述符1是输出的约定允许了`cat`的简单实现。

> `close`系统调用释放一个文件描述符，使其可以被未来使用的`open`、`pipe`或`dup`系统调用重用（见下文）。新分配的文件描述符总是当前进程中编号最小的未使用描述符。

**“如何让 `cat` 这种本来只知道往屏幕打字的小程序，乖乖去读一个文件”** 

我们把这段代码的逻辑拆解开，看看系统在背后经历了怎样的一场“瞒天过海”。

**代码动作流（发生了什么？）**

当执行 `cat < input.txt` 时，Shell 进程（父进程）决定不再自己读文件，而是启动一个子进程来干活。

1. **`fork()`**：复制出一个和 Shell 一模一样的子进程。此时，父子进程的“文件描述符表”完全一致，FD 0 都指向键盘。
2. **`close(0)`**：子进程发狠，直接把自己的 FD 0（键盘输入）钩子给剪断了。现在，FD 0 这个位置空出来了！
3. **`open("input.txt", O_RDONLY)`**：内核遵守规则：**“分配当前进程中编号最小的可用 FD”**。因为 0 号位刚才被剪断了，所以 `input.txt` 顺理成章地占领了 0 号位。
4. **`exec("cat", argv)`**：子进程变身成 `cat` 程序。

**为什么 `cat` 根本不知道发生了什么？**

这是最精彩的地方：**`cat` 的代码逻辑是死的。**

- `cat` 程序启动时，它只会按照自己的剧本去执行 `read(0, ...)`。
- 它以为自己还在读键盘（因为它看的是 FD 0）。
- 但由于子进程在 `exec` 之前偷偷调包了 FD 0，`cat` 实际上读到的是 `input.txt` 的内容。

**这就实现了“接口的统一性”：** `cat` 不用为了处理文件而写一套逻辑，也不用为了处理键盘写一套逻辑，它只需要跟 FD 0 对话，至于 FD 0 背后到底是谁，那是 Shell 和内核之间的“地下交易”。

**为什么父进程没受影响？（核心特性）**

这是 Unix 设计中防止“系统崩溃”的关键：

- **文件描述符表是进程私有的**：在 `fork` 之后，父子进程有了各自的表。
- 当子进程调用 `close(0)` 和 `open(...)` 时，它**只修改了自己那张表**。
- 父进程的 FD 0 依然稳稳地指向键盘（标准输入）。

所以，当子进程 `cat` 运行结束后，父进程 Shell 依然可以继续从键盘读取你输入的下一条命令，而不会因为子进程的操作而失去对键盘的访问。

**总结：Shell 的逻辑模型**

Shell 的本质就是一个 **“重定向管理器”**：

1. **识别符号**：看到 `<`，就知道要改 FD 0；看到 `>`，就知道要改 FD 1。
2. **原地克隆**：通过 `fork` 建立一个子环境。
3. **偷偷改表**：通过 `close` + `open` 改掉子环境的 FD 指向。
4. **丢弃身份**：通过 `exec` 把 `cat` 强行塞进这个环境。

--- 

> 文件描述符和`fork`相互作用，使I/O重定向更容易实现。`fork`复制父进程的文件描述符表及其内存，以便子级以与父级在开始时拥有完全相同的打开文件。系统调用`exec`替换了调用进程的内存，但保留其文件表。此行为允许shell通过`fork`实现I/O重定向，在子进程中重新打开选定的文件描述符，然后调用`exec`来运行新程序。下面是shell运行命令`cat < input.txt`的代码的简化版本。

```c
char* argv[2];
argv[0] = "cat";
argv[1] = 0;
if (fork() == 0) {
    close(0);
    open("input.txt", O_RDONLY);
    exec("cat", argv);
}
```
在子进程关闭文件描述符0之后，`open`保证使用新打开的 ***input.txt***：0的文件描述符作为最小的可用文件描述符。`cat`然后执行文件描述符0(标准输入)，但引用的是 ***input.txt***。父进程的文件描述符不会被这个序列改变，因为它只修改子进程的描述符。

Xv6shell中的I/O重定向代码就是这样工作的(***user/sh.c***:82)。回想一下，在代码执行到这里时，shell已经`fork`出了子shell，`runcmd`将调用`exec`来加载新程序。

`open`的第二个参数由一组标志组成，这些标志以位表示，用于控制打开的操作。可能的值定义在文件控制(fcntl)头文件(***kernel/fcntl.h***:1-5)中

在 `kernel/fcntl.h`（文件控制头文件）中，你会发现它们的定义：

| **标识符** | **全称** | **作用** |
| --- | --- | --- |
| **`O_RDONLY`** | Read Only | **只读**模式。你只能从这个 FD 读，不能写。 |
| **`O_WRONLY`** | Write Only | **只写**模式。你只能往这个 FD 写。 |
| **`O_RDWR`** | Read & Write | **读写**模式。既能读也能写。 |
| **`O_CREATE`** | Create | **创建**模式。如果文件不存在，内核就帮你新建一个。 |
| **`O_TRUNC`** | Truncate | **截断**模式。如果文件已存在，打开时直接把内容清空（长度变为 0）。 |

---
---

## b. fork() & exec() 的分离
### 1. 分离
现在应该很清楚为什么`fork`和`exec`分离的用处了：在这两个调用之间，shell有机会对子进程进行I/O重定向，而不会干扰主shell的I/O设置。我们可以想象一个假设的`forkexec`系统调用组合，但是用这样的调用进行I/O重定向是很笨拙的。Shell可以在调用`forkexec`之前修改自己的I/O设置(然后撤销这些修改);或者`forkexec`可以将I/O重定向的指令作为参数;或者(最不吸引人的是)可以让每个程序(如cat)执行自己的I/O重定向。

尽管`fork`复制了文件描述符表，但是每个基础文件偏移量在父文件和子文件之间是共享的，比如下面的程序：
```c
// forkexec.c
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int pid = fork();

    if (pid == 0) {
        // 子进程：先执行
        write(1, "hello ", 6);
        exit(0);
    } else {
        // 父进程：等待子进程结束
        wait(0); // 等待子进程结束，回收资源
        // 子进程结束后，父进程再执行
        write(1, "world\n", 6);
    }

    exit(0);
}
```
运行结果：
```bash
$ forkexec
hello world
```
> **注意，如果不写wait(0),父进程和子进程谁先执行是不确定的，可能会输出"world\nhello "，也可能是"hello world\n"，甚至可能这两字段都没有顺序，全是乱码。这取决于操作系统的调度。**

在这个片段的末尾，附加到文件描述符1的文件将包含数据`hello world`。父进程中的写操作(由于等待，只有在子进程完成后才运行)在子进程停止写入的位置进行。这种行为有助于从shell命令序列产生顺序输出，比如`(echo hello;echo world) >output.txt`。

`dup`系统调用复制一个现有的文件描述符，返回一个引用自同一个底层I/O对象的新文件描述符。两个文件描述符共享一个偏移量，就像fork复制的文件描述符一样。这是另一种将“hello world”写入文件的方法：

```c
// dupforkexec.c
#include "kernel/types.h"
#include "user/user.h"

int main() {
    int fd;

    // 1. 复制标准输出（1号），fd 拿到了当前最小的可用编号（通常是 3）
    fd = dup(1);

    // 2. 往 1 号钩子写 "hello "
    // 内核将 "hello " 送往屏幕，并将偏移量向后移动 6 位
    write(1, "hello ", 6);

    // 3. 往 fd (3号) 钩子写 "world\n"
    // 因为 1 和 fd 共享同一个偏移量，内核会从第 7 位开始写
    write(fd, "world\n", 6);

    exit(0);
}
```

**如果两个文件描述符是通过一系列`fork`和`dup`调用从同一个原始文件描述符派生出来的，那么它们共享一个偏移量。否则，文件描述符不会共享偏移量，即使它们来自于对同一文件的打开调用。**`dup`允许shell执行这样的命令：`ls existing-file non-existing-file > tmp1 2>&1`。`2>&1`告诉shell给命令的文件描述符2是描述符1的副本。现有文件的名称和不存在文件的错误信息都会显示在tmp1文件中。Xv6 shell不支持错误文件描述符的I/O重定向，但是现在你知道如何实现它了。

---
---

### 2. 共享偏移量
**文件描述符表 (FD Table)** 和 **打开文件表 (Open File Table)** 之间的映射关系。

在内核的视角里，这其实是**两层映射**。

**两层映射模型**

当你的程序执行 `open` 或 `dup` 时，内核实际上是在维护两张表：

- **进程级 FD 表 (Process FD Table)**：这是属于你进程的“私有账本”。
- **全局文件表 (Global Open File Table)**：这是内核维护的“所有被打开文件的状态清单”。

<mark>映射路径：</mark>

`进程 FD (索引 1) -> 账本中的某一行 -> 指向【全局打开文件表】的一行 -> 指向【真正的文件/设备】`

---

**`open` 做了什么？**

当你执行 `open("test.txt", O_RDWR)` 时：

1. 内核在**全局文件表**中分配了一个新行（创建一个“对象”），里面记录了：

    - **引用计数**：目前有几个 FD 连着我（初始为 1）。
    - **偏移量 (Offset)**：当前读写到哪个字节（初始为 0）。
    - **文件指针**：指向文件在磁盘上的位置或对应的设备驱动。
2. 在你的**进程 FD 表**中找一个空位（假设是 3），把 3 指向这行。


--- 

**`dup` 做了什么？（关键点！）**

当你执行 `fd2 = dup(fd1)` 时：

1. 内核**不会**在全局表里创建新行。
2. 它只是在你的**进程 FD 表**里找一个空位（假设是 4），把 4 也填上同一个全局行的地址。
3. 它将那个全局行的 **引用计数 (Reference Count)** 加 1。

这就是为什么我说它们**指向同一个结构体**：因为它们共用的是全局表中的**同一行信息**。

* * *

**为什么“偏移量”会共享？**

因为全局文件表的那一行里，**只有一个 `offset` 变量**。

- 如果你通过 FD 1 写了 5 个字节，内核更新全局表里的 `offset = 5`。
- 当你随后通过 `fd2` 写数据时，内核去全局表一看，`offset` 已经是 5 了，于是它直接从第 6 个字节开始写。

这就是为什么**通过 `dup` 得到的 FD 是“合体”的**。

* * *

**什么时候会“分离”？**

为了对比，看看 `open` 两次会发生什么：

- 如果你对同一个文件调用两次 `open`，内核会在全局表里创建 **两行独立的新行**。
- 每行都有自己独立的 `offset`。
- 这样，你通过 `fd1` 写入的数据，完全不会影响 `fd2` 的读取位置。

* * *

**总结：底层逻辑的秘密**

| **操作** | **进程 FD 表** | **全局打开文件表** | **是否共享偏移量？** |
| --- | --- | --- | --- |
| **`dup`** | 产生新的 FD 编号 | **不创建新行**，仅引用旧行 | **是 (共享)** |
| **`open`** | 产生新的 FD 编号 | **创建全新的行** | **否 (独立)** |

**理解了这个，你就彻底看穿了操作系统。这种“引用计数”机制是实现进程间通信、重定向以及管道的基础。`Pipe`（管道）的本质，就是内核在创建管道时，直接往全局文件表里塞了一对“读行”和“写行”，然后把这两个 FD 分别交给父子进程。**

> 文件描述符是一个强大的抽象，因为它们隐藏了它们所连接的细节：写入文件描述符1的进程可能写入文件、设备（如控制台）或管道。

---
---
---

# 1.3 管道
## Intro
!!! : 固定的两个端口，一个读，一个写
管道是作为一对文件描述符公开给进程的小型内核缓冲区，一个用于读取，一个用于写入。将数据写入管道的一端使得这些数据可以从管道的另一端读取。管道为进程提供了一种通信方式。

下面的示例代码使用连接到管道读端的标准输入来运行程序`wc`.
注1：`wc`即`word count`，输出：行数、单词数、字节数
注2：pipe()返回值：
- 调用成功时
  - **返回值**：`0`。
  - **副作用**：内核会填充你传入的数组 `p`。
    - `p[0]`：设定为**读取端**的FD。
    - `p[1]`：设定为**写入端**的FD。

- 调用失败时
  - **返回值**：`-1`。
  - **原因**：通常是因为进程打开的文件描述符数量达到了上限（FD 耗尽），或者内核内存不足。
  - **后果**：数组 `p` 中的内容不会被修改。
```c
// pipetest.c
#include "kernel/types.h"
#include "user/user.h"

int main() {
    int p[2];         // 定义一个数组来保存管道的两个文件描述符
    char *argv[2];
    argv[0] = "wc";   // 准备运行 wc 程序（词数统计）
    argv[1] = 0;      // 参数列表必须以空指针结尾

    // 创建管道：内核开辟缓冲区，p[0] 设为读端，p[1] 设为写端
    pipe(p);

    if (fork() == 0) {
        /* --- 子进程分支 --- */

        // 1. 关闭原本的标准输入（键盘）
        close(0);

        // 2. 复制管道读端。由于 0 号 FD 刚刚释放，dup 会自动将管道读端挂在 0 上
        // 这样 wc 程序运行时，就会默认从管道读取数据，而不是键盘
        dup(p[0]);

        // 3. 清理子进程中多余的描述符。已经有了 FD 0，原有的 p[0] 和 p[1] 就不再需要了
        // 必须关闭 p[1]，否则 wc 会因为管道写端未完全关闭而永远无法读到 EOF，导致卡死
        close(p[0]);
        close(p[1]);

        // 4. 加载并运行 wc 程序。wc 会读取 FD 0（即管道），统计完后退出
        exec("wc", argv); // word count 输出 ： lines words bytes
    } else {
        /* --- 父进程分支 --- */

        // 1. 父进程负责写数据，不需要读，所以关闭读端 p[0]
        close(p[0]);

        // 2. 往管道的写端 p[1] 写入字符串
        write(p[1], "hello world\n", 12);

        // 3. 写完后关闭写端。这会在管道中产生一个 EOF（文件结束符）
        // 子进程的 read 读到 EOF 会返回 0，从而通知 wc 数据已传输完毕
        close(p[1]); //随写随关 不容易出错

        // 4. 等待子进程执行完毕并退出，防止子进程变成僵尸进程
        wait(0); 
    }

    // 整个任务完成，父进程退出
    exit(0);
}
```
运行结果
```bash
$ pipetest
1 2 12
```
>程序调用`pipe`，创建一个新的管道，并在数组p中记录读写文件描述符。在`fork`之后，父子进程都有指向管道的文件描述符。子进程调用`close`和`dup`使文件描述符0指向管道的读取端（前面说过优先分配最小的未使用的描述符），然后关闭p中所存的文件描述符，并调用`exec`运行`wc`。当`wc`从它的标准输入读取时，就是从管道读取。父进程关闭管道的读取端，写入管道，然后关闭写入端。

>如果没有可用的数据，则管道上的`read`操作将会进入等待，直到有新数据写入或所有指向写入端的文件描述符都被关闭，在后一种情况下，`read`将返回0，就像到达数据文件的末尾一样。事**实上，`read`在新数据不可能到达前会一直阻塞，这是子进程在执行上面的`wc`之前关闭管道的写入端非常重要的一个原因：如果wc的文件描述符之一指向管道的写入端，wc将永远看不到文件的结束。**

---
---

## brief summary

**1. 管道要解决什么问题？**

  在没有管道之前，如果进程A想把数据传给进程B，通常有多种笨方法：

- **写文件**  ：进程A把结果存入`temp.txt`  ，进程B重新打开`temp.txt`  读取。

    - *缺点* ：磁盘I/O太慢；得手动清理临时文件；如果A没写完B就读，还得写复杂的同步逻辑。
- **写一个大程序**：把A和B的功能全部写进一个巨型`.c`文件里。

    - *缺点*：代码占领，难以维护；如果你想把 A 的输出传给进程 C，你就得重写整个程序。

**管道的精髓用途：解耦。** 它让进程之间互不相识，却能高效协作。


**2. 管道实现了什么？**

管道实现了一种 **“流式处理（StreamProcessing）”**。

- **它统一接口**：所有进程都只跟“文件占用”打交道。进程A不需要知道自己在发`wc`数据，它只管往`1`号口（stdout）写；进程B也不需要知道数据是谁发的，只管从`0`号口（stdin）读。
- **内存中转**：数据不落盘，直接在内核内存里像流水一样从A传到B。
- **自动同步**：这是最明显的位置。如果管道满了，写的进程会自动**阻塞（等待）**；如果管道空了，读的进程会自动**阻塞**。你不需要写任何线程锁或同步代码。

**3. 实现的方法是什么？**

管道的实现依托于Unix内核的三个支柱：

**第一招：核心枢纽（The Buffer）**

当你调用的`pipe(p)`时候，内核在内存里开辟了一个**环形蜡烛图**。`p[1]`就是这个蜡烛图的“写入入口”，`p[0]`就是“读取出口”。

- 数据就像管道带一样，一头进，一头出。

**第二招：文件重定向（The Redirect）**

这就是你的代码里`close`和`dup`作用。

- 我们利用`fork`后子进程继承 FD 的特性，强行把子进程的“嘴巴”（stdin/FD 0）接收管道的“出口”上，或者把“菊花”（stdout/FD 1）接收管道的“入口”上。
- **结果**：程序原有的I/O逻辑被“嫁接”到了管道上。

**第三招：引用计数与 EOF（The Cleanup）**

内核记录了有多少个FD连在这个管道上。

- **只有当所有写端FD都关闭了，读端`read`才会返回`0`（EOF）。**
- 这就是为什么我们要疯狂`close`的FD。这是一个**信号机制**，告诉对面的进程：“我话传完了，你可以收工了。”

---
---

## Shell中的管道
>Xv6 shell以类似于上面代码(***user/sh.c***:100)的方式实现了诸如`grep fork sh.c | wc -l`之类的管道。子进程创建一个管道将管道的左端和右端连接起来。然后对管道的左端调用`fork`和`runcmd`，对管道的右端调用`fork`和`runcmd`，并等待两者都完成。管道的右端可能是一个命令，该命令本身包含一个管道(例如，`a | b | c`)，该管道本身`fork`为两个新的子进程(一个用于b，一个用于c)。**因此，shell可以创建一个进程树。这个树的叶子是命令，内部节点是等待左右两个子进程完成的进程。**

在 xv6 中，管道不是扁平的，而是**递归**的。

- **内部节点**：是 Shell 派生出的子进程，它们不运行具体的 `grep` 或 `wc`，只负责“协调”。它们创建一个管道，然后 `fork` 出左、右两个子进程。
- **叶子节点**：是真正的命令（如 `grep`、`wc`）。

当你运行 `grep fork sh.c | wc -l`：

1. **子 Shell** 发现有 `|`，于是创建一个管道。
2. 它 **`fork()` 出左进程** 去运行 `grep`。
3. 它 **`fork()` 出右进程** 去运行 `wc`。
4. **内部节点（子 Shell）** 调用 `wait()`，确保左右两边都干完活才退出。

> 原则上，可以让内部节点在管道的左端运行，但是正确地这样做会使实现复杂化。
> 考虑进行以下修改：将 ***sh.c*** 更改为不对`p->left`进行`fork`，并在内部进程中运行`runcmd(p->left)`。
> 然后，例如，`echo hi | wc`将不会产生输出，因为当`echo hi`在`runcmd`中退出时，内部进程将退出，而不会调用`fork`来运行管道的右端。这个不正确的行为可以通过不调用内部进程的`runcmd`中的`exit`来修复，但是这个修复使代码复杂化：现在`runcmd`需要知道它是否是一个内部进程。同样的，当没有对`(p->right)`执行`fork`时也会更加复杂。
> 例如，只需进行上述的修改，`sleep 10 | echo hi`将立即打印“hi”，而不是在10秒后，因为`echo`将立即运行并退出，而不是等待`sleep`完成。因为 ***sh.c*** 的目标是尽可能的简单，所以它不会试图避免创建内部进程。

**main：为了省掉一个进程，能不能让内部节点自己去运行左边的命令（不 `fork` 左边）？**

文中给出了两个失败的理由，证明了 **“偷懒（优化）反而会变复杂”** ：
**问题 A：提前退出**

如果内部进程直接运行 `echo hi`：

- `echo` 运行完会调用 `exit()`。
- 这一退出，整个内部进程就没了，它根本没机会去 `fork` 右边的 `wc`。
- **修复方案**：得修改 `runcmd`，让它知道自己是“内部节点”从而不退出。这打破了代码的通用性。

**问题 B：时序错乱**

如果内部进程直接运行右边的命令（不 `fork` 右边）：

- 考虑 `sleep 10 | echo hi`。
- 正常情况下，`echo` 应该等 `sleep`。但如果内部进程直接运行 `echo`，它会立即打印并退出。
- 因为没有 `fork`，就没有独立的进程去 `wait` 左边的 `sleep`。

**试图通过减少 `fork` 来优化性能，会导致 `runcmd` 需要感知复杂的上下文状态，破坏了 Unix “组合小工具”的纯粹性。**

---

管道看起来并不比临时文件更强大：下面的管道命令行

    echo hello world | wc

可以不通过管道实现，如下

    echo hello world > /tmp/xyz; wc < /tmp/xyz

在这种情况下，管道相比临时文件至少有四个优势

- 首先，管道会自动清理自己；在文件重定向时，shell使用完`/tmp/xyz`后必须小心删除
- 其次，管道可以任意传递长的数据流，而文件重定向需要磁盘上足够的空闲空间来存储所有的数据。
- 第三，管道允许并行执行管道阶段，而文件方法要求第一个程序在第二个程序启动之前完成。
- 第四，如果实现进程间通讯，管道的**阻塞**式读写比文件的非阻塞语义更高效。
---
---
---

# 1.4 文件系统
## Intro
Xv6文件系统提供数据文件（包含未解释的字节数组）和目录（包含对数据文件和其他目录的命名引用）。这些目录形成一个树，从一个叫做根的特殊目录开始。像`/a/b/c`这样的路径是指在根目录`/`下名为`a`的目录中名为`b`的目录中名为`c`的文件或目录。不以`/`开始的路径相对于调用进程的当前工作目录进行计算，当前工作目录可以通过`chdir`系统调用进行更改。下面两个代码片段打开相同的文件(假设所有相关的目录都存在)。
```c
chdir("/a");
chdir("b"); // 这里的路径是相对于当前目录的，所以它会进入 b 目录
open("c", O_RDONLY); // 这里的路径也是相对于当前目录的，所以它会在 b 目录下寻找 c 文件
open("/a/b/c", O_RDONLY); // 这里的路径是绝对路径，从根目录开始寻找 a，再找 b，最后找到 c
```

还有创建新文件和目录的系统调用：

- `mkdir`创建一个新目录
- `open`中若使用`O_CREATE`标志将会创建一个新的数据文件
- `mknod`创建一个新的设备文件

这个例子说明了这三点:
```c
mkdir("/dir");
fd = open("/dir/file", O_CREATE | O_WRONLY);
close(fd);
mknod("/console", 1, 1);
```
> `mknod`创建一个引用设备的特殊文件。与设备文件相关联的是主设备号和次设备号(`mknod`的两个参数)，它们唯一地标识了一个内核设备。当进程稍后打开设备文件时，内核将使用内核设备实现`read`和`write`系统调用，而不是使用文件系统。

---
---

## 细说`mknod`
理解 `mknod` 的关键在于打破 **“文件即磁盘数据”** 的传统思维。在 Unix/Linux 系统中，`mknod` 是通往 **“硬件世界”** 的一道门。

**核心概念：为什么要有 `mknod`？**

通常情况下，当你 `open()` 一个文件时，内核会去磁盘读取该文件的物理数据。

但系统里有很多东西不是文件，比如：

- **键盘**：你敲击的字符是从哪来的？
- **屏幕**：你打印的文字输出到了哪？
- **磁盘驱动器本身**：直接读取磁盘扇区的数据。

如果让这些硬件也像普通文件一样被程序访问，编程就会变得异常简单。于是，Unix 引入了 **“设备文件 (Device File)”**。`mknod` 的作用就是**在文件系统里“凭空”造出一个文件入口，把它指向内核里的某个硬件驱动程序。**

---

**`mknod` 的参数是什么意思？**

`mknod` 并不是在磁盘上创建真正的数据内容，而是在元数据区（Inode）打上一个特殊的“标记”。

- **主设备号 (Major Number)**：相当于“类别 ID”。它告诉内核：“去找哪一个驱动程序”。比如 1 号可能是控制台驱动，2 号可能是磁盘驱动。
- **次设备号 (Minor Number)**：相当于“具体实例 ID”。如果你有两个磁盘驱动器，主设备号都是磁盘驱动，次设备号分别代表磁盘 0 和磁盘 1。

---

**当你执行 `open()` 时，背后发生了什么？**

当你的程序调用 `open("/dev/tty", ...)` 时：

1. **路径解析**：内核检查文件系统的 Inode。
2. **特殊标识**：内核发现这个 Inode 被标记为“设备文件”（通过 `mknod` 留下的特殊位）。
3. **跳转驱动**：内核不再去访问磁盘上的数据块，而是根据 Inode 里的**主/次设备号**，直接跳转到内核设备表里的对应函数。
4. **建立连接**：内核把你的文件描述符（FD）直接挂载到该硬件驱动的 `read/write` 函数上。

**从这一刻起，你对这个 FD 的任何操作，本质上都是在直接调用硬件驱动的函数！**

---

**一个直观的类比：插座**

- **普通文件**：就像是一盒磁带，你读取它，就是从里面放声音出来。
- **设备文件**：就像是墙上的**插座**。

    - `mknod` 就像是安装插座并给它编号（主/次设备号）。
    - 插上电器（`open`）后，电流（数据）就直接流向了背后的电线（内核驱动）。
    - 插座本身并不存电（不存数据），它只是一个**接口**。

---

**为什么 xv6 需要它？**

在像 xv6 这样极简的操作系统中，`mknod` 是实现 **“万物皆文件”** 的必要手段：

- 只有通过 `mknod` 创建设备文件，Shell 才能执行 `ls > /dev/console`（把输出重定向到控制台）。
- 如果没有 `mknod`，操作系统就需要设计完全不同的系统调用来访问键盘、鼠标和磁盘，那样系统就会变得臃肿且复杂。

---

**EXAMPLE**
```c
// mknod_demo.c
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

// 在 XV6 中，1 通常是控制台设备的主设备号 (CONSOLE)
#define CONSOLE_MAJOR 1

int main() {
    // 1. 使用 mknod 创建一个设备文件
    // 参数含义：文件名, 主设备号, 次设备号
    // 这会在文件系统中产生一个 Inode，指向内核的控制台驱动
    if (mknod("my_console", CONSOLE_MAJOR, 1) < 0) { // -1 表示失败
        printf("mknod failed\n");
        exit(1);
    }

    printf("Device file 'my_console' created.\n");

    // 2. 像打开普通文件一样打开这个设备
    int fd = open("my_console", O_WRONLY);
    if (fd < 0) {
        printf("open device failed\n");
        exit(1);
    }

    // 3. 重点：往这个 FD 写入数据
    // 内核发现这个 FD 指向的是 CONSOLE_MAJOR，
    // 于是它不会把 "Hello Hardware" 写进磁盘，而是直接发给显示器驱动。
    char *msg = "Hello Hardware through mknod!\n";
    write(fd, msg, strlen(msg));

    // 4. 关闭设备
    close(fd);

    exit(0);
}
```
运行结果
```bash
$ mknod_demo
Device file 'my_console' created.
Hello Hardware through mknod!
```

**说明：**

***`mknod` 参数位解析：如何指向真正的 `console`？***

`mknod` 函数的签名通常是：`mknod(char *path, short major, short minor)`。

**参数位代表什么？**
* **`path`**: 在文件系统里叫什么名字（例如 `/dev/console`）。
* **`major` (主设备号)**: **关键索引**。它代表的是**“哪一类驱动程序”**。在内核源码里有一个巨大的数组，叫做 `devsw` (Device Switch Table)。`major` 号就是这个数组的**下标**。
* **`minor` (次设备号)**: **具体参数**。代表该驱动管辖下的“第几个实例”。比如你有两个串口，它们的主设备号相同（都是串口驱动），但次设备号分别是 0 和 1。

**它是如何指向真正的 `console` 的？**
这并非 `mknod` 一手完成的，而是通过内核的 **“分派机制”** 动态链接的。

1.  **内核启动时**：在 `kernel/main.c` 或设备初始化代码中，内核会执行 `consoleinit()`。
2.  **注册驱动**：这个初始化函数会把控制台的读写函数指针（如 `consoleread` 和 `consolewrite`）填入 `devsw` 数组的第 1 号位置（假设 `CONSOLE_MAJOR` 是 1）。
3.  **用户调用时**：
    * 当你 `open("my_console")`，内核拿到该文件的 Inode。
    * 内核读取 Inode 里的 `major` 号（即 1）。
    * 内核去 `devsw[1]` 找到驱动函数指针。
    * **连接完成**：后续你的 `read` 和 `write` 调用，就会被重定向到 `console.c` 里的那两个函数。

---

**为什么你写程序时不需要指明具体的 `console` 函数？**

这就是 Unix 的抽象美学。你的代码里写的是：
```c
write(fd, ...);
```
内核在这里充当了**“交换机”**的角色：

* **如果 FD 指向普通文件**：内核分派给 `filewrite()`（写磁盘）。
* **如果 FD 指向设备文件**：内核根据主设备号，分派给 `devsw[major].write()`。

在这个设计中，**`mknod` 的参数并不直接存储函数指针，它只存储了一个“身份代码”（主/次设备号）**。这个身份代码在运行时像一把钥匙，去 `devsw` 表里“插”入对应的驱动锁孔，从而解锁硬件操作。

---
---

### **精髓——文件**
`mknod` 的真正魔力在于它让 **“设备”** 也变成了 **“文件”**。这就是 Unix 的核心哲学：**万物皆文件**。在这个意义下，`my_console` 想象成一个 **“特殊的、永远写不满也读不完的 txt 文件”**
对于你的代码（用户态程序）来说，读写 `my_console` 和读写 `test.txt` 的动作是**完全对等**的：    
- **打开**：都要调用 `open()`，都会得到一个文件描述符（FD）。
- **写入**：执行 `write(fd, "hello", 5)`。
- **读取**：执行 `read(fd, buf, 5)`。
- **关闭**：执行 `close(fd)`。

区别：

| 特性 | 真正的 `txt` 文件 | `my_console` (设备文件) |
| --- | --- | --- |
| **存储位置** | 数据存在**磁盘扇区**里 | 数据流向**硬件缓冲区**（如显示器/串口） |
| **持久性** | 你写进去，下次还能原样读出来 | 你写进去，屏幕亮一下就没了；你读它，取决于此时谁在敲键盘 |
| **文件大小** | 有大小（比如 1KB），受磁盘空间限制 | **没有大小**（或者说大小无限），它是一个持续的“流” |
| **随机访问** | 可以用 `lseek` 跳到开头重新读 | **不支持 `lseek`**（你没法让显示器“倒带”到刚才打印的内容） |


> 一个文件的名字和文件本身是不同的;
> 同一个底层文件（叫做inode，索引结点）可以有多个名字（叫做link，链接）。
> 每个链接都由目录中的一个条目组成;该条目包含一个文件名和一个inode引用。
> Inode保存有关文件的元数据（用于解释或帮助理解信息的数据），包括其类型(文件/目录/设备)、长度、文件内容在磁盘上的位置以及指向文件的链接数。


---
---

## `fstat`系统调用
`fstat`系统调用从文件描述符所引用的inode中检索信息。它填充一个`stat`类型的结构体，`struct stat`在 ***stat.h(kernel/stat.h)*** 中定义为
```c
#define T_DIR 1    // Directory
#define T_FILE 2   // File
#define T_DEVICE 3 // Device
struct stat {
    int dev;     // 文件系统的磁盘设备
    uint ino;    // Inode编号
    short type;  // 文件类型
    short nlink; // 指向文件的链接数
    uint64 size; // 文件字节数
};
```
---

**`fstat` 解决了什么问题？**
程序在处理文件时，往往会有很多疑问：
* 我手里拿的这个 FD，到底是个**普通文件**，还是一个**目录**，或者是一个**硬件设备**？
* 这个文件现在有多大？
* 这个文件在磁盘上的“唯一编号”（Inode）是多少？

---

**字段详细说明：文件的“房产证”**

当你调用 `fstat(fd, &st)` 后，`st` 结构体会填充以下字段：

* **`type` (文件类型)**：最关键的分类字段。
    * `T_DIR`：你是目录（比如 `.` 或 `/bin`）。
    * `T_FILE`：你是普通文件（比如 `hello.txt`）。
    * `T_DEVICE`：你是**硬件门户**（比如 `/dev/console`，通过 `mknod` 创建）。
* **`ino` (Inode 编号)**：这是文件在磁盘上的“身份证号”。在同一个文件系统中，两个不同文件的 Inode 号绝对不会重复。这在处理**硬链接**（多个路径指向同一个文件）时至关重要。
* **`nlink` (硬链接数)**：记录有多少个路径名（文件名）指向这同一个 Inode。如果你删除一个文件名，这个数字会减 1；当它降为 0 时，文件才真正从磁盘中销毁。
* **`size` (文件大小)**：文件总共占了多少个字节。如果是设备文件，这个值通常没意义。
* **`dev` (设备标识)**：文件所在的“分区”或“磁盘设备”ID。

---

**EXAMPLE**
```c
// stat_demo.c
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"

// 辅助函数：根据 type 打印类型描述
void print_type(struct stat *st) {
    if (st->type == T_DIR) {
        printf("类型: 目录 (T_DIR)\n");
    } else if (st->type == T_DEVICE) {
        printf("类型: 设备 (T_DEVICE)\n");
    } else if (st->type == T_FILE) {
        printf("类型: 普通文件 (T_FILE)\n");
    } else {
        printf("类型: 未知\n");
    }
}

int main() {
    struct stat st;
    int fd;

    // 1. 测试普通文件 (系统里有一个 README 文件)
    printf("--- 测试: README (普通文件) ---\n");
    fd = open("README", O_RDONLY);
    if (fd >= 0) {
        fstat(fd, &st); // 获取文件信息 把fd指向的文件的状态信息填充到 st 结构体中
        print_type(&st);
        printf("Inode: %d, 大小: %d 字节\n", st.ino, st.size);
        close(fd);
    }

    // 2. 测试目录 (通常 "." 代表当前目录)
    printf("\n--- 测试: . (当前目录) ---\n");
    fd = open(".", O_RDONLY);
    if (fd >= 0) {
        fstat(fd, &st);
        print_type(&st);
        close(fd);
    }

    // 3. 测试设备 (控制台)
    printf("\n--- 测试: console (设备) ---\n");
    // 在 XV6 中，控制台通常由 mknod 在启动时创建，可以通过 /console 访问
    fd = open("console", O_RDONLY);
    if (fd >= 0) {
        fstat(fd, &st);
        print_type(&st);
        close(fd);
    }

    exit(0);
}
```
运行结果
```bash
$ stat_demo
--- 测试: README (普通文件) ---
类型: 普通文件 (T_FILE)
Inode: 2, 大小: 2059 字节

--- 测试: . (当前目录) ---
类型: 目录 (T_DIR)

--- 测试: console (设备) ---
类型: 设备 (T_DEVICE)
```

如果没有 `fstat`，你尝试对一个目录执行 `read()`，或者对一个设备文件执行不当的操作，系统往往会报错或陷入死循环。

---
---

## `link`系统调用 (Hard Link)
`link`系统调用创建另一个文件名，该文件名指向与现有文件相同的inode。下面的代码片段创建了一个名字既为 ***a*** 又为 ***b*** 的新文件
``` c
open("a", O_CREATE | O_WRONLY);
link("a", "b");
```

从 ***a*** 读取或写入与从 ***b*** 读取或写入是相同的操作。每个inode由唯一的inode编号标识。在上面的代码序列之后，可以通过检查`fstat`的结果来确定a和b引用相同的底层内容:两者都将返回相同的inode号(`ino`)，并且`nlink`计数将被设置为2。


**EXAMPLE**
```c
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"

void print_stat(char *name) {
    struct stat st;
    int fd = open(name, O_RDONLY);
    if (fd < 0) {
        printf("无法打开 %s\n", name);
        return;
    }
    if (fstat(fd, &st) < 0) {
        printf("fstat 失败\n");
        close(fd);
        return;
    }
    printf("文件名: %s -> Inode编号: %d, 硬链接数(nlink): %d\n", 
            name, st.ino, st.nlink);
    close(fd);
}

int main() {
    // 1. 创建原始文件 "file_a"
    int fd = open("file_a", O_CREATE | O_WRONLY);
    if (fd < 0) {
        printf("创建失败\n");
        exit(1);
    }
    write(fd, "hello unix\n", 11);
    close(fd);

    printf("--- 创建 file_a 后 ---\n");
    print_stat("file_a");

    // 2. 使用 link 系统调用创建 "file_b"，指向 "file_a" 的 Inode
    if (link("file_a", "file_b") < 0) {
        printf("link 失败\n");
        exit(1);
    }

    printf("\n--- 执行 link(\"file_a\", \"file_b\") 后 ---\n");
    print_stat("file_a");
    print_stat("file_b");

    // 3. 证明：修改 file_b，file_a 也会变
    fd = open("file_b", O_WRONLY);
    write(fd, "WORLD", 5); // 覆盖写入前5个字符
    close(fd);

    printf("\n--- 修改 file_b 后，读取 file_a 的内容 ---\n");
    char buf[12];
    fd = open("file_a", O_RDONLY);
    read(fd, buf, 11);
    buf[11] = '\0';
    printf("file_a 的内容变为: %s\n", buf);
    close(fd);

    exit(0);
}
```
运行结果
```bash
$ link_demo
--- 创建 file_a 后 ---
文件名: file_a -> Inode编号: 35, 硬链接数(nlink): 1

--- 执行 link("file_a", "file_b") 后 ---
文件名: file_a -> Inode编号: 35, 硬链接数(nlink): 2
文件名: file_b -> Inode编号: 35, 硬链接数(nlink): 2

--- 修改 file_b 后，读取 file_a 的内容 ---
file_a 的内容变为: WORLD unix
```

---
---

## `unlink`系统调用
`unlink`系统调用从文件系统中删除一个名称。**只有当文件的链接数(`nlink`)为零且没有文件描述符引用时**，文件的inode和包含其内容的磁盘空间才会被释放，因此添加
```c
unlink("a");
```

最后一行代码序列中会使inode和文件内容可以作为b访问。此外
```c
fd = open("/tmp/xyz", O_CREATE | O_RDWR);
unlink("/tmp/xyz");    
```

是创建没有名称的临时inode的惯用方法，该临时inode将在进程关闭fd或退出时被清理。

**EXAMPLE**
```c
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"

int main() {
    int fd;
    struct stat st;

    // 1. 创建一个临时文件 "temp_secret"
    fd = open("temp_secret", O_CREATE | O_RDWR);
    if (fd < 0) {
        printf("创建失败\n");
        exit(1);
    }
    printf("1. 文件 'temp_secret' 已创建。\n");

    // 2. 立即 unlink 它（删除文件名）
    // 此时文件在磁盘上的名字没了，ls 看不到了
    if (unlink("temp_secret") < 0) {
        printf("unlink 失败\n");
        exit(1);
    }
    printf("2. 执行 unlink，文件名已从目录中移除。\n");

    // 3. 验证：尝试打开 "temp_secret" 会失败
    if (open("temp_secret", O_RDONLY) < 0) {
        printf("3. 验证成功：现在无法通过名字打开该文件。\n");
    }

    // 4. 重点：虽然名字没了，但我们手里的 fd 依然有效！
    // 我们往这个“无名文件”里写数据
    write(fd, "Ghost data is here!\n", 20);
    printf("4. 已通过旧的 FD 写入数据。\n");

    // 5. 寻道回开头并读取，证明数据确实存在
    // 注意：xv6 的系统调用可能需要用不同方式重置位置，
    // 这里我们简单关闭再重新打开是不行的（因为没名字了），
    // 实际在 xv6 中，这个 FD 的偏移量是持续的。
    // 为了简单演示，我们直接在当前位置读（虽然写完后在末尾）
    // 在标准 Unix 中会用 lseek(fd, 0, 0)
    
    printf("5. 进程依然持有该文件的引用，直到 close(fd) 或进程退出，空间才释放。\n");

    // 检查这个 FD 的状态
    fstat(fd, &st);
    printf("   此时 Inode 编号: %d, 硬链接数(nlink): %d\n", st.ino, st.nlink);

    close(fd); 
    printf("6. FD 已关闭，此时文件内容正式从磁盘抹除。\n");

    exit(0);
}
```
运行结果
```bash
$ nlink_demo
1. 文件 'temp_secret' 已创建。
2. 执行 unlink，文件名已从目录中移除。
3. 验证成功：现在无法通过名字打开该文件。
4. 已通过旧的 FD 写入数据。
5. 进程依然持有该文件的引用，直到 close(fd) 或进程退出，空间才释放。
   此时 Inode 编号: 36, 硬链接数(nlink): 0
6. FD 已关闭，此时文件内容正式从磁盘抹除。
```

---
---

## Outro
Unix以用户级程序的形式提供了可从shell调用的文件实用程序，例如`mkdir`、`ln`和`rm`。这种设计允许任何人通过添加新的用户级程序来扩展命令行接口。事后看来，这个计划似乎是显而易见的，但是在Unix时代设计的其他系统经常将这样的命令构建到shell中(并将shell构建到内核中)

一个例外是`cd`，它是内置在shell(***user/sh.c***:160)。`cd`必须更改shell本身的当前工作目录。如果`cd`作为常规命令运行，那么shell将分出一个子进程，子进程将运行`cd`，`cd`将更改子进程的工作目录。父目录(即shell的)的工作目录不会改变。

---
---
---

# END
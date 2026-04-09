### 核心系统调用速查表

| 分类 | 函数原型 | 功能描述 | 返回值 |
| :--- | :--- | :--- | :--- |
| **进程管理** | `int fork()` | 创建一个子进程 | 子进程 PID (父进程中); 0 (子进程中) |
| | `int exit(int status)` | 终止当前进程并报告状态 | 无返回 |
| | `int wait(int *status)` | 等待子进程退出并获取状态 | 退出子进程的 PID |
| | `int exec(char *file, char *argv[])` | 加载并执行指定文件 | 仅出错时返回 -1 |
| | `int getpid()` | 获取当前进程的 PID | 当前进程 PID |
| | `int sleep(int n)` | 暂停进程 n 个时钟节拍 | 0 |
| | `int kill(int pid)` | 终止指定 PID 的进程 | 0 (成功); -1 (错误) |
| **文件操作** | `int open(char *file, int flags)` | 打开文件并指定读写模式 | 文件描述符 (fd) |
| | `int read(int fd, char *buf, int n)` | 从 fd 读取 n 字节到 buf | 读取的字节数; 0 (EOF) |
| | `int write(int fd, char *buf, int n)` | 将 buf 中的 n 字节写入 fd | 写入的字节数 |
| | `int close(int fd)` | 释放/关闭文件描述符 | 0 (成功); -1 (错误) |
| | `int dup(int fd)` | 复制 fd，指向同一打开的文件 | 新的文件描述符 |
| **内存管理** | `char *sbrk(int n)` | 增加进程内存 n 字节 | 新内存的起始地址 |
| **文件系统** | `int pipe(int p[])` | 创建管道，p[0]读, p[1]写 | 0 (成功); -1 (错误) |
| | `int chdir(char *dir)` | 改变当前工作目录 | 0 (成功); -1 (错误) |
| | `int mkdir(char *dir)` | 创建新目录 | 0 (成功); -1 (错误) |
| | `int mknod(char *file, int, int)` | 创建设备文件 | 0 (成功); -1 (错误) |
| | `int fstat(int fd, struct stat *st)` | 获取已打开文件的状态信息 | 0 (成功); -1 (错误) |
| | `int stat(char *file, struct stat *st)` | 按名称获取文件的状态信息 | 0 (成功); -1 (错误) |
| | `int link(char *f1, char *f2)` | 为 f1 创建硬链接 f2 | 0 (成功); -1 (错误) |
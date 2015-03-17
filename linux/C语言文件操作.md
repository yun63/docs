
（一） 底层IO系统调用
=====================

### open 系统调用

```
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int open(const char *path, int oflags);
int open(const char *path, int oflags, mode_t mode);
```

在遵循posix标准的系统上，sys/types.h和sys/stat.h不需要被包含。

open建立了一条到文件或者设备的访问路径。如果调用成功，将返回一个可以
被read，write和其他系统调用使用的文件描述符。这个描述符唯一，如果两个进程
同时打开同一个文件，它们会分别得到两个不同的描述符。同时写文件彼此覆盖。

oflags参数指明文件访问模式：O_RDONLY,O_WRONLY,O_RDWD(只读，只写，读写)
open调用还可以在oflags参数中指定其他组合(|):

O_APPEND : 把写入数据追加在文件的末尾
O_TRUNC  : 把文件长度置0,丢弃已有的内容
O_CREATE : 如果需要，按参数mode中给出的访问模式创建文件
O_EXCL   : 与O_CREATE一起使用，确保调用者创建出文件

open调用在成功时返回一个新的文件描述符（非负），失败时返回-1并设置errno来
指明失败的原因。

当使用了带有O_CREATE标志的open来创建文件是，必须使用3个参数格式的open调用。
第三个参数mode是几个标志位按位或得到的，这些标志在sys/stat.h中定义。
S_IRUSR,S_IWUSR,S_IXUSR
S_IRGRP,S_IWGRP,S_IXGRP
S_IROTH,S_IWOTH,S_IXOTH

eg: open("myfile", O_CREATE, S_IRUSR|S_IWUSR|S_IXOTH)

#### close 系统调用

```
#include <unistd.h>
int close(fildes);
```

close终止文件描述符与其对应文件的关联，并释放文件描述符可以重新利用。成功时
返回0, 失败时返回-1.

### lseek 系统调用

```
#include <unistd.h>
#include <sys/types.h>
off_t lseek(int fildes, off_t offset, int whence);
```

offset参数用来指定位置，whence参数定义该偏移值的用法
whence的取值：
SEEK_SET    : offset是一个绝对位置
SEEK_CUR    : offset是相对于当前位置的一个相对位置
SEEK_END    : offset是相对于文件尾的一个相对位置

### fstat,stat和lstat系统调用

fstat系统调用返回与打开文件描述符相关的文件的状态信息，该信息会写到buf结构中

```
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int fstat(int fildes, struct stat *buf);
int stat(const char *path, struct stat *buf);
int lstat(const char *path, struct stat *buf);

struct stat statbuf;
mode_t modes;

fstat("filename", &statbuf);
modes = statbuf.st_mode;
if (!S_ISDIR(modes) && (modes & S_IRWXU) == S_IXUSR)
    ....
```

### dup和dup2系统调用

dup系统调用提供了一种复制文件描述符的方法，这样就能够通过多个不同的文件描述符来访问同一个文件。

```
#include <unistd.h>
int dup(int fildes);
int dup2(int fildes, int fildes2);
```

（二）标准I/O库
===============

标准I/O库函数：
fopen,  fclose;
fread,  fwrite;
fflush
fseek
fgetc,  getc,   getchar
fputc,  putc,   putchar
fgets,  gets
printf, fprintf,    sprintf
scanf,  fscanf, sscanf

### fopen函数

主要用于对文件和终端的输入输出，如果需要对设备进行明确的控制，最好使用底层系统调用open。

```
#include <stdio.h>
FILE *fopen(const char *filename, const char *mode);
```

fopen打开由filename参数指定的文件，并与文件流关联。mode参数指定文件的打开方式。
"r"或者"rb"：以只读方式打开
"w"或者"wb"：以写方式打开，并把文件长度截断为0
"a"或者"ab"：已写方式打开，新内容追加末尾
"r+"或者"rb+"或者"r+b"：以更新方式打开（读和写）
"w+"或者"wb+"或者"w+b"：以更新方式打开（读和写）,并把文件长度截断为0
"a+"或者"ab+"或者"a+b"：以更新方式打开，新内容追加末尾

注意：linux并不像MS-DOS那样把文件分为文本和二进制文件，linux把所有文件都看做是二进制文件。

### fread函数

fread函数从文件流里读取数据

```
#include <stdio.h>
size_t fread(void *ptr, size_t size, size_t nitems, FILE *stream);
```

参数size指定每个数据记录的长度，计数器nitems指定要传输的记录个数，返回值为成功读取数据
缓冲区里的记录个数，而不是字节数

### fwrite函数

fwrite函数从指定的数据缓冲区里取出数据记录，并写到输出流中。

`size_t fwrite(const void *ptr, size_t size, size_t nitems, FILE *stream);`

### fclose函数

fclose函数关闭指定的文件流，使所有尚未写出的数据都写出。

```
#include <stdio.h>
int fclose(FILE *stream);
```

### fflush函数

fflush的作用是把文件流里的所有未写出的数据立刻写出，还可以确保在程序执行之前重要的数据都已经
被写到磁盘上。在调用fclose函数隐含执行了一次fflush函数，所以在fclose之前不必调用fflush函数。

```
#include <stdio.h>
int fflush(FILE *stream);
```

### fseek函数

fseek函数是与lseek系统调用对应的文件流函数。它在文件流里为下一次读写操作指定位置。
fseek函数返回0表示成功，-1表示失败并置errno指出错误。

```
#include <stdio.h>
int fseek(FILE *stream, long int offset, int whence);
```

### fgetc,getc和getchar函数

fgetc函数从文件流里取出下一个字节并把它作为一个字符返回，当它到达文件尾或出错时，返回EOF，
必须通过ferror或feof来区分这两种情况。

```
#include <stdio.h>
int fgetc(FILE *stream);
int getc(FILE *stream);
int getchar();
```

getc函数和fgetc的作用一样。
getchar函数 < == >getc(stdin),它从标准输入流里读取下一个字节。

### fputc,putc和putchar函数

fputc函数把一个字节写到一个输出文件流中，它返回写入的值，如果失败则返回EOF。

```
#include <stdio.h>
int fputc(int c, FIFE *stream);
int putc(int c, FIFE *stream);
int putchar(int c);
```

putc的作用也相当于fputc，但它可能被实现为一个宏。
putchar函数 < == > putc(c, stdout)。7 fputc,putc和putchar函数

fputc函数把一个字节写到一个输出文件流中，它返回写入的值，如果失败则返回EOF。

### fgets和gets函数

fgets函数从输入文件流读取一个字符串。

```
#include <stdio.h>
char *fgets(char *s, int n, FILE *stream);
char *gets(char *s);
```

fgets把读到的字符串写到s指向的字符串里，直到出现下面某种情况：
遇到换行符，已经传输了n-1个字符，或者到达文件末尾;
它会把遇到的换行符也传递到接收字符串里，在加上一个表示结尾的\0。
一个调用最多只能传输n-1个字符，因为末尾自动加\0。

当成功完成时，fgets返回一个指向字符串s的指针。如果文件流已经到达文件末尾，fgets
会设置这个文件流的EOF标识并返回一个空指针。如果出现读错误，fgets返回空指针并设置errno指明出错类型。

gets函数类似于fgets，只不过它从标准输入读取数据并丢弃遇到的换行符，并在接收字符串的尾部加null字节。
注意：gets对传输字符的个数没有限制，可能导致自己的缓冲区溢出，所以应该避免使用gets而用fgets代替。

**************************** 以上介绍的是标准I/O库函数

### 格式化输入和输出函数

1. printf，fprintf和sprintf函数

```
#include <stdio.h>
int printf(const char *format, ...);
int sprintf(char *s, const char *format, ...);
int fprintf(FILE *stream, const char *format, ...);
```

printf函数把自己的输出送到标准输出。
fprintf函数把自己的输出送到一个指定的文件流。
sprintf函数把自己的输出和一个结尾空字符写到参数传递过来的字符串s里，这个字符串必须足够容纳所有的输出数据。

2. scanf,fscanf和sscanf函数

```
#include <stdio.h>
int scanf(const char *format, ...);
fscanf(FILE *stream, const char *format, ...);
sscanf(const char *s, const char *format, ...);
```

### 其他流函数

ftell：返回文件流当前（读写）位置的偏移值。

文件流错误

```
#include <errno.h>
extern int errno;
int ferror(FILE *stream);
int feof(FILE *stream);
void clearerr(FILE *stream);
```

文件流和文件描述符
每个文件流都和一个底文件描述符相关联。

```
#include <stdio.h>
int fileno(FILE *stream);
FILE *fdopen(int fildes, const char *mode);
```

函数fileno返回指定文件流使用的文件描述符，失败返回-1;如果对一个已经打开的
文件流进行底层访问时，这个函数非常有用。


（三）文件和目录的维护
======================

### chmod系统调用

chmod系统调用可以改变文件或目录的访问权限

```
#include <sys/stat.h>
int chmod(const char *path, mode_t mode);
```

只有文件的属主和超级用户才拥有修改文件的权限

### chown系统调用

超级用户可以使用chown系统调用来改变一个文件的属主。
```
#include <sys/stat.h>
#include <unistd.h>
int chown(const char *path, uid_t owner, gid_t group);
```

### unlink,link和symlink系统调用

unlink系统调用删除一个文件的目录项并减少它的链接数，成功时返回0,失败返回-1。
如果向通过这个函数来删除文件，必须拥有该文件所属目录的写和执行权限。

```
#include <unistd.h>
int unlink(const char *path);
int link(const char *path1, const char *path2);
int symlink(const char *path1, const char *path2);
```

如果一个文件的链接数减少到0,并且没有进程打开它，这个文件就会被删除
    
先用open创建一个文件，然后对文件调用unlink，这是创建临时文件的技巧。这些文件在被打开的时候才能
被程序使用，当程序退出后并且文件关闭的时候它们就会被自动删除。

link系统调用将创建一个指向已有文件path1的新链接，新目录项由path2指出。
symlink系统调用以类似的方式创建符号链接。

### mkdir和rmdir系统调用

```
#include <sys/stat.h>
int mkdir(const char *path, mode_t mode);

#include <unistd.h>
int rmdir(const char *path);
```

### chdir系统调用和getcwd函数

chdir系统调用可以切换工作目录，getcwd函数来确定自己的当前工作目录。

```
#include <unist.h>
int chdir(const char *path);
char *getcwd(char *buf, size_t size);
```

getcwd函数把当前目录的名字写到给定的缓冲区buf里。如果目录名的长度超出了参数size给出的缓冲区长度，
如果成功，它返回指针buf，否则返回NULL。


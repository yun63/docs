Erlang Aplication
=================

Erlang/OTP中将完成特定功能的一组模块组织起来，称之为application。

### 1. 启动application

application:start(log4erl) 实际上是执行了application:start(log4erl, temporary).
第2个参数表示应用程序的启动类型(StartType)。启动类型有3种：
permanent -- 应用程序终止之后所有其他的应用程序和运行时系统都会被kill
transient -- 如果应用程序终止的原因是normal，那么这个消息会报出来但其他应用程序不会重启;
             如果应用程序终止的原因不是normal，那么其他应用程序和运行时也会死掉。
temporary -- 应用程序死掉会报错误出来但是其他应用程序不受影响。

### 2. application的配置文件

application的配置文件(Application Resource File)基本上确定了application的格局。
如果启动失败了就要检查一下配置文件了,配置文件命名要求必须与application命名一致,
即必须要有一个log4erl.app文件:
```
{application, log4erl,
[{description, "Logger for erlang in the spirit of Log4J"},
{vsn, "0.9.0"},
{modules, [
    console_appender, %%该配置节可以留空 []
    dummy_appender,
    email_msg,
    error_logger_log4erl_h,
    % ................省略部分模块
    xml_appender]},
{registered,[log4erl]}, %%这个应用程序将使用的注册名
{applications, [kernel,stdlib]}, %%注意这个配置节是指定当前应用程序依赖哪些应用程序
{mod, {log4erl,[]}},
{env,[{key,value},{k2,v2}]}, %% env配置节,里面以key-value的形式组织配置数据.可以用application:get_env/2读取.
{start_phases, []}
]}.
```

### 3. application的启动过程

Erlang运行时启动时，application controller进程会随着kernel应用程序启动，
在erlang shell中可以通过whereis(application_controller)找到它，应用程序相关的操作都是它来协调完成。
它通过application模块暴露出来的接口来实现用用程序的加载，卸载，启动，停止等等。

应用程序首先会load, 如果没有加载, application controller会首先执行load/1,加载完成后，
application controller会检查application配置文件中的applications配置节点中所列出的应用程序都已经在运行。
如果有依赖项还没有启动，就抛出{error, {not_started, App}}的错误。

完成依赖项检查之后，application controller会为application创建application master。 application master会成为该
application中所有进程的group leader。通过配置文件的mod配置节，application master知道要调用回调函数
log4erl:start/2

application behavior有两个回调函数必须实现start/2, stop/1分别指定应用程序如何启动，如何停止。
启动application的时候调用start方法，通过启动项层的supervisor来创建进程树。



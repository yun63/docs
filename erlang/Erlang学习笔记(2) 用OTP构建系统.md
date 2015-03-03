

用OTP构建系统
=======

##1. supervisor

监控树是一种由进程组成的树形结构,树的上级进程(监控器)监视着下级进程(工作器),如果下级进程挂了就会重启它们.

>Supervisor的基本思想就是通过建立层级结构实现错误隔离和管理,具体方法是通过重启的方式保持子进程一直活着.如果supervisor是进程树的一部分,它会被它的supervisor自动终止,当它的supervisor让它shutdown的时候,它会按照子进程启动顺序的逆序终止其所有的子进程,最后终止掉自己.重启的目的是让系统回归到一个稳定的状态,回归稳定状态后再出现异常可以进行重试,如果初始化都不稳定,后续的监控-重启策略意义不大.换句话说,Application初始化的阶段要有可靠性的保障,初始化阶段可能读取配置文件或者从数据库加载恢复数据,哪怕执行时间长一点都等待同步执行完.如果application依赖非本地数据库或外部服务就可以采取更快的异步启动,因为这种服务在正常使用过程中也经常出状况,早一点还是晚一点启动没有什么关系.

1. 重启策略
* one_for_one : 把子进程当成各自独立的,一个进程出现问题其它进程不会受到崩溃的进程的影响.该子进程死掉,只有这个进程会被重启
 * one_for_all : 如果子进程终止,所有其它子进程也都会被终止,然后所有进程都会被重启.
 * rest_for_one:如果一个子进程终止,在这个进程启动之后启动的进程都会被终止掉.然后终止掉的进程和连带关闭的进程都会被重启.
 * simple_one_for_one 是one_for_one的简化版 ,所有子进程都动态添加同一种进程的实例
 
 >**Note**
one-for-one维护了一个按照启动顺序排序的子进程列表,而simple_one_for_one 由于所有的子进程都是同样的(相同的MFA),使用的是字典来维护子进程信息.

2. worker的格式
```
{Tag, {Mod, Fun, ArgList},
		 Restart,
		 Shutdown,
		 Type,
		 [Mod1]}
```
* Tag
	原子类型的标签,将来可以用它来指代工作进程
* {Mod, Fun, ArgList}
	它定义了监控器用于启动工作器的函数,将被用作apply(Mod,Fun, ArgList)               的参数.
* Restart = permanent | transient | temporary
	permanent进程总是会被重启
	transient进程只有在以非正常退出终止时才会被重启
	temporary进程不会被重启
* Type = worker | supervisor
	被监控进程的类型.可以用监控进程代替工作进程来构建一个由监控器组成的树
* [Mod1]
	如果子进程是监控器或者gen_server行为的回调模块,就在这里制定回调模块名.

**start_child**:
```
@spec start_child(SupRef, ChildSpec) -> startchild_ret()
	SupRef::sup_ref()
	ChildSpec::child_spec() | (List::[term()])
	child_spec()::{Id::child_id(),
					StartFunc::mfargs(),
					Restart::restart(),
					Shutdown::shutdown(),
					Type::worker(),
					Modules::modules()}
	startchild_ret()::{ok, Child::child()} | {ok, Child::child(), Info::term()} 
```
start_child(SupRef, ChildSpec)动态地添加子进程到supervisor,并且按制定的策略ChildSpec启动子进程.
SupRef可以是
+ pid
+ Name, 如果supervisor在本地注册过
+ {Name, Node},如果supervisor在本地的另一个节点注册过
+ {global, Name},如果supervisor在全局注册
+ {via, Module, Name}, 如果supervisor通过可变进程注册

**terminate_child**:
```
@spec terminate_child(SupRef, Id) -> Result
	SupRef::sup_ref()
	Id::pid() | child_id()
	Result::ok | {error, Error}
	Error::not_found | simple_one_for_one
```
terminate_child(SupRef, Id)通知supervisor (SupRef)结束制定的子进程(Id)

**delete_child**:
delete_child(SupRef, Id) -> Result
通知supervisor删除指定的子进程, 子进程必须不出于运行状态, 如果运行可以使用terminate_child来停止它.

**restart_child**:
restart_child(SupRef, Id) -> Result.

**which_children**:
while_children(SupRef) -> [{Id, Child, Type, Modules}]
返回属于supervisor(SupRef)的子进程列表,在内存少的情况下可能引起内存越界的异常.

## 2. application
application必须导出start/2和stop/1函数.
``` 
start(_Type, StartArgs) ->
	xxx_sup:start_link(StartArgs).
stop(_State) ->
	ok.
```
	


		
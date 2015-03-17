gen_server
=========
 Erlang的OTP behaviour是对一些通用编程模式的抽象,在用Erlang 语言做开发时可以在behavior基础上快速构建出可用且可靠的功能.OTP behaviour包含gen_server gen_event gen_fsm supervisor.其中绝大多数情况下都是在使用gen_server,supervisor本身也是使用gen_server实现的.我们就以gen_server做为起点,逐步学习Erlang OTP.
 
> Behaviours are formalizations of these common patterns. The idea is to divide the code for a process in a generic part (a behaviour module) and a specific part (a callback module).

```
 -module(server_template).
 -export([start/1]).
 -export([call/2, cast/2]).
 -export([init/1]).

 %%通用进程模式
start(Mod) ->
    spawn(server_template, init, [Mod]).
    
init(Mod) ->
    register(Mod, self()),
    State = Mod:init(),
    loop(Mod, State).
   
loop(Mod, State) ->
    receive
        {call, From, Req} ->
            {Res, State2} = Mod:handle_call(Req, State),
            From ! {Mod, Res},
            loop(Mod, State2);
        {cast, Req} ->
            State2 = Mod:handle_cast(Req, State),
            loop(Mod, State2);
         stop ->   
             stop   
    end.
   
%% 接口部分  
call(Name, Req) ->
    Name ! {call, self(), Req},
    receive
        {Name, Res} ->
            Res
    end.
cast(Name, Req) ->
    Name ! {cast, Req},
    ok.
   
%% 接口部分  
call(Name, Req) ->
    Name ! {call, self(), Req},
    receive
        {Name, Res} ->
            Res
    end.
cast(Name, Req) ->
    Name ! {cast, Req},
    ok.
```
这样一个gen_server的代码骨架就出来了
## 编写gen_server回调模块的简要步骤

1. 确定回调模块名.
2. 编写接口函数.
3. 在回调模块里编写六个必要的回调函数.

    这真的**so easy**! 不要多想,只需按步骤行事!

---------

### 1. 确定回调模块名

我们将制作一个简单的银行支付系统,把这个模块成为my_bank(来自`<<Erlang程序设计(第二版)>>`)

### 2. 编写接口方法
我们将定义五个接口方法,它们都在my_bank模块里.

* **start()** 
	开启银行
* **stop()**
	关闭银行
* **new_account(Who)**
	创建一个新账户
* **deposit(Who, Amount)**
	存钱
* **withdraw(Who, Amount)**
	取钱(如果有结余的话)
每个函数都正好对应一个gen_server方法调用

*my_bank.erl*
```
start() ->
	gen_server:start_link({local, ?SERVER}, ?MODULE, [], []).
stop() ->
	gen_server:call(?MODULE, stop).
new_account(Who) ->
	gen_server:call(?MODULE, {new, Who}).
deposit(Who, Amount) ->
	gen_server:call(?MODULE, {add, Who, Amount}).
withdraw(Who, Amount) ->
	gen_server:call(?MODULE, {remove, Who, Amount}).
```

`gen_server:start_link({local, Name}, Mod, ...)`启动一个本地服务器.如果第一个参数是原子global, 它就会启动一个能被erlang节点集群访问的全服服务器.start_link的第二个参数是Mod, 也就是回调模块名.

`gen_server:call(?MODULE, Term)`用来对服务器进行远程过程调用.

### 3. 编写回调方法

gen_server的回调模块必须导出六个回调方法: 	

`init/1,handle_call/3,handle_cast/2,handle_info/2,terminate/3,code_change/3`.

>*gen_server_template.mini*

```
-module().
%% gen_server模板
-behaviour(gen_server).
-export([start_link/0]).
%% gen_server回调函数
-export([init/1, 
		 handle_call/3,
		 handle_info/2, 
		 terminate/2, 
		 code_change/3
		]).

start_link() ->
	gen_server:start_link({local, ?SERVER}, ?MODULE, [], []).

init([]) -> {ok, State}.

handle_call(_Request, _From, State) ->
	{reply, Reply, State}.
handle_cast(_Request, State) ->
	{noreply, State}.
handle_info(_Info, State) ->
	{noreply, State}.
terminate(_Reason, _State) ->
	ok.
code_change(_OldVsn, State, Extra) ->
	{ok, State}.
```

handle_call/3函数尤为重要.我们来编写代码,让它匹配接口方法定义的3中查询数据类型.

```
handle_call({new, Who}, From, State) ->
	Reply = ...
	State1 = ...
	{reply, Reply, State1};
hanle_call({add, Who, Amount}, From , State) ->
	Reply = ...
	State1 = ...
	{reply, Reply, State1};
handle_call({remove, Who, Amount}, From , State) ->
	Reply = ...
	State1 = ...
	{reply, Reply, State1};
```
其中,Reply值会作为远程过程调用的返回值发回客户端.
State只是一个代表服务器全局状态的变量,它会在服务器里到处传递.在银行模块里,这个状态永远不会发生变化,它只是一个ETS表的索引,属于常量.

>*my_bank.erl*

```
init([]) -> {ok, ets:new(?MODULE, [])}.
handle_call({new_Who}, _From, Tab) ->
	Reply = 
	case ets:lookup(Tab, Who) of
		[] -> 
			ets:insert(Tab, {Who, 0}),
			{welcome, Who};
		[_] ->
			{Who, you_already_are_a_customer}
	end,
	{reply, Reply, Tab};

handle_call({add, Who, X}, _From, Tab) ->
	Reply = 
	case ets:lookup(Tab, Who) of
		[] -> not_a_customer;
		[{Who, Balance}] ->
			NewBalance = Balance + X,
			ets:insert(Tab, {Who, NewBalance}),
			{thanks, Who, your_balance_is, NewBalance}
	end,
	{reply, Reply, Tab};

hanlde_call({remove, Who, X}, _From, Tab) ->
	Reply = 
	case ets:lookup(Tab, Who) of
		[] -> not_a_customer;
		[{Who, Balance}] when X =< Balance ->
			NewBalance = Balance - X,
			ets:insert(Tab, {Who, NewBalance}),
			{thanks, Who, your_balance_is, NewBalance}
		[{Who, Balance}] ->
			{sorry, Who, you_only_have, Balance}
	end,
	{reply, Reply, Tab};

handle_call(stop, _From, Tab) ->
	{stop, normal, stopped, Tab}.

handle_cast(_Msg, State) ->
	{noreply, State}.
handle_info(_Info, State) ->
	{noreply, State}.
terminate(_Reason, _State) ->
	ok.
code_change(_OldVsn, State, _Extra) ->
	{ok, State}.
```

+ 启动服务器的方法:

调用gen_server:start_link(Name, CallBackMod, StartArgs, Opts)来启动服务器,之后第一个被调用的回调模块方法是Mod:init(StartArgs),它必须返回{ok, State}.State的值作为handle_call的第三个参数重新出现.

+ 停止服务器的方法:

handle_call(stop, From, Tab)返回{stop, normal, stopped, Tab},它会停止服务器,第二个参数(normal)被用作my_bank:terminate/2的首个参数,第三个参数(stopped)会成为my_bank:stop()的返回值.

------

## gen_server的回调结构

### 1. 启动服务器

`gen_server:start_link(Name, Mod, InitArgs, Opts)`这个调用是所有事务的起点.
它会创建一个名为Name的通用服务器,回调模块是Mod, Opts则控制通用服务器的行为.在这里可以制定消息记录,函数调试和其他行为.通用服务器通过`Mod:init(InitArgs)`来启动.
```
@spec init(Args) -> 
	{ok, State} | 
	{ok, State, Timeout} | 
	ignore | 
	{stop, Reason}
init([]) -> 
	{ok, #state{}}.
```							
### 2. 调用服务器

gen_server:call(Name, Request)最终会调用回调模块里的handle_call/3.

```
@spec handle_call(Request, From, State) ->
		{reply, Reply, State} |
		{reply, Reply, State, Timeout} |
		{noreply, State} |
		{noreply, State, Timeout} |
		{stop, Reason, Reply, State} |
		{stop, Reason, State}
handle_call(Request, From, State) ->
	Reply = ...
	{reply, Reply, State}.
```	
Request(gen_server:call/2的第二个参数)作为handle_call/3的第三个参数重新出现,From是发送请求的客户端进程的Pid, State则是客户端的当前状态.
通常返回{reply, Reply, NewState}, Reply会返回客户端, 成为gen_server:call的返回值, 其他返回值({noreply, ...}和{stop, ...})相对不常用. noreply会让服务器继续工作,但客户端会等待一个回复,所以服务器必须把回复的任务委派给其他进程.

### 3. 调用和cast

gen_server:cast(Name, Msg)实现了一个cast, 也就是没有返回值的调用.

对应的回调方法是handle_cast
```
@spec handle_cast(Msg, State) ->
		{noreply, State} |
		{noreply, State, Timeout} |
		{stop, Reason, State}
handle_cast(_Msg, State) ->
	{noreply, State}.
```
这个处理函数通常只返回{noreply, NewState}或{stop, ...},前者改变服务器状态, 后者停止服务器.

### 4. 发给服务器的自发性消息

回调函数handle_info(Info, State)被用来处理发给服务器的自发性消息.

**Note:**
> 自发性消息是一切未经显式调用gen_server:call或gen_server:cast而到达服务器的消息

举个例子,如果服务连接到另一个进程并捕捉退出信号,就可能会突然收到一个预料之外的{'EXIT', Pid, What}消息.除此之外,系统里任何知道gen_server的Pid的进程都可以向它发送消息,这样的消息在服务器里表现为Info值.

```
@spec handle_info(Info, State) ->
		{noreply, State} |
		{noreply, State, Timeout} |
		{stop, Reason, State}
handle_info(_Info, State) ->
		{noreply, State}
```
返回值和handle_cast相同.

### 5. terminate

服务器会因为许多原因终止.handle_开头的函数也许会返回一个{stop, Reson, NewState},服务器也可能奔溃并生成{'EXIT', Reason},在所有的情况下,无论它们是怎样发生的, 都会调用terminate(Reason, NewState).

```
@spec terminate(Reason, State) -> void()
terminate(_Reason, _State) ->
	ok.
```
### 6. 代码更改

你可以在服务器运行时动态更改它的状态,这个回调函数会在系统执行软件升级时由版本处理子系统调用.

```
@spec code_change(OldVsn, State, Extra) -> {ok, NewState}
code_change(_OldVsn, State, _Extra) ->
	{ok, State}.
```

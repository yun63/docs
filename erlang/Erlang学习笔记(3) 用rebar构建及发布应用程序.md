
用 rebar 来构建、编译、测试、发布 Erlang 应用程序
=================================================

rebar 是一个遵循 Erlang/OTP 原则的 Erlang 项目构建工具，使用它可以减少构建标准 Erlang/OTP 项目架构配置的工作量，
并且可以很容易的编译、测试、发布 Erlang 应用程序。更强大的是，rebar 提供一种依赖管理机制，
它可以使开发者很方便地通过 Git、Hg 等方式重用常见的第三方 Erlang 模块或库。

## 用rebar构建项目

创建一个名为rebarapp的文件夹

```
$ mkdir rebarapp
$ cd rebarapp
```
创建名为rebarapp项目:
`$ rebar create-app appid=rebarapp`

rebar 会根据默认模板（template）在当前目录下生成一个 src 文件夹，里面包含下面3个文件：
rebarapp.app.src 应用的资源描述文件，影响后面编译生成的 rebarapp.app 里的内容
rebarapp_app.erl 应用的 Application Behaviour 代码文件
rebarapp_sup.erl 应用的 Supervisor Behaviour 代码文件

rebar 还内置了 gen_server、gen_fsm、application 等 Erlang/OTP 行为模式的模板，可以自动生成这些行为模式的框架代码。
这里以 gen_server为例,给应用添加一个名为 rebarapp_server 的 gen_server 行为模式。在应用根目录执行以下命令：

`$ rebar create template=simplesrv srvid=rebarapp_server`

执行完后自动会在 src 文件夹里生成一个 rebarapp_server.erl 的 gen_server 框架格式的文件，
simplesrv 是 gen_server 模板的名称(gen_fsm、application对应的是simplefsm、simpleapp)，srvid 则是
该 gen_server 模板的ID（gen_fsm、application对应的是fsmid、appid）。

为了测试，这里对 rebarapp_server.erl 进行修改，export 一个 hello 方法，并添加一个 cast 的消息输出，
修改后的 rebarapp_server.erl 文件内容如下：

```
-module(rebarapp_server).
-behaviour(gen_server).
-define(SERVER, ?MODULE).
 
%% ------------------------------------------------------------------
%% API Function Exports
%% ------------------------------------------------------------------
 
-export([start_link/0, hello/0]).
 
%% ------------------------------------------------------------------
%% gen_server Function Exports
%% ------------------------------------------------------------------
 
-export([init/1, handle_call/3, handle_cast/2, handle_info/2,
         terminate/2, code_change/3]).
 
%% ------------------------------------------------------------------
%% API Function Definitions
%% ------------------------------------------------------------------
 
start_link() ->
    gen_server:start_link({local, ?SERVER}, ?MODULE, [], []).
 
%% @doc just a test
hello() ->
    gen_server:cast(?SERVER, 'HELLO').
 
%% ------------------------------------------------------------------
%% gen_server Function Definitions
%% ------------------------------------------------------------------
 
init(Args) ->
    {ok, Args}.
 
handle_call(_Request, _From, State) ->
    {reply, ok, State}.
 
handle_cast('HELLO', State) ->
    io:format("Hello World!~n"),
    {noreply, State};
 
handle_cast(_Msg, State) ->
    {noreply, State}.
 
handle_info(_Info, State) ->
    {noreply, State}.
 
terminate(_Reason, _State) ->
    ok.
 
code_change(_OldVsn, State, _Extra) ->
    {ok, State}.
 
%% ------------------------------------------------------------------
%% Internal Function Definitions
%% ------------------------------------------------------------------
```

修改 rebarapp_sup.erl 的 init 函数，把 rebarapp_server 作为应用管理者 rebarapp_sup 的工作进程启动，修改如下：
```
init([]) ->
    RebarappServer = ?CHILD(rebarapp_server, worker),
    {ok, {{one_for_one, 5, 10}, [RebarappServer]} }.
```

## 编译项目

`$ rebar compile`
编译完后，会在根目录下生成一个 ebin 的文件夹，里面存放的是该应用的资源文件 rebarapp.app 和应用的 beam 文件，
也可以执行以下命令对编译生成的应用文件进行清理：
`rebar clean`

## 使用rebar生成文档

`rebar doc`

命令执行完后，会在根目录生成一个 doc 的文件夹，打开里面的 index.html 就可以很直观地看到该应用的模块 API 概览。

## eunit测试

rebar 会根据一个名为 rebar.config 的文件里的 eunit 配置选项来对应用进行测试，rebar.config 详细地配置选项信息可以
查看官方上的 rebar.config.sample。在应用的根目录下创建一个 rebar.config，填入以下内容：

```
%%-*- mode: erlang -*-
 
%% Erlang compiler options
{erl_opts, [debug_info,
            {i, "test"},
            {src_dirs, ["src"]}]}.
 
{eunit_opts, [verbose, {report, {eunit_surefire, [{dir, "."}]}}]}.
 
{cover_enabled, true}.
```
上面的配置将会加载根目录下的 test 文件夹里的文件，所以需要在根目录下创建一个 test 文件夹

`$ mkdir -p test`

这里 test 文件夹将存放 eunit 的测试用例，在 test 文件夹里新建一个名为 rebarapp_test.hrl 的测试用例文件，内容如下：
```
-include_lib("eunit/include/eunit.hrl").
 
 
my_test() ->
    ?assert(1 + 2 =:= 3).
 
simple_test() ->
    ok = application:start(rebarapp),
    ?assertNot(undefined =:= whereis(rebarapp_sup)).
```
然后在 rebarapp_server.erl 的文件末尾加上以下测试代码：
```
-ifdef(TEST).
-include("rebarapp_test.hrl").
-endif.
```
当然，如果有必要的话也可以在每个模块文件上加上面测试代码。执行以下命令进行 eunit 测试：
`$ rebar compile eunit`
如果应用文件没什么变化修改，也可以直接运行 "rebar eunit"。这时终端出现以下类似显示，则 eunit 测试完成：
```
==> rebarapp (eunit)
======================== EUnit ========================
module 'rebarapp_app'
module 'rebarapp_server'
  rebarapp_server: my_test...ok
  rebarapp_server: simple_test...[0.014 s] ok
  [done in 0.019 s]
module 'rebarapp_sup'
=======================================================
  All 2 tests passed.
Cover analysis: /Users/dengjoe/erlang/rebarapp/.eunit/index.html
```
可以打开根目录下的.eunit/index.html 查看测试报告。

很多linux程序员喜欢使用Makefile,当然用Makefile包装一下rebar也是一个不错的选择
```
.PHONY: deps doc clean                                                                                                  
                                                                                                                        
all: deps compile                                                                                                       
                                                                                                                        
# 获取OTP项目                                                                                                           
deps:                                                                                                                   
    ./rebar get-deps                                                                                                    
                                                                                                                        
# 编译相关项目,在编译之前先查看依赖项目是否已经存在                                                                     
compile:deps                                                                                                            
    ./rebar compile                                                                                                     
                                                                                                                        
clean:                                                                                                                  
    ./rebar clean                                                                                                       
                                                                                                                        
# 清楚依赖项目                                                                                                          
distclean: clean                                                                                                        
    ./rebar delete-deps                                                                                                 
                                                                                                                        
# 测试所有项目                                                                                                          
_test:                                                                                                                  
    ./rebar eunit                                                                                                       
                                                                                                                        
dialyzer: compile                                                                                                       
    @dialyzer -c ebin                                                                                                   
                                                                                                                        
doc:                                                                                                                    
    @./rebar doc skip_deps=true                                                                                         
                                                                                                                        
release:                                                                                                                
    @./rebar generate                 
```

## 发布应用

在应用程序根目录下创建一个名为rel的目录,用来作为应用发布的文件夹

```
$ mkdir -p rel
$ cd rel
```

在当前rel文件夹里创建一个rebarapp的独立的ErlangVM节点:
`$ rebar create-node nodeid=rebarapp`
修改rel/reltool.config里的lib_dirs的值,默认是一个"[]",改为应用所在的目录路径["../../"],不然到后面编译发不是会报错,
修改后的reltool.config配置内容如下所示:
```
```

返回应用的根目录,在rebar.config加上以下一行,把新建的rel文件夹放到rebar可访问的子文件夹里,作为应用内容发布文件夹:
{sub_dirs, ["rel"]}
再重新编译下应用rebarapp
`$ rebar compile`
如果没有报错,应用程序就可以发布了
`$ rebar generate`
在终端上看到"==> rel(generate)"且没有报错,应用rebarapp发布成功,并在rel/rebarapp/bin目录下生成一个用来启动应用或者停止应用
等操作的shell文件rebarapp.

ok,到这里,应用程序发布就结束了.

## 版本升级


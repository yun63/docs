
git基础操作
=============

## 对比差异

* git diff显示还没有暂存起来的改动,而不是当前工作和上次提交之间的差异
* git diff --staged查看已经暂存起来的文件和上次提交时的快照之间的差异

## 提交更新

跳过使用暂存区域:git commit -a

## 移除文件

git rm

* 如果删除之前修改过并且已经放到暂存区域的话,则必须要用强制删除选项-f,以防误删文件后丢失修改的内容
* 如果想把文件从暂存区域移除,但仍然希望保留在当前工作目录中,用--cached选项

## 移动文件

git mv README README.md =>

> mv README README.md
> git rm README
> git add README.md

## 查看提交历史

git log

* 有用的log

    git log -n
    git log --graphy
    git log --author="yun63"
    git log --since=2.years 
    (git log --since="2008-01-02")
    (git log --since="10 years 2 months 1 day 3 hours ago")
    git log --pretty=format:"----"

## 取消已经暂存的文件

git reset HEAD filename 可以将filename文件从暂存区域里移除


## 取消对文件的修改

git checkout filename

> 任何已经提交到Git的都可以被恢复,即便是已经删除的分支中的提交










远程仓库的使用
=============

## 查看当前的远程仓库

git remote 命令会列出每个远程仓库的简短名字, 在克隆玩某个项目后,至少可以看到一个名为origin的远程仓库,
Git默认使用这个名字来标识你所克隆的原始仓库

也可以加上-v选项,显示对应的克隆地址

只有origin用的是SSH URL链接,所以也只有这个仓库可以推送数据上去?

## 添加远程仓库

git remote add [shortname] [url]

eg:

```
git remote add pb git://github.com/paulboone/ticgit.git
git remote -v

origin git://github.com/schacon/ticgit.git
pb git://github.com/paulboone/ticgit.git
```

现在可以用pb来只带对应的仓库地址了. 比如说,要抓取Paul有的,但本地仓库没有的信息,可以运行`git fetch pb`
现在,Paul的分支(master)已经完全可以在本地访问了,对应的名字是`pb/master`, 你可以将它合并到自己的某个分支,或者切换到这个分支,
看看有些什么有趣的更新.

## 从远程仓库抓取数据

git fetch [remote-name]

此命令会到远程仓库中拉去所有你本地仓库中还没有的数据,运行完成后,你就可以在本地访问远程仓库的所有分支,将其中某个分支合并到本地,
或者只是取出某个分支,一探究竟.

注意,fetch命令只是将远程的数据拉到本地仓库,并不自动合并到当前分支,只有确实准备好了,才能手动合并.

如果设置了某个分支用于跟踪某个远程仓库的分支,可以使用git pull命令自动抓取数据下来,然后将远程分支自动合并到本地仓库中当前分支.

## 推送数据到远程分支

git push [remote-name][branch-name]

如果要把本地的master分支推送到origin分支服务器上, 运行:
`git push origin master`

只有在所克隆的服务器上有写权限,或者同一时刻没有其他人在推送数据,这条命令才会如期完成. 如果在你推送数据之前,已经有其他人推送了
若干更新,那你的推送操作就会被驳回.你必须把他们的更新抓取到本地,并到自己的项目中,然后才可以再次推送.

## 查看远程仓库信息

git remote show [remote-name]

eg:
`git remote show origin`

## 远程仓库的删除与重命名

`git remote rename`命令可以修改某个远程仓库的名称

eg:
`git remote rename pb paul`把远程仓库名称由pb重命名为paul

注意,对远程仓库的重命名,也会是对应的分支名称发生变化,原来的pb/master分支现在成了paul/master

`git remote rm`命令可以删除对应的远程仓库


## 打标签

1. 列出现在所有的标签`git tag`

    `git tag -l 'v1.4.2.*'`命令可以列出所有1.4.2系列的版本的tag

2. 新建标签

    Git使用的标签有两种类型: 轻量级的和含附注的

    * 含附注的标签

        创建一个含附注的标签: git tag -a v1.4 -m "version 1.4"

    * git show可以查看响应标签的版本信息

    * 签署标签

        如果你有私钥,可以用GPG来签署标签,只需要把之前的-a改为-s即可

        `git tag -s v1.5 -m "version 1.5 tag"`

    * 轻量级标签

        轻量级标签实际上就是一个保存着对应提交对象的检验和信息的文件,创建这样的标签`git tag tagname`即可

    * 验证标签

        可以使用git tag -v [tag-name]的方式来验证已经签署的标签,次命令会调用GPG来验证签名,必须有签署者的公钥,存放在keyring中才能验证

    * 分享标签

        默认情况下,git push并不会把标签传送的远程服务器上,只有通过显示命令才能分享标签到远程仓库
        `git push origin [tag-name]`

    



Git分支管理
===================

## 新建分支

`git branch [branch-name]`

这会在当前commit对象上新建一个分支指针

## 切换分支

`git checkout [branch-name]`

> 由于Git中的分支实际上仅是一个包含所指对象校验和(40个字符长度SHA-1字符串)的文件,所以创建和销毁一个分支就变得非常廉价.
> 说白了,新建一个分支就是向一个文件写入41个字节那么简单,当然也就很快了.
> 这和大多数版本控制系统形成了鲜明的对比,它们管理分支大多采用备份所有项目文件到特定目录的方式,所以根据项目文件数量和大小
> 不同,可能花费的时间也会有相当大的差别,而Git的实现与项目复杂度无关,它永远可以在几毫秒的时间内完成分支的创建和切换.

## 基本的分支与合并

看一个简单的分支与合并的例子,基本流程:

1. 开发某个网站
2. 为实现某个新的需求,创建一个分支
3. 在这个分支上开展工作

---------------------------

假设此时,你突然接到一个电话说有个很严重的问题需要紧急修复,那么可以按照下面的方式处理:

1. 返回到原先已经发布到生产服务器上的分支
2. 为这次紧急修复建立一个新分支
3. 测试通过后,将此修复分支合并,再推送到生产服务器上
4. 切换到之前实现新需求的分支,继续工作

## 冲突的合并

如果修改了两个待合并分支里同一个文件的同一部分,Git就无法干净地把两者合并到一起,这样Git做了合并,但没有提交,它会停止下来等待
冲突的解决,`git status`可以查看那些冲突.
手动解决完冲突后,`git add`命令暂存(意味着冲突已经解决), `git commit`提交后完成了合并.

## 分支管理

`git branch`命令不仅仅能创建和删除分支, 如果不加任何参数,它会列出当前所有分支的清单

```
git branch
 iss53
 * master
 testing
```

`git branch --merge`可以查看哪些分支已被合并入当前分支
`git branch --no-merged`可以查看尚未合并的工作
当有未合并的工作时, `git branch -d`删除该分支会导致失败,不过你如果坚信要删除它,git branch -D [branch-name]会强制删除它.

## 远程分支

> 远程分支是对远程仓库状态的索引.它们是一些无法移动的本地分支;只有在Git的网络活动时才会更新.
> 远程分支就像是书签,提醒开发者上次连接远程仓库时上面个分支的位置.

> 用(远程仓库名)/(分支名)这样的形式标示远程分支.比如,我们想看上次同origin仓库通讯时master的样子,就应该查看orgin/master分支.

**Note:**
> 如果你和同伴一起修复某个问题，但他们先推送了一个 iss53 分支到远程仓库，虽然你可能也有一个本地的iss53 分支，
> 但指向服务器上最新更新的却应该是 origin/iss53 分支

> 可能有点乱，我们不妨举例说明。假设你们团队有个地址为 git.ourcompany.com 的 Git服务器。如果你从这里克隆，Git会自动为你
> 将此远程仓库命名为 origin，并下载其中所有的数据，建立一个指向它的 master分支的指针，在本地命名为 origin/master，但你无
> 法在本地更改其数据。接着，Git 建立一个属于你自己的本地 master 分支，始于 origin上master分支相同的位置,你可以就此开始工作.

一次git clone会建立你自己的的本地master分支和远程origin/master分支,它们都指向origin/master分支的最后一次提交.
`git fetch origin`进行同步,该命令首先找到origin是哪个服务器,从上面获取你尚未拥有的数据,更新本地数据库,然后把
origin/master的指针移动到它最新的位置.

## 推送

要想和其他人分享某个分支,你需要把它推送到一个你拥有写权限的远程仓库,你的本地分支不会被自动同步到你引入的远程分支中,除非
你明确执行推送操作.

> 如果你有个叫serverfix的分支需要和他人一起开发,可以运行git push (远程仓库名) (分支名)

```
$ git push origin serverfix
 * [new branch] serverfix -> serverfix
```
也可以运行git push origin serverfix:serverfix来实现相同的效果,"提取我的serverfix并更新到远程仓库的serverfix"
若想把远程分支叫作awesomebranch,可以用push origin serverfix:awesomebranch来推送数据.
 `**git push [远程仓库] [本地分支]:[远程分支]**`

接下来,当你的协作者再次从服务器上拉取数据时,他们将得到一个新的远程分支
```
$ git fetch origin
 * [new branch] serverfix   -> origin/serverfix
```
> **Note**:
> 在fetch操作抓来新的远程分支之后,你仍然无法在本地编辑该远程仓库,换句话说,在本例中,你不会有一个新的serverfix分支,有的
> 只是一个你无法移动的origin/serverfix指针.
> 如果要把该内容合并到当前分支,可以运行 `git merge origin/serverfix`.
> 如果想要一份自己的serverfix来开发,可以在远程分支的基础上分化出一个新的分支来:
>> $ git checkout -b serverfix origin/serverfix
> 这会切换到新建的serverfix**本地分支**,其内容和远程分支origin/serverfix一致,你可以在里面继续开发了.

## 跟踪分支

> 从远程分支检出的本地分支称为跟踪分支.跟踪分支是一种和远程分支有直接联系的本地分支
在克隆仓库时,Git通常会自动创建一个master分支来跟踪orgin/master,这这是git push和git pull一开始就能正常工作的原因.

## 删除远程分支

如果不再需要某个远程分支了,比如搞定了某个特性并把它合并进了远程的master分支(或任何其他存放稳定代码的地方),可以用
`git push [远程名] :[分支名]`来删除它.
```
$ git push origin :serverfix
 - [deleted]    serverfix
```
> 记忆方法: 远程推送命令`git push [远程仓库] [本地分支]:[远程分支]`省略[本地分支],也就是说"在这里提取空白然后把它变成[远程分支]"

## 衍合

把一个分支整合到另一个分支的办法有两种: merge(合并)和rebase(衍合)

1. 衍合基础

    merge的原理是把两个分支的最新快照以及二者最新的共同祖先进行三方合并.

    rebase的原理是回到两个分支的共同祖先,提取你所在分支每次提交时产生的diff,把这些diff分别保存到临时文件里,然后给需要衍合的分支依次打diff补丁.
    
2. 更多有趣的衍合

    你还可以在衍合分支以外的地方合并

    `git rebase --onto master server client`

    检出client分支,找出client和server分支的共同祖先之后的变化,然后把它们在master分支上重演一遍"

    `git checkout master`

    `git merge client`

    这样就把client分支的修改合并到主线中了.

    现在你决定把server分支的变化也包含进来,可以直接把server分支衍合到master分支而不用手工转到server分支再衍合.

    `git rebase [主分支] [特性分支]`命令会先检出特性分支server,然后在master分支上重演.

    ```
    $ git rebase master server

    $ git checkout master

    $ git merge master server
    ```

    现在client和server分支的变化都被整合了,可以删除掉它们了`git branch -d client server`

3. 衍合的风险

    **Warning**:

    > 永远不要衍合那些已经推送到公共仓库的更新

    > 如果你遵循这条金科玉律,就不会出差错.否则,人民群众会仇恨你,你的朋友和家人也会嘲笑你,唾弃你.

    如果把衍合当成一种在推送之前清理提交历史的手段，而且仅仅衍合那些永远不会公开的commit，那就不会有任何问题。
    如果衍合那些已经公开的 commit，而与此同时其他人已经用这些 commit 进行了后续的开发工作，那你有得麻烦了。



--------------

服务器上的Git
=============

## 协议

### 1. 本地协议

最基础的协议, 远程仓库在该协议中就是硬盘上的一个目录,可以用指向该仓库的路径作为URL.

`$ git clone /opt/git/project.git`
或者这样,
`$ git clone file:///opt/git/project.git`
使用路径会尝试使用硬链接或者直接复制它需要的文件,file://会通过网络来传输数据,效率相对低下.

添加本地仓库到现有的git工程
`$ git remote add local_proj /opt/git/project.git`

这种方式简单快速,但从不同的位置访问的共享权限难以架设,而且安全性不高.


### 2. SSH协议

最常见的传输协议,ssh也是唯一一个同时便于读写操作的网络协议,http和git协议通常都是只读的,ssh同时也是一个验证授权的网络协议
通过ssh克隆一个git仓库,可以使用
`$ git clone ssh://user@server:project.git`
或者不指明某个协议,这时Git会默认使用ssh:
`$ git clone user@server:project.git`

### 3. Git协议

该协议是一个包含在Git软件包中的特殊的守护进程,它会监听一个提供类似于ssh服务的特定端口(9418),而无需任何授权,
用git协议运行仓库,需要创建git-export-daemon-ok文件,它是协议进程提供仓库服务的必要条件,但除此之外该服务没有任何安全措施.
要么任何人都能克隆Git仓库,要么谁也不能.
该协议通常也不能用来进行推送.

git协议是最快的传输协议,如果你在提供一个有很大访问量的公共项目,或者一个不需要对读操作进行授权的庞大项目,假设一个git守护进程
来供应仓库是个不错的选择(开源项目github)

### 4. http协议

http协议的优美之处在于假设的便捷性.只需要把git的纯仓库放在http的文件根目录下,配置一个特定的post-update挂钩(hook)就搞定了.
从此,每个能访问git仓库所在服务器上的web服务的人都可以进行克隆操作.

```
$ cd /var/www/htdocs/
$ git clone --bare /path/to/git_project gitproject.git
$ cd gitproject.git
$ mv hooks/post-update.sample hooks/post-update
$ chmod a+x hooks/post-update
```
这样就ok了,其他人几可以用下面的命令来克隆仓库
`$ git clone http://example.com/gitproject.git`


## 分布式Git

### 1. 合并流程:

> 一般最简单的情形,是在master分支中维护稳定代码,然后在特性分支上开发新功能,或是审核测试别人贡献的代码,接着将它并入主干,
> 然后删除这个特性分支,如此反复.

这是最简单的流程,在处理一些大型项目可能会有问题.

对于大型项目,至少需要维护两个长期分支master和develop. 特性分支中的新代码将首先并入develop分支,经过一个阶段,确认develop中
的代码已稳定到可发行时,再将master分支快进到稳定点.而平时这两个分支都会被推送到公开的代码库.

这样,在人们克隆仓库时就有两种选择:既可检出最新稳定版本,确保正常使用;也能检出开发版本,试用最前沿的新特性.

### 2. 衍合与挑拣(cherry-pick)的流程

衍合或者挑拣贡献者的代码,而不是简单的合并,因为这样能够保持线性的提交历史.
如果你完成了一个特性的开发,并决定将它引入到主干代码中,你可以转到那个特性分支然后执行衍合命令,好在你的主干分支上重新提交这些修改,
如果这些代码工作得很好,你就可以快进master分支,得到一个线性的提交历史.


另一个引入代码的方式是挑拣.挑拣类似于针对某次特定提交的衍合.它首先提取某次提交的补丁,燃火试着应用在当前分支上.如果某个特性分支上有多个
commits,但你只想引入其中之一就可以使用这种方法,假设你有一个类似图1的工程

**图1**:

![image] (./res/挑拣之前的历史.png)

如果你想拉取e43a6到你的主干分支,可以这样:

`$ git cherry-pick e43a6fd3e94888d76779ad79fb568ed180e5fcdf`

这将会引入e43a6的代码,现在你的历史看起来想图2

**图2**:

![image] (./res/挑拣之后的历史.png)

现在,你可以删除这个特性分支并丢弃你不想引入的那些commit.







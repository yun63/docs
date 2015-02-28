
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
现在,Paul的猪肝分支(master)已经完全可以在本地访问了,对应的名字是`pb/master`, 你可以将它合并到自己的某个分支,或者切换到这个分支,
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
 `**git push origin [远程仓库] [本地分支]:[远程分支]**`

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
3. 衍合的风险





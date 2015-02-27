
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

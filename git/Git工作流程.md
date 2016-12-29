
介绍基于Git 两种协作开发模式 -- GitHub Flow & Git Flow
===================================================

对于Github 一些好用的特殊操作技巧 ，可以见[GitHub 特殊操作技巧 和Git的基本操作](http://www.cnblogs.com/sloong/p/5857303.html)

## 一 GitHub Flow

GitHub Flow —— **以部署为中心的开发模式**,通过简单的功能和规则，**持续**且**高速****安全**地进行部署。在实际开发中往往一天之内会实施几十次部署，而支撑这一切的，就是足够简单的开发流程以及完全的自动化。

![](http://images2015.cnblogs.com/blog/718344/201609/718344-20160913141424383-612008280.png)

GitHub Flow **特点**：

1.  **令master 分支时常保持可以部署的状态**
2.  进行新的作业时要从master 分支创建新的分支，新分支名称要具有描述性
3.  在`2`新建的本地仓库分支中进行提交
4.  在Github 端仓库创建同名分支，定期push
5.  需要帮助、反馈，或者branch已经准备merging时，创建Pull Request，以Pull Request 进行交流
6.  **让其他开发者进行审查**，确认作业完成后与master分支进行合并（合并的代码一定要测试
7.  与master分支合并后，立刻部署

使用Github Flow 的**前提条件**：

*   团队规模最好控制在15-20人之内，具体见 [how-github-works](http://zachholman.com/posts/how-github-works/)
*   部署作业完全自动化。必须自动化，一天之类需要多次部署
    *   使用部署工具（Capistrano，Mina，Fabric,Webistrano,Strano等），让部署时所需的一系列流程自动化。
    *   通过Web界面进行部署，Capistrano 等部署工具需要命令执行操作，开发者以外的人很难实施部署
        *   Capistrano [http://github.com/capistrano/capistrano](http://github.com/capistrano/capistrano) //Ruby开发的代表性部署工具
        *   Webistrano [http://kentaro/webistrano](http://kentaro/webistrano) //可以通过Web执行Capistrano的工具
    *   导入开发时注意事项：随着团队人数的增多及成熟度的提高，开发速度会越来越快。往往一个部署尚未完成，另一名开发者就已经处理完下一个pull request，开始实施下一个部署。在这种情况下，一旦正式环境出现问题，很难分辨哪个部署造成了影响。为了应对该情况，建议在部署实施过程中通过工具加锁。
    *   Git Hook 自动部署
*   重视测试
    *   让测试自动化
    *   编写测试代码，通过全部测试
    *   维护测试代码

![](http://images2015.cnblogs.com/blog/718344/201609/718344-20160913141504539-629430807.png)

## 二 Git Flow

荷兰程序员 Vincent Driessen 曾发表了一篇[博客](http://nvie.com/posts/a-successful-git-branching-model/)，让一个分支策略广为人知。具体流程见下图（引用该博客的一幅图片）

![](http://images2015.cnblogs.com/blog/718344/201609/718344-20160913141526648-581574208.png)

这一流程最大的亮点是考虑了紧急Bug的应对措施，整个流程显得过于复杂，所以在实施该方案前，需要对整个开发流程进行系统的学习。也需要借助Git flow 等工具的辅助。

下面根据上图，按不同分支 进行 说明：

### master 分支和 develop分支

在Git Flow 中，这两个分支至关重要，它们会贯彻整个流程始终，绝对不会被删除。

**master 分支**

master 分支时常保持着软件可以正常运行的状态。由于要维护这一状态，所以不允许开发者直接对master 分支的代码进行修改和提交。

其他分支的开发工作进展到可以发布的程度后，将会与master分支进行合并，并且这一合并只在发布成品时进行。发布时将会附加版本编号的Git标签。

**develop分支**

develop分支是开发过程中代码中心分支。与master 分支一样，这个分支也不允许开发者直接进行修改和提交。

程序员要以develop分支为起点新建feature 分支，在feature 分支中进行新功能的开发或者代码的修正。也就是说develop分支维系着开发过程中的最新代码，以便程序员创建feature分支进行自己的工作。

### 在feature 中工作

feature 分支以develop分支为起点，是开发者直接更改代码发送提交的分支。开发流程：

1.  从develop分支创建feature分支
2.  从feature分支中实现目标功能
3.  通过Github 向develop发送pull request
4.  接受其他开发者审核后，将Pull Request**合并至develop分支**

具体指令：

    $ git checkout develop
    $ git pull
    $ git flow feature start add-user //add branch feature/add-user
    $ git branch
    // feature/add user  start commit commit ....
    $ git push orgin feature/add-user
    //到github 上去代码审查，切到develop分支，进行pull request 
    $ git checkout develop
    $ git pull // 当feature/add-user 合并到 develop后，本地develop 需要更新到最新状态

注意，默认状态是pull request 到master。这时需要手动切换到develop分支，再进行pull Request 操作。

如果采用该开发策略，那么可以在setting 中 Option 中，修改Default Branch 为 develop ，这样就省去了手动修改的麻烦。

与develop分支合并后，已经完成工作的feature分支可以在适当的时机删除

![](http://images2015.cnblogs.com/blog/718344/201609/718344-20160913141549133-898273999.png)

### 更新本地的develop分支

我们发送的pull request 在github 端与develop 合并后，为了让其反应到本地的develop分支中，我们需要进行以下操作：

*   切换到develop分支
*   执行git pull (fetch & merge)

每当需要从develop分支创建feature等分支时，记得一定要先执行上述操作，保证develop分支处于最新状态。

### release分支

**创建 release分支 **，在这个分支，我们**只处理与发布前准备相关的提交**，比如版本编号变更的元数据的添加工作。如果软件部署到预演环境后测试出bug，相关修正也要提交到这个分支。

注意：该分支绝对不能包含需求变更或者功能变更等重大修正。这一阶段的提交数应该限制到最低。

    $ git checkout develop
    $ git pull
    $ git flow release start '1.0.0'

当所有修正处理完后，我们结束这分支

    $ git flow release finish '1.0.0'
    //期间会需要填写 提交信息、这个版本的提交信息、合并的提交信息。无特殊情况，一般默认。

全部结束后，会显示如下

    $ git flow release finish '1.0.0'
    Switched to branch 'master'
    Your branch is up-to-date with 'origin/master'.
    Merge made by the 'recursive' strategy.
     README.md | 2 ++
     1 file changed, 2 insertions(+)
    Switched to branch 'develop'
    Your branch is up-to-date with 'origin/develop'.
    Already up-to-date!
    Merge made by the 'recursive' strategy.
    Deleted branch release/1.0.0 (was d3f54a0).

    Summary of actions:
    - Release branch 'release/1.0.0' has been merged into 'master'
    - The release was tagged '1.0.0'
    - Release tag '1.0.0' has been back-merged into 'develop'
    - Release branch 'release/1.0.0' has been locally deleted
    - You are now on branch 'develop'

**查看版本tag**

通过前面一系列的操作，我们创建了与发布版本号相同的Git标签

    $ git tag
    1.0.0

**更新到远程仓库**

对此，我们对多个分支进行了修改，所以需要利用push操作将修改更新到Github端的远程仓库。先从develop开始

    $ git push origin develop

然后是master

    $ git checkout master
    $ git push origin master

再push 标签信息

    $ git push --tags

这样版本号 1.0.0 的标签信息就已经push 完成

### 在hotfix 分支下进行工作

下述情况需要创建 hotfix 分支

*   release 版本中发现了bug 或者漏洞
*   develop 分支正在开发新功能，无法面向用户进行发布
*   漏洞需要及早处理，无法等到下一次版本发布

假设修复BUG 后的版本至 1.0.1

    $ git fetch origin

现在以1.0.0的标签信息为起点，创建名为1.0.1 的hotfix分支。

    $ git flow hotfix start '1.0.1' '1.0.0'

修复工作结束后，将hotfix 分支push 到github端的远程仓库，并向master分支发起Pull Request

    $ git push origin hotfix/1.0.1

![](http://images2015.cnblogs.com/blog/718344/201609/718344-20160913141605398-1076219753.png)

**创建标签和进行发布**

在Github项目主页，点击release ，为本次hotfix 创建1.0.1标签。点击 Draft a new release 按钮，输入相关标签信息，在Target中指定master分支（master分支已经合并了hotfix1.0.1的修改）。然后填写相关信息，点击Publish release 进行发布

1.0.1发布后，之前发布的成品也就完成了生命周期

    $ git fetch origin

**从 hotfix 分支合并到develop 分支**

登录到Github，从hotfix1.0.1分支向develop分支发送Pull Request即可。审查后便会被合并到develop分支

### Git Flow 的小结

建议把开发流程图放大贴在墙上，这样能够有效帮助团队成员理解流程内容

版本号的分配规则 x.y.z

x: 在重大功能变更，或者版本不向下兼容+1，此时y z归零

y: 在添加新功能或者删除已有功能+1 此时z归零



Vim 中使用 OmniComplete 为 C/C++ 自动补全
=====

OmniComplete 并不是插件的名字，而是 Vim 众多补全方式中的一种（全能补全）。
说白了 OmniComplete 其实就是根据光标前的内容猜测光标后的内容，具体怎么猜取决于所采用的脚本。

而 OmniCppComplete 就是专为 C/C++ 编写的 OmniComplete 一个补全脚本。

------------

## 准备索引文件

以生成 C++ 标准库索引文件为例：

1. 下载专为 Ctags 修改过的 [libstdc++头文件](http://www.vim.org/scripts/script.php?script_id=2358)

2. uppack

3. ctags -R --c++-kinds=+p --fields=+iaS --extra=+q --language-force=C++ cpp_src

4. 在.vimrc配置里, set tags+=/path/to/cpp_src/tags

其它库的索引文件也可以依法炮制，只需切换到该库的 include 文件夹，执行：

ctags -R --sort=yes --c++-kinds=+p --fields=+iaS --extra=+q --language-force=C++ -f <文件名> .

## 安装OmniCppComplete

1. 下载[OmniCppComplete](http://www.vim.org/scripts/script.php?script_id=1520)

2. 解压到~/.vim

3. 在.vimrc中加入

```  
let OmniCpp_NamespaceSearch = 1  

let OmniCpp_GlobalScopeSearch = 1  

let OmniCpp_ShowAccess = 1  

let OmniCpp_ShowPrototypeInAbbr = 1 " 显示函数参数列表  

let OmniCpp_MayCompleteDot = 1   " 输入 .  后自动补全  

let OmniCpp_MayCompleteArrow = 1 " 输入 -> 后自动补全  

let OmniCpp_MayCompleteScope = 1 " 输入 :: 后自动补全  

let OmniCpp_DefaultNamespaces = ["std", "_GLIBCXX_STD"]  

au CursorMovedI,InsertLeave * if pumvisible() == 0|silent! pclose|endif  

set completeopt=menuone,menu,longest  
```

另外，还需确认在 vimrc 中开启了 filetype 选项，不然 OmniComplete 无法自动识别 C/C++ 文件类型进行补全。

这样，在插入模式编辑 C/C++ 源文件时按下 . 或 -> 或 ::，或者手动按下 Ctrl+X Ctrl+O 后就会弹出自动补全窗口，

此时可以用 Ctrl+N 和 Ctrl+P 上下移动光标进行选择。


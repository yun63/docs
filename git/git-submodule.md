Git Submodule
=============

## 添加submodule

`git submodule add ref_url path`

## 删除submodule

1. 从.gitmodules删除相关的submodule
2. 
2. 暂存.gitmodules文件的变化 `git add .gitmodules`
3. 
3. 删除.git/config里相关的submodule配置
4. 
4. `git rm --cache path_to_submodule`
5. 
5. `git rm -rf .git/modules/path_to_submodule`
6. 
6. 提交 `git commit -m "Removed submodule【name】"`
7. 
7. 删除submodule文件`rm -rf path_to_submodule`

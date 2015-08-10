Centos下mysql5.7.4源码安装
==========================

## 一 卸载旧版本

1. 查看是否有旧版本

```
rpm -qa | grep mysql5
```

2. 卸载旧版本

```
rmp -e mysql
rmp -e nodeps mysql 
```

## 二 安装mysql

1. 安装依赖

```
yum -y install make gcc-c++ cmake bison-devel  ncurses-devel
```

2. 下载源码

```
wget http://cdn.mysql.com/Downloads/MySQL-5.6/mysql-5.6.14.tar.gz
tar xvf mysql-5.6.14.tar.gz
cd mysql-5.6.14
```

3. 编译安装

```
cmake \
-DCMAKE_INSTALL_PREFIX=/usr/local/mysql \
-DMYSQL_DATADIR=/usr/local/mysql/data \
-DSYSCONFDIR=/etc \
-DWITH_MYISAM_STORAGE_ENGINE=1 \
-DWITH_INNOBASE_STORAGE_ENGINE=1 \
-DWITH_MEMORY_STORAGE_ENGINE=1 \
-DWITH_READLINE=1 \
-DMYSQL_UNIX_ADDR=/tmp/mysql.sock \
-DMYSQL_TCP_PORT=3306 \
-DENABLED_LOCAL_INFILE=1 \
-DWITH_PARTITION_STORAGE_ENGINE=1 \
-DEXTRA_CHARSETS=all \
-DDEFAULT_CHARSET=utf8 \
-DDEFAULT_COLLATION=utf8_general_ci

make && make install
```

## 三 配置mysql

1. 创建mysql组和用户

```
groupadd mysql
useradd -g mysql mysql
```

2. 修改/usr/local/mysql权限

```
chown -R mysql:mysql /usr/local/mysql
```

3. 初始化配置

进入安装路径
cd /usr/local/mysql
执行初始化配置脚本，创建系统自带的数据库和表
`scripts/mysql_install_db --basedir=/usr/local/mysql --datadir=/usr/local/mysql/data --user=mysql`

注：在启动MySQL服务时，会按照一定次序搜索my.cnf，先在/etc目录下找，找不到则会搜索"$basedir/my.cnf"，在本例中就是/usr/local/mysql/my.cnf，这是新版MySQL的配置文件的默认位置！注意：在CentOS6.4版操作系统的最小安装完成后，在/etc目录下会存在一个my.cnf，需要将此文件更名为其他的名字，如：/etc/my.cnf.bak，否则，该文件会干扰源码安装的MySQL的正确配置，造成无法启动。

4. 启动MySQL

添加服务，拷贝服务脚本到init.d目录，并设置开机启动
```
cp support-files/mysql.server /etc/init.d/mysql
chkconfig mysql on
service mysql start  --启动MySQL
```

四 配置用户

MySQL启动成功后，root默认没有密码，我们需要设置root密码。

设置之前，我们需要先设置PATH，要不不能直接调用mysql

修改/etc/profile文件，在文件末尾添加

```
PATH=/usr/local/mysql/bin:$PATH
export PATH
```
关闭文件，运行下面的命令，让配置立即生效

source /etc/profile
现在，我们可以在终端内直接输入mysql进入，mysql的环境了

执行下面的命令修改root密码

```
mysql -uroot  
mysql> SET PASSWORD = PASSWORD('123456');
```

若要设置root用户可以远程访问，执行

`mysql> GRANT ALL PRIVILEGES ON *.* TO 'root'@'180.76.128.15%' IDENTIFIED BY 'root3gx' WITH GRANT OPTION;`

五 配置防火墙

防火墙的3306端口默认没有开启，若要远程访问，需要开启这个端口

打开/etc/sysconfig/iptables

在`-A INPUT –m state --state NEW –m tcp –p –dport 22 –j ACCEPT`，下添加：

`-A INPUT -m state --state NEW -m tcp -p -dport 3306 -j ACCEPT`
然后保存，并关闭该文件，在终端内运行下面的命令，刷新防火墙配置：

`service iptables restart`




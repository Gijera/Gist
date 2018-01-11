# a-php-command-tool
这是一个基于[Symfony/console](https://github.com/symfony/console)构造的Todo命令行工具。

## 安装
* 先安装composer中的依赖文件
* 给tasks文件0777的权限

## 数据库
本例使用了sqlite数据库，创建表的命令如下：
```
create table tasks(
	id INTEGER PRIMARY KEY,
	description TEXT NOT NOLL
);
```

## 用法
* 在该目录下输入```./tasks```即可查看命令信息
* ```./tasks show```可以显示所有的待办事项列表
* ```./tasks add 'a new task'```可添加一条待办事项
* ```./tasks complete 4```可以删除id为4的待办事项

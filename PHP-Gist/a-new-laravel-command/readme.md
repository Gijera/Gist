# a-new-laravel-command
这个命令行工具是仿照Laravel的创建命令```laravel new filename```编写的，可以用来创建一个laravel应用。

## 安装
* 要先安装composer.json中的依赖文件，本命令基于Symfony/console的命令行工具创建。注意在composer中添加了Acme命名空间的路径为‘src’，如果更改了NewCommand文件的路径，要同时更改composer.json文件。
* 还要给drive文件chmod 0777权限。

## 用法
```./drive new filename```将会创建一个laravel应用程序

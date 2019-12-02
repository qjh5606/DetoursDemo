# DetoursDemo
Ussing Detours to Implement DLL Injection.



Detours实现的第三方Dll钩子测试代码

目标进程TargetExe启动后，循环调用目标动态库TargetDll的TargetFunc函数，计算返回值并显示，正常如下：

0 0
1 0
2 3
3 8
4 15
5 24
6 35
7 48
8 63
9 80
10 99
11 120
12 143
13 168
14 195
15 224

当通过钩子进程HookExe启动TargetExe时，会向TargetExe注入HookDll动态库，用NewTargetFunc挂钩旧的TargetFunc，并修改执行代码，此时显示如下：

---- hooking ... ----

0 0

---- hooking ... ----

1 0

---- hooking ... ----

2 0

---- hooking ... ----

3 8

---- hooking ... ----

4 0

---- hooking ... ----

5 24

---- hooking ... ----

6 0

---- hooking ... ----

7 48

---- hooking ... ----

8 0

---- hooking ... ----

9 80

....


注意：

- TargetExe、TargetDll，HookExe、HookDll使用VS编译

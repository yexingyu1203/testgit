# CMake



## CMake工作流程：

表面上可以感受到的工作流程：“CMake 是在一端读取源代码，在另一端生成二进制文件的工具”。**但正如上文所说CMake是一个工具集，那就说明了CMake 自己并没有构建任何东西的能力**，CMake它依赖于系统中的其他工具来执行实际的编译、链接和其他任务。CMake好似一个在构建过程中工作的“协调器”，它清楚哪些步骤需要完成，理解最终目标是什么，以及忙碌于为构建工作找到合适的“工人”和“材料”。综上，**这个过程有三个阶段：配置、生成、构建阶段**。



## 基本的CMake语法

### 变量



基本的变量操作指令是set()\unset()，变量名区分大小写并可以包含字符~~（使用括号和引号~~~~参数允许在变量名中包含空格。但当以后引用时，必须使用反斜杠来转义空格(\)~~，因此，建议在**变量名中只使用字母数字字符、减号(-) 和下划线(_)**）。具体的使用方式为在设置变量时只需使用set()并提供名称和值，要取消变量的设置时可以使用unset()并提供名称。

```cmake
set(MyString1 "Text1")
set([[My String2]] "Text2")#变量名尽量不用空格
set("My String 3" "Text3")

message(${MyString1})

 
unset(MyString1)
```



* message是用以构建过程中的打印，通过${}告诉CMake遍历**作用域堆栈**，尝试将${MyString1}替换为具体的值供message命令打印出来

* CMake若是没有找到对应的变量则会将其替换为空字符串并不会产生错误

* 通过${} 语法进行变量的求值和展开时，是由内而外执行的。

  * ```cmake
    set(MyOuter "My")
    set(MyInner "Hello")
    
    message(${${MyOuter}Inner}\ World)
    ```

    打印 Hello World



> • ${} 用于引用普通变量或缓存变量。
> • $ENV{} 用于引用环境变量。
> • $CACHE{} 用于引用缓存变量。





- 普通变量

- 缓存变量

  



​	

- 环境变量

  使用set(ENV{<variable>} <value>) 指令用以声明，使unset(ENV{<variable>})来清除某一个环境变量，其中ENV表示环境变量标志性前缀.

  **需要注意的是设定或读取环境变量时，都通过ENV前缀来访问环境变量，读取环境变量值时，要在ENV前加$符号；但if判断是否定义时，不用加$符号**

  ```cmake
  set(ENV{_USERNAME} "zhang")
  if(DEFINED ENV{_USERNAME})
  	message("USERNAME:$ENV{_USERNAME}")
  else()
  	message("NOT FOND _USERNAME")
  endif()
  ```

  * 输出：USERNAME:zhang
  * 如果把第一行注释(#)掉，输出：NOT FOND _USERNAME
  * 设定环境变量后，其作用域只影响当前CMake进程，也就是说**环境变量设定后是整个CMake进程的作用域都可用**，但是不会影响CMake进程外的整个系统环境。


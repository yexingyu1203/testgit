# CMake

```cmake
cmake -B build .
```

`-B` 选项指定了生成构建系统文件的目录，而 `build` 则是指定的目录名称。`.` 表示当前目录，因此这个命令的意思是在当前目录下创建一个名为 `build` 的子目录，并在该子目录中**生成构建系统文件。**

```cmake
cmake --build .
```

 用于编译一个CMake项目。这里的 `--build` 选项告诉CMake去构建/编译项目，而后面的 `.` 指的是当前目录，即指示CMake在当前目录下寻找生成的构建系统文件（如Makefile或其他构建工具的配置文件），并使用这些文件来编译项目。

这种方式的好处是，它提供了一种工具无关的编译命令。无论底层使用的是Make、Ninja还是其他构建工具，都可以通过 `cmake --build` 命令来编译项目，而不需要直接使用特定构建工具的命令（例如 `make`、`ninja` 等），这样增加了跨平台构建的便利性





## CMake工作流程：

表面上可以感受到的工作流程：“CMake 是在一端读取源代码，在另一端生成二进制文件的工具”。**但正如上文所说CMake是一个工具集，那就说明了CMake 自己并没有构建任何东西的能力**，CMake它依赖于系统中的其他工具来执行实际的编译、链接和其他任务。CMake好似一个在构建过程中工作的“协调器”，它清楚哪些步骤需要完成，理解最终目标是什么，以及忙碌于为构建工作找到合适的“工人”和“材料”。综上，**这个过程有三个阶段：配置、生成、构建阶段**。

![preview](https://pic2.zhimg.com/v2-aa52d0265eda2f2ab04cdc7b2f990701_r.png)

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

  缓存变量可以通过$CACHE{<name>} 语法来引用，而设置一个缓存变量使用`set(<variable> <value> CACHE <type> <docstring> [FORCE])`指令，与用于普通变量的set() 指令相比，缓存变量的设定中有一些必需参数和关键字（CACHE &FORCE）。与环境变量不同的是**，缓存变量是CMake进程在配置阶段收集相关信息后存储在在构建树中的CMakeCache.txt 文件中的变量**，缓存变量不可像环境变量中在脚本使用但是可以通过cmake-gui或者ccmake来声明
  
  **Cache Variable缓存变量相当于一个全局变量，在同一个CMake工程中任何地方都可以使用，比如父目录，子目录等**，而如上文中缓存变量的指令格式是
  
  ```cmake
  set(<variable> <value>... CACHE <type> <docstring> [FORCE])
  ```
  
  > variable：变量名称
  >
  >value：变量值列表
  >
  >CACHE：cache变量的标志
  >
  >type：变量类型，取决于变量的值。类型为：BOOL、FILEPATH、PATH、STRING、INTERNAL
  >
  >docstring：必须是字符串，作为变量概要说明
  >
  >FORCE：强制选项，强制修改变量值
  
  ​	
  
  其中FORCE选项，在**定义缓存变量时**不加也能定义成功，但是**修改时**不加FORCE选项则修改无效，所以不论定义或修改缓存变量时，建议都加上FORCE选项，具体实例如下：
  
  > 1、 //设置一个string类型的缓存变量，名称为FOO，变量值为BAR
  > 2、 set(FOO "BAR" CACHE STRING "interesting value" FORCE)
  > 3、 //设置一个string类型的缓存变量，名称为CMAKE_BUILD_TYPE，变量值为Release
  > 4、 set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)





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
  
  * 环境变量在启动CMake进程后会基于CMake在配置阶段中收集的信息在**CMake生成阶段**生成环境变量的**副本**，该副本会在**单一的、全局的**作用域中可用。即，若使用ENV 变量作为指令的参数，这些值将在CMake生成构建系统期间（配置阶段+生成阶段）插入，并且会将其嵌入到构建树中，在构建系统完成后即使再通过脚本或者命令行修改环境变量ENV{<variable>}的value，在构建阶段时该环境变量值也不会更新成新的value（**因为在构建系统中保存的是之前环境变量的副本**）
  
    ```cmake
    #CMakeLists.txt:
    cmake_minimum_required(VERSION 3.20.0)
    project(Environment)
     #在配置期间打印myenv环境变量
    message("generated with " $ENV{myenv})
     #在构建阶段过程中打印相同的变量
    add_custom_target(EchoEnv ALL COMMAND echo "myenv in build is" $ENV{myenv})
    ```
  
    ```bash
    #bash脚本:
    export myenv=first
    echo myenv is now $myenv
    
    
    cmake -B build . 	
    #在当前目录下创建build目录并在当前目录中生成构建系统文件
    cd build
    
    export myenv=second
    echo myenv is now $myenv
    
    cmake --build .
    #--build 选项告诉CMake去构建/编译项目，而后面的 `.` 指的是当前目录，即指示CMake在当前目录下寻找生成的构建系统文件（如Makefile或其他构建工具的配置文件），并使用这些文件来编译项目。
    
    sleep 120
    ```



### 作用域

（1）、CMake中变量的函数作用域可类比成C/C++中函数的参数值传递（不是引用、也不是指针），也就是说在一般情况下CMake函数中对变量的修改不会影响到函数外的CMake变量value值，而CMake函数中的变量就是从parent scope中“查询”到并生成的副本；

（2）、CMake中变量的目录作用域，也是类似于C/C++中的include文件依赖，也就是在子目录下的对变量的修改不会影响父目录中变量定义的value值；



话已至此，不妨再类比一下CMake中的普通变量、缓存变量和环境变量

（1）、CMake普通变量就好比C/C++中的普通变量定义。都是作用在定义变量时所在的作用域（scope）之下；

（2）、CMake缓存变量有些像C/C++中的指针，只是CMake中引用缓存变量的value值时不用像C/C++那样加一个“取地址符”，而且这个缓存变量（“指针”）是不对外部可见的（不能通过命令行修改和引用CMake缓存变量），如果想要CMake中修改后的缓存变量value值生效就必须加上FORCE关键字；

（3）、CMake的环境变量就好比C/C++中的宏定义了，不仅对外部可见，同时CMake中还支持对环境变量（“宏”）的修改。



目录作用域的启用一般是在父目录下的CmakeList.txt中有add_subdirectory(“子目录路径”)指令，而在子目录的CMakeLists.txt会将父目录的所有变量拷贝到当前CMakeLists.txt中，当前CMakeLists.txt中的变量的作用域仅在当前子目录有效。



不管是针对CMake函数作用域还是CMake目录作用域，其都有两个特点：**向下有效和数值拷贝生成副本**，在不使用特殊关键字的情况下，嵌套（子）作用域针对普通变量的修改不会影响到父作用域。针对变量，普通变量仅仅有效于当前作用域，而缓存变量和环境变量可以在全局作用域中使用



### 控制结构



* 条件块

  ```cmake
   if(<condition>)
     <commands>
   elseif(<condition>) # optional block, can be repeated
    <commands>
   else() # optional block
    <commands>
   endif()
  ```

  >- `EQUAL`：等于
  >- `NOT EQUAL`：不等于
  >- `LESS`：小于
  >- `GREATER`：大于
  >- `LESS_EQUAL`：小于等于
  >- `GREATER_EQUAL`：大于等于
  >- `STRLESS`：字符串小于
  >- `STRGREATER`：字符串大于
  >
  >- `AND`
  >- `OR`
  >- `NOT`



* 循环

  * while循环

    必须以while()开头创建并以endwhile()结尾

    ```cmake
    #从9打印到0
    cmake_minimum_required(VERSION 3.20.0)
    project(Environment)
    
    set(VALUE 9)
    
    WHILE(VALUE GREATER_EQUAL 0)
    	MESSAGE(${VALUE})
    	math(EXPR VALUE "${VALUE}-1")
    ENDWHILE()
    ```

  * foreach循环

    ` foreach(<loop_var> RANGE <min> <max> [<step>])`

    ```cmake
    #打印从0到20的偶数
    cmake_minimum_required(VERSION 3.20.0)
    project(Environment)
    
    foreach(val RANGE 0 20 2)
    	MESSAGE(${val})
    endforeach()
    ```

    

    ` foreach(<loop_variable> IN [LISTS <lists>] [ITEMS <items>])`

    ```cmake
    set(MY_LIST 1 2 3)
    foreach(VAR IN  ITEMS e f LISTS MY_LIST)
      message(${VAR})
    endforeach()
    #先从ITEMS<e,f>中逐个取元素的值，再逐个取MY_LIST中取 
    #打印：
    #e
    #f
    #1
    #2
    #3
    ```

    

    ```cmake
    set(MY_LIST 1 2 3)
    foreach(VAR IN LISTS MY_LIST ITEMS e f )
      message(${VAR})
    endforeach()
    #打印
    #1
    #2
    #3
    #e
    #f
    ```

  * ZIP_LISTS：通过ZIP_LISTS关键字来“压缩“多个列表，以在单次循环中处理相同索引的列表元素

    * 可以通过`<loop_var>_<N>`来获取元素
    * 也可以通过自定义传递两个<loop_var>变量，存储获取元素

    ```cmake
    set(L1 "one;two;three;four;five")
    set(L2 "1;2;3;4;5")
    set(L3 "Mon;Tue;Wed;Thu;Fir")
    foreach(val IN ZIP_LISTS L1 L2 L3)
    	message("val_0=${val_0};val_1=${val_1};val_2=${val_2}")
    endforeach()
    #注意 cmake是区分大小写的！ IN不要写成小写的in
    ```

    输出

    ```
    val_0=one;val_1=1;val_2=Mon
    val_0=two;val_1=2;val_2=Tue
    val_0=three;val_1=3;val_2=Wed
    val_0=four;val_1=4;val_2=Thu
    val_0=five;val_1=5;val_2=Fir
    ```



### 宏和函数



* 宏

  * 例一

    ```cmake
    macro(MyMacro)
    	message("FirstArg: ${FirstArg}")
    	set(FirstArg "new value")
    	message("FirstArg again: ${FirstArg}")
    endmacro()
    	
    	
    set(FirstArg "first value")
    MyMacro()
    message("FirstArg in global scope: ${FirstArg}")
    ```

    输出

    ```
    FirstArg: first value
    FirstArg again: new value
    FirstArg in global scope: new value
    ```

    宏涉及到替换

    替换后

    >set(FirstArg "first value")
    >message("FirstArg: ${FirstArg}")
    >set(FirstArg "new value")
    >message("FirstArg again: ${FirstArg}")
    >message("FirstArg in global scope: ${FirstArg}")

    

  * 例二

    ```cmake
    macro(MyMacro Arg)
    	message("Arg: ${Arg}")
    	set(Arg "new value")
    	message("Arg again: ${Arg}")
    	message("ARGV0: ${ARGV0} ARGV1: ${ARGV1} ARGC: ${ARGC}")
    endmacro()
    
    #调用函数，并传参个数比函数声明时的多了一个
    MyMacro("Value1" "Value2")
    ```

    输出

    ```
    Arg: Value1
    Arg again: Value1
    ARGV0: Value1 ARGV1: Value2 ARGC: 2
    ```

    



* 函数

  * 例一：

    ```cmake
    function(MyFunction)
    	message("FirstArg: ${FirstArg}")
    	set(FirstArg "new value")
    	message("FirstArg again: ${FirstArg}")
    endfunction()
    	
    	
    	set(FirstArg "first value")
    	MyFunction()
    	message("FirstArg in global scope: ${FirstArg}")
    ```

    输出

    ```
    FirstArg: first value
    FirstArg again: new value
    FirstArg in global scope: first value
    ```

    由这个例子看出：**函数中对全局变量的修改只停留在函数作用域中，在函数结束后不会影响到父作用域中的变量value值。**

  

  * 例二

    ```cmake
    function(MyFunction Arg)
    	message("Arg: ${Arg}")
    	set(Arg "new value")
    	message("Arg again: ${Arg}")
    	message("ARGV0: ${ARGV0} ARGV1: ${ARGV1} ARGC: ${ARGC}")
    endfunction()
    
    #调用函数，并传参个数比函数声明时的多了一个
    MyFunction("Value1" "Value2")
    ```

    输出：

    ```
    Arg: Value1
    Arg again: new value
    ARGV0: Value1 ARGV1: Value2 ARGC: 2
    ```

    这个例子表明：

    传递给函数的实参值被真正使用在了函数的作用域内，在调用函数MyFunction并传入Value1（Value2是“多余”的匿名实参值），而后在函数内打印message("Arg: ${Arg}")输出的是“Value1”，随后set(Arg "new value")再打印输出的是修改后的“new value”。但是{ARGV0}、{ARGV1}的值仍然是Value1、Value2



### include()指令

Modern CMake中重要的一个模块就是引用官方和CMake社区中已经配置好了的CMake模板，所谓的CMake模板就是将CMake代码划分到单独的.cmake文件中，以保持内容的有序和独立性。然后通过include()指令，从父列表文件引用：

```cpp
 1、 include(<file|module> [OPTIONAL] [RESULT_VARIABLE <var>])
```

若提供文件名(一个扩展名为.cmake)，CMake 将尝试打开并执行它。这里不会创建嵌套的、单独的作用域，因此对该文件中变量的修改会影响调用作用域。若文件不存在，CMake 将抛出一个错误，除非用optional 关键字指定为可选。若需要知道include() 指令操作是否成功，可以提供一个带有变量名的RESULT_VARIABLE 关键字，若include（）引用成功，则用包含的文件的完整路径填充，失败则用未找到(NOTFOUND) 填充。



### file()指令

使用语法为：

 `file(GLOB <variable> [LIST_DIRECTORIES true|false] [RELATIVE <path>] [CONFIGURE_DEPENDS] [<globbing-expressions>...])`
含义： GLOB, 就是globbing的缩写， 该命令查找所有在当前目录（CMakeLists.txt所在目录，即CMAKE_CURRENT_SOURCE_DIR变量）下所有满足匹配通配符表达式的文件，并保存到给定的变量中。

* GLOB: 是关键字。

* variable: 保存文件名的变量

* LIST_DIRECTORIES true| false : 表示是否要保存文件的路径，默认保存

* RELATIVE path: 给定该参数时，保存的路径中是相对于给定path的路径名。
  globbing-expressions: 通配符表达式。
  使用举例

  ```
  file(GLOB source_list "src/*.cpp")
  ```

  

* 如果你想查找当前源目录（`${CMAKE_CURRENT_SOURCE_DIR}`）下所有 `.cpp` 文件，并将它们存储在变量 `SOURCE_FILES` 中:
  
* `file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")`
  
* 如果你想创建一个目录:
  
  * `file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/mydir")`





### execute_process

CMake 提供了execute_process()指令以用来运行其他进程，并收集它们的输出。这个命令非常适合脚本，也可以在配置阶段的项目中使用。下面是命令的一般形式：

```cpp
execute_process(COMMAND <cmd1> [<arguments>]  [OPTIONS])
```

例如

```cmake
find_program(LIPDATE_EXECUTABLE lupdate)
excute_process(
	COMMAND ${LIPDATE_EXECUTABLE} -recursive ${CMAKE_SOURCE_DIR} -ts ${file}
)
```





## 简单的CMake构建



Animal.hpp

```c++
#pragma once
#define N 10
#include<iostream>

class Animal
{
public:
	virtual void sound()=0;
};

class Cat:public Animal
{
public:
	void sound();
};

class Dog
{
public:
	void sound();
};
```

Animal.cpp

```c++
#include "Animal.hpp"

void Cat::sound()
{
	std::cout << "喵喵喵"<<std::endl;
}

void Dog::sound()
{
	std::cout << "汪汪汪" << std::endl;
}
```

main.cpp

```cpp
#include<cstdlib>
#include<iostream>
#include<string>
#include "Animal.hpp"

std::string say_hello()
{
	return std::string("please just say hello ");
}

int main()
{
	std::cout<<say_hello()<<std::endl;

	Animal* ani=new Cat();
	ani->sound();

	while(1);
	return EXIT_SUCCESS;
}
```

这里有两个文件需要编译，所以CMakeLists.txt必须进行修改。本例中，先把它们编译成一个库，而不是直接编译成可执行文件，具体实施和注释如下所示：

```cmake
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
 
# project name and language
# LANGUAGES关键语法一般都不做声明，C表示C语言，CXX表示C++
# CMake中，C++是默认的编程语言。不过，我们还是建议使用LANGUAGES选项在project命令中显式地声明项目的语言
project(MakeBuild1 LANGUAGES CXX)

add_library(animal
 STATIC
    Animal.hpp
    Animal.cpp
  ) 

# 指示CMake创建一个新目标：可执行文件helloworld。
# 这个可执行文件是通过编译和链接源文件main.cpp生成的，CMake将为编译器使用默认设置，并自动选择生成工具
add_executable(helloworld main.cpp)
target_link_libraries(helloworld animal)

```



### add_Library

```cmake
add_library(<name> [STATIC | SHARED | MODULE] [EXCLUDE_FROM_ALL] [<source>...]
```

第二个参数

- STATIC：用于创建静态库，即编译文件的打包存档，以便在链接其他目标时使用，例如：可执行文件。
- SHARED：用于创建动态库，即可以动态链接，并在运行时加载的库。可以在CMakeLists.txt中使用add_library(message SHARED Message.hpp Message.cpp)从静态库切换到动态共享对象(DSO)。
- OBJECT：可将给定add_library的列表中的源码编译到目标文件，不将它们归档到静态库中，也不能将它们链接到共享对象中。如果需要一次性创建静态库和动态库，那么使用对象库尤其有用。
- MODULE：又为DSO组。与SHARED库不同，它们不链接到项目中的任何目标，不过可以进行动态加载。该参数可以用于构建运行时插件。



### target_link_libraries

```camke
target_link_libraries(
<target> <PRIVATE|PUBLIC|INTERFACE> <item>...[<PRIVATE |PUBLIC| INTERFACE><item>...]...
)
```


该命令的用于指定一个target的链接阶段的依赖库。



### 条件语句控制编译

```cmake
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
 
# project name and language
# LANGUAGES关键语法一般都不做声明，C表示C语言，CXX表示C++
# CMake中，C++是默认的编程语言。不过，我们还是建议使用LANGUAGES选项在project命令中显式地声明项目的语言
project(MakeBuild LANGUAGES CXX)

set(BUILD_SHARED_LIBS OFF)
set(USE_LIBRARY ON)
list(APPEND _source Animal.hpp Animal.cpp)

if(USE_LIBRARY)
	add_library(animal ${_source})
	add_executable(helloworld main.cpp)
	target_link_libraries(helloworld animal)
else()
	add_executable(helloworld main.cpp ${_source})
endif()
```



* `BUILD_SHARED_LIBS`是CMake的一个全局标志。因为CMake内部要查询`BUILD_SHARED_LIBS`全局变量，所以`add_library`命令可以在不传递`STATIC/SHARED/OBJECT`参数的情况下调用；如果为`false`或未定义，将生成一个静态库。
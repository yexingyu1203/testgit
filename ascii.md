diameter n.直径

successive adj.连续的，接替的，依次的

# ASCII格式约定：

* 全大写字母：控制声明和大多数关键字
* 小写斜体文本：代表变量
* 粗体且大小字母的组合：关键字
* 所有大小写字母、数字和特殊字符
* `*`,`?`,段落符，tab、换行符、`,`在name中出现都是不合法的
* 旋转角度是[0，359]之间的整数
* 可选数据放在中括号`[]`中

* 所有尺寸和坐标都以0.001英寸为单位





# ASCII文件结构：

> control statements:
>
> * `*REMARK*`  
> * `*SCH*`  general paremeter command
> * `*CAM*`  print and plot settings
> * `*MICS*` misellaneous seection (layers and rules data)
> * `*FIELDS*`
> * `*SHT*`
> * `*LINES*`
> * `*TEXT*`
> * `*CAEDECAL*`
> * `*PARTTYPE*`
> * `*PART*`
> * `*BUSSES*`
> * `*OFFPAGE REFS*`
> * `*TIEDOTS*` tie dot control command
> * `*CONNECTION*`
> * `*NETNAMES*`



* start of file

* system parameters
  
  * 从`*SCH*`开始
  
* plot output settings
  * 这是一个可选的部分
  * 从`*CAM*`开始
  
* PCB layer definition and design rules
  * 可选的部分
  * 从`*MISC*`开始

* fields
  
* 控制语句`*FIELDS*`， `"fieldname" fieldvalue`
  
* start  of schematic sheet

  从`*SHT*`开始

* text definition

  `*TEXT*`

  >x y rotation justification height width field fontinfo textstring
  
  * rotation 
  * justification 
  * height 10~1000
  * width 1~50
  * field  0:normal text , 1:field label
  * fontinfo
  * textstring 最多255个字符





* lines definition

  `*LINES*`

  * header line

    >name linetype x y pieces text

    `linetype`只能是LINES

  * piece definition

    >type 
    >
    >​	open/closed(最少4个corner)/circle
    >
    >corners:
    >
    >​	open item: it is the number of corners
    >
    >​	closed item:it is the number of 1+corners
    
    > circles:2corners
    
    >width:line width
      >
      >linestyle
      >
      >x y
    
  * text definitions



* CAE DECAL Definition

  `*CAEDECAL*`

  该部分定义了原理图中的逻辑符号，`CAEDECAL`信息包含部分概述、部分文本和终端信息。
  
  * header lines
  
    包含4行
  
  * attribute label locations
  
  * piece definitioins
  
  * text definitions
  
  * terminal definitions



* tie dot definition

  ```
  @@@Dnumber x y
  ```

* off-page reference

  * @@@Onumber
    * number从零开始有序增长
  * netname
    * 非页面符号连接的信号名称
  * type
  * x y
  * ori
    * orientation 0~90
  * xym
    * 0:default
    * 1:X镜像
    * 2:Y镜像
    * 3: X&Y镜像
  * alt

* Bus Definition

  从`*BUSSES*`开始

  * @@@**B**number
  * busname
  * corners:the number of corners in the bus
  * x y



# 主要解析段落

- `*CAEDECAL*` cae封装

  - Hearder lines

    - 第一行： 

      ```
      name x y pnhgt pnwid labels pieces txt terms vis pflags
      ```

      这里的name是封装名，对应cell节点的名字

    - 第二行

      TIMESTAMP

    - 第三行

      fontinfo

    - 第四行

      fontinfo

  - Atrribute label locations

    ```
    x y rotation justifiction height width fontinfo 
     textstring
    ```

    textstring:  REF-DES   PART-TYPE

    如果eds文件中cell=》view=》interface=》symbol下面有propertyDisplay节点并且节点的第一个属性为Comment，那么Comment也会作为textstring的一部分。并且HeaderLine里面的labels+1

  - piece definition

    - type of line
    - the number of corners to the piece
    - width
    - linestyle
    - 换行显示每一个角的坐标点

  - terminal definitions

    **T** ......

    **P**......

- `*PARTTYPE*`

- `*PART*`

- `*OFFPAGE REFS*`

- `*TIEDOTS*` 

- `*CONNECTION*`

- `*NETNAMES*`
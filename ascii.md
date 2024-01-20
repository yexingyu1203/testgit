

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
    >coners
    >
    >width
    >
    >linestyle
    >
    >x y

  * text definitions
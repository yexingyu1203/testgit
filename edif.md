silicon 硅

descend vi&vt 下降，降低，下来

in addition to…… 除……之外

in terms of 安装、依照

segmented adj. 分段的

modular adj. 模块化的

overlap n.重叠 v.发生重叠

intermediary adj.中间的，媒介的 n.中间人，媒介

nested adj.嵌套的，内嵌的

other than 除了，不同于



* libraries

  * cell definitions

    * 分段成多个视图

      >NETLIST view
      >
      >SCHEMATIC view
      >
      >LOGICMODEL view
      >
      >MASKLAYOUT view
      >
      >SYMBOLIC view
      * interface

        * port

          a simple port/ a port array / a port boundle

          port array中的port有相同的特征

    

  * technology information







```edif
(design root
	(cellRef TopOfDesignCell
		(libraryRef CMOSLibrary)))
```

设计root指定为**由TopOfDesignCell开始**，该单元可以在CMOSLibrary中找到。

design：指定the starting points for this file
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



```edif
(cell xxx
	(view xxx
		(contents
			(page
				(pagesize rect
				)
			)
		)
	)


)
```



PageSize是page和symbol的环境属性。

页的尺寸不是指页的绝对尺寸，而是其环境中页的范围。也就是，在页尺寸中的点与计数据中的点相关。pageSize不同于描述包含设计信息的最小矩形的boundingBox。页的尺寸必须覆盖设计信息，但在许多系统中页的尺寸比设计的范围要大。

````
(symbol
	(pageSize
		(rectangle
			(pt -120 -100)
			(pt 120 100))
	(figure..))

````



* orientation

  ```
  orientation R0|R90|R180|R270|MX|MY|MYR90|MXR90
  ```

  R后面的数字表示绕原点逆时针旋转的度数

  MX:关于X轴镜像操作

  MY:关于Y轴镜像操作



* cellType

  * GENERIC

    单元类型GENERIC指定单元是一个同类单元，并且包含除TIE和RIPPER类型单元外的所有cell的用途。

  * TIE

    单元类型TIE指出单元是**用于描述目标之间的连接关系**。TIE示例只被允许**用于net中**，并且主要是连接一个网表中的子网表。TE单元的定义在其界面上必须包含一个端口或一个端口阵列定义。多个子网表可以经端口连接到这个单一的网上。

  * RIPPER

    单元类型RIPPER指出单元是用于描述目标之间的连接关系。RIPPER示例用于合并不同名字的网表，描述网表之间的置换，或者提取网表阵列和网表组中的各个部分。RIPPER界面必须包含至少两个端口，或两个端口阵列，或两个端口组。在RIPPER的使用中，只有一个网表可以引用每个端口。RIPPER类型的单元示例只能出现在contents和page构件中。



* cell => view => interface下面有Symbol节点，用于定义元器件封装的形状、轮廓等。但是power和gnd没有symbol节点，它们的这些内容都定义在cell => view =>contentes中。

* pointList

  cell=>view=>interface=>symbol=>figure=>path下面的pointList，这些点的顺序

  和Ascii文件decal中的piece definition后面的点顺序是相反的。
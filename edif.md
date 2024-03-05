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




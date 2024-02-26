



* 一个edif文件中只能有一个design节点吗

* `WriteToGB2312`方法中，把code转成整数再转成char类型，超出表示范围？
  
  * 能够存放8位数据（编码）即可，不需要操作字符
  



* BusGraph是？

* Designator是什么？

  * 元件的参考编号，例如R5、TP5、LED1等等
  
* portInstance端口名和显示名称的映射指的是？

  ```
  (portInstance &1 (designator (stringDisplay "1")))
  ```

  * &1 是端口名
  * "1"是显示名称

* findNode(根节点，...节点类型)； 这些节点类型是“纵向的关系”

  ```
  findNode(root,NodeType::Status,NodeType::Written,NodeType::timeStamp);
  ```

  上面的例子是找Staus节点下的Written节点下的timeStamp节点



* transform

  ![1708425474755](D:\study\test1\testgit\巢粉\transform.png)



* std::remove
  *  需要结合容器的erase函数使用‘




* EDIFReader.cpp中 Line45 为什么用std::move()?







* ASCGlobalUtils.h中旋转处理180度坐标变换有问题？
* ASCSectionBase.h中 Line90  引用的封装名称是什么？Instance节点名？InstanceData结构体中的name?





* cmake加什么命令让生成的.sln支持x86编译
  * -A win32 生成win32的.sln文件
* 修过生成的.exe路径
  * msbuild命令 -p:OutDir:<path>可以修改路径


























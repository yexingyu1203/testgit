



* 一个edif文件中只能有一个design节点吗

* `WriteToGB2312`方法中，把code转成整数再转成char类型，超出表示范围？
  
  * 能够存放8位数据（编码）即可，不需要操作字符
  
* 按Enter键换行，行末尾\r\n?

  * 是的

* BusGraph是？

* Designator是什么？端口名和显示名称的映射指的是？

* findNode(根节点，...节点类型)； 这些节点类型是“纵向的关系”

  ```
  findNode(root,NodeType::Status,NodeType::Written,NodeType::timeStamp);
  ```

  上面的例子是找Staus节点下的Written节点下的timeStamp节点















* cmake加什么命令让生成的.sln支持x86编译
  * -A win32 生成win32的.sln文件
* 修过生成的.exe路径
  * msbuild命令 -p:OutDir:<path>可以修改路径


























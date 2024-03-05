



* 一个edif文件中只能有一个design节点吗

* `WriteToGB2312`方法中，把code转成整数再转成char类型，超出表示范围？
  
  * 能够存放8位数据（编码）即可，不需要操作字符
  

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
  *  需要结合容器的erase函数使用

* ASCSectionBase.h中 Line90  引用的封装名称是什么？Instance节点名？是否和InstanceData结构体中的name重复?

  

  在C++中，将结构体的成员作为`map`的键（key），并将结构体指针作为值（value）是一种常见的做法。这样做的好处是

  * **可以通过结构体的某个特定成员快速查找与之关联的结构体实例。**

  

  下面是一个示例，展示如何使用结构体的成员作为`map`的键，并将结构体指针作为值：

  ```cpp
  #include <iostream>  
  #include <map>  
    
  struct Person {  
      std::string name;  
      int age;  
      // 可以有其他成员...  
  };  
    
  int main() {  
      // 创建一个map，键是std::string类型（可以是结构体的任何成员），值是Person*类型  
      std::map<std::string, Person*> peopleByName;  
    
      // 创建几个Person对象  
      Person person1 = {"Alice", 30};  
      Person person2 = {"Bob", 25};  
      Person person3 = {"Charlie", 35};  
    
      // 将Person对象的指针插入到map中，以name作为键  
      peopleByName[&person1.name] = &person1;  
      peopleByName[&person2.name] = &person2;  
      peopleByName[&person3.name] = &person3;  
    
      // 通过键查找值（即Person指针）  
      std::string nameToFind = "Bob";  
      auto it = peopleByName.find(nameToFind);  
      if (it != peopleByName.end()) {  
          // 如果找到了，通过指针访问结构体成员  
          Person* foundPerson = it->second;  
          std::cout << "Found person: " << foundPerson->name << ", age: " << foundPerson->age << std::endl;  
      } else {  
          std::cout << "Person not found." << std::endl;  
      }  
    
      // 注意：在使用完map后，确保删除或管理这些指针，以避免内存泄漏  
    
      return 0;  
  }
  ```

  在这个例子中，我们创建了一个`map`，其中键是`Person`结构体的`name`成员，值是指向`Person`结构体的指针。我们插入了几个`Person`对象到`map`中，并通过名字快速查找对应的`Person`对象。

  使用结构体指针作为值的优点包括：

  1. **节省内存**：在`map`中只存储指向结构体的指针，而不是整个结构体的副本，这可以节省大量内存，尤其是当结构体很大时。
  2. **效率**：插入和查找操作通常比复制整个结构体更快。
  3. **灵活性**：通过指针，你可以修改`map`中存储的结构体实例，而不仅仅是它们的副本。

  然而，使用指针也需要注意内存管理和安全性问题。你需要确保在不再需要结构体时正确删除或释放它们，以防止内存泄漏。此外，使用指针也增加了程序出错的可能性，比如悬挂指针或野指针等问题。因此，在使用这种方法时，务必谨慎处理内存管理。



* cmake加什么命令让生成的.sln支持x86编译
  
  * -A win32 生成win32的.sln文件
  
* 修过生成的.exe路径
  
* msbuild命令 -p:OutDir:<path>可以修改路径
  
  











* BusGraph是？



- EDIFReader.cpp中 Line45 为什么用std::move()?







- ASCGlobalUtils.h中旋转处理270度坐标变换












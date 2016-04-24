##JDK与SDK的区别
JDK(Java Development Kit,Java开发工具包)是Sun Microsystems针对Java开发员的产品。自从Java推出以来，JDK已经成为使用最广泛的Java SDK（Software development kit）。可以认为jdk只是sdk的一种(子集)，因为它是开发java程序的一个平台，开发其他程序的sdk可以没有jdk。
##JDK与JRE的区别
安装完成之后，编写程序的时候显示Project SDK is not defined
jdk是java开发套件，是提供给开发人员的
jre是java运行环境，是提供给使用者的，使用者只关心这个程序能不能用，而不关系他是怎么运行的。所以提供的jre是供使用者下载的
1.需要下载JDK
2.选择JDK:`project structure`(或者ctrl+alt+shift+s)> `project` > `choose correct jdk`，然后apply后“Project SDK is not defined”错误消失。

##java中package和import的用法的不同之处

如果他们都在java这个文件夹下就可以这么写
第一个文件开头写package AAA.BBB
第二个文件 比如在AAA这个文件夹里 开头写
```
package AAA 
import AAA.BBB.*; 
```
导入包的前提是 你要导包的文件 也就是你说的第二个文件 必须跟你第一个文件的包结构的根目录是同级的 比如java文件夹 你的第二个文件必须放在这里才能用
 如果不这么放 你第二个文件放在哪 就要把相对你第一个文件的目录结构全部都打成第一个文件的包（第一个文件打包的时候结构就是相对于第二个文件的目录结构） 
其他项目导包 需要在`CLASSPATH`里加上其他项目包名的根目录就行了
##JAR文件结构
JAR 文件就是 Java Archive File，是 Java 的一种文档格式。JAR 文件非常类似 ZIP 文件——准确的说，它就是 ZIP 文件，所以叫它文件包。JAR 文件与 ZIP 文件唯一的区别就是在 JAR 文件的内容中，包含了一个 META-INF/MANIFEST.MF 文件，这个文件是在生成 JAR 文件的时候自动创建的。

##JAVA程序执行的顺序（编译+解释）
`.java`源文件-(javac编译)->`.class`字节码文件-（java解释执行）->特定平台的机器码

##java的class的名字是不是必须和其文件名相同? 

源文件的命名规则：
1、如果源文件中有多个类，那么只能有一个类是public类。
2、如果有一个类时public类，那么源文件的名字必须与这个类的名字完全相同，扩展名是.java
3、如果源文件没有public类，那么源文件的名字只要与某个类的名字相同，并且扩展名是.java 就可以 
 
##Main class（configuration里面的）有什么作用

Main class就是程序main方法所在的类文件夹。
开始的时候默认的是`com.company.Main`
然后在项目中建立com/company/Main.java
改成`com.mycompany.Main`后
out/路径中就会改名为变成com/mycompany/Main.java

注意：在windows直接编译的时候不用package com.company这一句话，只有project的时候才用

##windows中java “找不到或无法加载主类”
编译的时候没事，解释运行的时候只有一种形式可是运行，就是cmd进入hello.class所在的文件夹中，运行：
```
java hello
```
（hello.class不行）












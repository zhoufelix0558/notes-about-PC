#Windows10下MarkdownPad预览无法显示
----
2016/4/22 16:32:45 
安装Markdownpad软件完成后
>LivePreview is not working - it displays an error message stating This view has crashed!   

官方的说法是从Win8开始就有这个问题了，解决办法就是安装[Awesomium 1.6.6 SDK](http://markdownpad.com/download/awesomium_v1.6.6_sdk_win.exe)，如果还是不行就再安装 [Microsoft's DirectX End-User Runtimes (June 2010)](http://www.microsoft.com/en-us/download/details.aspx%3Fid%3D8109)

# Markdownpad如果实现代码换行
----------
markdown原生并没有换行
- 你在markdownpad 的`工具`的`选项` 中选择markdown那项，将处理器选成`Github Flavored Markdown`就可以实现代码换行了。
- 按Tab键也可以调出代码框（markdown原生也行）
- 行尾输入两个空格，输出换行，但是和换行符不相同（markdown原生也行）
```
include<stdio.h>
int main(){}
```

# MarkdownPad 使用 MathJax 
----------
- 在MarkdownPad中，点击`Tools` > `Options` > `Advanced` > `HTML Head Editor`，这个是自定义头文件。添加下列内容：
```
<script type="text/javascript" src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML">
</script>
```
这样在网页预览(F6)，**网页中<head>中会引用这段代码（添加本地地址的话不能显示）**，你写的公式就可以显示啦。
- 当然你也可以下载MathJax到本地，添加本地连接到上面的位置，原理都一样。   
示例：
When \\( a \ne 0 \\), there are two solutions to \\(ax^2 + bx + c = 0\\) and they are:
$$ x = {-b \pm \sqrt{b^2-4ac} \over 2a} $$
----------
# 消除table表格边框的距离
----------
由于解析md文件的时候兼容html，所以html的语句都能用。  
在css文件中的table的定义中加上一个属性：`border-collapse:collapse;`
示例：

| 项目        | 价格   |  数量  |
| ----   | :---:  | :---:  |
| 计算机     | \$1600 |   5     |

---
#markdownpad支持代码高亮解决方案
- 在`tools` > `options`中将markdown处理器选项选成github风格（online）的。下面用github账号登陆一下，然后就能支持代码高亮了。


#markdownpad怎么插入图片
-----
此方法输出html/pdf都能正常显示，但是在实时预览中不显示。
```
![cerf](xx.PNG)
```
其中xx.PNG和md文件在同一个目录下。
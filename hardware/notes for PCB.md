###双面焊盘网络问题
我做了一个双面焊盘，赋予其标号之后发现正反面的焊盘都变成了同一个net。

###器件对齐
原来有元件对齐的功能，我之前一直以为没有。使用这个功能需要切换工作模式，即在Application Mode中切换成Placement Edit 就行了。


### 常见问题
1. 有一段时候find窗口里面个别的类型隐藏看不见了，这时候可以右键选择Application Mode中的General Edit就行了。

2. 新添加的元件desref丝印没有线宽：这时候点击Edit->change，然后改一些参数后点击没有线宽的text就行了。

3. Artwork生成的Gerber文件没有边框，生成Artwork的时候将没有undefined line width 填上合适的线宽。（我之前遇到一个问题：我自己建立的R0402,C0402等等元件的封装里面Board Geometry层的OUtline有方框，导致gerber文件出现大量方框，后来我把这些封装的outline转到了Package Geometry层中不常用的层去了，然后就行了）。

4. 钻孔文件怎么弄？
   首先先点击Manufacture->NC->Drill Customization,在里面电机自动生成钻孔符号，这一步完成后相关图层才会出现不同的钻孔符号和位置。
   然后再点击Manufacture->NC->Drill Legend,点击OK会生成一张钻孔表格，放在电路板旁边就行。


###always #0.5 clk=~clk;不起振
我看modelsim里面发现clock一直是z状态。
后来上网发现原来是没有定义clock最初状态

```
intial begin
clock = 0;
...

always #0.5 clk=~clk;
endmodule

```



###新建的Quartus项目不成生成Simulation的testbench文件
这个可能是没有在Simulation根目录中指定仿真软件的类型，打开Setting->EDA tool settings，将这地方的Simulation工具改成ModelSim。
然后点击Processing->Start->Start Testbench Template Writer就能自动生成testbench文件。

###port must be connected to a structural net expression
引用IP核的时候，IP核里面的output变量在外部引用程序中定义为wire和output类型。


###Quartus11.0有时会出现not support device
一般直接打开qpf文件编译的时候会出现这个问题。这时候打开Quartus11.0软件，然后在软件里面打开qpf文件就行了。
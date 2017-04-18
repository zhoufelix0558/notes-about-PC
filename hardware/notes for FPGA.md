###还是关于Quartus仿真的问题。
现在明白了为什么之前仿真不行了。
不同的.v文件设置为top文件的时候所RTL仿真的不一样。比如我之前将ddr2_example_top.v的文件设置成top entity，用modelsim仿真的时候就跑的是
ddr2_example_top.v里面的代码。（原来.v文件也能当作testbench使用）

后来发现还是有一定问题：在testbench中我不知道怎么去激励mem_clk，我看了下官方的例程，超级麻烦。关于DDR2的仿真暂时放弃，之后慢慢调试。

###关于Quartus无法进行仿真的问题。
最开始的时候我拷贝了一份AX515关于ddr2 test的项目，然后试着编译发现报错说我主文件有好几个变量没有define，事实上是有的（这点预示着modelsim有点问题。。）
后来我将这几个变量放在了最开始的地方就不报错了。
但是还是无法仿真，有报错说 ddr2_example_top not defined。解不了。

最后是了好多遍，终于有一遍成功了！！！

看看文件发现这次主文件中编码都是正确的（之前编码变成乱码，但是是主时钟出现的，我没有在意，没想到差别这么大）



###我用逻辑分析仪采集fpga上面的信号
测试信号：pll产生的80Mhz的信号。
采样频率为250MHz的时候，发现有个别方波没抓到。
后来我将采样频率设置为500MHZ就好了。

说明采样频率真的要在时钟频率5倍以上才可靠，最好接上地线，这样测量的准确点。







###怎么禁止Quartus禁止优化未使用的reg变量。
```
`define LENGTH 15000
(* keep *) reg[`LENGTH-1:0] testdemo;
```
不同的软件可能禁止优化的指令不一样。

Cyclone IV EP4CE115有11480个逻辑单元。
Total logic elements	15,000 / 15,408 ( 97 % )
Total combinational functions	15,000 / 15,408 ( 97 % )
Dedicated logic registers	15,000 / 15,408 ( 97 % )
Total registers	15000


###SignalTap一直报错的原因：
这个bug是我自己造成的，但是发现起来比较困难。
SignalTap使用的时候系统会调用自己库文件`...\altera\12.1\quartus\libraries\megafunctions\sld_signaltap.vhd`
后来我无意中错按了键盘（后来我才知道是我错案了键盘），保存了文件，就再也编译不过去了。
一直出现：Error (10500): VHDL syntax error at Vhdl1.vhd(218) near text "generic",expecting "entity", or "architecture", or "use", or "library", or "package", or "configuration".
我不懂VHDL语言，所以一直google这个问题，发现没有人遇到过这种问题。。。

后来发现sld_signaltap.vhd同目录下有一个sld_signaltap.vhd.bak。（原来Quartus界面下修改vhd文件后会将修改前的文件备份，这个功能好赞）。
对比后发现
sld_signaltap.vhd（20549bytes）
sld_signaltap.vhd.bak（20596bytes）
通过软件的智能对比发现原本的代码是
```
entity sld_signaltap is
generic(
```
被我无意间删去了上半句，变成了
```
generic(
```
把文件变回来就行了。

###SystemVerilog和generate并行赋值语法的完整代码
normal_operation.v
```
`timescale 1ns/1ps


module normal_operation(clk,data_in,data_out);
input clk;
input[8:0][8:0] data_in;
output reg[8:0][8:0] data_out;

always@(posedge clk);

genvar i,j; 
generate 
for( i=0; i<8; i=i+1 ) 
begin : outer 
//    for (j=0;  j<8; j=j+1 ) 
//        begin : inner 
        assign data_out[i][7:0] = data_in[i][7:0]+1; 		//程序做到了完全实时，wire型连线
    end 
//end 
endgenerate


endmodule
```

normal_op_testbench.vt
```
`timescale 1ns/1ps


module normal_op_testbench;

	// Inputs
reg clk;
reg[8:0][8:0] data_in;
wire[8:0][8:0] data_out;

	// Instantiate the Unit Under Test (UUT)
normal_operation notest(
.clk(clk),
.data_in(data_in),
.data_out(data_out)
);

	initial begin
		// Initialize Inputs
		clk = 0;
		data_in[0] = 8'd12;
	
		// Wait 100 ns for global reset to finish
		#100;     
		// Add stimulus here
		data_in[1] = 8'd23;
		data_in[3] = 8'd40;
		#1
		data_in[1] = 8'd33;
		data_in[4] = 8'hff; 
		#2
		data_in[2] = 8'd45;		
		#3
		data_in[2] = 8'd78;
		
		#2000;
      //$stop;
	end
   
   always #0.5 clk = ~ clk; //产生1ns的时钟

   
endmodule
```

###Quartus II怎么缩放波形图
通过键盘键中的"+"和"-"键来缩放波形。

###关于module和testbench输入输出所用的类型的问题
在module中，input一定是wire，output可以是wire也可以是reg。
在testbench中，input是reg，output是wire。
基本上两者是相反的。
这样simulation就能跑通了


###Quartus II怎么支持SystemVerilog？
打开菜单Assignment->Setting->Analysis & Synthesis Settings->Verilog HDL Input。在里面将verilog version选成SystemVerilog
SystemVerilog的新功能详见https://zh.wikipedia.org/wiki/SystemVerilog

###generate的妙用。
一般verilog中不能定义多位数组，但是SystemVerilog是支持这个功能的。
```
`timescale 1ns/1ps
module normal_operation(clk,data_in,data_out);
input clk;
input[8:0][8:0] data_in;
output reg[8:0][8:0] data_out;

always@(posedge clk);

	genvar i,j; 
	generate 
	for( i=0; i<8; i=i+1 ) 
	begin : outer 
	    for (j=0;  j<8; j=j+1 ) 
	        begin : inner 
	        assign data_out[i][j] = data_in[7-i][7-j]; 
	    end 
	end 
	endgenerate
endmodule
```




###当使用ModelSim® 10.2编译Quartus® II 12.1 SP1库时会看到该错误。请注意Quartus® II 12.1 SP1官方支持ModelSim10.1b。
(vlog-2244) Variable 'mega' is implicitly static. You must explicitly declare it as static or automatic.
另外,对于Verilog HDL仿真,编辑文件<Quartus II installation directory>/eda/sim_lib/altera_lnsim.sv。添加automatic到1150行和10397行。
line 1158:
            automatic integer mega = 1000000;
line 10397:
            automatic real factor = 10**9;
 对于VHDL仿真,通过以下命令隐藏错误信息:
vlog -sv -suppress 2244 altera_lnsim_for_vhdl.sv





###Quartus怎么做仿真？
3/3/2017 11:04:35 PM 
调了半天，发现Quartus自带的ModelSim-Altera不好用，最后看网上Quarus 可以直接调用Modelsim
参见《ModelSim初学者教程.pdf》或者
1. 建立好项目，并且顺利编译。
2. Processing->Start->Start Test Bench Template Writer(Verilog HDL生成的文件后缀名为.vt，位于工程文件夹simulatin/modelsim中)。在里面加上测试代码（诸如#100 axxx之类的）。
	testbench中的module名称可以更改（例：add_testbench）
	testbench规定输入一律为reg型变量，输出为wire型。可以有不可综合的语句；for，while等。
3. Tools->Options->EDA Tool Options.将ModelSim指向ModelSim.exe安装路径（比如X：/modeltech_10.0c/win64）
4. Assignments->Settings->Simulation->Compile test bench进入Test Benches...
	benchname写成testbench文件中的model名。File Name指向想要添加的testbench文件（说明能同时建立很多个testbench文件）。
5. Tools->Run EDA Simulation Tool->EDA RTL Simulation，然后ModelSim就会被调用起来自动仿真波形。



###Quartus注意事项
3/3/2017 8:50:21 PM 
1. 项目不能有中文路径名。
2. 不能直接打开dpf文件（好像compile的时候户籍出现license相关的问题），可以先打开Quartus再在里面打开项目


###模块之间的引用
3/3/2017 8:55:29 PM 
终于搞懂了，调通了。
《Verilog 数字系统设计教程-夏宇闻》中有一段代码：
```
//文件aaa.v
module aaa(a,b,out);
	input a,b;
	output out;
	wire out;
	assign out=a^b;
endmodule

//文件bbb.v
`include "aaa.v"
module bbb(c,d,e,out);
	input c,d,e;
	output out;
	wire out_a;
	wire out;
	aaa aaa(.a(c),.b(d),.out(out_a));
	assign out = e&out_a;
endmodule
```

我实际compile通过的代码：
```
//文件my_and.v
module my_and(a,b,c);  //;号容易漏掉
input a,b;  //输入a由开关KEY1决定，0：按下，1：未按下
                   //输入b由开关KEY2决定，0：按下，1：未按下
output c;  //输出c由LED显示， 0：点亮，1：熄灭

add_test add_test(.A(a),.B(b),.C(c));

endmodule

//文件and_test.v
module add_test(A,B,C); 
input A,B; 
output C; 
assign C=A&B;
endmodule

```
注意事项：
1. 一般一个文件队医哦那个一个模块比较好。
2. 新建文件模块File->New->Verilog HDL File,保存的时候直接和主模块放在同一个文件夹就行。编译完成后系统自动决定继承关系。
3. 发现同文件夹的模块引用的时候不用写include ，不然会报出重复定义的错误。



###IP核的调用
3/3/2017 9:24:16 PM 
没想到模块调用学好后，IP核的调用这么方便就学好了。
调用IP核的步骤：Tools-> Megawizard Plug-In Manager->选择要使用的IP核和生成文件的保存路径（放在和主文件同文件夹就行）。
例如我生成了一个加法模块叫add_IP（文件保存名为add_IP.v）
打开文件复制模块的声明：
```
//文件add_IP.v
module add_IP (
	dataa,
	datab,
	result);
```

引用的时候写成下面的这种形式：
```
module my_and(a,b,c);
input a,b; 
output c; 

add_IP add_IP (
	.dataa(a),
	.datab(b),
	.result(c));

endmodule
```
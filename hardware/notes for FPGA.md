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
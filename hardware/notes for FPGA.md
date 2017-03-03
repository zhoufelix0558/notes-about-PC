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
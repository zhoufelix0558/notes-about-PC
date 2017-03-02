###STM32
3/2/2017 7:29:59 PM 
1. 函数中申请过大的数组，仿真后发现HardFault_Handler错误：在启动文件中把栈的容量变大就行。
2. 逻辑分析仪会对MISO的电压造成波动（1/f宽度的毛刺，MCU引脚作为输入，上拉能力很弱），如果是MCU是上拉模式，那么在MISO线上接1.5K电阻到VCC(3V),毛刺现象就消失了。
3. 检查SPI配置的时候可以将MISO和MOSI线接在一起，检查自己发送的是否能收到。
4. STM32F031-Nucleo用CubeMX来生成SPI的代码，但是MOSI一直不出数据。后来发现CubeMX没有自动SPI enable（SPI1->CR1[6]:SPI enable）,将这位置1就行了。
###STM32
3/2/2017 7:29:59 PM 
1. 函数中申请过大的数组，仿真后发现HardFault_Handler错误：在启动文件中把栈的容量变大就行。
2. 逻辑分析仪会对MISO的电压造成波动（1/f宽度的毛刺，MCU引脚作为输入，上拉能力很弱），如果是MCU是上拉模式，那么在MISO线上接1.5K电阻到VCC(3V),毛刺现象就消失了。
3. 检查SPI配置的时候可以将MISO和MOSI线接在一起，检查自己发送的是否能收到。
4. STM32F031-Nucleo用CubeMX来生成SPI的代码，但是MOSI一直不出数据。后来发现CubeMX没有自动SPI enable（SPI1->CR1[6]:SPI enable）,将这位置1就行了。



###STM32F0 SPI一直输出16个时钟
之前F1系列SPIx->CR1会有一个DFF（Data Frame Format）供选择8位或者是16位。现在F0系列参考手册没有DFF这个位。
如果还是直接写 `SPI1->DR = 0x23;`就会出现16个Clock。
SPI结构体定义DR这个成员是16位，因此【SPI2->DR=(uint8_t)TxData;】是把一个8位数据写到16位指针所指的地址；
用下面的函数传输数据就没问题了。
```
void SPI_SendData8(SPI_TypeDef* SPIx, uint8_t Data)
{
  uint32_t spixbase = 0x00;
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  spixbase = (uint32_t)SPIx; 
  spixbase += 0x0C;
  
  *(__IO uint8_t *) spixbase = Data;
}
```
具体情况需要看汇编语言。
# 关于
本节介绍UART0，介绍该设备的原因在于，输入中断只能由UART0产生。

UART0实际上就是设备PL011的实现。

本节还引入了bitsAnySet和bitsNonSet两个位测试函数。

从本节开始，我们将使用UART0作为输入输出的接口。对应QEMU调试选项有所变化。

对于PL011设置而言，不仅需要GPIO选择功能ALT0，还需要设置UART的时钟频率(默认48MHz，需要设置为4MHz)。
设置UART时钟频率的方式有两种：配置文件和MailBox，我们选择前者。

在处理中断中，我们在handleIRQ中增加了PL011的中断处理，根据PL011的文档，中断状态的消除可有两种方式：读取FIFO
使其降低到触发水平以下，或者清除中断标志。
由于我们只需要接收中断，所以启用该中断即可。UARTRXINTR。

对于树莓派而言，只有启用FIFO模式，字符才能被正确接收。

# 测试程序
在测试程序中，我们使用了PL011的waitInput方法替换此前的循环，等待用户确认输入，然后
才继续执行。

我们启用了输入中断，每输入一个字符，屏幕上都会显示相应字符。

# 状态
已完成
树莓派：已测试，但是已知存在一些不足。经过测试，单次中断最多接受的输入不超过16个字符，这与
最终raspiOS测试的结果大相径庭。而我们采用的几乎都是一模一样的初始化过程和处理过程。
我们将在后面有需要再处理这个问题。
但是，在8_1的程序中，输入确实能够正常处理超过16个字符。因此这个问题以一种不为人知的方式解决了。

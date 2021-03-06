#include <cstdio>
#include <driver/gpio/GPIO.h>
#include <new>
#include <generic/util.h>
#include <generic/IntegerFormatter.h>
#include <memory/MemoryManager.h>
#include <runtime_def.h>
#include <driver/uart/BCM2835MiniUART.h>
#include <io/char/BCM2835MiniUARTWriter.h>

constexpr size_t GPIO_BASE = 0x3F200000 ;
constexpr size_t UART1_BASE = 0x3F215000 ;
constexpr size_t RAM_SIZE = 1024*1024*1024 - 64*1024*1024; // 1GB - 64MB
extern uint64_t __free_ram_start[];

extern "C" void init();

__asm__(
	".section .text.boot \n\t"
	"mrs     x0, mpidr_el1 \n\t"
	"and     x0, x0, #0b11 \n\t"
	"cmp     x0,#0 \n\t"
	"b.eq      2f \n\t"
	"1:  		\n\t"
	"wfi         \n\t"
	"b       1b	\n\t"
	"2: \n\t"
	"ldr     x0, =__stack_top \n\t"
	"mov     sp,x0 \n\t"
	"bl      init \n\t"
	"b       1b \n\t"
);
__attribute__((section(".text.boot")))
void init()
{
	new (&uart1) BCM2835MiniUART(UART1_BASE);
	new (&uart1Writer) BCM2835MiniUARTWriter(&uart1);
	new (&kout) Output(&uart1Writer);

	new (&gpio) GPIO(GPIO_BASE);

	// DOCME 倘若去掉下面这两行，则树莓派不能输出信息
	//       当然，正确的输出还需要适当的初始化
	//       从这里，就可以看出QEMU模拟与树莓派
	//       的差异，前者无需额外设置，后者还需
	//       许多设置。
	gpio.selectAltFunction(14, GPIO::ALT_5);
	gpio.selectAltFunction(15, GPIO::ALT_5);

	uart1.init();

	// 之前设置好输出，现在初始化内存管理器
	new (&mman) MemoryManager(
			__free_ram_start,
			RAM_SIZE - reinterpret_cast<size_t>(__free_ram_start),
			true
	);


	char *buf=mman.allocateAs<char*>(1024);

	size_t n=20;
	while(n--)
	{
		kout << "allocated buf = " << Hex(buf) << "\n";
		delayCPU(1000,1000);
	}
}


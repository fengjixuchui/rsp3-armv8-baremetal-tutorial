/*
 * runtime_def.h
 *
 *  Created on: Jun 10, 2018
 *      Author: 13774
 */

#ifndef INCLUDE_RUNTIME_DEF_H_
#define INCLUDE_RUNTIME_DEF_H_
#include <cstddef>

class GPIO;
class BCM2835MiniUART;
class BCM2835MiniUARTWriter;
class Output;
class MemoryManager;
// class InterruptManager; // 替换
class BCM2835InterruptManager;
template <class IntManager>
     class ExceptionHandler;
class BCM2835SystemTimer;
class PL011;
class PL011Writer;

// io
extern GPIO gpio;
extern BCM2835MiniUART uart1;
extern PL011           uart0;
extern BCM2835MiniUARTWriter uart1Writer;
extern PL011Writer     uart0Writer;
extern Output kout;

// error
#define FATAL "[FATAL] "
#define INFO  "[INFO] "
#define WARNING "[WARNING] "

// memory
extern MemoryManager mman;

// exception
//extern InterruptManager                    intMan;
extern BCM2835InterruptManager            bcm2835IntMan;
extern ExceptionHandler<BCM2835InterruptManager> excpHandler;


//timer
extern BCM2835SystemTimer sysTimer;
extern size_t          sysTimerTick;

#endif /* INCLUDE_RUNTIME_DEF_H_ */

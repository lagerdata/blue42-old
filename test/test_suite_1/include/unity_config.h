#ifndef _UNITY_CONFIG_INCLUDED
#define _UNITY_CONFIG_INCLUDED
//-------------------------MODULES USED-------------------------------------
#include "uart_drv.h"


//-------------------------DEFINITIONS AND MACORS---------------------------



#define UNITY_OUTPUT_CHAR(a)    putc(a)
#define UNITY_OUTPUT_START()    init_putc()
#define UNITY_OUTPUT_FLUSH()    flush_putc()
#define UNITY_OUTPUT_COMPLETE() close_putc()


//-------------------------TYPEDEFS AND STRUCTURES--------------------------



//-------------------------EXPORTED VARIABLES ------------------------------
#ifndef _UNITY_CONFIG_C_SRC



#endif



//-------------------------EXPORTED FUNCTIONS-------------------------------
void int_putc(void);
void flush_putc(void);
void close_putc(void);
void putc(char c);


#endif

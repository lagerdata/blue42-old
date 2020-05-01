#ifndef _UNITY_CONFIG_INCLUDED
#define _UNITY_CONFIG_INCLUDED
//-------------------------MODULES USED-------------------------------------
#include "uart_drv.h"


//-------------------------DEFINITIONS AND MACORS---------------------------



#define UNITY_OUTPUT_CHAR(a)    stdout_putc(a)
#define UNITY_OUTPUT_START()    stdout_init_putc()
#define UNITY_OUTPUT_FLUSH()    stdout_flush_putc()
#define UNITY_OUTPUT_COMPLETE() stdout_close_putc()


//-------------------------TYPEDEFS AND STRUCTURES--------------------------



//-------------------------EXPORTED VARIABLES ------------------------------
#ifndef _UNITY_CONFIG_C_SRC



#endif



//-------------------------EXPORTED FUNCTIONS-------------------------------
void stdout_init_putc(void);
void stdout_flush_putc(void);
void stdout_close_putc(void);
void stdout_putc(char c);


#endif

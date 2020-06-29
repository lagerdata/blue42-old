#ifndef _UNITY_CONFIG_INCLUDED
#define _UNITY_CONFIG_INCLUDED
//-------------------------MODULES USED-------------------------------------
#include "nrf52_target_uart.h"


//-------------------------DEFINITIONS AND MACORS---------------------------



#define UNITY_OUTPUT_CHAR(a)    nrf52_target_putc(a)
#define UNITY_OUTPUT_START()    nrf52_target_init_putc()
#define UNITY_OUTPUT_FLUSH()    nrf52_target_flush_putc()
#define UNITY_OUTPUT_COMPLETE() nrf52_target_close_putc()


//-------------------------TYPEDEFS AND STRUCTURES--------------------------



//-------------------------EXPORTED VARIABLES ------------------------------
#ifndef _UNITY_CONFIG_C_SRC



#endif



//-------------------------EXPORTED FUNCTIONS-------------------------------



#endif

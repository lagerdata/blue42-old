#define _MAIN_C_SRC

//-------------------------MODULES USED-------------------------------------
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


//Free Rtos Includes
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

//-------------------------DEFINITIONS AND MACORS---------------------------



//-------------------------TYPEDEFS AND STRUCTURES--------------------------



//-------------------------PROTOTYPES OF LOCAL FUNCTIONS--------------------



//-------------------------EXPORTED VARIABLES ------------------------------



//-------------------------GLOBAL VARIABLES---------------------------------



//-------------------------EXPORTED FUNCTIONS-------------------------------
int main(void)
{

    //Start FreeRTOS scheduler
    vTaskStartScheduler();
    while(1);

    return 0;
}


void vApplicationStackOverflowHook( TaskHandle_t xTask, signed char *pcTaskName )
{
    while(1);

}


void vApplicationMallocFailedHook( void )
{
    //while(1);

}

void vApplicationTickHook( void )
{

}

void vApplicationIdleHook( void )
{

}

//-------------------------LOCAL FUNCTIONS----------------------------------

#define _MAIN_TEST1_C_SRC

//-------------------------MODULES USED-------------------------------------
#include "unity.h"
#include "test1.h"
#include "uart_drv.h"

//-------------------------DEFINITIONS AND MACORS---------------------------

//-------------------------TYPEDEFS AND STRUCTURES--------------------------



//-------------------------PROTOTYPES OF LOCAL FUNCTIONS--------------------



//-------------------------EXPORTED VARIABLES ------------------------------



//-------------------------GLOBAL VARIABLES---------------------------------
static uart_hdl_t * gp_uart_hdl;


//-------------------------EXPORTED FUNCTIONS-------------------------------





int main(void)
{
    uart_params_t uart_params;
    uart_params.baudrate = B115200;
    uart_params.stop_bits = STOP_BITS_1;
    uart_params.parity = PARITY_NONE;
    uart_params.flow_control = false;
    uart_params.tx_pin = 6;
    uart_params.rx_pin = 8;
    uart_params.cts_pin = 0xffffffff;
    uart_params.rts_pin = 0xffffffff;
    uart_params.fp_irq_cb = NULL;
    gp_uart_hdl = uart_drv_init(&uart_params);

    static char buf[] = "Hello World!\r\n";
    uart_drv_tx(gp_uart_hdl, buf, sizeof(buf));
    uart_drv_unit(gp_uart_hdl);

    UnityBegin("test1.c");
    RUN_TEST(test_freertosSystickCorrectFreq);
    //run test 2

    UnityEnd();
    while(1);
    return 0;
}


void HardFault_Handler(void)
{

    while(1);
}

//-------------------------LOCAL FUNCTIONS----------------------------------

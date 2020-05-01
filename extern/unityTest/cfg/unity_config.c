#define _UNITY_CONFIG_C_SRC

//-------------------------MODULES USED-------------------------------------
#include "uart_drv.h"
#include "unity_config.h"

//-------------------------DEFINITIONS AND MACORS---------------------------



//-------------------------TYPEDEFS AND STRUCTURES--------------------------



//-------------------------PROTOTYPES OF LOCAL FUNCTIONS--------------------



//-------------------------EXPORTED VARIABLES ------------------------------



//-------------------------GLOBAL VARIABLES---------------------------------
static uart_hdl_t * gp_uart_hdl;
static char g_byte;

//-------------------------EXPORTED FUNCTIONS-------------------------------
void stdout_init_putc(void)
{
    uart_params_t uart_params;
    uart_params.baudrate = B115200;
    uart_params.stop_bits = STOP_BITS_1;
    uart_params.parity = PARITY_NONE;
    uart_params.flow_control = false;
    uart_params.tx_pin = 6;
    uart_params.rx_pin = 8;
    uart_params.fp_irq_cb = NULL;
    gp_uart_hdl = uart_drv_init(&uart_params);
}

void stdout_putc(char c)
{
    g_byte = c;

    uart_drv_tx(gp_uart_hdl, &g_byte, 1);
}


void stdout_flush_putc(void)
{
    uart_drv_unit(gp_uart_hdl);
    stdout_init_putc();
}

void stdout_close_putc(void)
{
    uart_drv_unit(gp_uart_hdl);
}

//-------------------------LOCAL FUNCTIONS----------------------------------

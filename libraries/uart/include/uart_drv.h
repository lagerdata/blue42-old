#ifndef _UART_DRV_INCLUDED
#define _UART_DRV_INCLUDED
//-------------------------MODULES USED-------------------------------------
#include <stdint.h>
#include <stdbool.h>
#include <string.h>



//-------------------------DEFINITIONS AND MACORS---------------------------
#define UART_OK 0
#define UART_ERROR_IN_PROGRESS (-1)
#define UART_ERROR_RX_BUSY (-2)
#define UART_ERROR_INTERNAL (-3)
#define UART_ERROR_FORBIDDEN (-4)


typedef enum baud_rate{
    B1200 = 1,
    B2400,
    B4800,
    B9600,
    B14400,
    B19200,
    B28800,
    B31250,
    B38400,
    B56000,
    B57600,
    B76800,
    B115200,
    B230400,
    B250000,
    B460800,
    B921600,
    B1000000
}baudrate_e;

typedef enum stop_bits{
    STOP_BITS_1 = 1,
    STOP_BITS_2
}stop_bits_e;

typedef enum parity{
    PARITY_NONE = 1,
    PARITY_EVEN,
    PARITY_ODD,
    PARITY_ZERO,
    PARITY_ONE
}parity_e;

typedef enum data_lenght{
    DATA_LEN_5 = 1,
    DATA_LEN_6,
    DATA_LEN_7,
    DATA_LEN_8
}data_length_e;


typedef enum uart_state{
    UART_NO_STATUS = 0,
    UART_RX_DONE = 1,
    UART_TX_DONE = 2,
    UART_ERROR
}uart_state_t;

//-------------------------TYPEDEFS AND STRUCTURES--------------------------
typedef struct uart_hdl uart_hdl_t;

typedef struct cb_info{
    char * p_txrx_buf;
    uint32_t txrx_buf_len;
    uart_state_t uart_state;
}cb_info_t;

typedef void(* 	irq_handler_cb_t )(cb_info_t *);

typedef struct uart_params{
    baudrate_e baudrate;
    stop_bits_e stop_bits;
    parity_e parity;
    bool flow_control;
    uint32_t tx_pin;
    uint32_t rx_pin;
    uint32_t rts_pin;
    uint32_t cts_pin;
    uint32_t int_prio;
    irq_handler_cb_t fp_irq_cb;
}uart_params_t;


//-------------------------EXPORTED VARIABLES ------------------------------
#ifndef _UART_DRV_C_SRC



#endif



//-------------------------EXPORTED FUNCTIONS-------------------------------
uart_hdl_t * uart_drv_init(uart_params_t const * const p_uart_params);
void uart_drv_unit(uart_hdl_t * p_uart_hdl);
int32_t uart_drv_tx(uart_hdl_t * p_uart_hdl, char const * const p_tx_buf, size_t tx_len);
int32_t uart_drv_rx(uart_hdl_t * p_uart_hdl, char * const p_rx_buf, size_t rx_len);
#endif

#define _UART_DRV_C_SRC

//-------------------------MODULES USED-------------------------------------
#include "nrf.h"
#include "nrf_gpio.h"
#include "nrf_uart.h"

#include "uart_drv.h"
//-------------------------DEFINITIONS AND MACORS---------------------------



//-------------------------TYPEDEFS AND STRUCTURES--------------------------
struct uart_hdl{
    NRF_UART_Type * p_reg;
    irq_handler_cb_t fp_cb;
    char * p_rx_buf;
    uint32_t rx_buf_len;
    char * p_rx_buf_2;
    uint32_t rx_buf_len_2;
    uint32_t rx_cnt;
    char * p_tx_buf;
    uint32_t tx_buf_len;
    uint32_t tx_cnt;
};


//-------------------------PROTOTYPES OF LOCAL FUNCTIONS--------------------
static void rx_byte(void);
static void rx_done_event(size_t bytes, char * p_data);
static void tx_byte(void);

//-------------------------EXPORTED VARIABLES ------------------------------



//-------------------------GLOBAL VARIABLES---------------------------------
static uart_hdl_t g_uart_hdl;


//-------------------------EXPORTED FUNCTIONS-------------------------------
uart_hdl_t * uart_drv_init(uart_params_t const * const p_uart_params)
{

    if(NULL == g_uart_hdl.p_reg){
        g_uart_hdl.p_reg = NRF_UART0;
    }else{
        return NULL;
    }

    //Enable TX Pin
    nrf_gpio_pin_set(p_uart_params->tx_pin);
    nrf_gpio_cfg_output(p_uart_params->tx_pin);


    //Enable RX Pin
    nrf_gpio_cfg_input(p_uart_params->rx_pin, NRF_GPIO_PIN_NOPULL);

    nrf_uart_baudrate_t baudrate = NRF_UART_BAUDRATE_9600;
    switch(p_uart_params->baudrate){
        case B1200:{
            baudrate = NRF_UART_BAUDRATE_1200;
            break;
        }

        case B2400:{
            baudrate = NRF_UART_BAUDRATE_2400;
            break;
        }

        case B4800:{
            baudrate = NRF_UART_BAUDRATE_9600;
            break;
        }

        case B9600:{
            baudrate = NRF_UART_BAUDRATE_9600;
            break;
        }

        case B14400:{
            baudrate = NRF_UART_BAUDRATE_14400;
            break;
        }

        case B19200:{
            baudrate = NRF_UART_BAUDRATE_19200;
            break;
        }

        case B28800:{
            baudrate = NRF_UART_BAUDRATE_28800;
            break;
        }

        case B31250:{
            baudrate = NRF_UART_BAUDRATE_31250;
            break;
        }

        case B38400:{
            baudrate = NRF_UART_BAUDRATE_38400;
            break;
        }

        case B56000:{
            baudrate = NRF_UART_BAUDRATE_56000;
            break;
        }

        case B57600:{
            baudrate = NRF_UART_BAUDRATE_57600;
            break;
        }

        case B76800:{
            baudrate = NRF_UART_BAUDRATE_76800;
            break;
        }

        case B115200:{
            baudrate = NRF_UART_BAUDRATE_115200;
            break;
        }

        case B230400:{
            baudrate = NRF_UART_BAUDRATE_230400;
            break;
        }

        case B250000:{
            baudrate = NRF_UART_BAUDRATE_250000;
            break;
        }

        case B460800:{
            baudrate = NRF_UART_BAUDRATE_460800;
            break;
        }

        case B921600:{
            baudrate = NRF_UART_BAUDRATE_921600;
            break;
        }

        case B1000000:{
            baudrate = NRF_UART_BAUDRATE_1000000;
            break;
        }

        default:{
            return NULL;
        }
    }
    nrf_uart_baudrate_set(NRF_UART0, baudrate);

    nrf_uart_parity_t parity = NRF_UART_PARITY_EXCLUDED;
    switch(p_uart_params->parity){
        case PARITY_NONE:{
            parity = NRF_UART_PARITY_EXCLUDED;
            break;
        }
        case PARITY_EVEN:
        case PARITY_ODD:{
            parity = NRF_UART_PARITY_INCLUDED;
            break;
        }
        default:{
            return NULL;
        }
    }

    nrf_uart_hwfc_t hwfc = p_uart_params->flow_control?NRF_UART_HWFC_ENABLED:NRF_UART_HWFC_DISABLED;

    nrf_uart_configure(NRF_UART0, parity, hwfc);

    nrf_uart_txrx_pins_set(NRF_UART0, p_uart_params->tx_pin, p_uart_params->rx_pin);

    if(p_uart_params->flow_control){
        nrf_gpio_cfg_input(p_uart_params->cts_pin, NRF_GPIO_PIN_NOPULL);
        nrf_gpio_pin_set(p_uart_params->rts_pin);
        nrf_gpio_cfg_output(p_uart_params->rts_pin);
    }
    nrf_uart_hwfc_pins_set(NRF_UART0, p_uart_params->rts_pin, p_uart_params->cts_pin);


    //setup interrupts
    if(NULL != p_uart_params->fp_irq_cb){
        g_uart_hdl.fp_cb = p_uart_params->fp_irq_cb;
        nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_TXDRDY);
        nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_RXTO);
        nrf_uart_int_enable(NRF_UART0, NRF_UART_INT_MASK_TXDRDY | NRF_UART_INT_MASK_RXTO);
        NRFX_IRQ_PRIORITY_SET(nrfx_get_irq_number((void *)NRF_UART0), p_uart_params->int_prio);
        NRFX_IRQ_ENABLE(nrfx_get_irq_number((void *)NRF_UART0));
    }else{
        g_uart_hdl.fp_cb = NULL;
    }

    nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_ERROR);
    nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_RXDRDY);
    nrf_uart_task_trigger(NRF_UART0, NRF_UART_TASK_STARTRX);

    nrf_uart_enable(NRF_UART0);
    g_uart_hdl.rx_buf_len = 0;
    g_uart_hdl.rx_buf_len_2 = 0;
    g_uart_hdl.tx_buf_len = 0;

    return &g_uart_hdl;

}

void uart_drv_unit(uart_hdl_t * p_uart_hdl)
{
    nrf_uart_disable(p_uart_hdl->p_reg);
    if(NULL != g_uart_hdl.fp_cb){
        nrf_uart_int_disable(NRF_UART0, NRF_UART_INT_MASK_RXDRDY |
                         NRF_UART_INT_MASK_TXDRDY |
                         NRF_UART_INT_MASK_ERROR  |
                         NRF_UART_INT_MASK_RXTO);
        NRFX_IRQ_DISABLE(nrfx_get_irq_number((void *)NRF_UART0));
    }
    //reset pins to defaul
    uint32_t txd = nrf_uart_tx_pin_get(NRF_UART0);
    uint32_t rxd = nrf_uart_rx_pin_get(NRF_UART0);
    uint32_t rts = nrf_uart_rts_pin_get(NRF_UART0);
    uint32_t cts = nrf_uart_cts_pin_get(NRF_UART0);
    nrf_uart_txrx_pins_disconnect(NRF_UART0);
    nrf_uart_hwfc_pins_disconnect(NRF_UART0);

    if (txd != NRF_UART_PSEL_DISCONNECTED){
        nrf_gpio_cfg_default(txd);
    }
    if (rxd != NRF_UART_PSEL_DISCONNECTED){
        nrf_gpio_cfg_default(rxd);
    }
    if (cts != NRF_UART_PSEL_DISCONNECTED){
        nrf_gpio_cfg_default(cts);
    }
    if (rts != NRF_UART_PSEL_DISCONNECTED){
        nrf_gpio_cfg_default(rts);
    }
    nrf_uart_task_trigger(NRF_UART0, NRF_UART_TASK_STOPRX);

    g_uart_hdl.fp_cb = NULL;
}


int32_t uart_drv_tx(uart_hdl_t * p_uart_hdl, char const * const p_tx_buf, size_t tx_len)
{
    if(0 != g_uart_hdl.tx_buf_len){
        return UART_ERROR_IN_PROGRESS;
    }

    g_uart_hdl.tx_buf_len = tx_len;
    g_uart_hdl.p_tx_buf = (char *)p_tx_buf;
    g_uart_hdl.tx_cnt = 0;
    nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_TXDRDY);
    nrf_uart_task_trigger(NRF_UART0, NRF_UART_TASK_STARTTX);

    tx_byte();

    if(NULL == g_uart_hdl.fp_cb){
        size_t const tx_buffer_length = g_uart_hdl.tx_buf_len;
        while(g_uart_hdl.tx_cnt < tx_buffer_length){
            tx_byte();
            while(!nrf_uart_event_check(NRF_UART0, NRF_UART_EVENT_TXDRDY));

        }
        nrf_uart_task_trigger(NRF_UART0, NRF_UART_TASK_STOPTX);
        g_uart_hdl.tx_buf_len = 0;
    }
    return UART_OK;
}

int32_t uart_drv_rx(uart_hdl_t * p_uart_hdl, char * const p_rx_buf, size_t rx_len)
{
    bool second_buffer = false;
    if(NULL != g_uart_hdl.fp_cb){
        nrf_uart_int_disable(NRF_UART0, NRF_UART_INT_MASK_RXDRDY | NRF_UART_INT_MASK_ERROR);
    }

    if(0 != g_uart_hdl.rx_buf_len){
        if(0 != g_uart_hdl.rx_buf_len_2){
            if(NULL != g_uart_hdl.fp_cb){
                nrf_uart_int_enable(NRF_UART0, NRF_UART_INT_MASK_RXDRDY | NRF_UART_INT_MASK_ERROR);
            }
            return UART_ERROR_RX_BUSY;
        }
        second_buffer = true;
    }

    if(false == second_buffer){
        g_uart_hdl.rx_buf_len = rx_len;
        g_uart_hdl.p_rx_buf = (char *)p_rx_buf;
        g_uart_hdl.rx_cnt = 0;
        g_uart_hdl.rx_buf_len_2 = 0;
    }else{
        g_uart_hdl.rx_buf_len_2 = rx_len;
        g_uart_hdl.p_rx_buf_2 = (char *)p_rx_buf;
    }

    if(NULL == g_uart_hdl.fp_cb){
        bool rxrdy;
        bool rxto;
        bool error;
        nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_RXTO);
        do{
            do{
                error = nrf_uart_event_check(NRF_UART0, NRF_UART_EVENT_ERROR);
                rxrdy = nrf_uart_event_check(NRF_UART0, NRF_UART_EVENT_RXDRDY);
                rxto  = nrf_uart_event_check(NRF_UART0, NRF_UART_EVENT_RXTO);
            }while((!rxrdy) && (!rxto) && (!error));
            if(error || rxto){
                break;
            }
            rx_byte();
        }while (g_uart_hdl.rx_buf_len > g_uart_hdl.rx_cnt);
        g_uart_hdl.rx_buf_len = 0;
        if(error){
            return UART_ERROR_INTERNAL;
        }
        if(rxto){
            return UART_ERROR_FORBIDDEN;

        }
        nrf_uart_task_trigger(NRF_UART0, NRF_UART_TASK_STARTRX);

    }else{
        nrf_uart_int_enable(NRF_UART0, NRF_UART_INT_MASK_RXDRDY | NRF_UART_INT_MASK_ERROR);
    }

    return UART_OK;
}

//-------------------------LOCAL FUNCTIONS----------------------------------
static void rx_byte(void)
{
    if (!g_uart_hdl.rx_buf_len){
            nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_RXDRDY);
            // Byte received when buffer is not set - data lost.
            (void) nrf_uart_rxd_get(NRF_UART0);
            return;
    }
    nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_RXDRDY);
    g_uart_hdl.p_rx_buf[g_uart_hdl.rx_cnt] = nrf_uart_rxd_get(NRF_UART0);
    g_uart_hdl.rx_cnt++;
}

static void rx_done_event(size_t bytes, char * p_data)
{

    cb_info_t info;
    info.p_txrx_buf = p_data;
    info.txrx_buf_len = bytes;
    info.uart_state = UART_RX_DONE;
    g_uart_hdl.fp_cb(&info);
}

static void tx_byte(void)
{
    nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_TXDRDY);
    uint8_t txd = g_uart_hdl.p_tx_buf[g_uart_hdl.tx_cnt];
    g_uart_hdl.tx_cnt++;
    nrf_uart_txd_set(NRF_UART0, txd);
}

void nrfx_uart_0_irq_handler(void)
{
    if (nrf_uart_int_enable_check(NRF_UART0, NRF_UART_INT_MASK_ERROR) &&
        nrf_uart_event_check(NRF_UART0, NRF_UART_EVENT_ERROR)){

        nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_ERROR);
        nrf_uart_int_disable(NRF_UART0, NRF_UART_INT_MASK_RXDRDY | NRF_UART_INT_MASK_ERROR);
        nrf_uart_task_trigger(NRF_UART0, NRF_UART_TASK_STOPRX);

        cb_info_t info;
        info.p_txrx_buf = g_uart_hdl.p_rx_buf;
        info.txrx_buf_len = g_uart_hdl.rx_buf_len;
        info.uart_state = UART_ERROR;

        g_uart_hdl.rx_buf_len = 0;
        g_uart_hdl.rx_buf_len_2 = 0;

        g_uart_hdl.fp_cb(&info);
    }else if (nrf_uart_int_enable_check(NRF_UART0, NRF_UART_INT_MASK_RXDRDY) &&
              nrf_uart_event_check(NRF_UART0, NRF_UART_EVENT_RXDRDY)){
        rx_byte();
        if(g_uart_hdl.rx_buf_len == g_uart_hdl.rx_cnt){

            if(g_uart_hdl.rx_buf_len_2 > 0){
                char * p_data = g_uart_hdl.p_rx_buf;
                uint32_t rx_cnt = g_uart_hdl.rx_cnt;

                //switch to secondary buffer
                g_uart_hdl.rx_buf_len = g_uart_hdl.rx_buf_len_2;
                g_uart_hdl.p_rx_buf = g_uart_hdl.p_rx_buf_2;
                g_uart_hdl.rx_buf_len_2 = 0;
                g_uart_hdl.rx_cnt = 0;
                rx_done_event(rx_cnt, p_data);
            }else{
                nrf_uart_int_disable(NRF_UART0, NRF_UART_INT_MASK_RXDRDY | NRF_UART_INT_MASK_ERROR);
                g_uart_hdl.rx_buf_len = 0;
                rx_done_event(g_uart_hdl.rx_cnt, g_uart_hdl.p_rx_buf);
            }
        }
    }

    if (nrf_uart_event_check(NRF_UART0, NRF_UART_EVENT_TXDRDY)){
        size_t const tx_buffer_length = g_uart_hdl.tx_buf_len;
        if(g_uart_hdl.tx_cnt < tx_buffer_length){
            tx_byte();

        }else{
            nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_TXDRDY);
            if(g_uart_hdl.tx_buf_len > 0){
                cb_info_t info;
                info.p_txrx_buf = g_uart_hdl.p_tx_buf;
                info.txrx_buf_len = g_uart_hdl.tx_buf_len;
                info.uart_state = UART_TX_DONE;
                g_uart_hdl.tx_buf_len = 0;
                g_uart_hdl.fp_cb(&info);
            }
        }
    }

    if (nrf_uart_event_check(NRF_UART0, NRF_UART_EVENT_RXTO)){
        nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_RXTO);
        nrf_uart_task_trigger(NRF_UART0, NRF_UART_TASK_STARTRX);
        if(g_uart_hdl.rx_buf_len > 0){
            g_uart_hdl.rx_buf_len = 0;
            rx_done_event(g_uart_hdl.rx_cnt, g_uart_hdl.p_rx_buf);
        }
    }
}

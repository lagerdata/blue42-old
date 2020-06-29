#define _NRF52_TARGET_UART_C_SRC

//-------------------------MODULES USED-------------------------------------
#include <stdint.h>
#include "nrf52_target_uart.h"
//-------------------------DEFINITIONS AND MACORS---------------------------
#define NRF_UART0_BASE 0x40002000UL



//-------------------------TYPEDEFS AND STRUCTURES--------------------------
typedef struct {                                /*!< (@ 0x40002000) UART0 Structure                                            */
  volatile  uint32_t  TASKS_STARTRX;                /*!< (@ 0x00000000) Start UART receiver                                        */
  volatile  uint32_t  TASKS_STOPRX;                 /*!< (@ 0x00000004) Stop UART receiver                                         */
  volatile  uint32_t  TASKS_STARTTX;                /*!< (@ 0x00000008) Start UART transmitter                                     */
  volatile  uint32_t  TASKS_STOPTX;                 /*!< (@ 0x0000000C) Stop UART transmitter                                      */
  volatile const  uint32_t  RESERVED[3];
  volatile  uint32_t  TASKS_SUSPEND;                /*!< (@ 0x0000001C) Suspend UART                                               */
  volatile const  uint32_t  RESERVED1[56];
  volatile uint32_t  EVENTS_CTS;                   /*!< (@ 0x00000100) CTS is activated (set low). Clear To Send.                 */
  volatile uint32_t  EVENTS_NCTS;                  /*!< (@ 0x00000104) CTS is deactivated (set high). Not Clear To Send.          */
  volatile uint32_t  EVENTS_RXDRDY;                /*!< (@ 0x00000108) Data received in RXD                                       */
  volatile const  uint32_t  RESERVED2[4];
  volatile uint32_t  EVENTS_TXDRDY;                /*!< (@ 0x0000011C) Data sent from TXD                                         */
  volatile const  uint32_t  RESERVED3;
  volatile uint32_t  EVENTS_ERROR;                 /*!< (@ 0x00000124) Error detected                                             */
  volatile const  uint32_t  RESERVED4[7];
  volatile uint32_t  EVENTS_RXTO;                  /*!< (@ 0x00000144) Receiver timeout                                           */
  volatile const  uint32_t  RESERVED5[46];
  volatile uint32_t  SHORTS;                       /*!< (@ 0x00000200) Shortcut register                                          */
  volatile const  uint32_t  RESERVED6[64];
  volatile uint32_t  INTENSET;                     /*!< (@ 0x00000304) Enable interrupt                                           */
  volatile uint32_t  INTENCLR;                     /*!< (@ 0x00000308) Disable interrupt                                          */
  volatile const  uint32_t  RESERVED7[93];
  volatile uint32_t  ERRORSRC;                     /*!< (@ 0x00000480) Error source                                               */
  volatile const  uint32_t  RESERVED8[31];
  volatile uint32_t  ENABLE;                       /*!< (@ 0x00000500) Enable UART                                                */
  volatile const  uint32_t  RESERVED9;
  volatile uint32_t  PSELRTS;                      /*!< (@ 0x00000508) Pin select for RTS                                         */
  volatile uint32_t  PSELTXD;                      /*!< (@ 0x0000050C) Pin select for TXD                                         */
  volatile uint32_t  PSELCTS;                      /*!< (@ 0x00000510) Pin select for CTS                                         */
  volatile uint32_t  PSELRXD;                      /*!< (@ 0x00000514) Pin select for RXD                                         */
  volatile const  uint32_t  RXD;                          /*!< (@ 0x00000518) RXD register                                               */
  volatile  uint32_t  TXD;                          /*!< (@ 0x0000051C) TXD register                                               */
  volatile const  uint32_t  RESERVED10;
  volatile uint32_t  BAUDRATE;                     /*!< (@ 0x00000524) Baud rate                                                  */
  volatile const  uint32_t  RESERVED11[17];
  volatile uint32_t  CONFIG;                       /*!< (@ 0x0000056C) Configuration of parity and hardware flow control          */
} NRF_UART_Type;                                /*!< Size = 1392 (0x570)                                                       */

#define NRF_UART0 ((NRF_UART_Type*)NRF_UART0_BASE)
//-------------------------PROTOTYPES OF LOCAL FUNCTIONS--------------------



//-------------------------EXPORTED VARIABLES ------------------------------



//-------------------------GLOBAL VARIABLES---------------------------------



//-------------------------EXPORTED FUNCTIONS-------------------------------
void nrf52_target_putc(char a)
{
    NRF_UART0->TXD = (uint8_t)a;
    while(0==NRF_UART0->EVENTS_TXDRDY);
    NRF_UART0->EVENTS_TXDRDY = 0;
}

void nrf52_target_init_putc(void)
{
    NRF_UART0->CONFIG = (TARGET_HWFC | TARGET_PARITY | TARGET_STOP_BITS); //NO HWFC, NO Parity, 1 stop bit
    NRF_UART0->BAUDRATE = TARGET_BAUDRATE;
    NRF_UART0->PSELTXD = (TARGET_TX_PORT | TARGET_TX_PIN);
    NRF_UART0->PSELRXD = 0;
    NRF_UART0->PSELRTS = 0;
    NRF_UART0->PSELCTS = 0;
    NRF_UART0->ENABLE = 4;
    NRF_UART0->TASKS_STARTTX = 1;

}

void nrf52_target_flush_putc(void)
{
    NRF_UART0->TASKS_STOPTX = 1;
    NRF_UART0->TASKS_STARTTX = 1;

}

void nrf52_target_close_putc(void)
{
    NRF_UART0->TASKS_STOPTX = 1;
}


//-------------------------LOCAL FUNCTIONS----------------------------------

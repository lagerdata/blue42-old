#ifndef _NRF52_TARGET_UART_INCLUDED
#define _NRF52_TARGET_UART_INCLUDED
//-------------------------MODULES USED-------------------------------------



//-------------------------DEFINITIONS AND MACORS---------------------------
//NOTE: nrf52 target uses NRF_UART0 for UART communications
#define BAUD1200 0x0004F000
#define BAUD2400 0x0009D000
#define BAUD4800 0x0013B000
#define BAUD9600 0x00275000
#define BAUD14400 0x003B0000
#define BAUD19200 0x004EA000
#define BAUD28800 0x0075F000
#define BAUD31250 0x00800000
#define BAUD38400 0x009D5000
#define BAUD56000 0x00E50000
#define BAUD57600 0x00EBF000
#define BAUD76800 0x013A9000
#define BAUD115200 0x01D7E000
#define BAUD230400 0x03AFB000
#define BAUD25000 0x04000000

#define HWFC_OFF 0
#define HWFC_ON 1

#define PARITY_NONE 0
#define PARITY_ON (0x7<<1)

#define STOP_BITS_ONE 0
#define STOP_BITS_TWO (1<<4)

#define PORT_ZERO 0
#define PORT_ONE (1<<5)


#define TARGET_BAUDRATE BAUD115200
#define TARGET_HWFC HWFC_OFF
#define TARGET_PARITY PARITY_NONE
#define TARGET_STOP_BITS STOP_BITS_ONE
#define TARGET_TX_PIN 6
#define TARGET_TX_PORT PORT_ZERO



//-------------------------TYPEDEFS AND STRUCTURES--------------------------



//-------------------------EXPORTED VARIABLES ------------------------------
#ifndef _NRF52_TARGET_UART_C_SRC



#endif



//-------------------------EXPORTED FUNCTIONS-------------------------------
void nrf52_target_putc(char a);
void nrf52_target_init_putc(void);
void nrf52_target_flush_putc(void);
void nrf52_target_close_putc(void);


#endif

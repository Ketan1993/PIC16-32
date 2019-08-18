#include "../common_def.h"
#include "uart.h"

bool UART_SetParityStop(UART1PARITYbits parity, UART1STOPbits stopBit);
bool UART_CloseDriver(UART_Internal *handler);
bool UART_SetBaudate(long Baudrate);
bool UART_Enable(void);

typedef struct UART_Instance {
    UART_Internal uart;
} UART_Instance;

static UART_Instance UART_Instan[1] = {
    {
        {
            UART_SetParityStop,
            UART_CloseDriver,
            UART_SetBaudate,
            UART_Enable,
            false
        },
    }
};

bool UART_SetParityStop(UART1PARITYbits parity, UART1STOPbits stopBit) {
    U2MODEbits.STSEL = stopBit;
    U2MODEbits.PDSEL = parity;
    return true;
}

bool UART_CloseDriver(UART_Internal *handler) {
    return true;
}

bool UART_SetBaudate(long Baudrate) {
    U2BRG = BAUDARATE(Baudrate);
    return true;
}

bool UART_Enable(void) {
    
    U2STAbits.UTXEN = 1;
    return true;
}

void UART_Transmite(UART_Internal *uart, uint8_t data)
{
     U2TXREG = data;
     while(!U2STAbits.TRMT);
}
UART_Internal *UART_CoreDriverInit(uint8_t inst) {
    
    UART_Instance *uart = &UART_Instan[inst];

    if (uart->uart.Uart_Allocated) {
        return false;
    }
    uart->uart.Uart_Allocated = true;
    

    U2MODE = 0x0008;
    U2STA = 0x0000;
   
    //set uart baudrate
    uart->uart.UART_Baudate(UART_BAUDRATE); 
    //U2MODEbits.UARTEN = 1;

    //open the uart driver
    uart->uart.UART_SetParityStopBit(EIGHT_BIT_NOPARITY, ONE_STOPBIT);

    //enable uart tx mode
    uart->uart.UART_EnableForTxRx();

     return (UART_Internal*) uart;
}


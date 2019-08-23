#include "../common_def.h"
#include "uart.h"


bool UART_SetParityStop(UART1PARITYbits parity, UART1STOPbits stopBit);
bool UART_CloseDriver(UART_Internal *handler);
bool UART_SetBaudate(long Baudrate);
bool UART_Enable(void);
bool UART_TransmiteEnable(void);

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
            UART_TransmiteEnable,
            false,
            TX_RX_MAX_LEN
        },
    }
};

bool UART_TransmiteEnable(void) {
    U2STAbits.UTXEN = 1;
    return true;
}

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

    U2MODEbits.UARTEN = 1;
    return true;
}

void UART_Transmite(UART_Internal *uart, const uint8_t* data, uint8_t len, bool flag) {

    UART_Instance *pUart = (UART_Instance*) uart;

    if (!pUart) {
        return;
    }
    if (len > pUart->uart.RxTxlen) {
        return;
    }
    //start the transMission 
    pUart->uart.UART_TransmiteEn();

    while (len-- > 0) {

        U2TXREG = *data++; //shoud be in interrupt mode

        while (!U2STAbits.TRMT);
    }
    if (flag) {
        U2TXREG = '\r'; //send new line character
        while (!U2STAbits.TRMT);
    }
}

int report(UART_Internal *uart, const char *format, ...) {
    UART_Instance *pUart = (UART_Instance*) uart;

    uint8_t len = 0;
    char buf[254] = {'\0'};
    
    if (!pUart) {
        return -1;
    }
    va_list arg;
    
    va_start(arg, format);
    
    len = vsprintf(buf, format, arg);
    
    if(len > 254 || len < 0)
    {
        return -2;
    }
    
    UART_Transmite(uart, (uint8_t*)buf, len, true);
    
    return len;
}

UART_Internal *UART_CoreDriverInit(uint8_t inst) {

    UART_Instance *uart = &UART_Instan[inst];

    if (uart->uart.Uart_Allocated) {
        return false;
    }
    uart->uart.Uart_Allocated = true;

    U2MODE = 0x0000; //power of reset
    U2STA = 0x0000; //power of reset

#if defined BRG_LSPEED
    U2MODEbits.BRGH = 0;
#else
    U2MODEbits.BRGH = 1;
#endif
    //set uart baudrate
    uart->uart.UART_Baudate(UART_BAUDRATE);

    //open the uart driver
    uart->uart.UART_SetParityStopBit(EIGHT_BIT_NOPARITY, ONE_STOPBIT);

    //enable uart tx mode
    uart->uart.UART_EnableForTxRx();

    return (UART_Internal*) uart;
}


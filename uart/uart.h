/* 
 * File:   uart.h
 * Author: ketan
 *
 * Created on 6 August, 2019, 10:28 PM
 */

#ifndef UART_H
#define	UART_H

//standard header file 
#include "../common_def.h"

#ifdef	__cplusplus
extern "C" {
#endif

    //UART MODE FCY
#define PERIPHERAL_FREQUENCY        (FCY/2)
#define UART_BAUDRATE               ((long)9600)

#define TX_RX_MAX_LEN               254        //254 character 
//#define BRG_LSPEED
    //if BAUDRATE SPEED is high 
#ifdef BRG_LSPEED
#define DIVIDER_FACTOR               16
#define BAUDARATE(brg)               ((((PERIPHERAL_FREQUENCY)/(brg))/DIVIDER_FACTOR) - 1)          //(((PERIPHERAL_FREQUENCY) / ((DIVIDER_FACTOR) * (brg))) - 1)
#else
#define DIVIDER_FACTOR               4
#define BAUDARATE(brg)               ((((PERIPHERAL_FREQUENCY)/(brg))/DIVIDER_FACTOR) - 1)  //(((PERIPHERAL_FREQUENCY) / ((DIVIDER_FACTOR) * (brg))) - 1)
#endif    

    //UART parity bit configure
    //bit has been selected as per the data sheet of the controller

    typedef enum _UART_Parity {
        EIGHT_BIT_NOPARITY = 0x00,
        EIGHT_BIT_EVENPARITY = 0X01,
        EIGHT_BIT_OLDPARITY = 0X02,
        NINE_BIT_NOPARITY = 0X03
    } UART1PARITYbits;

    //UART stop big congigration

    typedef enum _UART_Stop {
        ONE_STOPBIT = 0X00,
        TWO_STOPBIT = 0X01
    } UART1STOPbits;

    typedef struct UART_Internal UART_Internal;

    struct UART_Internal {
        bool (*UART_SetParityStopBit)(UART1PARITYbits parity, UART1STOPbits stopBit);
        bool (*UART_Close)(UART_Internal *handler);
        bool (*UART_Baudate)(long Baudrate);
        bool (*UART_EnableForTxRx)(void);
        bool (*UART_TransmiteEn)(void);
        bool Uart_Allocated;
        uint8_t RxTxlen; 
    };

    typedef UART_Internal *(UART_Initilaztion) (uint8_t inst);
    void UART_Transmite(UART_Internal *uart, const uint8_t* data, uint8_t len, bool flag);
    UART_Initilaztion UART_CoreDriverInit;

#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */


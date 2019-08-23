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

    //maximum len len has define here
#define TX_RX_MAX_LEN               254        //254 character 
    /*
     this is used for the define speed of the UART
     */
    //#define BRG_LSPEED
#ifdef BRG_LSPEED
#define DIVIDER_FACTOR               16
#define BAUDARATE(brg)               ((((PERIPHERAL_FREQUENCY)/(brg))/DIVIDER_FACTOR) - 1)          //(((PERIPHERAL_FREQUENCY) / ((DIVIDER_FACTOR) * (brg))) - 1)
#else
#define DIVIDER_FACTOR               4
#define BAUDARATE(brg)               ((((PERIPHERAL_FREQUENCY)/(brg))/DIVIDER_FACTOR) - 1)  //(((PERIPHERAL_FREQUENCY) / ((DIVIDER_FACTOR) * (brg))) - 1)
#endif    

    /*UART parity bit configure
     *bit has been selected as per the data sheet of the controller
     * please refer the data-sheet (PIC24FJ128GA310) for the more information 
     */
    typedef enum _UART_Parity {
        EIGHT_BIT_NOPARITY = 0x00, //8 bit , no parity
        EIGHT_BIT_EVENPARITY = 0X01, //8 bit, even parity
        EIGHT_BIT_OLDPARITY = 0X02, //8 bit, old parity
        NINE_BIT_NOPARITY = 0X03 //9 bit, no parity
    } UART1PARITYbits;

    //UART stop bit congigration

    typedef enum _UART_Stop {
        ONE_STOPBIT = 0X00, /* one stop bit */
        TWO_STOPBIT = 0X01 /* two stop bit */
    } UART1STOPbits;

    //forward declaration of the uart main structure 
    typedef struct UART_Internal UART_Internal;

    /*this is main structure  of the uart communication
     *we used pointer function for the respective process, this is map with the uart.c file in 'uart/uart'
     * this structure used in board.c file  
     */
    struct UART_Internal {
        bool (*UART_SetParityStopBit)(UART1PARITYbits parity, UART1STOPbits stopBit);
        bool (*UART_Close)(UART_Internal *handler);
        bool (*UART_Baudate)(long Baudrate);
        bool (*UART_EnableForTxRx)(void);
        bool (*UART_TransmiteEn)(void);
        bool Uart_Allocated;
        uint8_t RxTxlen;
    };

    
    /*  UART INITIALIZATION FUNCTION
     *  this function used for the initialization core function of the to uart protocol
     *  internally it will check the all the valid parameter 
     *  to use other uart function this function has to initialized first
     * @parameter
     *  inst : valid uart instance
     * @return
     * it will return the uart core initialized structure
     */
    
    typedef UART_Internal *(UART_Initilaztion) (uint8_t inst);

    /*  UART TRANSMITE FUNCTION
     *  this function used for the transmit the data to uart protocol
     *  internally it will check the all the valid parameter 
     *  to use this function first uart initialization should be happen first
     * @parameter
     *  uart : this is handler of the uart 
     *  data : this is data to transmit over uart
     *  len  : len of the data
     *  flag : is true it will print the line-feed otherwise not
     */

    void UART_Transmite(UART_Internal *uart, const uint8_t* data, uint8_t len, bool flag);
    
    
    /*  UART PRINTF FUNCTION
     *  this function used for the transmit the formated data to uart protocol
     *  internally it will check the all the valid parameter 
     *  to use this function first uart initialization should be happen first
     * @parameter
     *  uart : this is handler of the uart 
     *  format : this is general printf format
     * @return
     * it will return total formatted bytes;
     */
    int report(UART_Internal *uart, const char *format, ...);
    
    //rename of the core driver function
    UART_Initilaztion UART_CoreDriverInit;

#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */


/* 
 * File:   serial_log.h
 * Author: ketan
 *
 * Created on 23 August, 2019, 11:09 PM
 */

#ifndef SERIAL_LOG_H
#define	SERIAL_LOG_H

#ifdef	__cplusplus
extern "C" {
#endif

#define LOG_NON    -1          /*to use non log */
#define LOG_INFO    1          /*to use general information */
#define LOG_ERR     2          /*to use error message print */

#define LOGLEVEL    LOG_INFO

#if LOGLEVEL > LOG_NON
#include "../uart/uart.h"
#define UART_SERIAL_LOG        report
#define UART_PRINT(...)        UART_SERIAL_LOG(__VA_ARGS__)
#else 
#warning "if you wanna track the code !!? -> please define LOGLEVEL in 'uitily/serial_log.h'"
#endif    
    
#ifdef	__cplusplus
}
#endif

#endif	/* SERIAL_LOG_H */


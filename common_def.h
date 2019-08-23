/* 
 * File:   common_def.h
 * Author: ketan
 *
 * Created on 6 August, 2019, 10:28 PM
 */

#ifndef COMMON_DEF_H
#define	COMMON_DEF_H

/*
 * standard header file
 */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <p24FJ128GA310.h>
#ifdef	__cplusplus
extern "C" {
#endif


    /* CPU is running on 32Mhz frequency 
     * pheriperal frequency will be /2 of main function frequency
     * pheriperal frequency used to configure the I2C, SPI, UART protocal 
     */
#define FCY 32000000UL

    //error code 
#define SUCCESS           0        /*to use return success on the successfully driver call*/
#define FAIL             -1        /*to use failure condition of the driver */

#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_DEF_H */


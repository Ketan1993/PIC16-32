/* 
 * File:   main.c
 * Author: ketan
 *
 * Created on 10 July, 2019, 3:20 PM
 */
#include "main.h"
/*
 * 
 */
int main(void) {

    SYSTEMS_Initialization();  //systems init for controller like clock init, pin init
    Main_Application();        // main application will run here
    return 0;
}


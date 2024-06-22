/**
 * main.c
 *
 *  Created on  :   Sun 09 JUN 2024
 *  Authors     :   Kareem Salah, Mohamed Samy, Nada Amr, Nouran Mahmoud
 */
#include <avr/io.h>
#include <util/delay.h>

#include "LEDM.h"
#include "WDGDrv.h"
#include "WDGM.h"
#include "GPIO.h"
char stuck_flag=0;
char called=1;
int main()
{
    LEDM_Init();
    WDGDrv_Init();
    WDGM_Init();
    while (1){
      LEDM_Manage();
      _delay_ms(10);
      if (called== 1){
    	  called= 0;
    	  continue;
      }
      else{
    	  called=1;
    	  stuck_flag=1;
    	  WDGM_MainFunction();
        }
    }
    return 0;
 }

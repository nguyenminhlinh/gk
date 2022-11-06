/*
 * processing.c
 *
 *  Created on: Nov 5, 2022
 *      Author: minhl
 */


#include"processing.h"

void fsm_simple_buttons_run (){
// TODO

	switch(status)
	{
	case INIT:
		 if(timer4_flag){display7SEG(count);setTimer4(100);}
		 if(isButton1Pressed()==1){status=RE;setTimer1(10000);}
		 if(isButton2Pressed()==1){status=INC;setTimer1(10000);}
		 if(isButton3Pressed()==1){status=DEC;setTimer1(10000);}
		 if((isbutton_flag_3s_delay()==1)&&(isbutton2_pressed_3s()==1)){status=INC_3s;timer2_flag=1;}
		 if((isbutton_flag_3s_delay()==1)&&(isbutton3_pressed_3s()==1)){status=DEC_3s;timer2_flag=1;}
		if(timer1_flag==1){status=AUTO;}
		break;
	case AUTO:
		if(timer3_flag)
		 {
			display7SEG(count);
			--count;
			if(count<0){count=0;}
		    setTimer3(1000);
		 }
		if(isButton1Pressed()==1){status=RE;setTimer1(10000);}
		 if(isButton2Pressed()==1){status=INC;setTimer1(10000);}
		 if(isButton3Pressed()==1){status=DEC;setTimer1(10000);}
		 if((isbutton_flag_3s_delay()==1)&&(isbutton2_pressed_3s()==1)){status=INC_3s;timer2_flag=1;}
		 if((isbutton_flag_3s_delay()==1)&&(isbutton3_pressed_3s()==1)){status=DEC_3s;timer2_flag=1;}
		break;
	case RE:
		count=0;
		display7SEG(count);
		timer4_flag=1;
		status = INIT;
		break;
	case INC:

		count++;
		if(count>9){count =0;}
		display7SEG(count);
		timer4_flag=1;
		status = INIT;
		break;
	case DEC:

		count--;
		if(count<0){count =9;}
		display7SEG(count);
		timer4_flag=1;
		status = INIT;
		break;
	case INC_3s:
		if(timer2_flag)
		 {
			  count++;
			  HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
			  if(count>9){count =0;}
			  display7SEG(count);
			  setTimer2(1000);
		 }
		if(isbutton_flag_3s_delay()==0){status=INIT;setTimer1(10000);}
		break;
	case DEC_3s:
		//todo
		if(timer2_flag)
		 {
			  count--;
			  if(count<0){count=9;}
			  display7SEG(count);
			  setTimer2(1000);
		 }
		if(isbutton_flag_3s_delay()==0){status=INIT;setTimer1(10000);}
		break;
	default:
		//display7SEG(count);
		break;
	}
}

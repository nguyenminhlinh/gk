/*
 * button.c
 *
 *  Created on: Nov 5, 2022
 *      Author: minhl
 */
#include"button.h"
int KeyReg0[3]= {NORMAL_STATE,NORMAL_STATE,NORMAL_STATE};
int KeyReg1[3] = {NORMAL_STATE,NORMAL_STATE,NORMAL_STATE};
int KeyReg2[3] = {NORMAL_STATE,NORMAL_STATE,NORMAL_STATE};
int KeyReg3[3] = {NORMAL_STATE,NORMAL_STATE,NORMAL_STATE};
int TimeOutForKeyPress[3] =  {300};
int button1_flag = 0;//reset
int button2_flag = 0;//inc
int button3_flag = 0;//dec
int button1_flag_3s = 0;
int button2_flag_3s = 0;
int button3_flag_3s = 0;
int button_flag_3s_delay=0;

int isButton1Pressed(){
	if(button1_flag == 1){
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		button1_flag = 0;
		return 1;
	}
	return 0;
}
int isButton2Pressed(){
	if(button2_flag == 1){
		button2_flag = 0;
		return 1;
	}
	return 0;
}
int isButton3Pressed(){
	if(button3_flag == 1){
		button3_flag = 0;
		return 1;
	}
	return 0;
}
int isbutton1_pressed_3s()
{
	if(button1_flag_3s == 1){
		button1_flag_3s = 0;
		return 1;
	}
		return 0;
	}
int isbutton2_pressed_3s()
{
	if(button2_flag_3s == 1){
		button2_flag_3s = 0;
		return 1;
	}
		return 0;
}
int isbutton3_pressed_3s()
{
	if(button3_flag_3s == 1){
		button3_flag_3s = 0;
		return 1;
	}
		return 0;
}
int isbutton_flag_3s_delay()
{
	if(button_flag_3s_delay == 1){
		button_flag_3s_delay = 0;
		return 1;
	}
		return 0;
}
void subKeyProcess(int i){
	//TODO
	if(i==0){
	button1_flag = 1;
	}
	else if(i==1){
		button2_flag = 1;
	}
	else if(i == 2){
		button3_flag = 1;
	}
}
void subKeyProcess3s(int i){
	//TODO
	if(i==0){
	button1_flag_3s = 1;
	}
	else if(i==1){
		button2_flag_3s = 1;
	}
	else if(i == 2){
		button3_flag_3s = 1;
	}
}
void subKeyProcess3sdelay(int i){
	//TODO
	if((i==1)||(i == 2)){
		button_flag_3s_delay = 1;
	}
}

void getKeyInput(){
  for(int i=0;i<3;i++){
	  KeyReg0[i] = KeyReg1[i];
	  KeyReg1[i] = KeyReg2[i];
	  if( i== 0){
	  KeyReg2[i] = HAL_GPIO_ReadPin(RE_GPIO_Port, RE_Pin);
	  }
	  else if(i==1){
		  KeyReg2[i] = HAL_GPIO_ReadPin(INC_GPIO_Port, INC_Pin);
	  }
	  else if(i==2){
		  KeyReg2[i] = HAL_GPIO_ReadPin(DEC_GPIO_Port, DEC_Pin);
	  }
	  if ((KeyReg1[i] == KeyReg0[i]) && (KeyReg1[i] == KeyReg2[i])){
		  if (KeyReg2[i] != KeyReg3[i]){
			  KeyReg3[i] = KeyReg2[i];
			  if (KeyReg2[i] == PRESSED_STATE){
				TimeOutForKeyPress[i] = 300;
				subKeyProcess(i);
			  }
		 }else{
			 if(KeyReg2[i]==PRESSED_STATE){button_flag_3s_delay=1;}
		   TimeOutForKeyPress[i] --;
		   if(TimeOutForKeyPress[i]==0)
			{
				//todo
				if(KeyReg2[i]==PRESSED_STATE)
				{
					//subKeyProcess(i);
					subKeyProcess3s(i);
				}
				TimeOutForKeyPress[i]=300;
			}
		}
	  }else{button_flag_3s_delay=0;}
	}
}


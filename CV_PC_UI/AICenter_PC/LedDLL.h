#pragma once
#include "stdafx.h"



#define IDC_MYICON                      2
#define IDD_LEDDLL_DIALOG               102
#define IDS_APP_TITLE                   103
#define IDD_ABOUTBOX                    103
#define IDM_ABOUT                       104
#define IDM_EXIT                        105
#define IDI_LEDDLL                      107
#define IDI_SMALL                       108
#define IDC_LEDDLL                      109
#define IDR_MAINFRAME                   128
#define IDD_DIALOG1                     129
#define IDC_BUTTON1                     1000
#define IDC_STATIC                      -1
#define IDC_ALLKEY                      1099
#define IDC_ONEKEY                      1100
#define IDC_LEDMODE                     1101
#define IDC_LEDONE                      1102
#define IDC_LEDALLKILL                  1103
#define IDC_DEVICELINK                  1104

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NO_MFC                     1
#define _APS_NEXT_RESOURCE_VALUE        130
#define _APS_NEXT_COMMAND_VALUE         32771
#define _APS_NEXT_CONTROL_VALUE         1001
#define _APS_NEXT_SYMED_VALUE           110
#endif
#endif


extern "C" _declspec(dllimport) int Set_hw_light_mode(uint8_t  mode);
extern "C" _declspec(dllimport) int Set_whole_light_to_device(uint8_t rvalue, uint8_t gvalue, uint8_t bvalue);
extern "C" _declspec(dllimport) int Set_single_light_to_device(uint8_t key, uint8_t rvalue, uint8_t gvalue, uint8_t bvalue);
extern "C" _declspec(dllimport) int Load_single_light_to_array(uint8_t key, uint8_t rvalue, uint8_t gvalue, uint8_t bvalue);
extern "C" _declspec(dllimport) int Send_light_array_to_device();
extern "C" _declspec(dllimport) bool Get_Device_Link();

#define		LED_ESC_INDEX		0		
#define		LED_OVERDOT_INDEX	1*21+0	
#define		LED_TAB_INDEX		2*21+0
#define		LED_CAP_INDEX		3*21+0	
#define		LED_SHIFT_L_INDEX	4*21+0
#define		LED_CTRL_L_INDEX	5*21+0	
//===================================================c1	
#define		LED_F1_INDEX		1			
#define		LED_1_INDEX			1*21+1	
#define		LED_Q_INDEX			2*21+1
#define		LED_A_INDEX			3*21+1	
#define		LED_K45_INDEX		4*21+1
#define		LED_WIN_L_INDEX		5*21+1	
//===================================================c2
#define		LED_F2_INDEX		2		
#define		LED_2_INDEX			1*21+2	
#define		LED_W_INDEX			2*21+2
#define		LED_S_INDEX			3*21+2	
#define		LED_Z_INDEX			4*21+2
#define		LED_ALT_L_INDEX		5*21+2	
//===================================================c3
#define		LED_F3_INDEX		3		
#define		LED_3_INDEX			1*21+3	
#define		LED_E_INDEX			2*21+3
#define		LED_D_INDEX			3*21+3	
#define		LED_X_INDEX			4*21+3
#define		LED_SPACE_INDEX		5*21+3
//===================================================c4
#define		LED_F4_INDEX		4		
#define		LED_4_INDEX			1*21+4	
#define		LED_R_INDEX			2*21+4
#define		LED_F_INDEX			3*21+4	
#define		LED_C_INDEX			4*21+4
#define		LED_ALT_R_INDEX		5*21+4	
//===================================================c5
#define		LED_F5_INDEX		5		
#define		LED_5_INDEX			1*21+5	
#define		LED_T_INDEX			2*21+5
#define		LED_G_INDEX			3*21+5	
#define		LED_V_INDEX			4*21+5
#define		LED_FN_INDEX		5*21+5	
//===================================================c6
#define		LED_F6_INDEX		6		
#define		LED_6_INDEX			1*21+6	
#define		LED_Y_INDEX			2*21+6
#define		LED_H_INDEX			3*21+6	
#define		LED_B_INDEX			4*21+6
#define		LED_APP_INDEX		5*21+6	
//===================================================c7
#define		LED_F7_INDEX		7		
#define		LED_7_INDEX			1*21+7	
#define		LED_U_INDEX			2*21+7
#define		LED_J_INDEX			3*21+7	
#define		LED_N_INDEX			4*21+7
#define		LED_WIN_R_INDEX		5*21+7	
//===================================================c8
#define		LED_F8_INDEX		8		
#define		LED_8_INDEX			1*21+8	
#define		LED_I_INDEX			2*21+8
#define		LED_K_INDEX			3*21+8	
#define		LED_M_INDEX			4*21+8
#define		LED_CTRL_R_INDEX	5*21+8	
//===================================================c9
#define		LED_F9_INDEX		9	
#define		LED_9_INDEX			1*21+9	
#define		LED_O_INDEX			2*21+9
#define		LED_L_INDEX			3*21+9	
#define		LED_COMMA_INDEX		4*21+9
//#define						5*21+9
//===================================================c10
#define		LED_F10_INDEX		10	
#define		LED_0_INDEX			1*21+10	
#define		LED_P_INDEX			2*21+10
#define		LED_SEMICOLON_INDEX	3*21+10		
#define		LED_PERIOD_INDEX	4*21+10	
//#define						5*21+10
//===================================================c11
#define		LED_F11_INDEX		11	
#define		LED_DEC_INDEX		1*21+11	
#define		LED_BRACKET_L_INDEX	2*21+11
#define		LED_QUOTES_INDEX	3*21+11			
#define		LED_QUESTION_INDEX	4*21+11
//#define						5*21+11
//===================================================c12
#define		LED_F12_INDEX		12		
#define		LED_ADD_INDEX		1*21+12	
#define		LED_BRACKET_R_INDEX	2*21+12
//#define	LED_K29_INDEX		3*21+12
//#define						4*21+12
//#define						5*21+12
//===================================================c13	
//#define						0*21+13
#define		LED_BACKSPACE_INDEX	1*21+13
#define		LED_K29_INDEX		2*21+13	
#define	 	LED_ENTER_INDEX		3*21+13
#define		LED_SHIFT_R_INDEX	4*21+13
//#define						5*21+13
//===================================================c14
#define		LED_PRINT_INDEX	   	14
#define		LED_INSERT_INDEX	1*21+14
#define		LED_DELETE_INDEX	2*21+14
//#define						3*21+14
//#define						4*21+14
#define		LED_LEFT_INDEX	   	5*21+14
//===================================================c15
#define		LED_SCROLL_INDEX   	15
#define		LED_HOME_INDEX		1*21+15
#define		LED_END_INDEX		2*21+15
//#define						3*21+15
#define		LED_UP_INDEX		4*21+15
#define		LED_DOWN_INDEX		5*21+15


//===================================================c16
#define		LED_PAUSE_INDEX	  	16
#define		LED_PGUP_INDEX		1*21+16
#define		LED_PGDN_INDEX		2*21+16
//#define						3*21+16
//#define						4*21+16
#define		LED_RIGHT_INDEX		5*21+16
//===================================================c17
//#define						0*21+17
#define		LED_NUM_LOCK_INDEX	1*21+17	
#define		LED_NUM_7_INDEX		2*21+17
#define		LED_NUM_4_INDEX		3*21+17
#define		LED_NUM_1_INDEX		4*21+17
//								5*21+17
//===================================================c18
//#define						0*21+18
#define		LED_NUM_SPRIT_INDEX	1*21+18	
#define		LED_NUM_8_INDEX		2*21+18
#define		LED_NUM_5_INDEX		3*21+18
#define		LED_NUM_2_INDEX		4*21+18	  
#define		LED_NUM_0_INDEX		5*21+18
//===================================================c19
//#define						0*21+19
#define		LED_NUM_STAR_INDEX	1*21+19	
#define		LED_NUM_9_INDEX		2*21+19
#define		LED_NUM_6_INDEX		3*21+19
#define		LED_NUM_3_INDEX		4*21+19
#define		LED_NUM_DEL_INDEX	5*21+19	
//===================================================c20
//#define						0*21+20
#define		LED_NUM_DEC_INDEX	1*21+20
#define		LED_NUM_ADD_INDEX	2*21+20

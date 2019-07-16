#pragma once

#include <list>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

#include "tinyxml2.h" 
#ifndef __MSXML_LIBRARY_DEFINED__
#define __MSXML_LIBRARY_DEFINED__
#endif
#include <Windows.h>
using namespace tinyxml2;

typedef enum
{
	/* no error */
	AI_CONFIGURE_SUCCESS = 1,    /**< no error: The key matching is correct and the setup is successful*/

	AI_ERR_NONE = 0,    /**< NOT FAIL */

	/* reserved for unexpected errors */
	AI_ERR_UNKNOWN = -1,   /**< unknown error. */

	/* error codes <0 */
	AI_ERR_LACK_XML = -2,   /**< Lack of XML files */
	AI_ERR_KEY = -3,   /**< Key error */
	AI_ERR_MODE_ERRIND = -4,   /**< Model input errors */
	AI_ERR_MODE_CFGSet = -5,   /**< Model Not Set */
	AI_ERR_EQUITMENT_ERRIND = -6,   /**< Equipment input errors */
} AI_RESULT;


#define AI_GAME_LEN	 2 
typedef enum
{
	PBUG = 0,
	MOVEMENTS,
	CSGO
}GAME_TYPE;

#define AI_CLASS_LEN  3
typedef enum
{
	CLASSIFICATION = 0, 
	CV,
	HTTPSERVER
}AI_MODE_TYPE;

#define AI_MOD_LEN  9
typedef enum
{
	PBUG_KILL = 0,
	PBUG_DEAD,

	HEAD_RIGHT,
	HEAD_LEFT,
	People_APPEAR,
	People_LEAVE,

	CSGO_KILL,
	CSGO_DEAD,
	CSGO_KNIFE
}AI_MOD;

#define AI_EQUIPMENT_LEN  2
typedef enum
{
	CPU = 0,
	GPU
}AI_Equipment;



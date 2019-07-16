#pragma once

#include "AI_UTIL.h"


//#include "face_lib.h"
//#pragma comment(lib, "face_lib.lib")

/** New Struct */
typedef struct  _MOD_MES {
	string Name;
	AI_MOD modInd;
	string Describe;
	bool ModChoose = false;
	AI_Equipment Equitment = AI_Equipment::CPU;
}AI_MOD_MES;

typedef vector<AI_MOD_MES> AI_MODMES_LIST;    
typedef struct  _GAME {
	string Name;
	AI_MODE_TYPE ModType;
	GAME_TYPE GameType;
	int ModMinInd;
	int ModMaxInd;
	AI_MODMES_LIST ModMesList;
	bool GameChoose = false;
}AI_GAME; 


/** CLASSIFICATION Struct */
typedef struct  _MOD_MES_CLASS : _MOD_MES {
	string XML;
	string BIN;
	int Rect[4];
	_MOD_MES_CLASS(XMLElement *Mod, int *ModeInd) {
		Name = Mod->Attribute("Name");
		modInd = AI_MOD(*ModeInd);
		Describe = Mod->FirstChildElement("Describe")->GetText();
		XML = Mod->FirstChildElement("Path_XML")->GetText();
		BIN = Mod->FirstChildElement("Path_BIN")->GetText();
		XMLElement* elmtRect = Mod->FirstChildElement("Rect");
		Rect[0] = atoi(elmtRect->FirstChildElement("X")->GetText());
		Rect[1] = atoi(elmtRect->FirstChildElement("Y")->GetText());
		Rect[2] = atoi(elmtRect->FirstChildElement("W")->GetText());
		Rect[3] = atoi(elmtRect->FirstChildElement("H")->GetText());
		(*ModeInd)++;
	}
}AI_MOD_MES_CLASS;

typedef struct  _GAME_CLASS : AI_GAME {
	_GAME_CLASS(XMLElement *Game, int *GameInd, int *ModeInd)
	{
		Name = Game->Attribute("Name");
		ModType  = AI_MODE_TYPE(atoi(Game->Attribute("Type")));

		//Configure
	//	XMLElement* elmtCFG = Game->FirstChildElement("Configure");
		GameType = GAME_TYPE(*GameInd);
		(*GameInd)++;
		ModMinInd = *ModeInd;
		//MOD
		XMLElement* elmtMod = Game->FirstChildElement("Mod");
		while (elmtMod != NULL) {
			ModMesList.push_back(AI_MOD_MES_CLASS(elmtMod, ModeInd));
			elmtMod = elmtMod->NextSiblingElement();//下一个兄弟节点
		}
		ModMaxInd = (*ModeInd)-1;
	}
}AI_GAME_CLASS;

/** CV Struct */
typedef struct  _MOD_MES_CV : _MOD_MES {
	_MOD_MES_CV(XMLElement *Mod, int *ModeInd) {
		Name = Mod->Attribute("Name");
		modInd = AI_MOD(*ModeInd);
		Describe = Mod->FirstChildElement("Describe")->GetText();
		(*ModeInd)++;
	}
}AI_MOD_MES_CV;

typedef struct  _GAME_CV : AI_GAME {
	_GAME_CV(XMLElement *Game, int *GameInd, int *ModeInd)
	{
		Name = Game->Attribute("Name");
		ModType = AI_MODE_TYPE(atoi(Game->Attribute("Type")));

		//Configure
	//	XMLElement* elmtCFG = Game->FirstChildElement("Configure");
		GameType = GAME_TYPE(*GameInd);
		(*GameInd)++;
		ModMinInd = *ModeInd;
		//MOD
		XMLElement* elmtMod = Game->FirstChildElement("Mod");
		while (elmtMod != NULL) {
			ModMesList.push_back(AI_MOD_MES_CV(elmtMod, ModeInd));
			elmtMod = elmtMod->NextSiblingElement();//下一个兄弟节点
		}
		ModMaxInd = (*ModeInd) - 1;
	}
}AI_GAME_CV;


/** HTTPSERVER Struct */
typedef struct  _MOD_MES_Server : _MOD_MES {
	_MOD_MES_Server(XMLElement *Mod, int *ModeInd) {
		Name = Mod->Attribute("Name");
		modInd = AI_MOD(*ModeInd);
		Describe = Mod->FirstChildElement("Describe")->GetText();
		(*ModeInd)++;
	}
}AI_MOD_MES_Server;

typedef struct  _GAME_Server : AI_GAME {
	string IP;
	int port;
	string cfg;
	_GAME_Server(XMLElement *Game, int *GameInd, int *ModeInd)
	{
		Name = Game->Attribute("Name");
		ModType = AI_MODE_TYPE(atoi(Game->Attribute("Type")));

		//Configure
		XMLElement* elmtCFG = Game->FirstChildElement("Configure");
		GameType = GAME_TYPE(*GameInd);
		(*GameInd)++;
		
		ModMinInd = *ModeInd;
		IP = elmtCFG->FirstChildElement("IP")->GetText();
		port = atoi(elmtCFG->FirstChildElement("Port")->GetText());
		cfg = elmtCFG->FirstChildElement("Cfg")->GetText();

		//MOD
		XMLElement* elmtMod = Game->FirstChildElement("Mod");
		while (elmtMod != NULL) {
			ModMesList.push_back(AI_MOD_MES_Server(elmtMod, ModeInd));
			elmtMod = elmtMod->NextSiblingElement();//下一个兄弟节点
		}
		ModMaxInd = (*ModeInd) - 1;
	}
}AI_GAME_Server;

/* Run*/


/** Old Struct */
typedef vector<string>  StringList;
StringList splitstr(const string& str, char tag);

class AICENTER
{

public:
	static AICENTER& Instance() {
		static AICENTER m_pInstance;
		return m_pInstance;
	}

	AI_RESULT Initial(string userKey);
	string MODsListReport(GAME_TYPE game);
	string ALL_MODsListReport(void);
	string CFG_MODsListReport(void);
	void Clean_CfgMOD(void);
	AI_RESULT CfgMOD(AI_MOD modHandler[], AI_Equipment equipments[]);
	AI_RESULT CfgMOD(AI_MOD modHandler, AI_Equipment equipments);
	int RunMOD(AI_MOD modHandler);
	int StopMOD(AI_MOD modHandler);
	int Free(void);

protected:
	AI_RESULT ReadXMLFile(string FilePath, string userKey);
//	AI_RESULT checkDeviceChoose(AI_MOD modHandler, AI_ExtDevice_LIST deviceChoose);
//	AI_RESULT getMOD_MES(AI_MOD modHandler, AI_MOD_MES  **modMes);
protected:
	bool checkKey;
	vector<AI_GAME> GameList;
	vector<AI_GAME> RunGameList;
//	AI_DISPLAY_INFO display;

private:
	AICENTER(){}
	~AICENTER() {}
	AICENTER(AICENTER const&);
	AICENTER& operator=(AICENTER const&);
};








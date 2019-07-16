#include "AICenter_LIB.h"

AI_RESULT AICENTER::Initial(string userKey) {
	AI_RESULT ret;
	//Read XML Configure
	ret = ReadXMLFile("./include/CONFXML.xml", userKey);
	if (ret != AI_ERR_NONE) 
		return ret;

	return AI_CONFIGURE_SUCCESS;

	//m_server = new Server(this);
	//connect(m_server, SIGNAL(getData(QString)), this, SLOT(getData(QString)));
	//connect(m_server, SIGNAL(getCSGOResult(int)), this, SLOT(getCSGOResult(int)));
	////m_server->setMaxPendingConnections(1);
	//m_server->listen(QHostAddress::Any, 3000);

}

AI_RESULT AICENTER::ReadXMLFile(string FilePath, string userKey) {
	tinyxml2::XMLDocument docXml; 
	if (docXml.LoadFile(FilePath.c_str()) != 0)
	{
		std::cout << "load xml file failed" << std::endl;
		return AI_ERR_LACK_XML;
	}
	XMLElement* elmtRoot = docXml.RootElement();

	//Get Setting
	XMLElement *elmtSet = elmtRoot->FirstChildElement("Setting");
	XMLElement *keyNode = elmtSet->FirstChildElement("Key");

	// Check Key
	string a = keyNode->GetText();
	checkKey = (userKey == string(keyNode->GetText()));
	if (checkKey) {
		XMLElement *elmtGame = elmtRoot->FirstChildElement("GameList");
		XMLElement *GameNode = elmtGame->FirstChildElement("Game");
		int GameInd = 0;
		int ModeInd = 0;
		while (GameNode != NULL) {
			AI_MODE_TYPE Type = AI_MODE_TYPE(atoi(GameNode->Attribute("Type")));
			switch (Type) {
			case CLASSIFICATION:
				GameList.push_back(AI_GAME_CLASS(GameNode, &GameInd, &ModeInd));
				break;
			case CV:
				GameList.push_back(AI_GAME_CV(GameNode, &GameInd, &ModeInd));
				break;
			case HTTPSERVER:
				GameList.push_back(AI_GAME_Server(GameNode, &GameInd, &ModeInd));
				break;
			}
			GameNode = GameNode->NextSiblingElement();//下一个兄弟节点
		}

		RunGameList = GameList;
		return AI_CONFIGURE_SUCCESS;
	}
	else
		return AI_ERR_KEY;
}

string AICENTER::MODsListReport(GAME_TYPE game) {
	string DESCRIBE;
	if (!checkKey)
		return DESCRIBE;
	for (int i = 0; i < GameList.size(); i++) {
		if (GameList[i].GameType == game) {
			DESCRIBE.append("Game Name: "+GameList[i].Name + "\n");
			for (int j = 0; j < GameList[i].ModMesList.size(); j++) {	
				DESCRIBE.append("Mode"+ std::to_string(j) + ": "+ GameList[i].ModMesList[j].Name + " " + GameList[i].ModMesList[j].Describe + "\n");
			}
			break;
		}
	}
	return DESCRIBE;
}

string AICENTER::ALL_MODsListReport(void) {
	string DESCRIBE;
	if (!checkKey)
		return DESCRIBE;
	for (int i = 0; i < GameList.size(); i++) {
		DESCRIBE.append("Game Name: " + GameList[i].Name  + "\n");
		for (int j = 0; j < GameList[i].ModMesList.size(); j++) {
			DESCRIBE.append("Mode" + std::to_string(GameList[i].ModMesList[j].modInd) + ": " + GameList[i].ModMesList[j].Name + " " + GameList[i].ModMesList[j].Describe + "\n");
		}
	}
	return DESCRIBE;
}

string AICENTER::CFG_MODsListReport(void) {
	string DESCRIBE;
	for (int i = 0; i < RunGameList.size(); i++) {
		if (RunGameList[i].GameChoose) {
			DESCRIBE.append("Game Name: " + RunGameList[i].Name + "\n");
			for (int j = 0; j < RunGameList[i].ModMesList.size(); j++) {
				if (RunGameList[i].ModMesList[j].ModChoose) {
					DESCRIBE.append("Mode" + std::to_string(GameList[i].ModMesList[j].modInd) + ": " + GameList[i].ModMesList[j].Name + " " + GameList[i].ModMesList[j].Describe + "\n");
					if (GameList[i].ModMesList[j].Equitment == AI_Equipment::CPU)
						DESCRIBE.append("\tCPU\n");
					else
						DESCRIBE.append("\tGPU\n");
				}
			}
		}
	}
	//if (!checkKey)
	//	return DESCRIBE;
	//for (int i = 0; i < RunGameList.size(); i++) {
	//	DESCRIBE.append("Game Name: " + RunGameList[i].Name + "\n");
	//	for (int j = 0; j < RunGameList[i].ModMesList.size(); j++) {
	//		DESCRIBE.append("Mode" + std::to_string(RunGameList[i].ModMesList[j].modInd) + ": " + RunGameList[i].ModMesList[j].Name + " " + RunGameList[i].ModMesList[j].Describe + "\n");
	//	}
	//}
	return DESCRIBE;
}

StringList splitstr(const string& str, char tag)
{
	StringList  li;
	string subStr;
	for (size_t i = 0; i < str.length(); i++)
	{
		if (tag == str[i])
		{
			if (!subStr.empty())
			{
				li.push_back(subStr);
				subStr.clear();
			}
		}
		else
			subStr.push_back(str[i]);

	}
	if (!subStr.empty())
		li.push_back(subStr);
	return li;
}

AI_RESULT AICENTER::CfgMOD(AI_MOD modHandler, AI_Equipment equipments) {
	if (!checkKey)
		return AI_ERR_KEY;
	if (int(modHandler) < 0 || int(modHandler) >= AI_MOD_LEN)
		return AI_ERR_MODE_ERRIND;
	if (int(equipments) < 0 || int(equipments) >= AI_EQUIPMENT_LEN)
		return AI_ERR_EQUITMENT_ERRIND;
	for (int j = 0; j < RunGameList.size(); j++) {
		if (int(modHandler) >= RunGameList[j].ModMinInd  && int(modHandler) <= RunGameList[j].ModMaxInd ) {
			RunGameList[j].GameChoose = true;
			int modInd_Game = int(modHandler) - RunGameList[j].ModMinInd;
			RunGameList[j].ModMesList[modInd_Game].ModChoose = true;
			RunGameList[j].ModMesList[modInd_Game].Equitment = equipments;
			break;
		}
	}
	return AI_ERR_NONE;
}

AI_RESULT AICENTER::CfgMOD(AI_MOD modHandler[], AI_Equipment equipments[]) {
	if (!checkKey)
		return AI_ERR_KEY;

	AI_RESULT ret;
	//模式数组去重
	//int n1 = unique(modHandler, modHandler + sizeof(modHandler) / sizeof(AI_MOD)) - modHandler;
	//if (n1 == 0)
	//	return AI_ERR_MODE_ERRIND;

	if (sizeof(modHandler) / sizeof(AI_MOD) != sizeof(equipments) / sizeof(AI_Equipment))
		return AI_ERR_MODE_ERRIND;

	//
	for (int i = 0; i < sizeof(modHandler) / sizeof(AI_MOD); i++) {
		if (int(modHandler[i]) < 0 || int(modHandler[i]) >= AI_MOD_LEN)
			return AI_ERR_MODE_ERRIND;
		if (int(equipments[i]) < 0 || int(equipments[i]) >= AI_EQUIPMENT_LEN)
			return AI_ERR_EQUITMENT_ERRIND;
	}

	for (int i = 0; i < sizeof(modHandler) / sizeof(AI_MOD); i++) {
		for (int j = 0; j < RunGameList.size(); j++) {
			int ii = int(modHandler[i]);
			if (int(modHandler[i]) >= RunGameList[j].ModMinInd && int(modHandler[i]) <= RunGameList[j].ModMaxInd) {
				RunGameList[j].GameChoose = true;
				int modInd_Game = int(modHandler[i]) - RunGameList[j].ModMinInd;
				RunGameList[j].ModMesList[modInd_Game].ModChoose = true;
				RunGameList[j].ModMesList[modInd_Game].Equitment = equipments[i];
				break;
			}
		}
	}

	return AI_ERR_NONE;
}

void AICENTER::Clean_CfgMOD(void) {
	RunGameList = GameList;
}

int AICENTER::RunMOD(AI_MOD modHandler) {
	if (!checkKey)
		return AI_ERR_KEY;

	int game_Ind;
	for (int i = 0; i < RunGameList.size(); i++) {
		if (int(modHandler) > RunGameList[i].ModMaxInd || int(modHandler) < RunGameList[i].ModMinInd) {
			game_Ind = i;
			break;
		}	
	}

	if (!RunGameList[game_Ind].GameChoose)
		return AI_ERR_MODE_CFGSet;

	int modInd_Game = int(modHandler) - RunGameList[game_Ind].ModMinInd;
	if (!RunGameList[game_Ind].ModMesList[modInd_Game].ModChoose)
		return AI_ERR_MODE_CFGSet;


	
	

	return AI_ERR_NONE;
}

int AICENTER::StopMOD(AI_MOD modHandler) {
	if (!checkKey)
		return AI_ERR_KEY;
	return AI_ERR_NONE;
}

int AICENTER::Free(void){
	if (!checkKey)
		return AI_ERR_KEY;
	return AI_ERR_NONE;
}
# Result
在我们Openvino项目中，中间层起到连接底层（models）和应用层（客户）的作用，中间层驱动底层并暴露APIs供应用层使用。<br>
![Frame](https://github.com/sustcpengyubin/QtPrivate/blob/master/CSGO_Server/images/Frame.jpg)  
Layer Frame<br>
在多次讨论后，我们定下以下几个基本的API实现：<br>
•	Initial()<br>
•	MODsListReport()<br>
•	CfgMOD()<br>
•	RunMOD()<br>
•	StopMOD()<br>
•	Free()<br>
考虑到sdk的用户实用性，我对以上APIs进行补充：<br>
•	Initial(key) :   Check key, Read XML Data<br>
•	MODsListReport(game) : Provide information about the patterns of the game<br>
•	All_MODsListReport() : Provide information about all the patterns we support<br>
•	Run_MODsListReport() : Provide information about all the patterns Running<br>
•	CfgMOD(modHandler, equipments):  Setting for a single mode<br>
•	CfgMOD([modHandler], [equipments]):  Setting for multiple modes<br>
•	RunMOD(modHandler) : Run the selected mode<br>
•	StopMOD(modHandler) : Stop the selected mode<br>
•	Free():Release memory<br>


## Learning
参数设置规范<br>
考虑到框架对大量参数存储、修改和调用的需要，以及不同模型的参数配置。我采用XML文件（可扩展标记语言）作为一个小型数据库。设计架构如下：<br>
![code1](https://github.com/sustcpengyubin/QtPrivate/blob/master/CSGO_Server/images/code1.jpg)  
![Frame2](https://github.com/sustcpengyubin/QtPrivate/blob/master/CSGO_Server/images/Frame2.jpg)  
XML Frame<br>
### 游戏分类与数据存储
我发现目前同种游戏下不同模式的实现方式是相同的，存在3类实现方式，以游戏为单位：<br>
1.	Classification: 0 <br>
2.	Camera: 1<br>
3.	HttpServer : 2<br>
其中，监测用户头部活动（扭头）和用户离开等模型我归属为一个“游戏”下的多个模式，称为MOVEMENTS，属于Camera。标签记录格式如下：<br>
![code2](https://github.com/sustcpengyubin/QtPrivate/blob/master/CSGO_Server/images/code2.jpg)  
对于XML数据，我的设计是在初始化过程中进行读取，并用一个结构体保存它。关于在C++实现XML文件的读取，网上有很多相关开源库，在实用性和功能性的对比下，我选择tinyxml2工具，它使用更少的内存，更快，并使用更少的内存分配。<br>
我发现不同类型的游戏的配置，和其模式需要的配置都是不同的，那么要怎么实现在一个Vector内高效简洁地保存不同类型的数据呢？我想到了软件设计模式中的装饰者模型，通过结构体继承的方式，实现多样化游戏和模式。游戏结构体为AI_GAME，模式结构体为AI_MOD_MES。<br>
#### 父类
typedef struct  _MOD_MES {<br>
	string Name;<br>
	AI_MOD modInd;<br>
	string Describe;<br>
	bool ModChoose = false;<br>
	AI_Equipment Equitment = AI_Equipment::CPU;<br>
}AI_MOD_MES;<br>
<br>
typedef vector<AI_MOD_MES> AI_MODMES_LIST;<br>
typedef struct  _GAME {<br>
	string Name;<br>
	AI_MODE_TYPE ModType;<br>
	GAME_TYPE GameType;<br>
	int ModMinInd;<br>
	int ModMaxInd;<br>
	AI_MODMES_LIST ModMesList;<br>
	bool GameChoose = false;<br>
}AI_GAME;<br>
#### 子类
/** CLASSIFICATION Struct */<br>
typedef struct  _MOD_MES_CLASS : _MOD_MES {<br>
	string XML;<br>
	string BIN;<br>
	int Rect[4];<br>
	_MOD_MES_CLASS(XMLElement *Mod, int *ModeInd) {<br>
		Name = Mod->Attribute("Name");<br>
		modInd = AI_MOD(*ModeInd);<br>
		Describe = Mod->FirstChildElement("Describe")->GetText();<br>
		XML = Mod->FirstChildElement("Path_XML")->GetText();<br>
		BIN = Mod->FirstChildElement("Path_BIN")->GetText();<br>
		XMLElement* elmtRect = Mod->FirstChildElement("Rect");<br>
		Rect[0] = atoi(elmtRect->FirstChildElement("X")->GetText());<br>
		Rect[1] = atoi(elmtRect->FirstChildElement("Y")->GetText());<br>
		Rect[2] = atoi(elmtRect->FirstChildElement("W")->GetText());<br>
		Rect[3] = atoi(elmtRect->FirstChildElement("H")->GetText());<br>
		(*ModeInd)++;<br>
	}<br>
}AI_MOD_MES_CLASS;<br>
<br>
typedef struct  _GAME_CLASS : AI_GAME {<br>
	_GAME_CLASS(XMLElement *Game, int *GameInd, int *ModeInd)<br>
	{<br>
		Name = Game->Attribute("Name");<br>
		ModType  = AI_MODE_TYPE(atoi(Game->Attribute("Type")));<br>
		GameType = GAME_TYPE(*GameInd);<br>
		(*GameInd)++;<br>
		ModMinInd = *ModeInd;<br>
		//MOD<br>
		XMLElement* elmtMod = Game->FirstChildElement("Mod");<br>
		while (elmtMod != NULL) {<br>
			ModMesList.push_back(AI_MOD_MES_CLASS(elmtMod, ModeInd));<br>
			elmtMod = elmtMod->NextSiblingElement();<br>
		}<br>
		ModMaxInd = (*ModeInd)-1;<br>
	}<br>
}AI_GAME_CLASS;<br>
在XML框架和结构体的设计中，都满足于未来扩展加入更多的游戏。XML数据会保存在vertor<AI_GAME>变量中。<br>

### 错误报错
考虑到用户在使用中间层API时，可能因为操作的不规范而造成错误，为了对中间层可能出现的不同错误进行区分性提示，我定义了一个枚举类型AI_RESULT:<br>
typedef enum<br>
{<br>
	/* no error */<br>
	AI_CONFIGURE_SUCCESS = 1,    /**< no error: The key matching is correct and the setup is successful*/<br>
<br>
	AI_ERR_NONE = 0,    /**< NOT FAIL */<br>
<br>
	/* reserved for unexpected errors */<br>
	AI_ERR_UNKNOWN = -1,   /**< unknown error. */<br>
<br>
	/* error codes <0 */<br>
	AI_ERR_LACK_XML = -2,   /**< Lack of XML files */<br>
	AI_ERR_KEY = -3,   /**< Key error */<br>
	AI_ERR_MODE_ERRIND = -4,   /**< Model input errors */<br>
	AI_ERR_MODE_CFGSet = -5,   /**< Model Not Set */<br>
	AI_ERR_EQUITMENT_ERRIND = -6,   /**< Equipment input errors */<br>
	… … <br>
} AI_RESULT;<br>
将根据后续开发过程中可能出现的错误继续扩充。<br>
## Suggestions 
对于中间层的实现，我的想法是立足用户的角度考虑APIs的实现，提供更多的功能选择，而且让客户操作起来方便、简单，是我们团队产出成熟化的一种展现。
未来我们可以把中间层接口定义为适应性更强，功能接口更为多元化的形式，有利于我们发展新客户和适应不同客户的要求。当然内部实现是不暴露给用户的。<br>


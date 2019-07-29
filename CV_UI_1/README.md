# Part 1 HTTP_Server Static Lib  Packaging
## Result
本项工作实现将前面CSGO_Server工具的内部功能打包成静态库的形式，已在客户端成功实现功能调用。最终输出如下：<br>
![app](https://github.com/sustcpengyubin/QtExample/blob/master/CV_UI_1/images/lib.jpg)  
其中.h和.lib为项目生成所需文件，.dll为项目运行所需文件。<br>

## Learning
### 学习思路分析
在此前，我并没有打包静态库的经验，而且因为CSGO_Server是基于Qt开发的，与常规的C++项目有一定的区别，所以要高效的掌握和实现Qt静态库打包的技能，我需要有目标的学习，我的学习例程如下：<br>
•	实现基本的C++静态库打包和运用<br>
•	分析静态库打包的依赖添加、学习打包技巧<br>
•	分析网上关于Qt静态库实现样例<br>
•	分析CSGO_Server实现函数的依赖库（如QtCore、QtNetwork）<br>
•	实现普通C++工程调用CSGO_Server功能（添加QtCore、QtNetwork依赖）<br>
•	实现基于Qt的静态库打包和运用<br>
•	优化静态库暴露接口，与中间层功能接轨<br>
单纯会用而不知其所然，这不利于长远的发展，所以学习对我而言必须是有章法可言的。实现一个任务首先需要理解其预期功能和实现目的，主要核心技术是什么。掌握一项技能需要从最简单最基础的实现开始，可能像累积木一样一步一步进阶，也可能像搭高达一样一个模块一个模块的实现然后拼装。从简到繁，再从繁到简，学习就是这么一回事。<br>

### Qt Class Lib 打包静态库
我发现在VS上的QT工程与普通的C++工程差别在于前者运用了Qt特有的变量、函数等，如默认的QtCore（Qt基础库）,以及提供TCP服务的QtNetwork）。首先我们要分析Qt本身到底怎么实现这些功能的。<br>
在“CSGO_Server”工具开发过程中，想要用什么功能，都是要引用对应的头文件的，而在VS+QT平台上开发，因为用到了QtNetwork，所以在链接器设置里面自动的引用了“QtNetwork.lib”。现在思路就清晰了，Qt功能实现同样是以加载静态库的方式实现，那么要在普通C++项目中使用Qt特有的一些函数和控件，加载对应的Qt库即可。
在QT本地安装路径中找到QtCore和QtNetwork文件夹以及QtCore.lib和QtNetwork.lib静态库，引用和加载即可。<br>

### TCP服务器同时支持同类型游戏
考虑到未来可能有同类型（同样基于HTTP协议实现）的游戏添加，基于TCP服务器是对每一个客户端开一个线程通信，所以我们可以只声明一个TCP服务器支持所有同类型的游戏。这时我想到了单例模式，即静态库主实现类，只会有一个声明（静态）。使用方式如下：<br>
![app](https://github.com/sustcpengyubin/QtExample/blob/master/CV_UI_1/images/point.jpg)  
 
服务器获取客户端（游戏）发送数据报后解析，每个客户端后设置其接收数据的类型（哪种游戏），即其会对接收到数据包进行初解析，是指定游戏发送的数据报则进行进一步解析，进而发送事件信息。 <br>

### 信息输出控制
因为中间层对于模型的运行是有两种方式：<br>
•	基于模式： AI_RESULT RunMOD(AI_MOD modHandler);<br>
•	基于游戏 ：AI_RESULT RunMOD(GAME_TYPE gameHandler);<br>
而对于本项目中，就CSGO而言，目前设置了4种模式输出：<br>
•	CSGO_MODE_KILL 普通击杀<br>
•	CSGO_MODE_KILLhs 爆头击杀<br>
•	CSGO_MODE_DEATH 死亡<br>
•	CSGO_MODE_KINFE 切换刀<br>
而服务器是根据客户端发送的数据包直接解析出这四种模式的输出，那么针对于中间层对于模式的选择，我的想法是在服务器内部加上模式输出的开关（bool[]，初始值都为false），衍生出以下APIs：<br>
•	void SetEnable_All(void); 所有模式设置为开<br>
•	void SetDisable_All(void); 所有模式设置为关<br>
•	void SetEnable(Game_Message mode); 选中模式设置为开<br>
•	void SetEnable(Game_Message modes[]);选中模式队列设置为开<br>
•	void SetDisable(Game_Message mode); 选中模式设置为关<br>
•	void SetDisable(Game_Message modes[]); 选中模式队列设置为关<br>
•	bool isAllDisable(); 判断是否所有模式为关，为了方便关闭服务器<br>

## Suggestions 
虽然如CSGO这样提供事件输出的游戏占少数，但是基于HTTP实现的方式在反应速度和事件正确性上，与AI训练相比较是有很大优势。因此我觉得我们未来在模型方面的工作可以分为几个方向：<br>
•	增强基于openvino的模型的事件预测准确率<br>
•	扩展更多的同样提供事件APIs的游戏<br>
•	探索更多的现有的游戏事件获取方式<br>

# Part 2 Middle Layer for Openvino Project
## Result
对中间层API的优化与更新是一个持续性的工作。针对于用户信息获取的便利性，在状态信息输出做了以下改进：<br>
•	MODsListReport(game) : 输出选择游戏suo 提供的模型信息<br>
•	All_MODsListReport(void) : 输出所有游戏所提供的模型信息<br>
•	CFG_MODsListReport(void) : 输出所有已配置游戏所提供的模型信息<br>
•	RUN_MODsListReport(void) : 输出所有正在服务的游戏所提供的模型信息<br>
其余APIs：<br>
•	void Clean_CfgMOD(void); ：清除已配置信息<br>
•	AI_RESULT CfgMOD(AI_MOD modHandler[], AI_Equipment equipments[]); ：设置模型（按列表）<br>
•	AI_RESULT CfgMOD(AI_MOD modHandler, AI_Equipment equipments); ：设置模型（单个模型）<br>
•	AI_RESULT CfgMOD(GAME_TYPE gameHandler, AI_Equipment equipments); ：设置模型（按游戏）<br>
•	AI_RESULT RunMOD(AI_MOD modHandler);： 运行模型（单个模型）<br>
•	AI_RESULT RunMOD(GAME_TYPE gameHandler); ： 运行模型（按游戏）<br>
•	AI_RESULT StopMOD(AI_MOD modHandler); ：停止运行（单个模型）<br>
•	AI_RESULT StopMOD(GAME_TYPE gameHandler);：停止运行（按游戏）<br>
•	AI_RESULT Free(void); ：释放资源<br>
## Learning
### 状态信息输出
状态信息输出的几个函数，返回值都是”string”类型。考虑到用户可能需要根据输出内容做信息提取，为了方便用户操作，我对输出进行框架设计，如下图：<br>
![app](https://github.com/sustcpengyubin/QtExample/blob/master/CV_UI_1/images/output1.jpg)  
 
以”游戏” { “模式”: “描述”, … … }, … … 的形式进行输出，用户可根据标签的前后信息的不同，利用正则表达式实现信息提取。<br>

### 模型事件---信号注册
随着对中间层功能的进一步理解，有个问题随之浮现：模型是以怎样的方式发事件消息发送出来的，换句话说，用户用我们的sdk，是怎么被通知事件发生的？（用户被动接收事件）<br>
这里需要注意的是，我们的最后产出的lib，是可以适用在纯C++项目里的。在QT中，实现信号的发射和接收是非常便捷的，类继承QObject，即可通过signal和slot实现事件绑定。但是在这里，需要用到windows自带的方式：<br>
信号注册：const UINT HTTP_SERVER_MESSAGE = ::RegisterWindowMessage(_T("HTTP_CSGO"));<br>
信号发射：::PostMessage(HWND_BROADCAST, HTTP_SERVER_MESSAGE, 0, int(type));<br>
用户需要做的，就是监听信号事件，根据不同信号，实现不同功能，在信号发射函数有两个可控数值，正好可以以[ 游戏， 模型 ]的格式，向用户输出事件。<br>
### 结构体继承与子类信息丢失
在“CSGO”中，是需要获取服务器端口号的，而相关信息都存在在XML文件中。在工程初始化过程中，读取XML文件并将游戏和模型信息存放在对应的结构体中。为了优化代码结构，我用装饰者模型以结构体继承方式，实现不同类型游戏配置信息的配置（在子类中重写初始化函数）。但是问题出现了，我用父类指针将子类存入vector，在这个过程中，父类和子类的非共有信息其实是丢失的。<br>
解决方法其实很简单，就是将所有变量声明放在父类实现。这是暴力的解决方法，更智慧的方案有待未来研究。<br>

## Suggestions 
底层、中间层、应用层（demo），我们的项目从无到有，现在俨然是一个不小的项目了。中间层框架的搭建，对于一个新手来说，是个不小的挑战。怎么设计出一种可扩展的、可兼容的、实用的、条理清晰的框架，是我一直在思考和探索的问题。包括报错规范、模块化功能函数、配置文件格式设计、模型的调用逻辑和嵌入等等，都是灵感和努力的共同产物。<br>
一开始接到这个任务时，是倍感压力的，因为自己对此一无所知，在印象里这是个大工程。但是我一步一步的实现，一个坑一个坑的去解决，最后发现，其实也不是很难，重在创造与实现。<br>
我的框架客观来说，可能在某些防线还是不够优化的，未来我会持续的改进、优化、扩展，逐步搭建起一个成熟实用的AI平台。<br>

# Part 3 Middle Layer Static Lib  Packaging and Demo
## Result
我们最终要输出给用户的，就是以静态库和依赖组成的sdk。所以成功实现这一过程，是最终能够交工的关键步骤。<br>
要实现的有两点：<br>
•	将各功能模块打包成lib<br>
•	将多个lib打包成一个lib<br>
## Learning
### 多个lib打包成一个lib
我们整个中间层需要加载很多不同的静态库lib，但理想情况是我们只输出一个lib。工程加载lib的方式是：#pragma comment(lib,"AILIBd")，lib文件的命名其实是什么都可以。那么怎么把多个lib打包成一个lib呢？经查询，在VS安装目录/VC/bin文件夹内有一个lib.exe，可实现对多个lib的合成。指令如下<br>
lib.exe /out:AILIB.lib AICENTERd.lib HttpServerd.lib Qt5Networkd.lib Qt5Cored.lib<br>

### 没有生成dll的问题
前面提到，dll是最终app需要使用的文件，但在静态库生成过程中，会出现输出目录下只有lib文件而没有.dll文件的情况。经查询后，解决方法其实很简单，修改项目输出类型即可，设置为.dll输出，目录下会同时生成.dll和.lib文件。<br>
https://blog.csdn.net/huanghai381/article/details/49854063<br>
![app](https://github.com/sustcpengyubin/QtExample/blob/master/CV_UI_1/images/set.jpg) 

### QMedaObject报错
在demo的实现过程中出现了这样的一个很奇怪的问题，在没有明显bug的情况下，编译不通过。报错显示缺乏moc_ AICENTER.cpp文件，经查询，这是VS环境下编译Qt工程的常见报错。解决方案是在Qt安装目录\Qt\bin文件夹内使用moc.exe工具，类似上面提到的lib.exe工具，命令行如下：<br>
moc "D:\VC++\QtT\MyDialog\MyDialog\LoginDlg.h" –o "D:\VC++\QtT\MyDialog\MyDialog\moc_LoginDlg.cpp"<br>
https://www.cnblogs.com/lovebay/p/9337528.html<br>
生成moc_AICENTER.cpp后要添加入工程，然后放在debug/release文件夹里，程序即可正常运行。<br>

## Suggestions 
在完成这项工作之前，我总担心会因为CSGO是基于Qt实现的，整合到总框架中会造成普通C++项目无法加载的问题。在一次次的尝试和探索中，我对于C++工程项目关于静态库依赖有了更深的认识，也学会了如何在普通C++工程项目中如何运用Qt现成库的功能。Qt函数库功能十分强大，可以很方便的实现很多我们需要的功能，这对未来项目的开发是极具好处的！<br>
在此项工作中完成了GUI运用静态lib的实现，已多次在给客户的展示中起到了关键作用。<br>


# Part 4 GUI DEMO For Project Output 
我们项目定位是最终产出sdk，服务于用户使用，那么我们需要做到的有两点：<br>
•	提供用户对于APIs使用的示例<br>
•	提供sdk的使用的呈现效果<br>
这要求我们实现一个APP Demo，用于为用户如何使用提供参考，而且要完美的呈现我们产出的实用性、可靠性。这对于吸引新用户是非常关键的一项工作。而且也服务于我们产品的功能性测试。<br>
## Result
整个GUI实现即项目的应用层，主界面有三个：<br>
•	设备支持：设备检索、设备选择<br>
•	AI辅助：游戏模型设备配置与选择、游戏运行<br>
•	场景辅助：用户自定义功能性场景实现<br>
## Learning
### 设备支持—目标设备
![app](https://github.com/sustcpengyubin/QtExample/blob/master/CV_UI_1/images/device_found.jpg)  
我们与设备合作商的卖点就在于“独家”“专供“，即“本服务仅适用于合作方或者厂商设备”。于是我设计在设备支持的列表中，只会检测是否连接目标设备（合作设备），供用户选择。<br>
那么如何实现对设备的过滤呢？我采用了读取预存数据的方法。在外置设备的属性值中，有：<br>
•	PID: 厂商id<br>
•	VID: 设备id<br>
不同厂商的不同型号的设备，PID和VID的组合值是不同的。我将目标设备的相关数据保存在XML文件中，以这种方式存储是为了方便未来新增新设备。信息包括：设备名、设备类型、PID、VID。（可扩增）<br>
![app](https://github.com/sustcpengyubin/QtExample/blob/master/CV_UI_1/images/deviceXML.jpg)  
在程序中获取本地usb设备连接信息后，与目标设备信息进行匹配即可进行信息过滤。<br>

### 设备支持—设备热插拔
设备的检测是对函数的调用，然后进行页面刷新。如果说用户每次插拔设备后都需要手动刷新目前设备的连接状况，这显得过于笨拙，也体现不出我们Intel的实力。我联想到windows系统下的设备管理器界面会随着usb设备的插拔而实时的更新界面，以及windows下事件发生机制，预判在windows机制下，存在已有的APIs能够实现对usb设备插拔事件的实现事件报告。经过网上检索与实践，我最终的设备热插拔功能实现原理很简单：<br>
•	获取系统事件、判断是否属于usb拔插事件<br>
•	是则发送事件信息，调用设备检测函数<br>
 ![app](https://github.com/sustcpengyubin/QtExample/blob/master/CV_UI_1/images/hotdevice.jpg)   
### 设备支持—设备显示
在关于设备显示这块，有这样的两个想法：<br>
•	显示所有的已插入设备（同型号设备有n个，则显示n个）<br>
•	只显示各型号一个设备<br>
第一种想法问题在于，同种型号设备属性值是一样的，而且合作商如delux提供的APIs是针对于电脑上所有插入的目标设备的，我们无法实现单独把信息发送给某个设备。倘若用户电脑上插入两个同型号设备，他只选择一个设备，另一个不选择，在游戏运行时如果事件发生，两个设备都会有同样的反应。解决方案是合作商提供新的APIs，满足针对性设备选择与设置。<br>
针对于第一种方法的存在问题，我们暂时采用第二种方案，以设备型号为基本单位。<br>
### AI辅助---游戏与模式选择
![app](https://github.com/sustcpengyubin/QtExample/blob/master/CV_UI_1/images/gameShow.jpg)   
![app](https://github.com/sustcpengyubin/QtExample/blob/master/CV_UI_1/images/gameShow2.jpg)   
考虑到我们未来会持续不断的添加新的游戏和扩展不同的设备，我将AI辅助页面以框架的形式搭建，软件根据XML文件内容来显示页面。框架如下<br>
<GameList><br>
  <Game Name="游戏名" Type="游戏类型"><br>
    <Describe><br>
      <text>游戏描述</text><br>
    </Describe><br>
    <Device Name="设备名" Type="设备类型"><br>
      <Mode Name="模型事件" Type="事件类型"><br>
        <Drop>效果1</Drop><br>
        <Drop>效果2</Drop><br>
        。。。。。。<br>
      </Mode><br>
      。。。。。。<br>
</Device><br>
。。。。。。<br>
  </Game><br>
  。。。。。。<br>
</GameList><br>

在AI辅助页面中每种游戏有各自的设备设置页面，点击游戏图标即可切换，游戏之间设置互不干扰，在欢迎界面启动模型。<br>
![app](https://github.com/sustcpengyubin/QtExample/blob/master/CV_UI_1/images/gameShow.jpg)   
未来将于加速器厂商合作，在软件内嵌入加速器功能<br>
 

### AI辅助---模式效果选择
我们计划联动的设备有：键盘、鼠标、鼠标垫、机箱、音响、摄像头等等，我将它们分为灯光（音频）输出类和图像输入类（即摄像头），这两种设备类型的效果选择界面，从功能实现上必然是不同的。<br>
灯光（音频）输出类<br>
![app](https://github.com/sustcpengyubin/QtExample/blob/master/CV_UI_1/images/light.jpg)  
如图，灯光（音频）输出类只需要软件获取模型事件输出信息后，实现调用设备APIs进行效果呈现。那么对于不同的事件，我们预置对应的效果供用户选择即可。用户勾选开启，即可在游戏运行时调动该设备。<br>
图像输入类<br>
![app](https://github.com/sustcpengyubin/QtExample/blob/master/CV_UI_1/images/camera.jpg)   
图像输入类在于通过摄像头获取用户活动事件后，联动键盘，触发对应的键盘事件，那么对于不同的模型事件，需要提供热键选择，即用户可以把该事件与任意的键盘事件绑定，当然，我们会提供一些初始化设置。<br>

### AI辅助---热键绑定
在热键选择中，如何让用户实现热键与事件绑定是一个问题，我想到以下方案：<br>
方案一：用户在下拉列表中选择<br>
Pass：操作麻烦，而且考虑到多按键组合，下拉列表内容会非常多。。。<br>
方案二：虚拟键盘<br>
Pass：操作繁琐，实现困难。<br>
方案三：捕捉实际键盘事件<br>
Good：这也是现在设置热键的主流方式<br>
用户点击“热键设置为：”后面的按钮，即进入该热键的设置模式，在此模式下，用户的按键事件会被实时捕捉并在按钮上呈现，满足多按键捕捉<br>如“Ctrl+?”、”Alt+？”等。当用户再次点击按钮，即退出热键设置模型，保存热键信息。<br>

### AI辅助---结构体指针实现整体布局
在之前的工作中，如外部库打包（项目最终产出sdk）等都是以结构体的方式进行数据保存和设置等操作，在页面的生成中，我之前都是采用实值传入的方式，那么在不同层次间的信息交互，往往需要用信号机制实现，这使得我的代码框架逻辑复杂，且不易修改。<br>
在AI辅助功能上，我采用指针传入的方式，以一个主结构体（游戏vector）控制和保存整个页面各个单元模块（游戏、设备模型选择、模型效果选择）的设置，无需进行信号传递。<br>

### 关于UI界面美化
UI界面美化素材将有Intel内部或者外包团队实现，期望获得Intel软件风格和游戏金属风格兼具的UI素材。<br>
## Suggestions 
在这段时间的工作中，我发现项目的功能实现很重要，但成果在合作商面前的展现效果如何更是至关重要，只有眼见为实才能获得客户和合作商的信赖和支持，进行更深度的合作。<br>
未来，我们将会有更多基于Openvino的合作项目以及各种展示，虽然我们目标是产出sdk，但一套完善前端应用Demo会让我们的想法更具有说服力。到底行不行，现场看看效果是最为直接的。<br>

在效果呈现方面，鉴于灯光在实验室环境中的不明显，我们可以先搞出音响联动，在事件发生时，音响发出对应的音频，这呈现效果会是极好的！<br>







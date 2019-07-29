# CsGo Server
## Result
Base on VS+Qt, I realize the tool called “CSGO_Server”, which 基于Tcp协议实现监测用户在玩CSGO时的特殊事件，如击杀、死亡、换刀等。响应速度快，无延迟。<br>
### Functions:
1.	Check the user's local environment for CSGO installation 检查游戏安装环境<br>
2.	Check CFG file and install it to user’s local directory 内置目标CFG文件<br>
3.	Real-time monitoring of user events and signal return 实时信息捕捉、分析和播报<br>
### Presentation:
 ![app](https://github.com/sustcpengyubin/QtPrivate/blob/master/CSGO_Server/images/app.jpg)  
CSGO_Server Show<br>
如图，当软件开始运行，会检测键盘（DELUX）是否连接。点击“Check CFG”检查本地环境和CFG文件的配置情况。上图游戏事件发生依次为：普通击杀、爆头击杀、死亡。<br>

## Learning
用户本地环境检查，注册表信息查看<br>
获取CSGO事件信息需要在电脑本地CSGO安装路径下放置一个CFG配置文件，那么检查用户电脑中是否安装CSGO是必要的步骤。<br>
![check](https://github.com/sustcpengyubin/QtPrivate/blob/master/CSGO_Server/images/Check.jpg)  
Check Process<br>
在CSGO_Server的开发中，是基于Qt现有的库函数实现的，在打包成外部库时需要添加Qt对应的依赖，这个将在后面的工作“Qt外部库打包”中解决。<br>
如果用户有安装Stream，我可以通过QSettings从注册表中获取 Stream的安装路径，进而通过QDir检查用户是否安装CSGO。<br>
 ![steamPath](https://github.com/sustcpengyubin/QtPrivate/blob/master/CSGO_Server/images/steamPath.jpg)  
SreamPath<br>
### 管理员权限的获取
要实现CSGO事件获取，需要在CSGO目录下放置特定的CFG文件，我通过QFile拷贝文件到指定位置。但如果用户将游戏安装在系统盘（C盘），会拷贝失败。经研究，我发现软件需要获取管理员权限。我是基于VS实现的Qt开发，经查询发现，在2017版VS可以很简单在设置里修改软件权限。<br>
![uac](https://github.com/sustcpengyubin/QtPrivate/blob/master/CSGO_Server/images/uac.jpg)  
Change UAC Level<br>
### 对返回字符串的识别和信息提取
CSGO游戏是通过HTTP协议发送长字符串的方式来告知游戏事件的，我需要做的就是从中提取出关键信息，如steamid、游戏状态、击杀人数、死亡人数、武器状态等。<br>

因为我们只需要实现简单的数据收发功能，所以搭建HTTP服务器不是必须的，而HTTP协议是基于TCP协议实现的。我采用Qt原有的库QTcpServer，对其接收信息函数等进行重写，实现满足项目需求的TCP服务器。<br>
对于字符串的提取，我想到了正则表达式，经查询，Qt中有现成的库QRegExp，这是极好的消息。然而QRegExp的语法规则与常见的正则表达式不太一样，在多次尝试中，我发现以下规律。<br>
•	String: "steamid": "76561198316270523",<br>
•	RegExp: \"steamid\": \"([0-9]+)\",<br>
•	QRegExp: \\\"steamid\\\": \\\"([0-9]+)\\\",<br>
对于转译，QRegExp需要多加’\\’。总的正则字符提取语句如下：<br>
"\\\"steamid\\\": \\\"([0-9]+)\\\",([0-9a-z\\n\\t\\\"\\s\\S]+)\\\"player\\\": \\{[\\n\\t\\s\\S]+\\\"steamid\\\": \\\"([0-9]+)\\\",[0-9a-z\\n\\t\\\"\\s\\S]+\\\"round_killhs\\\": ([0-9]+),[0-9a-z\\n\\t\\\"\\s\\S]+\\\"weapons\\\"([0-9a-z\\n\\t\\\"\\s\\S]+)\\\"kills\\\": ([0-9]+),\\n\\t\\t\\t\\\"assists\\\": [0-9]+,\\n\\t\\t\\t\\\"deaths\\\": ([0-9])+,"<br>
![code1](https://github.com/sustcpengyubin/QtPrivate/blob/master/CSGO_Server/images/code1.jpg)  
 
以此实现对事件信息的提取。<br>
 ![text1](https://github.com/sustcpengyubin/QtPrivate/blob/master/CSGO_Server/images/text1.jpg)  
CSGO Message<br>
### 死亡事件后的他人信息误报
在用户（第一人称）死亡后，游戏视角会自动切换到第三人称，游戏会继续发送他人的游戏信息。因为我们是只针对用户本人游戏事件进行处理，所以需要进行信息过滤。<br>
![text2](https://github.com/sustcpengyubin/QtPrivate/blob/master/CSGO_Server/images/text2.jpg) 
![text3](https://github.com/sustcpengyubin/QtPrivate/blob/master/CSGO_Server/images/text3.jpg) 
User Message<br>
起初我针对”name”标签进行信息提取和判定，以第一次出现的信息提出的”name”作为用户名称（第一次出现时为第一人称，必然是该用户的），但是因为名称会出现中文、字母、数组、特定字符等，有数据误提取的可能，所以不采取。<br>
在进一步的研究中，我发现，”provider”中提供的”steamed”是固定的，即为用户的steamid，不随游戏状态的改变而改变。而”player”中的”steamed”则与游戏状态相关，所以判断两个”steamed”是否相同可以作为游戏状态的判断，相同则为第一人称，即存活，不同则为第三人称，即死亡。<br>

### 解决数据包丢失的问题：HTTP 200 ok
在完成TCP服务器的基本功能后，我成功的接收到了CSGO游戏发出的消息并解析出事件信息，但是存在信息缺失和延迟问题。经研究我发现问题在于CSGO游戏是以HTTP协议发出信息，而我的服务器是TCP服务器，两者的差别在于HTTP服务器会在成功接收到数据包后发送”200 OK“数据包回复。因为我的TCP服务器并没有返回此数据报，所以游戏只能等timeout（5s）之后重新连接服务器，继续发送数据。于是我设置TCP服务器在每次收到信息之后都会直接返回以下数据报信息，成功实现无延迟的信息接收。<br>
 
### 多线程，防止阻塞
考虑到未来以此方式实现监测功能的游戏可能不止一种，我将TCP服务器修改成多线程模式，以防止消息阻塞。我采用Qt原有库QThread，对其Run函数进行重写。每当一个新的客户端连接进来，都会开启一个新的线程服务，在该客户端断开连接后退出该线程。  <br>

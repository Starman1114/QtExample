# 可控区域截屏软件<br>

## 初始界面
---
Ctrl+F1 ： 添加框（目前设置为最多一个框<br>
Ctrl+F2 ： 切换框的类型：绿：正样本；橙：负样本（目前设置为二分类<br>
Ctrl+F3 ： 启动和暂停（保存为jpg图片）<br>
Tips： 有Fn键的电脑需要Ctrl+Fn+F？ <br>
![初始界面](https://github.com/sustcpengyubin/QtExample/blob/master/ScreenShot/images/origin.png)  
文件夹名称 / 定时器时间间隔（单位：ms） / 桌面分辨率<br>
## 框操作
---
正、负框（置于最顶层）<br>
![框](https://github.com/sustcpengyubin/QtExample/blob/master/ScreenShot/images/positive.png)  
![框](https://github.com/sustcpengyubin/QtExample/blob/master/ScreenShot/images/negative.png)  
在实线处右键菜单：切换框类型（Ctrl+F2）、删除框<br>
![框](https://github.com/sustcpengyubin/QtExample/blob/master/ScreenShot/images/menu.png)  
实时显示矩形框的左上顶点坐标x、y和宽度、高度，并可直接输入数值改变框的位置和大小
![框](https://github.com/sustcpengyubin/QtExample/blob/master/ScreenShot/images/valueSet.jpg)  
## 运行
---
截屏并保存）虚线变实线<br>
![运行](https://github.com/sustcpengyubin/QtExample/blob/master/ScreenShot/images/save.png)  
![运行](https://github.com/sustcpengyubin/QtExample/blob/master/ScreenShot/images/result.jpg)  

## 相关技术
---
•	全局热键<br>
•	窗口置顶<br>
•	窗口透明（鼠标穿透）<br>
•	基于QT截屏<br>
•	右键菜单（Menu\Action）<br>
•	非父类窗口间同步关闭（signal）<br>
•	窗口移动<br>
•	键盘事件<br>

# Summary
### Goal：For the original training data acquisition, it is based on manual fine-tuning script parameters, which is time-consuming, laborious and inefficient. Therefore, a convenient image data acquisition tool is developed.  <br>
我们原先训练数据采集方式，是基于手工微调脚本参数（采集图像区域的位置，长宽），费时费力、效率低下。因此，开发了一种方便的图像数据采集工具是必然且急需的。<br>
## Result
Base on VS+Qt, I realize the tool called “ScreeShot”, which can intercepting image information of custom area and save them as pictures. 采集指定区域图像并保存为图片（jpg）。<br>
### Functions:
1.	Implemented by keyboard keystrokes:  通过键盘实现<br>
•	Add/delete box  添加/删除截图框<br>
•	Change box type (positive/negative) 改变截图框类型<br>
•	Start/stop recording 开始/停止截图<br>
2.	Rectangular frame can be moved and stretched at will 截图框可移动和拉伸<br>
3.	Real-time updating of the location, length and width of the box 实时显示截图框左顶点位置和长宽<br>
4.	Customize the location, length and width of the box (confirm by pressing the Enter key) 自定义截图框的左顶点位置和长宽<br>
5.	Customize Folder Naming and Sampling Interval 自定义文件名和采样频率<br>

## Learning
在此之前，我并未编写过类似的软件，这是一个新的开始。在开始编写脚本之前，我对开发的功能要求和可行性进行了分析。<br>
### 现有的类似软件分析：
 ![EV录屏](https://github.com/sustcpengyubin/QtExample/blob/master/ScreenShot/images/Ev.jpg) 
EV录屏<br>
现有的录屏软件都提供自定义区域录制和窗口置顶的功能。<br>

### QT截屏的可行性分析：
基于QT编写的截图软件如Snipaste功能受人推崇，而且在网上有很多基于QT的截图和录屏工程的实现。QT提供一个方法：QScreen::grabWindow(WId window, int x = 0, int y = 0, int width = -1, int height = -1), 可实现自定义区域（左顶点位置、长宽）图像截取。基于此，使用QT是可行的。<br>

### 功能要求分析：
从实用性与具体运用场景出发，我列举了一下实现要求与相关技术，并一一实现。<br>
•	截图框的实现  --> 窗口去除标题栏、边框绘制（Css）<br>
•	截图框透明，且不影响窗口下方其他软件的操作  -->  窗口透明、鼠标穿透<br>
•	截图框置于顶层 -->  窗口置顶<br>
•	截图框可移动、拉伸 --> 鼠标事件、窗口拉伸与移动、信号触发机制<br>
•	在截图框失去焦点时，仍对键盘事件有反应  --> 全局热键、键盘事件<br>
•	对特定区域图像获取  --> 屏幕图像获取<br>
•	持续的图像获取与保存 --> 定时器、文件夹和文件操作、图像保存<br>
•	截图框功能菜单 --> 右键菜单（Menu\Action）<br>
•	主程序最小化时，截图框不最小化 --> 父子窗口继承机制<br>
在我的设计中，截图框是独立的自定义控件，因此可以无限制的添加。满足于同时截取多个区域图像的要求。<br>

## Suggestions 
在机器学习、深度学习领域的研究工作中，准确、且大量的数据集是提高算法准确性的基础，也是最耗时间的。在我们的项目中，每个游戏不同模式都需要单独的数据集进行训练，所针对的位置不尽相同，而且为了提高准确率，对样本集的大小是有一定要求的。在这种情况下，开发一个便于图像数据采集的保存的工具是非常必要且明智的。
对于类似工具的开发，我有新的想法。目前模型在实际场景下的测试，光靠我们人眼对模型的准确率没有一个明确的判断。我们可以开发这样一个工具：<br>
•	提供视频打标签功能，在击杀/死亡等事件发生时，按下键盘特定键位，软件自动记录（文件名、事件序列[ 时间1，事件1；时间2，事件二；……]）并保存为数据文件。<br>
•	对模型的输出进行记录，以该视频的实际事件序列进行对比（时间对比允许一定的容错率），实现准确率和误判率的计算<br>

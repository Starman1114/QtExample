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
截屏并保存<br>
![运行](https://github.com/sustcpengyubin/QtExample/blob/master/ScreenShot/images/save.png)  

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


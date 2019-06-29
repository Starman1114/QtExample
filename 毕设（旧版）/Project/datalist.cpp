#include "datalist.h"

dataList::dataList()
{

}
unsigned long ulComNo =4;
unsigned long ulBaund =9600;
bool running =false;
int timeSpace = 200;
double SampleRate = 25;
bool record = false;
dataStore dataStore1;
int maxSize=60;
//图示
QList<QLineSeries*> m_series;
QList<QDateTimeAxis *> axisX;
QList<QValueAxis *> axisY;


int type=0;//修改类
QModelIndex ind;

QStringList cc={"color0","color1","black","white","darkGray","gray",
                  "lightGray","red","green","blue","cyan","magenta",
                  "yellow","darkRed","darkGreen","darkBlue","darkCyan",
                  "darkMagenta","darkYellow","transparent"};

FunctionD f_Recive;

QList<QLabel*> dataListShow;//数据显示

QString Path=".";

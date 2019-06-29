#include "datalist.h"

dataList::dataList()
{

}
unsigned long ulComNo =6;
unsigned long ulBaund =9600;
bool running =false;
int timeSpace = 5;
double SampleRate = 25;
bool record = false;
dataStore dataStore1;
int maxSize=100;
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

bool step_Count = false;
unsigned long STEPS=0;//记
unsigned long ENERGS=0;
signed short aOrg=0;
signed short xyzpeakthresdef=320*64;//20480 tempXYZ=tempXYZ>>6;  //这里把值右移了6位，就是乘以64
unsigned char weight1=62;
unsigned char height1=170;

QList<QLineSeries*> m_series_Count;
QList<QDateTimeAxis *> axisX_Count;
QList<QValueAxis *> axisY_Count;
FunctionD ff_Count;

float temp=0;
float valleythres = -100;
float peakthres = 20;
float isStatic=10;
bool startGait=false;
QList<QLineSeries*> m_series_Gait;
QList<QDateTimeAxis *> axisX_Gait;
QList<QValueAxis *> axisY_Gait;
FunctionD ff_Gait;
float  StepFrequence = 0;    //步频
float  StancePercent = 0;  //支撑相占的百分比
float  SwingPercent = 0; //摆动相占的百分比；
float  Speed = 0; //步速
float  SwingSpeed = 0; //摆动速度，一步中前向的最大速度
float  StrideLength = 0; //步幅
float  VerticalLength = 0;  //离地高度

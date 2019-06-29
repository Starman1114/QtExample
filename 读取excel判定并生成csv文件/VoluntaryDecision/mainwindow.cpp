#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug()<<"开始读取学生信息";
    execl_StudentNumber();
    qDebug()<<"学生信息获取，开始资格判定";
    execl_Decision();
    qDebug()<<"资格判定完毕";

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::execl_StudentNumber(){
    QAxObject excel("Excel.Application"); //加载Excel驱动
    excel.setProperty("Visible", false); //不显示Excel界面，如果为true会看到启动的Excel界面
    QAxObject* pWorkBooks = excel.querySubObject("WorkBooks");
    pWorkBooks->dynamicCall("Open (const QString&)", "C:/Users/Administrator/Desktop/专业志愿.xls");//打开指定文件
    QAxObject* pWorkBook = excel.querySubObject("ActiveWorkBook");
    QAxObject* pWorkSheets = pWorkBook->querySubObject("Sheets");//获取工作表
    int nSheetCount = pWorkSheets->property("Count").toInt();  //获取工作表的数目

    if(nSheetCount > 0){

        for(int n=0;n<nSheetCount;n++){
            QAxObject* pWorkSheet = pWorkBook->querySubObject("Sheets(int)", n+1);//获取第一张表
            QAxObject* usedrange = pWorkSheet->querySubObject("UsedRange"); // sheet范围
            QAxObject *rows, *columns;
            rows = usedrange->querySubObject("Rows");  // 行
            columns = usedrange->querySubObject("Columns");  // 列
            int intRow = rows->property("Count").toInt(); // 行数

            for(int i=1;i<intRow;i++){
                QString A = "A" + QString::number(i+1); //设置要操作的单元格，X1
                QAxObject* cellA = pWorkSheet->querySubObject("Range(QVariant, QVariant)", A); //获取单元格
                numberList.append(cellA->dynamicCall("Value2()").toString());

                QString B = "B" + QString::number(i+1); //设置要操作的单元格，X1
                QAxObject* cellB = pWorkSheet->querySubObject("Range(QVariant, QVariant)", B); //获取单元格
                nameList.append(cellB->dynamicCall("Value2()").toString());

                Class c;
                studentClass.append(c);
            }

        }
    }
    pWorkBook->dynamicCall("Close(Boolean)", false);//打开指定文件
    excel.dynamicCall( "Quit(void)" );
   // delete excel;
}

void MainWindow::execl_Decision(){
    qDebug()<<"开始课程信息读取";
    QAxObject excel("Excel.Application"); //加载Excel驱动
    excel.setProperty("Visible", false); //不显示Excel界面，如果为true会看到启动的Excel界面
    QAxObject* pWorkBooks = excel.querySubObject("WorkBooks");
    pWorkBooks->dynamicCall("Open (const QString&)", "C:/Users/Administrator/Desktop/计算机系.xls");//打开指定文件
    QAxObject* pWorkBook = excel.querySubObject("ActiveWorkBook");
    QAxObject* pWorkSheets = pWorkBook->querySubObject("Sheets");//获取工作表
    int nSheetCount = pWorkSheets->property("Count").toInt();  //获取工作表的数目
    qDebug()<<"获取文本";
    if(nSheetCount > 0){

        for(int n=0;n<nSheetCount;n++){
            QAxObject* pWorkSheet = pWorkBook->querySubObject("Sheets(int)", n+1);//获取第一张表
            QAxObject* usedrange = pWorkSheet->querySubObject("UsedRange"); // sheet范围
            QAxObject *rows, *columns;
            rows = usedrange->querySubObject("Rows");  // 行
            columns = usedrange->querySubObject("Columns");  // 列
            int intRow = rows->property("Count").toInt(); // 行数

            for(int i=1;i<intRow;i++){
                QString A = "A" + QString::number(i+1); //设置要操作的单元格，X1
                QAxObject* cellA = pWorkSheet->querySubObject("Range(QVariant, QVariant)", A); //获取单元格
                QString num = cellA->dynamicCall("Value2()").toString();

                int indexS =numberList.indexOf(num);

                QString F = "F" + QString::number(i+1); //设置要操作的单元格，X1
                QAxObject* cellF = pWorkSheet->querySubObject("Range(QVariant, QVariant)", F); //获取单元格
                QString Cnum = cellF->dynamicCall("Value2()").toString();

                int indexC =classNumber.indexOf(Cnum);

                QString H = "H" + QString::number(i+1); //设置要操作的单元格，X1
                QAxObject* cellH = pWorkSheet->querySubObject("Range(QVariant, QVariant)", H); //获取单元格
                int grade = cellH->dynamicCall("Value2()").toString().toInt();

                qDebug()<<num<<Cnum<<grade;

                ClassChange(&studentClass[indexS],indexC,grade);

            }
        }
    }
    qDebug()<<"资格信息收录完毕";
    pWorkBook->dynamicCall("Close(Boolean)", false);//打开指定文件
    excel.dynamicCall( "Quit(void)" );
   // delete excel;


}



void MainWindow::ClassChange(Class *c,int index,int value){
    switch (index){
        case 0:
        c->CS102=value;
        break;
        case 1:
        c->CS201=value;
        break;
        case 2:
        c->CS202=value;
        break;
        case 3:
        c->CS203=value;
        break;
        case 4:
        c->CS207=value;
        break;
        case 5:
        c->MA212=value;
        break;
        case 6:
        c->GE105=value;
        break;
    }
}

QString MainWindow::Conclude(Class *c){
    QString text;
    if(c->CS102==1||c->GE105==1){

    }else if(c->CS102==-1){
        text.append(QString("%1(F)、").arg(className[0]));
    }else if(c->CS102==0){
        text.append(QString("%1(未修读)、").arg(className[0]));
    }else if(c->GE105==-1){
        text.append(QString("%1(F)、").arg(className[6]));
    }else if(c->GE105==0){
        text.append(QString("%1(未修读)、").arg(className[6]));
    }

    if(c->CS201==-1){
        text.append(QString("%1(F)、").arg(className[1]));
    }else if(c->CS201==0){
        text.append(QString("%1(未修读)、").arg(className[1]));
    }

    if(c->CS202==-1){
        text.append(QString("%1(F)、").arg(className[2]));
    }else if(c->CS202==0){
        text.append(QString("%1(未修读)、").arg(className[2]));
    }

    if(c->CS203==-1){
        text.append(QString("%1(F)、").arg(className[3]));
    }else if(c->CS203==0){
        text.append(QString("%1(未修读)、").arg(className[3]));
    }

    if(c->CS207==-1){
        text.append(QString("%1(F)、").arg(className[4]));
    }else if(c->CS207==0){
        text.append(QString("%1(未修读)、").arg(className[4]));
    }

    if(c->MA212==-1){
        text.append(QString("%1(F)、").arg(className[5]));
    }else if(c->MA212==0){
        text.append(QString("%1(未修读)、").arg(className[5]));
    }

    if(text.length()==0)
        return "通过";
    return text.left(text.length()-1);
}

void MainWindow::on_CSVButton_clicked()
{
    QString file_name = QFileDialog::getSaveFileName(NULL,"文件保存",".","*.csv");
    QFile file(file_name);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return;
      }
    QTextStream out(&file);
    QStringList list;
    for(int k=0;k<numberList.length();k++){
        list.clear();
        list<<numberList[k]<<nameList[k]<<"计算机科学与技术"<<Conclude(&studentClass[k]);
        out <<list.join(",")<<"\r";
    }
    file.close();
}

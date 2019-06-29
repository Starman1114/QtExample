#include "workerthread.h"



void WorkerThread::run()
{

    if(current_STATE==EXECL_START){
        //调用一个Windows API函数初始化COM Library，头文件“windows.h”
        CoInitializeEx(NULL, COINIT_MULTITHREADED);  //这一句解决在子线程无法启动execl.exe
        execl_Data();
        emit OK_execl();
    }else if(current_STATE==WORD_START){
        //新开辟的子线程不会自动初始化COM库，所以需要我们手动来初始化。
        HRESULT r = OleInitialize(0);
        if (r != S_OK && r != S_FALSE)
        {
            qWarning("Qt:初始化Ole失败（error %x）",(unsigned int)r);
        }
        word_Gain();
        emit OK_word();
        //使用结束后需要释放掉
        OleUninitialize();
    }



}

void WorkerThread::execl_Data(){
    QAxObject excel("Excel.Application"); //加载Excel驱动
    excel.setProperty("Visible", false); //不显示Excel界面，如果为true会看到启动的Excel界面
    QAxObject* pWorkBooks = excel.querySubObject("WorkBooks");
    pWorkBooks->dynamicCall("Open (const QString&)", "C:/Users/Administrator/Desktop/list.xls");//打开指定文件
    QAxObject* pWorkBook = excel.querySubObject("ActiveWorkBook");
    QAxObject* pWorkSheets = pWorkBook->querySubObject("Sheets");//获取工作表
    int nSheetCount = pWorkSheets->property("Count").toInt();  //获取工作表的数目

    if(nSheetCount > 0){
        QAxObject* pWorkSheet = pWorkBook->querySubObject("Sheets(int)", 1);//获取第一张表

        QAxObject* usedrange = pWorkSheet->querySubObject("UsedRange"); // sheet范围
    //    int intRowStart = usedrange->property("Row").toInt(); // 起始行数
    //    int intColStart = usedrange->property("Column").toInt();  // 起始列数
        QAxObject *rows, *columns;
        rows = usedrange->querySubObject("Rows");  // 行
        columns = usedrange->querySubObject("Columns");  // 列
        intRow = rows->property("Count").toInt(); // 行数
       // int intCol = columns->property("Count").toInt();  // 列数

        //读方式
        int count=3;
        for(int i=0;i<intRow-2;i++){
            QString B = "B" + QString::number(i + count); //设置要操作的单元格，B1
            QAxObject* cellB = pWorkSheet->querySubObject("Range(QVariant, QVariant)", B); //获取单元格
            Name_Class.append(cellB->dynamicCall("Value2()").toString());

            QString D = "D" + QString::number(i + count); //设置要操作的单元格，D1
            QAxObject* cellD = pWorkSheet->querySubObject("Range(QVariant, QVariant)", D); //获取单元格
            Place.append(cellD->dynamicCall("Value2()").toString());

            QString F = "F" + QString::number(i + count); //设置要操作的单元格，F1
            QAxObject* cellF = pWorkSheet->querySubObject("Range(QVariant, QVariant)", F); //获取单元格
            Pre_Time.append(cellF->dynamicCall("Value2()").toString());

            QString G = "G" + QString::number(i + count); //设置要操作的单元格，G1
            QAxObject* cellG = pWorkSheet->querySubObject("Range(QVariant, QVariant)", G); //获取单元格
            End_Time.append(cellG->dynamicCall("Value2()").toString());

            QString H = "H" + QString::number(i + count); //设置要操作的单元格，H1
            QAxObject* cellH = pWorkSheet->querySubObject("Range(QVariant, QVariant)", H); //获取单元格
            Major.append(cellH->dynamicCall("Value2()").toString());

            QString I = "I" + QString::number(i + count); //设置要操作的单元格，I1
            QAxObject* cellI = pWorkSheet->querySubObject("Range(QVariant, QVariant)", I); //获取单元格
            Minor.append(cellI->dynamicCall("Value2()").toString());
        }
    }
}

void WorkerThread::word_Gain()
{
    for(int i=24;i<intRow-2;i++){
        qDebug()<<i<<endl;

        //   //新建一个word应用程序,并设置为不显示界面
        //   QAxWidget *word=new QAxWidget("Word.Application", 0, Qt::MSWindowsOwnDC);
        //   word->setProperty("Visible", false);
        //   // 获取所有的工作文档
        //   QAxObject * documents = word->querySubObject("Documents");
        //   // 以文件exam.doc为模版新建一个文档
        //   documents->dynamicCall("Add(QString)",QString::fromLocal8Bit("C:/Users/Administrator/Desktop/exam.docx"));
        //   // 获取当前激活的文档
        //   QAxObject *document=word->querySubObject("ActiveDocument");

        //在子线程中不能打开窗口，只能在主GUI线程打开，故而改用下面的代码
        QAxObject word("Word.Application"); //加载Word驱动
        word.setProperty("Visible", false); //不显示Word界面，如果为true会看到启动的Word界面
        QAxObject* documents = word.querySubObject("Documents");
        documents->dynamicCall("Add(QString)",QString::fromLocal8Bit("C:/Users/Administrator/Desktop/exam.docx"));//打开指定文件
        QAxObject *document=word.querySubObject("ActiveDocument");

        // 获得标签
        QAxObject*bookmark_Name_Class=document->querySubObject("Bookmarks(QString)","Name_Class");
        // 选中标签，将字符插入到标签位置
        if(!bookmark_Name_Class->isNull()){
        bookmark_Name_Class->dynamicCall("Select(void)");
        bookmark_Name_Class->querySubObject("Range")->setProperty("Text",Name_Class[i]);
        }

        QAxObject*bookmark_Place=document->querySubObject("Bookmarks(QString)","Place");
        if(!bookmark_Place->isNull()){
        bookmark_Place->dynamicCall("Select(void)");
        bookmark_Place->querySubObject("Range")->setProperty("Text",Place[i]);
        }

        QAxObject*bookmark_Pre_Time=document->querySubObject("Bookmarks(QString)","Pre_Time");
        if(!bookmark_Pre_Time->isNull()){
        bookmark_Pre_Time->dynamicCall("Select(void)");
        bookmark_Pre_Time->querySubObject("Range")->setProperty("Text",Pre_Time[i]);
        }

        QAxObject*bookmark_End_Time=document->querySubObject("Bookmarks(QString)","End_Time");
        if(!bookmark_End_Time->isNull()){
        bookmark_End_Time->dynamicCall("Select(void)");
        bookmark_End_Time->querySubObject("Range")->setProperty("Text",End_Time[i]);
        }

        QAxObject*bookmark_Major=document->querySubObject("Bookmarks(QString)","Major");
        if(!bookmark_Major->isNull()){
        bookmark_Major->dynamicCall("Select(void)");
        bookmark_Major->querySubObject("Range")->setProperty("Text",Major[i]);
        }

        QAxObject*bookmark_Minor=document->querySubObject("Bookmarks(QString)","Minor");
        if(!bookmark_Minor->isNull()){
        bookmark_Minor->dynamicCall("Select(void)");
        bookmark_Minor->querySubObject("Range")->setProperty("Text",Minor[i]);
        }

        // 将文件另存为docbyqt.doc,关闭工作文档，退出应用程序
        document->dynamicCall("SaveAs (const QString&)", QString("C:/Users/Administrator/Desktop/封面/"+QString::number(i+1)+"-"+Name_Class[i]+".docx"));
        document->dynamicCall("Close (boolean)", false);
        //word->dynamicCall("Quit()");
        emit resultReady(i);
     }
}

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
    pWorkBooks->dynamicCall("Open (const QString&)", execl_Name);//打开指定文件
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
        if(End_Row!=-1){
            if(intRow>End_Row)
                intRow=End_Row;
        }
       // int intCol = columns->property("Count").toInt();  // 列数

        Cell_Data.clear();
        Cell_Name.clear();
        Bookmarks_Data.clear();
        if(allRead){
            for(int k=0;k<Cells.name.length();k++){
                Cell_Data.append(QStringList{});
                Bookmarks_Data.append(Bookmarks.name[k]);
                Cell_Name.append(Cells.name[k]);
            }
        }else{
            for(int k=0;k<Cells.name.length();k++){
                if(Cells.state[k]==true){
                    Cell_Data.append(QStringList{});
                    Bookmarks_Data.append(Bookmarks.name[k]);
                    Cell_Name.append(Cells.name[k]);
                }
            }
        }
        //读方式
        for(int i=Begin_Row;i<=intRow-Begin_Row+1;i++){
            for(int j=0;j<Cell_Data.length();j++){
                QString X = Cell_Name[j] + QString::number(i); //设置要操作的单元格，X1
                QAxObject* cellX = pWorkSheet->querySubObject("Range(QVariant, QVariant)", X); //获取单元格
                Cell_Data[j].append(cellX->dynamicCall("Value2()").toString());
            }
        }
    }
    pWorkBook->dynamicCall("Close(Boolean)", false);//打开指定文件
    excel.dynamicCall( "Quit(void)" );
   // delete excel;
}

void WorkerThread::word_Gain()
{
    for(int i=Begin_Row;i<=intRow-Begin_Row+1;i++){
        //在子线程中不能打开窗口，只能在主GUI线程打开，故而改用下面的代码
        QAxObject word("Word.Application"); //加载Word驱动
        word.setProperty("Visible", false); //不显示Word界面，如果为true会看到启动的Word界面
        QAxObject* documents = word.querySubObject("Documents");
        documents->dynamicCall("Add(QString)",word_Name);//打开指定文件
        QAxObject *document=word.querySubObject("ActiveDocument");

        for(int j=0;j<Bookmarks_Data.length();j++){
            // 获得标签
            QAxObject*bookmark_Name=document->querySubObject("Bookmarks(QString)",Bookmarks.name[j]);
            // 选中标签，将字符插入到标签位置
            if(!bookmark_Name->isNull()){
                bookmark_Name->dynamicCall("Select(void)");
                bookmark_Name->querySubObject("Range")->setProperty("Text",Cell_Data[j].at(i-1));
            }
        }
        // 将文件另存为docbyqt.doc,关闭工作文档，退出应用程序
        QString Name;
       // for(int t=0;t<Cell_Name.length();t++){
        Name.append(Cell_Data[0].at(i-1)+".docx");
       // }

       // Name= Name.left(Name.length() - 1).append(".docx");
        document->dynamicCall("SaveAs (const QString&)",new_Route+Name);
        document->dynamicCall("Close (boolean)", false);
        word.dynamicCall("Quit()");
        emit resultReady(i,Name);
     }
}

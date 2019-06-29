#include "setpath.h"
#include "ui_setpath.h"

SetPath::SetPath(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetPath)
{
    ui->setupUi(this);
    InitStyle();
    model = new QStringListModel(this);
    ui->fileList->setModel(model);
    QList<QStorageInfo> list = QStorageInfo::mountedVolumes();
    for(QStorageInfo& si : list)
    {
        ui->comboBox->addItem(si.rootPath());
    }



    ui->currDir->setText(Path);
    QDir dir(Path);
    showFiles(dir);

    connect(ui->currDir, SIGNAL(returnPressed()),this, SLOT(showFiles()));

    ui->fileList->textElideMode();
    connect(ui->fileList,SIGNAL(doubleClicked(const QModelIndex &)),
            this, SLOT(showDir(const QModelIndex &)));

     Path=dir.absolutePath()+"/";
     temPath=Path;
}

SetPath::~SetPath()
{
    delete ui;
}

void SetPath::InitStyle()  //窗口栏设置
{
   //设置窗体标题栏隐藏
   this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
   location = this->geometry();
   max = false;
   mousePressed = false;
   //安装事件监听器,让标题栏识别鼠标双击
   ui->lab_Title->installEventFilter(this);

   IconHelper::Instance()->SetIcon(ui->btnMenu_Close, QChar(0xf00d), 10);//QChar决定图案
   IconHelper::Instance()->SetIcon(ui->btnMenu_Max, QChar(0xf096), 10);
   IconHelper::Instance()->SetIcon(ui->btnMenu_Min, QChar(0xf068), 10);
   IconHelper::Instance()->SetIcon(ui->lab_Ico, QChar(0x2338), 12);

   IconHelper::Instance()->SetIcon(ui->reloadButton, QChar(0x2B94), 14);
   IconHelper::Instance()->SetIcon(ui->saveButton, QChar(0x2714), 10);
   IconHelper::Instance()->SetIcon(ui->closeButton, QChar(0x2718), 10);

   IconHelper::Instance()->SetIcon(ui->newButton, QChar(0x25A4), 15);
   ui->newButton->setToolTip("新建文件夹");
   //  SetIcon(ui->addButton, ":/qss/psblack/branch_open.png","添加图表");
   //  SetIcon(ui->deleteButton, ":/qss/psblack/branch_close.png","删除图表");
   //  SetIcon(ui->clearButton, ":/image/flash.png","清空图表");
   //  SetIcon(ui->variaButton, ":/qss/psblack/branch_open.png","添加曲线");
   //  SetIcon(ui->dele_variaButton, ":/qss/psblack/branch_close.png","删除曲线");
   //  SetIcon(ui->clearVButton, ":/image/flash.png","清空曲线");

   //widget_title的界面黑色是专门在qss文件里写的
}

/**************************************************************************
    * 界面窗口操作
    */
bool SetPath::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        this->on_btnMenu_Max_clicked();
        return true;
    }
    return QObject::eventFilter(obj, event);
}

void SetPath::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton) && !max) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void SetPath::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void SetPath::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void SetPath::on_btnMenu_Close_clicked()
{
    //qApp->exit();
    hide();
}

void SetPath::on_btnMenu_Max_clicked()
{
    if (max) {
        this->setGeometry(location);
        IconHelper::Instance()->SetIcon(ui->btnMenu_Max, QChar(0xf096), 10);
        ui->btnMenu_Max->setToolTip("最大化");
    } else {
        location = this->geometry();
        this->setGeometry(qApp->desktop()->availableGeometry());
        IconHelper::Instance()->SetIcon(ui->btnMenu_Max, QChar(0xf079), 10);
        ui->btnMenu_Max->setToolTip("还原");
    }
    max = !max;
}

void SetPath::on_btnMenu_Min_clicked()
{
    this->showMinimized();
}






void SetPath::showFiles()
{
    QDir dir(ui->currDir->text());
    showFiles(dir);
}

void SetPath::showFiles(QDir dir)  //除初始化后的路径及文件显示
{
    QStringList strings;
    strings << "*";
    //strings << "*.hts"<<"*.mp3" ;
    QFileInfoList list = dir.entryInfoList(strings,   //文件名称过滤器，"*", "*.tar.gz"
                         QDir::Dirs,  //文件属性过滤器，目录，文件，读写
                         QDir::Type  //排序方式，名称，修改时间，大小，目录最后
                         //QDir::DirsFirst  //排序方式，名称，修改时间，大小，目录优先
                         );
    showFileInfoList(list); //列表信息显示
}

//显示文件信息列表
void SetPath::showFileInfoList(QFileInfoList list)
{
    //清空前面留下的数据
    int i=model->stringList().length();
    for(;i>0;i--){
        model->removeRows(i-1, 1);
    }

    int count =0;
      for(int i=0; i<list.count(); i++)
      {
           QFileInfo tmpFileInfo = list.at(i);  //文件列的第i个
           if((tmpFileInfo.isDir()))  //判断是否是路径    路径的名称就是一个路径
           {
               QString fileName = tmpFileInfo.fileName();  //返回文件名称
               if(fileName==".")
                   continue;
               model->insertRows(count, 1);
               QModelIndex index = model->index(count); //图表下标
               model->setData(index, fileName);
               count++;
           }
      }
}


void SetPath::showDir(const QModelIndex &index) //双击文件或路径
{
   QString str = model->stringList().at(index.row()); //得到所双击的名称
   QDir dir;
   dir.setPath(ui->currDir->text()); //设置路径,文件所在文件夹

   dir.cd(str); //切换到原路径下双击的文件夹
   temPath=dir.absolutePath()+"/";
   ui->currDir->setText(temPath); //现在的决定路径
   showFiles(dir);
}

void SetPath::on_reloadButton_clicked()
{
    showFiles();
}

void SetPath::on_saveButton_clicked()
{
    Path = temPath;
    ui->currDir->setText(Path);
    showFiles();
 //目标程序里所有内嵌的资源文件都是只读的
    hide();
}

void SetPath::on_closeButton_clicked()
{
    ui->currDir->setText(Path);
    showFiles();
    hide();
}

void SetPath::on_comboBox_currentTextChanged(const QString &arg1)
{
    temPath=arg1;
    ui->currDir->setText(arg1);
    showFiles();
}


void SetPath::on_newButton_clicked()
{
    int count = model->stringList().length();
    model->insertRows(count, 1);
    QModelIndex index = model->index(count); //图表下标
    model->setData(index, "");
    isCreatDir=true;
    ui->fileList->edit(index);
}

void SetPath::createDir()
{
    QDir *temp = new QDir;
    bool exist = temp->exists(name);
    if(!exist){
       temp->mkdir(name);
    }
}

void SetPath::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Enter|| event->key() == Qt::Key_Return)
    {                  //小键盘                            //大键盘
        if(isCreatDir){
              name=temPath+model->stringList().back();
              createDir();
              isCreatDir=false;
        }
    }

}

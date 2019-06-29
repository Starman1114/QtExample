#include "setpath.h"
#include "ui_setpath.h"

SetPath::SetPath(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetPath)
{
    ui->setupUi(this);
    model = new QStringListModel(this);
    ui->fileList->setModel(model);
    QList<QStorageInfo> list = QStorageInfo::mountedVolumes();
    for(QStorageInfo& si : list)
    {
        ui->comboBox->addItem(si.rootPath());
    }



    SetIcon(ui->reloadButton, ":/image/reload.png");
    SetIcon(ui->saveButton, ":/image/btn_ok.png");
    SetIcon(ui->closeButton, ":/image/btn_close.png");

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

void SetPath::SetIcon(QPushButton *btn, QString path)
{
    QIcon re(path);
    btn->setFixedSize(20,20);
    btn->setIcon(re);
    btn->setIconSize(QSize(btn->width(),btn->height()));
    btn->setFlat(false);
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

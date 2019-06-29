#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wt = new WorkerThread(this);
    connect(wt,SIGNAL(OK_execl()),this,SLOT(getExecl()));
    connect(wt,SIGNAL(resultReady(int,QString)),this,SLOT(changeList(int,QString)));
    connect(wt,SIGNAL(OK_word()),this,SLOT(getWord()));
    model = new QStringListModel(this);
    ui->fileList->setModel(model);
    ui->readButton->setDisabled(true);
    ui->createButton->setDisabled(true);

    // 设置表头
    excelModel = new QStandardItemModel();
    excelModel->setHorizontalHeaderItem(0, new QStandardItem(tr("Excel")));
    excelModel->setHorizontalHeaderItem(1, new QStandardItem(tr("路径")));
    excelModel->setHorizontalHeaderItem(2, new QStandardItem(tr("起始行")));
    excelModel->setHorizontalHeaderItem(3, new QStandardItem(tr("终止行")));
    ui->excelTable->setModel(excelModel);
    //删除按钮
    QAction *deleteAction = new QAction(tr("删除"), ui->excelTable);
    connect(deleteAction, &QAction::triggered, this, &MainWindow::delete_Excel);
    ui->excelTable->addAction(deleteAction);
    // 打开右键菜单属性
    //属性打开后，Signal才会开始发送customContextMenuRequested
    ui->excelTable->setContextMenuPolicy(Qt::ActionsContextMenu);//由Action定义菜单  这样右键列表里每一个都会弹出action菜单

    connect(excelModel, SIGNAL(itemChanged(QStandardItem *)), this, SLOT(check_State_Excel(QStandardItem *)));

    Cells.name=QStringList{"A","A","B","B"};
    Bookmarks.name=QStringList{"cName1","cName2","eName1","eName2"};

    connect(ui->fileList,SIGNAL(doubleClicked(const QModelIndex &)),
            this, SLOT(OpenWord(const QModelIndex &)));
    ui->fileList->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeList(int i,QString name){
    int count = model->stringList().length();
    model->insertRows(count, 1);
    QModelIndex index = model->index(count); //图表下标
    model->setData(index, name);
}

void MainWindow::getWord()
{
    ui->statusBar->showMessage("运行完毕");
    ui->RouteButton->setEnabled(true);
    ui->RouteEdit->setEnabled(true);
}

void MainWindow::on_wordButton_clicked()
{
    QString N = QFileDialog::getOpenFileName(NULL,"选择word文件",Path,"*.docx *.doc");
    if(N.isEmpty())
        return;
    word_Name = N;
    word_Read=true;

    new_Route.clear();
    QStringList Route =  word_Name.split(QRegExp("[/]"));
    for(int i=0;i<Route.length()-1;i++){
        new_Route.append(Route[i]+"/");
    }
}


void MainWindow::on_execlButton_clicked()
{
    QString N = QFileDialog::getOpenFileName(NULL,"选择excel文件",Path,"*.xlsx");
    if(N.isEmpty())
        return;
    execl_Name = N;
    QStringList Name =  execl_Name.split(QRegExp("[/]"));
    QStandardItem* itemProject = new QStandardItem(QIcon(QStringLiteral(":/image/excel_Image.jpg")),Name.last());
    itemProject->setCheckable(true);
    itemProject->setCheckState(Qt::Unchecked);
    itemProject->setEditable(false);
    execlState.append(0);
    excelModel->appendRow(itemProject);
    excelModel->setItem(excelModel->indexFromItem(itemProject).row(),1,new QStandardItem(execl_Name));
    excelModel->setItem(excelModel->indexFromItem(itemProject).row(),2,new QStandardItem("1"));
    excelModel->item(excelModel->indexFromItem(itemProject).row(),2)->setTextAlignment(Qt::AlignCenter);
    excelModel->setItem(excelModel->indexFromItem(itemProject).row(),3,new QStandardItem("-1"));
    excelModel->item(excelModel->indexFromItem(itemProject).row(),3)->setTextAlignment(Qt::AlignCenter);
    excelModel->item(excelModel->indexFromItem(itemProject).row(),0)->setCheckState(Qt::Checked);
}

void MainWindow::check_State_Excel(QStandardItem *item)
{
    if(item->column()==0){
        if(item->isCheckable()){
            if(item->checkState()==Qt::Checked){
                if(preCheck_Index!=-1&&preCheck_Index!=item->row()){
                    excelModel->item(preCheck_Index,0)->setCheckState(Qt::Unchecked);
                }
                preCheck_Index=item->row();
                execl_Name =excelModel->item(preCheck_Index,1)->text();
                Begin_Row=excelModel->item(preCheck_Index,2)->text().toInt();
                if(excelModel->item(preCheck_Index,3)->text().toInt()!=-1)
                    End_Row=excelModel->item(preCheck_Index,3)->text().toInt();
                execl_Read=true;
            }else{
                execl_Read=false;
            }

        }
    }else{
        if(preCheck_Index!=-1){
            Begin_Row=excelModel->item(preCheck_Index,2)->text().toInt();
            End_Row=excelModel->item(preCheck_Index,3)->text().toInt();
        }

    }
}

void MainWindow::delete_Excel()
{
    excelModel->removeRow(ui->excelTable->currentIndex().row());
}



void MainWindow::getExecl()
{
    ui->createButton->setEnabled(true);
    ui->statusBar->showMessage(QString("成功获取列表信息,总行数：%1").arg(QString::number(intRow-Begin_Row+1)));

}

void MainWindow::on_readButton_clicked()
{
    if(execl_Read){
        ui->statusBar->showMessage("正在获取列表信息......");
        current_STATE=EXECL_START;
        wt->start();
    }else{
        ui->statusBar->showMessage("未选择execl文件");
    }

}

void MainWindow::on_createButton_clicked()
{
    if(word_Read){
        //清空前面留下的数据
        int i=model->stringList().length();
        for(;i>0;i--){
            model->removeRows(i-1, 1);
        }
        ui->statusBar->showMessage("正在生成word文件......");
        current_STATE=WORD_START;
        ui->RouteButton->setDisabled(true);
        ui->RouteEdit->setDisabled(true);
        wt->start();
    }else{
        ui->statusBar->showMessage("未选择word模板");
    }

}

void MainWindow::on_SetButton_clicked()
{
    ChoosenDialog dialog(this);

    dialog.getData(Cells.name,Bookmarks.name);
    if (dialog.exec() != QDialog::Accepted) //如果不是accepted，则返回
        return;

    Cells.name=dialog.Cells;
    for(int i=0; i < Cells.name.length(); i++){
        Cells.state.append(false);
    }
    Bookmarks.name=dialog.Bookmarks;
    ui->unitsWidget->clear();
    addCheckbox(ui->unitsWidget,"* -- 全选",true);
    allRead=true;
    for (int i = 0; i < Cells.name.length(); ++i) {
        QString checkText = QString("%1 -- %2").arg(Cells.name[i]).arg(Bookmarks.name[i]);
        addCheckbox(ui->unitsWidget,checkText,false);
    }
    ui->readButton->setEnabled(true);
}

//添加checkbox到field列表中
void MainWindow::addCheckbox(QListWidget *widget,QString name,bool checked){
    QListWidgetItem * item = new QListWidgetItem ();
    QCheckBox * box = new QCheckBox (name);
    box->setCheckable (true);
    box->setChecked(checked);
    CheckList.append(box);
    connect(CheckList.back(), SIGNAL(stateChanged(int)), this, SLOT(change_Check_State(int)));
    widget->addItem( item );
    widget->setItemWidget( item,box );
}

void MainWindow::change_Check_State(int state){
   for(int i =0;i<Cells.state.length();i++){
       if(CheckList[i+1]->isChecked()!=Cells.state[i]){
           Cells.state[i]=state;
       }
   }
   allRead= CheckList[0]->isChecked();
}


void MainWindow::OpenWord(const QModelIndex &index) //双击文件或路径
{
   QString route = new_Route + model->stringList().at(index.row()); //得到所双击的名称
   QAxObject word("Word.Application"); //加载Word驱动
   word.setProperty("Visible", true); //不显示Word界面，如果为true会看到启动的Word界面
   QAxObject* documents = word.querySubObject("Documents");
   documents->dynamicCall("Add(QString)",route);//打开指定文件
}

void MainWindow::on_RouteButton_clicked()
{
    SetPath dialog(this);
    if (dialog.exec() != QDialog::Accepted) //如果不是accepted，则返回
        return;
    new_Route=Path;
    ui->RouteEdit->setText(new_Route);
}


void MainWindow::on_RouteEdit_textChanged(const QString &arg1)
{
    new_Route=arg1;
}

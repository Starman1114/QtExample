#include "function.h"
#include "ui_function.h"

Function::Function(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Function)
{
    ui->setupUi(this);
    InitStyle();


    setWindowTitle("图表设置");
    model = new QStringListModel(this);
    ui->FunctionView->setModel(model);
    ui->chooseView->setModel(model);
  //  ui->FunctionView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    connect(ui->FunctionView, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(chartName(const QModelIndex &)));
    connect(ui->FunctionView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(changeShow(const QModelIndex &)));


    F = new FunctionData();
    ui->variaButton->setDisabled(true);
    ui->dele_variaButton->setDisabled(true);

    m = new MathW();
    connect(m, SIGNAL(resultReady(QStringList)), this, SLOT(ChangeMath(QStringList)));

    StartShow();

}

Function::~Function()
{
    delete ui;
}

void Function::on_addButton_clicked()
{
    bool isOK;
    QString text = QInputDialog::getText(this, "图表增加",
                                         "输入新的图表类名:",
                                         QLineEdit::Normal,
                                         "",
                                         &isOK);
    if (isOK) {
        int row = fun.N;
        model->insertRows(row, 1);
        QModelIndex index = model->index(row);
        model->setData(index, text);
        ui->FunctionView->setCurrentIndex(index);
       // ui->FunctionView->edit(index);
        QCheckBox *b = new QCheckBox();
        CheckList.append(b);
        connect(CheckList.back(), SIGNAL(stateChanged(int)), this, SLOT(onStateChanged(int)));
        ui->chooseView->setIndexWidget(index,CheckList.back());

        send_Signal.append(false);

        fun.name.append(model->stringList()[fun.N]);
        func ff;
        fun.f.append(ff);

        function_Widget_Add(ui->functionWidget,fun,fun.N);

        ui->functionWidget->setCurrentIndex(fun.N);

        fun.N++;

        if(fun.N>0){
            ui->variaButton->setEnabled(true);
            ui->dele_variaButton->setEnabled(true);
        }
    }
}

void Function::function_Widget_Add(QTabWidget *tab, FunctionD fun,int row)
{
    //新建页面的部件
    QWidget *widget = new QWidget();
    QHBoxLayout *hLayout = new QHBoxLayout();
    QListView *t = new QListView();
    //t->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
  //  t->setFixedWidth(70);
    fl.append(t);

    QListView *tmax = new QListView();
   // tmax->setFixedWidth(45);
    flmax.append(tmax);

    QListView *tmin = new QListView();
 //   tmin->setFixedWidth(45);
    flmin.append(tmin);

    QListView *tunits = new QListView();
   // tunits->setFixedWidth(30);
    flunits.append(tunits);

    QListView *tc = new QListView();
  //  tc->setFixedWidth(70);
    flc.append(tc);

    QListView *ts = new QListView();
  //  ts->setFixedWidth(ui->functionWidget->width()-t->width()-tc->width()-tmax->width()-tmin->width()-tunits->width());
   // ts->setFixedWidth(90);
    ts->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    fls.append(ts);

    connect(fl[row], SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(variaName(const QModelIndex &)));
    connect(fls[row], SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(mathChange(const QModelIndex &)));
    connect(flmax[row], SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(maxChange(const QModelIndex &)));
    connect(flmin[row], SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(minChange(const QModelIndex &)));
    connect(flunits[row], SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(unitsChange(const QModelIndex &)));

    QStringListModel *m = new QStringListModel();
    QStringListModel *sm = new QStringListModel();
    QStringListModel *maxm = new QStringListModel();
    QStringListModel *minm = new QStringListModel();
    QStringListModel *unitsm = new QStringListModel();
  //  QStringListModel *cm = new QStringListModel();
    flm.append(m);
    flsm.append(sm);
    flmaxm.append(maxm);
    flminm.append(minm);
    flunitsm.append(unitsm);
    flcm.append(m);
    fl[row]->setModel(flm[row]);
    fls[row]->setModel(flsm[row]);
    flmax[row]->setModel(flmaxm[row]);
    flmin[row]->setModel(flminm[row]);
    flunits[row]->setModel(flunitsm[row]);
    flc[row]->setModel(flcm[row]);
    hLayout->addWidget(fl[row]);
    hLayout->addWidget(fls[row]);
    hLayout->addWidget(flmax[row]);
    hLayout->addWidget(flmin[row]);
    hLayout->addWidget(flunits[row]);
    hLayout->addWidget(flc[row]);
    widget->setLayout(hLayout);

    tab->addTab(widget,fun.name[row]);

}

void Function::chartName(const QModelIndex &index)
{
        type=1;
        ind = index;
}

void Function::InitStyle()  //窗口栏设置
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
   IconHelper::Instance()->SetIcon(ui->lab_Ico, QChar(0x2328), 12);

   IconHelper::Instance()->SetIcon(ui->addButton, QChar(0x2795), 13);
   IconHelper::Instance()->SetIcon(ui->deleteButton, QChar(0x2796), 13);
   IconHelper::Instance()->SetIcon(ui->clearButton, QChar(0x2B94), 13);
   IconHelper::Instance()->SetIcon(ui->variaButton, QChar(0x2795), 13);
   IconHelper::Instance()->SetIcon(ui->dele_variaButton, QChar(0x2796), 13);
   IconHelper::Instance()->SetIcon(ui->clearVButton, QChar(0x2B94), 13);
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
bool Function::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        this->on_btnMenu_Max_clicked();
        return true;
    }
    return QObject::eventFilter(obj, event);
}

void Function::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton) && !max) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void Function::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void Function::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void Function::on_btnMenu_Close_clicked()
{
    //qApp->exit();
    hide();
}

void Function::on_btnMenu_Max_clicked()
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

void Function::on_btnMenu_Min_clicked()
{
    this->showMinimized();
}






void Function::on_deleteButton_clicked()
{
        if (model->rowCount() > 0) {
                int row = ui->FunctionView->currentIndex().row();
                model->removeRows(row,1);
                send_Signal.removeAt(row);
                CheckList.removeAt(row);
                fun.name.removeAt(row);

                fl.removeAt(row);
                fls.removeAt(row);
                flmax.removeAt(row);
                flmin.removeAt(row);
                flunits.removeAt(row);
                flc.removeAt(row);
                flm.removeAt(row);
                flsm.removeAt(row);
                flmaxm.removeAt(row);
                flminm.removeAt(row);
                flunitsm.removeAt(row);
                flcm.removeAt(row);

                for(int i=ColorNum.length();i>0;i--){
                    if(ColorNum[i-1].fn==row){
                        ColorNum.removeAt(i-1);
                        ColorList.removeAt(i-1);
                    }
                }


                ui->functionWidget->removeTab(row);
                fun.f.removeAt(row);
                fun.N--;
            }
        if(fun.N==0){
            ui->variaButton->setDisabled(true);
            ui->dele_variaButton->setDisabled(true);
        }

}


void Function::on_clearButton_clicked()
{
    if (QMessageBox::Yes == QMessageBox::question(this,
                                                  tr("清空图表数据"),
                                                  tr("确定清空?"),
                                                  QMessageBox::Yes | QMessageBox::No,
                                                  QMessageBox::Yes)) {
    Clear();

    }
}

void Function::Clear()
{
    for(int i=fun.N;i>0;i--){
        model->removeRows(i-1, 1);
        ui->functionWidget->removeTab(i-1);
    }
    flm.clear();
    flsm.clear();
    flmaxm.clear();
    flminm.clear();
    flunitsm.clear();
    flcm.clear();
    fl.clear();
    fls.clear();
    flmax.clear();
    flmin.clear();
    flunits.clear();
    flc.clear();
    F->clear(&fun);
    CheckList.clear();
    send_Signal.clear();
    ColorList.clear();
    ColorNum.clear();
}


void Function::on_variaButton_clicked()  //添加变量
{
    bool isOK;
    int fn=ui->functionWidget->currentIndex();//图表下标
    QString text = QInputDialog::getText(this, "变量增加",
                                        "输入新的变量名:",
                                        QLineEdit::Normal,
                                        "",
                                        &isOK);
    if (isOK) {
        int row = fun.f[fn].n;//变量数
        flm[fn]->insertRows(row, 1);
        QModelIndex index = flm[fn]->index(row);
        flm[fn]->setData(index, text);
        fl[fn]->setCurrentIndex(index);

        flsm[fn]->insertRows(row, 1);
        flsm[fn]->setData(index, "");
        fls[fn]->setCurrentIndex(index);

        flmaxm[fn]->insertRows(row, 1);
        flmaxm[fn]->setData(index, "100");
        flmax[fn]->setCurrentIndex(index);

        flminm[fn]->insertRows(row, 1);
        flminm[fn]->setData(index, "0");
        flmin[fn]->setCurrentIndex(index);

        flunitsm[fn]->insertRows(row, 1);
        flunitsm[fn]->setData(index, "");
        flunits[fn]->setCurrentIndex(index);

        QComboBox *color = new QComboBox();

        color->addItems(cc);
        color->setCurrentIndex(7);
        connect(color, SIGNAL(activated(int)), this, SLOT(colorChange(int)));
        ColorList.append(color);
        ColorIndex cn;
        cn.fn=fn;
        cn.row=row;
        cn.index=7;
        ColorNum.append(cn);
        flc[fn]->setIndexWidget(index,ColorList.back());


        fun.f[fn].variaName.append(flm[fn]->stringList()[fun.f[fn].n]);//变量名
        fun.f[fn].s.append("");//公式初始化
        fun.f[fn].ymax.append("100");
        fun.f[fn].ymin.append("0");
        fun.f[fn].units.append("");
        fun.f[fn].c.append("7");//颜色初始化
        fun.f[fn].n++;
    }
}


//颜色修改
void Function::colorChange(int index)
{
     ColorIndex cn;
     for(int i =0;i<ColorNum.length();i++){
         if(ColorList[i]->currentIndex()!=ColorNum[i].index){
             ColorNum[i].index=ColorList[i]->currentIndex();
             cn=ColorNum[i];
         }
     }
    // fun.f[cn.fn].c[cn.row]=cc[index];
     fun.f[cn.fn].c[cn.row]=QString::number(index);
}



void Function::on_dele_variaButton_clicked()
{
    int fn=ui->functionWidget->currentIndex();//图表下标

    if (flm[fn]->rowCount() > 0) {
            int fln=fl[fn]->currentIndex().row();//变量下标
            flm[fn]->removeRows(fln,1);
            flsm[fn]->removeRows(fln,1);
            flmaxm[fn]->removeRows(fln,1);
            flminm[fn]->removeRows(fln,1);
            flunitsm[fn]->removeRows(fln,1);
            flcm[fn]->removeRows(fln,1);

            fun.f[fn].variaName.removeAt(fln);
            fun.f[fn].s.removeAt(fln);
            fun.f[fn].ymax.removeAt(fln);
            fun.f[fn].ymin.removeAt(fln);
            fun.f[fn].units.removeAt(fln);
            fun.f[fn].c.removeAt(fln);

            for(int i=ColorNum.length();i>0;i--){
                if(ColorNum[i-1].fn==fn&&ColorNum[i-1].row==fln){
                     ColorNum.removeAt(i-1);
                     ColorList.removeAt(i-1);
                }
            }


            fun.f[fn].n--;
    }
}


void Function::on_clearVButton_clicked()
{
    if (QMessageBox::Yes == QMessageBox::question(this,
                                                  tr("清空曲线数据"),
                                                  tr("确定清空?"),
                                                  QMessageBox::Yes | QMessageBox::No,
                                                  QMessageBox::Yes)) {
    int fn=ui->functionWidget->currentIndex();//图表下标
    for(int fln=fun.f[fn].n-1;fln>-1;fln--){
        flm[fn]->removeRows(fln,1);
        flsm[fn]->removeRows(fln,1);
        flmaxm[fn]->removeRows(fln,1);
        flminm[fn]->removeRows(fln,1);
        flunitsm[fn]->removeRows(fln,1);
        flcm[fn]->removeRows(fln,1);

        fun.f[fn].variaName.removeAt(fln);
        fun.f[fn].s.removeAt(fln);
        fun.f[fn].ymax.removeAt(fln);
        fun.f[fn].ymin.removeAt(fln);
        fun.f[fn].units.removeAt(fln);
        fun.f[fn].c.removeAt(fln);
    }
    F->clearf(&(fun.f[fn]));
}
}


void Function::functionShow()
{
    Clear();
    QString file_name = QFileDialog::getOpenFileName(NULL,"标题",".","*.txt"); //文件绝对路径
    QFile file(file_name);
     if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
         return;
    QTextStream in(&file);
    ShowAction(&in);
    file.close();
}

void Function::functionRecord()
{
    QString file_name = QFileDialog::getSaveFileName(NULL,"标题",".","*.txt");
    QFile file(file_name);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return;
      }
    QTextStream out(&file);
     out << "chartNumber;"<< QString::number(fun.N) << ";"
         << "\n";
    for(int i=0;i<fun.N;i++){
        out << fun.name[i] << ";"
            << fun.f[i].n << ";"
            << "\n";
        for(int j=0;j<fun.f[i].n;j++){
            out << fun.f[i].variaName[j] << ";"
                << fun.f[i].s[j] << ";"
                << fun.f[i].ymax[j] << ";"
                << fun.f[i].ymin[j] << ";"
                << fun.f[i].units[j] << ";"
                << fun.f[i].c[j] << ";"
                << "\n";
        }
    }
    file.close();
}

void Function::on_SaveButton_clicked()
{
    functionRecord();
}

void Function::on_openButton_clicked()
{
    functionShow();
}




void Function::keyReleaseEvent(QKeyEvent  *event)
{
    if (event->key() == Qt::Key_Enter|| event->key() == Qt::Key_Return)
    {                  //小键盘                            //大键盘
        //指向你想要触发的代码
        int fn=ui->functionWidget->currentIndex();//图表下标
        switch(type){
        case 1:
            if (model->rowCount() > 0) {
                int row = ind.row();
                fun.name[row]=model->stringList()[row];
                ui->functionWidget->setTabText(row,fun.name[row]);
                type=0;
            }
            break;
         case 2:
            if (flm[fn]->rowCount() > 0) {
                int row = ind.row();//变量下标
                fun.f[fn].variaName[row]=flm[fn]->stringList()[row];
                type=0;
            }
            break;
       case 3:
          if (flmaxm[fn]->rowCount() > 0) {
              int row = ind.row();//变量下标
              fun.f[fn].ymax[row]=flmaxm[fn]->stringList()[row];
              type=0;
          }
          break;
       case 4:
          if (flminm[fn]->rowCount() > 0) {
              int row = ind.row();//变量下标
              fun.f[fn].ymin[row]=flminm[fn]->stringList()[row];
              type=0;
          }
          break;
       case 5:
          if (flunitsm[fn]->rowCount() > 0) {
              int row = ind.row();//变量下标
              fun.f[fn].units[row]=flunitsm[fn]->stringList()[row];
              type=0;
          }
          break;
        }

    }


}


void Function::variaName(const QModelIndex &index)
{
    type=2;
    ind = index;
}

void Function::mathChange(const QModelIndex &index)
{
    int fn=ui->functionWidget->currentIndex();//图表下标
    ind = index;
    int row = ind.row();//变量下标
    QStringList fo =  fun.f[fn].s[row].split(QRegExp("[|]"));
    fo.pop_back();//最后一位为空
    m->show_MATH(fo);
    m->show();
}


void Function::ChangeMath(QStringList formula)
{
    QString show;
    QString save;

    for(int i=0;i<formula.length();i++){
        show.append(formula[i]);
        save.append(formula[i]+"|");
    }

    int fn=ui->functionWidget->currentIndex();//图表下标
    if (flsm[fn]->rowCount() > 0) {
        int row = ind.row();//变量下标
        fun.f[fn].s[row]=save;
        flsm[fn]->setData(ind,show);
    }
}




void Function::on_ChartShowButton_clicked()
{
    F->clear(&fun_Send);
    for(int i=0;i<send_Signal.length();i++){
             if(send_Signal[i]){
                fun_Send.name.append(fun.name[i]);
                fun_Send.f.append(fun.f[i]);
                fun_Send.N++;
             }
         }
    hide();
    emit ChartShowSend(fun_Send);
}

void Function::changeShow(const QModelIndex &index)
{
    int row = index.row();
    ui->functionWidget->setCurrentIndex(row);
}

void Function::maxChange(const QModelIndex &index)
{
    type=3;
    ind = index;
}

void Function::minChange(const QModelIndex &index)
{
    type=4;
    ind = index;
}

void Function::unitsChange(const QModelIndex &index)
{
    type=5;
    ind = index;
}

void Function::onStateChanged(int state)
{
   // int fn=whoChange_state();//选中框下标
   // if (state == Qt::Checked) // "选中"
   //     {
   //         send_Signal[0]=true;
   //     }
   //     else if(state == Qt::Unchecked)// 未选中 - Qt::Unchecked
   //     {
   //         send_Signal[0]=false;
   //     }
    whoChange_state();
}

int Function::whoChange_state()
{
    for(int i =0;i<send_Signal.length();i++){
        if(CheckList[i]->isChecked()!=send_Signal[i]){
            send_Signal[i]=CheckList[i]->isChecked();
            return i;
        }
    }
}

void Function::StartShow()
{
    QString file_name =":/qss/origin.txt"; //文件绝对路径
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    ShowAction(&in);
    file.close();
}

void Function::ShowAction(QTextStream *in)
{
    F->readData(&fun,in);
    ui->chooseChartBox->setChecked(true);
    ifchoose=true;
    //改变图表显示
    for(int i=0;i<fun.N;i++){
        model->insertRows(i, 1);
        QModelIndex index = model->index(i); //图表下标
        model->setData(index, fun.name[i]);
        QCheckBox *b = new QCheckBox();
        b->setChecked(true);
        CheckList.append(b);
        connect(CheckList.back(), SIGNAL(stateChanged(int)), this, SLOT(onStateChanged(int)));
        ui->chooseView->setIndexWidget(index,CheckList.back());

        send_Signal.append(true);

       function_Widget_Add(ui->functionWidget,fun,i);

       if(fun.N>1){
           ui->variaButton->setEnabled(true);
           ui->dele_variaButton->setEnabled(true);
        }
        for(int j=0;j<fun.f[i].n;j++){
             flm[i]->insertRows(j, 1);
             QModelIndex index = flm[i]->index(j);
             flm[i]->setData(index, fun.f[i].variaName[j]);
             fl[i]->setCurrentIndex(index);

             flsm[i]->insertRows(j, 1);
             QString ss;
             QStringList mm =  fun.f[i].s[j].split(QRegExp("[|]"));
             mm.pop_back();//最后一位为空
             for(int k=0;k<mm.length();k++){
                 ss.append(mm[k]);
             }
             flsm[i]->setData(index, ss);
             fls[i]->setCurrentIndex(index);

             flmaxm[i]->insertRows(j, 1);
             flmaxm[i]->setData(index, fun.f[i].ymax[j]);
             flmax[i]->setCurrentIndex(index);

             flminm[i]->insertRows(j, 1);
             flminm[i]->setData(index, fun.f[i].ymin[j]);
             flmin[i]->setCurrentIndex(index);

             flunitsm[i]->insertRows(j, 1);
             flunitsm[i]->setData(index, fun.f[i].units[j]);
             flunits[i]->setCurrentIndex(index);

             QComboBox *color = new QComboBox();
             color->addItems(cc);
            // color->setCurrentIndex(F->findColor(fun.f[i].c[j]));
             color->setCurrentIndex(fun.f[i].c[j].toInt());
             connect(color, SIGNAL(activated(int)), this, SLOT(colorChange(int)));
             ColorList.append(color);
             ColorIndex cn;
             cn.fn=i;
             cn.row=j;
             cn.index=F->findColor(fun.f[i].c[j]);
             ColorNum.append(cn);
             flc[i]->setIndexWidget(index,ColorList.back());
        }
    }
}

void Function::startChartShow()
{
    ui->ChartShowButton->clicked(true);
}


void Function::on_chooseChartBox_clicked()
{
    if(!ifchoose){
        for(int i =0;i<send_Signal.length();i++){
            CheckList[i]->setChecked(true);
            send_Signal[i]=true;
        }
        ifchoose=true;
    }else{
        for(int i =0;i<send_Signal.length();i++){
            CheckList[i]->setChecked(false);
            send_Signal[i]=false;
        }
        ifchoose=false;
    }
}


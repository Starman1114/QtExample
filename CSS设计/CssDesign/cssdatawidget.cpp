#include "cssdatawidget.h"
#include "ui_cssdatawidget.h"

CssDataWidget::CssDataWidget(QWidget *parent,QString path) :
    QWidget(parent),
    DataPath(path),
    ui(new Ui::CssDataWidget)
{
    ui->setupUi(this);
    InitStyle();
}

CssDataWidget::~CssDataWidget()
{
    delete ui;
}

void CssDataWidget::InitStyle()
{
    SetProp_Name(DataPath);
 // FontProperyC.append("常用字体");
 // FontProperyE.append("font-family");
 // FontProperyU.append("");

    ui->tableWidget->setColumnCount(3);//只设置列数，行数动态中增加
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"属性"<<"名称"<<"数值");
    for(int i=0;i<FontProperyE.length();i++){
        AddItemWidget(FontProperyE[i]);
    }

}

void CssDataWidget::AddItemWidget(QString name){
    int RowCont=ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(RowCont);//增加一行
    int DataIndex = getDataIndex(name);
    ui->tableWidget->setItem(RowCont,0,new QTableWidgetItem(FontProperyC[DataIndex]));
    ui->tableWidget->setItem(RowCont,1,new QTableWidgetItem(name));
    QStringList dataList;
    if(FontProperyT[DataIndex].toInt()==0)
        dataList = getDataSource(FontProperyS[DataIndex].toInt());

    QComboBox *comb = new QComboBox();
    QSpinBox *sp = new QSpinBox();
    QLineEdit *le = new QLineEdit();
  // QWidget *wid = new QWidget();
  // QHBoxLayout *vbox = new QHBoxLayout();
    switch(FontProperyT[DataIndex].toInt()){
    case ComboBox:  //      
        comb->addItems(dataList);
        comb->setCurrentIndex(dataList.indexOf(FontProperyOri[DataIndex]));
        DataList.append(FontProperyOri[DataIndex]);
        connect(comb,SIGNAL(currentTextChanged(const QString &)),this,SLOT(DataChange(const QString &)));
        ui->tableWidget->setCellWidget(RowCont,2,comb);
        break;
    case SpinBox:
        sp->setMaximum(999);
        sp->setValue(FontProperyOri[DataIndex].toInt());
        DataList.append(FontProperyOri[DataIndex]);
        connect(sp,SIGNAL(valueChanged(const QString &)),this,SLOT(DataChange(const QString &)));
        ui->tableWidget->setCellWidget(RowCont,2,sp);
        break;
    case LineEdit:
        le->setText(FontProperyOri[DataIndex]);
        DataList.append(FontProperyOri[DataIndex]);
        connect(le,SIGNAL(textEdited(const QString &)),this,SLOT(DataChange(const QString &)));
        ui->tableWidget->setCellWidget(RowCont,2,le);
        break;

  //  case SpinBox:  //
      //  QSpinBox *spin = new QSpinBox();
      //  comb->addItems(dataList);
      //  DataList.append(dataList.at(0));
      //  connect(comb,SIGNAL(currentTextChanged(const QString &)),this,SLOT(DataChange(const QString &)));
      //  ui->tableWidget->setCellWidget(RowCont,2,comb);
  //  break;
    }
}

void CssDataWidget::DataChange(const QString &str)
{
    int index = ui->tableWidget->currentIndex().row();
    DataList[index] = str;
}

void CssDataWidget::SetProp_Name(QString FireName)
{
    QFile file(FireName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
     }
    QTextStream in(&file);
    ChangeSet(&in);
}

void CssDataWidget::ChangeSet(QTextStream *in)
{
    QString line = in->readLine();
    while (!line.isNull()){
        QStringList data =  line.split(QRegExp("[;]"));
        FontProperyC.append(data[0]);
        FontProperyE.append(data[1]);
        FontProperyT.append(data[2]);
        FontProperyS.append(data[3]);
        FontProperyOri.append(data[4]);
        FontProperyU.append(data[5]);

        line = in->readLine();
    }
}

QString CssDataWidget::GetFontData()
{
    QString text;
    for(int i =0; i<FontProperyE.length();i++){
        text.append(FontProperyE[i]+": ");
        text.append(DataList[i]+FontProperyU[i]+";\n");
    }
    return text;
}

int CssDataWidget::getDataIndex(QString name)
{
    for(int i =0;i<FontProperyE.length();i++){
        if(name == FontProperyE[i])
            return i;
    }
    return 0;
}

QStringList CssDataWidget::getDataSource(int s)
{
    QFontDatabase fd;
    switch(s){
    //字体
    case 0:
        return fd.families(); //常用字体
        break;
    case 1: //样式
        return Font_Style;
        break;
    case 2: //修饰
        return Text_Decoration;
        break;
    case 3:
        return Border_Style;
        break;
    }
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

#define space 5
#define mapL 400
#define mapW 200

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    path = new QPainterPath();
    QPixmap icon1(tr("../map/cat.jpg"));
    ui->peopleButton->setIcon(icon1);
    ui->peopleButton->setGeometry(ui->mapBox->x()+space,ui->mapBox->y()+ui->mapBox->height()+space,icon1.width()/2,icon1.height()/2); //位置坐标+尺寸
    //ui->peopleButton->setFixedSize(icon1.size()/2);
    iwidth=icon1.width();
    iheight=icon1.height();
    ui->originEdit->setText(tr("(%1, %2)").arg(getmapX(ui->peopleButton->x())).arg(getmapY(ui->peopleButton->y())));
  //  path->moveTo(getmapX(ui->peopleButton->x()),getmapY(ui->peopleButton->y())); //移动当前点
    pixMap =new QPixmap(mapL, mapW);  //长宽
    pixMap->fill(Qt::white);   //背景填充为红色
    lastPoint.setX(getmapX(ui->peopleButton->x()));
    lastPoint.setY(getmapY(ui->peopleButton->y()));
    endPoint=lastPoint;
    path->moveTo(lastPoint.x(),lastPoint.y());

    ui->saveButton->setGeometry(ui->mapBox->x(),ui->mapBox->y()+ui->mapBox->height()+space+mapW,ui->mapBox->width(),ui->mapBox->height());
    ui->cleanButton->setGeometry(ui->saveButton->x()+ui->saveButton->width()+ui->mapBox->x(),ui->mapBox->y()+ui->mapBox->height()+space+mapW,ui->mapBox->width(),ui->mapBox->height());
    ui->pathBox->setGeometry( ui->cleanButton->x()+ui->cleanButton->width()+ui->mapBox->x(),ui->mapBox->y()+ui->mapBox->height()+space+mapW,ui->mapBox->width(),ui->mapBox->height());


    //临时保存窗口设置
    saveW= new QDialog();
    saveName =new QLineEdit;
    QVBoxLayout *vbox = new QVBoxLayout;
    QHBoxLayout *vbox1 = new QHBoxLayout;
    QLabel *a=new QLabel("Save as: ");

    vbox1->addWidget(a);
    vbox1->addWidget(saveName);

    QHBoxLayout *vbox2 = new QHBoxLayout;
    QPushButton *b=new QPushButton(tr("保存"));
    QPushButton *c=new QPushButton(tr("取消"));
    vbox2->addWidget(b);
    vbox2->addWidget(c);

    vbox->addLayout(vbox1);
    vbox->addLayout(vbox2);
    saveW->setLayout(vbox);
    connect(b, SIGNAL(clicked(bool)), this, SLOT(saveRoute()));
    connect(c, SIGNAL(clicked(bool)), saveW, SLOT(close()));
    
   

}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::getmapX(int x)
{
    int X = x-ui->mapBox->x()+iwidth/4;
    return X;
}

int MainWindow::getmapY(int y)
{
    int Y = y-ui->mapBox->y()-ui->mapBox->height()+iheight/4;
    return Y;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter pp(pixMap);
    QPen pen; //画笔
    //this表明绘图设备就是Widget部件，painter用于后面的绘制
    pen.setColor(QColor(50, 100, 200)); //红、绿、蓝 0-255
    pen.setStyle(Qt::SolidLine); //线条类型 实线
    pen.setCapStyle(Qt::RoundCap); //线条终端 圆
    pen.setJoinStyle(Qt::RoundJoin); //线条连接样式 平滑
    pen.setWidth(3); //线条宽度
    pp.setPen(pen); //添加画笔
    path->lineTo(endPoint.x(), endPoint.y());
    pp.drawPath(*path); //画路径
   // pp.drawLine(lastPoint, endPoint);
    // 让前一个坐标值等于后一个坐标值，
    // 这样就能实现画出连续的线
    QPainter painter(this);
    //lastPoint = endPoint;
    painter.drawPixmap(ui->mapBox->x(), ui->mapBox->y()+ui->mapBox->height()+space+10, *pixMap);

//
//
//
//
//
//
//
//       //   QBrush brush(QColor(0, 255, 0, 125)); //画刷 最后一个参数alpha是设置透明度 0表示完全透明，而255表示完全不透明
//
//        //  painter.setBrush(brush); //添加画刷
//          //painter.drawRect(50, 50, 200, 100); //绘制矩形 其左上角顶点在(50, 50)，宽为200，高为100
//          painter->drawPixmap(ui->mapBox->x(), ui->mapBox->y()+ui->mapBox->height()+space, pixMap);
//
//          //绘图设备--画布


// //
   // QPainterPath path; //路径
  //  path.addEllipse(100, 100, 50, 50); //画椭圆，左上点为100 100 两径为50 50
   // path.lineTo(200, 200); //接着画到200 200
    //path2.addPath(path); //加路径
    //path.moveTo(100, 100); 移动当前点
  //  QPainterPath path; //路径

 // //   painter->drawPath(path); //画路径

    //painter.drawLine(QPointF(0, 0), QPointF(100, 100)); //绘画直线

  //  QPixmap pixCat; //画图
  //  pixCat.load("../map/cat.jpg");
    //将（100，100）设为坐标原点
   // painter.translate(100, 100); //平移坐标系统
    //painter.scale(2, 2); 坐标系统放大2倍
    // painter.save(); //保存坐标系状态
    //painter.restore(); //恢复以前的坐标系状态  就是入栈出栈
    //   painter.drawPixmap(0, 0, 42, 39, pixCat); //左上角和大小
}



void MainWindow::mousePressEvent(QMouseEvent *e)
{
   ui->currentEdit->setText(tr("(%1, %2)").arg(e->x()).arg(e->y()));
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
   int x = ui->peopleButton->x();
   int y = ui->peopleButton->y();
   switch (e->key())
   {
   case Qt::Key_W : ui->peopleButton->move(x, y-10); break;
   case Qt::Key_S : ui->peopleButton->move(x, y+10); break;
   case Qt::Key_A : ui->peopleButton->move(x-10, y); break;
   case Qt::Key_D : ui->peopleButton->move(x+10, y); break;
   }
   ui->currentEdit->setText(tr("(%1, %2)").arg(getmapX(ui->peopleButton->x())).arg(getmapY(ui->peopleButton->y())));
   //path.lineTo(getmapX(ui->peopleButton->x()), getmapY(ui->peopleButton->y()));
   if(e->type()==QEvent::KeyPress){
            endPoint.setX(getmapX(ui->peopleButton->x()));
            endPoint.setY(getmapY(ui->peopleButton->y()));
            update();
   }

}

void MainWindow::on_cleanButton_clicked()
{
    QPixmap *p=new QPixmap(mapL, mapW);
    p->fill(Qt::white);
    pixMap = p;
    QPainterPath *pa = new QPainterPath();
    path =pa;
    path->moveTo(endPoint.x(),endPoint.y());
    update();
}
void MainWindow::on_saveButton_clicked()
{
    saveW->show();
}

void MainWindow::saveRoute()
{
    pixMap->save(saveName->text()+".jpg", "JPG");
    PathList.append(*path);
    Pathname.append(saveName->text());
    PathEnd.append(ui->peopleButton->pos());
    ui->pathBox->clear();
    ui->pathBox->addItems(Pathname);
    saveW->hide();
}


void MainWindow::on_pathBox_activated(int index)
{
    QPixmap *p=new QPixmap(mapL, mapW);
    p->fill(Qt::white);
    pixMap = p;
    path = &PathList[index];
    ui->peopleButton->move(PathEnd[index].x(),PathEnd[index].y());
    lastPoint =PathEnd[index];
    endPoint = PathEnd[index];
    update();
}

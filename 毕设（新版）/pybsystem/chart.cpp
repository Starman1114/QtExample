#include "chart.h"

Chart::Chart()
{

}

void Chart::setUp(QChartView *chartView,
                  QChart *chart,
                  QWidget *graph,
                  func f,
                  QList<QLineSeries*> *m_series,
                  QList<QDateTimeAxis *> *axisX,
                  QList<QValueAxis *> *axisY,
                  int type)
{

    /*设置画笔和画布*/
    chartView = new QChartView();

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(chartView);
    graph->setLayout(vbox);

    chart = chartView->chart();
    chart->legend()->setVisible(true);

    //自定义Chart字体颜色等 Customize chart title
    QFont font;
    font.setPixelSize(18);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::black));

//  chart->createDefaultAxes();  // 基于已添加到图表的 series 来创轴
    (*axisX)[type]->setMax(QDateTime::currentDateTime());
    (*axisX)[type]->setMin(QDateTime::currentDateTime().addMSecs(-timeSpace*maxSize));
  //  axisX->setMinorTickCount(10); //设置小刻度线的数目
    (*axisX)[type]->setTickCount(maxSize/10+1);//设置刻度线的数目
    (*axisX)[type]->setTitleText("t/s"); //设置X坐标名字
   (*axisX)[type]->setFormat("mm:ss.zzz"); //设置刻度的格式

   // axisY[type] = new QValueAxis;
    double max=0;
    double min=0;
    for(int k=0;k<f.n;k++){
        if(f.ymax[k].toDouble()>max)
            max=f.ymax[k].toDouble();
        if(f.ymin[k].toDouble()<min)
            min=f.ymin[k].toDouble();
    }

    (*axisY)[type]->setRange(min, max);
   // (*axisY)[type]->setTitleText(f.units[0]);//此版本Y轴不设文本
   // axisY->setLabelFormat("%.2f");
    (*axisY)[type]->setGridLineVisible(true);

    //自定义XY轴字体 Customize axis label font
    QFont labelsFont;
    labelsFont.setPixelSize(12);
    (*axisX)[type]->setLabelsFont(labelsFont);
    (*axisY)[type]->setLabelsFont(labelsFont);

    //自定义XY轴颜色 Customize axis colors
    QPen axisPen(QRgb(0xFFB400));//黄色
    axisPen.setWidth(2);
    (*axisX)[type]->setLinePen(axisPen);
    (*axisY)[type]->setLinePen(axisPen);

    //自定义XY轴数字颜色
    QBrush axisBrush(Qt::black);
    (*axisX)[type]->setLabelsBrush(axisBrush);
    (*axisY)[type]->setLabelsBrush(axisBrush);
    //自定义XY轴轴含义颜色
    (*axisX)[type]->setTitleBrush(axisBrush);
    (*axisY)[type]->setTitleBrush(axisBrush);

    //别忘记把坐标轴添加到chart
    chart->addAxis((*axisX)[type], Qt::AlignBottom);  //并且XY轴的位置是上和右
    chart->addAxis((*axisY)[type], Qt::AlignLeft);

    chart->setBackgroundBrush(Qt::white);

    chart->setAnimationOptions(QChart::SeriesAnimations);//设置曲线呈动画显示

    for(int k=0;k<f.n;k++){
        addSeries(chart,m_series,f,2,k);
    }

    connectMarkers(chart);

    chartView->setRenderHint(QPainter::Antialiasing); //设置抗锯齿
    chartView->show(); //显示
}

void Chart::graphShowSetup(QTabWidget *tabWidget,QString name,QList<QDateTimeAxis *> *axisX,QList<QValueAxis *> *axisY)
{
    QDateTimeAxis *axis1 = new QDateTimeAxis;
    axisX->append(axis1);
    QValueAxis *axis2 = new QValueAxis;
    axisY->append(axis2);

    QWidget *widget=new QWidget;
    tabWidget->addTab(widget,name);
}

void Chart::addSeries(QChart *chart,QList<QLineSeries*> *m_series,func f,unsigned int lineWidth,int type)
{
    QLineSeries*series = new QLineSeries();
    //设置一些QPen，以便待会设置线条的颜色，宽度
    QPen p0;
    p0.setWidth(lineWidth);
    p0.setColor(fd->returnColor(f.c[type].toInt()));
    series->setPen(p0);

    series->setName(f.variaName[type]);
    //Y轴最大值为全部数据里最大值，如最大值为10，Y轴最大值为2--->10在Y值为2的位置上
    //故先取一值为最大值1
    series->append(0,f.ymax[type].toDouble());
    series->append(1,f.ymin[type].toDouble());
    for(int i=2;i<maxSize;++i)
           series->append(i,0);
    series->setUseOpenGL(true);//openGl 加速
    m_series->append(series);
    chart->addSeries(series);

}

void Chart::changeData(QList<QLineSeries*> *m_series,QString value,func f,int index,int count)
{
    QVector<QPointF> oldPoints =(*m_series)[count]->pointsVector();
    QVector<QPointF> points;
    int size=1;
    for(int i=0;i<oldPoints.count()-size;++i){
        points.append(QPointF(i,oldPoints.at(i+size).y()));//替换数据用
    }
    qint64 sizePoints = points.count();
    for(int k=0;k<size;++k){
        points.append(QPointF(k+sizePoints,value.toDouble()));
    }
    (*m_series)[count]->replace(points);

    (*m_series)[count]->setName(f.variaName[index]+":"+value+f.units[index]);


}


void Chart::becomeOrigin(FunctionD ff,QList<QLineSeries*> *m_series)
{
    int count=0;
    for(int i=0;i<ff.N;i++){
        for(int j=0;j<ff.f[i].n;j++){
            becomeOrigin_one(m_series,ff.f[i],j,count);
            count++;
        }
    }
}

void Chart::becomeOrigin_one(QList<QLineSeries*> *m_series,func f,int index,int count)
{
    QVector<QPointF> points;
    for(int i=0;i<maxSize;++i){
          points.append(QPointF(i,0));//替换数据用
    }
    (*m_series)[count]->replace(points);
    (*m_series)[count]->setName(f.variaName[index]+":0"+f.units[index]);

}

void Chart::becomeOrigin_Count(FunctionD ff,QList<QLineSeries*> *m_series)
{
    int count=0;
    for(int i=0;i<ff.N;i++){
        for(int j=0;j<ff.f[i].n;j++){
            if(j==0)
              becomeOrigin_one_Count(m_series,ff.f[i],j,count,0);
            else if(j==1)
              becomeOrigin_one_Count(m_series,ff.f[i],j,count,xyzpeakthresdef);
            count++;
        }
    }
}

void Chart::becomeOrigin_one_Count(QList<QLineSeries*> *m_series,func f,int index,int count,int value)
{
    QVector<QPointF> points;
    for(int i=0;i<maxSize;++i){
        points.append(QPointF(i,value));
    }
    (*m_series)[count]->replace(points);
  //  (*m_series)[count]->setName(f.variaName[index]+":0"+f.units[index]);

}

void Chart::becomeOrigin_Gait(FunctionD ff,QList<QLineSeries*> *m_series)
{
    int count=0;
    for(int i=0;i<ff.N;i++){
        for(int j=0;j<ff.f[i].n;j++){
            if(j==0)
              becomeOrigin_one_Gait(m_series,ff.f[i],j,count,0);
            else if(j==1)
                becomeOrigin_one_Gait(m_series,ff.f[i],j,count,valleythres);
            else if(j==2)
                becomeOrigin_one_Gait(m_series,ff.f[i],j,count,peakthres);
            count++;
        }
    }
}

void Chart::becomeOrigin_one_Gait(QList<QLineSeries*> *m_series,func f,int index,int count,int value)
{
    QVector<QPointF> points;
    for(int i=0;i<maxSize;++i){
        points.append(QPointF(i,value));
    }
    (*m_series)[count]->replace(points);
  //  (*m_series)[count]->setName(f.variaName[index]+":0"+f.units[index]);

}

void Chart::SliderData(QList<QLineSeries*> *m_series, int value,dataStore dataStore1,QList<QDateTimeAxis *> *axisX,FunctionD fun)
{
    QDateTime time =QDateTime::fromString(dataStore1.sysTime[value-1], "yyyy-MM-dd hh:mm:ss.zzz");   
    int count=0;
    for(int i=0;i<fun.N;i++){
        for(int j=0;j<fun.f[i].n;j++){
            SliderData_one(m_series,fun.f[i],j,count,dataStore1.dataRecord,value);
            count++;
        }
        (*axisX)[i]->setRange( time.addMSecs(-maxSize/dataStore1.SampleRate*1000),time);
    }
}

void Chart::SliderData_one(QList<QLineSeries*> *m_series,func f,int index,int count,QList<QStringList> list,int value)
{
    QVector<QPointF> points;

    if(value<maxSize){
        for(int i=0;i<maxSize-value;++i){
            points.append(QPointF(i,0));//替换数据用
        }
        qint64 sizePoints = points.count();
        for(int k=0;k<value;++k){
            QString d=list[k].at(count);
            points.append(QPointF(k+sizePoints,d.toDouble()));
        }

    }else{
        for(int i=0;i<maxSize;++i){
            QString d=list[value-maxSize+i].at(count);
            points.append(QPointF(i,d.toDouble()));//替换数据用
        }
    }
    (*m_series)[count]->replace(points);
    (*m_series)[count]->setName(f.variaName[index]+":"+list[value-1].at(count)+f.units[index]);

}


void Chart::connectMarkers(QChart *chart)
{
//![1]
    // Connect all markers to handler
    const auto markers = chart->legend()->markers();
    for (QLegendMarker *marker : markers) {
        // Disconnect possible existing connection to avoid multiple connections
        QObject::disconnect(marker, &QLegendMarker::clicked,
                            this, handleMarkerClicked);
        QObject::connect(marker, &QLegendMarker::clicked, this, handleMarkerClicked);
    }
//![1]
}

void Chart::disconnectMarkers(QChart *chart)
{
//![2]
    const auto markers = chart->legend()->markers();
    for (QLegendMarker *marker : markers) {
        QObject::disconnect(marker, &QLegendMarker::clicked,
                            this, handleMarkerClicked);
    }
//![2]
}

void Chart::handleMarkerClicked()
{
//![3]
    QLegendMarker* marker = qobject_cast<QLegendMarker*> (sender());
    Q_ASSERT(marker);
//![3]

//![4]
    switch (marker->type())
//![4]
    {
        case QLegendMarker::LegendMarkerTypeXY:
        {
//![5]
        // Toggle visibility of series
        marker->series()->setVisible(!marker->series()->isVisible());

        // Turn legend marker back to visible, since hiding series also hides the marker
        // and we don't want it to happen now.
        marker->setVisible(true);
//![5]

//![6]
        // Dim the marker, if series is not visible
        qreal alpha = 1.0;

        if (!marker->series()->isVisible())
            alpha = 0.5;

        QColor color;
        QBrush brush = marker->labelBrush();
        color = brush.color();
        color.setAlphaF(alpha);
        brush.setColor(color);
        marker->setLabelBrush(brush);

        brush = marker->brush();
        color = brush.color();
        color.setAlphaF(alpha);
        brush.setColor(color);
        marker->setBrush(brush);

        QPen pen = marker->pen();
        color = pen.color();
        color.setAlphaF(alpha);
        pen.setColor(color);
        marker->setPen(pen);

//![6]
        break;
        }
    default:
        {
        qDebug() << "Unknown marker type";
        break;
        }
    }
}


#include "mainwindow.h"
#include "qwdialogpen.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createChart();
    prepareData();
    updateFromChart();

    ui->chkPointVisible->setCheckState(Qt::Unchecked);
    ui->radioLabelFormy->setCheckable(false);
    ui->radioPLabelFormxy->setCheckable(false);
    ui->btnSeriesName->setCheckable(ui->radioSeries0->isChecked()|ui->radioSeries1->isChecked());
    ui->btnSeriesColor->setCheckable(ui->radioSeries0->isChecked()|ui->radioSeries1->isChecked());
    ui->btnSeriesPen->setCheckable(ui->radioSeries0->isChecked()|ui->radioSeries1->isChecked());
    ui->btnDataLabelColor->setCheckable(ui->radioSeries0->isChecked()|ui->radioSeries1->isChecked());

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::createChart()
{
    //创建图表的各个组件
    QChart *chart=new QChart();
    chart->setTitle("简单函数曲线");
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);

    QLineSeries *series0=new QLineSeries();
    QLineSeries *series1=new QLineSeries();
    series0->setName("Sin曲线");
    series1->setName("Cos曲线");
   // curSeries=series0;

    QPen pen;
    pen.setStyle(Qt::DotLine);
    pen.setWidth(2);
    pen.setColor(Qt::blue);
    series0->setPen(pen);

    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::green);
    series1->setPen(pen);

    chart->addSeries(series0);
    chart->addSeries(series1);

    QValueAxis * axisX=new QValueAxis;
    curAxis=axisX;  //当前坐标轴
    axisX->setRange(0,10);
    axisX->setLabelFormat("%.1f");  //标签格式
    axisX->setTickCount(11);       //主分隔个数
    axisX->setMinorTickCount(4);
    axisX->setTitleText("time(secs)");

    QValueAxis * axisY=new QValueAxis;
    axisY->setRange(-2,2);
    axisY->setTitleText("Value");
    axisY->setLabelFormat("%.2f");  //标签格式
    axisX->setTickCount(5);       //主分隔个数
    axisX->setMinorTickCount(4);

    chart->setAxisX(axisX,series0);
    chart->setAxisX(axisX,series1);
    chart->setAxisY(axisY,series0);
    chart->setAxisY(axisY,series1);



}

void MainWindow::prepareData()
{
    QLineSeries *series0=(QLineSeries*)ui->chartView->chart()->series().at(0);
    QLineSeries* series1=(QLineSeries*)ui->chartView->chart()->series().at(1);
    series0->clear();
    series1->clear();
    qsrand(QTime::currentTime().second());
    qreal t=0,y1,y2,intv=0.1;
    qreal rd;
    int cnt=100;
    for(int i=0;i<cnt;i++)
    {
        rd=(qrand()%10)-5;  //-5~5
        y1=qSin(t)+rd/50;
        series0->append(t,y1);
        rd=(qrand()%10)-5;  //-5~5
        y2=qCos(t)+rd/50;
        series1->append(t,y2);
        t+=intv;
    }


    ui->comboAnimation->addItem("NoAnimation");
    ui->comboAnimation->addItem("GridAxisAnimations");
    ui->comboAnimation->addItem("SeriesAnimations");
    ui->comboAnimation->addItem("AllAnimations");

    ui->comboTheme->addItem("ChartThemeLight");
    ui->comboTheme->addItem("ChartThemeBlueCerulean");
    ui->comboTheme->addItem("ChartThemeDark");
    ui->comboTheme->addItem("ChartThemeBrownSand");
    ui->comboTheme->addItem("ChartThemeBlueNcs");
    ui->comboTheme->addItem("ChartThemeHighContrast");
    ui->comboTheme->addItem("ChartThemeBlueIcy");
    ui->comboTheme->addItem("ChartThemeQt");



}

void MainWindow::updateFromChart()
{
    QChart * chart= ui->chartView->chart();
    ui->editTitle->setText(chart->title()); //图表标题
    QMargins mg=chart->margins();
    ui->spinMarginLeft->setValue(mg.left());
    ui->spinMarginRight->setValue(mg.right());
    ui->spinMarginTop->setValue(mg.top());
    ui->spinMarginBottom->setValue(mg.bottom());


}

void MainWindow::on_btnTitileFont_clicked()
{
    bool ok=false;
    QFont font=ui->chartView->chart()->titleFont();
    font=QFontDialog::getFont(&ok,font);
    if(ok)
    {
        ui->chartView->chart()->setTitleFont(font);
    }
}


void MainWindow::on_radioSeries0_clicked()
{
    if(ui->radioSeries0->isChecked())
        curSeries=(QLineSeries*)ui->chartView->chart()->series().at(0);
    else
        curSeries=(QLineSeries*)ui->chartView->chart()->series().at(1);

    ui->editSeriesName->setText(curSeries->name());
    ui->chkSeriesVisible->setChecked(curSeries->isVisible());
    ui->chkPointLabelVisible->setChecked(curSeries->pointsVisible());
    ui->sliderSeriesOpacity->setValue(curSeries->opacity()*10);
}


void MainWindow::on_radioSeries1_clicked()
{
    if(ui->radioSeries1->isChecked())
        curSeries=(QLineSeries*)ui->chartView->chart()->series().at(1);
    else
        curSeries=(QLineSeries*)ui->chartView->chart()->series().at(0);

    ui->editSeriesName->setText(curSeries->name());
    ui->chkSeriesVisible->setChecked(curSeries->isVisible());
    ui->chkPointLabelVisible->setChecked(curSeries->pointsVisible());
    ui->sliderSeriesOpacity->setValue(curSeries->opacity()*10);
}


void MainWindow::on_radioLabelFormy_clicked()
{
    if(ui->radioLabelFormy->isChecked())
        curSeries->setPointLabelsFormat("@yPoint");
}



void MainWindow::on_radioPLabelFormxy_clicked()
{
    if(ui->radioPLabelFormxy->isChecked())
        curSeries->setPointLabelsFormat("(@xPoint,@yPoint)");

}


void MainWindow::on_radioX_clicked()
{
    if(ui->radioX->isChecked())
        curAxis=(QValueAxis*)ui->chartView->chart()->axisX();
    else
        curAxis=(QValueAxis*)ui->chartView->chart()->axisY();

    ui->spinAxisMin->setValue(curAxis->min());
    ui->spinAxisMax->setValue(curAxis->max());
    ui->editAxisTitle->setText(curAxis->titleText());
    ui->editAxisLabelFormat->setText(curAxis->labelFormat());
    ui->chkBoxLabelsVisble->setChecked(curAxis->labelsVisible());
}



void MainWindow::on_btnSetTitle_clicked()
{
    ui->chartView->chart()->setTitle(ui->editTitle->text());
}


void MainWindow::on_btnLegendFont_clicked()
{
    bool ok=false;
    QFont font=ui->chartView->chart()->legend()->font();
    font=QFontDialog::getFont(&ok,font);
    if(ok)
    {
        ui->chartView->chart()->legend()->setFont(font);
    }
}


void MainWindow::on_btnSetMargin_clicked()
{
    QMargins mg=ui->chartView->chart()->margins();
    mg.setLeft(ui->spinMarginLeft->value());
    mg.setRight(ui->spinMarginRight->value());
    mg.setTop(ui->spinMarginTop->value());
    mg.setBottom(ui->spinMarginBottom->value());

    ui->chartView->chart()->setMargins(mg);
}


void MainWindow::on_comboAnimation_currentIndexChanged(int index)
{
    QString option=ui->comboAnimation->currentText();
    if(option=="AllAnimations")ui->chartView->chart()->setAnimationOptions(QChart::AllAnimations);
    else if(option=="GridAxisAnimations")ui->chartView->chart()->setAnimationOptions(QChart::GridAxisAnimations);
    else if(option=="SeriesAnimations")ui->chartView->chart()->setAnimationOptions(QChart::SeriesAnimations);
    else ui->chartView->chart()->setAnimationOptions(QChart::NoAnimation);
}


void MainWindow::on_comboTheme_currentTextChanged(const QString &arg1)
{

    QString option=ui->comboTheme->currentText();
    if(option=="ChartThemeLight")
        ui->chartView->chart()->setTheme(QChart::ChartThemeLight);
    else if(option=="ChartThemeBlueCerulean")
        ui->chartView->chart()->setTheme(QChart::ChartThemeBlueCerulean);
    else if(option=="ChartThemeDark")
        ui->chartView->chart()->setTheme(QChart::ChartThemeDark);
    else if(option=="ChartThemeBrownSand")
        ui->chartView->chart()->setTheme(QChart::ChartThemeBrownSand);
    else if(option=="ChartThemeBlueNcs")
        ui->chartView->chart()->setTheme(QChart::ChartThemeBlueNcs);
    else if(option=="ChartThemeHighContrast")
        ui->chartView->chart()->setTheme(QChart::ChartThemeHighContrast);
    else if(option=="ChartThemeBlueIcy")
        ui->chartView->chart()->setTheme(QChart::ChartThemeBlueIcy);
    else ui->chartView->chart()->setTheme(QChart::ChartThemeQt);
}


void MainWindow::on_btnSeriesName_clicked()
{
    curSeries->setName(ui->editSeriesName->text());
}


void MainWindow::on_chkSeriesVisible_clicked()
{
    curSeries->setVisible(ui->chkSeriesVisible->isChecked());
}


void MainWindow::on_chkPointVisible_clicked()
{
    curSeries->setPointsVisible(ui->chkPointLabelVisible->isChecked());
}


void MainWindow::on_btnSeriesColor_clicked()
{
    QColor color=curSeries->color();
    color=QColorDialog::getColor(color,this,"为当前曲线选择颜色");
    curSeries->setColor(color);
}


void MainWindow::on_btnSeriesPen_clicked()
{
    QWDialogPen * pDlg=new QWDialogPen;
    bool ok;
    QPen pen=curSeries->pen();
    pDlg->setPen(pen);

    pen=pDlg->getPen(pen,ok);
    if(ok)
        curSeries->setPen(pen);
}



void MainWindow::on_sliderSeriesOpacity_valueChanged(int value)
{
    curSeries->setOpacity(ui->sliderSeriesOpacity->value()/10.0);

}


void MainWindow::on_chkPointLabelVisible_clicked()
{
    bool flag=ui->chkPointLabelVisible->isChecked();
    curSeries->setPointLabelsVisible(flag);
    ui->radioLabelFormy->setCheckable(flag);
    ui->radioPLabelFormxy->setCheckable(flag);
}


void MainWindow::on_btnDataLabelColor_clicked()
{
    QColor color=curSeries->pointLabelsColor();
    color=QColorDialog::getColor(color,this,"设置数据标签颜色");
    if(color.isValid())
        curSeries->setPointLabelsColor(color);
}


void MainWindow::on_btnDataLabelFont_clicked()
{
    QFont font=curSeries->pointLabelsFont();
    bool ok;
    font=QFontDialog::getFont(&ok,this);
    curSeries->setPointLabelsFont(font);
}


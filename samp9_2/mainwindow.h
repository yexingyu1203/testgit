#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtCharts/QtCharts>
QT_CHARTS_USE_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnTitileFont_clicked();

    void on_radioSeries0_clicked();

    void on_radioSeries1_clicked();

    void on_radioLabelFormy_clicked();

    void on_radioPLabelFormxy_clicked();

    void on_radioX_clicked();

    void on_btnSetTitle_clicked();

    void on_btnLegendFont_clicked();

    void on_btnSetMargin_clicked();

    void on_comboAnimation_currentIndexChanged(int index);

    void on_comboTheme_currentTextChanged(const QString &arg1);

    void on_btnSeriesName_clicked();

    void on_chkSeriesVisible_clicked();

    void on_chkPointVisible_clicked();

    void on_btnSeriesColor_clicked();

    void on_btnSeriesPen_clicked();

    void on_sliderSeriesOpacity_valueChanged(int value);

    void on_chkPointLabelVisible_clicked();

    void on_btnDataLabelColor_clicked();

    void on_btnDataLabelFont_clicked();

private:
    Ui::MainWindow *ui;
    QLineSeries *curSeries; //当前序列
    QValueAxis *curAxis;    //当前坐标轴
    void createChart(); //创建图表
    void prepareData(); //更新数据
    void updateFromChart(); //从图标更新到界面

};
#endif // MAINWINDOW_H

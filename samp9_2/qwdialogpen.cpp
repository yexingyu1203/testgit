#include "qwdialogpen.h"
#include "ui_qwdialogpen.h"

QWDialogPen::QWDialogPen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::QWDialogPen)
{
    ui->setupUi(this);
    ui->comboPenStyle->addItem("Solid Line");
    ui->comboPenStyle->addItem("Dash Line");
    ui->comboPenStyle->addItem("Dot Line");
    ui->comboPenStyle->addItem("DashDot Line");
    ui->comboPenStyle->addItem("DashDotDot Line");
    ui->comboPenStyle->addItem("CustomDash Line");
}

QWDialogPen::~QWDialogPen()
{
    delete ui;
}

void QWDialogPen::setPen(QPen pen)
{
    m_pen=pen;
    ui->spinWidth->setValue(pen.width());
    int i=static_cast<int>(pen.style());
    ui->comboPenStyle->setCurrentIndex(i);
    QColor color=pen.color();
    ui->btnColor->setAutoFillBackground(true);
    QString str=QString::asprintf("background-color:rgb(%d,%d,%d);",color.red(),color.green(),color.blue());
    ui->btnColor->setStyleSheet(str);
}

QPen QWDialogPen::getPen()
{
    m_pen.setStyle(Qt::PenStyle(ui->comboPenStyle->currentIndex()));    //线形
    m_pen.setWidth(ui->spinWidth->value());
    QColor color=ui->btnColor->palette().color(QPalette::Button);
    return m_pen;
}

QPen QWDialogPen::getPen(QPen iniPen, bool &ok)
{
    //静态函数 获取pen
    QWDialogPen *Dlg=new QWDialogPen;
    Dlg->setPen(iniPen);
    QPen pen;
    int ret=Dlg->exec();
    if(ret==QDialog::Accepted)
    {
        pen=Dlg->getPen();
        ok=true;
    }
    else
    {
        pen=iniPen;
        ok=false;
    }
    delete Dlg;
    return pen; //返回设置的QPen对象
}

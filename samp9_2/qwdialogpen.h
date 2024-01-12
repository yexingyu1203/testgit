#ifndef QWDIALOGPEN_H
#define QWDIALOGPEN_H

#include <QDialog>
#include <QPen>

namespace Ui {
class QWDialogPen;
}

class QWDialogPen : public QDialog
{
    Q_OBJECT
private:
    QPen m_pen;

public:
    explicit QWDialogPen(QWidget *parent = nullptr);
    ~QWDialogPen();
    void setPen(QPen pen);
    QPen getPen();
    static QPen getPen(QPen iniPen,bool &ok);

private:
    Ui::QWDialogPen *ui;
};

#endif // QWDIALOGPEN_H

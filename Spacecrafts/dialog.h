#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtSql>
#include <QSqlTableModel>
#include "qcustomplot.h"
#include "QColorDialog"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0, QStringList name = {},int count=0, QString min = "", QString max = "");
    ~Dialog();

private slots:


    void slotRangeChanged(const QCPRange &newRange);

    void colorChanged(QColor);

    void on_ChangeColorBtn_clicked();

    void slotMousePress(QMouseEvent *event);
    void slotMouseMove(QMouseEvent *event);

    void on_ChangeColorBox_currentIndexChanged(int index);

private:
    Ui::Dialog *ui;
    QCPGraph *graphic;
    QCPCurve *verticalLine;
    QCPItemTracer *tracer;

};

#endif // DIALOG_H

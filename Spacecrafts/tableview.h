#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QDialog>

namespace Ui {
class tableview;
}

class tableview : public QDialog
{
    Q_OBJECT

public:
    explicit tableview(QWidget *parent = 0);
    ~tableview();

private slots:

    void on_SpaceshipsView_currentIndexChanged(int index);

    void on_OnboardsystemsView_currentIndexChanged(int index);

    void on_ButtonCancel_clicked();

    void on_ButtonView_clicked();

private:
    Ui::tableview *ui;
};

#endif // TABLEVIEW_H

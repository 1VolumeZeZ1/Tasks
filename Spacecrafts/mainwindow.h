#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlTableModel>
#include "qcustomplot.h"
#include "QColorDialog"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool CreateConnection();

private slots:
    void on_load_clicked();

    void on_clear_clicked();

    void on_OnBoardSystems_currentIndexChanged(int index);

    void on_SpaceShips_currentIndexChanged(int index);

    void on_AddButton_clicked();

    void on_TableViewButton_clicked();

private:
    Ui::MainWindow *ui;
    QCPGraph *graphic;
};

#endif // MAINWINDOW_H

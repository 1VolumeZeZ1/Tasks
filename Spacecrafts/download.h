#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QDialog>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace Ui {
class Download;
}

class Download : public QDialog
{
    Q_OBJECT

public:
    explicit Download(QWidget *parent = 0,QString name="",QString id="");
    ~Download();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Download *ui;
    QString name;
    QString id;
};

#endif // DOWNLOAD_H

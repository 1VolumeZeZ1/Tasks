#include "download.h"
#include "ui_download.h"

Download::Download(QWidget *parent,QString name1,QString id1) :
    QDialog(parent),
    ui(new Ui::Download)
{
    ui->setupUi(this);
    name=name1;
    id=id1;
    srand(time(NULL));

}

Download::~Download()
{
    delete ui;
}

void Download::on_buttonBox_accepted()
{
    QSqlQuery query;
    int value;
    //Фукнция сравнения даты min - max
    int a = ui->MaximumRand_2->text().toInt();
    int b = ui->MinimumRand_2->text().toInt();
    QDateTime datemin, datemax;
    int interval = ui->interval_2->text().toInt();
    datemin = QDateTime::fromString(ui->minimum_2->text(),"dd MM yyyy hh:mm:ss");//считывание даты в формате "день месяц год час:минута:секунда"
    double min = datemin.toTime_t();//дата в число
    datemax = QDateTime::fromString(ui->maximum_2->text(),"dd MM yyyy hh:mm:ss");//считывание даты в формате "день месяц год час:минута:секунда"
    double max = datemax.toTime_t();//дата в число
    QDateTime date;
    //Заполнение граф дата и значение рандомными значениями и соответственными датами
    if(b<a){
        while(min<max)
        {
            date.setTime_t(min);
            value = b + rand()%(a-b+1);
            QString s = QString::number(value);
            query.prepare("INSERT INTO " + name + " (id_op,value,time) VALUES ( :id_op,:value,:time)");
            query.bindValue(":id_op", id);
            query.bindValue(":value",value);
            query.bindValue(":time",date.toString("dd MM yyyy hh:mm:ss"));
            query.exec();
            min += interval;
        }
    }

}

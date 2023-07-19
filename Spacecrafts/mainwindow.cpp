#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSqlQueryModel"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <dialog.h>
#include <download.h>
#include <tableview.h>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    CreateConnection();
    srand(time(NULL));
    ui->setupUi(this);

    QSqlQuery query;
    QSqlQuery query2;
    QSqlQuery query3;
    QSqlQuery query4;
    query.exec("CREATE TABLE "                          /* Запрос на создание таблицы при её отсутствии */
               "IF NOT EXISTS "
               "spaceships (id serial NOT NULL PRIMARY KEY,"
                          "name varchar(20)"
               ");");


    query.exec("CREATE TABLE "                          /* Запрос на создание таблицы при её отсутствии */
               "IF NOT EXISTS "
               "onboardsystems (id serial NOT NULL PRIMARY KEY,"
                          "name varchar(20),"
                          "id_ka int"
               ");");

    query.exec("CREATE TABLE "                          /* Запрос на создание таблицы при её отсутствии */
               "IF NOT EXISTS "
               "options (id serial NOT NULL PRIMARY KEY,"
                          "name varchar(50),"
                          "id_bs int"
               ");");

    query.exec("ALTER TABLE options "
               "ADD CONSTRAINT fk_id FOREIGN KEY (id_bs) "
               "REFERENCES onboardsystems (id)");


    query.exec("ALTER TABLE onboardsystems "
               "ADD CONSTRAINT fk_id FOREIGN KEY (id_ka) "
               "REFERENCES spaceships (id)");

    //Подключение таблиц к ComboBox
    query.exec("SELECT id,name FROM spaceships");
    while(query.next())
    {
        ui->SpaceShips->addItem(query.value(1).toString(),query.value(0));
    }


    //Создание таблиц для датчиков
    QString s;
    query.exec("SELECT id, name FROM onboardsystems");
    query2.exec("SELECT id, name FROM spaceships");
    int count_ka = 0;
    query.next();
    query2.next();
    while(count_ka != 2)
    {
        int count_bs = 0;
        count_ka++;
        while (count_bs != 3)
        {
            count_bs++;
            int count = 0;
            while( count != 3)
            {

                count++;
                s=QString::number(count);
                query3.exec("CREATE TABLE " "IF NOT EXISTS "+ query2.record().value(1).toString() + "_" + query.record().value(1).toString() +
                                             "_Temperature_" + s + " (id serial NOT NULL PRIMARY KEY,"
                                                        "id_op int,"
                                                        "value int,"
                                                        "time timestamp without time zone"
                                             ");");;
                query4.exec("ALTER TABLE "+query2.record().value(1).toString() + "_" + query.record().value(1).toString() +
                            "_Temperature_" + s +
                           " ADD CONSTRAINT fk_id FOREIGN KEY (id_op) "
                           "REFERENCES options (id)");

            }
            query.next();
        }
        query2.next();
    }

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_load_clicked()
{
   //Переход на форму загрузки
    QDialog *download  = new Download(this,ui->Options->currentText(), ui->Options->itemData(ui->Options->currentIndex()).toString());
    download->open();
}

bool MainWindow::CreateConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");   //Драйвер PostreSQL
    db.setHostName("127.0.0.1");                            //Адрес сервера
    db.setDatabaseName("Spacecraft");                              //Имя БД zoo
    db.setUserName("postgres");                             //Имя пользователя capybara
    db.setPassword("astralinux");                       //Пароль пользователя capybaras4ever
    db.setPort(5432);                                       //Номер порта
    if (!db.open()) {                                       //Создание связи
        QMessageBox msgBox;
        QString str=QString("Ошибка при открытии базы данных:");
        msgBox.setText(str);
        msgBox.setWindowTitle("Ошибка");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setInformativeText(db.lastError().text());
        msgBox.exec();                                      //При ошибке отображение сообщения
        return false;
    }
    return true;
}

void MainWindow::on_clear_clicked()
{
    int count;
    int i = 0;
    QStringList array;
    count = ui->AdditemList->count();
    //получение данных из ListView и заполнение QStringList
    while(i != count)
    {
        array.append(ui->AdditemList->item(i)->text());
        i++;
    }
    //переход на страницу графика
    Dialog *graph = new Dialog(this, array,count, ui->mindate->text(), ui->maxdate->text());
    graph->open();
}

void MainWindow::on_OnBoardSystems_currentIndexChanged(int index)
{
    //Заполнение ComboBox Options в соответствии с предыдущим ComboBox Onboardsystems
    ui->Options->clear();
    QSqlQuery query;
    query.exec("SELECT id,name FROM options where id_bs = "+ ui->OnBoardSystems->itemData(index).toString());
    while(query.next())
    {
        ui->Options->addItem(query.value(1).toString(),query.value(0));
    }

}

void MainWindow::on_SpaceShips_currentIndexChanged(int index)
{
    //Заполнение ComboBox Onboardsystems в соответствии с предыдущим ComboBox SpaceShips
    ui->OnBoardSystems->clear();
    QSqlQuery query;
    query.exec("SELECT id,name FROM onboardsystems where id_ka = "+ ui->SpaceShips->itemData(index).toString());
    while(query.next())
    {
        ui->OnBoardSystems->addItem(query.value(1).toString(),query.value(0));
    }
}

void MainWindow::on_AddButton_clicked()
{
    //Добавление элементов в ListView
    QString string = ui->Options->currentText();
    ui->AdditemList->addItem(string);
}

void MainWindow::on_TableViewButton_clicked()
{
    //переход на страницу вывода таблиц
    tableview *table = new tableview(this);
    table->open();
}

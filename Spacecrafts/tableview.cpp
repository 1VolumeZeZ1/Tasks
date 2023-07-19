#include "QSqlQueryModel"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "tableview.h"
#include "ui_tableview.h"

tableview::tableview(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tableview)
{

    ui->setupUi(this);
    //Подключение таблиц к ComboBox
    QSqlQuery query;
    query.exec("SELECT id,name FROM spaceships");
    while(query.next())
    {
        ui->SpaceshipsView->addItem(query.value(1).toString(),query.value(0));
    }
}

tableview::~tableview()
{
    delete ui;
}

void tableview::on_SpaceshipsView_currentIndexChanged(int index)
{
    //Заполнение ComboBox Onboardsystems в соответствии с предыдущим ComboBox SpaceShips
    ui->OnboardsystemsView->clear();
    QSqlQuery query;
    query.exec("SELECT id,name FROM onboardsystems where id_ka = "+ ui->SpaceshipsView->itemData(index).toString());
    while(query.next())
    {
        ui->OnboardsystemsView->addItem(query.value(1).toString(),query.value(0));
    }
}

void tableview::on_OnboardsystemsView_currentIndexChanged(int index)
{
    //Заполнение ComboBox Options в соответствии с предыдущим ComboBox Onboardsystems
    ui->OptionsView->clear();
    QSqlQuery query;
    query.exec("SELECT id,name FROM options where id_bs = "+ ui->OnboardsystemsView->itemData(index).toString());
    while(query.next())
    {
        ui->OptionsView->addItem(query.value(1).toString(),query.value(0));
    }
}

void tableview::on_ButtonCancel_clicked()
{
    close();
}

void tableview::on_ButtonView_clicked()
{
    //Вывод выбранной таблицы в ComboBox
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("SELECT * FROM " + ui->OptionsView->currentText());
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setResizeMode(3, QHeaderView::Stretch);
}

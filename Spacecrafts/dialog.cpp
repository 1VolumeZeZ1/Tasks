#include "dialog.h"
#include "ui_dialog.h"
#include <QSqlQuery>
#include <QSqlQueryModel>

Dialog::Dialog(QWidget *parent,QStringList name,int count, QString min, QString max) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->customPlot->setMinimumHeight(300);


    ui->customPlot->setInteraction(QCP::iRangeZoom,true);
    ui->customPlot->setInteraction(QCP::iRangeDrag,true);
    ui->customPlot->axisRect()->setRangeDrag(Qt::Horizontal);
    ui->customPlot->axisRect()->setRangeZoom(Qt::Horizontal);
    ui->customPlot->xAxis2->setVisible(false);
    ui->customPlot->yAxis2->setVisible(false);
    //Обозначение оси x
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker.data()->setDateTimeFormat("hh:mm");
    ui->customPlot->xAxis->setTicker(dateTicker);
    int j=0;
    tracer = new QCPItemTracer(ui->customPlot);
    tracer->setGraph(ui->customPlot->graph(0));
    //Цикл создания графиков
    while(j!=count)
    {
        qDebug() << count;
        int r,g,b;
        r=rand()%255;
        g=rand()%255;
        b=rand()%255;
        ui->customPlot->addGraph(ui->customPlot->xAxis,ui->customPlot->yAxis);
        qDebug() << count;
        ui->customPlot->graph(j)->setName(name[j]);
        ui->customPlot->graph(j)->setPen(QColor(r,g,b,255));
        ui->customPlot->graph(j)->setLineStyle(QCPGraph::lsNone);
        ui->customPlot->graph(j)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 6));
        //Задаём графу таблицы с выбранными границами вывода
        QSqlQuery query;
        QSqlQuery query2;
        query.exec("SELECT COUNT(id) FROM " + name[j] + " WHERE time BETWEEN '" + min + "' AND '" + max+"'");
        int number;
        query.next();
        number = query.record().value(0).toInt();
        qDebug() << query.lastError();
        qDebug() << number;
        qDebug() << min;
        qDebug() << max;
        query.exec("SELECT time FROM " + name[j] + " WHERE time BETWEEN '" + min + "' AND '" + max+ "'");
        query2.exec("SELECT value FROM " + name[j] + " WHERE time BETWEEN '" + min + "' AND '" + max+"'");
        qDebug() << query.lastError();
        qDebug() << query2.lastError();


        QVector <double> time(number), value(number);
        for(int i=0;i<number;i++)
        {
            query2.next();
            query.next();
            time[i]=query.record().value(0).toDateTime().toTime_t();
            value[i]=query2.record().value(0).toInt();
        }


        ui->customPlot->graph(j)->setData(time,value);
        ui->ChangeColorBox->addItem(name[j],j);
        j++;

    }
    //Создаём label чтоб в него поместить легенду графика
    QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    QCPLayoutElement *dummyElement = new QCPLayoutElement;
    ui->customPlot->plotLayout()->addElement(1, 0, subLayout);
    subLayout->addElement(0, 0, ui->customPlot->legend);
    subLayout->addElement(1, 0, dummyElement);
    subLayout->setColumnStretchFactor(0, 0.001);
    subLayout->setMaximumSize(700, QWIDGETSIZE_MAX);
    subLayout->setRowStretchFactor(0, 0.001);
    ui->customPlot->plotLayout()->setRowStretchFactor(1, 0.01);
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->legend->setBrush(QColor(255,255,255,150));
    connect(ui->customPlot->xAxis,SIGNAL(rangeChanged(QCPRange)),this,SLOT(slotRangeChanged(QCPRange)));

    verticalLine = new QCPCurve(ui->customPlot->xAxis,ui->customPlot->yAxis);

    connect(ui->customPlot, SIGNAL(mouseMove(QMouseEvent*)),this,SLOT(slotMouseMove(QMouseEvent*)));
    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)),this,SLOT(slotMousePress(QMouseEvent*)));

    ui->customPlot->rescaleAxes();
    ui->customPlot->replot();

}


Dialog::~Dialog()
{
    delete ui;
}

void Dialog::slotRangeChanged(const QCPRange &newRange)
{
    //Задаём значения оси х, чтоб они менялись при увелечение масштаба графика
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker.data()->setDateTimeFormat((newRange.size() <= 86400)? "hh:mm" : "dd MMM yy");
    ui->customPlot->xAxis->setTicker(dateTicker);
}

void Dialog::colorChanged(QColor newCol)
{
    //Функция смены цвета
    ui->customPlot->graph(ui->ChangeColorBox->itemData(ui->ChangeColorBox->currentIndex()).toInt())->setPen(newCol);
    ui->customPlot->replot();
}

void Dialog::on_ChangeColorBtn_clicked()
{
    //Вызов окна с изменением цвета
    QColorDialog *dialog = new QColorDialog(this);
    connect(dialog,SIGNAL(colorSelected(QColor)),this,SLOT(colorChanged(QColor)));
    dialog->open();
}

void Dialog::slotMousePress(QMouseEvent *event)
{
    //Получаем координаты нахождения мыши и выводим значения в label
    double cordx = ui->customPlot->xAxis->pixelToCoord(event->pos().x());
    tracer->setGraphKey(cordx);
    tracer->updatePosition();
    QDateTime date;
    date.setTime_t(tracer->position->key());
    ui->graph_result->setText("date: "+ date.toString() + " value: "+ QString::number(tracer->position->value()));
    ui->customPlot->replot();
}

void Dialog::slotMouseMove(QMouseEvent *event)
{
    if(QApplication::mouseButtons())
        slotMousePress(event);
}

void Dialog::on_ChangeColorBox_currentIndexChanged(int index)
{
    //Повторная привязка трейсера к графам по выбору ComboBox
    tracer->setGraph(ui->customPlot->graph(index));
    ui->customPlot->replot();
}

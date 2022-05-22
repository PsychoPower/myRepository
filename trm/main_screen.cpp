#include "main_screen.h"
#include "ui_main_screen.h"
main_screen::main_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::main_screen)
{
    show();
    SetApiMode(OWENIO_API_NEW);
    settings= new QSettings(QCoreApplication::QCoreApplication::applicationDirPath() + "/save.ini",QSettings::IniFormat);
    ui->setupUi(this);
    if(settings->value("first_com_port").toInt())
    {ui->spin_box_first_com_port->setValue(settings->value("first_com_port").toInt());}
    if(settings->value("last_com_port").toInt())
    {ui->spin_box_last_com_port->setValue(settings->value("last_com_port").toInt());}
    if(settings->value("count_devices").toInt())
    {ui->spin_box_count_devices->setValue(settings->value("count_devices").toInt());}
    timer_start.setInterval(1000*30);
    timer_start.setSingleShot(true);
    connect(&timer_start, SIGNAL(timeout()), SLOT(on_pushButton_clicked()));
    timer_start.start();
}

main_screen::~main_screen()
{
    while(ui->trm_layout->count())
    {
        delete ui->trm_layout->itemAt(0)->widget();
    }
    delete ui;
    delete trm_iterator;
}


void main_screen::on_pushButton_clicked()
{
    while(ui->trm_layout->count())
    {
        delete ui->trm_layout->itemAt(0)->widget();
    }
    trm_container.clear();
    if(trm_iterator){delete trm_iterator;}
    for(int row=ui->spin_box_first_com_port->value();row<=ui->spin_box_last_com_port->value();row++)
    {
        for(int column=0;column<=ui->spin_box_count_devices->value();column++)
        {
            trm_widget *trm = new trm_widget(row,column*8);
            trm->setParent(this);
            connect(trm,SIGNAL(done_checking()),this,SLOT(ping_trm()));
            connect(trm,SIGNAL(emited_temperature(int,int,float)),this,SIGNAL(send_temperature_to_write_in_db(int,int,float)));
            ui->trm_layout->addWidget(trm,row,column);
            trm_container.append(trm);
        }
    }
    trm_iterator =new QVectorIterator<QWidget*>(trm_container);
    ping_trm();
}

void main_screen::ping_trm()
{
    if(trm_iterator->hasNext())
    {
        ((trm_widget*)trm_iterator->next())->check_trm();
    }
    else
    {
        trm_iterator->toFront();
        ((trm_widget*)trm_iterator->next())->check_trm();
    }
}

void main_screen::closeEvent(QCloseEvent *event)
{
    emit closing_of_program();
    QWidget::closeEvent(event);
}


void main_screen::on_spin_box_first_com_port_textChanged(const QString &arg1)
{
    settings->setValue("first_com_port",arg1);
    settings->sync();
}


void main_screen::on_spin_box_last_com_port_textChanged(const QString &arg1)
{
    settings->setValue("last_com_port",arg1);
    settings->sync();
}


void main_screen::on_spin_box_count_devices_textChanged(const QString &arg1)
{
    settings->setValue("count_devices",arg1);
    settings->sync();
}


void main_screen::on_stop_button_clicked()
{
    timer_start.stop();
}


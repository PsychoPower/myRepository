#include "main_screen.h"
#include "ui_main_screen.h"
main_screen::main_screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::main_screen)
{
    show();
    SetApiMode(OWENIO_API_NEW);
    ui->setupUi(this);
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


#include "trm_widget.h"
#include "ui_trm_widget.h"
#include "owen_io.h"
trm_widget::trm_widget(int com_port, int adress) :ui(new Ui::trm_widget)
{
    ui->setupUi(this);
    this->com_port=com_port;
    this->adress=adress;
    settings= new QSettings(QCoreApplication::QCoreApplication::applicationDirPath() + "/save.ini",QSettings::IniFormat);
    ui->line_koz->setText(settings->value("COM "+QString::number(com_port)+" adress "+ QString::number(adress)).toString());
}

trm_widget::~trm_widget()
{
    delete ui;
    delete settings;
}

void trm_widget::check_temerature()
{
    if(OpenPort(com_port, 8, prty_NONE, databits_8, stopbit_1, 0)==0)
    {
        ui->label_koz->setStyleSheet("background-color:green;");
        float sum_of_all_temperature=0;
        for(int row=0;row<8;row++)
        {
            int time=8;

            float current_temperature = 0;
            float installed_temperature=0.0;

            //            current_temperature = qrand() % ((190 + 1) - 180) + 180;
            //            installed_temperature = 185;

            QCoreApplication::processEvents();
            ReadIEEE32(adress+row,0,"rEAd",current_temperature,time,-1);
            ((QLabel*)ui->temperature_layout->itemAtPosition(row,0)->widget())->setNum((int)current_temperature);
            sum_of_all_temperature+=current_temperature;

            QCoreApplication::processEvents();
            ReadStoredDotS(adress+row,0,"C.SP",installed_temperature,-1);
            ((QLabel*)ui->temperature_layout->itemAtPosition(row,1)->widget())->setNum((int)installed_temperature);



            if(qFabs(current_temperature-installed_temperature)<5)
            {
                ((QLabel*)ui->temperature_layout->itemAtPosition(row,0)->widget())->setStyleSheet("background-color:green;");
            }
            else
            {
                ((QLabel*)ui->temperature_layout->itemAtPosition(row,0)->widget())->setStyleSheet("background-color:red;");
            }

            if(current_temperature>0)
            {
                emit emited_temperature(com_port,adress+row,current_temperature);
            }
        }
        if(sum_of_all_temperature==0)
        {
            is_active=false;
            current_count_checking=count_skip_checking;
        }
    }
    ui->label_koz->setStyleSheet("background-color:white;");
    ClosePort();
    emit done_checking();
}

void trm_widget::check_trm()
{
    if(is_active)
    {
        check_temerature();
    }
    else
    {
        current_count_checking--;
        if(current_count_checking==0)
        {
            is_active=true;
        }
        emit done_checking();
    }
}

void trm_widget::on_line_koz_textChanged(const QString &arg1)
{
    settings->setValue("COM "+QString::number(com_port)+" adress "+ QString::number(adress) ,arg1);
    settings->sync();
}

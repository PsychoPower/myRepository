#include "logic_handler.h"

logic_handler::logic_handler()
{
    if(!check_db())
    {
        QMessageBox::critical(nullptr,"Error acsess to database",db.lastError().text());
    }
    else
    {
        start();
    }
}

logic_handler::~logic_handler()
{
    db.close();
}

bool logic_handler::check_db()
{
    db=QSqlDatabase::addDatabase("QSQLITE","1");
    db.setDatabaseName(QCoreApplication::applicationDirPath()+"/db.sqlite");
    db_query=new QSqlQuery(db);
    if(!db.open())
    {return false;}

    if(!db.tables().contains("temperature_sheet"))
    {

        if(!db_query->exec("CREATE TABLE 'temperature_sheet' (date TEXT, time TEXT, com_port INTEGER, adress INTEGER, temperature INTEGER)"))
        {return false;}
    }
    return true;
}

void logic_handler::start()
{
    connect(&screen,SIGNAL(send_temperature_to_write_in_db(int,int,float)),this,SLOT(write_temperature(int,int,float)));
    connect(&screen,SIGNAL(closing_of_program()),this,SLOT(end_of_program()));
}

void logic_handler::write_temperature(int com_port, int adress, float current_temperature)
{
    db.open();
    db_query->exec("INSERT INTO 'temperature_sheet' (date, time, com_port, adress, temperature) VALUES ('"+QDate::currentDate().toString("dd.MM.yyyy")+ "', '" + QTime::currentTime().toString("hh:mm:ss")+"', "+QString::number(com_port)+", "+QString::number(adress)+", "+QString::number(current_temperature)+");");
    db.close();
}

void logic_handler::end_of_program()
{
    delete this;
}

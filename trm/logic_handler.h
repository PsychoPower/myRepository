#ifndef LOGIC_HANDLER_H
#define LOGIC_HANDLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QCoreApplication>
#include <QMessageBox>
#include <QDateTime>
#include "main_screen.h"

class logic_handler: public QObject
{
    Q_OBJECT

public:
    logic_handler();
    ~logic_handler();

private:
    main_screen screen;
    QSqlDatabase db;
    QSqlQuery *db_query;
    bool check_db();
    void start();
private slots:
    void write_temperature(int com_port, int adress, float current_temperature);
    void end_of_program();
};

#endif // LOGIC_HANDLER_H

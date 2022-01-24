#include "mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QApplication>
#include <QTextStream>
#include <QChar>
#include <QSqlDatabase>
#include <QSqlQuery>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file1(qApp->applicationDirPath()+"/test_file1.csv");
    QFile file2(qApp->applicationDirPath()+"/test_file2.csv");
    QTextStream out1(&file1);
    QTextStream out2(&file2);
    //Task 1A
    if (!file1.open(QFile::WriteOnly))
    {
        qDebug() << "File not exists";
        return 0;
    }

    QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    for(int rows=0;rows<1024;rows++)
    {
        for(int columns=0;columns<6;columns++)
        {
            for(int symbol=0;symbol<8;symbol++)
            {
                int index = qrand() % possibleCharacters.length();
                out1 <<possibleCharacters.at(index);
            }
            if(columns!=5)
            {
                out1 <<",";
            }
        }
        out1 <<"\n";
    }
    file1.close();
    //Task 1A

    //Task 1B
    if (!file1.open(QFile::ReadOnly))
    {
        qDebug() << "File not exists";
        return 0;
    }
    if (!file2.open(QFile::WriteOnly))
    {
        qDebug() << "File not exists";
        return 0;
    }

    QTextStream in(&file1);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QString lower_line=line.toLower();
        if(lower_line.contains(",a") or lower_line.contains(",e") or lower_line.contains(",i") or lower_line.contains(",o") or lower_line.contains(",u"))
        {
            continue;
        }
        line.replace("1","#");
        line.replace("3","#");
        line.replace("5","#");
        line.replace("7","#");
        line.replace("9","#");
        out2<<line<<"\n";
    }
    file1.close();
    file2.close();
    //Task 1B

    //Task 1C
    if (!file1.open(QFile::ReadOnly))
    {
        qDebug() << "File not exists";
        return 0;
    }
    QSqlDatabase db;
    db=QSqlDatabase::addDatabase("QSQLITE","1");
    db.setDatabaseName(qApp->applicationDirPath()+"/db.sqlite");
    db.open();
    QSqlQuery Query(db);
    if(!db.tables().contains("data"))
    {
          Query.exec("CREATE TABLE 'data'  (column1 TEXT,column2 TEXT,column3 TEXT,column4 TEXT,column5 TEXT,column6 TEXT)");
    }
    while (!in.atEnd())
    {
        QString line = in.readLine();
        line.replace(",","','");
        Query.exec("INSERT INTO 'data' (column1, column2, column3, column4, column5, column6) VALUES ('"+line+"')");
    }
    Query.exec("DELETE FROM 'data' WHERE column2 LIKE '0%'");
    Query.exec("DELETE FROM 'data' WHERE column2 LIKE '1%'");
    Query.exec("DELETE FROM 'data' WHERE column2 LIKE '2%'");
    Query.exec("DELETE FROM 'data' WHERE column2 LIKE '3%'");
    Query.exec("DELETE FROM 'data' WHERE column2 LIKE '4%'");
    Query.exec("DELETE FROM 'data' WHERE column2 LIKE '5%'");
    Query.exec("DELETE FROM 'data' WHERE column2 LIKE '6%'");
    Query.exec("DELETE FROM 'data' WHERE column2 LIKE '7%'");
    Query.exec("DELETE FROM 'data' WHERE column2 LIKE '8%'");
    Query.exec("DELETE FROM 'data' WHERE column2 LIKE '9%'");

    return 0;
}

#include "widget.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QLabel>
#include <QHBoxLayout>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    server = new QTcpServer(this);
    connect(server,&QTcpServer::newConnection,this,&Widget::new_connection);
    server->listen(QHostAddress::Any,1234);
    QLabel *label = new QLabel();
    label->setText("Server is running");
    label->show();
    QHBoxLayout lay;
    lay.addWidget(label);
    this->setLayout(&lay);
    QFile file(qApp->applicationDirPath()+"/response.txt");
    if(!file.exists())
    {
        file.open(QFile::WriteOnly);
        QTextStream out(&file);
        QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");

        for(int i=0;i<10000;i++)
        {
            int index = qrand() % possibleCharacters.length();
            out <<possibleCharacters.at(index);
        }
        file.close();
    }
}

Widget::~Widget()
{

}

void Widget::new_connection()
{
    QFile file(qApp->applicationDirPath()+"/response.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray q = file.readAll();
    QTcpSocket *socket = server->nextPendingConnection();
    socket->write(q);
    socket->flush();
    socket->waitForBytesWritten(3000);
    socket->close();
}


#include "widget.h"
#include <QApplication>
#include <QTcpSocket>
#include <QFile>
#include <QLabel>
#include <QHBoxLayout>
Widget::Widget(QWidget *parent)
    : QWidget(parent)

{
    socket = new QTcpSocket(this);
    connect(socket,&QTcpSocket::channelReadyRead,this,&Widget::connection);
    QLabel *label = new QLabel();
    label->setText("Connection fale");
    label->show();
    QHBoxLayout lay;
    lay.addWidget(label);
    this->setLayout(&lay);
    socket->connectToHost("127.0.0.1",1234);
    !socket->waitForConnected();

}

Widget::~Widget()
{

}

void Widget::connection()
{
    QFile file(qApp->applicationDirPath()+"/response.txt");
    file.open(QIODevice::WriteOnly);
    QByteArray line = socket->readAll();
    qDebug()<<line;
    file.write(line);
    file.close();
    delete this;
}

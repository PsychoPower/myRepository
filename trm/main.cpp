#include <QApplication>
#include "logic_handler.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    logic_handler app;
    return a.exec();
}

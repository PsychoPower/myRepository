#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_H

#include <QWidget>
#include <QSqlDatabase>
#include <QDebug>
#include <QVector>
#include "owen_io.h"
#include "trm_widget.h"
namespace Ui {
class main_screen;
}

class main_screen : public QWidget
{
    Q_OBJECT

public:
    explicit main_screen(QWidget *parent = nullptr);
    ~main_screen();

signals:
    void send_temperature_to_write_in_db(int com_port, int adress, float current_temperature);
    void closing_of_program();


private slots:
    void on_pushButton_clicked();
    void ping_trm();

private:
    Ui::main_screen *ui;
    QVector <QWidget*> trm_container;
    QVectorIterator<QWidget*> *trm_iterator;
    void closeEvent(QCloseEvent *event);

};

#endif // MAIN_SCREEN_H

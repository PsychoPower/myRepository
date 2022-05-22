#ifndef TRM_WIDGET_H
#define TRM_WIDGET_H

#include <QWidget>
#include <QSettings>
#include <QtMath>
#include <QDebug>
#include <QTimer>
namespace Ui {
class trm_widget;
}

class trm_widget : public QWidget
{
    Q_OBJECT

public:
    explicit trm_widget(int com_port, int adress);
    ~trm_widget();
    void check_trm();
signals:
    void emited_temperature(int com_port, int adress, float current_temperature);
    void done_checking();

private slots:
    void on_line_koz_textChanged(const QString &arg1);
    void check_temerature();

private:
    Ui::trm_widget *ui;
    int adress;
    int com_port;
    int count_skip_checking=10000;
    int current_count_checking;

    bool is_active=true;
    QSettings *settings;



};

#endif // TRM_WIDGET_H

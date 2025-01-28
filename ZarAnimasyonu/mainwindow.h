#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dicewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    // Ana pencereyi oluşturur.

    ~MainWindow();


private slots:
    void on_rollButton_clicked();
    // "rollButton" düğmesine tıklandığında çağrılır ve zarlar çevrilir..

private:
    Ui::MainWindow *ui;
    DiceWidget *diceWidget1; // İlk zar widget'ı.
    DiceWidget *diceWidget2; // İkinci zar widget'ı.
};

#endif // MAINWINDOW_H

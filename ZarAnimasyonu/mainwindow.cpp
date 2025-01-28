#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); // Kullanıcı arayüzü ayarları yapılır.

    // Zar widget'ları oluşturulur ve ana pencereye eklenir.
    diceWidget1 = new DiceWidget(this);
    diceWidget2 = new DiceWidget(this);
    ui->gridLayout->addWidget(diceWidget1, 0, 0); // İlk zar widget'ı yerleştirilir.
    ui->gridLayout->addWidget(diceWidget2, 0, 1); // İkinci zar widget'ı yerleştirilir.

    // "rollButton" düğmesine tıklandığında on_rollButton_clicked işlevi çağrılır.
    connect(ui->rollButton, &QPushButton::clicked, this, &MainWindow::on_rollButton_clicked);
}

MainWindow::~MainWindow() {
    delete ui; // Kullanıcı arayüzü nesnesi silinir.
}

void MainWindow::on_rollButton_clicked() {
    diceWidget1->roll(); // İlk zar çevrilir.
    diceWidget2->roll(); // İkinci zar çevrilir.
}

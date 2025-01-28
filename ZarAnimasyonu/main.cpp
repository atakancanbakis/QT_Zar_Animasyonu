#include <QApplication>
#include "./mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Ana pencere nesnesi oluşturulur ve gösterilir.
    MainWindow w;
    w.show();


    return a.exec();
}

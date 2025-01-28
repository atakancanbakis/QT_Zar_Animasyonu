#ifndef DICEWIDGET_H
#define DICEWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QVector3D>
#include <QTimer>

class DiceWidget : public QWidget {
    Q_OBJECT

public:
    explicit DiceWidget(QWidget *parent = nullptr);
    // Zar widget'ını oluşturur.

    void roll();
    // Zarı rastgele çevirmek için.

protected:
    void paintEvent(QPaintEvent *event) override;
    // Widget'ın boyanma olayı gerçekleştiğinde çağrılır ve zarın şeklini oluşturur.

private:
    int currentNumber; // Geçerli zar numarasını tutar.
    QVector<QVector<QVector3D>> triangles; // Zar oluşumu için gerekli 12 üçgeni tutar.
    QTimer *animationTimer; // Animasyon zamanlayıcısı.
    int animationStep; // Animasyon adımı.
    int rotateAngle; // Döndürme açısını belirler.

    void initTriangles();
    // Zarın üçgenlerini oluşturur.

    void rotateTriangles(float angleX, float angleY, float angleZ);
    // Üçgenleri 3D uzayda döndürme işlemi için gerekli.

    void drawDiceFace(QPainter &painter, int face);
    // Belirli bir yüzün çizimini yapmak için kullandık.


    QImage faceImages[6];
    // 6 deseni eklemek için kullanılan sınıf.
};

#endif // DICEWIDGET_H

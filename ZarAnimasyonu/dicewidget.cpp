#include "dicewidget.h"
#include <QPainter>
//#include <QTimer>

DiceWidget::DiceWidget(QWidget *parent) : QWidget(parent), currentNumber(1), animationStep(0), rotateAngle(0) {
    std::srand(std::time(nullptr)); // Rastgele sayılar için başlangıç noktası belirlenir.
    initTriangles(); // Zarın üçgenlerinin başlatılması.

    // Desen yollarının tanımlanması
    faceImages[0].load(":/resimler/images/face1.jpg");
    faceImages[1].load(":/resimler/images/face2.png");
    faceImages[2].load(":/resimler/images/face3.jpg");
    faceImages[3].load(":/resimler/images/face4.png");
    faceImages[4].load(":/resimler/images/face4.png");
    faceImages[5].load(":/resimler/images/face6.jpg");


    animationTimer = new QTimer(this); // Animasyon zamanlayıcısı oluşturma.
    connect(animationTimer, &QTimer::timeout, this, [=]() {
        animationStep++;
        rotateAngle = (rotateAngle + 10) % 360; // Zarın dönme açısını güncelleme
        if (animationStep > 30) {
            animationTimer->stop(); // Animasyon durdurma islemi.
            animationStep = 0;
            rotateAngle = 0;
        }
        update();
    });
}

void DiceWidget::roll() {
    currentNumber = std::rand() % 6 + 1; // Rastgele bir zar numarası oluşturulur.
    animationTimer->start(50); // Zarın çevrilmesi için animasyon başlatılır.
}

void DiceWidget::initTriangles() {
    // Zarın yüzlerini oluşturan üçgenler tanımlanır.
    triangles = {
                 // Face 1 (on)
                 {QVector3D(-0.3f, -0.3f, -0.3f), QVector3D(-0.3f, 0.3f, -0.3f), QVector3D(0.3f, 0.3f, -0.3f)},
                 {QVector3D(0.3f, 0.3f, -0.3f), QVector3D(0.3f, -0.3f, -0.3f), QVector3D(-0.3f, -0.3f, -0.3f)},

                 // Face 2 (arka)
                 {QVector3D(-0.3f, -0.3f, 0.3f), QVector3D(-0.3f, 0.3f, 0.3f), QVector3D(0.3f, 0.3f, 0.3f)},
                 {QVector3D(0.3f, 0.3f, 0.3f), QVector3D(0.3f, -0.3f, 0.3f), QVector3D(-0.3f, -0.3f, 0.3f)},

                 // Face 3 (sol)
                 {QVector3D(-0.3f, -0.3f, -0.3f), QVector3D(-0.3f, 0.3f, -0.3f), QVector3D(-0.3f, 0.3f, 0.3f)},
                 {QVector3D(-0.3f, 0.3f, 0.3f), QVector3D(-0.3f, -0.3f, 0.3f), QVector3D(-0.3f, -0.3f, -0.3f)},

                 // Face 4 (sag)
                 {QVector3D(0.3f, -0.3f, -0.3f), QVector3D(0.3f, 0.3f, -0.3f), QVector3D(0.3f, 0.3f, 0.3f)},
                 {QVector3D(0.3f, 0.3f, 0.3f), QVector3D(0.3f, -0.3f, 0.3f), QVector3D(0.3f, -0.3f, -0.3f)},

                 // Face 5 (alt)
                 {QVector3D(-0.3f, -0.3f, -0.3f), QVector3D(0.3f, -0.3f, -0.3f), QVector3D(0.3f, -0.3f, 0.3f)},
                 {QVector3D(0.3f, -0.3f, 0.3f), QVector3D(-0.3f, -0.3f, 0.3f), QVector3D(-0.3f, -0.3f, -0.3f)},

                 // Face 6 (ust)
                 {QVector3D(-0.3f, 0.3f, -0.3f), QVector3D(0.3f, 0.3f, -0.3f), QVector3D(0.3f, 0.3f, 0.3f)},
                 {QVector3D(0.3f, 0.3f, 0.3f), QVector3D(-0.3f, 0.3f, 0.3f), QVector3D(-0.3f, 0.3f, -0.3f)},
                 };
}


void DiceWidget::rotateTriangles(float angleX, float angleY, float angleZ) {
    for (auto& triangle : triangles) {
        for (auto& vertex : triangle) {
            // X ekseni etrafında döndürme
            float tempY = vertex.y();
            vertex.setY(tempY * cos(angleX) - vertex.z() * sin(angleX));
            vertex.setZ(tempY * sin(angleX) + vertex.z() * cos(angleX));

            // Y ekseni etrafında döndürme
            float tempZ = vertex.z();
            vertex.setZ(tempZ * cos(angleY) - vertex.x() * sin(angleY));
            vertex.setX(tempZ * sin(angleY) + vertex.x() * cos(angleY));

            // Z ekseni etrafında döndürme
            float tempX = vertex.x();
            vertex.setX(tempX * cos(angleZ) - vertex.y() * sin(angleZ));
            vertex.setY(tempX * sin(angleZ) + vertex.y() * cos(angleZ));
        }
    }
}


void DiceWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int side = qMin(width(), height());
    painter.setViewport((width() - side) / 2, (height() - side) / 2, side, side);
    painter.setWindow(-50, -50, 100, 100);

    painter.translate(0, 0);

    // Üçgenlerin dönmesi
    rotateTriangles(rotateAngle * 3.14159 / 180, rotateAngle * 3.14159 / 180, rotateAngle * 3.14159 / 180);

    // Desenleri Yüzeylere giydirme işlemi
    for (int i = 0; i < 6; ++i) {
        QPolygonF poly;
        for (const auto& vertex : triangles[i * 2]) {
            float x = vertex.x() * 25 / (1 - vertex.z() * 0.1);
            float y = vertex.y() * 25 / (1 - vertex.z() * 0.1);
            poly << QPointF(x, y);
        }

        // Her Yüz için desen giydirme işlemi
        painter.drawImage(poly.boundingRect().toRect(), faceImages[i]);
    }


    // Üçgenlerin 2D ekran çizimi
    for (const auto& triangle : triangles) {
        QPolygonF poly;
        for (const auto& vertex : triangle) {
            float x = vertex.x() * 25 / (1 - vertex.z() * 0.1);
            float y = vertex.y() * 25 / (1 - vertex.z() * 0.1);
            poly << QPointF(x, y);
        }
        painter.drawPolygon(poly);
    }

    // Üst yüzeydeki sayı çizilir.
    painter.setPen(Qt::black);
    QFont font = painter.font();
    font.setPointSize(20);
    painter.setFont(font);
    drawDiceFace(painter, currentNumber);
}

void DiceWidget::drawDiceFace(QPainter &painter, int face) {
    // Belirli bir yüzeydeki sayıyı çizer.
    painter.save(); // Mevcut durumu kaydediyoruz
    QFont font = painter.font(); // Mevcut font bilgisini alıyoruz
    font.setPointSize(10); // Font boyutunu küçültüyoruz
    painter.setFont(font); // Yeni font bilgisini ayarlıyoruz

    switch (face) {
    case 1:
        painter.drawText(QRect(-25, -25, 50, 50), Qt::AlignCenter | Qt::AlignBottom, "1");
        break;
    case 2:
        painter.drawText(QRect(-25, -25, 50, 50), Qt::AlignCenter | Qt::AlignBottom, "2");
        break;
    case 3:
        painter.drawText(QRect(-25, -25, 50, 50), Qt::AlignCenter | Qt::AlignBottom, "3");
        break;
    case 4:
        painter.drawText(QRect(-25, -25, 50, 50), Qt::AlignCenter | Qt::AlignBottom, "4");
        break;
    case 5:
        painter.drawText(QRect(-25, -25, 50, 50), Qt::AlignCenter | Qt::AlignBottom, "5");
        break;
    case 6:
        painter.drawText(QRect(-25, -25, 50, 50), Qt::AlignCenter | Qt::AlignBottom, "6");
        break;
    default:
        break;
    }

    painter.restore(); // Önceki duruma geri dönme işleminin gerçekleşmesi.
}


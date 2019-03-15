#ifndef CUBE_H
#define CUBE_H

#include <QWidget>
#include <QVector>
#include <QMatrix3x3>

class Cube : public QWidget
{
    Q_OBJECT
public:
    explicit Cube(QWidget *parent = nullptr);

    void rotateAroundZ(float phi);
    void rotateAroundX(float phi);
    void rotateAroundY(float phi);

    QVector<QVector<QGenericMatrix<1,3,float>>> edges;
signals:

public slots:

private:
    const float rotateZ_M[9] = {
        0, 0, 0,
        0, 0, 0,
        0, 0, 1
    };

    const float rotateX_M[9] = {
        1, 0, 0,
        0, 0, 0,
        0, 0, 0
    };

    const float rotateY_M[9] = {
        0, 0, 0,
        0, 1, 0,
        0, 0, 0
    };

    QGenericMatrix<3,3,float> rotateAroundXMatrix =
            QGenericMatrix<3,3,float>(rotateX_M);
    QGenericMatrix<3,3,float> rotateAroundYMatrix =
            QGenericMatrix<3,3,float>(rotateY_M);
    QGenericMatrix<3,3,float> rotateAroundZMatrix =
            QGenericMatrix<3,3,float>(rotateZ_M);

    static constexpr float EPS = 0.0001;

};

#endif // CUBE_H

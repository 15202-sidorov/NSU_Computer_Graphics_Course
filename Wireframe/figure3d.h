#ifndef FIGURE3D_H
#define FIGURE3D_H

#include <QWidget>
#include <QVector>
#include <QMatrix3x3>
#include <QRgb>

#include "splineedit.h"

# define M_PI 3.14159265358979323846

class Figure3D : public QWidget
{
    Q_OBJECT

public:

    explicit Figure3D(QWidget *parent = nullptr,
                      SplineEdit *inputSpline = nullptr);
    ~Figure3D();

    void buildFigure();

    inline int   getN() { return n; }
    inline int   getM() { return m; }
    inline float getA() { return a; }
    inline float getB() { return b; }
    inline float getC() { return c; }
    inline float getD() { return d; }
    inline float getK() { return k; }

    void  setK(int k_);
    void  setN(int k_);
    void  setM(int k_);

    void  setA(float k_);
    void  setB(float k_);
    void  setC(float k_);
    void  setD(float k_);

    QGenericMatrix<1,3,float> getClass1Knot(int i);
    QGenericMatrix<1,3,float> getClass2Knot(int i);
    QGenericMatrix<1,3,float> getClass2kKnot(int i);
    QGenericMatrix<1,3,float> getClass1kKnot(int i);
    QGenericMatrix<1,3,float> getBaseKnot(int i);

    inline QRgb  getColor() { return color; }
    inline void  setColor(int r, int g, int b)
    {
        color = qRgb(r,g,b);
    }

    inline SplineEdit *getSpline()
    {
        return spline;
    }

    inline bool  isBuild() { return built; }

    void rotateAroundZ(float phi);
    void rotateAroundX(float phi);
    void rotateAroundY(float phi);

signals:

public slots:

private:
    QVector<QGenericMatrix<1,3,float>> baseKnots;
    QVector<QGenericMatrix<1,3,float>> class1Knots;
    QVector<QGenericMatrix<1,3,float>> class2Knots;
    QVector<QGenericMatrix<1,3,float>> class1kKnots;
    QVector<QGenericMatrix<1,3,float>> class2kKnots;

    int n = 5;
    int m = 5;
    int k = 0;

    float a = 0;
    float b = 1;
    float c = 0;
    float d = 2 * M_PI;

    void addBaseKnot(float u, float v);
    void addClass1Knot(float u, float v);
    void addClass2Knot(float u, float v);
    void addClass1kKnot(float u, float v);
    void addClass2kKnot(float u, float v);

    void configKKnots();
    void configKnots();

    SplineEdit *spline;

    QGenericMatrix<1,3,float> getValueFromSpline(float u, float v);

    QVector<float> vKnots;
    QVector<float> uKnots;

    bool built = false;

    float currentPhiX = 0;
    float currentPhiZ = 0;
    float currentPhiY = 0;

    float rotateZ_M[9] = {
        cos(currentPhiZ), -sin(currentPhiZ),  0,
        sin(currentPhiZ),  cos(currentPhiZ),  0,
                       0,                 0,  1
    };

    float rotateX_M[9] = {
        1,                0,                 0,
        0, cos(currentPhiX), -sin(currentPhiX),
        0, sin(currentPhiX), -cos(currentPhiX)
    };

    float rotateY_M[9] = {
         cos(currentPhiY), 0,  sin(currentPhiY),
                        0, 1,                 0,
        -sin(currentPhiY), 0,  cos(currentPhiY)
    };

    QGenericMatrix<3,3,float> rotateAroundXMatrix =
            QGenericMatrix<3,3,float>(rotateX_M);
    QGenericMatrix<3,3,float> rotateAroundYMatrix =
            QGenericMatrix<3,3,float>(rotateY_M);
    QGenericMatrix<3,3,float> rotateAroundZMatrix =
            QGenericMatrix<3,3,float>(rotateZ_M);

    QRgb color = qRgb(255,255,255);

    static const int MAX_K = 30;
    static const int MIN_K = 0;
    static const int MAX_N = 30;
    static const int MIN_N = 0;
    static const int MAX_M = 30;
    static const int MIN_M = 0;

    static constexpr float MAX_A = 1.0f;
    static constexpr float MAX_B = 1.0f;
    static constexpr float MIN_A = 0.0f;
    static constexpr float MIN_B = 0.0f;
    static constexpr float MAX_C = 2 * M_PI;
    static constexpr float MAX_D = 2 * M_PI;
    static constexpr float MIN_C = 0.0f;
    static constexpr float MIN_D = 0.0f;
};

#endif // FIGURE3D_H

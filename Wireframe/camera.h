#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>
#include <QVector3D>
#include <QMatrix4x4>
#include <QMatrix3x3>


# define M_PI 3.14159265358979323846

class Camera : public QWidget
{
    Q_OBJECT
public:
    explicit Camera(QWidget *parent = nullptr);

    inline float getWidth  ()             { return scaleW; }
    inline float getHeight ()             { return scaleH; }
    inline void  setWidth  (float width)  { scaleW = width; }
    inline void  setHeight (float height) { scaleH = height; }
    inline void  setZn     (float z)      { zn = z; }
    inline void  setZf     (float z)      { zf = z; }
    inline float getZn     ()             { return zn; }
    inline float getZf     ()             { return zf; }

    void incZn();
    void decZn();
    bool canSee(float z);
    void rotateWorldAroundX(float phi);
    void rotateWorldAroundY(float phi);
    void rotateWorldAroundZ(float phi);

    QPointF getProjection(float x, float y, float z);

signals:
    void znChanged(float zn, float zf);

public slots:

private:
    QVector3D Pcat  = QVector3D(-10, 0, 0);
    QVector3D Pview = QVector3D( 10, 0, 0);
    QVector3D Vup   = QVector3D(  0, 1, 0);

    QGenericMatrix<1,4,float> worldToCamera(float x,
                                            float y,
                                            float z);

    QGenericMatrix<1,4,float> cameraToHalfCube(
            QGenericMatrix<1,4,float> cubeCoordinate);

    // Camera orts.
    QVector3D w = (Pview - Pcat) / (Pview - Pcat).length();
    QVector3D u = QVector3D::crossProduct(Vup, w) /
                  QVector3D::crossProduct(Vup, w).length();
    QVector3D v = QVector3D::crossProduct(w,u);

    float scaleW = 3;
    float scaleH = 3;

    float zn = 1.9;
    float zf = 101.9f;
    float deltaZ = 0.1;

    // World to camera matrix.
    const float Mp1[16] = {
        u.x(), u.y(), u.z(), -u.x() * Pcat.x(),
        v.x(), v.y(), v.z(), -u.y() * Pcat.y(),
        w.x(), w.y(), w.z(), -u.z() * Pcat.z(),
            0,     0,     0,                 1
    };

    // Camera to cube matrix.
    const float Mp2[16] = {
        2*zn/scaleW,             0,               0,              0,
                   0,  2*zn/scaleH,               0,              0,
                   0,            0,    zn/(zf - zn),-zn*zf/(zf - zn),
                   0,            0,               1,              0
    };

    QGenericMatrix<4,4,float> Mproj1 =
            QGenericMatrix<4,4,float>(Mp1);

    QGenericMatrix<4,4,float> Mproj2 =
            QGenericMatrix<4,4,float>(Mp2);

    QVector3D worldX;
    QVector3D worldY;
    QVector3D worldZ;

    QGenericMatrix<4,4,float> rotateWorldAroundX_Matrix;
    QGenericMatrix<4,4,float> rotateWorldAroundY_Matrix;
    QGenericMatrix<4,4,float> rotateWorldAroundZ_Matrix;

    void setRotateAroundXMatrix(float phi);
    void setRotateAroundYMatrix(float phi);
    void setRotateAroundZMatrix(float phi);
    void setRotationMatrix(float x, float y, float z,
                           float phi,QGenericMatrix<4,4,float> &matrix);

    float phiX = 0;
    float phiY = 0;
    float phiZ = 0;
};

#endif // CAMERA_H

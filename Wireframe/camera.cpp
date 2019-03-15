#include "camera.h"

#include <QDebug>

Camera::Camera(QWidget *parent) : QWidget(parent)
{
    auto xVector = worldToCamera(1.0f,0.0f,0.0f);
    worldX.setX(xVector(0,0));
    worldX.setY(xVector(1,0));
    worldX.setZ(xVector(2,0));

    auto yVector = worldToCamera(0.0f,1.0f,0.0f);
    worldY.setX(yVector(0,0));
    worldY.setY(yVector(1,0));
    worldY.setZ(yVector(2,0));

    auto zVector = worldToCamera(0.0f,0.0f,1.0f);
    worldZ.setX(zVector(0,0));
    worldZ.setY(zVector(1,0));
    worldZ.setZ(zVector(2,0));
}

void Camera::incZn()
{
    if ( zn + deltaZ >= Pview.x() - Pcat.x() )
    {
        return;
    }
    zn += deltaZ;
    zf += deltaZ;
    emit znChanged(zn,zf);
}

void Camera::decZn()
{
    if ( zf - deltaZ <= Pview.x() - Pcat.x() )
    {
        return;
    }
    zn -= deltaZ;
    zf -= deltaZ;
    emit znChanged(zn,zf);
}

bool Camera::canSee(float z)
{
    return (zn <= z) && (zf >= z);
}

void Camera::rotateWorldAroundX(float phi)
{
    phiX += phi;
    setRotateAroundXMatrix(phiX);
}

void Camera::rotateWorldAroundY(float phi)
{
    phiY += phi;
    setRotateAroundYMatrix(phiY);
}

void Camera::rotateWorldAroundZ(float phi)
{
    phiZ += phi;
    setRotateAroundZMatrix(phiZ);
}

void Camera::setRotateAroundXMatrix(float phi)
{
    setRotationMatrix(worldX.x(), worldX.y(), worldX.z(),
                      phi, rotateWorldAroundX_Matrix);
}

void Camera::setRotateAroundYMatrix(float phi)
{
     setRotationMatrix(worldY.x(), worldY.y(), worldY.z(),
                       phi, rotateWorldAroundY_Matrix);
}

void Camera::setRotateAroundZMatrix(float phi)
{
     setRotationMatrix(worldZ.x(), worldZ.y(), worldZ.z(),
                       phi, rotateWorldAroundZ_Matrix);
}

void Camera::setRotationMatrix(float x, float y, float z,
                               float phi, QGenericMatrix<4,4,float> &matrix)
{
    matrix(0,0) = cos(phi) + (1 - cos(phi)) * x * x;
    matrix(1,0) = (1 - cos(phi)) * y * x + sin(phi) * z;
    matrix(2,0) = (1 - cos(phi)) * z * x - sin(phi) * y;

    matrix(0,1) = (1 - cos(phi)) * x * y - sin(phi) * z;
    matrix(1,1) = cos(phi) + (1 - cos(phi)) * y * y;
    matrix(2,1) = (1 - cos(phi)) * z * y + sin(phi) * x;

    matrix(0,2) = (1 - cos(phi)) * x * z + sin(phi) * y;
    matrix(1,2) = (1 - cos(phi)) * y * z - sin(phi) * x;
    matrix(2,2) = cos(phi) + (1-cos(phi)) * z * z;
}

QGenericMatrix<1,4,float> Camera::worldToCamera(float x, float y, float z)
{
    float tempVector[4] = {x,y,z,1};
    QGenericMatrix<1,4,float> temp =
            QGenericMatrix<1,4,float>(tempVector);

    return  (rotateWorldAroundZ_Matrix) * (rotateWorldAroundX_Matrix) * (rotateWorldAroundY_Matrix)* Mproj1 * temp;
}

QGenericMatrix<1,4,float> Camera::cameraToHalfCube(
        QGenericMatrix<1,4,float> cubeCoordinate)
{
    return Mproj2 * cubeCoordinate;
}

QPointF Camera::getProjection(float x, float y, float z)
{
    auto result = cameraToHalfCube(worldToCamera(x,y,z));
    result = result / result(3,0);
    return QPointF(result(0,0)/(result(2,0)/zn), result(1,0)/(result(2,0)/zn));
}







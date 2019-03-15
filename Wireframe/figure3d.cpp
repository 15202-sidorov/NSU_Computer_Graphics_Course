#include "figure3d.h"

Figure3D::Figure3D(QWidget *parent, SplineEdit* inputSpline) :
                   QWidget(parent), spline(inputSpline)
{
    configKnots();
}

Figure3D::~Figure3D()
{
    delete spline;
}


void Figure3D::setK(int k_)
{
    if ( k_ < MIN_K  || k_ > MAX_K )
    {
        return;
    }
    k = k_;
}

void Figure3D::setN(int k_)
{
    if ( k_ < MIN_N  || k_ > MAX_N )
    {
        return;
    }
    n = k_;
    configKnots();
}

void Figure3D::setM(int k_)
{
    if ( k_ < MIN_M  || k_ > MAX_M )
    {
        return;
    }
    m = k_;
    configKnots();
}

void Figure3D::setA(float k_)
{
    if ( k_ < MIN_A  || k_ > MAX_A )
    {
        return;
    }
    a = k_;
    configKnots();
}

void Figure3D::setB(float k_)
{
    if ( k_ < MIN_B || k_ > MAX_B )
    {
        return;
    }
    b = k_;
    configKnots();
}

void Figure3D::setC(float k_)
{
    if ( k_ < MIN_C || k_ > MAX_C )
    {
        return;
    }
    c = k_;
    configKnots();
}

void Figure3D::setD(float k_)
{
    if ( k_ < MIN_D  || k_ > MAX_D )
    {
        return;
    }
    d = k_;
    configKnots();
}

void Figure3D::configKnots()
{
    uKnots.clear();
    vKnots.clear();
    for (int i = 0; i <= n; i++)
    {
        uKnots.push_back(a + (b - a) * i/n);
    }

    for (int i = 0; i <= m; i++)
    {
        vKnots.push_back(c + (d - c) * i/m);
    }
}

void Figure3D::configKKnots()
{
    class1kKnots.clear();
    class2kKnots.clear();

    for (int i = 0; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            for (int t = 1; t < k; t++)
            {
                addClass1kKnot(uKnots[i], vKnots[j-1] + (d-c)*t/(k*m));
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            for (int t = 1; t < k; t++)
            {
                addClass2kKnot(uKnots[i-1] + (b-a)*t/(k * n), vKnots[j]);
            }
        }
    }

}

void Figure3D::buildFigure()
{
    if ( spline->isEmpty() )
    {
        return;
    }

    baseKnots.clear();
    class1Knots.clear();
    class2Knots.clear();

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            addClass2Knot(uKnots[i-1], vKnots[j]);
        }
    }

    for (int i = 0; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            addClass1Knot(uKnots[i], vKnots[j-1]);
        }
    }

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            addBaseKnot(uKnots[i], vKnots[j]);
        }
    }

    configKKnots();

    built = true;
}

QGenericMatrix<1,3,float> Figure3D::getValueFromSpline(float u, float v)
{
    QPointF splineValue = spline->getSplineValue(u);
    float x = splineValue.ry() * cos(v);
    float y = splineValue.ry() * sin(v);
    float z = splineValue.rx();

    float vector[3] = {x,y,z};
    return QGenericMatrix<1,3,float>(vector);
}

void Figure3D::addClass1kKnot(float u, float v)
{
    auto newVector = getValueFromSpline(u,v);
    class1kKnots.append(newVector);
}

void Figure3D::addClass2kKnot(float u, float v)
{
    auto newVector = getValueFromSpline(u,v);
    class2kKnots.append(newVector);
}

void Figure3D::addBaseKnot(float u, float v)
{
    auto newVector = getValueFromSpline(u,v);
    baseKnots.append(newVector);
}

void Figure3D::addClass1Knot(float u, float v)
{
    auto newVector = getValueFromSpline(u,v);
    class1Knots.append(newVector);
}

void Figure3D::addClass2Knot(float u, float v)
{
    auto newVector = getValueFromSpline(u,v);
    class2Knots.append(newVector);
}

void Figure3D::rotateAroundZ(float phi)
{
    currentPhiZ += phi;
    phi = currentPhiZ;

    rotateAroundZMatrix(0,0) = cos(phi);
    rotateAroundZMatrix(0,1) = -sin(phi);
    rotateAroundZMatrix(1,0) = sin(phi);
    rotateAroundZMatrix(1,1) = cos(phi);
}

void Figure3D::rotateAroundX(float phi)
{
    currentPhiX += phi;
    phi = currentPhiX;

    rotateAroundXMatrix(1,1) = cos(phi);
    rotateAroundXMatrix(1,2) = -sin(phi);
    rotateAroundXMatrix(2,1) = sin(phi);
    rotateAroundXMatrix(2,2) = cos(phi);
}

void Figure3D::rotateAroundY(float phi)
{
    currentPhiY += phi;
    phi = currentPhiY;

    rotateAroundYMatrix(0,0) = cos(phi);
    rotateAroundYMatrix(0,2) = sin(phi);
    rotateAroundYMatrix(2,0) = -sin(phi);
    rotateAroundYMatrix(2,2) = cos(phi);
}

QGenericMatrix<1,3,float> Figure3D::getClass1Knot(int i)
{
    return rotateAroundXMatrix *
           rotateAroundYMatrix *
           rotateAroundZMatrix * class1Knots[i];
}

QGenericMatrix<1,3,float> Figure3D::getClass2Knot(int i)
{
    return rotateAroundXMatrix *
           rotateAroundYMatrix *
           rotateAroundZMatrix * class2Knots[i];
}

QGenericMatrix<1,3,float> Figure3D::getClass1kKnot(int i)
{
    return rotateAroundXMatrix *
           rotateAroundYMatrix *
           rotateAroundZMatrix * class1kKnots[i];
}

QGenericMatrix<1,3,float> Figure3D::getClass2kKnot(int i)
{
    return rotateAroundXMatrix *
           rotateAroundYMatrix *
           rotateAroundZMatrix * class2kKnots[i];
}

QGenericMatrix<1,3,float> Figure3D::getBaseKnot(int i)
{
    return rotateAroundXMatrix *
           rotateAroundYMatrix *
           rotateAroundZMatrix * baseKnots[i];
}

#include "cube.h"

Cube::Cube(QWidget *parent) : QWidget(parent)
{
    QVector<QGenericMatrix<1,3,float>> cube;
    float cubeArray[24] = {
        -1.0f, -1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    QGenericMatrix<3,8,float> cubeMatrix(cubeArray);

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < i+1; j++)
        {
            int count = 0;
            for (int k = 0; k < 3; k++)
            {
                if ( cubeMatrix(i,k) != cubeMatrix(j,k) )
                {
                    count++;
                }
            }

            if ( count == 1 )
            {
                float arr1[3] = {cubeMatrix(i,0), cubeMatrix(i,1), cubeMatrix(i,2) };
                float arr2[3] = {cubeMatrix(j,0), cubeMatrix(j,1), cubeMatrix(j,2) };
                QVector<QGenericMatrix<1,3,float>> result;
                result.push_back(QGenericMatrix<1,3,float>(arr1));
                result.push_back(QGenericMatrix<1,3,float>(arr2));
                edges.push_back(result);
            }
        }
    }
}


void Cube::rotateAroundZ(float phi)
{
    rotateAroundZMatrix(0,0) = cos(phi);
    rotateAroundZMatrix(0,1) = -sin(phi);
    rotateAroundZMatrix(1,0) = sin(phi);
    rotateAroundZMatrix(1,1) = cos(phi);

    for (int i = 0; i < edges.size(); i++)
    {
        edges[i][0] = rotateAroundZMatrix * edges[i][0];
        edges[i][1] = rotateAroundZMatrix * edges[i][1];
    }
}


void Cube::rotateAroundX(float phi)
{
    rotateAroundXMatrix(1,1) = cos(phi);
    rotateAroundXMatrix(1,2) = -sin(phi);
    rotateAroundXMatrix(2,1) = sin(phi);
    rotateAroundXMatrix(2,2) = cos(phi);

    for (int i = 0; i < edges.size(); i++)
    {
        edges[i][0] = rotateAroundXMatrix * edges[i][0];
        edges[i][1] = rotateAroundXMatrix * edges[i][1];
    }
}


void Cube::rotateAroundY(float phi)
{
    rotateAroundYMatrix(0,0) = cos(phi);
    rotateAroundYMatrix(0,2) = sin(phi);
    rotateAroundYMatrix(2,0) = -sin(phi);
    rotateAroundYMatrix(2,2) = cos(phi);

    for (int i = 0; i < edges.size(); i++)
    {
        edges[i][0] = rotateAroundYMatrix * edges[i][0];
        edges[i][1] = rotateAroundYMatrix * edges[i][1];
    }
}




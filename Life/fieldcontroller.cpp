#include "fieldcontroller.h"

#include <iostream>

FieldController::CubeCoordinate
FieldController::offsetToCube( const FieldController::OffsetCoordinate &coordinate )
{
    int x = coordinate.column - (coordinate.row  - (coordinate.row % 2)) / 2;
    int z = coordinate.row;
    int y = -x - z;

    return CubeCoordinate(x,y,z);
}

FieldController::OffsetCoordinate
FieldController::cubeToOffset( const FieldController::CubeCoordinate &coordinate )
{
    int col = coordinate.x + (coordinate.z - (coordinate.z % 2)) / 2;
    int row = coordinate.z;

    return OffsetCoordinate(col, row);
}

int FieldController::getAliveCellsCount()
{
    int result = 0;
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            result += getCell(i,j).isAlive();
        }
    }

    return result;
}

void FieldController::resize(int width_, int height_)
{
    std::vector<Cell> prevPoligons = poligons;
    poligons.resize(0);

    for (int j = 0; j < height_; j++)
    {
        for (int i = 0; i < width_; i++)
        {
           poligons.push_back(Cell(OffsetCoordinate(i,j),this));
           if ((i < width) && (j < height))
           {
               poligons[j * width_ + i].setAlive(prevPoligons[j * width + i].isAlive());
           }
        }
    }
    width = width_;
    height = height_;
}

void FieldController::newSize(int width_, int height_)
{
    width = width_;
    height = height_;
    poligons.resize(0);
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            poligons.push_back(Cell(OffsetCoordinate(i,j),this));
        }
    }
}

void FieldController::Cell::refreshState()
{
    if ( alive )
    {
        if ( !(nextImpact >= parent->LIFE_BEGIN && nextImpact <= parent->LIFE_END) )
        {
            alive = false;
        }
    }
    else
    {
        if ( nextImpact >= parent->BIRTH_BEGIN && nextImpact <= parent->BIRTH_END )
        {
            alive = true;
        }
    }

    impact = nextImpact;

}

FieldController::Cell& FieldController::getCell( OffsetCoordinate coordinate )
{
    return getCell(coordinate.column, coordinate.row);
}

FieldController::Cell& FieldController::getCell( int i, int j )
{
    if ( i < 0 )
    {
        i += width;
    }
    if ( j < 0 )
    {
        j+= height;
    }
    j %= height;
    i %= width;

    return poligons[j * width + i];
}

void FieldController::countImpact( Cell &input_cell )
{
    OffsetCoordinate cell_location = input_cell.getLocation();
    float first_impact = 0;
    float second_impact = 0;

    if ( input_cell.getLocation().row % 2 )
    {
        first_impact += getCell(cell_location.column - 1, cell_location.row).isAlive();
        first_impact += getCell(cell_location.column + 1, cell_location.row).isAlive();
        first_impact += getCell(cell_location.column, cell_location.row + 1).isAlive();
        first_impact += getCell(cell_location.column, cell_location.row - 1).isAlive();
        first_impact += getCell(cell_location.column + 1, cell_location.row + 1).isAlive();
        first_impact += getCell(cell_location.column + 1, cell_location.row - 1).isAlive();

        second_impact += getCell(cell_location.column + 2, cell_location.row + 1).isAlive();//
        second_impact += getCell(cell_location.column, cell_location.row + 2).isAlive();
        second_impact += getCell(cell_location.column - 1, cell_location.row + 1).isAlive();//
        second_impact += getCell(cell_location.column - 1, cell_location.row - 1).isAlive();//
        second_impact += getCell(cell_location.column, cell_location.row  - 2).isAlive();//
        second_impact += getCell(cell_location.column + 2, cell_location.row - 1).isAlive();//
    }
    else
    {
        first_impact += getCell(cell_location.column - 1, cell_location.row).isAlive();//
        first_impact += getCell(cell_location.column + 1, cell_location.row).isAlive();//
        first_impact += getCell(cell_location.column, cell_location.row + 1).isAlive();
        first_impact += getCell(cell_location.column, cell_location.row - 1).isAlive();
        first_impact += getCell(cell_location.column - 1, cell_location.row + 1).isAlive();
        first_impact += getCell(cell_location.column - 1, cell_location.row - 1).isAlive();

        second_impact += getCell(cell_location.column, cell_location.row + 2).isAlive();
        second_impact += getCell(cell_location.column - 2, cell_location.row - 1).isAlive();
        second_impact += getCell(cell_location.column - 2, cell_location.row + 1).isAlive();
        second_impact += getCell(cell_location.column + 1, cell_location.row + 1).isAlive();//
        second_impact += getCell(cell_location.column, cell_location.row  - 2).isAlive();
        second_impact += getCell(cell_location.column + 1, cell_location.row - 1).isAlive();
    }


    input_cell.setImpact(first_impact * FST_IMPACT + second_impact * SCD_IMPACT);
}

void FieldController::countImpact()
{
    for( auto elem : poligons )
    {
        countImpact(elem);
    }

}

void FieldController::nextItaration()
{
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            countImpact(getCell(i,j));
        }
    }

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            getCell(i,j).refreshState();
        }
    }
}

void FieldController::clear()
{
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            getCell(i,j).setAlive(false);
        }
    }


}

#include "fieldwriter.h"

int FieldWriter::loadSize()
{
    int width = fieldCtl->getWidth();
    int height = fieldCtl->getHeight();

    stream << width << " " << height << std::endl;
    return LOADER_CORRECT;
}

int FieldWriter::loadPoligonSize()
{
    stream << drawArea->getPoligonSize() << std::endl;
    return LOADER_CORRECT;
}

int FieldWriter::loadAliveCellsAmount()
{
    return fieldCtl->getAliveCellsCount();
}

int FieldWriter::loadAliveCells( int aliveCells )
{
    stream << aliveCells << std::endl;

    for (int j = 0; j < fieldCtl->getHeight(); j++)
    {
        for (int i = 0; i < fieldCtl->getWidth(); i++)
        {
            if ( fieldCtl->getCell(i,j).isAlive() )
            {
                FieldController::OffsetCoordinate currentLocation = fieldCtl->getCell(i,j).getLocation();
                stream << currentLocation.row << " " << currentLocation.column << std::endl;
            }
        }
    }
    return LOADER_CORRECT;
}

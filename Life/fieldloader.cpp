#include "fieldloader.h"
#include <iostream>

int FieldLoader::loadField( std::string file_path )
{
    initStream(file_path);
    std::cout << "Loading start" << std::endl;
    if ( LOADER_ERROR == loadSize() )
    {
        return LOADER_ERROR;
    }

    if ( LOADER_ERROR == loadPoligonSize() )
    {
        return LOADER_ERROR;
    }

    int aliveCells = 0;

    if ( LOADER_ERROR == (aliveCells = loadAliveCellsAmount()) )
    {
        return LOADER_ERROR;
    }

    if ( LOADER_ERROR == loadAliveCells(aliveCells) )
    {
        return LOADER_ERROR;
    }

    std::cout << "Loading stop" << std::endl;

    return LOADER_CORRECT;
}


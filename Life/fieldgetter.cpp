#include "fieldgetter.h"

#include <iostream>

FieldGetter::TwoDigits FieldGetter::getTwoDigits()
{
    std::string line;
    if (!std::getline(stream, line))
    {
        std::cout << "Failed to read" << std::endl;
    }

    std::string width_string;
    std::string height_string;
    int breakPoint = 0;

    for (int i = 0; i < line.size(); i++)
    {
        if ((line[i] <= '9') && (line[i] >= '0'))
        {
            continue;
        }
        else if ( ' ' == line[i] )
        {
            breakPoint = i;
            width_string.append(line, 0, i);
            break;
        }
        else
        {
            return {.x = -1, .y = -1};
        }
    }

    breakPoint++;

    for (int i = breakPoint; i < line.size(); i++)
    {
        if ((line[i] <= '9') && (line[i] >= '0'))
        {
            continue;
        }
        else
        {
            if ( i == breakPoint )
            {
                return {.x = -1, .y = -1};
            }
            height_string.append(line, breakPoint, i - breakPoint);

            break;
        }
    }

    if ( height_string == "" )
    {
        height_string.append(line, breakPoint, line.size() + 1 - breakPoint);
    }

    TwoDigits result = { .x = stoi(width_string), .y = stoi(height_string) };
    return result;
}

int FieldGetter::loadSize()
{
    TwoDigits result = getTwoDigits();
    if ( result.x == -1 )
    {
        return LOADER_ERROR;
    }

    fieldCtl->newSize(result.x, result.y);
    return LOADER_CORRECT;
}

int FieldGetter::loadPoligonSize()
{
    std::string line;
    std::getline(stream,line);
    drawArea->setPoligonSize(stoi(line));
    return LOADER_CORRECT;
}

int FieldGetter::loadAliveCellsAmount()
{
    std::string line;
    std::getline(stream, line);
    return stoi(line);
}

int FieldGetter::loadAliveCells( int aliveCells )
{
    std::string line;
    TwoDigits result;

    for (int i = 0; i < aliveCells; i++)
    {
        result = getTwoDigits();
        fieldCtl->getCell(result.y, result.x).setAlive(true);
    }

    return LOADER_CORRECT;
}

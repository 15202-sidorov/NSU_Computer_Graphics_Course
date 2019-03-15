#ifndef FIELDLOADER_H
#define FIELDLOADER_H

#include "fieldcontroller.h"
#include "drawarea.h"

#include <string>

class FieldLoader
{

public:

    inline FieldLoader (DrawArea *drawArea) : drawArea(drawArea)
    {
        fieldCtl = drawArea->getField();
    }

    virtual int loadField (std::string file_path);

    virtual ~FieldLoader() {}

    static const int LOADER_ERROR   = -1;
    static const int LOADER_CORRECT =  0;

protected:
    virtual void initStream           (std::string file_path) = 0;
    virtual int  loadSize             () = 0;
    virtual int  loadPoligonSize      () = 0;
    virtual int  loadAliveCellsAmount () = 0;
    virtual int  loadAliveCells       (int aliveCells) = 0;

    FieldController *fieldCtl;
    DrawArea *drawArea;
};

class FieldGetter;
class FieldWriter;

#endif // FIELDLOADER_H

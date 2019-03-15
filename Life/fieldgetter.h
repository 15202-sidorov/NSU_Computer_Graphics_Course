#ifndef FIELDGETTER_H
#define FIELDGETTER_H

#include "fieldloader.h"
#include <fstream>
#include <iostream>

class FieldGetter : public FieldLoader
{
public:
    inline FieldGetter(DrawArea *drawArea) : FieldLoader(drawArea) {}
    inline ~FieldGetter () { if ( stream.is_open() ) { stream.close(); } }

private:
    std::ifstream stream;

    typedef struct
    {
        int x;
        int y;
    } TwoDigits;

    inline
    void initStream          (std::string file_path) override { stream.open(file_path); }

    int loadSize             () override;
    int loadPoligonSize      () override;
    int loadAliveCellsAmount () override;
    int loadAliveCells       (int aliveCells) override;

    TwoDigits getTwoDigits();

};

#endif // FIELDGETTER_H

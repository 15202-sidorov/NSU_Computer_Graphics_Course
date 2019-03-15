#ifndef FIELDWRITER_H
#define FIELDWRITER_H

#include "fieldloader.h"
#include <fstream>

class FieldWriter : public FieldLoader
{
public:
    inline FieldWriter(DrawArea *drawArea) : FieldLoader(drawArea) {}
    inline ~FieldWriter() { if ( stream.is_open() ) { stream.close(); }  }

private:
    std::ofstream stream;

    inline void initStream (std::string file_path) override { stream.open(file_path); }

    int loadSize             () override;
    int loadPoligonSize      () override;
    int loadAliveCellsAmount () override;
    int loadAliveCells       (int aliveCells) override;
};

#endif // FIELDWRITER_H

#ifndef FIELDCONTROLLER_H
#define FIELDCONTROLLER_H

#include <vector>

class FieldController
{

public:
    FieldController(int width_ = DEFAULT_WIDTH, int height_ = DEFAULT_HEIGHT) :
                    width(width_), height(height_)
    {
        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++)
            {
                poligons.push_back(Cell(OffsetCoordinate(i,j),this));
            }
        }
    }

    struct OffsetCoordinate
    {
        OffsetCoordinate(int x, int y) : column(x), row(y) {}
        inline friend bool operator==(const OffsetCoordinate &c1, const OffsetCoordinate &c2)
        {
            return (c1.row == c2.row && c1.column == c2.column);
        }

        int column;
        int row;
    };

    struct CubeCoordinate
    {
        CubeCoordinate (int x_, int y_, int z_) : x(x_), y(y_), z(z_) {}
        int x;
        int y;
        int z;
    };

    class Cell
    {
    public: 
        Cell() {}
        Cell (const OffsetCoordinate &coordinate, const FieldController *parent_ptr):
            location(coordinate), parent(parent_ptr){}

        inline void  setImpact  (float inc) { nextImpact = inc; }
        inline float getImpact  () { return impact; }
        inline float getNextImpact() { return nextImpact; }
        inline bool  isAlive    () { return alive; }
        inline void  setAlive   (bool status) { alive = status; }
        inline OffsetCoordinate &getLocation () { return location; }

        void refreshState ();

    private:
        OffsetCoordinate location = OffsetCoordinate(0,0);
        float impact = 0;
        float nextImpact = 0;
        bool alive = false;
        const FieldController *parent;
    };

    inline int    getWidth        () { return width; }
    inline int    getHeight       () { return height; }
    inline float  getLifeBegin    () { return LIFE_BEGIN; }
    inline void   setLifeBegin    (float value) { LIFE_BEGIN = value; }
    inline float  getLifeEnd      () { return LIFE_END; }
    inline void   setLifeEnd      (float value) { LIFE_END = value; }
    inline float  getBirthBegin   () { return BIRTH_BEGIN; }
    inline void   setBrithBegin   (float value) { BIRTH_BEGIN = value;}
    inline float  getBirthEnd     () { return BIRTH_END; }
    inline void   setBirthEnd     (float value) { BIRTH_END = value; }
    inline float  getFstImpact    () { return FST_IMPACT; }
    inline void   setFstImpact    (float value) { FST_IMPACT = value; }
    inline float  getScdImpact    () { return SCD_IMPACT; }
    inline void   setScdImpact    (float value) { SCD_IMPACT = value; }


    Cell& getCell        (int i, int j);
    Cell& getCell        (OffsetCoordinate coordinate);

    void  resize        (int width, int height);
    void  newSize       (int width, int height);
    void  countImpact   (Cell &input_cell);
    void  countImpact   ();
    void  nextItaration ();
    void  clear();
    int   getAliveCellsCount();


    static CubeCoordinate   offsetToCube (const OffsetCoordinate &coordinate);
    static OffsetCoordinate cubeToOffset (const CubeCoordinate   &coordinate);

protected:
    static const int DEFAULT_WIDTH  = 20;
    static const int DEFAULT_HEIGHT = 13;

    float LIFE_BEGIN  = 2.0;
    float LIFE_END    = 3.3;
    float BIRTH_BEGIN = 2.3;
    float BIRTH_END   = 2.9;
    float FST_IMPACT  = 1.0;
    float SCD_IMPACT  = 0.3;

    int width = DEFAULT_WIDTH;
    int height = DEFAULT_HEIGHT;

    std::vector<Cell> poligons;
};

#endif // FIELDCONTROLLER_H

#ifndef CMAP_H
#define CMAP_H

struct SMapTile
{
    bool passable;
    int tileID;
};

class CMap
{
    public:
        CMap(int w,int h);
        CMap(const char* file_name);
        virtual ~CMap();

        SMapTile* getMapTile(unsigned int x,unsigned int y);
        void setMapTile(unsigned int x,unsigned int y,SMapTile tile);

    protected:
    private:
        unsigned int MapWidth;
        unsigned int MapHeight;
        SMapTile* Map;
};

#endif // CMAP_H

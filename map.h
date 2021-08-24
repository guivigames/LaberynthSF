#pragma onece
#ifndef MAP_H
#define MAP_H

#include <string>
#include "TextureManager.h"
#include <SFML/Graphics.hpp>

enum TileType 
{
    Horyzontal = 0, 
    Vertical,
    TRight,
    TLeft,
    TUp,
    TDown,
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight
};

class Tiles
{
private:
    std::string m_tiles;
    void SetHoryzontal();
    void SetVertical();
    void SetTRight();
    void SetTLeft();
    void SetTUp();
    void SetTDown();
    void SetTopLeft();
    void SetTopRight();
    void SetBottomLeft();
    void SetBottomRight();
public:
    Tiles();
    ~Tiles();
    void Set(TileType type);
    std::string GetTiles();
    char GetTile(int x, int y);
};


// Each icon is 16 by 16 pixels. Each tile will be 48 by 48 pixels.
// Making a map of 10 by 10 tyles will be a 480 by 480 piexels.

class GameMap
{
private:
    int m_width = 10;
    int m_height =10;
    int m_totalwidth = 30;
    int m_totalheight = 30;
    Tiles* m_tiles;
    std::string m_map;
    sf::Sprite m_MapStrip[900];
public:
    GameMap();
    ~GameMap();
    int GetTotalWidth(){return m_totalwidth;};
    int GetTotalHeigt(){return m_totalheight;};
    sf::Sprite& GetStripe(int x, int y);
    char GetTile(int x, int y);
};

#endif
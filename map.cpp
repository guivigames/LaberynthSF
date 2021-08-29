#include "map.h"
#include <iostream>

/// TILES MEMBER FUNCTIONS /////////////////////////
void Tiles::SetHoryzontal(){m_tiles = "###XXX###";};
void Tiles::SetVertical(){  m_tiles = "#X##X##X#";};
void Tiles::SetTRight(){    m_tiles = "#X##XX#X#";};
void Tiles::SetTLeft(){     m_tiles = "#X#XX##X#";};
void Tiles::SetTUp(){       m_tiles = "#X#XXX###";};
void Tiles::SetTDown(){     m_tiles = "###XXX#X#";};
void Tiles::SetTopLeft(){   m_tiles = "####XX#X#";};
void Tiles::SetTopRight(){  m_tiles = "###XX##X#";};
void Tiles::SetBottomLeft(){m_tiles = "#X##XX###";};
void Tiles::SetBottomRight(){m_tiles = "#X#XX####";};
Tiles::Tiles(){}
Tiles::~Tiles(){}
void Tiles::Set(TileType type)
{
    switch(type){
        case Horyzontal:
            SetHoryzontal();
        break;
        case Vertical:
            SetVertical();
        break;
        case TRight:
            SetTRight();
        break;
        case TLeft:
            SetTLeft();
        break;
        case TUp:
            SetTUp();
        break;
        case TDown:
            SetTDown();
        break;
        case TopLeft:
            SetTopLeft();
        break;
        case TopRight:
            SetTopRight();
        break;
        case BottomLeft:
            SetBottomLeft();
        break;
        case BottomRight:
            SetBottomRight();
        break;
        default:
            SetTopLeft();
    }
}
std::string Tiles::GetTiles(){return m_tiles;};
char Tiles::GetTile(int x, int y)
{
    if (x < 3 && y < 3)
        return m_tiles[ (3 * y) + x];
    else return '?';
}

/// MAP MEMBER FUNCTIONS ///////////////////////////
GameMap::GameMap()
{
    m_width     = 9;
    m_height    = 9;
    m_totalwidth    = m_width*3;
    m_totalheight   = m_height*3;
    m_pxWidth   = m_width * 16;     ///< Width of the map in pixels
    m_pxHeight  = m_height *16;     ///< height of the map in piels
    
    
    CreateTiles();
    CreateMap();
}

GameMap::~GameMap()
{
    delete [] m_tiles;
}

void GameMap::CreateTiles()
{
    srand(time(nullptr));
    
    m_tiles = new Tiles[m_width * m_height];

    for (int i = 0; i < m_width * m_height; i++){
        m_tiles[i].Set( (TileType)(rand() % 10));
    }
}

void GameMap::CreateMap()
{
    m_map = "";

    for (int h = 0; h < m_height; h++){
        for (int y = 0; y < 3; y++){
            for (int w = 0; w < m_width; w++){
                for (int x = 0; x < 3; x++){
                    m_map += m_tiles[(h * m_width) + w].GetTile(x, y);
                    m_MapStrip[m_map.size()-1].setTexture(TextureManager::GetTexture("maps.png"));
                    if (m_tiles[(h * m_width) + w].GetTile(x, y) == '#'){
                        m_MapStrip[m_map.size()-1].setTextureRect(sf::IntRect(16, 16, 16, 16));
                        //printf("wall\r\n");
                    }
                    else {
                        m_MapStrip[m_map.size()-1].setTextureRect(sf::IntRect( 0, 32, 16, 16));
                         //printf("Path\r\n");
                    }
                }
            }
        }
    }
}

sf::Sprite&  GameMap::GetStripe(int x, int y)
{
    return m_MapStrip[ (y * m_totalwidth) + x];
}

char GameMap::GetTile(int x, int y)
{
    if (x < m_totalwidth && x < m_totalheight)
    {
        return m_map[(y * m_totalwidth) + x];
    }
    else return '?';
}
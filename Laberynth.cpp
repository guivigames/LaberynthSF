#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <memory>
#include "TextureManager.h"
#include "map.h"

TextureManager g_textureManager;

const float fps = 60;
const float period = 1000000/fps;
const int width = 800;
const int height = 600;
const float radius = 8;

// CIRCLE/RECTANGLE
bool circleRect(float cx, float cy, float rad, float rx, float ry, float rw, float rh) 
{
  // temporary variables to set edges for testing
  float testX = cx;
  float testY = cy;

  // which edge is closest?
  if (cx < rx)         testX = rx;      // test left edge
  else if (cx > rx+rw) testX = rx+rw;   // right edge
  if (cy < ry)         testY = ry;      // top edge
  else if (cy > ry+rh) testY = ry+rh;   // bottom edge

  // get distance from closest edges
  float distX = cx-testX;
  float distY = cy-testY;
  float distance = sqrt( (distX*distX) + (distY*distY) );

  // if the distance is less than the radius, collision!
  if (distance+0.01 < rad) {
    return true;
  }
  return false;
}
// CIRCLE/CIRCLE
bool circleCircle(float c1x, float c1y, float c1r, float c2x, float c2y, float c2r) {

  // get distance between the circle's centers
  // use the Pythagorean Theorem to compute the distance
  float distX = c1x - c2x;
  float distY = c1y - c2y;
  float distance = sqrt( (distX*distX) + (distY*distY) );

  // if the distance is less than the sum of the circle's
  // radii, the circles are touching!
  if (distance <= c1r+c2r) {
    return true;
  }
  return false;
}

struct player
{
    sf::Vector2f m_vPos;
    sf::Vector2f m_vVel;
    float fRadius = 0.5;
};

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode( 800, 600), "Laberynth");
    sf::Text text;
    sf::Font font;
    font.loadFromFile("Pacifico.ttf");
    text.setFont(font);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);

    
    sf::Clock timer;
    sf::Clock gameTime;

    GameMap *_map = new GameMap();
    sf::ConvexShape _arrows[4][5];
    player _playerOne;
    sf::Vector2f _scale = {16.0f, 16.0f};
    sf::Vector2f _mapOffest = {40.0, 40.0};

    ///< Arrow positions.
    {
        int row = _scale.y*3;
        int halfrow = _scale.y+(_scale.y/2);
        _arrows[0][0].setPointCount(3);
        _arrows[0][0].setPoint(0, sf::Vector2f( 10.0, _mapOffest.y+row));
        _arrows[0][0].setPoint(1, sf::Vector2f( 30.0, _mapOffest.y+row+halfrow));
        _arrows[0][0].setPoint(2, sf::Vector2f( 10.0, _mapOffest.y+(2*row)));
        _arrows[0][0].setFillColor(sf::Color::Green);
    }
    ///< Player Initial position.
    _playerOne.m_vPos = sf::Vector2f(1.0+_playerOne.fRadius, 1.0+_playerOne.fRadius);

    int score = 0;
    while (window.isOpen())
    {
        /// Event Haneling
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            delete _map;
            _map = new GameMap();
            _playerOne.m_vPos = sf::Vector2f(1.0+_playerOne.fRadius, 1.0+_playerOne.fRadius);
            sf::sleep(sf::microseconds(500));
        }

        /// Control Player Oject
        sf::Time dt = timer.restart();  ///< Frame rate controller.
        _playerOne.m_vVel = {0.0, 0.0};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) _playerOne.m_vVel += {  0.0f, -1.0f};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) _playerOne.m_vVel += {  0.0f,  1.0f};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _playerOne.m_vVel += { -1.0f,  0.0f};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _playerOne.m_vVel += {  1.0f,  0.0f};

        /// Where will object be
        sf::Vector2f vPotentilPos;
        vPotentilPos.x = _playerOne.m_vPos.x + _playerOne.m_vVel.x * 5 * dt.asSeconds();
        vPotentilPos.y = _playerOne.m_vPos.y + _playerOne.m_vVel.y * 5 * dt.asSeconds();
        
        /*bool moveFlag = true;
        if (_playerOne.m_vVel.x != 0 || _playerOne.m_vVel.y != 0){
            for (int y = 0; y <= 1; y++){
                for (int x = 0; x <= 1; x++){
                    int rx =  floor((vPotentilPos.x) + (x));
                    int ry = floor((vPotentilPos.y) + (y));
                    int pox = floor(rx);
                    int poy = floor(ry);
                    if (pox >= 0 && poy >= 0){
                        char cr =_map.GetTile( pox, poy);
                        if (cr == '#'){
                            if (circleRect( vPotentilPos.x + _playerOne.fRadius, vPotentilPos.y + _playerOne.fRadius, _playerOne.fRadius,
                                            rx, ry, 1.0, 1.0))
                            {
                                moveFlag = false;
                                printf("%f\t%f--%d\t%d\r\n", vPotentilPos.x, vPotentilPos.y, pox, poy);
                                //vPotentilPos = _playerOne.m_vPos;
                            } 
                        }
                    }
                }
            }
            if (moveFlag) {
                if (vPotentilPos.x > 0 && vPotentilPos.x < 30)
                    _playerOne.m_vPos.x = vPotentilPos.x;
                if (vPotentilPos.y > 0 && vPotentilPos.y < 30)
                    _playerOne.m_vPos.y = vPotentilPos.y;
                printf("%f\t%f--%d\r\n", vPotentilPos.x, vPotentilPos.y, moveFlag);
            }
        }*/

        sf::Vector2i currentCell = {floor(_playerOne.m_vPos.x), floor(_playerOne.m_vPos.y)};
        sf::Vector2i targetCell = {floor(vPotentilPos.x), floor(vPotentilPos.y)};
        sf::Vector2i vAreaTL = {std::max( std::min(currentCell.x, targetCell.x)-1, 0), 
                                std::max( std::min(currentCell.y, targetCell.y)-1, 0)};
        sf::Vector2i vAreaBR = {std::min( std::max(currentCell.x, targetCell.x)+1, 30), 
                                std::min( std::max(currentCell.y, targetCell.y)+1, 30)};
        sf::Vector2f vRayToNearest;
        sf::Vector2i vCell;

        for (vCell.y = vAreaTL.y; vCell.y <= vAreaBR.y; vCell.y++){
            for (vCell.x = vAreaTL.x; vCell.x <= vAreaBR.x; vCell.x++){
                char cr =_map->GetTile( vCell.x, vCell.y);
                if (cr == '#'){
                    sf::Vector2f vNearestPoint;
                    vNearestPoint.x = std::max( (float)vCell.x, std::min(vPotentilPos.x, (float)vCell.x+1));
                    vNearestPoint.y = std::max( (float)vCell.y, std::min(vPotentilPos.y, (float)vCell.y+1));

                    sf::Vector2f vRayToNearest = vNearestPoint - vPotentilPos;
                    float fMag = pow(pow(vRayToNearest.x, 2)+pow(vRayToNearest.y, 2), 0.5);
                    float fOverlap = _playerOne.fRadius - fMag;
                    if (std::isnan(fOverlap)) fOverlap = 0;
                    if (fOverlap > 0)
                    {
                        vPotentilPos.x = vPotentilPos.x - (vRayToNearest.x/fMag)*fOverlap;
                        vPotentilPos.y = vPotentilPos.y - (vRayToNearest.y/fMag)*fOverlap;
                    }
                }
            }
        }
        if (vPotentilPos.x > 0 && vPotentilPos.x < 30)
            _playerOne.m_vPos.x = vPotentilPos.x;// - _playerOne.fRadius;
        if (vPotentilPos.y > 0 && vPotentilPos.y < 30)
            _playerOne.m_vPos.y = vPotentilPos.y;//- _playerOne.fRadius;
        ///< Draw Everyting.
        window.clear();
        
        for (int y = 0; y < 30; y++){
            for (int x = 0; x < 30; x++){
                auto& sprite = _map->GetStripe(x, y);
                sprite.setPosition(sf::Vector2f(x*_scale.x, y*_scale.y)+_mapOffest); // absolute position
                window.draw(sprite);
            }
        }

        /// Draw player
        sf::CircleShape _circl;
        _circl.setRadius(_playerOne.fRadius*_scale.x);
        _circl.setPosition(sf::Vector2f((_playerOne.m_vPos.x-_playerOne.fRadius)*_scale.x,
                            (_playerOne.m_vPos.y-_playerOne.fRadius)*_scale.y) +_mapOffest);
        _circl.setFillColor(sf::Color::Red);
        window.draw(_circl);
        
        window.draw(_arrows[0][0]);

        window.display();
        
    }
    return 0;
}


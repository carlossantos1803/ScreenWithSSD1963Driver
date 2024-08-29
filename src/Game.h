#pragma once

#include "defines.h"
#include <vector>
#include <cmath>
#include "GT911.h"

/*struct AShape
{
  String name;
  Vec2 velocity;
  Vec2 pos;
  Vec2 oldPos;
  int32_t color;
  float mass;  
  int32_t id;
  AShape(String _name, int32_t _id, Vec2 _pos, Vec2 _velocity, int32_t _color, int32_t _mass) :
  name(_name), id(_id), pos(_pos), velocity(_velocity), color(_color), mass(_mass)
  {}
};*/

struct CircleObject
{
  String name;
  Vec2 velocity;
  Vec2 pos;
  Vec2 oldPos;
  int32_t color;
  int32_t mass;  
  int32_t id;
  float radius;
  float changePos = false;
	
  CircleObject();
  CircleObject(String _name, int32_t _id, Vec2 _pos, Vec2 _velocity, int32_t _color, float _radius, int32_t _mass):
  name(_name), id(_id), pos(_pos), velocity(_velocity), color(_color), mass(_mass), radius(_radius)
  {}
  
  CircleObject(String _name, int32_t _id, Vec2 _pos, Vec2 _velocity, int32_t _color, float _radius):
  name(_name), id(_id), pos(_pos), velocity(_velocity), color(_color)
  {
	Serial.println("building ball");
    mass = radius;
  }
  
};

/*struct TextObject
{
  String name;
  Vec2 pos;
  uint32_t fontColor;
  uint32_t backColor;
  int32_t data;
  String msg = " ";
  TextObject(String _name, Vec2 _pos, uint32_t _fontColor, uint32_t _backColor, String _msg) : name(_name), pos(_pos), fontColor(_fontColor), backColor(_backColor), msg(_msg)
  {}

}*/

class Game : public TFT_eSPI, public GT911
{
    int width, height;
    std::vector<CircleObject> circles;
    //std::vector<TextObject> texts;
    int map_float_to_int(const float value = 10);
    void overlappingCorrection(CircleObject& a, CircleObject& b);
    uint32_t end_time, end_time_2, framesPerSeconds, elapsedTime, fps;
    /*
    In C++, a static data member is a class variable that is shared by all objects of the class, rather than being unique to each object.
    */
    static bool istouch;
    
  public:
    Game(); // : TFT_eSPI(map_float_to_int(WIDTH_SCREEN), map_float_to_int(HEIGTH_SCREEN)){}
    void Init();
    void play();
    void render();
    //void textRender();
    void addCircle(const CircleObject& c);
    void addCircle(Vec2 _pos, Vec2 _vel, uint32_t _color, float _radius, float _mass = 0);
    //void addText(const TextObject& t);
    void collisionResponse(CircleObject& a, CircleObject& b);
    void collisionResponse2(CircleObject& a, CircleObject& b);
    void collision(uint32_t elapsedTime);
    void energy();
    
    Vec2 gettouch();
    //static bool istouch;
};

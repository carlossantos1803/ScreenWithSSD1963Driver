#include "Game.h"
#include <Wire.h>

#define TOUCH_SDA      20
#define TOUCH_SCL      21
#define TOUCH_INT      22
#define TOUCH_RST      23
#define TOUCH_ADDR     0x5D

#ifndef __WIRE0_DEVICE
#define __WIRE0_DEVICE i2c0
#endif

TwoWire Wire10(__WIRE0_DEVICE, TOUCH_SDA, TOUCH_SCL);

bool Game::istouch = false;

Game::Game() : TFT_eSPI(map_float_to_int(WIDTH_SCREEN), map_float_to_int(HEIGTH_SCREEN)), GT911(Wire10, TOUCH_ADDR, TOUCH_RST, TOUCH_INT)
{}

void Game::Init()
{
  TFT_eSPI::init();
  fillScreen(BACKGROUND_COLOR);
  setRotation(1); //landscape
  setCursor(0,0);
  setTextSize(2);
  setTextColor(TFT_GREEN,TFT_BLUE);
  width = WIDTH_SCREEN;
  height = HEIGTH_SCREEN -10 ;
  
  Wire10.setClock(400000);
  Wire10.begin(); 
  gt911setup();
    
  attachInterrupt(digitalPinToInterrupt(TOUCH_INT),[](){istouch = true;}, FALLING);

  CircleObject c = {"Circle1",1,{5.0f,40.0f},{0.09f,0.0f}, TFT_YELLOW, 1.0f, 1};
  game.addCircle(c);
  c = {"Circle2",2,{45.0f,45.8f},{-0.9f,0.0f}, TFT_RED, 5.0f, 5};
  game.addCircle(c);
  c = {"Circle3",3,{3.0f,4.5f},{0.05f,-0.9f}, TFT_PURPLE, 3.0f, 3};
  game.addCircle(c);
  c = {"Circle4",4,{20.0f,4.5f},{0.8f,0.09f}, TFT_GREEN, 2.0f, 2};
  game.addCircle(c);
  c = {"Circle5",5,{30.0f,7.5f},{0.6f,0.09f}, TFT_BLUE, 6.0f, 6};
  game.addCircle(c);
  
  for(auto& a : circles)
  {
    fillCircle(map_float_to_int(a.pos.x),map_float_to_int(a.pos.y),map_float_to_int(a.radius),a.color);
  
  }
  end_time = millis() + 1000;
  end_time_2 = millis() + 200;
  framesPerSeconds = 0;
  fps = 0;
}

void Game::play()
{
  if(istouch)
  {
    Vec2 point = gettouch();
    point.printVec("Position:");
    istouch = false;
  }
  if(millis() > end_time) 
  {
    //imprimir en pantalla fps
    String frames = "fps " + String(fps);
    drawString(frames, 700, 20);
    fps = 0;
    end_time = millis() + 1000;
  }
  /*if(millis() > end_time_2)
  {
    mpu.update();
    String accAngle = "AccAngle:";
    String accAngleX = "X: " + String(mpu.getAccAngleX());
    String accAngleY = "Y: " + String(mpu.getAccAngleY());
    drawString(accAngle, 700,230);
    drawString(accAngleX, 700,250);
    drawString(accAngleY, 700,270);
    end_time_2 = millis() + 200;
  }*/
  if(millis() > framesPerSeconds)
  {
    uint32_t Start = millis();
    elapsedTime = millis() - elapsedTime;
    collision(elapsedTime);
    render(); 
    fps++;
    framesPerSeconds = millis() + 1000/FPS - (millis() - Start);
    elapsedTime = millis();
  }
   
}

void Game::addCircle(const CircleObject& c)
{
  circles.push_back(c);
}

void Game::addCircle(Vec2 _pos, Vec2 _vel, uint32_t _color, float _radius, float _mass)
{
  
  static uint16_t _id = 1;
  String name= "Circle" + _id;
  const char *_name = name.c_str();
  CircleObject c = {_name, _id, _pos, _vel, _color,_radius};
  if (_mass == 0) c.mass = _radius;  
  else c.mass = _mass;
  circles.push_back(c);
  _id++;
  Serial.printf("Creating ball %s, with radius %f",c.name,c.radius);
}

/*void Game::addText(const TextObject& t)
{

}*/

void Game::collision(uint32_t elapsedTime)
{
  for(auto& a : circles)
  {
    auto isThereOverlapping = [](CircleObject& a, CircleObject& b)
    {
      return abs((a.pos.x-b.pos.x)*(a.pos.x-b.pos.x)+(a.pos.y-b.pos.y)*(a.pos.y-b.pos.y)) <= (a.radius + b.radius)*(a.radius + b.radius);
    };
    
    a.oldPos = a.pos;
    a.pos.x = a.pos.x + a.velocity.x*elapsedTime/10.0f;
    a.pos.y = a.pos.y + a.velocity.y*elapsedTime/10.0f;
    for(auto& b : circles)
    {
      if(a.id != b.id)
      {
        if(isThereOverlapping(a,b))
        {
          //b.oldPos = b.pos;
          //b.oldPos.printVec("b.oldPos:");
          overlappingCorrection(a,b);
          collisionResponse(a,b);
          energy();
        }
      }
    }
       
    if((a.pos.x + a.radius) > height)
    {
      a.velocity.x *= -1;
      a.pos.x = height - a.radius;
    }
    else if( a.pos.x < a.radius) 
    {
      a.velocity.x *= -1;
      a.pos.x = a.radius;
    }
    else if((a.pos.y + a.radius) > width)
    {
      a.velocity.y *= -1;
      a.pos.y = width - a.radius;
    }
    else if( a.pos.y < a.radius)
    {
      a.velocity.y *= -1;
      a.pos.y = a.radius;
    }
    
  }
}

void Game::energy()
{
  float tmp, result = 0;
  for(auto& a: circles)
  {
    //String vel1 = "Vel " + a.name;
    //const char *vel = vel1.c_str(); 
    //a.velocity.printVec(vel);
    tmp = a.velocity.mag();
    tmp = a.mass*tmp*tmp*0.5;
    result += tmp;    
  }
  //DEBUG_PRINTF("Total Energy %d\n", result);
}

void Game::render()
{
  for(auto& a : circles)
  {
    //a.changePos = false;
    //Serial.printf("%d",a.id);
    //a.oldPos.printVec("renderPos:");
    fillCircle(map_float_to_int(a.oldPos.x),map_float_to_int(a.oldPos.y),map_float_to_int(a.radius),BACKGROUND_COLOR);
    //a.pos.printVec("renderPos:");
    fillCircle(map_float_to_int(a.pos.x),map_float_to_int(a.pos.y),map_float_to_int(a.radius),a.color);
  }
}
/*
void Game::textRender()
{
  for(auto& t : texts)
  {
    game.drawString(t.msg + String(t.data), t.pos.x, t.pos.y);
  }
}*/

void Game::overlappingCorrection(CircleObject& a, CircleObject& b)
{
float distance = a.pos.distance(b.pos);
float overlap = distance - (a.radius + b.radius);
Vec2 dist = a.pos - b.pos;
dist.normalize(distance);
dist *= overlap; ///2;
a.pos -= dist;
//b.pos += dist;
//b.pos.printVec("b.pos:");
//b.changePos = true;  
}

void Game::collisionResponse(CircleObject& a, CircleObject& b)
{

// Distance between balls
float fDistance = sqrtf((a.pos.x - b.pos.x)*(a.pos.x - b.pos.x) + (a.pos.y - b.pos.y)*(a.pos.y - b.pos.y));

// Normal
float nx = (b.pos.x - a.pos.x) / fDistance;
float ny = (b.pos.y - a.pos.y) / fDistance;

// Tangent
float tx = -ny;
float ty = nx;

// Dot Product Tangent
float dpTan1 = a.velocity.x * tx + a.velocity.y * ty;
float dpTan2 = b.velocity.x * tx + b.velocity.y * ty;

// Dot Product Normal
float dpNorm1 = a.velocity.x * nx + a.velocity.y * ny;
float dpNorm2 = b.velocity.x * nx + b.velocity.y * ny;

// Conservation of momentum in 1D
float m1 = (dpNorm1 * (a.mass - b.mass) + 2.0f * b.mass * dpNorm2) / (a.mass + b.mass);
float m2 = (dpNorm2 * (b.mass - a.mass) + 2.0f * a.mass * dpNorm1) / (a.mass + b.mass);

// Update ball velocities
a.velocity.x = tx * dpTan1 + nx * m1;
a.velocity.y = ty * dpTan1 + ny * m1;
b.velocity.x = tx * dpTan2 + nx * m2;
b.velocity.y = ty * dpTan2 + ny * m2;

}

void Game::collisionResponse2(CircleObject& a, CircleObject& b)
{
  float distance = a.pos.distance(b.pos);
  //float overlap =  distance - (a.radius + b.radius);
  Vec2 dist = a.pos - b.pos;
  //dist.normalize(distance);
  //dist *= overlap; ///2;
  //a.pos -= dist;
  //b.pos -= dist;
  
  //distance = a.pos.distance(b.pos);
  //dist = a.pos - b.pos;
  Vec2 Speed = a.velocity - b.velocity;
  
  float num = (2*a.mass)*(Speed.dot(dist));
  float den = (a.mass + b.mass)*(distance*distance);
  float resul = num/den;
  dist*=resul;
  b.velocity += dist;  
  
  dist = b.pos - a.pos;
  Speed *= -1;         
  num = (2*b.mass)*(Speed.dot(dist));
  resul = num/den;
  dist*=resul;
  a.velocity += dist;  

}

int Game::map_float_to_int(float value) {
    return (int)(value * 10);
}

Vec2 Game::gettouch() {
  TouchLocation touchLocations[5] = {0,0};  
  uint8_t points = readGT911TouchLocation(touchLocations,5);
  Serial.printf("Points: %d\n",points);
  return {touchLocations[0].x,touchLocations[0].y};
}



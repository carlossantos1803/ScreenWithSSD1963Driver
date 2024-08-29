#include "src/Game.h"
//#include "src/class_Touch_GT911.h"
//#include <MPU6050_light.h>
//#include <Wire.h>
/*
#define TOUCH_SDA      20
#define TOUCH_SCL      21

#ifndef __WIRE0_DEVICE
#define __WIRE0_DEVICE i2c0
#endif

TwoWire Wire10(__WIRE0_DEVICE, TOUCH_SDA, TOUCH_SCL);
*/
/*#include "src/defines.h"
#include <vector>
#include <cmath>

struct AShape
{
  String name;
  Vec2 velocity;
  Vec2 pos;
  Vec2 oldPos;
  int32_t color;
  int32_t mass;  
  int32_t id;
  AShape(String _name, int32_t _id, Vec2 _pos, Vec2 _velocity, int32_t _color, int32_t _mass) :
  name(_name), id(_id), pos(_pos), velocity(_velocity), color(_color), mass(_mass)
  {}
};

struct CircleObject : AShape
{
  float radius;

  CircleObject(String _name, int32_t _id, Vec2 _pos, Vec2 _velocity, int32_t _color, float _radius, int32_t _mass):
  AShape(_name, _id, _pos, _velocity, _color, _mass), radius(_radius)
  {}
  
};


class Game : public TFT_eSPI 
{
    std::vector<CircleObject> circles;
    int map_float_to_int(const float value = 10);
    void overlappingCorrection(CircleObject& a, CircleObject& b);
    
  public:
    Game() : TFT_eSPI(map_float_to_int(WIDTH_SCREEN), map_float_to_int(HEIGTH_SCREEN)){}
    void Init();
    void play();
    void render();
    void addCircle(const CircleObject& c);
    void collision();
    void energy();
};
*/

/*
void gpio_callback(uint8_t gpio, uint32_t event)
{
  printf("GPIO %d triggered with event %d\n",gpio, event);
}

void blinking()
{
  //Serial.printf("data register: 0x%x\n\r",cpu->dataRegister);
  digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN)?LOW:HIGH);
}*/

//void i2cscanner();
//Ticker blinkLed(blinking,1000);
Game game;
uint32_t end_time, end_time_2,framesPerSeconds,fps, Start;
uint32_t elapsedTime;

//MPU6050 mpu(Wire10);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial);
  DEBUG_PRINT("Show Game\n");

  //Wire10.begin();
  //touch.gt911setup();
  
  //i2cscanner();

  /*byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(true,true); // gyro and accelero
  Serial.println("Done!\n");
  */
  pinMode(LED_BUILTIN, OUTPUT);
//  blinkLed.start();
  
  //attachInterrupt(digitalPinToInterrupt(TOUCH_INT), checkfortouch, RISING);
  //gpio_set_irq_enabled_with_callback(TOUCH_INT, GPIO_IRQ_EDGE_RISE, true, gpio_callback);  )

  
  
  /*CircleObject c("Circle1",1,{24.0f,3.5f},{0.0f,-0.3f}, TFT_RED, 3.0f, 35);
  game.addCircle(c);
  c = {"Circle2",2,{24.0f,70.0f},{0.0f,-0.5f}, TFT_PURPLE, 3.0f, 35};
  game.addCircle(c);*/
  
  /*CircleObject c = {"Circle1",1,{50,400},{5,0}, TFT_YELLOW, 30, 35};
  game.addCircle(c);
  c = {"Circle2",2,{450,400},{-7,0}, TFT_BLUE, 30, 25};
  game.addCircle(c);*/
  /*  
  CircleObject c = {"Circle1",1,{5.0f,40.0f},{0.09f,0.0f}, TFT_YELLOW, 1.0f, 1};
  game.addCircle(c);
  c = {"Circle2",2,{45.0f,45.8f},{-0.9f,0.0f}, TFT_RED, 5.0f, 5};
  game.addCircle(c);
  c = {"Circle3",3,{3.0f,4.5f},{0.05f,-0.9f}, TFT_PURPLE, 3.0f, 3};
  game.addCircle(c);
  c = {"Circle4",4,{20.0f,4.5f},{0.8f,0.09f}, TFT_GREEN, 2.0f, 2};
  game.addCircle(c);
  c = {"Circle5",5,{20.0f,4.5f},{0.8f,0.09f}, TFT_BLUE, 6.0f, 6};
  game.addCircle(c);
  */
  /*CircleObject c = {"Circle1",1,{5.0f,40.0f},{0.09f,0.0f}, TFT_YELLOW, 1.0f, 1};
  game.addCircle(c);
  c = {"Circle2",2,{45.0f,45.8f},{-0.9f,0.0f}, TFT_RED, 5.0f, 5};
  game.addCircle(c);
  c = {"Circle3",3,{3.0f,4.5f},{0.05f,-0.9f}, TFT_PURPLE, 3.0f, 3};
  game.addCircle(c);
  c = {"Circle4",4,{20.0f,4.5f},{0.8f,0.09f}, TFT_GREEN, 2.0f, 2};
  game.addCircle(c);
  c = {"Circle5",5,{30.0f,7.5f},{0.6f,0.09f}, TFT_BLUE, 6.0f, 6};
  game.addCircle(c);*/
  
  //game.addCircle({5.0f,40.0f},{0.09f,0.0f}, TFT_YELLOW, 1.0f);
  /*
  game.addCircle({45.0f,45.8f},{-0.9f,0.0f}, TFT_RED, 5.0f);
  game.addCircle({3.0f,4.5f},{0.05f,-0.9f}, TFT_PURPLE, 3.0f,15);
  game.addCircle({20.0f,4.5f},{0.8f,0.09f}, TFT_GREEN, 2.0f);
  game.addCircle({50.0f,4.5f},{0.8f,0.09f}, TFT_BLUE, 6.0f);
  game.addCircle({30.0f,14.5f},{0.8f,0.09f}, TFT_ORANGE, 1.5f);
  */
  /*c = {"Circle4",4,{20.0f,4.5f},{0.8f,0.09f}, TFT_GREEN, 2.0f, 2};
  game.addCircle(c);*/
  /*CircleObject c = {"Circle1",1,{40,40},{6,7}, TFT_YELLOW, 30, 1};
  game.addCircle(c);
  c = {"Circle2",2,{400,400},{-15,-9}, TFT_BLUE, 30, 1};
  game.addCircle(c);
  c = {"Circle3",3,{30,45},{5,-9}, TFT_BLUE, 30, 1};
  game.addCircle(c);
  c = {"Circle4",4,{200,45},{10,9}, TFT_BLUE, 30, 1};
  game.addCircle(c);
  c = {"Circle5",5,{40,200},{15,9}, TFT_BLUE, 30, 1};
  game.addCircle(c);
  *//*CircleObject c = {"Circle2",{450,700},{1,-2}, TFT_YELLOW, 30, 15};
  game.addCircle(c);
  c = {"Circle2",{45,70},{1,3}, TFT_BLUE, 30, 45};
  game.addCircle(c);*/

  game.Init();
}


void loop() 
{
  game.play();
}


void loop1()
{
  
  
}
/*
void i2cscanner()
{

  byte error, address;
  int nDevices;

  Serial.println("\nI2C Scanner");

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire10.beginTransmission(address);
    error = Wire10.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknown error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

}*/
 /*
void Game::Init()
{
  for(auto& a : circles)
  {
    fillCircle(map_float_to_int(a.pos.x),map_float_to_int(a.pos.y),map_float_to_int(a.radius),a.color);
  
  }
}

void Game::play()
{
  collision();
  render();  
}

void Game::addCircle(const CircleObject& c)
{
  circles.push_back(c);
}

void Game::collision()
{
  for(auto& a : circles)
  {
    auto isThereOverlapping = [](CircleObject& a, CircleObject& b)
    {
      return abs((a.pos.x-b.pos.x)*(a.pos.x-b.pos.x)+(a.pos.y-b.pos.y)*(a.pos.y-b.pos.y)) <= (a.radius + b.radius)*(a.radius + b.radius);
    };
    
    a.oldPos = a.pos;
    a.pos = {a.pos.x + a.velocity.x, a.pos.y + a.velocity.y};
      
    for(auto& b : circles)
    {
      if(a.id != b.id)
      {
        if(isThereOverlapping(a,b))
        {
          overlappingCorrection(a,b);
          energy();
        }
      }
    }
       
    if((a.pos.x + a.radius) > WIDTH_SCREEN) 
    {
      a.velocity.x *= -1;
      a.pos.x = WIDTH_SCREEN - a.radius;
    }
    else if( a.pos.x < a.radius) 
    {
      a.velocity.x *= -1;
      a.pos.x = a.radius;
    }
    else if((a.pos.y + a.radius) > HEIGTH_SCREEN)
    {
      a.velocity.y *= -1;
      a.pos.y = HEIGTH_SCREEN - a.radius;
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
  int32_t tmp, result = 0;
  for(auto& a: circles)
  {
    tmp = a.velocity.mag();
    tmp = a.mass*tmp*tmp*0.5;
    result += tmp;    
  }
  DEBUG_PRINTF("Total Energy %d\n", result);
}

void Game::render()
{
  for(auto& a : circles)
  {
    fillCircle(map_float_to_int(a.oldPos.x),map_float_to_int(a.oldPos.y),map_float_to_int(a.radius),BACKGROUND_COLOR);
    fillCircle(map_float_to_int(a.pos.x),map_float_to_int(a.pos.y),map_float_to_int(a.radius),a.color);
  }

}

void Game::overlappingCorrection(CircleObject& a, CircleObject& b)
{
  float distance = a.pos.distance(b.pos);
  float overlap =  distance - (a.radius + b.radius);
  Vec2 dist = a.pos - b.pos;
  dist.normalize(distance);
  dist *= overlap; ///2;
  a.pos -= dist;
  //b.pos -= dist;
  
  distance = a.pos.distance(b.pos);
  dist = a.pos - b.pos;
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

*/

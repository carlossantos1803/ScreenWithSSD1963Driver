#include "src/Game.h"

Game game;
uint32_t end_time, end_time_2,framesPerSeconds,fps, Start;
uint32_t elapsedTime;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial);
  DEBUG_PRINT("Show Game\n");

  pinMode(LED_BUILTIN, OUTPUT);

  game.Init();
}


void loop() 
{
  game.play();
}


void loop1()
{
}

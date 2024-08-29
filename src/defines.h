#pragma once

#include <Ticker.h>
#include <TFT_eSPI.h>
#include "hardware/gpio.h"
#include "Vec2.h"

#define FPS 140 
#define WIDTH_SCREEN 48.0f
#define HEIGTH_SCREEN 80.0f

#define BACKGROUND_COLOR TFT_BLACK

#define DEBUGING

#define DEBUG_PRINTER Serial

#ifdef DEBUGING
  #define DEBUG_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); }
  #define DEBUG_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); }
  #define DEBUG_PRINTF(...) { DEBUG_PRINTER.printf(__VA_ARGS__); }
#else
  #define DEBUG_PRINT(...) {}
  #define DEBUG_PRINTLN(...) {}
  #define DEBUG_PRINTF(...) {}
#endif

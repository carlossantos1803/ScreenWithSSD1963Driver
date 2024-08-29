//                            USER DEFINED SETTINGS
//   Set driver type, fonts to be loaded, pins used and SPI control method etc
//
//   See the User_Setup_Select.h file if you wish to be able to define multiple
//   setups and then easily select which setup file is used by the compiler.
//
//   If this file is edited correctly then all the library example sketches should
//   run without the need to make any more changes for a particular hardware setup!
#define USER_SETUP_ID 666
// ##################################################################################
//
// Section 1. Call up the right driver file and any options for it
//
// ##################################################################################
//#define SSD1963_800_DRIVER    // 480 x 800 display
#define SSD1963_800ALT_DRIVER // Alternative 480 x 800 display
//#define SSD1963_800BD_DRIVER    // 480 x 800 display sourced from https://www.buydisplay.com/7-tft-screen-touch-lcd-display-module-w-ssd1963-controller-board-mcu

#define TFT_RGB_ORDER TFT_RGB  // Colour order Red-Green-Blue
//#define TFT_RGB_ORDER TFT_BGR  // Colour order Blue-Green-Red

//#define TFT_PARALLEL_8_BIT
#define TFT_PARALLEL_16_BIT

// ##################################################################################
//
// Section 2. Define the pins that are used to interface with the display here
//
// ##################################################################################
// These pins can be moved and are controlled directly by the library software
#define TFT_DC    26    // Data Command control pin
#define TFT_RST   27    // Reset pin

//#define TFT_CS    25  // Do not define if chip select control pin permanently connected to 0V
#define TFT_BL    19  // Do not define if chip select control pin permanently connected to 0V
#define TFT_BACKLIGHT_ON HIGH  // Level to turn ON back-light (HIGH or LOW)

//#define TFT_RD   -1  // Do not define, read pin must be permanently connected to 3V3
#define TFT_WR   24

// PIO requires these to be sequentially increasing GPIO with no gaps
#define TFT_D0    0
#define TFT_D1    1
#define TFT_D2    2
#define TFT_D3    3
#define TFT_D4    4
#define TFT_D5    5
#define TFT_D6    6
#define TFT_D7    7

#define TFT_D8    8
#define TFT_D9    9
#define TFT_D10  10
#define TFT_D11  11
#define TFT_D12  12
#define TFT_D13  13
#define TFT_D14  14
#define TFT_D15  15

// ##################################################################################
//
// Section 3. Define the fonts that are to be used here
//
// ##################################################################################

// Comment out the #defines below with // to stop that font being loaded
// The ESP8366 and ESP32 have plenty of memory so commenting out fonts is not
// normally necessary. If all fonts are loaded the extra FLASH space required is
// about 17Kbytes. To save FLASH space only enable the fonts you need!

#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:-.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
//#define LOAD_FONT8N // Font 8. Alternative to Font 8 above, slightly narrower, so 3 digits fit a 160 pixel TFT
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

// Comment out the #define below to stop the SPIFFS filing system and smooth font code being loaded
// this will save ~20kbytes of FLASH
#define SMOOTH_FONT



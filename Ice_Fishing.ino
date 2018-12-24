#include <gamma.h>
#include <RGBmatrixPanel.h>
#include <Adafruit_GFX.h>

// define the wiring of the LED screen
const uint8_t CLK  = 8;
const uint8_t LAT = A3;
const uint8_t OE = 9;
const uint8_t A = A0;
const uint8_t B = A1;
const uint8_t C = A2;

// define the wiring of the inputs
const int POTENTIOMETER_PIN_NUMBER = 5;
const int BUTTON_PIN_NUMBER = 10;

// a global variable that represents the LED screen
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

const int HUNDRED = 100;
//class for color
class Color {
  public:
    int red;
    int green;
    int blue;
    Color() {
      red = 0;
      green = 0;
      blue = 0;
    }
    Color(int r, int g, int b) {
      red = r;
      green = g;
      blue = b;
    }
    uint16_t to_333() const {
      return matrix.Color333(red, green, blue);
    }
};

const Color BLACK(0, 0, 0);
const Color RED(4, 0, 0);
const Color ORANGE(6, 1, 0);
const Color YELLOW(4, 4, 0);
const Color GREEN(0, 1, 0);
const Color BLUE(0, 0, 4);
const Color PURPLE(1, 0, 2);
const Color WHITE(4, 4, 4);
const Color LIME(2, 4, 0);
const Color AQUA(0, 1, 1);
const Color MAROON(1, 0, 0);
const Color NAVY(0, 0, 1);
//draws the ic
void drawIce() {
  for (int i = 0; i < 12; ++i) {
    matrix.drawPixel(i, 5, WHITE.to_333());
  }
  for (int k = 18; k < 32; ++k) {
    matrix.drawPixel(k, 5, WHITE.to_333());
  }
}
//draws sky
void drawSky() {
  for (int i = 0; i < 5; i++) {
    for (int k = 0; k < 32; k++) {
      matrix.drawPixel(k, i, BLACK.to_333());
    }
  }

}

//function to draw the number of bait remaining
//on top right of screen
void drawBait(int Bait){
if (Bait==3)
{
  //code to print 3
  matrix.drawPixel(27, 0, GREEN.to_333());
  matrix.drawPixel(28, 0, GREEN.to_333());
  matrix.drawPixel(28, 1, GREEN.to_333());
  matrix.drawPixel(28, 2, GREEN.to_333());
  matrix.drawPixel(27, 2, GREEN.to_333());
  matrix.drawPixel(28, 3, GREEN.to_333());
  matrix.drawPixel(28, 4, GREEN.to_333());
  matrix.drawPixel(27, 4, GREEN.to_333());
}
else if (Bait ==2 ){
  //code to print 2
  matrix.drawPixel(27, 0, YELLOW.to_333());
  matrix.drawPixel(28, 0, YELLOW.to_333());
  matrix.drawPixel(29, 1, YELLOW.to_333());
  matrix.drawPixel(28, 2, YELLOW.to_333());
  matrix.drawPixel(27, 3, YELLOW.to_333());
  matrix.drawPixel(28, 3, YELLOW.to_333());
  matrix.drawPixel(29, 3, YELLOW.to_333());

}
else if(Bait == 1){
// code to print 1
  matrix.drawPixel(27, 1, RED.to_333());
  matrix.drawPixel(28, 0, RED.to_333());
  matrix.drawPixel(28, 1, RED.to_333());
  matrix.drawPixel(28, 2, RED.to_333());
  matrix.drawPixel(28, 3, RED.to_333());
}
}

//draws the player
void drawPlayer() {

  matrix.drawPixel(19, 4, GREEN.to_333());
  matrix.drawPixel(20, 4, GREEN.to_333());
  matrix.drawPixel(20, 3, GREEN.to_333());
  matrix.drawPixel(20, 2, GREEN.to_333());
  matrix.drawPixel(20, 1, GREEN.to_333());
  matrix.drawPixel(20, 0, GREEN.to_333());
  matrix.drawPixel(19, 1, GREEN.to_333());
  matrix.drawPixel(19, 0, GREEN.to_333());
  matrix.drawPixel(21, 1, GREEN.to_333());
  matrix.drawPixel(21, 0, GREEN.to_333());

  for (int i = 19; i > 17; --i) {
    matrix.drawPixel(i, 2, GREEN.to_333());
  }

  //the graphics for rod
  matrix.drawPixel(17, 2, ORANGE.to_333());
  matrix.drawPixel(16, 1, ORANGE.to_333());
  matrix.drawPixel(15, 0, ORANGE.to_333());

}

//class to represent the yellow fish
class FishUpper {
  public:

    FishUpper() {
      //spawns fish at random y coordinate
      y = random(6, 10);
      //spawns fish from either left or right side
      leftSide = random(0, 2);
      if (leftSide) {
        x = 0;
      }
      else {
        x = 31;
      }
      has_been_fired = false;

    }
    //function to reset fish to initial location
    void reset() {
      erase();
      y = random(6, 10);
      leftSide = random(0, 2);
      if (leftSide) {
        x = 0;
      }
      else {
        x = 31;
      }
      has_been_fired = false;
    }
    //setters amd getters for the class
    int get_x() const {
      return x;
    }
    int get_y() const {
      return y;
    }

    void set_y(int y_arg){
      y = y_arg;
    }

    bool get_leftSide() {
      return leftSide;
    }

    void hit() {
      reset();

    }
    //draws a verticle fish if the fish has been hooked
    void drawVerticalFish() {
      matrix.drawPixel(15, y + 1, YELLOW.to_333());
      matrix.drawPixel(14, y + 2, YELLOW.to_333());
      matrix.drawPixel(15, y + 2, YELLOW.to_333());
      matrix.drawPixel(16, y + 2, YELLOW.to_333());
      matrix.drawPixel(14, y + 3, YELLOW.to_333());
      matrix.drawPixel(15, y + 3, YELLOW.to_333());
      matrix.drawPixel(16, y + 3, YELLOW.to_333());
      matrix.drawPixel(15, y + 4, YELLOW.to_333());
      matrix.drawPixel(14, y + 5, YELLOW.to_333());
      matrix.drawPixel(15, y + 5, YELLOW.to_333());
      matrix.drawPixel(16, y + 5, YELLOW.to_333());
    }
    //draws the fish
    void draw() {
      //if fish will be drawn on left side then
      //this code is used, else the other code is
      if (leftSide) {
        matrix.drawPixel(x, y, YELLOW.to_333());
        matrix.drawPixel(x, y + 1, YELLOW.to_333());
        matrix.drawPixel(x, y + 2, YELLOW.to_333());
        matrix.drawPixel(x + 1, y + 1, YELLOW.to_333());
        matrix.drawPixel(x + 3, y + 1, YELLOW.to_333());
        matrix.drawPixel(x + 2, y, YELLOW.to_333());
        matrix.drawPixel(x + 2, y + 1, YELLOW.to_333());
        matrix.drawPixel(x + 2, y + 2, YELLOW.to_333());
        matrix.drawPixel(x + 3, y, YELLOW.to_333());
        matrix.drawPixel(x + 3, y + 2, YELLOW.to_333());
        matrix.drawPixel(x + 4, y + 1, YELLOW.to_333());
      }

      else {
        matrix.drawPixel(x, y, YELLOW.to_333());
        matrix.drawPixel(x, y + 1, YELLOW.to_333());
        matrix.drawPixel(x, y + 2, YELLOW.to_333());
        matrix.drawPixel(x - 1, y + 1, YELLOW.to_333());
        matrix.drawPixel(x + 1, y, YELLOW.to_333());
        matrix.drawPixel(x + 1, y + 1, YELLOW.to_333());
        matrix.drawPixel(x + 1, y + 2, YELLOW.to_333());
        matrix.drawPixel(x + 2, y + 1, YELLOW.to_333());
        matrix.drawPixel(x + 3, y, YELLOW.to_333());
        matrix.drawPixel(x + 3, y + 1, YELLOW.to_333());
        matrix.drawPixel(x + 3, y + 2, YELLOW.to_333());
      }


    }
    //erases the fish
    void erase() {
      if (leftSide) {
        matrix.drawPixel(x, y, AQUA.to_333());
        matrix.drawPixel(x, y + 1, AQUA.to_333());
        matrix.drawPixel(x, y + 2, AQUA.to_333());
        matrix.drawPixel(x + 1, y + 1, AQUA.to_333());
        matrix.drawPixel(x + 3, y + 1, AQUA.to_333());
        matrix.drawPixel(x + 2, y, AQUA.to_333());
        matrix.drawPixel(x + 2, y + 1, AQUA.to_333());
        matrix.drawPixel(x + 2, y + 2, AQUA.to_333());
        matrix.drawPixel(x + 3, y, AQUA.to_333());
        matrix.drawPixel(x + 3, y + 2, AQUA.to_333());
        matrix.drawPixel(x + 4, y + 1, AQUA.to_333());
      }
      else {
        matrix.drawPixel(x, y, AQUA.to_333());
        matrix.drawPixel(x, y + 1, AQUA.to_333());
        matrix.drawPixel(x, y + 2, AQUA.to_333());
        matrix.drawPixel(x - 1, y + 1, AQUA.to_333());
        matrix.drawPixel(x + 1, y, AQUA.to_333());
        matrix.drawPixel(x + 1, y + 1, AQUA.to_333());
        matrix.drawPixel(x + 1, y + 2, AQUA.to_333());
        matrix.drawPixel(x + 2, y + 1, AQUA.to_333());
        matrix.drawPixel(x + 3, y, AQUA.to_333());
        matrix.drawPixel(x + 3, y + 1, AQUA.to_333());
        matrix.drawPixel(x + 3, y + 2, AQUA.to_333());
      }


    }

    void move() {
      if (leftSide) {
        erase();
        x = x + 1;
        draw();
        if (x > 32) {
          reset();
        }
      }
      else {
        erase();
        x -= 1;
        draw();
        if (x < 0) {
          reset();
        }
      }

    }
    //moves fish up along hook
    void moveVertical(){
      eraseVertical();
      y -= 1;
      drawVerticalFish();

      if(y < 4){
        reset();
      }
    }
    //erases fish as it is moving along hook
    void eraseVertical(){
      //if fish is above water then draws black,else draws aqua
      if(y < 4){
        matrix.drawPixel(15, y + 1, BLACK.to_333());
        matrix.drawPixel(14, y + 2, BLACK.to_333());
        matrix.drawPixel(15, y + 2, BLACK.to_333());
        matrix.drawPixel(14, y + 3, BLACK.to_333());
        matrix.drawPixel(16, y + 2, BLACK.to_333());
        matrix.drawPixel(15, y + 3, BLACK.to_333());
        matrix.drawPixel(16, y + 3, BLACK.to_333());
        matrix.drawPixel(15, y + 4, BLACK.to_333());
        matrix.drawPixel(14, y + 5, BLACK.to_333());
        matrix.drawPixel(15, y + 5, BLACK.to_333());
        matrix.drawPixel(16, y + 5, BLACK.to_333());
      }else{
        matrix.drawPixel(15, y + 1, AQUA.to_333());
        matrix.drawPixel(14, y + 2, AQUA.to_333());
        matrix.drawPixel(15, y + 2, AQUA.to_333());
        matrix.drawPixel(16, y + 2, AQUA.to_333());

        matrix.drawPixel(14, y + 3, AQUA.to_333());
        matrix.drawPixel(15, y + 3, AQUA.to_333());
        matrix.drawPixel(16, y + 3, AQUA.to_333());

        matrix.drawPixel(15, y + 4, AQUA.to_333());

        matrix.drawPixel(14, y + 5, AQUA.to_333());
        matrix.drawPixel(15, y + 5, AQUA.to_333());
        matrix.drawPixel(16, y + 5, AQUA.to_333());
      }

    }
  private:
    int x;
    int y;
    bool has_been_fired;
    bool leftSide;
};
//same function as above but for the red fish
class FishLower {
  public:
    //constructor
    FishLower() {
      //assigns random y value
      y = random(11, 15);
      leftSide = random(0, 2);
      if (leftSide) {
        x = 0;
      }
      else {
        x = 31;
      }
      has_been_fired = false;
    }
    //resets fish
    void reset() {
      erase();
      leftSide = random(0, 2);
      if (leftSide) {
        x = 0;
      }
      else {
        x = 31;
      }
      y = random(11, 15);
      has_been_fired = false;
    }
    //setters and getters
    int get_x() const {
      return x;
    }
    int get_y() const {
      return y;
    }
    bool get_leftSide() {
      return leftSide;
    }
    void set_y(int y_arg){
      y = y_arg;
    }
    void hit() {
      // if coordinates match then hit
      reset();
    }
    //draws fish from either left or right side
    void draw() {

      if (leftSide) {
        matrix.drawPixel(x, y, RED.to_333());
        matrix.drawPixel(x, y + 1, RED.to_333());
        matrix.drawPixel(x, y + 2, RED.to_333());
        matrix.drawPixel(x + 1, y + 1, RED.to_333());
        matrix.drawPixel(x + 3, y + 1, RED.to_333());
        matrix.drawPixel(x + 2, y, RED.to_333());
        matrix.drawPixel(x + 2, y + 1, RED.to_333());
        matrix.drawPixel(x + 2, y + 2, RED.to_333());
        matrix.drawPixel(x + 3, y, RED.to_333());
        matrix.drawPixel(x + 3, y + 2, RED.to_333());
        matrix.drawPixel(x + 4, y + 1, RED.to_333());
      }

      else {
        matrix.drawPixel(x, y, RED.to_333());
        matrix.drawPixel(x, y + 1, RED.to_333());
        matrix.drawPixel(x, y + 2, RED.to_333());
        matrix.drawPixel(x - 1, y + 1, RED.to_333());
        matrix.drawPixel(x + 1, y, RED.to_333());
        matrix.drawPixel(x + 1, y + 1, RED.to_333());
        matrix.drawPixel(x + 1, y + 2, RED.to_333());
        matrix.drawPixel(x + 2, y + 1, RED.to_333());
        matrix.drawPixel(x + 3, y, RED.to_333());
        matrix.drawPixel(x + 3, y + 1, RED.to_333());
        matrix.drawPixel(x + 3, y + 2, RED.to_333());
      }


    }
    //erases fish
    void erase() {

      if (leftSide) {
        matrix.drawPixel(x, y, AQUA.to_333());
        matrix.drawPixel(x, y + 1, AQUA.to_333());
        matrix.drawPixel(x, y + 2, AQUA.to_333());
        matrix.drawPixel(x + 1, y + 1, AQUA.to_333());
        matrix.drawPixel(x + 3, y + 1, AQUA.to_333());
        matrix.drawPixel(x + 2, y, AQUA.to_333());
        matrix.drawPixel(x + 2, y + 1, AQUA.to_333());
        matrix.drawPixel(x + 2, y + 2, AQUA.to_333());
        matrix.drawPixel(x + 3, y, AQUA.to_333());
        matrix.drawPixel(x + 3, y + 2, AQUA.to_333());
        matrix.drawPixel(x + 4, y + 1, AQUA.to_333());
      }

      else {
        matrix.drawPixel(x, y, AQUA.to_333());
        matrix.drawPixel(x, y + 1, AQUA.to_333());
        matrix.drawPixel(x, y + 2, AQUA.to_333());
        matrix.drawPixel(x - 1, y + 1, AQUA.to_333());
        matrix.drawPixel(x + 1, y, AQUA.to_333());
        matrix.drawPixel(x + 1, y + 1, AQUA.to_333());
        matrix.drawPixel(x + 1, y + 2, AQUA.to_333());
        matrix.drawPixel(x + 2, y + 1, AQUA.to_333());
        matrix.drawPixel(x + 3, y, AQUA.to_333());
        matrix.drawPixel(x + 3, y + 1, AQUA.to_333());
        matrix.drawPixel(x + 3, y + 2, AQUA.to_333());
      }


    }
    //function moves shirt along the x axis depending
    //on if th fish is moving left to right or vice versa
    void move() {

      if (leftSide) {

        erase();
        x += 1;
        draw();

        if (x > 32) {
          reset();
        }
      }
      else {
        erase();
        x -= 1;
        draw();
        if (x < 0) {
          reset();
        }
      }
    }

  private:
    int x;
    int y;
    bool has_been_fired;
    bool leftSide;
};
//class for the fish when it is caught and reeled in
class verticalFish {
  public:
    //draws verticle fish
    void drawVerticalFish(Color FishyColor) {
      matrix.drawPixel(15, y + 1, FishyColor.to_333());

      matrix.drawPixel(14, y + 2, FishyColor.to_333());
      matrix.drawPixel(15, y + 2, FishyColor.to_333());
      matrix.drawPixel(16, y + 2, FishyColor.to_333());

      matrix.drawPixel(14, y + 3, FishyColor.to_333());
      matrix.drawPixel(15, y + 3, FishyColor.to_333());
      matrix.drawPixel(16, y + 3, FishyColor.to_333());

      matrix.drawPixel(15, y + 4, FishyColor.to_333());

      matrix.drawPixel(14, y + 5, FishyColor.to_333());
      matrix.drawPixel(15, y + 5, FishyColor.to_333());
      matrix.drawPixel(16, y + 5, FishyColor.to_333());
    }
    //moves fish up on y axis
    void moveVertical(){
      eraseVertical();
      y -= 1;
      drawVerticalFish(FishColor);
    }
    //erases fish
    void eraseVertical(){
      matrix.drawPixel(15, y + 1, AQUA.to_333());
      matrix.drawPixel(14, y + 2, AQUA.to_333());
      matrix.drawPixel(15, y + 2, AQUA.to_333());
      matrix.drawPixel(16, y + 2, AQUA.to_333());
      matrix.drawPixel(14, y + 3, AQUA.to_333());
      matrix.drawPixel(15, y + 3, AQUA.to_333());
      matrix.drawPixel(16, y + 3, AQUA.to_333());
      matrix.drawPixel(15, y + 4, AQUA.to_333());
      matrix.drawPixel(14, y + 5, AQUA.to_333());
      matrix.drawPixel(15, y + 5, AQUA.to_333());
      matrix.drawPixel(16, y + 5, AQUA.to_333());
    }
    void set_y(int b) {
      y = b;
    }
    void set_x(int d) {
      x=d;
    }
    void set_FishColor(Color c) {
      FishColor = c;
    }
    int get_y() {
      return y;
    }
    int get_x(){
      return x;
    }
    Color get_FishColor() {
      return FishColor;
    }
  private:
  Color FishColor;
  int y;
  int x;


};
//class for the Jellyfish
class Jellyfish {
  public:
    Jellyfish() {
      //random y coordinate
      y = random(6, 15);
      //randomizes if jellyfish will come from left or right side
      leftSide = random(0, 2);
      if (leftSide) {
        x = 1;
      }
      else {
        x = 31;
      }
    }
    //resets jellyfish
    void reset() {
      erase();

      leftSide = random(0, 2);
      if (leftSide) {
        x = 0;
      }
      else {
        x = 31;
      }
      y = random(6, 15);
    }
    //setters and getters
    int get_x() const {
      return x;
    }
    int get_y() const {
      return y;
    }
    //if the jellyfish reaches end of display , then reset
    void jhit() {
      reset();

    }
    //draws jellyfish
    void draw() {
      matrix.drawPixel(x, (y), PURPLE.to_333());
      matrix.drawPixel(x, (y + 1), PURPLE.to_333());
      matrix.drawPixel(x - 1, (y + 1), PURPLE.to_333());
      matrix.drawPixel(x - 1, (y + 2), PURPLE.to_333());
      matrix.drawPixel(x + 1, (y + 1), PURPLE.to_333());
      matrix.drawPixel(x + 1, (y + 2), PURPLE.to_333());
    }
    //erases jellyfish
    void erase() {
      matrix.drawPixel(x, y, AQUA.to_333());
      matrix.drawPixel(x, (y + 1), AQUA.to_333());
      matrix.drawPixel(x - 1, (y + 1), AQUA.to_333());
      matrix.drawPixel(x - 1, (y + 2), AQUA.to_333());
      matrix.drawPixel(x + 1, (y + 1), AQUA.to_333());
      matrix.drawPixel(x + 1, (y + 2), AQUA.to_333());
    }

    //moves jellyfish on x axis
    void move() {
      if (leftSide) {
        erase();
        x += 1;
        draw();
        if (x > 32) {
          reset();
        }

      }

      else {

        erase();
        x -= 1;
        draw();

        if (x < 0) {
          reset();
        }

      }


    }

  private:
    int x;
    int y;
    bool leftSide;
};
//class for the line
class Line {

  public:

    Line(){

    }

    int getLength() {
      return lineLength;
    }

    void drawLine() {
      for (int i = 1; i < lineLength - 1; ++i) {
        matrix.drawPixel(15, i, WHITE.to_333());

      }

      for (int i = lineLength - 1; i <= lineLength; ++i) {
        matrix.drawPixel(15, lineLength - 1, ORANGE.to_333());
        matrix.drawPixel(14, lineLength, RED.to_333());
        matrix.drawPixel(15, lineLength, RED.to_333());
        matrix.drawPixel(16, lineLength, RED.to_333());

      }


    }
    //erases the line
    void eraseLine(FishUpper A, FishLower B, verticalFish Dinner,Jellyfish J,Jellyfish X) {
      if (lineLength < 5) {
        for (int i = lineLength + 1 ; i < 5; ++i) {
          matrix.drawPixel(15, i, BLACK.to_333());
          matrix.drawPixel(14, i, BLACK.to_333());
          matrix.drawPixel(16, i, BLACK.to_333());
        }
        for (int j = 0; j < lineLength+1; ++j) {
          matrix.drawPixel(14, j, BLACK.to_333());
          matrix.drawPixel(16, j, BLACK.to_333());
        }
      }

      else if (lineLength > 5) {
        for (int i = lineLength+1  ; i < 16; ++i) {
          matrix.drawPixel(15, i, AQUA.to_333());
          matrix.drawPixel(14, i, AQUA.to_333());
          matrix.drawPixel(16, i, AQUA.to_333());
          withinBaitUpper(A);
          withinBaitLower(B);
          withinBaitVertical(Dinner);
          withinBaitJelly(J);
          withinBaitJelly1(X);
        }
        for(int j = 5; j < lineLength; ++j) {
          matrix.drawPixel(14, j, AQUA.to_333());
          matrix.drawPixel(16, j, AQUA.to_333());
          withinBaitUpper(A);
          withinBaitLower(B);
          withinBaitVertical(Dinner);
          withinBaitJelly(J);
          withinBaitJelly1(X);

        }
      }

       else {
        for (int i = lineLength; i < 16; ++i) {
        matrix.drawPixel(15, i, AQUA.to_333());
        matrix.drawPixel(14, i, AQUA.to_333());
        matrix.drawPixel(16, i, AQUA.to_333());
        withinBaitUpper(A);
        withinBaitLower(B);
        withinBaitJelly(J);
        withinBaitVertical(Dinner);
        withinBaitJelly1(X);

        }
      }
    }

    void withinBaitUpper(FishUpper A) {
          if ((14 == A.get_x() || 16 == A.get_x() || 15 == A.get_x()) && !(lineLength == A.get_y())) {
               matrix.drawPixel(A.get_x(), A.get_y(), YELLOW.to_333());
            }
          if ((14 == A.get_x() || 16 == A.get_x() || 15 == A.get_x()) && !(lineLength == A.get_y()+1)) {
               matrix.drawPixel(A.get_x(), A.get_y()+1, YELLOW.to_333());
            }
            if ((14 == A.get_x() || 16 == A.get_x() || 15 == A.get_x()) && !(lineLength == A.get_y()+2)) {
               matrix.drawPixel(A.get_x(), A.get_y()+2, YELLOW.to_333());
            }
            if ((14 == A.get_x()+1 || 16 == A.get_x()+1 || 15 == A.get_x()+1) && !(lineLength == A.get_y()+1)) {
               matrix.drawPixel(A.get_x()+1, A.get_y()+1, YELLOW.to_333());
            }
            if ((14 == A.get_x()+3 || 16 == A.get_x()+3 || 15 == A.get_x()+3) && !(lineLength == A.get_y()+1)) {
               matrix.drawPixel(A.get_x()+3, A.get_y()+1, YELLOW.to_333());
            }
            if ((14 == A.get_x()+2 || 16 == A.get_x()+2 || 15 == A.get_x()+2) && !(lineLength == A.get_y())) {
               matrix.drawPixel(A.get_x()+2, A.get_y(), YELLOW.to_333());
            }
            if ((14 == A.get_x()+2 || 16 == A.get_x()+2 || 15 == A.get_x()+2) && !(lineLength == A.get_y()+1)) {
               matrix.drawPixel(A.get_x()+2, A.get_y()+1, YELLOW.to_333());
            }
            if ((14 == A.get_x()+2 || 16 == A.get_x()+2 || 15 == A.get_x()+2) && !(lineLength == A.get_y()+2)) {
               matrix.drawPixel(A.get_x()+2, A.get_y()+2, YELLOW.to_333());
            }
            if ((14 == A.get_x()+3 || 16 == A.get_x()+3 || 15 == A.get_x()+3) && !(lineLength == A.get_y())) {
               matrix.drawPixel(A.get_x()+3, A.get_y(), YELLOW.to_333());
            }
            if ((14 == A.get_x()+3 || 16 == A.get_x()+3 || 15 == A.get_x()+3) && !(lineLength == A.get_y()+2)) {
               matrix.drawPixel(A.get_x()+3, A.get_y()+2, YELLOW.to_333());
            }
            if ((14 == A.get_x()+4 || 16 == A.get_x()+4 || 15 == A.get_x()+4) && !(lineLength == A.get_y()+1)) {
               matrix.drawPixel(A.get_x()+3, A.get_y()+1, YELLOW.to_333());
            }
        }

        void withinBaitLower(FishLower B) {

              if(B.get_leftSide()) {
                if ((14 == B.get_x() || 16 == B.get_x() || 15 == B.get_x()) && !(B.get_y() == lineLength)){
                    matrix.drawPixel(B.get_x(), B.get_y(), RED.to_333());
                  }
                  if ((14 == B.get_x() || 16 == B.get_x() || 15 == B.get_x()) && !(B.get_y() + 1 ==  lineLength)){
                    matrix.drawPixel(B.get_x(), B.get_y() + 1, RED.to_333());
                  }
                  if ((14 == B.get_x() || 16 == B.get_x() || 15 == B.get_x()) && !(B.get_y() + 2 ==  lineLength)){
                    matrix.drawPixel(B.get_x(), B.get_y() + 2, RED.to_333());
                  }
                  if ((14 == B.get_x() + 1 || 16 == B.get_x() + 1  || 15 == B.get_x() + 1) && !(B.get_y() + 1 ==  lineLength)){
                    matrix.drawPixel(B.get_x() + 1, B.get_y() + 1, RED.to_333());
                  }
                  if ((14 == B.get_x() + 3 || 16 == B.get_x() + 3  || 15 == B.get_x() + 3) && !(B.get_y()+1 ==  lineLength)){
                    matrix.drawPixel(B.get_x() + 3, B.get_y()+1, RED.to_333());
                  }
                  if ((14 == B.get_x() + 2 || 16 == B.get_x() + 2 || 15 == B.get_x() + 2) && !(B.get_y() ==  lineLength)){
                    matrix.drawPixel(B.get_x() + 2, B.get_y(), RED.to_333());
                  }
                  if ((14 == B.get_x() + 2 || 16 == B.get_x() + 2 || 15 == B.get_x() + 2) && !(B.get_y() + 1 ==  lineLength)){
                    matrix.drawPixel(B.get_x() + 2, B.get_y() + 1, RED.to_333());
                  }
                  if ((14 == B.get_x() + 2 || 16 == B.get_x() + 2 || 15 == B.get_x() + 2) && !(B.get_y() + 2 ==  lineLength)){
                    matrix.drawPixel(B.get_x() + 2, B.get_y() + 2, RED.to_333());
                  }
                  if ((14 == B.get_x() + 3 || 16 == B.get_x() + 3 || 15 == B.get_x() + 3) && !(B.get_y() == lineLength)){
                    matrix.drawPixel(B.get_x() + 3, B.get_y(), RED.to_333());
                  }
                  if ((14 == B.get_x() + 3 || 16 == B.get_x() + 3 || 15 == B.get_x() + 3) && !(B.get_y() + 2 == lineLength)){
                    matrix.drawPixel(B.get_x() + 3, B.get_y() + 2, RED.to_333());
                  }
                  if ((14 == B.get_x() + 4 || 16 == B.get_x() + 4 || 15 == B.get_x() + 4) && !(B.get_y() + 1 ==  lineLength)){
                    matrix.drawPixel(B.get_x() + 4, B.get_y() + 1, RED.to_333());
                  }
              }
              else {
                  if ((14 == B.get_x() || 16 == B.get_x() || 15 == B.get_x()) && !(B.get_y() == lineLength)){
                    matrix.drawPixel(B.get_x(), B.get_y(), RED.to_333());
                  }
                  if ((14 == B.get_x() || 16 == B.get_x() || 15 == B.get_x()) && !(B.get_y() + 1 ==  lineLength)){
                    matrix.drawPixel(B.get_x(), B.get_y() + 1, RED.to_333());
                  }
                  if ((14 == B.get_x() || 16 == B.get_x() || 15 == B.get_x()) && !(B.get_y() + 2 ==  lineLength)){
                    matrix.drawPixel(B.get_x(), B.get_y() + 2, RED.to_333());
                  }
                  if ((14 == B.get_x() - 1 || 16 == B.get_x() - 1  || 15 == B.get_x() - 1) && !(B.get_y() + 1 ==  lineLength)){
                    matrix.drawPixel(B.get_x() - 1, B.get_y() + 1, RED.to_333());
                  }
                  if ((14 == B.get_x() + 1 || 16 == B.get_x() + 1  || 15 == B.get_x() + 1) && !(B.get_y() ==  lineLength)){
                    matrix.drawPixel(B.get_x() + 1, B.get_y(), RED.to_333());
                  }
                  if ((14 == B.get_x() + 1 || 16 == B.get_x() + 1 || 15 == B.get_x() + 1) && !(B.get_y() + 1 ==  lineLength)){
                    matrix.drawPixel(B.get_x() + 1, B.get_y() + 1, RED.to_333());
                  }
                  if ((14 == B.get_x() + 1 || 16 == B.get_x() + 1 || 15 == B.get_x() + 1) && !(B.get_y() + 2 ==  lineLength)){
                    matrix.drawPixel(B.get_x() + 1, B.get_y() + 2, RED.to_333());
                  }
                  if ((14 == B.get_x() + 2 || 16 == B.get_x() + 2 || 15 == B.get_x() + 2) && !(B.get_y() + 1 ==  lineLength)){
                    matrix.drawPixel(B.get_x() + 2, B.get_y() + 1, RED.to_333());
                  }
                  if ((14 == B.get_x() + 3 || 16 == B.get_x() + 3 || 15 == B.get_x() + 3) && !(B.get_y() == lineLength)){
                    matrix.drawPixel(B.get_x() + 3, B.get_y(), RED.to_333());
                  }
                  if ((14 == B.get_x() + 3 || 16 == B.get_x() + 3 || 15 == B.get_x() + 3) && !(B.get_y() + 1 == lineLength)){
                    matrix.drawPixel(B.get_x() + 3, B.get_y() + 1, RED.to_333());
                  }
                  if ((14 == B.get_x() + 3 || 16 == B.get_x() + 3 || 15 == B.get_x() + 3) && !(B.get_y() + 2 ==  lineLength)){
                    matrix.drawPixel(B.get_x() + 3, B.get_y() + 2, RED.to_333());
                  }
              }

            }

            void withinBaitVertical(verticalFish Dinner) {
              if ((14 == Dinner.get_x()+1 || 16 == Dinner.get_x()+1 || 15 == Dinner.get_x()+1)){
                matrix.drawPixel(Dinner.get_x()+1, Dinner.get_y() + 1, Dinner.get_FishColor().to_333());
              }
              if ((14 == Dinner.get_x() || 16 == Dinner.get_x() || 15 == Dinner.get_x()) ){
                matrix.drawPixel(Dinner.get_x(), Dinner.get_y() + 2, Dinner.get_FishColor().to_333());
              }
              if ((14 == Dinner.get_x() + 1 || 16 == Dinner.get_x() + 1 || 15 == Dinner.get_x() + 1) ){
                matrix.drawPixel(Dinner.get_x() + 1, Dinner.get_y() + 2, Dinner.get_FishColor().to_333());
              }
              if ((14 == Dinner.get_x() + 2 || 16 == Dinner.get_x() + 2  || 15 == Dinner.get_x() + 2) ){
                matrix.drawPixel(Dinner.get_x() + 2, Dinner.get_y() + 2, Dinner.get_FishColor().to_333());
              }
              if ((14 == Dinner.get_x()  || 16 == Dinner.get_x()   || 15 == Dinner.get_x()) ){
                matrix.drawPixel(Dinner.get_x() , Dinner.get_y() + 3, Dinner.get_FishColor().to_333());
              }
              if ((14 == Dinner.get_x() + 1 || 16 == Dinner.get_x() + 1 || 15 == Dinner.get_x() + 1) ){
                matrix.drawPixel(Dinner.get_x() + 1, Dinner.get_y() + 3, Dinner.get_FishColor().to_333());
              }
              if ((14 == Dinner.get_x() + 2 || 16 == Dinner.get_x() + 2 || 15 == Dinner.get_x() + 2) ){
                matrix.drawPixel(Dinner.get_x() + 1, Dinner.get_y() + 3, Dinner.get_FishColor().to_333());
              }
              if ((14 == Dinner.get_x() + 1 || 16 == Dinner.get_x() + 1 || 15 == Dinner.get_x() + 1) ){
                matrix.drawPixel(Dinner.get_x() + 1, Dinner.get_y() + 4, Dinner.get_FishColor().to_333());
              }
              if ((14 == Dinner.get_x()  || 16 == Dinner.get_x() || 15 == Dinner.get_x() ) ){
                matrix.drawPixel(Dinner.get_x() , Dinner.get_y() + 5, Dinner.get_FishColor().to_333());
              }
              if ((14 == Dinner.get_x() + 1 || 16 == Dinner.get_x() + 1 || 15 == Dinner.get_x() + 1) ){
                matrix.drawPixel(Dinner.get_x() + 1, Dinner.get_y() + 5, Dinner.get_FishColor().to_333());
              }
              if ((14 == Dinner.get_x() + 2 || 16 == Dinner.get_x() + 2 || 15 == Dinner.get_x() + 2) ){
                matrix.drawPixel(Dinner.get_x() + 2, Dinner.get_y() + 5, Dinner.get_FishColor().to_333());
              }
            }


    void withinBaitJelly(Jellyfish J) {
      if ((14 == J.get_x() || 16 == J.get_x() || 15 == J.get_x()) && !(J.get_y() == lineLength)){
        matrix.drawPixel(J.get_x(), J.get_y(), PURPLE.to_333());
      }
      if ((14 == J.get_x() || 16 == J.get_x() || 15 == J.get_x()) & !(J.get_y() + 1 ==  lineLength)){
        matrix.drawPixel(J.get_x(), J.get_y() + 1, PURPLE.to_333());
      }
      if ((14 == J.get_x() - 1 || 16 == J.get_x() - 1 || 15 == J.get_x() - 1) & !(J.get_y() + 1 ==  lineLength)){
        matrix.drawPixel(J.get_x() - 1, J.get_y() + 1, PURPLE.to_333());
      }
      if ((14 == J.get_x() - 1 || 16 == J.get_x() - 1  || 15 == J.get_x() - 1)& !(J.get_y() + 2 ==  lineLength)){
        matrix.drawPixel(J.get_x() - 1, J.get_y() + 2, PURPLE.to_333());
      }
      if ((14 == J.get_x() + 1 || 16 == J.get_x() + 1  || 15 == J.get_x() + 1) & !(J.get_y() + 1 ==  lineLength)){
        matrix.drawPixel(J.get_x() + 1, J.get_y() + 1, PURPLE.to_333());
      }
      if ((14 == J.get_x() + 1 || 16 == J.get_x() + 1 || 15 == J.get_x() + 1) & !(J.get_y() + 2 ==  lineLength)){
        matrix.drawPixel(J.get_x() + 1, J.get_y() + 2, PURPLE.to_333());
      }

    }

    void withinBaitJelly1(Jellyfish X) {
      if ((14 == X.get_x() || 16 == X.get_x() || 15 == X.get_x()) && !(X.get_y() == lineLength)){
        matrix.drawPixel(X.get_x(), X.get_y(), PURPLE.to_333());
      }
      if ((14 == X.get_x() || 16 == X.get_x() || 15 == X.get_x()) & !(X.get_y() + 1 ==  lineLength)){
        matrix.drawPixel(X.get_x(), X.get_y() + 1, PURPLE.to_333());
      }
      if ((14 == X.get_x() - 1 || 16 == X.get_x() - 1 || 15 == X.get_x() - 1) & !(X.get_y() + 1 ==  lineLength)){
        matrix.drawPixel(X.get_x() - 1, X.get_y() + 1, PURPLE.to_333());
      }
      if ((14 == X.get_x() - 1 || 16 == X.get_x() - 1  || 15 == X.get_x() - 1)& !(X.get_y() + 2 ==  lineLength)){
        matrix.drawPixel(X.get_x() - 1, X.get_y() + 2, PURPLE.to_333());
      }
      if ((14 == X.get_x() + 1 || 16 == X.get_x() + 1  || 15 == X.get_x() + 1) & !(X.get_y() + 1 ==  lineLength)){
        matrix.drawPixel(X.get_x() + 1, X.get_y() + 1, PURPLE.to_333());
      }
      if ((14 == X.get_x() + 1 || 16 == X.get_x() + 1 || 15 == X.get_x() + 1) & !(X.get_y() + 2 ==  lineLength)){
        matrix.drawPixel(X.get_x() + 1, X.get_y() + 2, PURPLE.to_333());
      }

    }

    bool isHooked(){
      return hooked;
    }

    void hook(){
      hooked = true;
    }

    void resetHook(){
      hooked = false;
    }

    int get_y(){
      return lineLength;
    }

  private:
    int lineLength = analogRead(POTENTIOMETER_PIN_NUMBER) / 68;
    bool hooked;

};

class Game {
  public:
    //Default constructor for Game class
    Game() {
    }


    // sets up a new game of Space Invaders
    // Modifies: global variable matrix
    void start() {
      // initializes the matrix on screen
      matrix.begin();
      matrix.fillScreen(AQUA.to_333());
      drawIce();
      drawSky();
      drawBait(3);
      score = 0;
      level = 0;
      checkRun = 1;
      Bait = 3;
    }



    // advances the game simulation one step and renders the graphics
    // see spec for details of game
    // Modifies: global variable matrix
    void update(int potentiometer_value, bool button_pressed) {

      Line FishingLine;

      if (millis() == 0) {
        FishingLine.resetHook();
      }

      //draws the player
      drawPlayer();

      //updates the size of the fishing line
      FishingLine.drawLine();
      FishingLine.eraseLine(Nemo, Dory, Dinner,jelly,jelly2);


      //Spawns upper quadrant fish (yellow)
      if(!FishingLine.isHooked()){
        if (millis() % 1000 == 0) {
          FishUpper Nemo;
        }
      }

      //Spawns lower quadrant fish (red)
      if(!FishingLine.isHooked()){
        if (millis() % 500 == 0) {
          FishUpper Dory;
        }
      }

      //Spawns jellyfish (purple)
      if (millis() % 1000 == 0) {
        Jellyfish jelly;
      }
      //spawns second jellyfish
      Serial.print(score);
      if (score >= 30) {
        Jellyfish jelly2;
      }



      if ((14 == Nemo.get_x() || 16 == Nemo.get_x()) && FishingLine.getLength() == Nemo.get_y()   ||
          (14 == Nemo.get_x() || 16 == Nemo.get_x()) && FishingLine.getLength() == Nemo.get_y() + 1  ||
          (14 == Nemo.get_x() || 16 == Nemo.get_x()) && FishingLine.getLength() == Nemo.get_y() + 2  ||
          (14 == Nemo.get_x() + 1 || 16 == Nemo.get_x() + 1) && FishingLine.getLength() == Nemo.get_y() + 1 ||
          (14 == Nemo.get_x() + 3 || 16 == Nemo.get_x() + 3) && FishingLine.getLength() == Nemo.get_y() + 1 ||
          (14 == Nemo.get_x() + 2 || 16 == Nemo.get_x() + 2) && FishingLine.getLength() == Nemo.get_y()    ||
          (14 == Nemo.get_x() + 2 || 16 == Nemo.get_x() + 2) && FishingLine.getLength() == Nemo.get_y() + 1 ||
          (14 == Nemo.get_x() + 2 || 16 == Nemo.get_x() + 2) && FishingLine.getLength() == Nemo.get_y() + 2 ||
          (14 == Nemo.get_x() + 3 || 16 == Nemo.get_x() + 3) && FishingLine.getLength() == Nemo.get_y()    ||
          (14 == Nemo.get_x() + 3 || 16 == Nemo.get_x() + 3) && FishingLine.getLength() == Nemo.get_y() + 2 ||
          (14 == Nemo.get_x() + 4 || 16 == Nemo.get_x() + 4) && FishingLine.getLength() == Nemo.get_y() + 1)
      {

        if(!FishingLine.isHooked()){
          Nemo.erase();
          Nemo.reset();
          FishingLine.hook();
          checkFish = 0;
        }
      }
      else if ((14 == Dory.get_x() || 16 == Dory.get_x()) && FishingLine.getLength() == Dory.get_y() ||
               (14 == Dory.get_x() || 16 == Dory.get_x()) && FishingLine.getLength() == Dory.get_y() + 1 ||
               (14 == Dory.get_x() || 16 == Dory.get_x()) && FishingLine.getLength() == Dory.get_y() + 2 ||
               (14 == Dory.get_x() - 1 || 16 == Dory.get_x() - 1) && FishingLine.getLength() == Dory.get_y() + 1 ||
               (14 == Dory.get_x() + 1 || 16 == Dory.get_x() + 1) && FishingLine.getLength() == Dory.get_y() ||
               (14 == Dory.get_x() + 1 || 16 == Dory.get_x() + 1) && FishingLine.getLength() == Dory.get_y() + 1 ||
               (14 == Dory.get_x() + 1 || 16 == Dory.get_x() + 1) && FishingLine.getLength() == Dory.get_y() + 2 ||
               (14 == Dory.get_x() + 2 || 16 == Dory.get_x() + 2) && FishingLine.getLength() == Dory.get_y() + 1 ||
               (14 == Dory.get_x() + 3 || 16 == Dory.get_x() + 3) && FishingLine.getLength() == Dory.get_y() ||
               (14 == Dory.get_x() + 3 || 16 == Dory.get_x() + 3) && FishingLine.getLength() == Dory.get_y() + 1 ||
               (14 == Dory.get_x() + 3 || 16 == Dory.get_x() + 3) && FishingLine.getLength() == Dory.get_y() + 2)
      {

        if(!FishingLine.isHooked()){
          Dory.erase();
          Dory.reset();
          FishingLine.hook();
          checkFish = 1;
        }
      }

     if ((14 == jelly2.get_x() - 1 || 15 == jelly2.get_x() - 1 || 16 == jelly2.get_x() - 1) && jelly2.get_y() <= FishingLine.getLength() ||
           (14 == jelly2.get_x() || 15 == jelly2.get_x() || 16 == jelly2.get_x()) && jelly2.get_y() <= FishingLine.getLength() ||
           (14 == jelly2.get_x() || 15 == jelly2.get_x()  || 16 == jelly2.get_x()) && FishingLine.getLength() == jelly2.get_y() ||
           (14 == jelly2.get_x() || 15 == jelly2.get_x()  || 16 == jelly2.get_x()) && FishingLine.getLength()  == jelly2.get_y() + 1 ||
           (14 == jelly2.get_x() - 1 || 15 == jelly2.get_x() - 1 || 16 == jelly2.get_x() - 1) && FishingLine.getLength()  == jelly2.get_y() + 1 ||
           (14 == jelly2.get_x() - 1 || 15 == jelly2.get_x() - 1 || 16 == jelly2.get_x() - 1) && FishingLine.getLength()  == jelly2.get_y() + 2 ||
           (14 == jelly2.get_x() + 1 || 15 == jelly2.get_x() + 1 || 16 == jelly2.get_x() + 1) && FishingLine.getLength()  == jelly2.get_y() + 1 ||
           (14 == jelly2.get_x() + 1 || 15 == jelly2.get_x() + 1 || 16 == jelly2.get_x() + 1) && FishingLine.getLength() == jelly2.get_y() + 2
          )
        {

            Bait--;
            jelly2.reset();
            matrix.drawPixel(27, 0, BLACK.to_333());
            matrix.drawPixel(27, 1, BLACK.to_333());
            matrix.drawPixel(27, 2, BLACK.to_333());
            matrix.drawPixel(27, 3, BLACK.to_333());
            matrix.drawPixel(27, 4, BLACK.to_333());
            matrix.drawPixel(28, 0, BLACK.to_333());
            matrix.drawPixel(28, 1, BLACK.to_333());
            matrix.drawPixel(28, 2, BLACK.to_333());
            matrix.drawPixel(28, 3, BLACK.to_333());
            matrix.drawPixel(28, 4, BLACK.to_333());
            matrix.drawPixel(29, 0, BLACK.to_333());
            matrix.drawPixel(29, 1, BLACK.to_333());
            matrix.drawPixel(29, 2, BLACK.to_333());
            matrix.drawPixel(29, 3, BLACK.to_333());
            matrix.drawPixel(29, 4, BLACK.to_333());

            if(Bait > 0 ){
            drawBait(Bait);
            }
            //prints game over it bait is less than 0
            else{



              matrix.fillScreen(BLACK.to_333());
              //sets text color on matrix to red
              matrix.fillScreen(BLACK.to_333());
              matrix.setTextColor(RED.to_333());

            while(!(digitalRead(BUTTON_PIN_NUMBER) == HIGH)){
              matrix.setCursor(5,0);
              matrix.print('G');
              matrix.setCursor(11,0);
              matrix.print('A');
              matrix.setCursor(17,0);
              matrix.print('M');
              matrix.setCursor(23,0);
              matrix.print('E');
              matrix.setCursor(5,8);
              matrix.print('O');
              matrix.setCursor(11,8);
              matrix.print('V');
              matrix.setCursor(17,8);
              matrix.print('E');
              matrix.setCursor(23,8);
              matrix.print('R');
              //delays by 450 milliseconds
              delay(450);
              matrix.fillScreen(BLACK.to_333());
              //delays by 150 milliseconds
              delay(150);

            }

            start();
            }

            if(FishingLine.isHooked()){
              FishingLine.resetHook();

          }





        }

        if ((14 == jelly.get_x() - 1 || 15 == jelly.get_x() - 1 || 16 == jelly.get_x() - 1) && jelly.get_y() <= FishingLine.getLength() ||
              (14 == jelly.get_x() || 15 == jelly.get_x() || 16 == jelly.get_x()) && jelly.get_y() <= FishingLine.getLength() ||
              (14 == jelly.get_x() || 15 == jelly.get_x()  || 16 == jelly.get_x()) && FishingLine.getLength() == jelly.get_y() ||
              (14 == jelly.get_x() || 15 == jelly.get_x()  || 16 == jelly.get_x()) && FishingLine.getLength()  == jelly.get_y() + 1 ||
              (14 == jelly.get_x() - 1 || 15 == jelly.get_x() - 1 || 16 == jelly.get_x() - 1) && FishingLine.getLength()  == jelly.get_y() + 1 ||
              (14 == jelly.get_x() - 1 || 15 == jelly.get_x() - 1 || 16 == jelly.get_x() - 1) && FishingLine.getLength()  == jelly.get_y() + 2 ||
              (14 == jelly.get_x() + 1 || 15 == jelly.get_x() + 1 || 16 == jelly.get_x() + 1) && FishingLine.getLength()  == jelly.get_y() + 1 ||
              (14 == jelly.get_x() + 1 || 15 == jelly.get_x() + 1 || 16 == jelly.get_x() + 1) && FishingLine.getLength() == jelly.get_y() + 2
             )
           {

               Bait--;
               jelly.reset();
               matrix.drawPixel(27, 0, BLACK.to_333());
               matrix.drawPixel(27, 1, BLACK.to_333());
               matrix.drawPixel(27, 2, BLACK.to_333());
               matrix.drawPixel(27, 3, BLACK.to_333());
               matrix.drawPixel(27, 4, BLACK.to_333());
               matrix.drawPixel(28, 0, BLACK.to_333());
               matrix.drawPixel(28, 1, BLACK.to_333());
               matrix.drawPixel(28, 2, BLACK.to_333());
               matrix.drawPixel(28, 3, BLACK.to_333());
               matrix.drawPixel(28, 4, BLACK.to_333());
               matrix.drawPixel(29, 0, BLACK.to_333());
               matrix.drawPixel(29, 1, BLACK.to_333());
               matrix.drawPixel(29, 2, BLACK.to_333());
               matrix.drawPixel(29, 3, BLACK.to_333());
               matrix.drawPixel(29, 4, BLACK.to_333());

               if(Bait > 0 ){
               drawBait(Bait);
               }
               //prints game over it bait is less than 0
               else{



                 matrix.fillScreen(BLACK.to_333());
                 //sets text color on matrix to red
                 matrix.fillScreen(BLACK.to_333());
                 matrix.setTextColor(RED.to_333());

               while(!(digitalRead(BUTTON_PIN_NUMBER) == HIGH)){
                 matrix.setCursor(5,0);
                 matrix.print('G');
                 matrix.setCursor(11,0);
                 matrix.print('A');
                 matrix.setCursor(17,0);
                 matrix.print('M');
                 matrix.setCursor(23,0);
                 matrix.print('E');
                 matrix.setCursor(5,8);
                 matrix.print('O');
                 matrix.setCursor(11,8);
                 matrix.print('V');
                 matrix.setCursor(17,8);
                 matrix.print('E');
                 matrix.setCursor(23,8);
                 matrix.print('R');
                 //delays by 450 milliseconds
                 delay(450);
                 matrix.fillScreen(BLACK.to_333());
                 //delays by 150 milliseconds
                 delay(150);
               }

               start();
               }

               if(FishingLine.isHooked()){
                 FishingLine.resetHook();

             }





           }






      int temp;

      //hooking fish and drawing vertically
      if(FishingLine.isHooked()){
        if(checkFish == 0){
          goingUp.set_y(Nemo.get_y());
          goingUp.set_FishColor(YELLOW);
          if(goingUp.get_y() != FishingLine.get_y()){
            goingUp.eraseVertical();
            goingUp.set_y(FishingLine.get_y());
            goingUp.drawVerticalFish(goingUp.get_FishColor());
          }
          if(FishingLine.get_y() < 5){
            goingUp.eraseVertical();
            FishingLine.resetHook();
            checkFish = -1;
            score += 1;
          }
        }else if(checkFish == 1){
          goingUp.set_y(Dory.get_y());
          goingUp.set_FishColor(RED);
          if(FishingLine.isHooked()) {
            if(goingUp.get_y() != FishingLine.get_y()){
              goingUp.eraseVertical();
              goingUp.set_y(FishingLine.get_y());
              goingUp.drawVerticalFish(goingUp.get_FishColor());
            }
          }
          if(FishingLine.get_y() < 5){
            goingUp.eraseVertical();
            FishingLine.resetHook();
            checkFish = -1;
            score += 1;
          }
        }
      }

      //sets  the speed on the fish depending on the level that is being played
      time = 1;
      if(score > 10){
        time = 2;
      }
      if(score >20){
        time = 3;
      }
      if(score >30){
        time = 4;
      }
      if (millis() % (50/time) == 0) {
        jelly.move();
        if (score >= 40) {
          jelly2.move();
        }
        FishingLine.drawLine();
        FishingLine.eraseLine(Nemo, Dory, Dinner,jelly,jelly2);
      }


      if (millis() % (60/time) == 0) {
          Nemo.move();
          FishingLine.drawLine();
          FishingLine.eraseLine(Nemo, Dory, Dinner,jelly,jelly2);
      }

      if (millis() % (70/time) == 0) {
          Dory.move();
          FishingLine.drawLine();
          FishingLine.eraseLine(Nemo, Dory,Dinner,jelly,jelly2);
      }


      if(score % 10 == 0){
        if(checkRun == 1){
          print_score(score);
          delay(1000);
          checkRun = 0;
          matrix.fillScreen(AQUA.to_333());
          drawIce();
          drawSky();
          drawBait(Bait);

        }
      }else if(score % 10 > 0){
        checkRun = 1;
      }
      //prints you won if user has about over 100 points
     if(score>100){
            matrix.fillScreen(BLACK.to_333());
            while(!(digitalRead(BUTTON_PIN_NUMBER) == HIGH)){
            matrix.setTextColor(RED.to_333());
            delay(1000);
            matrix.setCursor(3,0);
            matrix.print('Y');
            matrix.setCursor(10,0);
            matrix.print('O');
            matrix.setCursor(16,0);
            matrix.print('U');
            matrix.setCursor(3,8);
            matrix.print('W');
            matrix.setCursor(10,8);
            matrix.print('O');
            matrix.setCursor(16,8);
            matrix.print('N');
            delay(1000);
            matrix.fillScreen(BLACK.to_333());
                }
            start();
          }


    }

    int get_checkFish() {
        return checkFish;
      }


//prints the score of the user
void print_score(int score) {

  char first_digit = (score / 10) + 48;
  char one_digit = score + 48;

    matrix.fillScreen(BLACK.to_333());
    matrix.setTextColor(WHITE.to_333());
    matrix.setCursor(1,0);
    matrix.print('F');
    matrix.setCursor(7,0);
    matrix.print('I');
    matrix.setCursor(13,0);
    matrix.print('S');
    matrix.setCursor(19,0);
    matrix.print('H');

    matrix.setCursor(25,0);
    matrix.print(':');

    matrix.setCursor(1,7);
    if(Bait >= 1){
    matrix.print(first_digit);
    }
    else{
    char one_digit = score + 48;
    }

    matrix.setCursor(5,7);
    matrix.print('0');

  }




bool get_score() {
  return score;
}



  private:
    FishUpper Nemo;
    FishLower Dory;
    Jellyfish jelly;
    int checkFish;
    verticalFish goingUp;
    verticalFish Dinner;
    int score;
    int Bait;
    int level;
    int checkRun;
    int time;
    Jellyfish jelly2;





};

// a global variable that represents the reach game
Game game;


//function that sets up the code
void setup() {
  //begins the serial after 9600 milliseconds
  Serial.begin(9600);
  //setting pinmode with pin number and input
  pinMode(BUTTON_PIN_NUMBER, INPUT);
  //starts the game
  game.start();

}
void loop() {
  //initializes potentiometer_value to analogRead
  int potentiometer_value = analogRead(POTENTIOMETER_PIN_NUMBER);
  //initializes button_pressed to digitalRead
  bool button_pressed = (digitalRead(BUTTON_PIN_NUMBER) == HIGH);
  //game class accesses update method
  game.update(potentiometer_value, button_pressed);

}

void print() {
  matrix.setCursor(5, 0);
  matrix.print('3');
  matrix.setCursor(5, 0);
  matrix.print('2');
  matrix.setCursor(5, 0);
  matrix.print('1');
  matrix.setCursor(5, 0);
  matrix.print('0');

}

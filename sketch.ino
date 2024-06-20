// Now turn this trash into treasure!

#include <lcdgfx.h>

#define ENCODER_CLK 6
#define ENCODER_DT 7
#define ENCODER_SW 8

DisplaySSD1306_128x64_I2C display(-1);

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  Serial1.println("Hello, Raspberry Pi Pico W!");

  display.begin();

  display.clear();

  display.setFixedFont( ssd1306xled_font6x8 );

  display.printFixed(0,8,"0", STYLE_NORMAL);

  // pinMode(BUTTON, INPUT_PULLUP);
  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  pinMode(ENCODER_SW, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER_CLK), readEncoder, FALLING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_SW), readbutton, FALLING);
}

int add_counter = 0;

void readEncoder() {
  int dtValue = digitalRead(ENCODER_DT);
  if (dtValue == HIGH) {
    add_counter++;
  }
  if (dtValue == LOW) {
    add_counter--;
  }
  updatedisplay();
}

void readbutton() {
  Serial1.println("Input placed with a count of: " + String(add_counter));
  add_counter = 0;
  updatedisplay();
}

void updatedisplay() {
  display.clear();
  display.setFixedFont( courier_new_font11x16_digits );
  display.printFixed(0,8,String(add_counter).c_str(), STYLE_NORMAL);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1); // this speeds up the simulation
  // if (digitalRead(BUTTON) == LOW) {
  //   Serial1.println("Button is a go");
  // }
}
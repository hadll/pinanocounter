// Now turn this trash into treasure!

#include <lcdgfx.h>
#include <MD_MAX72xx.h>


#define ENCODER_CLK 6
#define ENCODER_DT 7
#define ENCODER_SW 8

#define	CLK_PIN		13
#define	DATA_PIN	11
#define	CS_PIN		10

#define BUZZER 27

float notes[12] {
    261.63,277.18,293.66,311.13,329.63,349.23,369.99,392,415.3,440,466.16,493.88
};

int tickets = 0;
int add_counter = 0;

DisplaySSD1306_128x64_I2C display(-1);
int display_width = 128;
int display_height = 64;

int ui_mode = -1;

String main_menu_items[3] {
  "add / remove",
  "visualise progress",
  "set goal"
};


void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  Serial1.println("Hello, Raspberry Pi Pico W!");

  display.begin();

  display.clear();

  display.setFixedFont( courier_new_font11x16_digits );

  updatedisplay();

  // pinMode(BUTTON, INPUT_PULLUP);
  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  pinMode(ENCODER_SW, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER_CLK), readEncoder, FALLING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_SW), readbutton, FALLING);
}

void displayListMenu(String menu_items[3],int scroll) {
  for (int i = 0; i<3; i++){
    if (i+scroll > 3){ // make sure we dont exceed the array
      break;
    }
    display.printFixed(0, display_height/4*(i+1), menu_items[i+scroll].c_str(), STYLE_NORMAL);
  }
  
}

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
  switch (ui_mode){
    case 1:
      Serial1.println("Input placed with a count of: " + String(add_counter));

      for (int i = 0; i<=add_counter; i++) {
        int led = tickets + i;
        // update leds
      }
      tickets += add_counter;
      add_counter = 0;
      updatedisplay();
      break;
  }
}

void updatedisplay() {
  display.clear();
  switch (ui_mode){
    case -1: // main menu
      displayListMenu(main_menu_items, 0);
    case 1: // add menu
      if (add_counter < 0){
        tone(BUZZER, notes[0], 100);
      }else if (add_counter < 12) {
        tone(BUZZER, notes[add_counter-1], 100);
      }else {
        tone(BUZZER, notes[11], 100);
      }
      display.clear();
      display.printFixed(0,8,String(add_counter).c_str(), STYLE_NORMAL);
      break;
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1); // this speeds up the simulation
  // if (digitalRead(BUTTON) == LOW) {
  //   Serial1.println("Button is a go");
  // }
}
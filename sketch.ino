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

MD_MAX72XX mx = MD_MAX72XX(MD_MAX72XX::PAROLA_HW, CS_PIN, 1);

DisplaySSD1306_128x64_I2C display(-1);

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  Serial1.println("Hello, Raspberry Pi Pico W!");

  display.begin();

  display.clear();

  display.setFixedFont( ssd1306xled_font6x8 );

  display.printFixed(0,8,"0", STYLE_NORMAL);

  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, MAX_INTENSITY/2);
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  mx.clear();

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

  for (int i = 0; i<=add_counter; i++) {
    int led = tickets + i;
    // update leds
  }
  tickets += add_counter;
  add_counter = 0;
  updatedisplay();
}

void updatedisplay() {
  if (add_counter < 0){
    tone(BUZZER, notes[0], 100);
  }else if (add_counter < 12) {
    tone(BUZZER, notes[add_counter-1], 100);
  }else {
    tone(BUZZER, notes[11], 100);
  }
  display.clear();
  display.setFixedFont( courier_new_font11x16_digits );
  display.printFixed(0,8,String(add_counter).c_str(), STYLE_NORMAL);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100); // this speeds up the simulation
  // if (digitalRead(BUTTON) == LOW) {
  //   Serial1.println("Button is a go");
  // }
  mx.setPoint(1, 1, true);
  mx.update();
}
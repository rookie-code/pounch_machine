#include <timer.h>
#include "OneButton.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

auto timer = timer_create_default();

OneButton button1(A1, true);
OneButton buttonPounch(A2, true);
int timerCount = 60;
int record = 0;
int pounch = 0;
int pounchTimer = 0;
boolean buttonTimerPress = false;
boolean counterActive = false;
boolean activePounchTimer = false;
boolean pause = false;
boolean top = false;

void setup() {
  Serial.begin(9600);
  // init LCD
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight
  initPageDisplay();
  delay(3000);

  lcd.clear();
  displayLcd(pounch, timerCount, record);
  button1.attachClick(singleClick);
  button1.attachLongPressStart(longClick);
  button1.setDebounceTicks(80);

  buttonPounch.attachClick(pounchClick);
  buttonPounch.setDebounceTicks(30);

  timer.every(1000, decrementCounter );

}


void loop() {
  button1.tick();
  buttonPounch.tick();
  timer.tick();

}


int countPause = 0;
void decrementCounter() {

  displayCountDown(0);

  if (countPause >= 5) {
    pause = false;
    countPause = 0;
    pounch = 0;
    timerCount = 60;
    pounchTimer = 0;
    top = false;
    displayLcd(pounch, timerCount, record);

  }
  if (pause) {
    countPause++;
    displayTop(top);
        
    
  } else {
    
    if (counterActive) {

      changeVariable(2, timerCount);
      timerCount--;
      pounchTimer++;

      if (activePounchTimer) {
        displayCountDown(5 - pounchTimer);
      }

    }
    if (timerCount == 0 || pounchTimer >= 6) {
      
      activePounchTimer = false;
      changeVariable(1, pounch);
      changeVariable(2, timerCount);
      counterActive = false;
      // inserire schermata riepilogativa
      pounch = 0;
      timerCount = 60;
      changeVariable(1, pounch);
      changeVariable(2, timerCount);
      pause = true;

    }
  }
}

void singleClick() {

  activePounchTimer = false;
  timerCount = 60;
  pounch = 0;
  changeVariable(1, pounch);
  changeVariable(2, timerCount);
  counterActive = false;
}

void longClick() {
  record = 0;
  activePounchTimer = false;
  timerCount = 60;
  pounch = 0;
  changeVariable(1, pounch);
  changeVariable(2, timerCount);
  changeVariable(3, record);
  counterActive = false;
  top = false;
}

void recordCompare(int value) {
  if (value >= record) {
    record = value;
    changeVariable(3, value);
    top = true;
  }

}

void pounchClick() {
  if (!pause) {
    pounchTimer = 0;
    displayCountDown(pounchTimer);
    changeVariable(1, pounch);
    recordCompare(pounch);
    pounch++;
    counterActive = true;
    activePounchTimer = true;
  }
}

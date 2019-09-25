#include <timer.h>
#include "OneButton.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

Timer timer;


OneButton buttonPounch(A1, false);
int timerCount = 60;
int record = 0;
int pounch = 0;
int pounchTimer = 0;
int lastPounch;
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
  displayLcd(pounch, timerCount, record, lastPounch);

  buttonPounch.attachClick(pounchClick);

  timer.setInterval(1000);

  // The function to be called
  timer.setCallback(decrementCounter);

  // Start the timer
  timer.start();

}

void loop() {
  //button1.tick();
  buttonPounch.tick();
  timer.update();

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
    displayLcd(pounch, timerCount, record, lastPounch);
    changeVariable(4, lastPounch);

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
      lastPounch = pounch;
      pounch = 0;
      timerCount = 60;
      changeVariable(1, pounch);
      changeVariable(2, timerCount);
      changeVariable(4, lastPounch);
      pause = true;

    }
  }
}

void recordCompare(int value) {
  if (value >= record) {
    record = value;
    changeVariable(3, value);
    top = true;
  }

}

void pounchClick() {
  Serial.println("schiacciato");
  if (!pause) {
    pounchTimer = 0;
    displayCountDown(pounchTimer);    
    pounch++;
    recordCompare(pounch);
    changeVariable(1, pounch);
    counterActive = true;
    activePounchTimer = true;
  }
}

void displayLcd(int pounch, int timer, int record) {
  lcd.clear();
  lcd.setCursor ( 0, 0 );            // go to the top left corner
  lcd.print("POUNCH"); // write this string on the top row

  lcd.setCursor ( 0, 1 );            // go to the 2nd row
  lcd.print(pounch); // pad string with spaces for centering
  lcd.setCursor ( 0, 2);            // go to the third row
  lcd.print("TIMER"); // pad with spaces for centering
  lcd.setCursor ( 0, 3 );            // go to the fourth row
  lcd.print(timer);
  lcd.setCursor ( 2, 3 );
  lcd.print("s");
  lcd.setCursor ( 8, 3 );
  lcd.print("RECORD");
  lcd.setCursor ( 16, 3 );
  lcd.print(record);
  lcd.setCursor ( 10, 0 );
  lcd.print("Delay");

}

void displayStatus(boolean state) {
  if (state) {
    lcd.setCursor ( 10, 1 );
    lcd.print("wait ");
  } else {
    lcd.setCursor ( 10, 1 );
    lcd.print("ready");
  }
}
void displayTop(boolean val) {
  if (!val) {
    lcd.clear();
    lcd.setCursor ( 7, 1 );
    lcd.print("LOOSER");
  } else {
    lcd.clear();
    lcd.setCursor ( 5, 1 );
    lcd.print("TOP RECORD");
  }
}
void displayCountDown(int value) {
  if (value == 0) {
    lcd.setCursor ( 19, 0 );
    lcd.print(" ");
  } else {
    lcd.setCursor ( 19, 0 );
    lcd.print(" ");
    lcd.setCursor ( 19, 0 );
    lcd.print(value);
  }

}
void changeVariable(int _case, int value) {

  switch (_case) {
    // pounch case
    case 1:
      lcd.setCursor ( 0, 1 );
      lcd.print("   ");
      lcd.setCursor ( 0, 1 );
      lcd.print(value);
      break;
    // timer case
    case 2:
      lcd.setCursor ( 0, 3 );
      lcd.print("  ");
      lcd.setCursor ( 0, 3 );
      lcd.print(value);
      break;
    // record case
    case 3:
      lcd.setCursor ( 16, 3 );
      lcd.print("   ");
      lcd.setCursor ( 16, 3 );
      lcd.print(value);
      break;
  }

}

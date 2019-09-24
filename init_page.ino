void initPageDisplay() {

  
  lcd.setCursor ( 0, 0 );            // go to the top left corner
  lcd.print("  POUNCH COUNTER "); // write this string on the top row
  lcd.setCursor ( 0, 1 );            // go to the 2nd row
  lcd.print("  -------------  "); // pad string with spaces for centering
  lcd.setCursor ( 0, 2 );            // go to the third row
  lcd.print("  Power by MASKA  "); // pad with spaces for centering
  lcd.setCursor ( 0, 3 );            // go to the fourth row
  lcd.print(" ______________ ");
}

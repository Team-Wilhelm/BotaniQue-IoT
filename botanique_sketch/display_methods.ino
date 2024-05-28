void displayMoodEmoji(int mood) {
  tft.fillScreen(ST77XX_WHITE);
  switch (mood) {
    case 0:
      drawEmojiBase(tft.color565(235, 23, 22));
      tft.fillRoundRect(105, 136, 30, 15, 10, ST77XX_BLACK);

      tft.fillCircle(89, 164, 8, ST77XX_BLACK);
      tft.fillCircle(89, 162, 8, ST77XX_BLACK);
      tft.fillCircle(92, 160, 8, ST77XX_BLACK);
      tft.fillCircle(97, 155, 8, ST77XX_BLACK);
      tft.fillCircle(101, 150, 8, ST77XX_BLACK);
      tft.fillCircle(106, 145, 8, ST77XX_BLACK);

      tft.fillCircle(134, 145, 8, ST77XX_BLACK);
      tft.fillCircle(139, 150, 8, ST77XX_BLACK);
      tft.fillCircle(143, 155, 8, ST77XX_BLACK);
      tft.fillCircle(148, 160, 8, ST77XX_BLACK);
      tft.fillCircle(151, 162, 8, ST77XX_BLACK);
      tft.fillCircle(151, 164, 8, ST77XX_BLACK);
      break;
    case 1:
      drawEmojiBase(tft.color565(251, 147, 24));
      tft.fillRoundRect(100, 142, 40, 15, 10, ST77XX_BLACK);

      tft.fillCircle(89, 162, 8, ST77XX_BLACK);
      tft.fillCircle(92, 160, 8, ST77XX_BLACK);
      tft.fillCircle(97, 155, 8, ST77XX_BLACK);
      tft.fillCircle(101, 152, 8, ST77XX_BLACK);

      tft.fillCircle(139, 152, 8, ST77XX_BLACK);
      tft.fillCircle(143, 155, 8, ST77XX_BLACK);
      tft.fillCircle(148, 160, 8, ST77XX_BLACK);
      tft.fillCircle(151, 162, 8, ST77XX_BLACK);
      break;
    case 2:
      drawEmojiBase(tft.color565(255, 209, 25));
      tft.fillRoundRect(85, 145, 70, 15, 10, ST77XX_BLACK);
      break;
    case 3:
      drawEmojiBase(tft.color565(179, 210, 31));
      tft.fillRoundRect(100, 158, 40, 15, 10, ST77XX_BLACK);

      tft.fillCircle(89, 152, 8, ST77XX_BLACK);
      tft.fillCircle(92, 155, 8, ST77XX_BLACK);
      tft.fillCircle(97, 160, 8, ST77XX_BLACK);
      tft.fillCircle(101, 162, 8, ST77XX_BLACK);

      tft.fillCircle(139, 162, 8, ST77XX_BLACK);
      tft.fillCircle(143, 160, 8, ST77XX_BLACK);
      tft.fillCircle(148, 155, 8, ST77XX_BLACK);
      tft.fillCircle(151, 152, 8, ST77XX_BLACK);

      break;
    case 4:
      drawEmojiBase(tft.color565(45, 196, 39));
      tft.fillRoundRect(105, 160, 30, 15, 10, ST77XX_BLACK);

      tft.fillCircle(87, 145, 8, ST77XX_BLACK);
      tft.fillCircle(89, 150, 8, ST77XX_BLACK);
      tft.fillCircle(92, 155, 8, ST77XX_BLACK);
      tft.fillCircle(97, 160, 8, ST77XX_BLACK);
      tft.fillCircle(101, 162, 8, ST77XX_BLACK);
      tft.fillCircle(105, 164, 8, ST77XX_BLACK);

      tft.fillCircle(135, 164, 8, ST77XX_BLACK);
      tft.fillCircle(139, 162, 8, ST77XX_BLACK);
      tft.fillCircle(143, 160, 8, ST77XX_BLACK);
      tft.fillCircle(148, 155, 8, ST77XX_BLACK);
      tft.fillCircle(151, 150, 8, ST77XX_BLACK);
      tft.fillCircle(153, 145, 8, ST77XX_BLACK);
      break;
  }
}

void drawEmojiBase(uint16_t color) {
  tft.fillScreen(tft.color565(59,59,59));
  tft.fillCircle(120, 120, 90, color);

  tft.fillCircle(85, 94, 9, ST77XX_BLACK);
  tft.fillCircle(85, 97, 9, ST77XX_BLACK);
  tft.fillCircle(85, 100, 9, ST77XX_BLACK);
  tft.fillCircle(155, 94, 9, ST77XX_BLACK);
  tft.fillCircle(155, 97, 9, ST77XX_BLACK);
  tft.fillCircle(155, 100, 9, ST77XX_BLACK);
}

void drawStatsScreen() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 10);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(3);
  tft.println("I am " + currentMoodString);
  tft.println("");
  tft.setTextSize(2);
  tft.println("Air humidity: " + String(airMoisture) + "%");
  tft.println("");
  tft.println("Light: ");
  tft.println("");
  tft.println("Soil moisture: " + String(soilMoisturePercentage) + "%");
  tft.println("");
  tft.println("Temperature: " + String(temperature) + "C");
  delay(5000);
  displayMoodEmoji(currentMood);
}
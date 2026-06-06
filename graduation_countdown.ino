/*********
  Graduation countdown timer. Counts down the days until 5/3/2026.
*********/

#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
RTC_DS3231 rtc;

const DateTime targetDate(2026, 5, 3, 0, 0, 0);

void setup() {
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  if (!rtc.begin()) {
    Serial.println(F("Couldn't find RTC"));
    for (;;);
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
}

void loop() {
  DateTime now = rtc.now();
  TimeSpan remaining = targetDate - now;

  int daysRemaining = (remaining.totalseconds() + 86399) / 86400;

  display.clearDisplay();
  display.setCursor(8, 0);
  display.setTextSize(2);
  display.println("Pitt 2026");
  display.setCursor(5, 22);
  display.println("graduation");
  display.setCursor(15, 47);
  display.print(daysRemaining);
  display.println(" days!");
  display.display();

  delay(60000);
}
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "video_frames.h"  // Your generated frames file

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // No reset pin (shared with ESP32)
#define OLED_ADDR     0x3C  // Common I2C address for 0.96" OLED

// Create display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Frame timing (adjust these for smooth playback)
const int FRAME_DELAY_MS = 66;  // 150ms = ~6-7 frames per second

// Playback settings
const bool LOOP_VIDEO = true;     // Set to false to play once and stop
const bool SHOW_FRAME_COUNT = false; // Set to true to show frame counter on display

// Countdown settings
const int COUNTDOWN_SECONDS = 3;  // Change this to set countdown duration

// Forward declaration
void playVideo();

void showCountdown(int seconds) {
  display.clearDisplay();
  display.setTextSize(2);  // Larger text for countdown
  display.setTextColor(SSD1306_WHITE);
  
  for (int i = seconds; i > 0; i--) {
    display.clearDisplay();
    
    // Optional: Add "Starting in..." text
    display.setTextSize(1);
    display.setCursor((SCREEN_WIDTH - 60) / 2, 15);
    display.print("Starting in");
    
    // Center the number on screen
    display.setTextSize(3);  // Even larger for the number
    char countText[8];
    snprintf(countText, sizeof(countText), "%d", i);
    int16_t x1, y1;
    uint16_t w, h;
    // Removed .c_str() since countText is already a char array
    display.getTextBounds(countText, 0, 0, &x1, &y1, &w, &h);
    int x = (SCREEN_WIDTH - w) / 2;
    int y = (SCREEN_HEIGHT - h) / 2;
    
    display.setCursor(x, y);
    display.print(countText);
    
    display.display();
    delay(1000);  // Wait 1 second
  }
  
  // Show "GO!" or "Start" message
  display.clearDisplay();
  display.setTextSize(2);
  char goText[] = "GO!";
  int16_t x1, y1;
  uint16_t w, h;
  // Removed .c_str() since goText is already a char array
  display.getTextBounds(goText, 0, 0, &x1, &y1, &w, &h);
  int x = (SCREEN_WIDTH - w) / 2;
  int y = (SCREEN_HEIGHT - h) / 2;
  display.setCursor(x, y);
  display.print(goText);
  display.display();
  delay(500);  // Brief pause before video starts
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Video Player...");
  
  // Initialize OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("SSD1306 allocation failed!"));
    Serial.println(F("Check wiring: SDA->GPIO21, SCL->GPIO22"));
    for(;;);  // Stop here if display not found
  }
  
  Serial.println("Display initialized successfully!");
  
  // Show countdown before playing
  showCountdown(COUNTDOWN_SECONDS);
  
  // Clear display after countdown
  display.clearDisplay();
  display.display();
}

void loop() {
  playVideo();
  
  if (!LOOP_VIDEO) {
    // Play once and stop
    Serial.println("Video finished. Stopping...");
    display.clearDisplay();
    display.setCursor(20, 25);
    display.println("Video End");
    display.display();
    while(1);  // Stop forever
  }
}

void playVideo() {
  unsigned long targetFrameTime = FRAME_DELAY_MS;  // Time per frame in ms
  unsigned long lastFrameTime = 0;
  
  for (int frameIndex = 0; frameIndex < TOTAL_FRAMES; frameIndex++) {
    unsigned long currentTime = millis();
    
    // Wait until it's time for the next frame
    if (lastFrameTime != 0) {
      unsigned long elapsed = currentTime - lastFrameTime;
      if (elapsed < targetFrameTime) {
        delay(targetFrameTime - elapsed);  // Wait the remaining time
      }
    }
    
    // Record when we're showing this frame
    lastFrameTime = millis();
    
    // Draw the current frame
    display.clearDisplay();
    display.drawBitmap(0, 0, FRAMES[frameIndex], SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
    
    // Optional: Show frame counter
    if (SHOW_FRAME_COUNT) {
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
      display.setCursor(0, 0);
      display.print(frameIndex + 1);
      display.print("/");
      display.print(TOTAL_FRAMES);
    }
    
    display.display();
    
    // Print progress every 30 frames
    if (frameIndex % 30 == 0) {
      Serial.print("Playing frame: ");
      Serial.print(frameIndex + 1);
      Serial.print("/");
      Serial.println(TOTAL_FRAMES);
    }
  }
  
  Serial.println("Video loop completed!");
}

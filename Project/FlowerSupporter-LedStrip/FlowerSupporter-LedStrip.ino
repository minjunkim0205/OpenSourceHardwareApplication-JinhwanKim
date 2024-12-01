#include <Adafruit_NeoPixel.h>

/*네오픽셀*/
#define LED_PIN 17 // 데이터 핀
#define LED_COUNT 7 // LED 소자 갯수
#define BRIGHTNESS 255 // 밝기(0~255)
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

/*Setup*/
void setup() {
  strip.begin();                    // 네오픽셀 초기화(필수)
  strip.setBrightness(BRIGHTNESS);  // 네오픽셀 밝기 설정 *RGBW만
  strip.show();
}

/*Main*/
void loop() {
  // 네오픽셀 LED 색(0~255)
  int color_r = 255;  // RED
  int color_g = 255;    // GREEN
  int color_b = 255;    // BLUE

  // 모든 네오픽셀에 색 설정하기
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, color_r, color_g, color_b, 0);
    // RGB일 경우 strip.setPixelColor(i, color_r, color_g, color_b);
  }
  // 네오픽셀 설정값 적용하기
  strip.show();
}
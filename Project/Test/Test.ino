#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT11.h>
#include <Adafruit_NeoPixel.h>

// 핀 설정
#define LED_PIN 17
#define LED_COUNT 7
#define LED_BRIGHTNESS 255
#define PIEZO_PIN 13
#define DHT11_PIN 14
#define POTENTIOMETER_PIN 12
// LCD 설정
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT11 dht(DHT11_PIN);

// Piezo 설정
const int SCALE[8] = { 262, 294, 330, 249, 392, 440, 494, 523 };

// Neo RGB 설정
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
const int GROW_LIGHT[7][3] = {
  {255, 0, 0},
  {255, 0, 0},
  {0, 0, 255},
  {255, 0, 0},
  {255, 0, 0},
  {0, 0, 255},
  {255, 0, 0}
};

// Wi-Fi 설정
const char *ssid = "iptime 2.4G - iot";
const char *password = "Iptime@iot@connect";

// 웹 서버 생성
AsyncWebServer server(80);

// 상태 변수
bool led_auto_mode = true;
bool day_mode = true;
float temperature = 0.0;
float humidity = 0.0;
int red_value = 255;
int green_value = 255;
int blue_value = 255;

// HTML 웹 페이지
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>Plant Assistant</title>
  <meta http-equiv="refresh" content="2">
  <style>
    body { font-family: Arial, sans-serif; text-align: center; background-color: #f0f8ff; }
    .button { padding: 10px; margin: 10px; font-size: 20px; }
    h1 { color: #2e8b57; }
    p { font-size: 18px; }
    .color-picker { margin: 20px; }
  </style>
</head>
<body>
  <h1>Plant Assistant</h1>
  <p><strong>Temperature:</strong> %TEMPERATURE% &deg;C</p>
  <p><strong>Humidity:</strong> %HUMIDITY% %</p>
  <p><strong>Led Mode:</strong> %LEDMODE%</p>

  <div class="color-picker">
    <label for="red">Red: </label>
    <input type="range" id="red" min="0" max="255" value="255">
    <br>
    <label for="green">Green: </label>
    <input type="range" id="green" min="0" max="255" value="255">
    <br>
    <label for="blue">Blue: </label>
    <input type="range" id="blue" min="0" max="255" value="255">
  </div>

  <button class="button" onclick="setMode('auto')">Auto Mode</button>
  <button class="button" onclick="setMode('manual')">Manual Mode</button>

  <script>
    function setMode(mode) {
      fetch(`/setMode?mode=${mode}`)
        .then(response => response.text())
        .then(data => {
          //alert(data); // 서버 알람 응답(테스트용 꺼놨음 지금은)
        });
    }

    // 슬라이더 값이 변경될 때마다 RGB 값을 서버에 자동으로 전송
    document.getElementById("red").addEventListener("input", applyColor);
    document.getElementById("green").addEventListener("input", applyColor);
    document.getElementById("blue").addEventListener("input", applyColor);

    function applyColor() {
      const red = document.getElementById("red").value;
      const green = document.getElementById("green").value;
      const blue = document.getElementById("blue").value;
      fetch(`/setColor?red=${red}&green=${green}&blue=${blue}`)
        .then(response => response.text())
        .then(data => {
          // 서버에서 응답 받은 메시지 출력
          console.log(data);
        });
    }

    // 페이지가 로드될 때마다 RGB 값을 서버에서 받아 슬라이더에 적용
    window.onload = function() {
      updateColorFromServer();  // 처음 로드 시 RGB 값을 서버에서 가져옴
    };

    // 2초마다 RGB 값을 서버에서 가져오는 함수
    function updateColorFromServer() {
      fetch('/getColor')
        .then(response => response.text())
        .then(data => {
          const colorData = data.split(" ");
          const red = colorData[0].split(":")[1];
          const green = colorData[1].split(":")[1];
          const blue = colorData[2].split(":")[1];

          // 서버에서 받은 RGB 값을 슬라이더에 적용
          document.getElementById("red").value = red;
          document.getElementById("green").value = green;
          document.getElementById("blue").value = blue;
        });
    }
  </script>
</body>
</html>
)rawliteral";

void setup() {
  // 시리얼 초기화
  Serial.begin(115200);

  // Piezo 초기화
  pinMode(PIEZO_PIN, OUTPUT);

  // LCD 초기화
  lcd.init();
  lcd.backlight();

  // Neo RGB 초기화
  strip.begin();
  strip.setBrightness(LED_BRIGHTNESS);
  strip.show();

  // POTENTIOMETER 초기화
  pinMode(POTENTIOMETER_PIN, OUTPUT);

  // Wi-Fi 연결
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi Connected!");
  Serial.println(WiFi.localIP());
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("[ Local Ip ]");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  delay(2500);
  tone(PIEZO_PIN, SCALE[0], 250);

  // 웹 서버 라우트 설정
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    String html = index_html;
    html.replace("%TEMPERATURE%", String(temperature, 1));
    html.replace("%HUMIDITY%", String(humidity, 1));
    html.replace("%LEDMODE%", (led_auto_mode ? "Auto" : "Manual"));
    request->send(200, "text/html", html);
  });

  server.on("/setMode", HTTP_GET, [](AsyncWebServerRequest *request) {
    tone(PIEZO_PIN, SCALE[0], 250);
    if (request->hasParam("mode")) {
      String mode = request->getParam("mode")->value();
      led_auto_mode = (mode == "auto");
      request->send(200, "text/plain", "Mode set to " + mode);
    } else {
      request->send(400, "text/plain", "Missing 'mode' parameter");
    }
  });

  // RGB 색상 설정 라우트
  server.on("/setColor", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (request->hasParam("red") && request->hasParam("green") && request->hasParam("blue")) {
      red_value = request->getParam("red")->value().toInt();
      green_value = request->getParam("green")->value().toInt();
      blue_value = request->getParam("blue")->value().toInt();
      request->send(200, "text/plain", "Color set to R:" + String(red_value) + " G:" + String(green_value) + " B:" + String(blue_value));
    } else {
      request->send(400, "text/plain", "Missing RGB parameters");
    }
  });

  // RGB 값 반환 라우트
  server.on("/getColor", HTTP_GET, [](AsyncWebServerRequest *request) {
    String colorData = "R:" + String(red_value) + " G:" + String(green_value) + " B:" + String(blue_value);
    request->send(200, "text/plain", colorData);
  });

  // 404 핸들러
  server.onNotFound([](AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not Found");
  });

  // 서버 시작
  server.begin();
}

void loop() {
  // Sensor value update
  int light_level = analogRead(POTENTIOMETER_PIN);
  Serial.println(light_level);
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  // Led update
  if(led_auto_mode){
    for (int i = 0; i < LED_COUNT; i++) {
      strip.setPixelColor(i, GROW_LIGHT[i][0], GROW_LIGHT[i][1], GROW_LIGHT[i][2], 0);
    }
  }else{
    for (int i = 0; i < LED_COUNT; i++) {
      strip.setPixelColor(i, red_value, green_value, blue_value, 0);
    }
  }
  strip.show();
  // LCD update
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature);
  lcd.print(" H:");
  lcd.print(humidity);
  lcd.setCursor(0, 1);
  lcd.print("Mode : ");
  lcd.print(led_auto_mode ? "Auto" : "Manual");
  delay(200);
}

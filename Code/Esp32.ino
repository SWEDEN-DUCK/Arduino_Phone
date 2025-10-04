#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int BackNP = 0;  // Back, Next, Previous
int NP = 0;      // Next, Previous
int currentApp = 0;
int SPR = 0;
bool inMenu = true;
bool inPass = false;
bool inSW = false;

// Buttons
const int Button_U = 6;
const int Button_D = 7;
const int Button_L = 5;
const int Button_R = 10;
const int Button_OK = 20;

// Setting hours, minutes, seconds, and milliseconds to 0
int h = 0;
int m = 0;
int s = 0;
int ms = 0;

unsigned long previousMillis = 0;
bool running = false;

int calcStep = 0;  // 0 = first number, 1 = operator, 2 = second number
int num1 = 0;
int num2 = 0;
int result = 0;
int opIndex = 0;  // 0=+, 1=-, 2=*, 3=/
const char* ops[] = { "+", "-", "*", "/" };
float evaluateExpression(String expr);

bool isJumping = false;
bool gameOver = false;
int PlayerY = 40;
int velocity = 0;
const int gravity = 2;
const int groundY = 40;

float PillarX1 = 128.0;
float PillarX2 = 180.0;
float gameSpeed = 3.0;

unsigned long lastSpeedIncrease = 0;
unsigned long lastFrame = 0;
unsigned long score = 0;
unsigned long highScore = 0;

bool buttonPressed = false;

// Functions
bool rectCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
  return !(x1 + w1 < x2 || x1 > x2 + w2 || y1 + h1 < y2 || y1 > y2 + h2);
}

void setup() {
  Wire.begin(8, 9);
  Serial.begin(115200);

  pinMode(Button_U, INPUT_PULLUP);
  pinMode(Button_D, INPUT_PULLUP);
  pinMode(Button_L, INPUT_PULLUP);
  pinMode(Button_R, INPUT_PULLUP);
  pinMode(Button_OK, INPUT_PULLUP);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.display();

  EEPROM.begin(512);
  highScore = EEPROM.read(0);

  delay(1000);
  menu();
}

void loop() {
  if (inMenu) {
    menu();
    delay(100);
  } else if (currentApp == 0) {
    Calculator();
    delay(100);
  } else if (currentApp == 1) {
    Game_Spike();
  } else if (currentApp == 2) {
    password();
    delay(100);
  } else if (currentApp == 3) {
    Stopwatch();
    delay(100);
  } else {
  }
}

void menu() {
  delay(100);
  inMenu = true;

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);

  // Calculator
  display.setCursor(2, 11);
  display.println("Calc");

  // Game 1
  display.setCursor(30, 11);
  display.println("Game");

  // Passwords
  display.setCursor(58, 11);
  display.println("Pass");

  // Stopwatch
  display.setCursor(86, 11);
  display.println("Stop");

  // Underline current selection
  if (currentApp == 0) {
    display.setCursor(2, 13);
    display.println("____");
  } else if (currentApp == 1) {
    display.setCursor(30, 13);
    display.println("____");
  } else if (currentApp == 2) {
    display.setCursor(58, 13);
    display.println("____");
  } else if (currentApp == 3) {
    display.setCursor(86, 13);
    display.println("____");
  }

  display.display();

  if (digitalRead(Button_L) == LOW) {
    currentApp++;                        // Right = next app
    if (currentApp > 3) currentApp = 0;  // Wrap
    delay(150);
  }

  if (digitalRead(Button_R) == LOW) {
    currentApp--;                        // Left = previous app
    if (currentApp < 0) currentApp = 3;  // Wrap
    delay(150);
  }

  if (digitalRead(Button_OK) == LOW) {
    if (currentApp == 0) Calculator();
    else if (currentApp == 1) Game_Spike();
    else if (currentApp == 2) password();
    else if (currentApp == 3) Stopwatch();
    delay(200);
    inMenu = false;  // Leave menu
    delay(200);
  }
}

void password() {
  inPass = true;

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);

  // GUI
  display.setCursor(2, 11);
  display.println("Back");
  display.setCursor(40, 11);
  display.println("<");
  display.setCursor(50, 11);
  display.println(">");

  if (BackNP == 0) {
    display.setCursor(2, 13);
    display.println("____");
  } else if (BackNP == 1) {
    display.setCursor(40, 13);
    display.println("_");
  } else if (BackNP == 2) {
    display.setCursor(50, 13);
    display.println("_");
  }

  if (digitalRead(Button_L) == LOW) {
    BackNP++;
    if (BackNP > 2) BackNP = 0;
    delay(150);
  }
  if (digitalRead(Button_R) == LOW) {
    BackNP--;
    if (BackNP < 0) BackNP = 2;
    delay(150);
  }
//======== Add howerver many of this as you wamt just make shore to change the NP == X to the next number thats free. I have made 2 starting but you can expand it. ===========
  if (NP == 0) {
    display.setCursor(0, 26);
    display.println("your@email.com");
    display.setCursor(0, 36);
    display.println("Password123!");
  } else if (NP == 1) {
    display.setCursor(0, 26);
    display.println("mine@email.com");
    display.setCursor(0, 36);
    display.println("CoolGuy2?");
  }

  display.display();

  if (digitalRead(Button_OK) == LOW) {
    if (BackNP == 0) {
      menu();
      delay(200);
      inPass = false;  // Leave password
    } else if (BackNP == 1) {
      NP--;
      delay(100);
    } else if (BackNP == 2) {
      NP++;
      delay(100);
    }
  }
}

void Stopwatch() {
  inSW = true;

  // Read button presses for navigation
  if (digitalRead(Button_R) == LOW) {
    SPR--;
    if (SPR < 0) SPR = 3;
    delay(150);
  }

  if (digitalRead(Button_L) == LOW) {
    SPR++;
    if (SPR > 3) SPR = 0;
    delay(150);
  }

  if (digitalRead(Button_OK) == LOW) {
    if (SPR == 0) {
      menu();  // Back to menu
      inSW = false;
      return;
    } else if (SPR == 1) {  // Start
      running = true;
    } else if (SPR == 2) {  // Pause/stop
      running = false;
    } else if (SPR == 3) {  // Reset
      stopwatch_reset();
    }
    delay(200);
  }

  // Count time if running is true
  if (running) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 1000) {
      previousMillis = currentMillis;
      s++;
      if (s >= 60) {
        s = 0;
        m++;
        if (m >= 60) {
          m = 0;
          h++;
        }
      }
    }
  }

  // Draw GUI
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);

  // Menu indicators
  display.setCursor(2, 11);
  display.println("Back");
  display.setCursor(40, 11);
  display.println(">");
  display.setCursor(60, 11);
  display.println("||");
  display.setCursor(80, 11);
  display.println("R");

  // Highlight selected button (underline)
  if (SPR == 0) {
    display.setCursor(2, 13);
    display.println("____");
  } else if (SPR == 1) {
    display.setCursor(40, 13);
    display.println("_");
  } else if (SPR == 2) {
    display.setCursor(60, 13);
    display.println("__");
  } else if (SPR == 3) {
    display.setCursor(80, 13);
    display.println("_");
  }

  // Display time
  display.setCursor(20, 35);
  display.setTextSize(2);
  char timeBuffer[10];
  sprintf(timeBuffer, "%02d:%02d:%02d", h, m, s);
  display.print(timeBuffer);

  display.display();
}

void stopwatch_reset() {
  h = 0;
  m = 0;
  s = 0;
  previousMillis = millis();
}

void Game_Spike() {
  unsigned long currentTime = millis();
  if (currentTime - lastFrame < 50) return;
  lastFrame = currentTime;

  // Back to menu
  if (digitalRead(Button_D) == LOW) {
    menu();
    return;
  }

  int buttonState = digitalRead(Button_U);

  // Game over
  if (gameOver) {
    if (buttonState == HIGH && !buttonPressed) {
      buttonPressed = true;
    }

    if (buttonState == LOW && buttonPressed) {
      buttonPressed = false;
      SweepEffect(10);
      resetGame();
    }
    return;
  }

  // Jump
  if (buttonState == LOW && !buttonPressed && PlayerY == groundY) {
    buttonPressed = true;
    isJumping = true;
    velocity = -13;
  }
  if (buttonState == HIGH) {
    buttonPressed = false;
  }

  // Physics
  if (isJumping) {
    PlayerY += velocity;
    velocity += gravity;
    if (PlayerY >= groundY) {
      PlayerY = groundY;
      isJumping = false;
    }
  }

  PillarX1 -= gameSpeed;
  PillarX2 -= gameSpeed;

  if (PillarX1 < -10) PillarX1 = 128 + random(15, 60);
  if (PillarX2 < -10) PillarX2 = 128 + random(15, 60);

  if (currentTime - lastSpeedIncrease > 2000) {
    gameSpeed += 0.2;
    lastSpeedIncrease = currentTime;
  }

  score++;

  // Draw display
  display.clearDisplay();
  display.fillRoundRect(10, PlayerY, 8, 14, 4, SSD1306_WHITE);
  display.fillTriangle((int)PillarX1, groundY + 17, (int)PillarX1 + 5, groundY, (int)PillarX1 + 10, groundY + 17, SSD1306_WHITE);
  display.fillTriangle((int)PillarX2, groundY + 17, (int)PillarX2 + 5, groundY, (int)PillarX2 + 10, groundY + 17, SSD1306_WHITE);
  display.drawLine(0, 58, 128, 58, SSD1306_WHITE);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Score: ");
  display.print(score / 10);
  display.display();

  // Collision detection
  bool hit1 = rectCollision(10, PlayerY, 8, 14, (int)PillarX1, groundY, 10, 15);
  bool hit2 = rectCollision(10, PlayerY, 8, 14, (int)PillarX2, groundY, 10, 15);

  if (hit1 || hit2) {
    gameOver = true;
    if (score > highScore) {
      highScore = score;
      EEPROM.put(0, highScore);
      EEPROM.commit();
    }

    SweepEffect(10);
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(43, 0);
    display.print("Score:");
    display.print(score / 10);
    display.setCursor(26, 40);
    display.print("High Score:");
    display.print(highScore / 10);
    display.setTextSize(2);
    display.setCursor(12, 15);
    display.print("Game Over");
    display.setTextSize(1);
    display.setCursor(15, 55);
    display.print("Press to restart");
    display.display();
  }
}

void resetGame() {
  isJumping = false;
  PlayerY = groundY;
  velocity = 0;
  PillarX1 = 128.0;
  PillarX2 = 180.0;
  gameSpeed = 3.0;
  score = 0;
  gameOver = false;
  lastSpeedIncrease = millis();
  lastFrame = millis();
  display.clearDisplay();
  display.display();
}

void SweepEffect(int speed) {
  for (int i = 0; i < display.width(); i += speed) {
    display.fillRect(i, 0, speed, display.height(), WHITE);
    display.display();
  }
  for (int i = 0; i < display.width(); i += speed) {
    display.fillRect(i, 0, speed, display.height(), BLACK);
    display.display();
  }
}

void Calculator() {
  static String expression = "";  // Holds the whole expression e.g. "7+2*5/2"
  static float result = 0;
  static int selRow = 0, selCol = 0;

  const char* buttons[5][4] = {
    { "7", "8", "9", "+" },
    { "4", "5", "6", "-" },
    { "1", "2", "3", "*" },
    { "0", ".", "=", "/" },
    { "Del", "(", ")", "Back" }  // New row: parentheses between Del and Back
  };

  // Navigation
  if (digitalRead(Button_U) == LOW) { selRow--; if (selRow < 0) selRow = 4; delay(150); }
  if (digitalRead(Button_D) == LOW) { selRow++; if (selRow > 4) selRow = 0; delay(150); }
  if (digitalRead(Button_L) == LOW) { selCol++; if (selCol > 3) selCol = 0; delay(150); }
  if (digitalRead(Button_R) == LOW) { selCol--; if (selCol < 0) selCol = 3; delay(150); }

  // OK button
  if (digitalRead(Button_OK) == LOW) {
    String key = String(buttons[selRow][selCol]);
    if (key == "Del") {
      if (expression.length() > 0) expression.remove(expression.length() - 1);
    } else if (key == "Back") {
      expression = "";
      result = 0;
      menu();
      return;
    } else if (key == "=") {
      result = evaluateExpression(expression.c_str());
    } else if (key != "") {
      if (expression.length() < 32) expression += key;
    }
    delay(250);
  }

  // Draw display
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Result: ");
  if (isnan(result)) display.print("Err"); else display.print(result);
  display.setCursor(0, 10);
  display.print(expression);

  int startY = 24;
  for (int r = 0; r < 5; r++) {
    for (int c = 0; c < 4; c++) {
      String label = buttons[r][c];
      if (label == "") continue;
      int x = c * 30 + 2;
      int y = startY + r * 8;
      display.setCursor(x, y);
      display.print(label);
      if (r == selRow && c == selCol) display.drawRect(x - 2, y - 1, 25, 9, WHITE);
    }
  }

  display.display();
}


// This function can calculate long expressions, e.g. (7+2*5)/2-3
float evaluateExpression(String expr) {
  expr.replace(" ", "");  // Remove spaces

  // Handle parentheses first
  int openIndex = expr.lastIndexOf('(');
  while (openIndex != -1) {
    int closeIndex = expr.indexOf(')', openIndex);
    if (closeIndex == -1) break;  // Invalid parenthesis
    String inner = expr.substring(openIndex + 1, closeIndex);
    float innerResult = evaluateExpression(inner);
    expr = expr.substring(0, openIndex) + String(innerResult) + expr.substring(closeIndex + 1);
    openIndex = expr.lastIndexOf('(');
  }

  // Handle * and / first
  for (int i = 0; i < expr.length(); i++) {
    if (expr[i] == '*' || expr[i] == '/') {
      int leftStart = i - 1;
      while (leftStart >= 0 && (isDigit(expr[leftStart]) || expr[leftStart] == '.')) leftStart--;
      String left = expr.substring(leftStart + 1, i);
      int rightEnd = i + 1;
      while (rightEnd < expr.length() && (isDigit(expr[rightEnd]) || expr[rightEnd] == '.')) rightEnd++;
      String right = expr.substring(i + 1, rightEnd);
      float a = left.toFloat();
      float b = right.toFloat();
      float res = (expr[i] == '*') ? a * b : (b != 0 ? a / b : NAN);
      expr = expr.substring(0, leftStart + 1) + String(res) + expr.substring(rightEnd);
      i = -1;  // Start over
    }
  }

  // Handle + and -
  for (int i = 1; i < expr.length(); i++) {  // Start at 1 to not interpret first char as minus
    if (expr[i] == '+' || expr[i] == '-') {
      int leftStart = i - 1;
      while (leftStart >= 0 && (isDigit(expr[leftStart]) || expr[leftStart] == '.')) leftStart--;
      String left = expr.substring(leftStart + 1, i);
      int rightEnd = i + 1;
      while (rightEnd < expr.length() && (isDigit(expr[rightEnd]) || expr[rightEnd] == '.')) rightEnd++;
      String right = expr.substring(i + 1, rightEnd);
      float a = left.toFloat();
      float b = right.toFloat();
      float res = (expr[i] == '+') ? a + b : a - b;
      expr = expr.substring(0, leftStart + 1) + String(res) + expr.substring(rightEnd);
      i = -1;
    }
  }

  return expr.toFloat();
}

#include <Wire.h>
#include <Adafruit_NeoPixel.h>

const int STRIP_PIN = 11;
const int NUM_PIXELS = 103;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, STRIP_PIN);
Adafruit_NeoPixel incomeStrip = Adafruit_NeoPixel(3, 5);
Adafruit_NeoPixel raceStrip = Adafruit_NeoPixel(3, 4);
Adafruit_NeoPixel educationStrip = Adafruit_NeoPixel(4, 3);

int incomeOn = -1;
int raceOn = -1;
int educationOn = -1;

bool isOutro = false;

void setup() {
  Serial.begin(115200);

  strip.begin();

  turnOnLabels();

  // Start the I2C Bus as Slave on address 9
  Wire.begin(9);
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);
}

void loop() {
  if (isOutro) {
    allPixelsOff();
  } else {
    setRacePixels();
    setIncomePixels();
    setEducationPixels() ;
  }

  strip.show();

  /** GLOBAL DELAY **/
  delay(30);
}

void turnOnLabels() {
  incomeStrip.begin();
  for (int i = 0; i < 3; i++) {
    incomeStrip.setPixelColor(i, 255, 160, 0);
  }
  incomeStrip.show();

  raceStrip.begin();
  for (int j = 0; j < 3; j++) {
    raceStrip.setPixelColor(j, 0, 120, 60);
  }
  raceStrip.show();

  educationStrip.begin();
  for (int i = 0; i < 4; i++) {
    educationStrip.setPixelColor(i, 200, 20, 50);
  }
  educationStrip.show();
}

void turnOffLabels() {
  incomeStrip.begin();
  for (int i = 0; i < 3; i++) {
    incomeStrip.setPixelColor(i, 0, 0, 0);
  }
  incomeStrip.show();

  raceStrip.begin();
  for (int j = 0; j < 3; j++) {
    raceStrip.setPixelColor(j, 0, 0, 0);
  }
  raceStrip.show();

  educationStrip.begin();
  for (int i = 0; i < 4; i++) {
    educationStrip.setPixelColor(i, 0, 0, 0);
  }
  educationStrip.show();
}


void receiveEvent(int bytes) {
  while (Wire.available() > 0) {
    //Read one value from the I2C
    char receivedChar = Wire.read();
    Serial.println(receivedChar);

    //If the value received was true turn the led on, otherwise turn it off
    if (receivedChar == 'Q') {
      incomeOn = 0;
    }
    else if (receivedChar == 'W') {
      incomeOn = 1;
    }
    else if (receivedChar == 'E') {
      incomeOn = 2;
    }
    else if (receivedChar == 'R') {
      incomeOn = 3;
    }

    else if (receivedChar == 'A') {
      raceOn = 4;
    }
    else if (receivedChar == 'S') {
      raceOn = 7;
    }
    else if (receivedChar == 'D') {
      raceOn = 8;
    }
    else if (receivedChar == 'F') {
      raceOn = 5;
    }
    else if (receivedChar == 'G') {
      raceOn = 6;
    }

    else if (receivedChar == 'Z') {
      educationOn = 9;
    }
    else if (receivedChar == 'X') {
      educationOn = 10;
    }
    else if (receivedChar == 'C') {
      educationOn = 11;
    }
    else if (receivedChar == 'V') {
      educationOn = 12;
    }
    else if (receivedChar == 'B') {
      educationOn = 13;
    }
    else if (receivedChar == 'I') {
      // RESET lights (on)
      incomeOn = -1;
      raceOn = -1;
      educationOn = -1;
      isOutro = false;
      turnOnLabels();
    }
    else if (receivedChar == '0') {
      // DIM lights
      isOutro = true;
      turnOffLabels();
    }
  }
}

void allPixelsOff() {
  for (int i = 0; i < 103; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
}

void setIncomePixels() {
  for (int i = 70; i < 103; i++) {
    strip.setPixelColor(i, 50, 50, 50);

    if ( incomeOn == 0 ) {
      Serial.println("lower");
      strip.setPixelColor(70, 255, 160, 0);
      strip.setPixelColor(71, 255, 160, 0);
      strip.setPixelColor(72, 255, 160, 0);
      strip.setPixelColor(73, 255, 160, 0);
      strip.setPixelColor(74, 255, 160, 0);
      strip.setPixelColor(75, 255, 160, 0);
      strip.setPixelColor(76, 255, 160, 0);
      strip.setPixelColor(77, 255, 160, 0);
    }

    else if ( incomeOn == 1) {
      Serial.println("middle");
      strip.setPixelColor(78, 255, 160, 0);
      strip.setPixelColor(79, 255, 160, 0);
      strip.setPixelColor(80, 255, 160, 0);
      strip.setPixelColor(81, 255, 160, 0);
      strip.setPixelColor(82, 255, 160, 0);
      strip.setPixelColor(83, 255, 160, 0);
      strip.setPixelColor(84, 255, 160, 0);
      strip.setPixelColor(85, 255, 160, 0);
    }

    else if ( incomeOn == 2) {
      Serial.println("upper-middle");
      strip.setPixelColor(86, 255, 160, 0);
      strip.setPixelColor(87, 255, 160, 0);
      strip.setPixelColor(88, 255, 160, 0);
      strip.setPixelColor(89, 255, 160, 0);
      strip.setPixelColor(90, 255, 160, 0);
      strip.setPixelColor(91, 255, 160, 0);
      strip.setPixelColor(92, 255, 160, 0);
      strip.setPixelColor(93, 255, 160, 0);
    }
    else if ( incomeOn == 3) {
      Serial.println("upper");
      strip.setPixelColor(94, 255, 160, 0);
      strip.setPixelColor(95, 255, 160, 0);
      strip.setPixelColor(96, 255, 160, 0);
      strip.setPixelColor(97, 255, 160, 0);
      strip.setPixelColor(98, 255, 160, 0);
      strip.setPixelColor(99, 255, 160, 0);
      strip.setPixelColor(100, 255, 160, 0);
      strip.setPixelColor(101, 255, 160, 0);
      strip.setPixelColor(102, 255, 160, 0);
    }
  }
}

void setRacePixels() {
  for (int i = 34; i < 70; i++) {
    strip.setPixelColor(i, 50, 50, 50);

    if ( raceOn == 4 ) {
      Serial.println("black");
      strip.setPixelColor(61, 0, 120, 60);
      strip.setPixelColor(62, 0, 120, 60);
      strip.setPixelColor(63, 0, 120, 60);
      strip.setPixelColor(64, 0, 120, 60);
      strip.setPixelColor(65, 0, 120, 60);
      strip.setPixelColor(66, 0, 120, 60);
      strip.setPixelColor(67, 0, 120, 60);
      strip.setPixelColor(68, 0, 120, 60);
      strip.setPixelColor(69, 0, 120, 60);
    }

    else if ( raceOn == 5 ) {
      Serial.println("hispanic");
      strip.setPixelColor(48, 0, 120, 60);
      strip.setPixelColor(49, 0, 120, 60);
      strip.setPixelColor(50, 0, 120, 60);
      strip.setPixelColor(51, 0, 120, 60);
      strip.setPixelColor(52, 0, 120, 60);
      strip.setPixelColor(53, 0, 120, 60);
    }

    else if ( raceOn == 6 ) {
      Serial.println("other");
      strip.setPixelColor(54, 0, 120, 60);
      strip.setPixelColor(55, 0, 120, 60);
      strip.setPixelColor(56, 0, 120, 60);
      strip.setPixelColor(57, 0, 120, 60);
      strip.setPixelColor(58, 0, 120, 60);
      strip.setPixelColor(59, 0, 120, 60);
      strip.setPixelColor(60, 0, 120, 60);
    }

    else if ( raceOn == 7 ) {
      Serial.println("asian");
      strip.setPixelColor(41, 0, 120, 60);
      strip.setPixelColor(42, 0, 120, 60);
      strip.setPixelColor(43, 0, 120, 60);
      strip.setPixelColor(44, 0, 120, 60);
      strip.setPixelColor(45, 0, 120, 60);
      strip.setPixelColor(46, 0, 120, 60);
      strip.setPixelColor(47, 0, 120, 60);
    }

    else if ( raceOn == 8 ) {
      Serial.println("white");
      strip.setPixelColor(34, 0, 120, 60);
      strip.setPixelColor(35, 0, 120, 60);
      strip.setPixelColor(36, 0, 120, 60);
      strip.setPixelColor(37, 0, 120, 60);
      strip.setPixelColor(38, 0, 120, 60);
      strip.setPixelColor(39, 0, 120, 60);
      strip.setPixelColor(40, 0, 120, 60);
    }
  }
}

void setEducationPixels() {
  for (int i = 0; i < 34; i++) {
    strip.setPixelColor(i, 50, 50, 50);

    if ( educationOn == 9 ) {
      Serial.println("less-than-high-school");
      strip.setPixelColor(28, 200, 20, 50);
      strip.setPixelColor(29, 200, 20, 50);
      strip.setPixelColor(30, 200, 20, 50);
      strip.setPixelColor(31, 200, 20, 50);
      strip.setPixelColor(32, 200, 20, 50);
      strip.setPixelColor(33, 200, 20, 50);
    }

    else if ( educationOn == 10 ) {
      Serial.println("high-school");
      strip.setPixelColor(0, 200, 20, 50);
      strip.setPixelColor(1, 200, 20, 50);
      strip.setPixelColor(2, 200, 20, 50);
      strip.setPixelColor(3, 200, 20, 50);
      strip.setPixelColor(4, 200, 20, 50);
      strip.setPixelColor(5, 200, 20, 50);
      strip.setPixelColor(6, 200, 20, 50);
    }

    else if ( educationOn == 11 ) {
      Serial.println("some-college");
      strip.setPixelColor(7, 200, 20, 50);
      strip.setPixelColor(8, 200, 20, 50);
      strip.setPixelColor(9, 200, 20, 50);
      strip.setPixelColor(10, 200, 20, 50);
      strip.setPixelColor(11, 200, 20, 50);
      strip.setPixelColor(12, 200, 20, 50);
      strip.setPixelColor(13, 200, 20, 50);
    }

    else if ( educationOn == 12 ) {
      Serial.println("bachelors");
      strip.setPixelColor(14, 200, 20, 50);
      strip.setPixelColor(15, 200, 20, 50);
      strip.setPixelColor(16, 200, 20, 50);
      strip.setPixelColor(17, 200, 20, 50);
      strip.setPixelColor(18, 200, 20, 50);
      strip.setPixelColor(19, 200, 20, 50);
      strip.setPixelColor(20, 200, 20, 50);
    }

    else if ( educationOn == 13 ) {
      Serial.println("advanced");
      strip.setPixelColor(21, 200, 20, 50);
      strip.setPixelColor(22, 200, 20, 50);
      strip.setPixelColor(23, 200, 20, 50);
      strip.setPixelColor(24, 200, 20, 50);
      strip.setPixelColor(25, 200, 20, 50);
      strip.setPixelColor(26, 200, 20, 50);
      strip.setPixelColor(27, 200, 20, 50);
    }
  }
}

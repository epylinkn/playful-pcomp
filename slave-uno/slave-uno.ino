#include <Wire.h>
#include <Adafruit_NeoPixel.h>

const int STRIP_PIN = 11;
const int NUM_PIXELS = 103;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, STRIP_PIN);
//int incomeLights[] = {70, 78, 86, 94};

int incomeOn = NULL; // Off = 0 On = 1
int raceOn = NULL;
int educationOn = NULL;

void setup() {
  Serial.begin(115200);
  strip.begin();

  // Start the I2C Bus as Slave on address 9
  Wire.begin(9);
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);
}

void loop() {
  setRacePixels();
  setIncomePixels();
  setEducationPixels() ;

  strip.show();
  delay(30);
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
      raceOn = 5;
    }
    else if (receivedChar == 'D') {
      raceOn = 6;
    }
    else if (receivedChar == 'F') {
      raceOn = 7;
    }
    else if (receivedChar == 'G') {
      raceOn = 8;
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
    else if (receivedChar == 'M') {
      incomeOn = NULL;
      raceOn = NULL;
      educationOn = NULL;
    }
  }
}


void setIncomePixels() {
  for (int i = 70; i < 103; i++) {
    strip.setPixelColor(i, 50, 50, 50);

    if ( incomeOn == 0 ) {
      Serial.println("lower");
      strip.setPixelColor(70, 255, 0, 0);
      strip.setPixelColor(71, 255, 0, 0);
      strip.setPixelColor(72, 255, 0, 0);
      strip.setPixelColor(73, 255, 0, 0);
      strip.setPixelColor(74, 255, 0, 0);
      strip.setPixelColor(75, 255, 0, 0);
      strip.setPixelColor(76, 255, 0, 0);
      strip.setPixelColor(77, 255, 0, 0);
    }

    else if ( incomeOn == 1) {
      Serial.println("middle");
      strip.setPixelColor(78, 255, 0, 0);
      strip.setPixelColor(79, 255, 0, 0);
      strip.setPixelColor(80, 255, 0, 0);
      strip.setPixelColor(81, 255, 0, 0);
      strip.setPixelColor(82, 255, 0, 0);
      strip.setPixelColor(83, 255, 0, 0);
      strip.setPixelColor(84, 255, 0, 0);
      strip.setPixelColor(85, 255, 0, 0);
    }

    else if ( incomeOn == 2) {
      Serial.println("upper-middle");
      strip.setPixelColor(86, 255, 0, 0);
      strip.setPixelColor(87, 255, 0, 0);
      strip.setPixelColor(88, 255, 0, 0);
      strip.setPixelColor(89, 255, 0, 0);
      strip.setPixelColor(90, 255, 0, 0);
      strip.setPixelColor(91, 255, 0, 0);
      strip.setPixelColor(92, 255, 0, 0);
      strip.setPixelColor(93, 255, 0, 0);
    }
    else if ( incomeOn == 3) {
      Serial.println("upper");
      strip.setPixelColor(94, 255, 0, 0);
      strip.setPixelColor(95, 255, 0, 0);
      strip.setPixelColor(96, 255, 0, 0);
      strip.setPixelColor(97, 255, 0, 0);
      strip.setPixelColor(98, 255, 0, 0);
      strip.setPixelColor(99, 255, 0, 0);
      strip.setPixelColor(100, 255, 0, 0);
      strip.setPixelColor(101, 255, 0, 0);
      strip.setPixelColor(102, 255, 0, 0);
    }
  }
}

void setRacePixels() {
  for (int i = 34; i < 70; i++) {
    strip.setPixelColor(i, 50, 50, 50);

    if ( raceOn == 4 ) {
      Serial.println("black");
      strip.setPixelColor(61, 0, 255, 0);
      strip.setPixelColor(62, 0, 255, 0);
      strip.setPixelColor(63, 0, 255, 0);
      strip.setPixelColor(64, 0, 255, 0);
      strip.setPixelColor(65, 0, 255, 0);
      strip.setPixelColor(66, 0, 255, 0);
      strip.setPixelColor(67, 0, 255, 0);
      strip.setPixelColor(68, 0, 255, 0);
      strip.setPixelColor(69, 0, 255, 0);
    }

    else if ( raceOn == 5 ) {
      Serial.println("hispanic");
      strip.setPixelColor(48, 0, 255, 0);
      strip.setPixelColor(49, 0, 255, 0);
      strip.setPixelColor(50, 0, 255, 0);
      strip.setPixelColor(51, 0, 255, 0);
      strip.setPixelColor(52, 0, 255, 0);
      strip.setPixelColor(53, 0, 255, 0);
    }

    else if ( raceOn == 6 ) {
      Serial.println("other");
      strip.setPixelColor(54, 0, 255, 0);
      strip.setPixelColor(55, 0, 255, 0);
      strip.setPixelColor(56, 0, 255, 0);
      strip.setPixelColor(57, 0, 255, 0);
      strip.setPixelColor(58, 0, 255, 0);
      strip.setPixelColor(59, 0, 255, 0);
      strip.setPixelColor(60, 0, 255, 0);
    }

    else if ( raceOn == 7 ) {
      Serial.println("asian");
      strip.setPixelColor(41, 0, 255, 0);
      strip.setPixelColor(42, 0, 255, 0);
      strip.setPixelColor(43, 0, 255, 0);
      strip.setPixelColor(44, 0, 255, 0);
      strip.setPixelColor(45, 0, 255, 0);
      strip.setPixelColor(46, 0, 255, 0);
      strip.setPixelColor(47, 0, 255, 0);
    }

    else if ( raceOn == 8 ) {
      Serial.println("white");
      strip.setPixelColor(34, 0, 255, 0);
      strip.setPixelColor(35, 0, 255, 0);
      strip.setPixelColor(36, 0, 255, 0);
      strip.setPixelColor(37, 0, 255, 0);
      strip.setPixelColor(38, 0, 255, 0);
      strip.setPixelColor(39, 0, 255, 0);
      strip.setPixelColor(40, 0, 255, 0);
    }
  }
}

void setEducationPixels() {
  for (int i = 0; i < 34; i++) {
    strip.setPixelColor(i, 50, 50, 50);

    if ( educationOn == 9 ) {
      Serial.println("less-than-high-school");
      strip.setPixelColor(28, 0, 0, 255);
      strip.setPixelColor(29, 0, 0, 255);
      strip.setPixelColor(30, 0, 0, 255);
      strip.setPixelColor(31,0, 0, 255);
      strip.setPixelColor(32, 0, 0, 255);
      strip.setPixelColor(33, 0, 0, 255);
    }

    else if ( educationOn == 10 ) {
      Serial.println("high-school");
      strip.setPixelColor(0, 0, 0, 255);
      strip.setPixelColor(1, 0, 0, 255);
      strip.setPixelColor(2, 0, 0, 255);
      strip.setPixelColor(3, 0, 0, 255);
      strip.setPixelColor(4, 0, 0, 255);
      strip.setPixelColor(5, 0, 0, 255);
      strip.setPixelColor(6, 0, 0, 255);
    }

    else if ( educationOn == 11 ) {
      Serial.println("some-college");
      strip.setPixelColor(7, 0, 0, 255);
      strip.setPixelColor(8, 0, 0, 255);
      strip.setPixelColor(9, 0, 0, 255);
      strip.setPixelColor(10,0, 0, 255);
      strip.setPixelColor(11, 0, 0, 255);
      strip.setPixelColor(12, 0, 0, 255);
      strip.setPixelColor(13, 0, 0, 255);
    }

    else if ( educationOn == 12 ) {
      Serial.println("bachelors");
      strip.setPixelColor(14, 0, 0, 255);
      strip.setPixelColor(15, 0, 0, 255);
      strip.setPixelColor(16, 0, 0, 255);
      strip.setPixelColor(17, 0, 0, 255);
      strip.setPixelColor(18, 0, 0, 255);
      strip.setPixelColor(19, 0, 0, 255);
      strip.setPixelColor(20, 0, 0, 255);
    }

    else if ( educationOn == 13 ) {
      Serial.println("advanced");
      strip.setPixelColor(21, 0, 0, 255);
      strip.setPixelColor(22, 0, 0, 255);
      strip.setPixelColor(23, 0, 0, 255);
      strip.setPixelColor(24, 0, 0, 255);
      strip.setPixelColor(25, 0, 0, 255);
      strip.setPixelColor(26, 0, 0, 255);
      strip.setPixelColor(27, 0, 0, 255);
    }
  }
}

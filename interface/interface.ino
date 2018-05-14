#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>
#include <Bounce2.h>
#include <Keyboard.h>
#include <Wire.h>

Encoder income(7, 6);
Encoder race(8, 9);
Encoder education(13, 10);

String incomeLabels[] = { "lower", "middle", "upper-middle", "upper" };
char incomeKeys[] = { 'Q', 'W', 'E', 'R' };
String raceLabels[] = { "black", "asian", "white", "hispanic", "other" };
char raceKeys[] = { 'A', 'G', 'F', 'S', 'D' };
String educationLabels[] = { "less-than-high-school", "high-school", "some-college", "bachelors", "advanced" };
char educationKeys[] = { 'Z', 'X', 'C', 'V', 'B' };

long oldIncomePosition = 0;
int incomeSelection = 0;

long oldRacePosition = 0;
int raceSelection = 0;

long oldEducationPosition = 0;
int educationSelection = 0;

Bounce resetButton = Bounce();
Bounce randomButton = Bounce();

Bounce searchButton1 = Bounce();
int searchButtonPin1 = 4;
int searchLedPin1 = 5;

Bounce searchButton2 = Bounce();
int searchButtonPin2 = A2;
int searchLedPin2 = A1;

Bounce searchButton3 = Bounce();
int searchButtonPin3 = A4;
int searchLedPin3 = A3;

long lastSearchDebounceTime = 0;
long debounceDelay = 10;

int resetButtonPin = 2;
int resetLedPin = 3;

int randomButtonPin = 14;

String sceneName = "Intro";
String prevSceneName;

int lastStartedAt;

void setup() {
  Wire.begin();
  Keyboard.begin();
  Serial.begin(115200);
  pinMode(resetButtonPin, INPUT_PULLUP);
  pinMode(randomButtonPin, INPUT_PULLUP);
  pinMode(searchButtonPin1, INPUT_PULLUP);
  pinMode(searchButtonPin2, INPUT_PULLUP);
  pinMode(searchButtonPin3, INPUT_PULLUP);
  pinMode(resetLedPin, OUTPUT);
  pinMode(searchLedPin1, OUTPUT);
  pinMode(searchLedPin2, OUTPUT);
  pinMode(searchLedPin3, OUTPUT);

  resetButton.attach(resetButtonPin);
  resetButton.interval(5);
  randomButton.attach(randomButtonPin);
  randomButton.interval(5);
  searchButton1.attach(searchButtonPin1);
  searchButton1.interval(5);
  searchButton2.attach(searchButtonPin2);
  searchButton2.interval(5);
  searchButton3.attach(searchButtonPin3);
  searchButton3.interval(5);

  setSceneLighting();

  lastStartedAt = millis();
}

void loop() {
  //== Check scene change
  if (Serial.available() > 0) {
    String incomingString = Serial.readString();
    Serial.println(incomingString);
    sceneName = incomingString;

    setSceneLighting();
  }

  //== Check all our encoders
  if (sceneName == "Profile") {
    checkIncomeEncoder();
    checkRaceEncoder();
    checkEducationEncoder();
  }

  if (sceneName == "Intro") {
    int elapsedTime = millis() - lastStartedAt;

    if (elapsedTime / 1000 % 2 == 0) {
      searchLedsHigh();
    } else {
      searchLedsLow();
    }
  }

  // Always active
  checkReset();
  checkSearch();

  // Only on slot pull scenes
  if (sceneName == "Prompt" || sceneName == "RandomGame") {
    checkRandom();
  }

  //== Global delay
  delay(1);
}

void sendToUno(char key) {
  // Wire.requestFrom(9, 1);
  Wire.beginTransmission(9); // transmit to device #9
  Wire.write(key);
  Wire.endTransmission();    // stop transmitting

  return;
}

// Random utility to "constrain" but wrapover
int rollover(int x, int lower, int upper) {
  int range = upper - lower;
  while (x < lower) x += range;
  while (x >= upper) x -= range;

  return x;
}

int getEncoderSelection(int x, int num_selections) {
  x = rollover(x, 0, 80);

  // NB. The OBOB is not a bug. It's important!
  return map(x, 0, 80, 0, num_selections);
}

void checkIncomeEncoder() {
  long incomePosition = income.read();

  if (incomePosition != oldIncomePosition) {
    incomeSelection = getEncoderSelection(incomePosition, 4);
    oldIncomePosition = incomePosition;

    Keyboard.write(incomeKeys[incomeSelection]);
    sendToUno(incomeKeys[incomeSelection]);
  }
}

void checkRaceEncoder() {
  long racePosition = race.read();

  if (racePosition != oldRacePosition) {
    raceSelection = getEncoderSelection(racePosition, 5);
    oldRacePosition = racePosition;

    Keyboard.write(raceKeys[raceSelection]);
    sendToUno(raceKeys[raceSelection]);
  }
}

void checkEducationEncoder() {
  long educationPosition = education.read();

  if (educationPosition != oldEducationPosition) {
    educationSelection = getEncoderSelection(educationPosition, 5);
    oldEducationPosition = educationPosition;

    Keyboard.write(educationKeys[educationSelection]);
    sendToUno(educationKeys[educationSelection]);
  }
}

void checkReset() {
  resetButton.update();
  if (resetButton.fell()) {
    digitalWrite(resetLedPin, HIGH);
    Keyboard.write('I');

    prevSceneName = "NULL";
    oldIncomePosition = income.read();
    oldRacePosition = race.read();
    oldEducationPosition = education.read();
    lastStartedAt = millis();
  }
}

void checkSearch() {
  searchButton1.update();
  searchButton2.update();
  searchButton3.update();

  if (millis() - lastSearchDebounceTime < debounceDelay) {
    return;
  }

  if (searchButton1.fell() || searchButton2.fell() || searchButton3.fell()) {
    lastSearchDebounceTime = millis();

    searchLedsHigh();
    Keyboard.write('O');
  }
}

void searchLedsHigh() {
  digitalWrite(searchLedPin1, HIGH);
  digitalWrite(searchLedPin2, HIGH);
  digitalWrite(searchLedPin3, HIGH);
}

void searchLedsLow() {
  digitalWrite(searchLedPin1, LOW);
  digitalWrite(searchLedPin2, LOW);
  digitalWrite(searchLedPin3, LOW);
}

void checkRandom() {
  randomButton.update();

  if (randomButton.fell()) {
    Keyboard.write('P');

    // NB slot sound is 2.821224 sec
    for (int x = 1; x < 14; x++) {
      spinnerIncome();
      spinnerRace();
      spinnerEducation();
      delay(200);
    }
  }
}

void setSceneLighting() {
  if (sceneName == prevSceneName) return;

  if (sceneName == "Intro") {
    // allPixelsOn();
    searchLedsHigh();
    digitalWrite(resetLedPin, LOW);
  }

  if (sceneName == "Profile") {
    // for (int i = 0; i < 4; i++) {
    //   setIncomePixels(i);
    // }
    //
    // for (int i = 0; i < 5; i++) {
    //   setRacePixels(i);
    // }
    //
    // for (int i = 0; i < 5; i++) {
    //   setEducationPixels(i);
    // }

    searchLedsLow();
  }

  if (sceneName == "Searching") {
    // setIncomePixels(incomeSelection);
    // setRacePixels(raceSelection);
    // setEducationPixels(educationSelection);

    searchLedsLow();
  }

  if (sceneName == "Game") {
    // setIncomePixels(incomeSelection);
    // setRacePixels(raceSelection);
    // setEducationPixels(educationSelection);

    searchLedsHigh();
  }

  if (sceneName == "Explore") {
    // setIncomePixels(incomeSelection);
    // setRacePixels(raceSelection);
    // setEducationPixels(educationSelection);

    searchLedsHigh();
  }

  if (sceneName == "Prompt") {
    // allPixelsOn();

    searchLedsLow();
  }

  if (sceneName == "RandomProfile") {
    // allPixelsOn();

    searchLedsLow();
  }

  if (sceneName == "RandomGame") {
    // setIncomePixels(incomeSelection);
    // setRacePixels(raceSelection);
    // setEducationPixels(educationSelection);

    searchLedsHigh();
  }

  if (sceneName == "Outro") {
    // allPixelsOn();

    searchLedsLow();
    digitalWrite(resetLedPin, HIGH);
  }

  prevSceneName = sceneName;
}

void spinnerIncome() {
  int randomSelection = random(4);
  while (randomSelection == incomeSelection) {
    randomSelection = random(4);
  }

  incomeSelection = randomSelection;
  Keyboard.write(incomeKeys[incomeSelection]);
}

void spinnerRace() {
  int randomSelection = random(5);
  while (randomSelection == raceSelection) {
    raceSelection = random(5);
  }

  raceSelection = randomSelection;
  Keyboard.write(raceKeys[raceSelection]);
}

void spinnerEducation() {
  int randomSelection = random(5);
  while (randomSelection == educationSelection) {
    educationSelection = random(4);
  }

  educationSelection = randomSelection;
  Keyboard.write(educationKeys[educationSelection]);
}

#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>
#include <Bounce2.h>
#include <Keyboard.h>
#include <Adafruit_NeoPixel.h>

Encoder race(8, 9);
Encoder income(6, 7);
Encoder education(10, 11);

String incomeLabels[] = { "lower", "middle", "upper-middle", "upper" };
char incomeKeys[] = { 'Q', 'W', 'E', 'R' };
int incomeLights[] = { 0, 3, 6, 9 };
String raceLabels[] = { "black", "hispanic", "other", "asian", "white" };
char raceKeys[] = { 'A', 'S', 'D', 'F', 'G' };
int raceLights[] = { 12, 15, 18, 21, 24 };
String educationLabels[] = { "less-than-high-school", "high-school", "some-college", "bachelors", "advanced" };
char educationKeys[] = { 'Z', 'X', 'C', 'V', 'B' };
int educationLights[] = { 27, 30, 33, 36, 39 };

long oldIncomePosition = -1;
int incomeSelection = 0;

long oldRacePosition = -1;
int raceSelection = 0;

long oldEducationPosition = -1;
int educationSelection = 0;

Bounce resetButton = Bounce();
Bounce searchButton = Bounce();
Bounce randomButton = Bounce();

int searchButtonPin = 12;
int searchLedPin = 13;

int resetButtonPin = 2;
int resetLedPin = 3;

int randomButtonPin = 5;
int randomLedPin = 4;

const int dinPin = 0;    // Din pin to Arduino pin 4
const int numOfLeds = 48;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numOfLeds, dinPin, NEO_GRB + NEO_KHZ800);

String sceneName = "Profile";
String prevSceneName;

void setup() {
  Keyboard.begin();
  Serial.begin(115200);
  pinMode(resetButtonPin, INPUT_PULLUP);
  pinMode(searchButtonPin, INPUT_PULLUP);
  pinMode(randomButtonPin, INPUT_PULLUP);
  pinMode(resetLedPin, OUTPUT);
  pinMode(searchLedPin, OUTPUT);
  pinMode(randomLedPin, OUTPUT);

  searchButton.attach(searchButtonPin);
  searchButton.interval(5);
  resetButton.attach(resetButtonPin);
  resetButton.interval(5);
  randomButton.attach(randomButtonPin);
  randomButton.interval(5);

  pixels.begin(); // Initializes the NeoPixel library
  pixels.show(); //// Initialize all pixels to 'off'
  pixels.setBrightness(5); // Value from 0 to 100%

  setSceneLighting();
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
  checkIncomeEncoder();
  checkRaceEncoder();
  checkEducationEncoder();

  //== Check all our buttons
  checkSearch();
  checkReset();
  checkRandom();

  //== Lights
  // allPixelsOff();
  // setIncomePixels(incomeSelection);
  // setRacePixels(raceSelection);
  // setEducationPixels(educationSelection);
  pixels.show();

  //== Global delay
  delay(1);
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
  }
}

void checkRaceEncoder() {
  long racePosition = race.read();


  if (racePosition != oldRacePosition) {
    raceSelection = getEncoderSelection(racePosition, 5);
    oldRacePosition = racePosition;

    Keyboard.write(raceKeys[raceSelection]);
  }
}

void checkEducationEncoder() {
  long educationPosition = education.read();

  if (educationPosition != oldEducationPosition) {
    educationSelection = getEncoderSelection(educationPosition, 5);
    oldEducationPosition = educationPosition;

    Keyboard.write(educationKeys[educationSelection]);
  }
}

void checkReset() {
  resetButton.update();
  if (resetButton.fell()) {
    digitalWrite(resetLedPin, HIGH);
    Keyboard.write('I');
  }
}

void checkSearch() {
  searchButton.update();

  if (searchButton.fell()) {
    digitalWrite(searchLedPin, HIGH);
    Keyboard.write('O');
  }
}

void checkRandom() {
  randomButton.update();

  if (randomButton.fell()) {
    digitalWrite(randomLedPin, HIGH);
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
    allPixelsOff();
    digitalWrite(searchLedPin, HIGH);
    digitalWrite(resetLedPin, LOW);
  }

  if (sceneName == "Profile") {
    for (int i = 0; i < 4; i++) {
      setIncomePixels(i);
    }

    for (int i = 0; i < 5; i++) {
      setRacePixels(i);
    }

    for (int i = 0; i < 5; i++) {
      setEducationPixels(i);
    }

    digitalWrite(searchLedPin, LOW);
  }

  if (sceneName == "Searching") {
    setIncomePixels(incomeSelection);
    setRacePixels(raceSelection);
    setEducationPixels(educationSelection);

    digitalWrite(searchLedPin, LOW);
  }

  if (sceneName == "Game") {
    setIncomePixels(incomeSelection);
    setRacePixels(raceSelection);
    setEducationPixels(educationSelection);

    digitalWrite(searchLedPin, HIGH);
  }

  if (sceneName == "Explore") {
    setIncomePixels(incomeSelection);
    setRacePixels(raceSelection);
    setEducationPixels(educationSelection);

    digitalWrite(searchLedPin, HIGH);
  }

  if (sceneName == "Prompt") {
    allPixelsOff();

    digitalWrite(searchLedPin, LOW);
  }

  if (sceneName == "RandomProfile") {
    allPixelsOff();

    digitalWrite(searchLedPin, LOW);
  }

  if (sceneName == "RandomGame") {
    setIncomePixels(incomeSelection);
    setRacePixels(raceSelection);
    setEducationPixels(educationSelection);

    digitalWrite(searchLedPin, HIGH);
  }

  if (sceneName == "Outro") {
    allPixelsOff();

    digitalWrite(searchLedPin, LOW);
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
  setIncomePixels(incomeLights[incomeSelection]);
  Keyboard.write(incomeKeys[incomeSelection]);
}

void spinnerRace() {
  int randomSelection = random(5);
  while (randomSelection == raceSelection) {
    raceSelection = random(5);
  }

  raceSelection = randomSelection;
  setRacePixels(raceLights[raceSelection]);
  Keyboard.write(raceKeys[raceSelection]);
}

void spinnerEducation() {
  int randomSelection = random(5);
  while (randomSelection == educationSelection) {
    educationSelection = random(4);
  }

  educationSelection = randomSelection;
  setEducationPixels(educationLights[educationSelection]);
  Keyboard.write(educationKeys[educationSelection]);
}

void allPixelsOff() {
  for (int i = 0; i < numOfLeds; i++) {
    pixels.setPixelColor(i, 0, 0, 0);
  }
}

void setIncomePixels(int selection) {
  int firstPixel = incomeLights[selection];

  pixels.setPixelColor(firstPixel, 255, 211, 26);
  pixels.setPixelColor(firstPixel + 1, 255, 211, 26);
  pixels.setPixelColor(firstPixel + 2, 255, 211, 26);
}


void setRacePixels(int selection) {
  int firstPixel = raceLights[selection];

  pixels.setPixelColor(firstPixel, 38, 216, 215);
  pixels.setPixelColor(firstPixel + 1, 38, 216, 215);
  pixels.setPixelColor(firstPixel + 2, 38, 216, 215);
}


void setEducationPixels(int selection) {
  int firstPixel = educationLights[selection];

  pixels.setPixelColor(firstPixel, 237, 125, 41);
  pixels.setPixelColor(firstPixel + 1, 237, 125, 41);
  pixels.setPixelColor(firstPixel + 2, 237, 125, 41);
}

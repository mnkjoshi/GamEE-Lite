#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int current = 0;
int spikePos = 20;
int characterHeight = 0;
int systemItem = 0;
String message = "GamEE";
const int buttonPin = 7;
int sameMessage = 0;
int selected = 1;
int score = 0;
int dinoDelay = 250;
int birdHeight = 2;
int counterBird = 0;
int pillarLoc = 16;
int jackAdd = 0;
int dealer = (rand() % 10 + 1) + (rand() % 10 + 1);
int counterHand = (rand() % 10 + 1) + (rand() % 10 + 1);
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(20,4);
  // Print a message to the LCD.
  
}

void loop() {
  lcd.clear();
  switch(systemItem) {
    case(0):
      homeScreen();
      break;
    case(1):
      dinoGame();
      break;
    case(2):
      flappyBird();
      break;
    case(3):
      blackjack();
      break;
  }
}

void homeScreen() {
  pinMode(buttonPin, INPUT);
  int buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    systemItem = selected;
  }
  byte dinoApp[] = {
  B11111,
  B10001,
  B10101,
  B10001,
  B11011,
  B11011,
  B10101,
  B11111
};

byte birdApp[] = {
  B11111,
  B11111,
  B10011,
  B10101,
  B10011,
  B10101,
  B11111,
  B11111
};


byte blackjack[] = {
  B11111,
  B11111,
  B11011,
  B10001,
  B10001,
  B10101,
  B11011,
  B11111
};


  lcd.createChar(0, dinoApp);
  lcd.createChar(1, birdApp);
  lcd.createChar(2, blackjack);
  lcd.home();
  lcd.print(message);
  int sensor0 = analogRead(A0);
  int sensor1 = analogRead(A1);
  lcd.setCursor((selected * 2) -1,2);
  lcd.print("^");
  lcd.setCursor(0,3);
  lcd.setCursor(0, 2);
  if (sameMessage > 2) {
    message = "GamEE Pro Main Menu";
  } else {
  sameMessage++;
  }
  lcd.setCursor(1, 1);
  lcd.write((byte) 0);
  lcd.setCursor(3, 1);
  lcd.write((byte) 1);
  lcd.setCursor(5, 1);
  lcd.write((byte) 2);
  
  if (sensor1 > 700) {
    selected = menuAdd(selected);
  } else if(sensor1 < 100) {
    selected = menuSub(selected);
  }
  delay(250);
}

void dinoGame() {
  byte evenRun[] = {
  B01110,
  B01010,
  B01110,
  B00101,
  B11111,
  B10100,
  B01010,
  B10010
};


byte oddRun[] = {
  B01110,
  B01010,
  B01110,
  B00101,
  B11111,
  B10100,
  B01010,
  B01001
};

byte spike[] = {
  B00000,
  B00000,
  B00100,
  B00100,
  B01110,
  B11111,
  B11111,
  B11111
};

byte jumping[] = {
  B01110,
  B01010,
  B01110,
  B10101,
  B01110,
  B00100,
  B11011,
  B00000
};
  lcd.createChar(0, evenRun);
  lcd.createChar(1, oddRun);
  lcd.createChar(2, jumping);
  lcd.createChar(3, spike);
  pinMode(buttonPin, INPUT);
  int buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    current = 2;
    characterHeight = 1;
  }
  if(current == 1) {
    current = 0;
  } else if(current == 0) {
    current = 1;
  }
  int height = 1 - characterHeight;
  lcd.setCursor(6,height);
  lcd.write((byte) current);
  delay(1);
  lcd.setCursor(spikePos--, 1);
  lcd.write((byte) 3);
  if (current == 2) {
    current = 1;
    characterHeight = 0;
  }
  if (height == 1) {
    if (spikePos == 6) {
      systemItem = 0;
      dinoDelay = 250;
      score = 0;
    }
  }
  if (spikePos == 0) {
    spikePos = 16;
    score = score + 1;
    dinoDelay = dinoDelay - 10;
  }
  lcd.setCursor(6, 3);
  lcd.print("Score: ");
  lcd.setCursor(12, 3);
  lcd.print(score);
  delay(dinoDelay);

}

void flappyBird() {
  byte birdChar[] = {
  B00000,
  B00000,
  B01110,
  B01011,
  B10011,
  B11100,
  B00000,
  B00000
};
byte pillar[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
  lcd.createChar(0, birdChar);
  lcd.createChar(1, pillar);
  pinMode(buttonPin, INPUT);
  int buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    if(birdHeight < 3 ) {
      birdHeight = birdHeight + 1;
    }
  }
  //lcd.setCursor(3, 3 - birdHeight);
  lcd.setCursor(3, 3 - birdHeight);
  lcd.write((byte) 0);

  lcd.setCursor(pillarLoc, 0);
  lcd.write((byte) 1);
  delay(1);
  lcd.setCursor(pillarLoc, 3);
  lcd.write((byte) 1);
  counterBird++;
  if(counterBird > 3) {
    birdHeight = birdHeight - 1;
    counterBird = 0;
  }
  pillarLoc = pillarLoc - 1;
  if(pillarLoc == 0) {
    pillarLoc = 16;
  }
  if(pillarLoc == 3) {
    if(birdHeight == 0 || birdHeight == 3) {
      systemItem = 0;
      sameMessage = 0;
      message = "Your bird crashed!";
    }
  }
  delay(250);
}

void blackjack() {
  lcd.home();
  lcd.print("Your hand is: ");
  lcd.setCursor(0, 1);
  lcd.print(dealer);
  lcd.setCursor(0, 2);
  lcd.print("Hit? Right");
  lcd.setCursor(0, 3);
  lcd.print("Hold? Left");
  int sensor0 = analogRead(A0);
  int sensor1 = analogRead(A1);
  if (sensor1 > 700) {
    dealer = dealer +  (rand() % 10 + 1);
    lcd.clear();
    lcd.home();
    lcd.print("Your hand is: ");
    
    lcd.print(dealer);
    lcd.setCursor(2, 1);
    lcd.print("Dealer hand is: ");
    lcd.setCursor(2, 2);
    lcd.print(counterHand);
    if (dealer > counterHand && dealer <= 21) {
      lcd.setCursor(2, 3);
      lcd.print("You win!");
      delay(4000);
      dealer = (rand() % 10 + 1) + (rand() % 10 + 1);
      counterHand = (rand() % 10 + 1) + (rand() % 10 + 1);
      systemItem = 0;
    } else {
      lcd.setCursor(2, 3);
      lcd.print("You lose!");
      delay(4000);
      dealer = (rand() % 10 + 1) + (rand() % 10 + 1);
      counterHand = (rand() % 10 + 1) + (rand() % 10 + 1);
      systemItem = 0;
    }
  } else if(sensor1 < 100) {
    lcd.clear();
    lcd.home();
    lcd.print("Your hand is: ");
    
    lcd.print(dealer);
    lcd.setCursor(2, 1);
    lcd.print("Dealer hand is: ");
    lcd.setCursor(2, 2);
    lcd.print(counterHand);
    if (dealer > counterHand && dealer <= 21) {
      lcd.setCursor(2, 3);
      lcd.print("You win!");
      delay(4000);
      dealer = (rand() % 10 + 1) + (rand() % 10 + 1);
      counterHand = (rand() % 10 + 1) + (rand() % 10 + 1);
      systemItem = 0;
    } else {
      lcd.setCursor(2, 3);
      lcd.print("You lose!");
      delay(4000);
      dealer = (rand() % 10 + 1) + (rand() % 10 + 1);
      counterHand = (rand() % 10 + 1) + (rand() % 10 + 1);
      systemItem = 0;
    }
  }
  delay(250);
}

int menuAdd(int which) {
  if (which == 3) {
    return 1;
  } else { 
    return (which + 1);
  }
}

int menuSub(int which) { 
  if (which == 1) {
    return 3;
  } else {
    return (which - 1);
  }
}
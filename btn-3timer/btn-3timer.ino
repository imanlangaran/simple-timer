#define cal 60*60*1000
#define btn 3
#define l1 0
#define l2 1
#define l3 2
#define out 4

bool buttonState;
bool lastButtonState = LOW;
bool reading;
unsigned long lastDebounceTime = 0;
bool b0 = 1, b1 = 1;

unsigned long off_milis = 0;

void setup() {
  pinMode(btn, INPUT_PULLUP);

  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(l3, OUTPUT);
  pinMode(out, OUTPUT);
  go_next();
  refresh();
  digitalWrite(out, 1);
  // Serial.begin(9600);
  // Serial.println("setup...");
}

void loop() {
  if (millis() > off_milis) {
    digitalWrite(out, 0);
    Serial.print(off_milis);
    Serial.print("-");
    Serial.println(millis());
  } else {
    digitalWrite(out, 1);
  }


  reading = digitalRead(btn);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > 100) {
    if (reading != buttonState) {
      buttonState = reading;
      if (!reading) {
        go_next();
        refresh();
      }
      // while(!digitalRead(2));
    }
  }

  lastButtonState = reading;
}

void go_next() {
  if (b0 && !b1) {
    b0 = 0;
    b1 = 1;
    off_milis = 2*cal;
  } else if (!b0 && b1) {
    b0 = 1;
    b1 = 1;
    off_milis = 3 * cal;
  } else if (b0 && b1) {
    b0 = 1;
    b1 = 0;
    off_milis = cal;
  }
}


void refresh() {
  if (b0 && !b1) {
    digitalWrite(l1, 1);
    digitalWrite(l2, 0);
    digitalWrite(l3, 0);
  }
  if (!b0 && b1) {
    digitalWrite(l1, 0);
    digitalWrite(l2, 1);
    digitalWrite(l3, 0);
  }
  if (b0 && b1) {
    digitalWrite(l1, 0);
    digitalWrite(l2, 0);
    digitalWrite(l3, 1);
  }
  // Serial.print(b0);
  // Serial.print("-");
  // Serial.print(b1);
  // Serial.print("-");
  // Serial.print(off_milis);
  // Serial.print("-");
  // Serial.println(millis());
}
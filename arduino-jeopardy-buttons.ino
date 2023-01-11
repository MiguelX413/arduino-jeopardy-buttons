struct Player {
  uint8_t buttonPin;
  uint8_t ledPin;
};

const Player players[] = {{2, 3}, {4, 5}, {7, 6}};

const uint8_t resetButton = 8;

struct {
  bool isActive;
  size_t player;
} activePlayer = {false, 0};

void setup() {
  for (const Player &player : players) {
    pinMode(player.ledPin, OUTPUT);
    pinMode(player.buttonPin, INPUT);
  }
  pinMode(resetButton, INPUT);
}

void loop() {
  // Reset
  if (digitalRead(resetButton)) {
    activePlayer = {false, 0};
    // Reset all LEDs
    for (const Player &player : players) {
      digitalWrite(player.ledPin, LOW);
    }
    return;
  }
  size_t i = 0;
  for (const Player &player : players) {
    if (activePlayer.isActive) {
      break;
    }
    if (digitalRead(player.buttonPin)) {
      activePlayer = {true, i};
      digitalWrite(player.ledPin, HIGH);
    }
    i++;
  }
}

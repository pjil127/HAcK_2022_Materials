void setup() {
  // TASK: Define and initialize Serial
  while (!Serial) {
  ; // wait for serial port to connect. Needed for native USB port only
  }
}

char uart_receive; // Define char variable that will store char from ESP32

void loop() {
  
  if (Serial.available()) {
    uart_receive = char(Serial.read()); //Reading characters
  }

  // QUESTION: Do you think we can still print to the Serial Monitor?
  // TASK: Insert code that will print to the Serial Monitor
  delay (2000);
}

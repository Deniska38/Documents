#define LED 5  // светодиод
#define BUT 9   // кнопка

void setup() {
  pinMode(BUT, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    byte a = Serial.read();
    if (a == '1') {           // если пришла команда на включение, зажигаем светодиод
      digitalWrite(LED, HIGH);
    } else if (a == '5') {    // если на выключение - выключаем
      digitalWrite(LED, LOW);
    }
  }
  but_read();                 // отслеживание нажатий кнопки
}

void but_read() {
  static unsigned long timerT;
  if ((timerT + 100) > millis()) return;
  but[0] = but[1];
  but[1] = digitalRead(BUT);
  if (but[0] && !but[1]) Serial.write("1"); // кнопка нажата, отправляем 1
  if (!but[0] && but[1]) Serial.write("5"); // кнопка отжата, отправляем 5
  timerT = millis();
}

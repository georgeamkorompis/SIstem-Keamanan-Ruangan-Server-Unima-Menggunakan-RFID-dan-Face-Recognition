int Sensor = A0;
int relay = 2;
void setup() {
  Serial.begin(9600); // Inisialisasi Serial Monitor
  pinMode(relay,OUTPUT);
  tutup();
}

void loop() {
  int data_sensor = map(analogRead(Sensor), 0, 675, 0, 100);
  Serial.println(data_sensor);
  if(data_sensor > 90){
    buka();
  }
  else
  {
    tutup();
  }
  delay(100);
}

void buka(){
 digitalWrite(relay,HIGH);
}

void tutup(){
 digitalWrite(relay,LOW);
}

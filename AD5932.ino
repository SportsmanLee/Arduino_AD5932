
int SDATA = 2;
int SCLK = 3;
int FSYNC = 4;
int STANDBY = 5;
int INTERRUPT = 6;
int CTRL = 7;
int SYNCOUT = 8;

int VOUT = A0;

void myShiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, byte val)
{
	int i;
	for (i = 0; i < 8; i++)  {
		if (bitOrder == LSBFIRST)
			digitalWrite(dataPin, !!(val & (1 << i)));
		else	
			digitalWrite(dataPin, !!(val & (1 << (7 - i))));
		digitalWrite(clockPin, LOW);
		digitalWrite(clockPin, HIGH);		
	}
}

// the setup routine runs once when you press reset:
void setup() {

  Serial.begin(51200);

  pinMode(VOUT , INPUT);

  pinMode(CTRL , OUTPUT);
  pinMode(SCLK , OUTPUT);  
  pinMode(SDATA , OUTPUT);
  pinMode(FSYNC , OUTPUT);  
  pinMode(INTERRUPT , OUTPUT);  
  pinMode(STANDBY , OUTPUT);  

  digitalWrite(INTERRUPT , LOW);
  digitalWrite(STANDBY , LOW);
  digitalWrite(CTRL , LOW);
  digitalWrite(FSYNC , HIGH);
  digitalWrite(SCLK , HIGH);
  
  delay(10);
  
  //Control Register 16-bit
  
  digitalWrite(FSYNC , LOW);
  delay(1);
  myShiftOut(SDATA , SCLK , MSBFIRST , 0b00001111);
  myShiftOut(SDATA , SCLK , MSBFIRST , 0b11111111);  
  delay(1);
  digitalWrite(FSYNC , HIGH);  
  delay(10);
  
  
  //Fstart LSB 16-bit
  digitalWrite(FSYNC , LOW);
  delay(1);
  myShiftOut(SDATA , SCLK , MSBFIRST , 0b11001110);
  myShiftOut(SDATA , SCLK , MSBFIRST , 0b10111000);
  delay(1);
  digitalWrite(FSYNC , HIGH);  
  delay(10);


  //Fstart MSB 16-bit
  digitalWrite(FSYNC , LOW);
  delay(1);
  myShiftOut(SDATA , SCLK , MSBFIRST , 0b11010000);
  myShiftOut(SDATA , SCLK , MSBFIRST , 0b01010001);
  delay(1);
  digitalWrite(FSYNC , HIGH);  
  delay(10);
  
  //Fsatrt delta f 24-bit <- input 32-bit (frame4 + frame5)
  digitalWrite(FSYNC , LOW);
  delay(1);
  myShiftOut(SDATA , SCLK , MSBFIRST , 0b00100011);
  myShiftOut(SDATA , SCLK , MSBFIRST , 0b00010010);
  delay(1);
  digitalWrite(FSYNC , HIGH);    
  delay(10);
  
  digitalWrite(FSYNC , LOW);
  delay(1);
  myShiftOut(SDATA , SCLK , MSBFIRST , 0b00110000);
  myShiftOut(SDATA , SCLK , MSBFIRST , 0b00001000);
  delay(1);
  digitalWrite(FSYNC , HIGH);
  delay(10);
  
  //Number of Increments 16-bit
  digitalWrite(FSYNC , LOW);
  delay(1);
  myShiftOut(SDATA , SCLK , MSBFIRST , 0b00010000);
  myShiftOut(SDATA , SCLK , MSBFIRST , 0b01011010);
  delay(1);
  digitalWrite(FSYNC , HIGH);  
  delay(10);
  
  //Increment Interval
  /*digitalWrite(FSYNC , LOW);
  delay(1);
  myShiftOut(SDATA , SCLK , MSBFIRST , 0b01000000);
  myShiftOut(SDATA , SCLK , MSBFIRST , 0b00000011);
  delay(1);
  digitalWrite(FSYNC , HIGH);  
  delay(10);*/
  
  digitalWrite(CTRL , HIGH);
  delay(1);
  digitalWrite(CTRL , LOW);
  delay(25);
}

int counter = 0;

// the loop routine runs over and over again forever:
void loop() {
  int analogValue = analogRead(VOUT);
  int syncValue = digitalRead(SYNCOUT);
  if (syncValue > 0)
    Serial.println(syncValue);
  //Serial.println(analogValue);
  //delay(10);
  
  if(counter > 2000){
    Serial.println("counter reset");
    digitalWrite(CTRL , HIGH);
    delay(1);
    digitalWrite(CTRL , LOW);
    delay(25);
    counter = 0;  
  }
  
  counter++;
  
  
//  int sensorValue = analogRead(A0);
//  float voltage = sensorValue * (5.0 / 1023.0);
//  Serial.println(voltage);
}

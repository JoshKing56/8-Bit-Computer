int i = 0;
int j = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop()
{

  digitalWrite(3, HIGH);
  delay(1000);
  digitalWrite(3, LOW);
  delay(1000);

  for (int j = 0; j < 4; j++)
  {
    for (int i = 0; i < 16; i++)
    {
//      Serial.print("j = ");
//      Serial.print(j);
//      Serial.print(", i = ");
//      Serial.println(i);
      delay(50);
      digitalWrite(2, LOW);
//      digitalWrite(13, LOW);
      delay(50);
      digitalWrite(2, HIGH);
//      digitalWrite(13, HIGH);
    }
  }
}

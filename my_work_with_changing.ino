#include <Servo.h>
#include <Password.h>
#include <Keypad.h>


static Password *password = NULL;  // password
int passLength = 4;                        // length of the password
static Password *change = NULL; 
 
int ledRed = 11;
int ledGreen = 12;
int buzzer = 13;

 
int inputedLength; // number of clicks
 
const byte ROWS = 4; // rows
const byte COLS = 3; // cols
 
char keys[ROWS][COLS] =
{
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
 
byte rowPins[ROWS] = {2,3,4,5};
byte colPins[COLS] = {6,7,8};
 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

Servo servo;
 
void setup()
{
  Serial.begin(9600);
  
  pinMode(ledRed, OUTPUT);  
  pinMode(ledGreen, OUTPUT);
  pinMode(buzzer, OUTPUT);
 
  digitalWrite(ledRed, HIGH);
  digitalWrite(ledGreen, LOW);
  servo.attach(10);
  servo.write(0);
  
  const char* pwd = "7031";
  size_t pwdlen = strlen(pwd);
  Serial.println(pwdlen);    //output 4????
char* pass = new char[pwdlen+1];

Serial.println(strlen(pass));  // and this is 4????
size_t i = 0;
for(i = 0; i < pwdlen; i++){
  pass[i]= pwd[i];
    Serial.println(pwd[i]);
}
pass[i] = '\0';

password = new Password(pass);
 Serial.println(pass);


  const char* pswCh = "*##*";
  size_t pswlen = strlen(pswCh);
char* passCh = new char[pswlen+1];
Serial.println(pswlen);
size_t k = 0;
for(k = 0; k < pswlen; k++){
  passCh[k]= pswCh[k];
    Serial.println(pswCh[k]);
}
passCh[k] = '\0';

change = new Password(passCh);
 Serial.println(passCh);
 
}
 
void loop()
{
  keypadEvent();
}
void keypadEvent()
{
  for(int count = 0; count < 4; count++){
  char eKey = keypad.waitForKey();
   
int i;
for( i = 1; i <= 1; i++ )
{
  digitalWrite(buzzer, HIGH);  
  delay(50);            
  digitalWrite(buzzer, LOW);  
  delay(50);      
}    
 
Serial.print("Pressed: ");
Serial.println(eKey);
 
switch (eKey)
{

default:
inputedLength=inputedLength+1;
password->append(eKey);
change->append(eKey);
}
Serial.println(inputedLength);
  } 
 
if(inputedLength == passLength)
{
delay(250);
password->append('\0');
change->append('\0');
checkPassword();
inputedLength = 0;
}

}

 
void checkPassword()
{

if(change->evaluate()){

   inputedLength = 0;
    Serial.println("changing");

    
char* passCh = new char[5];

size_t k = 0;
for(k = 0; k <4; k++){
  passCh[k]= keypad.waitForKey();

int i;
for( i = 1; i <= 1; i++ )
{
  digitalWrite(buzzer, HIGH);  
  delay(50);            
  digitalWrite(buzzer, LOW);  
  delay(50);      
} 
  
    Serial.println(passCh[k]);
}
passCh[4] = '\0';
Serial.println(passCh);

password = new Password(passCh);

  delay(250);
    int i;
for( i = 1; i <= 1; i++ )
{
  digitalWrite(buzzer, HIGH);  
  delay(150);            
  digitalWrite(buzzer, LOW);  
  delay(50);      
  digitalWrite(buzzer, HIGH);  
  delay(150);            
  digitalWrite(buzzer, LOW);  
  delay(50);  
} 
    
    inputedLength = 0;
    change->reset();
    password->reset();

   return;
  }

  
  if (password->evaluate())
  {
     
int i;
for( i = 0; i <= 2; i++ )
{
 
  digitalWrite(buzzer, HIGH);  
  delay(70);            
  digitalWrite(buzzer, LOW);  
  delay(70); 
     
}    
    inputedLength = 0;
 
    Serial.println("Success");    
    servo.write(180);
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, HIGH);
    delay(2500);
     servo.write(0); 
    inputedLength = 0;  
    password->reset();
    change->reset();

    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH); 
    
 }  

  else
  {
int i;
for( i = 1; i <= 1; i++ )
{
  digitalWrite(buzzer, HIGH);  
  delay(200);            
  digitalWrite(buzzer, LOW);  
  delay(200);      
}  
    inputedLength = 0;  
    password->reset();
    change->reset();
    Serial.println("Wrong");
 
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH);    
             
  }
}

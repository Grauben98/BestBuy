#include <Keypad.h>
#include <LiquidCrystal.h>

#define EN_pin 2
#define RS_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

LiquidCrystal lcd(EN_pin, RS_pin, D4_pin, D5_pin, D6_pin, D7_pin);

const byte rows = 4;
const byte cols = 4;

char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[rows] = {40, 41, 42, 43};
byte colPins[cols] = {44, 45, 46, 47};

Keypad keyp = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

char outgoingChar = ' ';
char auxOutgoingChar;
String outgoingText;
String complOutgoingText;

char incomingChar;
String incomingText;

int opt = 1; 

void setup() {
  Serial.begin(9600);
  lcd.begin(20, 4);
  lcd.setCursor(0,0);                 //20, 4
}

void loop() {
  menu();
  
  outgoingChar = keyp.getKey();
  
  if(outgoingChar != ' '){
    lcd.clear();
    
    outgoingText = (String)outgoingChar;
    lcd.print(outgoingText);
    
    if(outgoingChar == 'A'){          //storer requests for all products with no stock, through their ID's. . .   
      Serial.print(outgoingChar);
      lcd.print(outgoingText);
    }
    else if(outgoingChar == 'B'|| outgoingChar == 'C'){     
      if(outgoingChar == 'B')         //storer requests for a single product, their stock value. . .
        lcd.print("P. a checar: ");
      else if(outgoingChar == 'C')    //storer fills stock for a single product. . .
        lcd.print("P. a llenar: ");
        
      auxOutgoingChar = outgoingChar;
      outgoingChar = ' '; 

      while(outgoingChar == ' ')
        outgoingChar = keyp.getKey();

      outgoingText = (String)outgoingChar;
      
      complOutgoingText = (String)auxOutgoingChar;
      complOutgoingText += outgoingText;
      
      Serial.print(complOutgoingText);
      lcd.print(outgoingText);
      outgoingChar = auxOutgoingChar;
    }
  }
  else{
    while(Serial.available() > 0){
      lcd.clear();
      
      incomingChar = Serial.read();
      incomingText = (String)incomingChar;

      if(outgoingChar == 'A'){
        lcd.print("P. sin stock son");
        lcd.setCursor(0,1);
        lcd.print(incomingText);
        lcd.print(" ");
      }
      else if(outgoingChar == 'B'){
        lcd.print("P. elegido tiene");
        lcd.setCursor(0,1);
        lcd.print("stock de: ");
        lcd.print(incomingText);
      }
      else if(incomingChar == 'C')
        lcd.print("Stock P. llenado");

      outgoingChar = ' ';
      incomingChar = ' ';
    }
  }
  delay(1000);
}

void menu(){
  lcd.clear();
   
  if(opt == 1)
    lcd.print("A: P. sin stock");
  else if(opt == 2)
    lcd.print("B: Checar P.");
  else if(opt == 3){
    opt = 0;
    lcd.print("C: Llenar P.");
  }
 
  opt++;
  delay(500);
}

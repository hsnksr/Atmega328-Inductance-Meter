
#include <LiquidCrystal.h>
const int rs = A5, en = A4, d4 = A3, d5 = A2, d6 = A1, d7 = A0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int start=3, clr=4, shift=2;
int strt_st=0, clr_st=0, shift_st=0, i=0;

//8 is the input to the circuit (connects to 150ohm resistor), 9 is the comparator/op-amp output.
double pulse, frequency, capacitance, inductance;
float induct=0;
void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  delay(500);
  lcd.print("Inductance Meter");
  lcd.setCursor(0,1); 
  lcd.print("Ready To Measure");
  pinMode(9, INPUT);
  pinMode(8, OUTPUT);
  pinMode(start, INPUT);//start measument
  pinMode(clr, INPUT);// clear screen after measument
  pinMode(shift, INPUT);//uH,mH, point shift function
  delay(1000);
}
void loop()
{

strt_st=digitalRead(start);
while(!digitalRead(start)){}
clr_st=digitalRead(clr);
while(!digitalRead(clr)){}
shift_st=digitalRead(shift);
while(!digitalRead(shift)){}

//if(strt_st==0 && clr==0){lcd.clear(); lcd.setCursor(1,1);  lcd.print("ERROR"); }
if(strt_st==0){measurement();}
if(clr_st==0){start_screen();}
if(shift_st==0 ){point_shift();}

}

void measurement()
{
  digitalWrite(8, HIGH);
  delay(5);//give some time to charge inductor.
  digitalWrite(8,LOW);
  delayMicroseconds(100); //make sure resination is measured
  pulse = pulseIn(9,HIGH,5000);//returns 0 if timeout
  if(pulse > 0.1)
  { //if a timeout did not occur and it took a reading:  
  capacitance = 2.E-6; // - insert value here
  frequency = 1.E6/(2*pulse);
  inductance = 1./(capacitance*frequency*frequency*4.*3.14159*3.14159);//one of my profs told me just do squares like this
  inductance *= 1E6; //note that this is the same as saying inductance = inductance*1E6
  }

  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("Inductance:");
  lcd.setCursor(0,1); 
  lcd.print(inductance);
  lcd.setCursor(14,1); 
  lcd.print("uH");      
  delay(100);

  induct=inductance;
  i=0;

}

void point_shift()
{
 i=i+1;   
 if(i>2) return(0);
 induct=induct/1000;
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("Inductance:");
  //lcd.setCursor(0,1); 
 // lcd.print(induct,4);

 if(i==1){   lcd.setCursor(0,1); lcd.print(induct,2); lcd.setCursor(14,1); lcd.print("mH");   }//mH
 if(i==2){   lcd.setCursor(0,1); lcd.print(induct,4); lcd.setCursor(14,1); lcd.print(" H"); }//H      
  delay(100);
}
void start_screen()
{ i=0; induct=0; inductance=0;// load zero to all variables
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("Inductance Meter");
  lcd.setCursor(0,1); 
  lcd.print("Ready To Measure");
  delay(100);
  }

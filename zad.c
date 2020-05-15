#include <LiquidCrystal.h>
#include <util/delay.h>
#include <stdbool.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
bool isto = false;

byte heart[8] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
};

byte diamond[8] = {
  B00100,
  B01110,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000,
};

byte spade[8] = {
  B00100,
  B01110,
  B11111,
  B11111,
  B00100,
  B01110,
  B00000,
  B00000,
};

byte club[8] = {
  B01110,
  B01110,
  B11111,
  B11111,
  B00100,
  B01110,
  B00000,
  B00000,
};

bool soft_dif = false;
int simboli[4];
int provera[4] = {0,0,0,0};

char ocitaj_taster()
{
  char taster = 0;
  unsigned char row;

  MCUCR &= ~0x10;
  PORTD = 0x0f;

  for(row = 0x80; row != 0x08; row >>= 1)
  {
    DDRD = row;
	_delay_ms(2);

    switch(row | ((~PIND) & 0x0f))
    {
      case 0x88:
      	taster = '1'; break;
      case 0x84:
      	taster = '2'; break;
      case 0x82:
      	taster = '3'; break;
      case 0x81:
      	taster = 'A'; break;

	  case 0x48:
      	taster = '4'; break;
      case 0x44:
      	taster = '5'; break;
      case 0x42:
      	taster = '6'; break;
      case 0x41:
      	taster = 'B'; break;

	  case 0x28:
      	taster = '7'; break;
      case 0x24:
      	taster = '8'; break;
      case 0x22:
      	taster = '9'; break;
      case 0x21:
      	taster = 'C'; break;

	  case 0x18:
      	taster = '*'; break;
      case 0x14:
      	taster = '0'; break;
      case 0x12:
      	taster = '#'; break;
      case 0x11:
      	taster = 'D'; break;
    }
  }

  return taster;
}

int main()
{
  lcd.createChar(0, heart);
  lcd.createChar(1, diamond);
  lcd.createChar(2, spade);
  lcd.createChar(3, club);

  lcd.begin(16, 2);
  lcd.print("Pritisni *.");
  //lcd.write(byte(0));
  //lcd.write(byte(1));
  //lcd.write(byte(2));
  //lcd.write(byte(3));
  int i = 0;
  int j = 0;
  int k = 0;
  while(1){

  		char taster = ocitaj_taster();
        if(taster != 0 && !soft_dif ){

        	soft_dif = true;
          if(taster == '*'){
          	lcd.clear();
          	for (i; i<4; i++){
          		simboli[i] = random(0,4);

          	}
          	i = 0;
          	for (i; i<4; i++){

          	    lcd.write(byte(simboli[i]));
          	}
          	_delay_ms(1000);
          	lcd.clear();
          	lcd.print("____");
          	lcd.setCursor(j,k);
          	i = 0;
          }
          if (taster == '4'){
        	  if (j == 0){
        		  j = 3;
        	  }else{
        	  j--;
        	  }
          }


          if (taster == '6'){
              if (j == 3){
                   j = 0;
              }else{
               j++;
              }
          }
          lcd.setCursor(j,k);

          if (taster == '8'){
              if (i == 3){
                   i = 0;
              }else{
               i++;
              }
              provera[k] = i;
              lcd.write(byte(i));
          }
          if (taster == '2'){
              if (i == 0){
                   i = 3;
              }else{
               i--;
              }
              provera[k] = i;
              lcd.write(byte(i));
          }

          if (taster == '5'){
        	  lcd.setCursor(0,1);
        	  i = 0;
        	  for (i;i<4;i++){
        		  lcd.write(byte(simboli[i]));
        		  if (simboli [i] == provera [i]){
        			  isto = true;
        		  }else{
        			  isto = false;
        		  }
        	  }
        	  lcd.setCursor (6,0);
        	  if(isto){
        		  lcd.print ("POBEDA!!!");
        	  }else{
        		  lcd.print ("Izgubio.");
        	  }
          }

          }
          if(ocitaj_taster() == 0){
          soft_dif = false;


          }

      }

  	return 0;
}

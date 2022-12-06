#include <GyverButton.h>
#include <AnalogKey.h>
#include "TimerOne.h"

GButton set1(3);
GButton p1(4);


GButton p2(2);

int pA, pB, sA1, sB1, sA2, sB2, sA3, sB3, gA, gB;
int pAr, pBr, sA1r, sB1r, sA2r, sB2r, sA3r, sB3r, gAr, gBr;

String ganador, pBc, pAc;
void setup() {

set1.setType(HIGH_PULL);

p1.setType(HIGH_PULL);
p2.setType(HIGH_PULL);
Serial.begin(9600);

  Timer1.initialize(10000);           // установка таймера на каждые 1000 микросекунд (= 1 мс)
  Timer1.attachInterrupt(timerIsr);   // запуск таймера
}

void timerIsr() {   // прерывание таймера
set1.tick();

p1.tick();  
p2.tick();     // отработка теперь находится здесь
}

void redo(){
pA = pAr;
pB = pBr;
gA = gAr;
gB = gBr;
sA1 = sA1r;
sA2 = sA2r;
sA3 = sA3r;
sB1 = sB1r;
sB2 = sB2r;
sB3 = sB3r;

}
void save(){
pAr = pA;
pBr = pB;
gAr = gA;
gBr = gB;
sA1r = sA1;
sA2r = sA2;
sA3r = sA3;
sB1r = sB1;
sB2r = sB2;
sB3r = sB3;
}
void sAp(int p){
  
    switch(gA + gB){
      case 0:
      sA1=sA1+p;
      break;
      case 1:
      sA2=sA2+p;
      break;
      case 2:
      sA3=sA3+p;
      break;
    }
  
}
void sBp(int s){
  
    switch(gA + gB){
      case 0:
      sB1=sB1+s;
      break;
      case 1:
      sB2=sB2+s;
      break;
      case 2:
      sB3=sB3+s;
      break;
    }
  
}
int sA(){
  
    switch(gA + gB){
      case 0:
      return sA1;
      break;
      case 1:
      return sA2;
      break;
      case 2:
      return sA3;
      break;
    }
  
}
int sB(){
  
    switch(gA + gB){
      case 0:
      return sB1;
      break;
      case 1:
      return sB2;
      break;
      case 2:
      return sB3;
      break;
    }
  
}


void loop() {


if(set1.isClick()){
  redo();
}
if(p1.isClick()){
  save();
  pA++;
}
if(p2.isClick()){
  save();
  pB++;
}

if((pA >= 4) && (pB <= (pA-2))){
  pA = 0;
  pB = 0;
  if((sA() == 7) and (sB() == 7) ){
    sBp(-1);
  }else{
    sAp(1);

  }

  
}
if((pB >= 4) && (pA <= (pB-2))){
    pA = 0;
  pB = 0;
    if((sA() == 7) and (sB() == 7) ){
    sAp(-1);
  }else{
    sBp(1);
  }

  
}
if((pA == 4) and (pB == 4)){
  pA = 3;
  pB = 3;
}

if(( ((sA()) == 6 ) and ((sB()) <= (sA()-2) ) ) or ((sA()==8) and (sB() <= 6)))  {
   gA++;

}
if(( ((sB()) == 6 ) and ((sA()) <= (sB()-2) ) ) or ((sB()==8) and (sA() <= 6))) {
   gB++;
   
}


if(gA == 2){
  while(1){
    Serial.println("Ganador: A");
  }
  
}
if(gB == 2){
  while(1){
    Serial.println("Ganador: B");
  }
  
}

switch (pA){
  case 0:
  pAc = '0';
  break;
    case 1:
  pAc = "15";
  break;
    case 2:
  pAc = "30";
  break;
    case 3:
  pAc = "40";
  break;

    case 4:
  pAc = "ad";
  break;
}
switch (pB){
  case 0:
  pBc = '0';
  break;
    case 1:
  pBc = "15";
  break;
    case 2:
  pBc = "30";
  break;
    case 3:
  pBc = "40";
  break;

    case 4:
  pBc = "ad";
  break;
}




Serial.print("<div style='background-color:black;'>  <table style='position:absolute; top:0%; left:0%;'>");

Serial.print("<tr style='font-size: 1.6em; color: red;'>");
Serial.print("<td>");
Serial.print(pAc);
Serial.print("</td>");
Serial.print("<td style=' position: relative; left: 10%;'>");
Serial.print(sA1);
Serial.print("</td>");
Serial.print("<td style=' position: relative; left: 10%;'>");
Serial.print(sA2);
Serial.print("</td>");
Serial.print("<td style=' position: relative; left: 10%;'>");
Serial.print(sA3);
Serial.print("</td>");
Serial.print("</tr>");

Serial.print("<tr style=''>");
Serial.print("<td style='width: 40%;'>");
Serial.print("POINTS");
Serial.print("</td>");
Serial.print("<td style=' position: relative; left: 10%;'>");
Serial.print("1");
Serial.print("</td>");
Serial.print("<td style=' position: relative; left: 10%;'>");
Serial.print("2");
Serial.print("</td>");
Serial.print("<td style=' position: relative; left: 10%;'>");
Serial.print("3");
Serial.print("</td>");
Serial.print("</tr>");

Serial.print("<tr style='font-size: 1.6em; color: red;'>");
Serial.print("<td>");
Serial.print(pBc);
Serial.print("</td>");
Serial.print("<td style=' position: relative; left: 10%;'>");
Serial.print(sB1);
Serial.print("</td>");
Serial.print("<td style=' position: relative; left: 10%;'>");
Serial.print(sB2);
Serial.print("</td>");
Serial.print("<td style=' position: relative; left: 10%;'>");
Serial.print(sB3);
Serial.print("</td>");
Serial.print("</tr>");

Serial.println("</table> </div>");
}

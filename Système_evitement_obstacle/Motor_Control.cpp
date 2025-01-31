#include "Motor_Control.h"

Motor::Motor(byte enca, byte encb, byte in1, byte in2) {
  this->enca = enca;
  this->encb = encb;
  this->in1 = in1;
  this->in2 = in2;
}

void Motor::init() {
  pinMode(enca, INPUT_PULLUP);
  pinMode(encb, INPUT_PULLUP);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

void Motor::setMotorSpeed(int phi) {
  int pwr = 0.5 * fabs(phi); //Equation à modifier selon l'étalonnage permettant de trouver la zone de fonctionnement linéaire

  if (pwr > 220) {
    pwr = 220;
  } else if (pwr < 80) { //Valeur de tension en dessous de laquelle le moteur ne tourne plus, obtenue grossièrement, à vérifier
    pwr = 0;
  }

  int sign = 1;
  if (phi < 0) {
    sign = -1;
  }

  if (sign == 1) {
    analogWrite(in2, 0);
    analogWrite(in1, fabs(pwr));
  } else {
    analogWrite(in1, 0);
    analogWrite(in2, fabs(pwr));
  }

  
}

void Motor::readEncoder() {
  int d = digitalRead(encb);
  if (d > 0) {
    pos++;
  } else {
    pos--;
  }
}
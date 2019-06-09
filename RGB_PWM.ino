/*скетч управления RGB-диодом с помощью пульта и IR-приемника
 * кнопки 1,4,7 увеличивают интенсивность красного, зеленого и синего сответственно
 * кнопки 2, 5, 8 - уменьшают
 * кнопки 3, 6, 9 - устанавливают в значении 0
 */


#include "IRremote.h"//подключаем библиотеку

IRrecv irrecv(3); // указываем вывод, к которому подключен приемник

//----Задаем номера пинов----
//
byte r_PIN = 5;
byte g_PIN = 6;
byte b_PIN = 9;

//----Устанавливаем начальные значения переменных-----
//
byte red = 0;
byte green = 0;
byte blue = 0;

//----вызов класса decode_results из подключеной библиотеки----
//
decode_results results;

void setup() {
  Serial.begin(9600); // выставляем скорость COM порта, для отладки
  irrecv.enableIRIn(); // запускаем прием
  //----Настраиваем режимы работы пинов----
  pinMode(r_PIN, OUTPUT);
  pinMode(g_PIN, OUTPUT);
  pinMode(b_PIN, OUTPUT);
  //----Задаем начальные значения на пинах----
  analogWrite(r_PIN, red);
  analogWrite(g_PIN, green);
  analogWrite(b_PIN, blue);
}

void loop() {

  if (irrecv.decode( &results )) { // если данные пришли

    switch (results.value) {

      //----красный-----
      case 0xFF30CF://кнопка 1
        red = red + 5;
        analogWrite(r_PIN, red);
        break;
      case 0xFF18E7://кнопка 2
        red = red - 5;
        analogWrite(r_PIN, red);
        break;
      case 0xFF7A85://кнопка 3
        red = 0;//сброс цвета
        analogWrite(r_PIN, red);
        break;

      //----зеленый----
      case 0xFF10EF://кнопка 4
        green = green + 5;
        analogWrite(g_PIN, green);
        break;
      case 0xFF38C7://кнопка 5
        green = green - 5;
        analogWrite(g_PIN, green);
        break;
      case 0xFF5AA5://кнопка 6
        green = 0;//сброс цвета
        analogWrite(g_PIN, green);
        break;

      //----синий----
      case 0xFF42BD://кнопка 7
        blue = blue + 5;
        analogWrite(b_PIN, blue);
        break;
      case 0xFF4AB5://кнопка 8
        blue = blue - 5;
        analogWrite(b_PIN, blue);
        break;
      case 0xFF52AD://кнопка 9
        blue = 0;//сброс цвета
        analogWrite(b_PIN, blue);
        break;
    }
    //------Отладка------
    //--Вывод кода цвета--
    Serial.print("R:");
    Serial.println(red);
    Serial.print("G:");
    Serial.println(green);
    Serial.print("B:");
    Serial.println(blue);
    //----коды кнопок----
    Serial.print("Код кнопки: ");
    Serial.println( results.value, HEX ); 
    //----Конец отладки-----
    
    irrecv.resume(); // принимаем следующую команду
  }
}

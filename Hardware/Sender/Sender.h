#ifndef  SENDER_H  //Защита от двойного подключения заголовочного файла
#define  SENDER_H  //Защита от двойного подключения заголовочного файла

#include <string>    // Библиотека типа данных строка 
#include <iostream> 
#include <array>
#include <sstream>                // библиотека для преобразования числа в строку 

  template <typename TUSART> // Шаблонный класс, куда передаётся любой из USARTов
class Sender 
{
  public:
   static void Send (float str) // Функция передачи данных
    {
      std::ostringstream ss;                           // поток, который конвертирует число в строку
      ss << str;                                      // Преобразуем число в строку
      i = 0U;                                         //Обнуление счётчика количества символов 
      localStroka = ss.str() + " B "+"\t";          // Перезапись отправляемого значения
      SendOneSymvol();                               // Вызов функции
      
      TUSART::CR1::TE::Enable::Set();                // 
      TUSART::CR1::TXEIE::InterruptWhenTXE::Set();   //
    }

   static void SendOneSymvol ()    //Функция отправки каждогов сивола
   {
     if (i > localStroka.size())   // если достигли конца строки
     {
       i = 0;                                         // Обнуляем счётчик
       TUSART::CR1::TE::Disable::Set();               // Запрешаем передачу
       TUSART::CR1::TXEIE::InterruptInhibited::Set(); // Запрещаем прерывание 
     }
     else  // Если не достигли конца строки, то
     {
       //std::cout << localStroka[i] << std::endl;
       TUSART::DR::Write(localStroka[i]);  // Записываем в регистр символ (1 байт)
       i++;                                // Переходим к следующему символу
     }
   }
   
   private:
   static inline std::string localStroka;    // Строка отправки   
   static inline int32_t i = 0U;            // Счётчик колличества символов для отправки данных
}; 





#endif  //Конец заголовочного файла
#include "rccregisters.hpp"           // Для модуля тактирования RCC
#include "usart2registers.hpp"    // Регистры USART для передачи данных
#include "adc1registers.hpp"         // библиотека для АЦП

#include "tim3registers.hpp"         // библиотека для TIM3

#include "nvicregisters.hpp"
//----------------------------Стандартные библиотеки С++------------------------
#include <iostream> // подключение стандартной библиотеки С++
 

//----------------------------Порты---------------------------------------------
#include "gpioaregisters.hpp"       // регистр для порта a
#include "gpiocregisters.hpp"       // регистр для порта c

//====================================Интерфейсы================================
#include "IMeasureParameter.h" 
#include "IDataSource.h"

//====================================Классы====================================
#include "ADC.h"
#include "Voltage.h" 
#include "PWM.h"
#include "Sender.h"               // Функция передачи данных
#include "Filter.h"
 //================================-ОСРВ и задачи===============================
#include "rtos.hpp"
#include "PowerRegulationTask.h"
#include "InSender.h"


std::uint32_t SystemCoreClock = 16'000'000U;    // тактирование внутреннего генератора, 1 такт = 8 000 000 Гц = 1 сек
std::uint32_t OneMillisecondRation = 1000U;     // коэффициент деления
std::uint32_t Timer3Prescaller = SystemCoreClock / OneMillisecondRation; // 1 млсек


//----------------------------Создание объектов---------------------------------  
  ADC adc;                                           // объект АЦП для измерения кода с потенциометра
  Voltage volt(static_cast<IDataSource&>(adc));      // объект для перевода кода в напряжение
  
  Filter filter (static_cast<IDataSource&>(volt));
  
  PWM pwm(static_cast<IDataSource&>(filter));         // создание обекта для расчёта CCR в зависимсоти от значения потенциометра
  PowerRegulationTask power(pwm);                   // создание задачи для измерения напряжения каждые 50мс
  
  InSender send(static_cast<IDataSource&>(filter));
 
int main()
{
 
  RCC::AHB1ENR::GPIOAEN::Enable::Set();         // Подать тактирование на порт A
  RCC::AHB1ENR::GPIOCEN::Enable::Set();         // Подать тактирование на порт C
  
  //------------------------------------АЦП-------------------------------------
  GPIOA::MODER::MODER0::Analog::Set();
  RCC::APB2ENR::ADC1EN::Enable::Set();       // подали тактирование на АЦП
  RCC::AHB1ENR::DMA2EN::Enable::Set();       // подали тактирование на ДМА
  adc.Start();

  ADC1::CR1::RES::Bits12::Set();             // разрядность АЦП   
  ADC1::CR1::SCAN::Enable::Set();            // режим сканирования

  ADC1::CR2::CONT::ContinuousConversion::Set();
  ADC1::CR2::DMA::Enable::Set();
  ADC1::CR2::DDS::DMARequest::Set();
  ADC1::CR2::ADON::Enable::Set();
  ADC1::CR2::SWSTART::On::Set();
  
  //----------------------------------ШИМ---------------------------------------
  
  GPIOC::MODER::MODER8::Alternate::Set();
  GPIOC::AFRH::AFRH8::Af2::Set();

   RCC::APB1ENR::TIM3EN::Enable::Set();       // подали тактирование на таймер TIM3

  TIM3::CNT::Write(0);
  TIM3::SR::UIF::NoInterruptPending::Set();             // скинули флаг
  // настройка ШИМ для 4 канала
  TIM3::CCMR2_Output::OC3M::Value6::Set();   
  TIM3::CCMR2_Output::OC3PE::Value1::Set(); 
  
  TIM3::PSC::Write(Timer3Prescaller);                   // делитель частоты
  TIM3::ARR::Write(100);
  TIM3::CCR3::Write(10);  
  
  TIM3::CCER::CC3E::Value1::Set();          // разрешаем работу таймера

  TIM3::CR1::CEN::Value1::Set();           // включение счётчика      
  
  //--------------------------------Передача данных-----------------------------

  RCC::APB1ENR::USART2EN::Enable::Set();      // Подать тактирование на USART
  NVIC::ISER1::Write(1U << 6U);              // UART = 38 позиция от системного таймера (38-32 = 6), разрешить глобальное прерывание
  
  
  GPIOA::MODER::MODER2::Alternate::Set();  // настройка порта А2  на альтернативный режим для передачи данных
  GPIOA::MODER::MODER3::Alternate::Set();  // настройка порта А3 на альтернативный режим для приёма данных
  GPIOA::AFRL::AFRL2::Af7::Set();         // перевели порт А2 в режим TX отправки
  GPIOA::AFRL::AFRL3::Af7::Set();         // перевели порт А3 в режим RX приёмки
 
  USART2::CR1::M::Data8bits::Set();         // передача данных по 8 бит
  
  USART2::CR1::TXEIE::InterruptWhenTXE::Set();     // разрешить прерывание по передаче

  USART2::CR1::TE::Enable::Set();       // разрешить передачу
  USART2::CR1::RE::Enable::Set();       // Разрешить приём
  
  USART2::CR2::STOP::Value0::Set();    // 1 стоповый бит
  
  uint32_t usartdiv = SystemCoreClock/ (9600);   // расчёт скорости
  USART2::BRR::Write(usartdiv);             // Целая часть скорости

  USART2::CR1::UE::Enable::Set();            // включение модуля USART
//------------------------------------------------------------------------------   
  
  //---------------------------Создание задач-----------------------------------
  OsWrapper::Rtos::CreateThread(power, "PowerRegulationTask"); 
  OsWrapper::Rtos::CreateThread(send, "InSender");
  
  OsWrapper::Rtos::Start();
  
  // Макрос assert используется для выявления ошибок логики во время разработки программы. 
  // аргумент assert(expression) принимает значение false только в том случае, если программа работает неправильно.
  // другими словами, следующая строча кода не должна никогда выполняться, если вызовится ошибка от assert, то программа работает неправильно.
  assert(false); 
  return 0;
  
  

  
}

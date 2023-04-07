#include "rccregisters.hpp" // for RCC
#include "gpiocregisters.hpp" // Register of Port C
#include "gpioaregisters.hpp" // Register of Port A


#include "pinconfig.h"
#include "Led.h"   // Connection of header file
#include  "Button.h" // Connection of button
#include "AllMode.h" // Mode of "All the LEDs are on"
#include "ChessMode.h" // Mode of "Chess"
#include "TreeMode.h" // Mode of "Christmas tree"
#include "SlideMode.h" // Mode of "Christmas tree"
#include "Garland.h" // Mode of "Garland"

#include <iostream>
#include <array> // Connection of libraries for work with arraies

#include "interrupthandler.hpp"
#include "stkregisters.hpp"
#include "tim2registers.hpp" // Connection with Timer 2
#include "tim5registers.hpp" // Connection with Timer 5
#include "nvicregisters.hpp"
#include "usart2registers.hpp" // Library of interfase USAST

#include "adc1registers.hpp" // регистры для аналого-цифрового преобразователя (АЦП)

#include "Sender.h"

constexpr std::uint32_t SystemClock = 16000000U; // clock of HSI
constexpr std::uint32_t OneMillisecondRation = 1000U; // ratio of division

// -------------------------Function of delay-----------------------------------
void Delay(std::uint32_t milliseconds)
{
  // for System Timer
  /* const std::uint32_t delayCounts = milliseconds * SystemClock / OneMillisecondRation - 1U;
  STK::VAL::Write(0U);
  STK::LOAD::Write(delayCounts);
  
  STK::CTRL::ENABLE::Enable::Set();
  while(!STK::CTRL::COUNTFLAG::Overflow::IsSet())
  {
    
  }
  STK::CTRL::ENABLE::Disable::Set(); */
  
  // for TIM2
  /* TIM2::CNT::Write(0U); // reset of Counter (CNT) to zero
  TIM2::ARR::Write(milliseconds); // maximum value in Timer 2
  
  TIM2::CR1::CEN::Enable::Set(); // Enable of Timer 2
  while(!TIM2::SR::UIF::InterruptPending::IsSet())
  {
    // InterruptPending – indicator of reaching of Timer 2 the maximum value (ARR)
  }
  TIM2::SR::UIF::NoInterruptPending::Set();
  TIM2::CNT::Write(0U);
  TIM2::CR1::CEN::Disable::Set(); // Disable of Timer 2 */
  
  // Interrupt for Timer 2
  /* TIM2::ARR::Write(milliseconds); // max value of recalculation of Timer 2
  TIM2::CNT::Write(0); // initial value of recalculation of Timer 2
  TIM2::SR::UIF::NoInterruptPending::Set(); // resetting the flag of interruption
  TIM2::CR1::CEN::Enable::Set(); */
  
  // Interrupt for Timer 5
  TIM5::ARR::Write(milliseconds);
  TIM5::CNT::Write(0);
  TIM5::SR::UIF::NoInterruptPending::Set();
  TIM5::CR1::CEN::Enable::Set(); // 
}
//-------------Creation of LEDs with binding of pins--------------

Led led1(pinA5); 
Led led2(pinC5);
Led led3(pinC8);
Led led4(pinC9);
Button userButton1(pinC13);
//------------------------------------------------------------------------------

//----------------------------------Array of LEDs-----------------------
   
    tArrayLeds leds =
    { 
      &led1,
      &led2,
      &led3,
      &led4,
    };
//------------------------------------------------------------------------------
    
//-------------Creation of objects with array of LEDs------------  
  AllMode allMode(leds); 
  ChessMode chessMode(leds);
  TreeMode treeMode(leds);
  SlideMode slideMode(leds);
//------------------------------------------------------------------------------  
  
//----------------------------------Array of modes--------------------------
    using tArrayModes = std::array<IMode*,4>;
    tArrayModes modes =
    {
      &allMode,
      &chessMode,
      &treeMode,
      &slideMode,

    };
//------------------------------------------------------------------------------
    
//-------------Creation of object (garland) with binding of modes----------------  
  Garland garland(modes);

//------------------------------------------------------------------------------     
    
int main()
{
  
  // Submitting the clock for TIM2
  RCC::APB1ENR::TIM2EN::Enable::Set(); // submitting the clock for Timer 2
  
  // Prescaller for Timer 2
  constexpr std::uint32_t Timer2Prescaller = SystemClock/OneMillisecondRation; // Timer 2 will 1 tick for 1 ms
  TIM2::PSC::Write(Timer2Prescaller);
  
  // Allow of global interruption for Timer 2
  //NVIC::ISER0::Write(1U<<28U); // Allow of global Interruption of Timer 2
  TIM2::DIER::UIE::Enable::Set(); // Allow of Interrupt by overflow
  
  // Submitting the clock for TIM5
  RCC::APB1ENR::TIM5EN::Enable::Set(); // submitting the clock for Timer 5
    
  // Prescaller for Timer 5
  constexpr std::uint32_t Timer5Prescaller = SystemClock/OneMillisecondRation; // Timer 2 will 1 tick for 1 ms
  TIM5::PSC::Write(Timer5Prescaller);
  
  // Allow of global interruption for Timer 5
  NVIC::ISER1::Write(1U<<18U); // Allow of global Interruption of Timer 5
  TIM5::DIER::UIE::Value1::Set(); // Allow of Interrupt by overflow

  // Подача тактирования на порты микроконтроллера
  RCC::AHB1ENR::GPIOCEN::Enable::Set(); // Подали тактирование на порт С
  RCC::AHB1ENR::GPIOAEN::Enable::Set(); // Подали тактирование на порт А
  
  // Connection of Port C and port A to Output
  GPIOA::MODER::MODER5::Output::Set();
  GPIOC::MODER::MODER5::Output::Set();
  GPIOC::MODER::MODER8::Output::Set();
  GPIOC::MODER::MODER9::Output::Set();
  
  // Порт А2 USART настроить на альтернативный режим
  GPIOA::MODER::MODER2::Alternate::Set(); // перевели порт А2 в альтернативный режим
  GPIOA::MODER::MODER3::Alternate::Set(); // перевели порт А3 в альтернативный режим
  GPIOA::AFRL::AFRL2::Af7::Set(); // перевели порт А2 в режим USART_TX (режим передачи данных)
  GPIOA::AFRL::AFRL3::Af7::Set(); // перевели порт А3 в режим USART_RX (режим передачи данных)
  
  // Transfer of data by UART
  RCC::APB1ENR::USART2EN::Enable::Set();
  NVIC::ISER1::Write(1U<<6U);
  USART2::CR1::M::Data8bits::Set();
  
  USART2::CR1::TXEIE::InterruptWhenTXE::Set();
  //USART2::CR1::TCIE::InterruptWhenTC::Set();
  //USART2::CR1::RXNEIE::InterruptWhenRXNE::Set();
  
  USART2::CR1::TE::Enable::Set(); // влкючили передачу
  USART2::CR1::RE::Enable::Set();
  uint32_t usartDiv = SystemClock/9600; // 9600 - требуемая скорость передачи
  USART2::BRR::Write(usartDiv); // число 16 компенсируется
  
  USART2::CR2::STOP::Value0::Set();
  USART2::CR1::UE::Enable::Set();
  
  
  // Подача тактирования на АЦП
  RCC::APB2ENR::ADC1EN::Enable::Set();
  // Настройка разрядности АЦП
  ADC1::CR1::RES::Bits12::Set(); // установили разрядность АЦП в 12 бит (4096 точек)
  // Установить количество измерений для АЦП
  ADC1::SQR1::L::Conversions1::Set(); // количество измерений, которые будет производить АЦП - 1
  ADC1::SQR3::SQ1::Channel0::Set(); // задание номера канала, на котором будет осуществляться первое преобразование АЦП
  // Скорость дискретизации
  ADC1::SMPR2::SMP0::Cycles480::Set(); // количество циклов, затрачиваемых на дискретизацию
  ADC1::CR2::ADON::Enable::Set(); // влкючили АЦП
  
  GPIOA::MODER::MODER0::Analog::Set(); // АЦП находится на порту 0 (настроили порт в аналоговый режим)
  uint32_t voltage = 0;
  
  userButton1.AddObserver(garland);
  
 //---------------------------Port and number of ports--------------------------------


  //std::uint32_t modeNumber = 0;
  Delay(500);
  for(;;)
  {
    userButton1.IsPressed();
    if(isInterrupt) // if flag is true...
    {
      garland.UpdateCurrentMode(); // updating the current mode
      isInterrupt = false; // resetting the flag to false
      Sender<USART2>::Send("Hello world");
      ADC1::CR2::SWSTART::On::Set(); // запуск АЦП на измерение
      uint32_t value = ADC1::DR::Get();
      voltage = (value*3000)/4095;
      while(ADC1::SR::EOC::ConversionNotComplete::IsSet()) // пока преобразование не завершено, ...
      {
        // Ждем, пока завершится преобразование
      }
      //std::cout<<ADC1::DR::Get()<<std::endl;
      //std::cout<<voltage/1000<<','<<(voltage/100)%10<<(voltage/10)%10<<voltage%10<<std::endl;
      
    }
  }
  // create a mode for adding of subscriber (for the next lesson)
}

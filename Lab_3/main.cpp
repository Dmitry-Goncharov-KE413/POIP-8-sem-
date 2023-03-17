#include "rccregisters.hpp" // for RCC
#include "gpiocregisters.hpp" // Register of Port C
#include "gpioaregisters.hpp" // Register of Port A
#include "gpiobregisters.hpp" // Register of Port B
#include "gpiodregisters.hpp" // Register of Port D


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

constexpr std::uint32_t SystemClock = 8000000U; // clock of HSI
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
  
  
  // Submitting the clock for Ports of MCU
  RCC::AHB1ENR::GPIOCEN::Enable::Set(); // Clock for port C
  RCC::AHB1ENR::GPIOAEN::Enable::Set(); // Clock for port A

  // Connection of Port C and port A to Output
  GPIOA::MODER::MODER5::Output::Set();
  GPIOC::MODER::MODER5::Output::Set();
  GPIOC::MODER::MODER8::Output::Set();
  GPIOC::MODER::MODER9::Output::Set();
  
  
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
    }
  }
  // create a mode for adding of subscriber (for the next lesson)
}

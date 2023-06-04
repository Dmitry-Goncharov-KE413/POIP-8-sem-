#ifndef  SENDER_H  //������ �� �������� ����������� ������������� �����
#define  SENDER_H  //������ �� �������� ����������� ������������� �����

#include <string>    // ���������� ���� ������ ������ 
#include <iostream> 
#include <array>
#include <sstream>                // ���������� ��� �������������� ����� � ������ 

  template <typename TUSART> // ��������� �����, ���� ��������� ����� �� USART��
class Sender 
{
  public:
   static void Send (float str) // ������� �������� ������
    {
      std::ostringstream ss;                           // �����, ������� ������������ ����� � ������
      ss << str;                                      // ����������� ����� � ������
      i = 0U;                                         //��������� �������� ���������� �������� 
      localStroka = ss.str() + " B "+"\t";          // ���������� ������������� ��������
      SendOneSymvol();                               // ����� �������
      
      TUSART::CR1::TE::Enable::Set();                // 
      TUSART::CR1::TXEIE::InterruptWhenTXE::Set();   //
    }

   static void SendOneSymvol ()    //������� �������� �������� ������
   {
     if (i > localStroka.size())   // ���� �������� ����� ������
     {
       i = 0;                                         // �������� �������
       TUSART::CR1::TE::Disable::Set();               // ��������� ��������
       TUSART::CR1::TXEIE::InterruptInhibited::Set(); // ��������� ���������� 
     }
     else  // ���� �� �������� ����� ������, ��
     {
       //std::cout << localStroka[i] << std::endl;
       TUSART::DR::Write(localStroka[i]);  // ���������� � ������� ������ (1 ����)
       i++;                                // ��������� � ���������� �������
     }
   }
   
   private:
   static inline std::string localStroka;    // ������ ��������   
   static inline int32_t i = 0U;            // ������� ����������� �������� ��� �������� ������
}; 





#endif  //����� ������������� �����
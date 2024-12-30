Hướng dẫn chạy prf:
1. Tạo thư mục mới:
     Khởi chạy phần mềm STM32CubeIDm
     File -> New -> STM32 project
2. Chỉnh sửa trong file .ioc
     Pin Unclock PA3 & PA2
     -> Conectivity -> USART2 -> Mode -> SynChronous Master
     -> Save (Generate code)
3. Thêm mã cho hàm prinft
     Thêm đoạn mã sau vào cuối chương trình:
         //
           #if defined(__GNUC__)
      int _write(int fd, char * ptr, int len) {
        HAL_USART_Transmit( & husart2, (uint8_t * ) ptr, len, HAL_MAX_DELAY);
        return len;
      }
      #elif defined(__ICCARM__)#include "LowLevelIOInterface.h"
      
      size_t __write(int handle,
        const unsigned char * buffer, size_t size) {
        HAL_USART_Transmit( & husart2, (uint8_t * ) buffer, size, HAL_MAX_DELAY);
        return size;
      }
      #elif defined(__CC_ARM)
      int fputc(int ch, FILE * f) {
        HAL_USART_Transmit( & husart2, (uint8_t * ) & ch, 1, HAL_MAX_DELAY);
        return ch;
      }
      #endif
      //
     Thực hiện comment toàn bộ đoạn code:
           /* Initialize leds */
      //  BSP_LED_Init(LED_BLUE);
      //  BSP_LED_Init(LED_GREEN);
      //  BSP_LED_Init(LED_RED);
      //
      //  /* Initialize USER push-button, will be used to trigger an interrupt each time it's pressed.*/
      //  BSP_PB_Init(BUTTON_SW1, BUTTON_MODE_EXTI);
      //  BSP_PB_Init(BUTTON_SW2, BUTTON_MODE_EXTI);
      //  BSP_PB_Init(BUTTON_SW3, BUTTON_MODE_EXTI);
      //
      //  /* Initialize COM1 port (115200, 8 bits (7-bit data + 1 stop bit), no parity */
      //  BspCOMInit.BaudRate   = 115200;
      //  BspCOMInit.WordLength = COM_WORDLENGTH_8B;
      //  BspCOMInit.StopBits   = COM_STOPBITS_1;
      //  BspCOMInit.Parity     = COM_PARITY_NONE;
      //  BspCOMInit.HwFlowCtl  = COM_HWCONTROL_NONE;
      //  if (BSP_COM_Init(COM1, &BspCOMInit) != BSP_ERROR_NONE)
      //  {
      //    Error_Handler();
      //  }

4. Chạy chương trình
     Run as -> 1 STM32 C/C++ Aplication

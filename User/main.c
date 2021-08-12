/**
  ******************************************************************************
  * @file    GPIO/JTAG_Remap/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *    
  *    
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "PROJ_book.h" 

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */

void fn_LED_Flash_Init(void);
void fn_usart_show_Init(void);
void fn_DMA_show_Init(void);
void fn_I2C_EE_Init(void);
void fn_I2C_EE_Soft_Init(void);
void fn_SPI_FLASH_Soft_Init(void);
void fn_FatFs_Document_Init(void);
void fn_SRAM_Init(void);

#define countof(a)      (sizeof(a) / sizeof(*(a)))
  
#define  _I2C_BufferSize (countof(writeData)-1)
static uint8_t writeData[_I2C_PageSize]={4,5,6,7,8,9,10,11};
static uint8_t writeData2[_I2C_PageSize]={24,25,26,27,28,29,30,31};
static uint8_t ReadData[_I2C_BufferSize]={0};

#define  _SPI_BufferSize  SPI_PAGE_SIZE   //(countof(write_SPI_Data)-1)
static uint8_t write_SPI_Data[_SPI_BufferSize]={0};
static uint8_t Read_SPI_Data[_SPI_BufferSize]={0};

int main(void)
{ 
      
      fn_RCC_Init();              //CPU 倍频
      fn_Led_Init();              //LED 输出初始化
      fn_Key_Init();              //按键 输入初始化
      fn_USART_Init();            //串口输出初始化
      printf("\n\n\r\n********** IC系统开始运行 **********\r\n");
      fn_LED_Flash_Init();        //RGB 输出测试
      fn_usart_show_Init();       //串口输出测试
      fn_EXTI_GPIO_Config();      //外部中断入口
      fn_DMA_show_Init();         //初始化DMA数据链路
      fn_I2C_EE_Init();           //初始化硬件I2C数据链路
      fn_I2C_EE_Soft_Init();      //初始化软件I2C数据链路
      fn_SPI_FLASH_Soft_Init();   //SPI测试通讯
      fn_FatFs_Document_Init();   //FatFs文件读取测试 
  
      fn_SRAM_Init();             //SRAM文件读取测试 
       
           
      while(1){
        fn_LED_ALL_OFF();
         fn_Systick_Delay(500,_Systick_ms);
        __G_OUT__;
        fn_Systick_Delay(500,_Systick_ms);
      }
}

//======================================================================
//======================================================================

  
void fn_LED_Flash_Init(void){
  uint16_t  count_Init = 2;
  printf("\n ---> LED开始运行 \n");
  while(count_Init-->0){
    fn_LED_ALL_OFF();
    __R_OUT__;
    fn_Systick_Delay(500,_Systick_ms);
    fn_LED_ALL_OFF();
    __G_OUT__;
    fn_Systick_Delay(500,_Systick_ms);
    fn_LED_ALL_OFF();
    __B_OUT__;
    fn_Systick_Delay(500,_Systick_ms);
    fn_LED_ALL_OFF();
    __R_OUT__;
  } 
}
//======================================================================
//======================================================================
void fn_usart_show_Init(void){ 
  fn_Usart_Send_Byte(_DEBUG_USARTx,'\r');
  printf("-->串口通信指测试完毕 \n");
  fn_Usart_SendString(_DEBUG_USARTx," : wangqi \n");
}
//======================================================================
//======================================================================
void fn_DMA_show_Init(void){
  printf("\n ---> DMA开始运行 \n");
  _DMA_ROM_TO_RAM(Map_BUFFER_SIZE ,aSRC_Cont_Buffer , aDST_Buffer);
  _DMA_RAM_TO_USART(Map_BUFFER_SIZE ,USART_Source_ADDR , aDST_Buffer); 
  printf("---> DMA运行完毕 \n");
}
//======================================================================
//======================================================================
void fn_I2C_EE_Init(void){
  printf("\n-->I2C_函数写入开始 \n");
  _I2C_EE_Init();
  I2C_Write_fun(writeData ,EEP_Firstpage ,_I2C_BufferSize);
  I2C_Read_fun(ReadData ,EEP_Firstpage ,_I2C_BufferSize);
  printf("--->I2C_函数写入完毕\n\r");
}
//======================================================================
//======================================================================
void fn_I2C_EE_Soft_Init(void){
  printf("\n-->I2C_软件函数写入开始 \n");
  I2C_Soft_Init();
  I2C_Soft_Write_fun(writeData2 ,EEP_Firstpage ,_I2C_BufferSize);
  I2C_Soft_Read_fun(ReadData ,EEP_Firstpage ,_I2C_BufferSize);
  printf("\n--->I2C_软件函数写入完毕\n\r");
}
//======================================================================
//======================================================================
void fn_SPI_FLASH_Soft_Init(void){
  uint16_t i,FlashID;
  printf("-->SPI通信指测试开始 \n");
  SPI_FLASH_Init(); 
  FlashID = SPI_Read_ID() ;
  if(FlashID == _SPI_FLASH_ID){
    printf("-->SPI  0x%x \n",FlashID);
  }
  
  SPI_Erase_Sector(0); //清除一个页的空间 
  printf("\n\n-->SPI清空开始 \n");
  SPI_Read_Data(Read_SPI_Data , 0, SPI_PAGE_SIZE);
  SPI_Show_Data(Read_SPI_Data , SPI_PAGE_SIZE);
  printf("\n\n-->SPI清空完成 \n");
   
  for(i=0 ; i < _SPI_BufferSize ; i++){
    write_SPI_Data[i] = 0xA7;
  }
  SPI_Show_Data(write_SPI_Data , SPI_PAGE_SIZE);
  
  SPI_BufferWrite_Data(write_SPI_Data ,0x000000,_SPI_BufferSize);
  
  
  printf("\n\n-->SPI输入完成 \n");
  SPI_Read_Data(Read_SPI_Data , 0x000000, _SPI_BufferSize);
  SPI_Show_Data(Read_SPI_Data , _SPI_BufferSize);
  
  printf("-->SPI通信指测试完毕 \n");
}
//======================================================================
//======================================================================
void fn_FatFs_Document_Init(void){
  /*----------------------- 格式化测试 -----------------*/ 
  FatFs_equipment_flash("1:");
  /*----------------------- 文件系统读写测试 -------------------*/
  FatFs_document_Text(FileTest_ADDR_Buffer_Document, "Wangqi加油!\n" );
   /*----------------------- 文件具体内容识别 -------------------*/
  file_check(FileTest_ADDR_Buffer_Document);
  /*----------------------- 文件目录更改测试 -------------------*/
  FatFs_document_set_content(FileTest_ADDR_Buffer_Document , FileTest_ADDR_Buffer_path , FileTest_ADDR_Buffer_NewDocument2);
  /*----------------------- 文件具体内容识别 -------------------*/
  file_check(FileTest_ADDR_Buffer_NewDocument2);
  /*----------------------- 文件目录查找识别 -------------------*/
  Scan_file_Check("1:");
  /*----------------------- 完成操作 -------------------*/
  FatFs_Close_flash("1:");
}
//======================================================================
//======================================================================

void fn_SRAM_Init(void){             //SRAM文件读取测试
  printf("********** SRAM_扩展内存测试 ********** \n");  
  printf("-->外部SRAM_内存函数初始化开始 \n");
  SRAM_Init();
  printf("\n-->外部SRAM_内存函数测试开始 \n");
  SRAM_Test();
  printf("\n-->外部SRAM_内存函数写入开始 \n");
  SRAM_Write();
  
}

//======================================================================
//======================================================================
void delay(int x){
	int y = 0xFFFFF;
	while((x--)>0){
		while((y--)>0){
			__NOP();
			__NOP();
			__NOP();
			__NOP();
			__NOP();
		}
	}
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

#include "SRAM_book.h" 
#include "Systick_book.h"
#include "USART_book.h"

/**
  * @brief  初始化控制SRAM的IO
  * @param  无
  * @retval 无
  */
static void SRAM_GPIO_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 
  /* 使能SRAM相关的GPIO时钟 */

                         /*地址信号线*/
  RCC_APB2PeriphClockCmd(FSMC_A0_GPIO_CLK | FSMC_A1_GPIO_CLK | FSMC_A2_GPIO_CLK | 
                         FSMC_A3_GPIO_CLK | FSMC_A4_GPIO_CLK | FSMC_A5_GPIO_CLK |
                         FSMC_A6_GPIO_CLK | FSMC_A7_GPIO_CLK | FSMC_A8_GPIO_CLK |
                         FSMC_A9_GPIO_CLK | FSMC_A10_GPIO_CLK| FSMC_A11_GPIO_CLK| 
												 FSMC_A12_GPIO_CLK| FSMC_A13_GPIO_CLK|FSMC_A14_GPIO_CLK|
												 FSMC_A15_GPIO_CLK|FSMC_A16_GPIO_CLK|FSMC_A17_GPIO_CLK|FSMC_A18_GPIO_CLK|
                         /*数据信号线*/
                         FSMC_D0_GPIO_CLK | FSMC_D1_GPIO_CLK | FSMC_D2_GPIO_CLK | 
                         FSMC_D3_GPIO_CLK | FSMC_D4_GPIO_CLK | FSMC_D5_GPIO_CLK |
                         FSMC_D6_GPIO_CLK | FSMC_D7_GPIO_CLK | FSMC_D8_GPIO_CLK |
                         FSMC_D9_GPIO_CLK | FSMC_D10_GPIO_CLK| FSMC_D11_GPIO_CLK|
                         FSMC_D12_GPIO_CLK| FSMC_D13_GPIO_CLK| FSMC_D14_GPIO_CLK|
                         FSMC_D15_GPIO_CLK|  
                         /*控制信号线*/
                         FSMC_CS_GPIO_CLK  | FSMC_WE_GPIO_CLK | FSMC_OE_GPIO_CLK |
                         FSMC_UDQM_GPIO_CLK|FSMC_LDQM_GPIO_CLK, ENABLE);
												 //UDQM UB引脚


	 /*-- GPIO 配置 -----------------------------------------------------*/

  /* 通用 GPIO 配置 */
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;       //配置为复用功能
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      //都是复用推完功能因为这个是数据手册的规定
  
  /*A地址信号线 针对引脚配置*/
  GPIO_InitStructure.GPIO_Pin = FSMC_A0_GPIO_PIN; 
  GPIO_Init(FSMC_A0_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_A1_GPIO_PIN; 
  GPIO_Init(FSMC_A1_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_A2_GPIO_PIN; 
  GPIO_Init(FSMC_A2_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_A3_GPIO_PIN; 
  GPIO_Init(FSMC_A3_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_A4_GPIO_PIN; 
  GPIO_Init(FSMC_A4_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_A5_GPIO_PIN; 
  GPIO_Init(FSMC_A5_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_A6_GPIO_PIN; 
  GPIO_Init(FSMC_A6_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_A7_GPIO_PIN; 
  GPIO_Init(FSMC_A7_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_A8_GPIO_PIN; 
  GPIO_Init(FSMC_A8_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_A9_GPIO_PIN; 
  GPIO_Init(FSMC_A9_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_A10_GPIO_PIN; 
  GPIO_Init(FSMC_A10_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_A11_GPIO_PIN; 
  GPIO_Init(FSMC_A11_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = FSMC_A12_GPIO_PIN; 
  GPIO_Init(FSMC_A12_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_A13_GPIO_PIN; 
  GPIO_Init(FSMC_A13_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_A14_GPIO_PIN; 
  GPIO_Init(FSMC_A14_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_A15_GPIO_PIN; 
  GPIO_Init(FSMC_A15_GPIO_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = FSMC_A16_GPIO_PIN; 
  GPIO_Init(FSMC_A16_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_A17_GPIO_PIN; 
  GPIO_Init(FSMC_A17_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_A18_GPIO_PIN; 
  GPIO_Init(FSMC_A18_GPIO_PORT, &GPIO_InitStructure);
    
  /*DQ数据信号线 针对引脚配置*/
  GPIO_InitStructure.GPIO_Pin = FSMC_D0_GPIO_PIN; 
  GPIO_Init(FSMC_D0_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D1_GPIO_PIN; 
  GPIO_Init(FSMC_D1_GPIO_PORT, &GPIO_InitStructure);
    
  GPIO_InitStructure.GPIO_Pin = FSMC_D2_GPIO_PIN; 
  GPIO_Init(FSMC_D2_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D3_GPIO_PIN; 
  GPIO_Init(FSMC_D3_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D4_GPIO_PIN; 
  GPIO_Init(FSMC_D4_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D5_GPIO_PIN; 
  GPIO_Init(FSMC_D5_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D6_GPIO_PIN; 
  GPIO_Init(FSMC_D6_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D7_GPIO_PIN; 
  GPIO_Init(FSMC_D7_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D8_GPIO_PIN; 
  GPIO_Init(FSMC_D8_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D9_GPIO_PIN; 
  GPIO_Init(FSMC_D9_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D10_GPIO_PIN; 
  GPIO_Init(FSMC_D10_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D11_GPIO_PIN; 
  GPIO_Init(FSMC_D11_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D12_GPIO_PIN; 
  GPIO_Init(FSMC_D12_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D13_GPIO_PIN; 
  GPIO_Init(FSMC_D13_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D14_GPIO_PIN; 
  GPIO_Init(FSMC_D14_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_D15_GPIO_PIN; 
  GPIO_Init(FSMC_D15_GPIO_PORT, &GPIO_InitStructure);
  
  /*控制信号线*/
  GPIO_InitStructure.GPIO_Pin = FSMC_CS_GPIO_PIN; 
  GPIO_Init(FSMC_CS_GPIO_PORT, &GPIO_InitStructure);
    
  GPIO_InitStructure.GPIO_Pin = FSMC_WE_GPIO_PIN; 
  GPIO_Init(FSMC_WE_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_OE_GPIO_PIN; 
  GPIO_Init(FSMC_OE_GPIO_PORT, &GPIO_InitStructure);    
  
  GPIO_InitStructure.GPIO_Pin = FSMC_UDQM_GPIO_PIN; 
  GPIO_Init(FSMC_UDQM_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = FSMC_LDQM_GPIO_PIN; 
  GPIO_Init(FSMC_LDQM_GPIO_PORT, &GPIO_InitStructure);	
}				  			


//  写时钟周期 
  //ADDSET +1 + DATAST +1 > 55ns;
  //DATAST +1 >40ns
  //ADDSET +1 > 0  ns
  //  读的时钟
  //ADDSET +1 > 25ns
  //DATAST +1 > 0 ns
  /////时钟单位 1.38*10-8S = 13.8ns
  
  //写时序
  //ADDSET
  //DATAST
  //
  //读时序
  //ADDSET = 0
  //DATAST = 2
  //
  //ADDSET +1 + DATAST +1 = (0+1+2+1)(13.8)=55.2> 55ns;
  //DATAST +1 >=2+1*(13.8 = 41.4)40ns
  //ADDSET +1  = 0+1*(13.8) = 13.8>0  ns
static void FSMC_ModleConfig(void){
  //对寄存器进行配置
  FSMC_NORSRAMTimingInitTypeDef readTimingInitStruct ;  //读时序
  FSMC_NORSRAMTimingInitTypeDef writeTimingInitStruct ; //写时序
  FSMC_NORSRAMInitTypeDef SRAMInitStruct;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);     //注意时钟使能
  
  //读
  readTimingInitStruct.FSMC_AccessMode = FSMC_AccessMode_A ;/*设置访问模式 */
  readTimingInitStruct.FSMC_AddressHoldTime = 0; //SRAM 没有用到
  readTimingInitStruct.FSMC_BusTurnAroundDuration = 0;//SRAM 没有用到
  readTimingInitStruct.FSMC_CLKDivision = 0;//SRAM 没有用到
  readTimingInitStruct.FSMC_DataLatency = 0;//SRAM 没有用到
  readTimingInitStruct.FSMC_AddressSetupTime = 0; //代表ADDSET单位13.8ns
  readTimingInitStruct.FSMC_DataSetupTime =2;//代表DATAST单位13.8ns 
  //写
  writeTimingInitStruct.FSMC_AccessMode = FSMC_AccessMode_A ;/*设置访问模式 */
  writeTimingInitStruct.FSMC_AddressHoldTime = 0; //SRAM 没有用到
  writeTimingInitStruct.FSMC_BusTurnAroundDuration = 0;//SRAM 没有用到
  writeTimingInitStruct.FSMC_CLKDivision = 0;//SRAM 没有用到
  writeTimingInitStruct.FSMC_DataLatency = 0;//SRAM 没有用到
  writeTimingInitStruct.FSMC_AddressSetupTime = 0; //代表ADDSET单位13.8ns
  writeTimingInitStruct.FSMC_DataSetupTime =2;//代表DATAST单位13.8ns 
  //到此读时序结构体完成
  
  SRAMInitStruct.FSMC_Bank = FSMC_Bank1_NORSRAM3;
  SRAMInitStruct.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; //读写时序
  SRAMInitStruct.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  SRAMInitStruct.FSMC_MemoryType = FSMC_MemoryType_SRAM;
  //SRAM 没有用到
  SRAMInitStruct.FSMC_BurstAccessMode =  FSMC_BurstAccessMode_Disable ;
  SRAMInitStruct.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
  SRAMInitStruct.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  SRAMInitStruct.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  SRAMInitStruct.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  SRAMInitStruct.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  SRAMInitStruct.FSMC_WrapMode = FSMC_WrapMode_Disable;
  SRAMInitStruct.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  SRAMInitStruct.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  //读写操作结构化评估
  SRAMInitStruct.FSMC_ReadWriteTimingStruct = &readTimingInitStruct;//读
  SRAMInitStruct.FSMC_WriteTimingStruct = &writeTimingInitStruct;//写 
  //写操作 注意FSMC_ExtendedMode 配置成 FSMC_ExtendedMode_Enable 时候有用
  
  // 吧配置写入寄存器
  FSMC_NORSRAMInit(&SRAMInitStruct);
  //使能FSMC
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM3,ENABLE);
  
}



/**
  * @brief  测试SRAM是否正常 
  * @param  None
  * @retval 正常返回1，异常返回0
  */
uint8_t SRAM_Test(void){
  /*写入数据计数器*/
  uint32_t counter=0;
  
  /* 8位的数据 */
  uint8_t ubWritedata_8b = 0, ubReaddata_8b = 0;  
  
  /* 16位的数据 */
  uint16_t uhWritedata_16b = 0, uhReaddata_16b = 0; 
  
  printf("正在检测SRAM，以8位、16位的方式读写sram...");


  /*按8位格式读写数据，并校验*/
  
  /* 把SRAM数据全部重置为0 ，IS62WV51216_SIZE是以8位为单位的 */
  for (counter = 0x00; counter < SRAM_SIZE; counter++)
  {
    *(__IO uint8_t*) (SRAM_BASE_ADDR + counter) = (uint8_t)0x0;
  }
  
  /* 向整个SRAM写入数据  8位 */
  for (counter = 0; counter < SRAM_SIZE; counter++)
  {
    *(__IO uint8_t*) (SRAM_BASE_ADDR + counter) = (uint8_t)(ubWritedata_8b + counter);
  }
  
  /* 读取 SRAM 数据并检测*/
  for(counter = 0; counter<SRAM_SIZE;counter++ )
  {
    ubReaddata_8b = *(__IO uint8_t*)(SRAM_BASE_ADDR + counter);  //从该地址读出数据
    
    if(ubReaddata_8b != (uint8_t)(ubWritedata_8b + counter))      //检测数据，若不相等，跳出函数,返回检测失败结果。
    {
      printf("8位数据读写错误！");
      return 0;
    }
  }
	 
  /*按16位格式读写数据，并检测*/
  
  /* 把SRAM数据全部重置为0 */
  for (counter = 0x00; counter < SRAM_SIZE/2; counter++)
  {
    *(__IO uint16_t*) (SRAM_BASE_ADDR + 2*counter) = (uint16_t)0x00;
  }
  
  /* 向整个SRAM写入数据  16位 */
  for (counter = 0; counter < SRAM_SIZE/2; counter++)
  {
    *(__IO uint16_t*) (SRAM_BASE_ADDR + 2*counter) = (uint16_t)(uhWritedata_16b + counter);
  }
  
    /* 读取 SRAM 数据并检测*/
  for(counter = 0; counter<SRAM_SIZE/2;counter++ )
  {
    uhReaddata_16b = *(__IO uint16_t*)(SRAM_BASE_ADDR + 2*counter);  //从该地址读出数据
    
    if(uhReaddata_16b != (uint16_t)(uhWritedata_16b + counter))      //检测数据，若不相等，跳出函数,返回检测失败结果。
    {
      printf("16位数据读写错误！\n");

      return 0;
    }
  }
  
  printf("SRAM读写测试正常！\n"); 
  /*检测正常，return 1 */
  return 1;

}



void SRAM_Init(void){
  SRAM_GPIO_Config();
  FSMC_ModleConfig();
}


static uint8_t testSRAM_Value __attribute__ ((at (SRAM_BASE_ADDR)));
  
void SRAM_Write(void){
  uint8_t* SRAM_P ;
  uint16_t* SRAM_P16 ;
  float* SRAM_Pf ;
  //---------------------------------
  SRAM_P = (uint8_t*)SRAM_BASE_ADDR;
  *SRAM_P = 0xA2;
  printf("读出的数据为1: 0x%x\n",*SRAM_P); 
  //---------------------------------
  SRAM_P16 = (uint16_t*)SRAM_BASE_ADDR;
  *SRAM_P16 = 0x2AA2;
  printf("读出的数据为2: 0x%x\n",*SRAM_P16);
  //---------------------------------
  SRAM_Pf = (float*)SRAM_BASE_ADDR;
  *SRAM_Pf = 83.65;
  printf("读出的数据为3: 0x%.2f\n",*SRAM_Pf);
  //-----------利用常量来设计----------------------
  testSRAM_Value = 0x6A;
  printf("读出的数据为1: 0x%x\n",testSRAM_Value); 
}





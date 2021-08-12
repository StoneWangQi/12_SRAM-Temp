/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
#include "ff.h"
#include "SPI_book.h"

//#include "usbdisk.h"	/* Example: Header file of existing USB MSD control module */
//#include "atadrive.h"	/* Example: Header file of existing ATA harddisk control module */
//#include "sdcard.h"		/* Example: Header file of existing MMC/SDC contorl module */

/* Definitions of physical drive number for each drive */
#define ATA		0	/* Example: Map ATA harddisk to physical drive 0 */
#define MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define USB		2	/* Example: Map USB MSD to physical drive 2 */

#define SD_CARD   0
#define SPI_FLASH 1

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = STA_NOINIT;
//	int result;

	switch (pdrv) {
    case SD_CARD : break;
    
    case SPI_FLASH :
      if(SPI_Read_ID() == _SPI_FLASH_ID){
        stat = RES_OK;
      }else{
        stat = RES_ERROR;
      }
      break;
    default:
			stat = STA_NOINIT;  
	}
	return stat;
}

//disk_status 函数只有一个参数 pdrv，表示物理编号。一般我们都是使用 switch 函数实
//现对 pdrv 的分支判断。对于 SD 卡只是预留接口，留空即可。对于 SPI Flash 芯片，我们直
//接调用在 SPI_FLASH_ReadID()获取设备 ID，

/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = STA_NOINIT;
//	int result;

	switch (pdrv) {
    case SD_CARD : break;
  
    case SPI_FLASH :
      SPI_FLASH_Init();
      SPI_Flash_WAKEUP();
      stat = disk_status(SPI_FLASH);
      break;
    default:
			stat = STA_NOINIT;  
	}
	return stat;
}

//disk_initialize 函数也是有一个参数 pdrv，用来指定设备物理编号。对于 SPI Flash 芯片
//我们调用 SPI_FLASH_Init()函数实现对 SPI Flash 芯片引脚 GPIO 初始化配置以及 SPI 通信
//参数配置。SPI_Flash_WAKEUP()函数唤醒 SPI Flash 芯片，当 SPI Flash 芯片处于睡眠模式
//时需要唤醒芯片才可以进行读写操作。

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res = RES_PARERR;
	//int result;

	switch (pdrv) {
    case SD_CARD : break;
  
    case SPI_FLASH :
      // 扇区偏移2MB  外部Flash 文件系统空间放在 SPI_FLAH后面的6MB空间
      sector += 512;
      SPI_Read_Data(buff,(sector << 12),(count << 12));
      res = RES_OK ; 
      break;
    default:
			res = RES_PARERR;  
	}

	return res;
}

//SPI Flash 芯片型号为 W25Q64FV，每个扇区大小为 4096 个字节(4KB)，
//总共有 8M 字节空间，为兼容后面实验程序，我们只将后部分 6MB 空间分配给 FatFs 使用，
//前部分 2MB 空间用于其他实验需要，即 FatFs 是从 2MB 空间开始，为实现这个效果需要
//将所有的读写地址都偏移 512 个扇区空间

/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res = RES_PARERR;
	//int result;
  if(!count){return res;}
	switch (pdrv) {
	  case SD_CARD : break;
  
    case SPI_FLASH :
      // 扇区偏移2MB  外部Flash 文件系统空间放在 SPI_FLAH后面的6MB空间
      sector += 512;
      SPI_Erase_Sector(sector << 12);
      SPI_BufferWrite_Data((uint8_t *)buff ,sector << 12,count << 12);
      res = RES_OK ; 
      break;
    default:
			res = RES_PARERR;  
	}

	return res;
}
#endif
//disk_write 函数有四个形参，pdrv 为设备物理编号。buff 指向待写入扇区数据的首地址。
//sector，指定要写入数据的扇区首地址。count 指定扇区数量。对于 SPI Flash 芯片，在写入
//数据之前需要先擦除，所以用到扇区擦除函数(SPI_FLASH_SectorErase)。然后就是在调用
//数据写入函数(SPI_FLASH_BufferWrite)把数据写入到指定位置内。

/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res = RES_PARERR;
//	int result;

	switch (pdrv) {
    case SD_CARD : break;
  
    case SPI_FLASH :{
       switch(cmd){
          //返回 扇区的个数 1280*4096/1024/1024 = 5MB
         case GET_SECTOR_COUNT:
           *(DWORD * )buff = 1280;
           break;
         //返回每一个扇区的大小
         case GET_SECTOR_SIZE:
           *(DWORD * )buff = 4096;
           break;
         case GET_BLOCK_SIZE:
           *(DWORD * )buff = 1;
           break;    
         default:
          return RES_PARERR; 
       }
       res = RES_OK;
       break;
    }
   default:
      res =  RES_PARERR;     
	}
	return res;
}
#endif

 DWORD get_fattime(void) {
	/* 返回当前时间戳 */
	return	  ((DWORD)(2015 - 1980) << 25)	/* Year 2015 */
			| ((DWORD)1 << 21)				/* Month 1 */
			| ((DWORD)1 << 16)				/* Mday 1 */
			| ((DWORD)0 << 11)				/* Hour 0 */
			| ((DWORD)0 << 5)				  /* Min 0 */
			| ((DWORD)0 >> 1);				/* Sec 0 */
}


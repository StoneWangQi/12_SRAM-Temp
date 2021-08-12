#ifndef  __FATFS_BOOK_H_
#define  __FATFS_BOOK_H_

#include "ff.h"			/* Declarations of FatFs API */

extern FATFS     fs;                   /* FatFs 文件系统对象 */
extern FIL       fnew;                 /* 文件对象 */
extern FRESULT   res_flash;            /* 文件操作结果 */
extern UINT      fnum;                 /* 文件成功读写数量 */
extern BYTE      FATFS_buffer[0];      /* 读缓冲区 */
extern BYTE      textFile_Buffer[];
extern BYTE      textFile_Buffer2[];
extern BYTE      File_Read_Buffer[1024];
 
#define  textFile_Buffer         "欢迎自己完成第一阶段回国隔离任务，后面加油 今天是个好日子，新建文件系统测试文件\r\n" 
 
#define  FileTest_ADDR_Buffer_Document        "1:Wangqi.txt" 
#define  FileTest_ADDR_Buffer_NewDocument     "1:Wangqi/Wangqi.txt" 
#define  FileTest_ADDR_Buffer_path            "1:test" 
#define  FileTest_ADDR_Buffer_NewDocument2    "1:test/testdir.txt" 
    
FRESULT FatFs_equipment_flash(
  const TCHAR* path
);
FRESULT FatFs_Close_flash(
  const TCHAR* path 
);
BYTE* FatFs_document_Text(
  const TCHAR* _File_ADDR ,
  BYTE* Text_Buffer 
);
  
void FatFs_document_set_content(
  const TCHAR* _File_ADDR , 
  const TCHAR* _File_OldPath , 
  const TCHAR* _File_NewPath 
);
  
FRESULT file_check(const TCHAR*  FileTest_ADDR); 
FRESULT Scan_file_Check(const TCHAR*  File_ADDR);
  
#endif

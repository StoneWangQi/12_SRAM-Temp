#include "FatFs_book.h"
#include "Systick_book.h"
#include "USART_book.h"
#include "string.h"
FATFS     fs;                   /* FatFs 文件系统对象 */
FIL       fnew;                 /* 文件对象 */
FRESULT   res_flash;            /* 文件操作结果 */
UINT      fnum;                 /* 文件成功读写数量 */
BYTE      FATFS_buffer[0];      /* 读缓冲区 */
 
/**************************************************************
* @brief  
* FRESULT FatFs_equipment_flash(const TCHAR* path )
* @param  
* 
*FatFs 的第一步工作就是使用 f_mount 函数挂载工作区。f_mount 函数有三个形参，第
*一个参数是指向 FATFS 变量指针，如果赋值为 NULL 可以取消物理设备挂载。第二个参数
*为逻辑设备编号，使用设备根路径表示，与物理设备编号挂钩，在代码清单 26-1 中我们定
*义 SPI Flash 芯片物理编号为 1，所以这里使用“1：”。第三个参数可选 0 或 1，1 表示立
*即挂载，0 表示不立即挂载，延迟挂载。 f_mount 函数会返回一个 FRESULT 类型值，指示
*运行情况。
*如果 f_mount 函数返回值为 FR_NO_FILESYSTEM，说明没有 FAT 文件系统，比如新
*出厂的 SPI Flash 芯片就没有 FAT 文件系统。我们就必须对物理设备进行格式化处理。使用
*f_mkfs 函数可以实现格式化操作。f_mkfs 函数有三个形参，第一个参数为逻辑设备编号；
*第二参数可选 0 或者 1，0 表示设备为一般硬盘，1 表示设备为软盘。第三个参数指定扇区
*大小，如果为 0，表示通过代码清单 26-6 中 disk_ioctl 函数获取。格式化成功后需要先取消
*挂载原来设备，再重新挂载设备。
*
*/
FRESULT FatFs_equipment_flash(
  const TCHAR* path 
){
  //在外部 SPI Flash 挂载文件系统，文件系统挂载时会对 SPI 设备初始化
  //初始化函数调用流程如下
  //f_mount()->find_volume()->disk_initialize->SPI_FLASH_Init()
  DIR     dir;
  FATFS   *pfs;
  DWORD   fre_clust , fre_sect , tot_sect ;
  printf("\n********** 外部SPIFlash挂载文件系统 **********\r\n");
  printf(" 在外部SPI Flash挂载文件系统，文件系统挂载时会对SPI设备初始化\r\n");
  res_flash = f_mount(&fs ,path,1); //SPI Flash 芯片物理编号为 1，所以这里使用“1：”。
  /* Pointer to the file system object (NULL:unmount)*/
  /* Logical drive number to be mounted/unmounted */
  /* 0:Do not mount (delayed mount), 1:Mount immediately */
  /*----------------------- 格式化测试 -----------------*/
  /* 如果没有文件系统就格式化创建创建文件系统 */  
  if(res_flash ==  FR_NO_FILESYSTEM ){  
    printf("》FLASH 还没有文件系统，即将进行Flash FatFS 格式化...\r\n");
    /* 格式化 */
    res_flash=f_mkfs(path,0,0);/* Create a file system on the volume */
     /* Logical drive number */
	   /* Partitioning rule 0:FDISK, 1:SFD */
	   /* Size of allocation unit in unit of byte or sector */
    //格式完成，先取消挂载
    if(res_flash == FR_OK ){
      printf("》FLASH 已成功格式化文件系统。\r\n");
      res_flash = f_mount(NULL ,path ,1); 
      //重新挂载
      res_flash = f_mount(&fs ,path ,1); 
    }else{
      printf("》格式化失败。 \r\n");
      return res_flash;
    } 
  }
  else if(res_flash != FR_OK){
    printf("！外部 Flash 挂载文件系统失败。(%d)\r\n",res_flash);
    printf("！可能原因：SPI Flash 初始化不成功。\r\n");
    return res_flash;
  }
  else{
    printf("》文件系统挂载成功，可以进行读写测试\r\n");
  } 
  
  //获取设备信息和空间的大小
  res_flash  = f_getfree(path ,&fre_clust ,&pfs );
  //计算得到的总扇区个数和空扇区个数
  tot_sect = (pfs->n_fatent-2)*pfs->csize ;
  fre_sect = fre_clust * pfs->csize ;
  /* 打印信息(4096 字节/扇区) */
  printf("》设备总空间：%10lu KB。\n》可用空间：  %10lu KB。\r\n", tot_sect<<2, fre_sect<<2);
  return FR_OK;
}

/**************************************************************
* @brief  
* FRESULT FatFs_Close_flash( const TCHAR* path )
* @param  
*  关闭Flash操作
**************************************************************/
FRESULT FatFs_Close_flash(
  const TCHAR* path 
){
  res_flash=f_mkfs(path,0,0);
  /* 不再使用文件系统，取消挂载文件系统 */
 return f_mount(NULL ,path ,1);
}

/**************************************************************
* @brief  
* void FatFs_document_Text(
*  const TCHAR* _File_ADDR , 文件的目录
*  BYTE* Text_Buffer       需要写入的内容
*)
* @param  
*  关闭Flash文件的读写操作
**************************************************************/
BYTE* FatFs_document_Text(
  const TCHAR* _File_ADDR ,
  BYTE* Text_Buffer   
){
  BYTE  File_Read_Buffer[1024]={0}  ;
 
  printf("\n******** 文件%s定位和格式化写入功能测试 ********\r\n",File_Read_Buffer);
  res_flash = f_open(&fnew , _File_ADDR, FA_OPEN_ALWAYS|FA_WRITE|FA_READ );
  if( res_flash == FR_OK ){
    //res_flash = f_write(&fnew,Text_Buffer ,sizeof(Text_Buffer), &fnum);  这个函数有点问题:sizeof(Text_Buffer)
    //f_printf(&fnew ,Text_Buffer );
    printf("******** 文件定位追加内容 ********\r\n");
    res_flash = f_lseek(&fnew , f_size(&fnew));	//文件定位到 文件的末尾   Move file pointer of a file object  
    if( res_flash == FR_OK ){
      //格式化写入 参数格式类似printf函数
      f_printf(&fnew ,Text_Buffer );  
      res_flash = f_lseek(&fnew,0);
      res_flash = f_read(&fnew , File_Read_Buffer , f_size(&fnew),&fnum );
      if(res_flash == FR_OK){
        printf("> 文件内容：\n%s\n" ,File_Read_Buffer );
      }
    }  
  }
  else{
    printf("!! 打开文件失败：%d\n",res_flash);
    printf("!! 或许需要再次运行“FatFs移植与读写测试”工程\n");
  }
  f_close(&fnew);
  return File_Read_Buffer;
}
 

/**************************************************************
* @brief  
*void FatFs_document_set_content(
*  const TCHAR* _File_ADDR ,  //文件原始名字路径
*  const TCHAR* _File_OldPath ,//建立新的文件夹目录 
*  const TCHAR* _File_NewPath  //文件移动以后的文件目录
*)
* @param  
*  文件目录的更改
**************************************************************/
void FatFs_document_set_content(
  const TCHAR* _File_ADDR , 
  const TCHAR* _File_OldPath , 
  const TCHAR* _File_NewPath 
){
   DIR     dir;
  //尝试打开目录、
  printf("\n********** 目录创建和重命名功能测试 **********\r\n");
  res_flash = f_opendir(&dir,_File_OldPath);
  if(res_flash != FR_OK){
    printf("!! 打开目录%s 失败开始尝试创建新的目录\n",_File_OldPath);
    res_flash = f_mkdir(_File_OldPath);
      res_flash = f_opendir(&dir,_File_OldPath);
      if(res_flash != FR_OK){
         printf("!! 创建新的目录还是失败(%d) \n",res_flash);
         return;
      } 
  }
  else{
    printf("!! 如果目录已经存在，关闭它\n"); 
    res_flash = f_closedir(&dir);
    //删除文件
    f_unlink(_File_NewPath);
  }
    //重命名并移动文件
    res_flash=f_rename(_File_ADDR , _File_NewPath);
    printf(">  重命名并移动文件%d完成 \n",res_flash);

 
}

/**************************************************************
* @brief  
* FRESULT file_check(const TCHAR*  File_ADDR)
* @param  
* 文件属性的查看
**************************************************************/
FRESULT file_check(const TCHAR*  File_ADDR){
  static FILINFO fno;
  printf("\n********** file_check 测试 **********\r\n");
  /* 获取文件信息，必须确保文件存在*/
  res_flash = f_stat(File_ADDR,&fno);
  if(res_flash==FR_OK){
    printf("%s 文件信息：\n",File_ADDR);
    printf("》文件大小: %ld(字节)\n", fno.fsize);
    printf("》时间戳: %u/%02u/%02u, %02u:%02u\n",
      (fno.fdate >> 9) + 1980, fno.fdate >> 5 & 15, fno.fdate & 31,
       fno.ftime >> 11, fno.ftime >> 5 & 63);
    printf("》属性: %c%c%c%c%c\n\n",
      (fno.fattrib & AM_DIR) ? 'D' : '-', // 是一个目录
      (fno.fattrib & AM_RDO) ? 'R' : '-', // 只读文件
      (fno.fattrib & AM_HID) ? 'H' : '-', // 隐藏文件
      (fno.fattrib & AM_SYS) ? 'S' : '-', // 系统文件
      (fno.fattrib & AM_ARC) ? 'A' : '-'); // 档案文件
  }  
  else{
     printf("》错误 %ld(字节)\n",res_flash);
  }
  return res_flash;
} 

/**************************************************************
* @brief  
* FRESULT scan_file(char*  File_ADDR)
* @param  
* 文件目录内容的查看
**************************************************************/
static FRESULT scan_file(char*  File_ADDR){
  FRESULT res;  //部分在递归过程被修改的变了
  FILINFO fno;
  DIR     dir;
  int     i;
  TCHAR*  fn;
#if _USE_LFN  
  //长文件名支持
  //简体中文需要2个字节保存一个字
  static char lfn[_MAX_LFN*2 + 1];
  fno.lfname = lfn;
  fno.lfsize = sizeof(lfn);
#endif
  //打开目录 
  res = f_opendir(&dir, File_ADDR);
  if(res == FR_OK){
    i = strlen(File_ADDR);
    while(1){
      //读取 目录下的内容，再读会自动读取下一个文件
      res = f_readdir(&dir , &fno);
      //为空时候表示读取完毕
      if((res != FR_OK) || (fno.fname[0] == 0 )){
        break;}
#if _USE_LFN  
      fn = *fno.lfname ?fno.lfname : fno.fname ;
#else
      fn = fno.fname;
#endif 
      //表示当前目录跳过
      if(*fn == '.'){continue;}
      //目录 递归读取
      if( fno.fattrib & AM_DIR ){
        //合成完整目录名
        sprintf(&File_ADDR[i], "/%s", fn); 
        //递归遍历
        res = scan_file(File_ADDR);
        //打开失败，跳出循环
        File_ADDR[i] = 0;
        if(res != FR_OK ){break;}
      }else{
        printf( "%s/%s\r\n" , File_ADDR  , fn);
      }
    }
  }
  else{
    printf("》错误 %d \n",res);
  }
  return res;
}

/**************************************************************
* @brief  
* FRESULT Scan_file_Check(const TCHAR*  File_ADDR)
* @param  
* 文件目录内容的查看
**************************************************************/
FRESULT Scan_file_Check(const TCHAR*  File_ADDR){
  BYTE      fpath[100];                  /* 保存当前扫描路径 */
  printf("\n********** file_路径测试 **********\r\n");
  strcpy(fpath,File_ADDR);
  return scan_file(fpath); 
}


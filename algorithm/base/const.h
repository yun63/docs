/// =====================================================================================
/// 
///    @filename         :  const.h
/// 
///    @description      :  常量定义
/// 
/// -------------------------------------------------------------------------------------
///    @version          :  1.0
///    @created          :  2014年03月30日 20时02分31秒
///    @revision         :  none
///    @compiler         :  g++
/// 
///    @author           :  Lei Yunfei (leiyunfei), yunfei_lei@126.com
///    @Company          :  
/// 
/// =====================================================================================

#ifndef  __CONST_H_
#define  __CONST_H_

#define     MAX_LINE        4096
#define     BUFF_SIZE       8192
#define     SERVER_PORT     9877
#define     SERVER_PORT_STR "9877"
#define     UNIXSTR_PATH    "/tmp/unix.str"
#define     UNIXDG_PATH     "/tmp/unix.dg"

#define     SA              struct sockaddr 

/* Default file access permissions for new files 
 */
#define FILE_MODE	(S_IRUSR | S_IWUSE | S_IRGRP | S_IROTH)

/* Default permissions for new directories
 */
#define DIR_MODE	(FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)

#endif   // ----- #ifndef __CONST_H_ -----

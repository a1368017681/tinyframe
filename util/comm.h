/**********************************************************
 * Author        : geqiankun
 * Email         : scugqk@gmail.com
 * Last modified : 2017-12-07 20:30
 * Filename      : comm.h
 * Description   : 
 * *******************************************************/

#ifndef _COMM_H

#include <assert.h>

#ifndef TCHAR
#ifdef _UNICODE
typedef wchar_t         TCHAR;
#else
typedef char            TCHAR;
#endif
#endif

typedef unsigned char       uchar;
typedef unsigned short      ushort;
typedef unsigned int        uint;
typedef unsigned long       ulong;

#define charptr             char*
#define const_charptr       const char*

typedef int64_t             int64;
typedef int32_t             int32;
typedef int16_t             int16;
typedef int8_t              int8;
typedef uint64_t            uint64;
typedef uint32_t            uint32;
typedef uint16_t            uint16;
typedef uint8_t             uint8;
typedef uint16_t            WORD;
typedef uint32_t            DWORD;


#endif

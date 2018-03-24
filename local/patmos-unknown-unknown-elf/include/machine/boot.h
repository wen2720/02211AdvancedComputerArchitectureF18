/*
   Copyright 2014 Technical University of Denmark, DTU Compute. 
   All rights reserved.
   
   This file is part of the time-predictable VLIW processor Patmos.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

      1. Redistributions of source code must retain the above copyright notice,
         this list of conditions and the following disclaimer.

      2. Redistributions in binary form must reproduce the above copyright
         notice, this list of conditions and the following disclaimer in the
         documentation and/or other materials provided with the distribution.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER ``AS IS'' AND ANY EXPRESS
   OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
   OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
   NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
   THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

   The views and conclusions contained in the software and documentation are
   those of the authors and should not be interpreted as representing official
   policies, either expressed or implied, of the copyright holder.
 */

/*
 * Definitions for CMP boot loaders.
 * 
 * Author: Wolfgang Puffitsch (wpuffitsch@gmail.com)
 *
 */

#ifndef _BOOT_H
#define _BOOT_H

#include <machine/patmos.h>

#define MAX_CORES 64

#define STATUS_NULL     0
#define STATUS_BOOT     1
#define STATUS_INIT     2
#define STATUS_INITDONE 3
#define STATUS_RETURN   4

#ifndef __ENTRYPOINT_T
typedef volatile int (*entrypoint_t)(void);
#define __ENTRYPOINT_T
#endif

#ifndef __FUNCPOINT_T
typedef volatile void (*funcpoint_t)(void*);
#define __FUNCPOINT_T
#endif

struct master_info_t {  
  volatile entrypoint_t entrypoint;
  volatile int status;
};

struct slave_info_t {
  volatile funcpoint_t funcpoint;
  volatile void* param;
  volatile int return_val;
  volatile int status;
};

struct boot_info_t {
  struct master_info_t master;
  struct slave_info_t slave[MAX_CORES];
};

/* Place boot info at the beginning of the memory. Nothing else may be
   placed there. */
#define boot_info ((_UNCACHED struct boot_info_t *)0x00000010)

#endif /* _BOOT_H */

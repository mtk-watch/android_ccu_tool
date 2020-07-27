/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2016
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

#ifndef CCU_LENS_PORTING_H
#define CCU_LENS_PORTING_H


#include "ccu_ext_interface/ccu_types.h"
#include "lens/ccu_lens_if.h"

/******************************************************************************
* Function prototypes
*
* These functions can be used in lens drivers and they will be directed to the
* corresponding functions in the CCU Main binary.
******************************************************************************/
int iWriteI2CSlaveAddr(char *wData , u16 wrLength, u32 slave_addr);
int iReadI2CSlaveAddr(char *rData , u16 rdLength, u32 slave_addr);
void MyLog(char *msg);
void MyAssert(char *msg, int errno);
void MyWarning(char *msg);


/******************************************************************************
******************************************************************************/
#define GENERATE_FUNC_TABLE_CODE()                                                                        \
    /*** ConvertedShutter = PC_CLK / LINE_LENGTH * shutter / 10^6 ***/                                    \
    /* Functions cannot be removed without recompilation of the Main */                                   \
    /* binary. New functions must be appended to the end of this table. */                                \
    static LENS_FUNC_TABLE_T func_table =                                                                 \
    {                                                                                                     \
        sizeof(func_table),                                                                               \
        moveAF,                                                                                           \
        (PFN_I2C_WRITE_SLAVEADDR_FUNC)0xFFFFFFFF,         /* To be fixed at run time */                   \
        (PFN_I2C_READ_SLAVEADDR_FUNC)0xFFFFFFFF,       /* To be fixed at run time */                      \
        (PFN_LOG)0xFFFFFFFF,                        /* To be fixed at run time */                         \
        (PFN_ASSERT)0xFFFFFFFF,                     /* To be fixed at run time */                         \
        (PFN_WARNING)0xFFFFFFFF                     /* To be fixed at run time */                         \
    };                                                                                                    \
                                                                                                          \
    int iWriteI2CSlaveAddr(char *wData , u16 wrLength, u32 slave_addr)                                    \
    {                                                                                                     \
        return func_table.pfnI2CWriteSlaveAddrFunc(wData, wrLength, slave_addr);                          \
    }                                                                                                     \
                                                                                                          \
    int iReadI2CSlaveAddr(char *rData , u16 rdLength, u32 slave_addr)                                     \
    {                                                                                                     \
        return func_table.pfnI2CReadSlaveAddrFunc(rData, rdLength, slave_addr);                           \
    }                                                                                                     \
                                                                                                          \
    void MyLog(char *msg)                                                                                 \
    {                                                                                                     \
        func_table.pfnLog(CCU_LENS_LOGTAG,0,msg,0,0,0,0);                                               \
    }                                                                                                     \
                                                                                                          \
    void MyAssert(char *msg, int errno)                                                                   \
    {                                                                                                     \
        func_table.pfnAssert(msg, errno);                                                                 \
    }                                                                                                     \
                                                                                                          \
    void MyWarning(char *msg)                                                                             \
    {                                                                                                     \
        func_table.pfnWarning(msg);                                                                       \
    }                                                                                                     \
                                                                                                          \
    /* Do NOT define GetFuncTable() as a static function!!! */                                            \
    void __attribute__ ((section(".text.getfunctable")))                                                  \
        GetFuncTable(LENS_FUNC_TABLE_T **ppFuncTable)                                                     \
    {                                                                                                     \
        *ppFuncTable = &func_table;                                                                       \
    }


#endif  // CCU_LENS_PORTING_H


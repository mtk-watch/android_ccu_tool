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

#ifndef CCU_CUSTFUNC_IF_H
#define CCU_CUSTFUNC_IF_H


#include "ccu_main/ccu_debug.h"     // for CCU_ERROR_T
#include "ccu_main/ccu_log.h"     // for ccu_log_tag
#include "ccu_custfunc_porting.h"
#include "algorithm/ccu_ae_param.h"

#if __SIMTRACER__ || __PLATFORM__
#include <stdio.h>
#endif

/******************************************************************************
* Define types of function pointers
******************************************************************************/
typedef void (*PFN_LOG)(ccu_log_tag log_tag, unsigned char arg_num, char *log_str, MINT32 value1, MINT32 value2, MINT32 value3, MINT32 value4);
typedef void (*PFN_ASSERT)(char*, int);
typedef void (*PFN_WARNING)(char*);
typedef void (*PFN_TRANSSUPERNIGHTSHOT)(CCU_AE_CUST_Super_Night_Param_T* a_AeCustParam, const MVOID* const pNVRAMData, MVOID* const pData);


/******************************************************************************
* Cust function table
******************************************************************************/
typedef struct CUST_FUNC_TABLE
{   
    unsigned int u2TableSize;
    PFN_TRANSSUPERNIGHTSHOT pfnTransSuperNightShot;
    PFN_LOG pfnLog;                                          // Initialized at run time.
    PFN_ASSERT pfnAssert;                                    // Initialized at run time.
    PFN_WARNING pfnWarning;                                  // Initialized at run time.
} CUST_FUNC_TABLE_T;



#endif  // CCU_SENSOR_IF_H


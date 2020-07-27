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

#ifndef CCU_SENSOR_PORTING_H
#define CCU_SENSOR_PORTING_H


#include "ccu_ext_interface/ccu_sensor_extif.h"
#include "ccu_sensor_if.h"
#include "imgsensor/ccu_sensor_fctrl.h"
#include "ccu_main/ccu_log.h"     // for ccu_log_tag

/******************************************************************************
* For easier customization/porting.
* To save one byte of memory space, define DEFINE_SPINLOCK to be an empty macro.
* Even though macro parameters are not used, it may be defined to be a
* type-casting expression to eliminate build warning.
******************************************************************************/
#define DEFINE_SPINLOCK(X)              /* Empty! or U8 X = 0 */
#define LOG_INF(X, ...)                 /* Empty! */
#define spin_lock(X)                    /* Empty! */
#define spin_lock_irq(X)                /* Empty! */
#define spin_lock_irqsave(X, Y)         /* Empty! or ((void*)Y) */
#define spin_unlock(X)                  /* Empty! */
#define spin_unlock_irq(X)              /* Empty! */
#define spin_unlock_irqrestore(X, Y)    /* Empty! or ((void*)Y) */
#define SENSORDB(X, ...)                /* Empty! */
#define mdelay(X)                       /* Empty! */
// #define KAL_FALSE                       0
// #define KAL_TRUE                        1

/******************************************************************************
******************************************************************************/
#define BASEGAIN                    0x40


/******************************************************************************
* Function prototypes
*
* These functions can be used in sensor drivers and they will be directed to the
* corresponding functions in the CCU Main binary.
******************************************************************************/
int iWriteRegI2C(char *pu1SendData , u16 u2DataSize, u16 u2I2CID);
int iWriteRegI2CTiming(char *pu1SendData , u16 wrLength, u16 wrPerCycle, u16 u2I2CID, u16 timing);
void iReadRegI2CTiming(char *wData, u16 wLen, char *rData, u16 rLen, u16 u2I2CID, u16 timing);
void MyLog(char *msg);
void MyAssert(char *msg, int errno);
void MyWarning(char *msg);


/******************************************************************************
******************************************************************************/
#define GENERATE_FUNC_TABLE_CODE()                                                                        \
    /*** ConvertedShutter = PC_CLK / LINE_LENGTH * shutter / 10^6 ***/                                    \
    static kal_uint32 time_to_line_count(kal_uint32 mtime)                                                \
    {                                                                                                     \
        unsigned long long line_count = imgsensor.pclk / 1000000;                                         \
        line_count *= mtime;                                                                              \
        line_count /= imgsensor.line_length;                                                              \
        return (kal_uint32)line_count;                                                                    \
    }                                                                                                     \
                                                                                                          \
    static void sensor_driver_ctrl(enum CCU_MSDK_SENSOR_FEATURE_ENUM cmdType, void *prIn, void *prOut)    \
    {                                                                                                     \
        switch(cmdType)                                                                                   \
        {                                                                                                 \
            case CCU_SENSOR_FEATURE_SET_ESHUTTER:                                                         \
                MyLog("CCU_SENSOR_FEATURE_SET_ESHUTTER\n");                                               \
                feature_control(SENSOR_FEATURE_SET_ESHUTTER, prIn, NULL);                                 \
                break;                                                                                    \
            case CCU_SENSOR_FEATURE_SET_GAIN:                                                             \
                MyLog("CCU_SENSOR_FEATURE_SET_GAIN\n");                                                   \
                feature_control(SENSOR_FEATURE_SET_GAIN, prIn, NULL);                                     \
                break;                                                                                    \
            case CCU_SENSOR_FEATURE_SET_SHUTTER_FRAME_TIME:                                               \
                MyLog("CCU_SENSOR_FEATURE_SET_SHUTTER_FRAME_TIME\n");                                     \
                feature_control(SENSOR_FEATURE_SET_SHUTTER_FRAME_TIME, prIn, NULL);                       \
                break;                                                                                    \
            case CCU_SENSOR_FEATURE_SET_HDR_SHUTTER:                                                      \
                MyLog("CCU_SENSOR_FEATURE_SET_HDR_SHUTTER\n");                                            \
                feature_control(SENSOR_FEATURE_SET_HDR_SHUTTER, prIn, NULL);                              \
                break;                                                                                    \
            case CCU_SENSOR_FEATURE_SET_DUAL_GAIN:                                                        \
                MyLog("CCU_SENSOR_FEATURE_SET_HDR_DUAL_GAIN\n");                                          \
                feature_control(SENSOR_FEATURE_SET_DUAL_GAIN, prIn, NULL);                                \
                break;                                                                                    \
            case CCU_SENSOR_FEATURE_SET_HDR_TRI_SHUTTER:                                                  \
                MyLog("CCU_SENSOR_FEATURE_SET_HDR_TRI_SHUTTER\n");                                        \
                feature_control(SENSOR_FEATURE_SET_HDR_TRI_SHUTTER, prIn, NULL);                          \
                break;                                                                                    \
            case CCU_SENSOR_FEATURE_SET_HDR_TRI_GAIN:                                                     \
                MyLog("CCU_SENSOR_FEATURE_SET_HDR_TRI_GAIN\n");                                           \
                feature_control(SENSOR_FEATURE_SET_HDR_TRI_GAIN, prIn, NULL);                             \
                break;                                                                                    \
            case CCU_SENSOR_FEATURE_SET_HDR:                                                              \
                MyLog("CCU_SENSOR_FEATURE_SET_HDR\n");                                                    \
                feature_control(SENSOR_FEATURE_SET_HDR, prIn, NULL);                                      \
                break;                                                                                    \
            case CCU_SENSOR_FEATURE_SET_FLICKER:                                                          \
                imgsensor.autoflicker_en = (bool *)prIn;                                                  \
                break;                                                                                    \
            case CCU_SENSOR_FEATURE_SET_FPS:                                                              \
                imgsensor.current_fps = (U16 *)prIn;                                                      \
                break;                                                                                    \
            case CCU_SENSOR_FEATURE_GET_FPS:                                                              \
                *(U16 *)prOut = (U16 *)imgsensor.current_fps;                                             \
                break;                                                                                    \
            case CCU_SENSOR_FEATURE_GET_GDELAY:                                                           \
                *(U8 *)prOut = (U8 *)imgsensor.u8GainDelay;                                               \
                break;                                                                                    \
            case CCU_SENSOR_FEATURE_GET_SDELAY:                                                           \
                *(U8 *)prOut = (U8 *)imgsensor.u8ShutterDelay;                                            \
                break;                                                                                    \
            case CCU_SENSOR_FEATURE_GET_FDELAY:                                                           \
                *(U8 *)prOut = imgsensor_info.frame_time_delay_frame;                                     \
                break;                                                                                    \
            case CCU_SENSOR_FEATURE_GET_TXLEN:                                                            \
                *(U16 *)prOut = (U16 *)imgsensor.u8I2CTransferLength;                                     \
                break;                                                                                    \
            case CCU_SENSOR_FEATURE_GET_MIN_FL:                                                           \
                *(U16 *)prOut = imgsensor.min_frame_length;                                               \
                break;                                                                                    \
            case CCU_SENSOR_FEATURE_GET_CCU_SUPPORT:                                                      \
                *(U8 *)prOut = (U8 *)(imgsensor.u8I2CTransferLength != 0);                                \
                break;                                                                                    \
            case CCU_SENSOR_FEATURE_GET_PCLK_LINELENGTH:                                                  \
                *(U32 *)prOut = (imgsensor.pclk);                                                         \
                *(((U32 *)prOut)+1) = (imgsensor.line_length);                                            \
                break;                                                                                    \
            case CCU_SENSOR_FEATURE_SET_MIN_FL:                                                           \
                imgsensor.min_frame_length = (U32 *)prIn;                                                 \
                break;                                                                                    \
            case CCU_SENSOR_FEATURE_GET_VBLANKING:                                                        \
                *(U32 *)prOut = imgsensor.v_blanking_us;                                                  \
                break;                                                                                    \
            default:                                                                                      \
                MyLog("CCU_SENSOR_FEATURE_DEFAULT\n");                                                    \
                break;                                                                                    \
        }                                                                                                 \
    }                                                                                                     \
    /* Functions cannot be removed without recompilation of the Main */                                   \
    /* binary. New functions must be appended to the end of this table. */                                \
    static SENSOR_FUNC_TABLE_T func_table =                                                               \
    {                                                                                                     \
        sizeof(func_table),                                                                               \
        sensor_driver_ctrl,                                                                               \
        time_to_line_count,                                                                               \
        control,                                                                                          \
        set_max_framerate_by_scenario,                                                                    \
        (PFN_I2C_WRITE_REG_FUNC)0xFFFFFFFF,         /* To be fixed at run time */                         \
        (PFN_I2C_WRITE_REG_TIMIMG_FUNC)0xFFFFFFFF,  /* To be fixed at run time */                         \
        (PFN_I2C_READ_REG_TIMING_FUNC)0xFFFFFFFF,   /* To be fixed at run time */                         \
        (PFN_LOG)0xFFFFFFFF,                        /* To be fixed at run time */                         \
        (PFN_ASSERT)0xFFFFFFFF,                     /* To be fixed at run time */                         \
        (PFN_WARNING)0xFFFFFFFF                     /* To be fixed at run time */                         \
    };                                                                                                    \
                                                                                                          \
    int iWriteRegI2C(char *pu1Data , u16 u2Size, u16 u2I2CID)                                             \
    {                                                                                                     \
        func_table.pfnI2CWriteRegFunc(pu1Data, u2Size, u2I2CID);                                          \
        return false;                                                                                     \
    }                                                                                                     \
	                                                                                                      \
    int iWriteRegI2CTiming(char *pu1Data, u16 u2Size, u16 wrCycle, u16 u2I2CID, u16 timing)               \
    {                                                                                                     \
        func_table.pfnI2CWriteRegTimingFunc(pu1Data, u2Size, wrCycle, u2I2CID, timing);                   \
		return false;                                                                                     \
    }                                                                                                     \
    void iReadRegI2CTiming(char *wData, u16 wLen, char *rData, u16 rLen, u16 u2I2CID, u16 timing)         \
    {                                                                                                     \
        func_table.pfnI2CReadRegTimingFunc(wData, wLen, rData, rLen, u2I2CID, timing);                    \
    }                                                                                                     \
                                                                                                          \
    void MyLog(char *msg)                                                                                 \
    {                                                                                                     \
        func_table.pfnLog(CCU_SENSOR_LOGTAG,0,msg,0,0,0,0);                                               \
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
        GetFuncTable(SENSOR_FUNC_TABLE_T **ppFuncTable)                                                   \
    {                                                                                                     \
        *ppFuncTable = &func_table;                                                                       \
    }


#endif  // CCU_SENSOR_PORTING_H


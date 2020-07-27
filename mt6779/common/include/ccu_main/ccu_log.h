#ifndef __CCU_LOG_H__
#define __CCU_LOG_H__

typedef enum
{
    CCU_FLOW_BASIC_LOGTAG = 0,
    CCU_MUST_LOGTAG,
    CCU_SENSOR_LOGTAG,
    CCU_LENS_LOGTAG,
    CCU_AE_FLOW_LOGTAG,
    CCU_AE_ALGO_LOGTAG,
    CCU_AE_SYNC_ALGO_LOGTAG,
    CCU_AF_FLOW_LOGTAG,
    CCU_AF_ALGO_LOGTAG,
    CCU_AF_SYNC_ALGO_LOGTAG,
    CCU_LTM_FLOW_LOGTAG,
    CCU_LTM_ALGO_LOGTAG,
    CCU_I2C_LOGTAG,
    CCU_RESERVE3_LOGTAG, //placeholder
    CCU_RESERVE2_LOGTAG, //placeholder
    CCU_RESERVE1_LOGTAG, //placeholder
} ccu_log_tag;

#endif
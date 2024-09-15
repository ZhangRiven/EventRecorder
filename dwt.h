/*
 * @Author: ZhangRiven
 * @Date: 2024-08-21 18:18:52
 * @LastEditors: ZhangRiven
 * @LastEditTime: 2024-08-21 18:23:18
 * @FilePath: \Core\dwt.h
 * @Version: v1.0
 * @Description:
 */

/* 使用说明:
 * 1.不适用于Cortex-M0/M0+内核,他们不具有DWT单元,测试平台:STM32F103HAL库
 * 2.首先使用DWT_Init(HAL_RCC_GetSysClockFreq());初始化外设
 * 3.如果你想使用DWT做us/ms级延时,使用DWT_Delay_us(us);或者DWT_Delay_ms(ms);
 * 4.如果你想用DWT做us级时间测量,使用DWT_MeasureBegin();开始测量,使用DWT_MeasureEnd();结束测量
 * 5.测量结束后,使用DWT_GetMeasure_us();获取测量结果(us)
 */
#ifndef __DWT_H__
#define __DWT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "main.h"

void DWT_Init(uint32_t freq);
void DWT_Delay_us(uint32_t time_us);
void DWT_Delay_ms(uint32_t time_ms);
uint32_t DWT_get_tick();
void DWT_MeasureBegin();
void DWT_MeasureEnd();
uint32_t DWT_GetMeasure_us();

#ifdef __cplusplus
}
#endif

#endif
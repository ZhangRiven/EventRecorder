/*
 * @Author: ZhangRiven
 * @Date: 2024-08-21 18:18:44
 * @LastEditors: ZhangRiven
 * @LastEditTime: 2024-08-21 18:58:15
 * @FilePath: \Core\dwt.c
 * @Version: v1.0
 * @Description:
 */
#include "DWT.h"

// 保存1us内的计数值
uint32_t us_period;
// 保存1ms内的计数值
uint32_t ms_period;
// 用于保存us级延时的数据
uint32_t delay_us_val_begin;
uint32_t delay_us_val_end;
// 用于保存ms级延时的数据
uint32_t delay_ms_val_begin;
uint32_t delay_ms_val_end;
// 用于保存测量值
uint32_t measure_val_begin;
uint32_t measure_val_end;


/**
 * @description: 用于初始化DWT外设
 * @param {uint32_t} freq 传入系统主频(Hz)
 * @return {*}
 */
void DWT_Init(uint32_t freq) {
  // 使能DWT外设,置DEMCR寄存器的TRCENA位为1
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  // 清空CYCCNT
  DWT->CYCCNT = 0;
  // 写DWTCR寄存器的CYCCNTTENA位为1,启动CYCCNT计数
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

  // 计算系统时钟周期,以算出1us和1ms里的DWT增加的值
  uint32_t sys_clk_freq = freq;
  us_period = sys_clk_freq * 0.000001;
  ms_period = sys_clk_freq * 0.001;
}


/**
 * @description: 使用DWT微秒级延时
 * @param {uint32_t} time_us 微秒数
 * @return {*}
 */
void DWT_Delay_us(uint32_t time_us) {
  delay_us_val_begin = DWT->CYCCNT;
  delay_us_val_end = delay_us_val_begin + (time_us * us_period);
  while (DWT->CYCCNT < delay_us_val_end) {
    __NOP();
  }
}

/**
 * @description: 使用DWT毫秒级延时
 * @param {uint32_t} time_ms 毫秒数
 * @return {*}
 */
void DWT_Delay_ms(uint32_t time_ms) {
  delay_ms_val_begin = DWT->CYCCNT;
  delay_ms_val_end = delay_ms_val_begin + (time_ms * ms_period);
  while (DWT->CYCCNT < delay_ms_val_end) {
  }
}

uint32_t DWT_get_tick() {
  return DWT->CYCCNT;
}

/**
 * @description: 开始DWT时间测量,注意测量时间不要让DWT->CYCCNT溢出
 * @return {*}
 */
inline void DWT_MeasureBegin() {
  measure_val_begin = DWT->CYCCNT;
}

/**
 * @description: DWT时间测量结束
 * @return {*}
 */
inline void DWT_MeasureEnd() {
  measure_val_end = DWT->CYCCNT;
}

/**
 * @description: 获取DWT时间测量的微秒值
 * @return {*}
 */
uint32_t DWT_GetMeasure_us() {
  // 处理发生边界溢出的情况
  if (measure_val_end <= measure_val_begin) {
    return ((0xFFFFFFFF - measure_val_begin) + measure_val_end) / us_period;
  }  // 正常情况
  else {
    return (measure_val_end - measure_val_begin) / us_period;
  }
}

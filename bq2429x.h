#ifndef BQ2429X_H
#define BQ2429X_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef int32_t (*bq2429x_write_ptr)(void *, uint8_t, const uint8_t *, uint16_t);
typedef int32_t (*bq2429x_read_ptr)(void *, uint8_t, uint8_t *, uint16_t);

typedef struct {
    bq2429x_write_ptr write_reg;
    bq2429x_read_ptr read_reg;
    void *handle;
    uint8_t is_init;
} bq2429x_ctx_t;

#define BQ2429X_I2C_ADD (0x6B << 1)

#define BQ2429X_INPUT_SRC_CTRL_REG 0x00
#define BQ2429X_CONFIG_REG         0x01
#define BQ2429X_ICHG_CTRL_REG      0x02
#define BQ2429x_PRECHG_CTRL_REG    0x03
#define BQ2429X_VREG_CTRL_REG      0x04
#define BQ2429X_TIMER_CTRL_REG     0x05
#define BQ2429x_BOOSTV_CTRL_REG    0x06
#define BQ2429x_MISC_CTRL_REG      0x07
#define BQ2429x_SYSTEM_STAT_REG    0x08
#define BQ2429x_FAULT_STAT_REG     0x09
#define BQ2429x_VENDOR_STAT_REG    0x0A

typedef struct {
    uint8_t iinlim : 3;
    uint8_t vindpm : 4;
    uint8_t en_hiz : 1;
} bq2429x_input_src_ctrl_t;

typedef struct {
    uint8_t boost_lim  : 1;
    uint8_t sys_min    : 3;
    uint8_t chg_config : 1;
    uint8_t otg_config : 1;
    uint8_t wdg_reset  : 1;
    uint8_t reg_reset  : 1;
} bq2429x_power_on_cfg_t;

typedef struct {
    uint8_t force_20pct : 1;
    uint8_t bcold       : 1;
    uint8_t ichg        : 6;
} bq2429x_chg_current_ctrl_t;

typedef struct {
    uint8_t iterm   : 4;
    uint8_t iprechg : 4;
} bq2429x_pre_chg_term_current_ctrl_t;

typedef struct {
    uint8_t vrechg  : 1;
    uint8_t batlowv : 1;
    uint8_t vreg    : 6;
} bq2429x_chg_voltage_ctrl_t;

typedef struct {
    uint8_t           : 1;
    uint8_t chg_timer : 2;
    uint8_t en_timer  : 1;
    uint8_t watchdog  : 2;
    uint8_t           : 1;
    uint8_t en_term   : 1;
} bq2429x_chg_term_timer_ctrl_t;

typedef struct {
    uint8_t treg   : 2;
    uint8_t bhot   : 2;
    uint8_t boostv : 4;
} bq2429x_boostv_thermal_ctrl_t;

typedef struct {
    uint8_t int_mask0      : 1;
    uint8_t int_mask1      : 1;
    uint8_t res            : 3;
    uint8_t batfet_disable : 1;
    uint8_t tmr2x_en       : 1;
    uint8_t iindet_en      : 1;
} bq2429x_misc_ctrl_t;

typedef struct {
    uint8_t vsys_stat  : 1;
    uint8_t therm_stat : 1;
    uint8_t pg_stat    : 1;
    uint8_t dpm_stat   : 1;
    uint8_t chrg_stat  : 2;
    uint8_t vbus_stat  : 2;
} bq2429x_sys_stat_t;

typedef struct {
    uint8_t ntc_fault  : 2;
    uint8_t            : 1;
    uint8_t bat_fault  : 1;
    uint8_t chrg_fault : 2;
    uint8_t otg_fault  : 1;
    uint8_t wdg_fault  : 1;
} bq2429x_fault_stat_t;

typedef struct {
    uint8_t rev         : 3;
    uint8_t             : 2;
    uint8_t part_number : 3;
} bq2429x_vendor_stat_t;

typedef enum
{
    BQ24296 = 1,
    BQ24297 = 3,
} bq2429x_part_number_t;

int32_t bq2429x_input_voltage_limit_set(bq2429x_ctx_t *ctx, uint8_t val);
int32_t bq2429x_input_current_limit_set(bq2429x_ctx_t *ctx, uint8_t val);
int32_t bq2429x_charge_enable(bq2429x_ctx_t *ctx, bool val);
int32_t bq2429x_watchdog_reset(bq2429x_ctx_t *ctx);
int32_t bq2429x_minimum_system_voltage_set(bq2429x_ctx_t *ctx, uint8_t val);
int32_t bq2429x_boost_current_limit_set(bq2429x_ctx_t *ctx, uint8_t val);
int32_t bq2429x_charge_current_set(bq2429x_ctx_t *ctx, uint8_t val);
int32_t bq2429X_precharge_current_set(bq2429x_ctx_t *ctx, uint8_t val);
int32_t bq2429x_termination_current_set(bq2429x_ctx_t *ctx, uint8_t val);
int32_t bq2429x_charge_voltage_set(bq2429x_ctx_t *ctx, uint8_t val);
int32_t bq2429x_batt_low_threshold_set(bq2429x_ctx_t *ctx, uint8_t val);
int32_t bq2429x_recharge_voltage_set(bq2429x_ctx_t *ctx, uint8_t val);
int32_t bq2429x_termination_enable(bq2429x_ctx_t *ctx, bool val);
int32_t bq2429x_watchdog_timer_set(bq2429x_ctx_t *ctx, uint8_t val);
int32_t bq2429x_safety_timer_enable(bq2429x_ctx_t *ctx, bool val);
int32_t bq2429x_charge_timer_set(bq2429x_ctx_t *ctx, uint8_t val);
int32_t bq2429x_boost_voltage_set(bq2429x_ctx_t *ctx, uint8_t val);
int32_t bq2429x_boost_temp_monitor_set(bq2429x_ctx_t *ctx, uint8_t val);
int32_t bq2429x_thermal_regulation_threshold_set(bq2429x_ctx_t *ctx, uint8_t val);
int32_t bq2429x_batt_fault_interrupt_enable(bq2429x_ctx_t *ctx, uint8_t val);
int32_t bq2429x_chg_fault_interrupt_enable(bq2429x_ctx_t *ctx, uint8_t val);

int32_t bq2429x_system_status_get(bq2429x_ctx_t *ctx, bq2429x_sys_stat_t *sys_stat);
int32_t bq2429x_fault_status_get(bq2429x_ctx_t *ctx, bq2429x_fault_stat_t *fault_stat);
int32_t bq2429x_part_number_get(bq2429x_ctx_t *ctx, bq2429x_part_number_t *pn);

#ifdef __cplusplus
}
#endif

#endif /* BQ2429X_H */
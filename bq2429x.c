#include "bq2429x.h"

static int32_t bq2429x_read_reg(bq2429x_ctx_t *ctx, uint8_t reg, uint8_t *data, uint16_t len)
{
    int32_t ret;
    ret = ctx->read_reg(ctx->handle, reg, data, len);
    return ret;
}

static int32_t bq2429x_write_reg(bq2429x_ctx_t *ctx, uint8_t reg, const uint8_t *data, uint16_t len)
{
    int32_t ret;
    ret = ctx->write_reg(ctx->handle, reg, data, len);
    return ret;
}

/**
 * @brief DPM Input Voltage Limit Set.
 *
 * @param ctx Pointer to device handle
 * @param val Voltage Limit(mV) = 3880mV + (val * 80mV)
 * @return int32_t (-1) on error, (0) otherwise.
 */
int32_t bq2429x_input_voltage_limit_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_input_src_ctrl_t input_src_ctrl = {0};
    int32_t ret;

    ret = bq2429x_read_reg(ctx, BQ2429X_INPUT_SRC_CTRL_REG, (uint8_t *)&input_src_ctrl, 1);
    if (ret == 0)
    {
        input_src_ctrl.vindpm = val;
        return bq2429x_write_reg(ctx, BQ2429X_INPUT_SRC_CTRL_REG, (uint8_t *)&input_src_ctrl, 1);
    }
    return ret;
}

/**
 * @brief DPM Input Current Limit Set.
 *
 * @param ctx Pointer to device handle
 * @param val Current Limit = 000 – 100 mA, 001 – 150 mA,
 *                            010 – 500 mA, 011 – 900 mA,
 *                            100 – 1 A,    101 – 1.5 A,
 *                            110 – 2 A,    111 – 3A
 *
 * @return int32_t (-1) on error, (0) otherwise.
 */
int32_t bq2429x_input_current_limit_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_input_src_ctrl_t input_src_ctrl = {0};
    int32_t ret;

    ret = bq2429x_read_reg(ctx, BQ2429X_INPUT_SRC_CTRL_REG, (uint8_t *)&input_src_ctrl, 1);
    if (ret == 0)
    {
        input_src_ctrl.iinlim = val;
        return bq2429x_write_reg(ctx, BQ2429X_INPUT_SRC_CTRL_REG, (uint8_t *)&input_src_ctrl, 1);
    }
    return ret;
}

/**
 * @brief Charge Enable.
 *
 * @param ctx Pointer to device handle.
 * @param val true = enable, false = disable
 * @return int32_t (-1) on error, (0) otherwise.
 */
int32_t bq2429x_charge_enable(bq2429x_ctx_t *ctx, bool val)
{
    bq2429x_power_on_cfg_t power_on_cfg = {0};
    int32_t ret;

    ret = bq2429x_read_reg(ctx, BQ2429X_CONFIG_REG, (uint8_t *)&power_on_cfg, 1);
    if (ret == 0)
    {
        power_on_cfg.chg_config = val;
        return bq2429x_write_reg(ctx, BQ2429X_CONFIG_REG, (uint8_t *)&power_on_cfg, 1);
    }
    return ret;
}

/**
 * @brief Reset Watchdog Timer.
 *
 * @param ctx Pointer to device handle.
 * @return int32_t (-1) on error, (0) otherwise.
 */
int32_t bq2429x_watchdog_reset(bq2429x_ctx_t *ctx)
{
    bq2429x_power_on_cfg_t power_on_cfg = {0};
    int32_t ret;

    ret = bq2429x_read_reg(ctx, BQ2429X_CONFIG_REG, (uint8_t *)&power_on_cfg, 1);
    if (ret == 0)
    {
        power_on_cfg.wdg_reset = 1;
        return bq2429x_write_reg(ctx, BQ2429X_CONFIG_REG, (uint8_t *)&power_on_cfg, 1);
    }
    return ret;
}

/**
 * @brief Minimum System Voltage Set.
 *
 * @param ctx Pointer to device handle.
 * @param val VSYS_Min(mV) = 3000mV + (val * 100mV)
 * @return int32_t (-1) on error, (0) otherwise.
 */
int32_t bq2429x_minimum_system_voltage_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_power_on_cfg_t power_on_cfg = {0};
    int32_t ret;

    ret = bq2429x_read_reg(ctx, BQ2429X_CONFIG_REG, (uint8_t *)&power_on_cfg, 1);
    if (ret == 0)
    {
        power_on_cfg.sys_min = val;
        return bq2429x_write_reg(ctx, BQ2429X_CONFIG_REG, (uint8_t *)&power_on_cfg, 1);
    }
    return ret;
}

/**
 * @brief Boost Current Limit Set.
 *
 * @param ctx Pointer to device handle.
 * @param val 0 = 1A, 1 = 1.5A
 * @return int32_t (-1) on error, (0) otherwise.
 */
int32_t bq2429x_boost_current_limit_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_power_on_cfg_t power_on_cfg = {0};
    int32_t ret;

    ret = bq2429x_read_reg(ctx, BQ2429X_CONFIG_REG, (uint8_t *)&power_on_cfg, 1);
    if (ret == 0)
    {
        power_on_cfg.boost_lim = val;
        return bq2429x_write_reg(ctx, BQ2429X_CONFIG_REG, (uint8_t *)&power_on_cfg, 1);
    }
    return ret;
}

/**
 * @brief Charge Current Set.
 *
 * @param ctx Pointer to device handle.
 * @param val ICharge(mA) = 512mA + (val * 64mA)
 * @return int32_t (-1) on error, (0) otherwise.
 */
int32_t bq2429x_charge_current_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_chg_current_ctrl_t chg_current_ctrl = {0};
    int ret;
    ret = bq2429x_read_reg(ctx, BQ2429X_ICHG_CTRL_REG, (uint8_t *)&chg_current_ctrl, 1);
    if (ret == 0)
    {
        chg_current_ctrl.ichg = val;
        return bq2429x_write_reg(ctx, BQ2429X_ICHG_CTRL_REG, (uint8_t *)&chg_current_ctrl, 1);
    }
    return ret;
}

/**
 * @brief Precharge Current Set.
 *
 * @param ctx Pointer to device handle.
 * @param val IPreCharge(mA) = 128mA + (val * 128mA)
 * @return int32_t (-1) on error, (0) otherwise.
 */
int32_t bq2429X_precharge_current_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_pre_chg_term_current_ctrl_t pre_chg_term_current = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429x_PRECHG_CTRL_REG, (uint8_t *)&pre_chg_term_current, 1);
    if (ret == 0)
    {
        pre_chg_term_current.iprechg = val;
        return bq2429x_write_reg(ctx, BQ2429x_PRECHG_CTRL_REG, (uint8_t *)&pre_chg_term_current, 1);
    }
    return ret;
}

/**
 * @brief Termination Current Set.
 *
 * @param ctx Pointer to device handle.
 * @param val ITermination(mA) = 128mA + (val * 128mA)
 * @return int32_t (-1) on error, (0) otherwise.
 */
int32_t bq2429x_termination_current_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_pre_chg_term_current_ctrl_t pre_chg_term_current = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429x_PRECHG_CTRL_REG, (uint8_t *)&pre_chg_term_current, 1);
    if (ret == 0)
    {
        pre_chg_term_current.iterm = val;
        return bq2429x_write_reg(ctx, BQ2429x_PRECHG_CTRL_REG, (uint8_t *)&pre_chg_term_current, 1);
    }
    return ret;
}

/**
 * @brief Charge Voltage Set.
 *
 * @param ctx Pointer to device handle.
 * @param val VREG(mV) = 3504mV + (val * 16mV)
 * @return int32_t (-1) on error, (0) otherwise.
 */
int32_t bq2429x_charge_voltage_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_chg_voltage_ctrl_t chg_voltage_ctrl = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429X_VREG_CTRL_REG, (uint8_t *)&chg_voltage_ctrl, 1);
    if (ret == 0)
    {
        chg_voltage_ctrl.vreg = val;
        return bq2429x_write_reg(ctx, BQ2429X_VREG_CTRL_REG, (uint8_t *)&chg_voltage_ctrl, 1);
    }
    return ret;
}

/**
 * @brief Battery low threshold set.
 *
 * @param ctx Pointer to device handle.
 * @param val 0: 2.8V, 1: 3.0V
 * @return int32_t (-1) on error, (0) otherwise.
 */
int32_t bq2429x_batt_low_threshold_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_chg_voltage_ctrl_t chg_voltage_ctrl = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429X_VREG_CTRL_REG, (uint8_t *)&chg_voltage_ctrl, 1);
    if (ret == 0)
    {
        chg_voltage_ctrl.batlowv = val;
        return bq2429x_write_reg(ctx, BQ2429X_VREG_CTRL_REG, (uint8_t *)&chg_voltage_ctrl, 1);
    }
    return ret;
}

/**
 * @brief Recharge Threshold Set.
 *
 * @param ctx Pointer to device handle.
 * @param val 0: 100mV, 1: 300mV
 * @return int32_t (-1) on error, (0) otherwise.
 */
int32_t bq2429x_recharge_voltage_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_chg_voltage_ctrl_t chg_voltage_ctrl = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429X_VREG_CTRL_REG, (uint8_t *)&chg_voltage_ctrl, 1);
    if (ret == 0)
    {
        chg_voltage_ctrl.vrechg = val;
        return bq2429x_write_reg(ctx, BQ2429X_VREG_CTRL_REG, (uint8_t *)&chg_voltage_ctrl, 1);
    }
    return ret;
}

/**
 * @brief Enable Battery Termination.
 *
 * @param ctx Pointer to device handle.
 * @param val true = enable, false = disable
 * @return int32_t (-1) on error, (0) otherwise.
 */
int32_t bq2429x_termination_enable(bq2429x_ctx_t *ctx, bool val)
{
    bq2429x_chg_term_timer_ctrl_t chg_term_timer_ctrl = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429X_TIMER_CTRL_REG, (uint8_t *)&chg_term_timer_ctrl, 1);
    if (ret == 0)
    {
        chg_term_timer_ctrl.en_term = val;
        return bq2429x_write_reg(ctx, BQ2429X_TIMER_CTRL_REG, (uint8_t *)&chg_term_timer_ctrl, 1);
    }
    return ret;
}

/**
 * @brief Watchdog Timer Period Set
 *
 * @param ctx Pointer to device handle.
 * @param val 00 – Disable timer, 01 – 40 s, 10 – 80 s, 11 – 160 s
 * @return int32_t (-1) on error, (0) otherwise.
 */
int32_t bq2429x_watchdog_timer_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_chg_term_timer_ctrl_t chg_term_timer_ctrl = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429X_TIMER_CTRL_REG, (uint8_t *)&chg_term_timer_ctrl, 1);
    if (ret == 0)
    {
        chg_term_timer_ctrl.watchdog = val;
        return bq2429x_write_reg(ctx, BQ2429X_TIMER_CTRL_REG, (uint8_t *)&chg_term_timer_ctrl, 1);
    }
    return ret;
}

/**
 * @brief Enable Safety Timer.
 *
 * @param ctx Pointer to device handle.
 * @param val true = enable, false = disable
 * @return int32_t (-1) on error, (0) otherwise.
 */
int32_t bq2429x_safety_timer_enable(bq2429x_ctx_t *ctx, bool val)
{
    bq2429x_chg_term_timer_ctrl_t chg_term_timer_ctrl = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429X_TIMER_CTRL_REG, (uint8_t *)&chg_term_timer_ctrl, 1);
    if (ret == 0)
    {
        chg_term_timer_ctrl.en_timer = val;
        return bq2429x_write_reg(ctx, BQ2429X_TIMER_CTRL_REG, (uint8_t *)&chg_term_timer_ctrl, 1);
    }
    return ret;
}

/**
 * @brief Safety Timer Period Set
 *
 * @param ctx Pointer to device handle.
 * @param val 00 – 5 hrs, 01 – 8 hrs, 10 – 12 hrs, 11 – 20 hrs
 * @return int32_t (-1) on error, (0) otherwise.
 */
int32_t bq2429x_charge_timer_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_chg_term_timer_ctrl_t chg_term_timer_ctrl = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429X_TIMER_CTRL_REG, (uint8_t *)&chg_term_timer_ctrl, 1);
    if (ret == 0)
    {
        chg_term_timer_ctrl.chg_timer = val;
        return bq2429x_write_reg(ctx, BQ2429X_TIMER_CTRL_REG, (uint8_t *)&chg_term_timer_ctrl, 1);
    }
    return ret;
}

/**
 * @brief Boost Voltage Set.
 *
 * @param ctx Pointer to device handle.
 * @param val Vboost(mV) = 4550mV + (val * 64mV)
 * @return int32_t (-1) on error, (0) otherwise.
 */
int32_t bq2429x_boost_voltage_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_boostv_thermal_ctrl_t boostv_thermal_ctrl = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429x_BOOSTV_CTRL_REG, (uint8_t *)&boostv_thermal_ctrl, 1);
    if (ret == 0)
    {
        boostv_thermal_ctrl.boostv = val;
        return bq2429x_write_reg(ctx, BQ2429x_BOOSTV_CTRL_REG, (uint8_t *)&boostv_thermal_ctrl, 1);
    }
    return ret;
}

/**
 * @brief Boost Temperature Monitor Set.
 *
 * @param ctx Pointer to device handle.
 * @param val 00 – Vbhot1 (33% of REGN or 55°C w/ 103AT thermistor)
              01 – Vbhot0 (36% of REGN or 60°C w/ 103AT thermistor)
              10 – Vbhot2 (30% of REGN or 65°C w/ 103AT thermistor)
              11 – Disable boost mode thermal protection
 * @return int32_t (-1) on error, (0) otherwise.
 */
int32_t bq2429x_boost_temp_monitor_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_boostv_thermal_ctrl_t boostv_thermal_ctrl = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429x_BOOSTV_CTRL_REG, (uint8_t *)&boostv_thermal_ctrl, 1);
    if (ret == 0)
    {
        boostv_thermal_ctrl.bhot = val;
        return bq2429x_write_reg(ctx, BQ2429x_BOOSTV_CTRL_REG, (uint8_t *)&boostv_thermal_ctrl, 1);
    }
    return ret;
}

/**
 * @brief Thermal Regulation Threshold Set.
 *
 * @param ctx Pointer to device handle.
 * @param val 00 – 60°C, 01 – 80°C, 10 – 100°C, 11 – 120°C
 * @return int32_t (-1) on error, (0) otherwise.
 */
int32_t bq2429x_thermal_regulation_threshold_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_boostv_thermal_ctrl_t boostv_thermal_ctrl = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429x_BOOSTV_CTRL_REG, (uint8_t *)&boostv_thermal_ctrl, 1);
    if (ret == 0)
    {
        boostv_thermal_ctrl.treg = val;
        return bq2429x_write_reg(ctx, BQ2429x_BOOSTV_CTRL_REG, (uint8_t *)&boostv_thermal_ctrl, 1);
    }
    return ret;
}

/**
 * @brief Enable Interrupt on Battery Fault.
 *
 * @param ctx Pointer to device handle.
 * @param val true = enable, false = disable
 * @return int32_t (-1) on error, (0) otherwise.
 */
int32_t bq2429x_batt_fault_interrupt_enable(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_misc_ctrl_t misc_ctrl = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429x_MISC_CTRL_REG, (uint8_t *)&misc_ctrl, 1);
    if (ret == 0)
    {
        misc_ctrl.int_mask0 = val;
        return bq2429x_write_reg(ctx, BQ2429x_MISC_CTRL_REG, (uint8_t *)&misc_ctrl, 1);
    }
    return ret;
}

/**
 * @brief Enable Interrupt on Charge Fault.
 *
 * @param ctx Pointer to device handle.
 * @param val true = enable, false = disable
 * @return int32_t (-1) on error, (0) otherwise.
 */
int32_t bq2429x_chg_fault_interrupt_enable(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_misc_ctrl_t misc_ctrl = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429x_MISC_CTRL_REG, (uint8_t *)&misc_ctrl, 1);
    if (ret == 0)
    {
        misc_ctrl.int_mask1 = val;
        return bq2429x_write_reg(ctx, BQ2429x_MISC_CTRL_REG, (uint8_t *)&misc_ctrl, 1);
    }
    return ret;
}

/**
 * @brief Read System Status Register.
 *
 * @param ctx Pointer to device handle.
 * @param sys_stat Pointer to system status value.
 * @return int32_t (-1) on error, (0) otherwise.
 */
int32_t bq2429x_system_status_get(bq2429x_ctx_t *ctx, bq2429x_sys_stat_t *sys_stat)
{
    return bq2429x_read_reg(ctx, BQ2429x_SYSTEM_STAT_REG, (uint8_t *)sys_stat, 1);
}

/**
 * @brief Read Fault Status Register.
 *
 * @param ctx Pointer to device handle.
 * @param sys_stat Pointer to fault status value.
 * @return int32_t (-1) on error, (0) otherwise.
 */
int32_t bq2429x_fault_status_get(bq2429x_ctx_t *ctx, bq2429x_fault_stat_t *fault_stat)
{
    return bq2429x_read_reg(ctx, BQ2429x_FAULT_STAT_REG, (uint8_t *)fault_stat, 1);
}

/**
 * @brief Read IC Part Number
 *
 * @param ctx Pointer to device handle.
 * @param pn 001 - (bq24296)
             011 - (bq24297)
 * @return int32_t (-1) on error, (0) otherwise.
 */
int32_t bq2429x_part_number_get(bq2429x_ctx_t *ctx, bq2429x_part_number_t *pn)
{
    bq2429x_vendor_stat_t vendor_stat = {0};
    int ret;
    ret = bq2429x_read_reg(ctx, BQ2429x_VENDOR_STAT_REG, (uint8_t *)&vendor_stat, 1);
    *pn = vendor_stat.part_number;
    return ret;
}
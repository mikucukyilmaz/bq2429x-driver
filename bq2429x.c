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

int32_t bq2429x_input_voltage_limit_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_input_src_ctrl_t input_src_ctrl = {0};
    int32_t ret;

    ret = bq2429x_read_reg(ctx, BQ2429X_INPUT_SRC_CTRL_REG, (uint8_t *)&input_src_ctrl, 1);
    if (ret == 0)
    {
        input_src_ctrl.vindpm = val;
        ret = bq2429x_write_reg(ctx, BQ2429X_INPUT_SRC_CTRL_REG, (uint8_t *)&input_src_ctrl, 1);
    }
    return ret;
}

int32_t bq2429x_input_current_limit_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_input_src_ctrl_t input_src_ctrl = {0};
    int32_t ret;

    ret = bq2429x_read_reg(ctx, BQ2429X_INPUT_SRC_CTRL_REG, (uint8_t *)&input_src_ctrl, 1);
    if (ret == 0)
    {
        input_src_ctrl.iinlim = val;
        ret = bq2429x_write_reg(ctx, BQ2429X_INPUT_SRC_CTRL_REG, (uint8_t *)&input_src_ctrl, 1);
    }
    return ret;
}

int32_t bq2429x_charge_enable(bq2429x_ctx_t *ctx, bool val)
{
    bq2429x_power_on_cfg_t power_on_cfg = {0};
    int32_t ret;

    ret = bq2429x_read_reg(ctx, BQ2429X_CONFIG_REG, (uint8_t *)&power_on_cfg, 1);
    if (ret == 0)
    {
        power_on_cfg.chg_config = val;
        ret = bq2429x_write_reg(ctx, BQ2429X_CONFIG_REG, (uint8_t *)&power_on_cfg, 1);
    }
    return ret;
}

int32_t bq2429x_minimum_system_voltage_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_power_on_cfg_t power_on_cfg = {0};
    int32_t ret;

    ret = bq2429x_read_reg(ctx, BQ2429X_CONFIG_REG, (uint8_t *)&power_on_cfg, 1);
    if (ret == 0)
    {
        power_on_cfg.sys_min = val;
        ret = bq2429x_write_reg(ctx, BQ2429X_CONFIG_REG, (uint8_t *)&power_on_cfg, 1);
    }
    return ret;
}

int32_t bq2429x_boost_current_limit_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_power_on_cfg_t power_on_cfg = {0};
    int32_t ret;

    ret = bq2429x_read_reg(ctx, BQ2429X_CONFIG_REG, (uint8_t *)&power_on_cfg, 1);
    if (ret == 0)
    {
        power_on_cfg.boost_lim = val;
        ret = bq2429x_write_reg(ctx, BQ2429X_CONFIG_REG, (uint8_t *)&power_on_cfg, 1);
    }
    return ret;
}

int32_t bq2429x_charge_current_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_chg_current_ctrl_t chg_current_ctrl = {0};
    int ret;
    ret = bq2429x_read_reg(ctx, BQ2429X_ICHG_CTRL_REG, (uint8_t *)&chg_current_ctrl, 1);
    if (ret == 0)
    {
        chg_current_ctrl.ichg = val;
        ret = bq2429x_write_reg(ctx, BQ2429X_ICHG_CTRL_REG, (uint8_t *)&chg_current_ctrl, 1);
    }
    return ret;
}

int32_t bq2429X_precharge_current_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_pre_chg_term_current_ctrl_t pre_chg_term_current = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429x_PRECHG_CTRL_REG, (uint8_t *)&pre_chg_term_current, 1);
    if (ret == 0)
    {
        pre_chg_term_current.iprechg = val;
        ret = bq2429x_write_reg(ctx, BQ2429x_PRECHG_CTRL_REG, (uint8_t *)&pre_chg_term_current, 1);
    }
    return ret;
}

int32_t bq2429x_termination_current_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_pre_chg_term_current_ctrl_t pre_chg_term_current = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429x_PRECHG_CTRL_REG, (uint8_t *)&pre_chg_term_current, 1);
    if (ret == 0)
    {
        pre_chg_term_current.iterm = val;
        ret = bq2429x_write_reg(ctx, BQ2429x_PRECHG_CTRL_REG, (uint8_t *)&pre_chg_term_current, 1);
    }
    return ret;
}

int32_t bq2429x_charge_voltage_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_chg_voltage_ctrl_t chg_voltage_ctrl = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429X_VREG_CTRL_REG, (uint8_t *)&chg_voltage_ctrl, 1);
    if (ret == 0)
    {
        chg_voltage_ctrl.vreg = val;
        ret = bq2429x_write_reg(ctx, BQ2429X_VREG_CTRL_REG, (uint8_t *)&chg_voltage_ctrl, 1);
    }
    return ret;
}

int32_t bq2429x_batt_low_threshold_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_chg_voltage_ctrl_t chg_voltage_ctrl = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429X_VREG_CTRL_REG, (uint8_t *)&chg_voltage_ctrl, 1);
    if (ret == 0)
    {
        chg_voltage_ctrl.batlowv = val;
        ret = bq2429x_write_reg(ctx, BQ2429X_VREG_CTRL_REG, (uint8_t *)&chg_voltage_ctrl, 1);
    }
    return ret;
}

int32_t bq2429x_termination_enable(bq2429x_ctx_t *ctx, bool val)
{
    bq2429x_chg_term_timer_ctrl_t chg_term_timer_ctrl = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429X_TIMER_CTRL_REG, (uint8_t *)&chg_term_timer_ctrl, 1);
    if (ret == 0)
    {
        chg_term_timer_ctrl.en_term = val;
        ret = bq2429x_write_reg(ctx, BQ2429X_TIMER_CTRL_REG, (uint8_t *)&chg_term_timer_ctrl, 1);
    }
    return ret;
}

int32_t bq2429x_watchdog_timer_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_chg_term_timer_ctrl_t chg_term_timer_ctrl = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429X_TIMER_CTRL_REG, (uint8_t *)&chg_term_timer_ctrl, 1);
    if (ret == 0)
    {
        chg_term_timer_ctrl.watchdog = val;

        ret = bq2429x_write_reg(ctx, BQ2429X_TIMER_CTRL_REG, (uint8_t *)&chg_term_timer_ctrl, 1);
    }
    return ret;
}

int32_t bq2429x_safety_timer_enable(bq2429x_ctx_t *ctx, bool val)
{
    bq2429x_chg_term_timer_ctrl_t chg_term_timer_ctrl = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429X_TIMER_CTRL_REG, (uint8_t *)&chg_term_timer_ctrl, 1);
    if (ret == 0)
    {
        chg_term_timer_ctrl.en_timer = val;

        ret = bq2429x_write_reg(ctx, BQ2429X_TIMER_CTRL_REG, (uint8_t *)&chg_term_timer_ctrl, 1);
    }
    return ret;
}

int32_t bq2429x_charge_timer_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_chg_term_timer_ctrl_t chg_term_timer_ctrl = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429X_TIMER_CTRL_REG, (uint8_t *)&chg_term_timer_ctrl, 1);
    if (ret == 0)
    {
        chg_term_timer_ctrl.chg_timer = val;

        ret = bq2429x_write_reg(ctx, BQ2429X_TIMER_CTRL_REG, (uint8_t *)&chg_term_timer_ctrl, 1);
    }
    return ret;
}

int32_t bq2429x_boost_voltage_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_boostv_thermal_ctrl_t boostv_thermal_ctrl = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429x_BOOSTV_CTRL_REG, (uint8_t *)&boostv_thermal_ctrl, 1);
    if (ret == 0)
    {
        boostv_thermal_ctrl.boostv = val;

        ret = bq2429x_write_reg(ctx, BQ2429x_BOOSTV_CTRL_REG, (uint8_t *)&boostv_thermal_ctrl, 1);
    }
    return ret;
}

int32_t bq2429x_boost_temp_monitor_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_boostv_thermal_ctrl_t boostv_thermal_ctrl = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429x_BOOSTV_CTRL_REG, (uint8_t *)&boostv_thermal_ctrl, 1);
    if (ret == 0)
    {
        boostv_thermal_ctrl.bhot = val;

        ret = bq2429x_write_reg(ctx, BQ2429x_BOOSTV_CTRL_REG, (uint8_t *)&boostv_thermal_ctrl, 1);
    }
    return ret;
}

int32_t bq2429x_thermal_regulation_threshold_set(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_boostv_thermal_ctrl_t boostv_thermal_ctrl = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429x_BOOSTV_CTRL_REG, (uint8_t *)&boostv_thermal_ctrl, 1);
    if (ret == 0)
    {
        boostv_thermal_ctrl.treg = val;

        ret = bq2429x_write_reg(ctx, BQ2429x_BOOSTV_CTRL_REG, (uint8_t *)&boostv_thermal_ctrl, 1);
    }
    return ret;
}

int32_t bq2429x_batt_fault_interrupt_enable(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_misc_ctrl_t misc_ctrl = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429x_MISC_CTRL_REG, (uint8_t *)&misc_ctrl, 1);
    if (ret == 0)
    {
        misc_ctrl.int_mask0 = val;
        ret = bq2429x_write_reg(ctx, BQ2429x_MISC_CTRL_REG, (uint8_t *)&misc_ctrl, 1);
    }
    return ret;
}

int32_t bq2429x_chg_fault_interrupt_enable(bq2429x_ctx_t *ctx, uint8_t val)
{
    bq2429x_misc_ctrl_t misc_ctrl = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429x_MISC_CTRL_REG, (uint8_t *)&misc_ctrl, 1);
    if (ret == 0)
    {
        misc_ctrl.int_mask1 = val;
        ret = bq2429x_write_reg(ctx, BQ2429x_MISC_CTRL_REG, (uint8_t *)&misc_ctrl, 1);
    }
    return ret;
}

int32_t bq2429x_system_status_get(bq2429x_ctx_t *ctx, bq2429x_sys_stat_t *sys_stat)
{
    int ret;
    ret = bq2429x_read_reg(ctx, BQ2429x_SYSTEM_STAT_REG, (uint8_t *)sys_stat, 1);
    return ret;
}

int32_t bq2429x_fault_status_get(bq2429x_ctx_t *ctx, bq2429x_fault_stat_t *fault_stat)
{
    int ret;
    ret = bq2429x_read_reg(ctx, BQ2429x_FAULT_STAT_REG, (uint8_t *)fault_stat, 1);
    return ret;
}

int32_t bq2429x_part_number_get(bq2429x_ctx_t *ctx, bq2429x_part_number_t *pn)
{
    bq2429x_vendor_stat_t vendor_stat = {0};
    int ret;

    ret = bq2429x_read_reg(ctx, BQ2429x_VENDOR_STAT_REG, (uint8_t *)&vendor_stat, 1);
    *pn = vendor_stat.part_number;
    return ret;
}
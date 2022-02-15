# bq2429x-driver
BQ2429x I2C Controlled Charger Driver.

## Usage
Create prototype read/write functions,

```
static int32_t i2c_write(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len)
{
    HAL_I2C_Mem_Write(handle, BQ2429X_I2C_ADD, reg, I2C_MEMADD_SIZE_8BIT, (uint8_t *)bufp, len, 1000);
    return 0;
}

static int32_t i2c_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
{
    HAL_I2C_Mem_Read(handle, BQ2429X_I2C_ADD, reg, I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);
    return 0;
}
```

Configure the device,

```
bq2429x_ctx.handle    = &hi2c1;
bq2429x_ctx.read_reg  = i2c_read;
bq2429x_ctx.write_reg = i2c_write;
bq2429x_part_number_t part_number;
bq2429x_part_number_get(&bq2429x_ctx, &part_number);
if (part_number == BQ24296 || part_number == BQ24297)
{
    bq2429x_input_voltage_limit_set(&bq2429x_ctx, 8);
    bq2429x_input_current_limit_set(&bq2429x_ctx, 7);
    bq2429x_charge_enable(&bq2429x_ctx, true);
    bq2429x_minimum_system_voltage_set(&bq2429x_ctx, 0);
    bq2429x_boost_current_limit_set(&bq2429x_ctx, 1);
    bq2429x_charge_current_set(&bq2429x_ctx, 39);
    bq2429X_precharge_current_set(&bq2429x_ctx, 7);
    bq2429x_termination_current_set(&bq2429x_ctx, 1);
    bq2429x_charge_voltage_set(&bq2429x_ctx, 44);
    bq2429x_batt_low_threshold_set(&bq2429x_ctx, 0);
    bq2429x_termination_enable(&bq2429x_ctx, true);
    bq2429x_watchdog_timer_set(&bq2429x_ctx, 3);
    bq2429x_safety_timer_enable(&bq2429x_ctx, true);
    bq2429x_charge_timer_set(&bq2429x_ctx, 3);
    bq2429x_boost_voltage_set(&bq2429x_ctx, 0);
    bq2429x_boost_temp_monitor_set(&bq2429x_ctx, 3);
    bq2429x_thermal_regulation_threshold_set(&bq2429x_ctx, 3);
    SEGGER_RTT_printf(0, "Charger[%d] Init Completed.", part_number);
}
```


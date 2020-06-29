#define _MPU9250_DRV_C_SRC

//-------------------------MODULES USED-------------------------------------



//-------------------------DEFINITIONS AND MACORS---------------------------



//-------------------------TYPEDEFS AND STRUCTURES--------------------------



//-------------------------PROTOTYPES OF LOCAL FUNCTIONS--------------------



//-------------------------EXPORTED VARIABLES ------------------------------



//-------------------------GLOBAL VARIABLES---------------------------------



//-------------------------EXPORTED FUNCTIONS-------------------------------
int32_t mpu9250_drv_who_am_i(uint8_t * p_whoami)
{
    return MPU9250_OK;
}

int32_t mpu9250_drv_set_sample_rate(uint32_t sample_rate_hz)
{
    return MPU9250_OK;
}

int32_t mpu9250_drv_set_fifo_mode(fifo_mode_e mode)
{
    return MPU9250_OK;
}

int32_t mpu9250_drv_set_ext_sync_location(ext_sync_e location)
{

    return MPU9250_OK;
}

int32_t mpu9250_drv_enable_gdlpf(bool dlpf_en)
{

    return MPU9250_OK;
}

int32_t mpu9250_drv_cfg_gyro_dlpf(uint8_t dlpf_cfg)
{

    return MPU9250_OK;
}

int32_t mpu9250_drv_set_gyro_offset(int16_t x_offs, int16_t y_offs, int16_t z_offs)
{

    return MPU9250_OK;
}

int32_t mpu9250_drv_set_gyro_fs_sel(gyro_fs_e full_scale_dps)
{

    return MPU9250_OK;
}

int32_t mpu9250_drv_enable_gyro_self_test(bool x_self, bool y_self, bool z_self)
{

    return MPU9250_OK;
}

int32_t mpu9250_drv_enable_fifo_gyro(bool fifo_x_en, bool fifo_y_en, bool fifo_z_en)
{

    return MPU9250_OK;
}

int32_t mpu9250_drv_set_accel_fs_sel(accel_fs_e full_scale_g)
{

    return MPU9250_OK;
}

int32_t mpu9250_drv_enable_accel_self_test(bool x_self, bool y_self, bool z_self)
{

    return MPU9250_OK;
}

int32_t mpu9250_drv_enable_accel_dlpf(bool dlpf_en)
{

    return MPU9250_OK;
}

int32_t mpu9250_drv_cfg_accel_dlpf(uint8_t dlpf_cfg)
{

    return MPU9250_OK;
}

int32_t mpu9250_drv_enable_fifo_accel(bool fifo_en)
{

    return MPU9250_OK;
}


int32_t mpu9250_drv_enable_fifo_temp(bool fifo_en)
{

    return MPU9250_OK;
}

int32_t mpu9250_drv_set_lowpower_clk(lowpwr_clk_e freq)
{

    return MPU9250_OK;
}

int32_t mpu9250_drv_set_wake_on_motion_thrsh(uint8_t thrsh)
{

    return MPU9250_OK;
}

int32_t mpu9250_drv_enable_wake_on_motion_int(bool wom_en)
{

    return MPU9250_OK;
}

int32_t mpu9250_drv_enable_fifo_ovflw_int(bool fifo_ovflw_en)
{

    return MPU9250_OK;
}

int32_t mpu9250_drv_enable_fsync_int(bool fsync_en)
{

    return MPU9250_OK;
}

int32_t mpu9250_drv_enable_raw_rdy_int(bool raw_rdy_en)
{

    return MPU9250_OK;
}

int32_t mpu9250_drv_set_int_pin_logic_level(int_logic_level_e level)
{

    return MPU9250_OK;
}

int32_t mpu9250_drv_set_pin_drv(int_drv_e drv)
{

    return MPU9250_OK;
}

int32_t mpu9250_drv_set_latch_mode(latch_mode_e mode)
{

    return MPU9250_OK;
}

int32_t mpu9250_drv_set_status_clear_mode(status_clear_e mode)
{

    return MPU9250_OK;
}

int32_t mpu9250_drv_set_fsync_logic_level(fsync_logic_level_e level)
{

    return MPU9250_OK;
}

int32_t mpu9250_drv_enable_fsync_int(bool fsync_int_en)
{

    return MPU9250_OK;
}

int32_t mpu9250_drv_enable_bypass(bool bypass_en)
{

    return MPU9250_OK;
}

int32_t mpu9250_drv_write(uint8_t reg_addr, uint8_t const * const p_write_buf, size_t len)
{

    return MPU9250_OK;
}

int32_t mpu9250_drv_read(uint8_t reg_addr, uint8_t const * const p_read_buf, size_t len)
{

    return MPU9250_OK;
}


//-------------------------LOCAL FUNCTIONS----------------------------------

#ifndef __APP_SOFT_I2C_H_
#define __APP_SOFT_I2C_H_
#include "platform.h"


void app_i2c_init(void);
void app_i2c_start(void);
void app_i2c_stop(void);
u8 app_i2c_senddata8(u8 data); //the value return is Ack
u8 app_i2c_revdata8(u8 Ack);   






#endif

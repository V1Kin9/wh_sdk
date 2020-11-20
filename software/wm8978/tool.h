#ifndef __TOOL_H_
#define __TOOL_H_
#include "platform.h"

int reg_write_read_test_if_ok(int addr,int len);

int reg_bit_write_read_test_if_ok(int addr, int len);

char test_one_bit_is_ok(int addr , int bit_pos);

void peri_test_reg();
#endif

#ifndef __APP_I2S_H_
#define __APP_I2S_H_
#include "platform.h"
//when WS is 0, it is left stereo ; when WS is 1,it is right stereo
#define X 0 

#define I2S_BASE 0X10004C00
#define IER_OFFSET 0x00
#define IRER_OFFSET 0x04
#define ITER_OFFSET 0x08
#define CER_OFFSET 0x0c
#define CCR_OFFSET 0x10
#define RXFFR_OFFSET 0x14
#define TXFFR_OFFSET 0x18
#define LRBR_OFFSET (0x020+0x04*X)
#define LTHR_OFFSET (0x020+0x04*X)
#define RRBR_OFFSET (0x024+0x04*X)
#define RTHR_OFFSET (0x024+0x04*X)
#define RER_OFFSET (0x028+0x04*X)
#define TER_OFFSET (0x02c+0x40*X)
#define RCR_OFFSET (0x030+0x04*X)
#define TCR_OFFSET (0x034+0x04*X)
#define ISR_OFFSET (0x038+0x04*X)
#define IMR_OFFSET (0x03c+0x04*X)
#define ROR_OFFSET (0x040+0x04*X)
#define _TOR_OFFSET (0x044+0x04*X)
#define RFCR_OFFSET (0x048+0x04*X)
#define TFCR_OFFSET (0x04c+0x04*X)
#define RFF_OFFSET (0x050+0x04*X)
#define TFF_OFFSET (0x054+0x04*X)
#define RXDMA_OFFSET 0x1c0
#define RRXDMA_OFFSET 0x1c4
#define TXDMA_OFFSET 0x1c8
#define RTXDMA_OFFSET 0x1cc
#define COMP_PARAM_2_OFFSET 0x1f0 
#define COMP_PARAM_1_OFFSET 0x1f4
#define COMP_VERSION_OFFSET 0x1f8
#define COMP_TYPE_OFFSET 0x1fc

#define I2S_IER  (*((volatile unsigned int*)(I2S_BASE+IER_OFFSET)))
#define I2S_IRER (*((volatile unsigned int*)(I2S_BASE+IRER_OFFSET)))
#define I2S_ITER (*((volatile unsigned int*)(I2S_BASE+ITER_OFFSET)))
#define I2S_CER (*((volatile unsigned int*)(I2S_BASE+CER_OFFSET)))
#define I2S_CCR (*((volatile unsigned int*)(I2S_BASE+CCR_OFFSET)))
#define I2S_RXFFR (*((volatile unsigned int*)(I2S_BASE+RXFFR_OFFSET)))
#define I2S_TXFFR (*((volatile unsigned int*)(I2S_BASE+TXFFR_OFFSET)))
#define I2S_LRBR (*((volatile unsigned int*)(I2S_BASE+LRBR_OFFSET)))
#define I2S_LTHR (*((volatile unsigned int*)(I2S_BASE+LTHR_OFFSET)))
#define I2S_RRBR (*((volatile unsigned int*)(I2S_BASE+RRBR_OFFSET)))
#define I2S_RTHR (*((volatile unsigned int*)(I2S_BASE+RTHR_OFFSET)))
#define I2S_RER (*((volatile unsigned int*)(I2S_BASE+RER_OFFSET)))
#define I2S_TER (*((volatile unsigned int*)(I2S_BASE+TER_OFFSET)))
#define I2S_RCR (*((volatile unsigned int*)(I2S_BASE+RCR_OFFSET)))
#define I2S_TCR (*((volatile unsigned int*)(I2S_BASE+TCR_OFFSET)))
#define I2S_ISR (*((volatile unsigned int*)(I2S_BASE+ISR_OFFSET)))
#define I2S_IMR (*((volatile unsigned int*)(I2S_BASE+IMR_OFFSET)))
#define I2S_ROR (*((volatile unsigned int*)(I2S_BASE+ROR_OFFSET)))
#define I2S_TOR (*((volatile unsigned int*)(I2S_BASE+TOR_OFFSET)))
#define I2S_RFCR (*((volatile unsigned int*)(I2S_BASE+RFCR_OFFSET)))
#define I2S_TFCR (*((volatile unsigned int*)(I2S_BASE+TFCR_OFFSET)))
#define I2S_RFF (*((volatile unsigned int*)(I2S_BASE+RFF_OFFSET)))
#define I2S_TFF (*((volatile unsigned int*)(I2S_BASE+TFF_OFFSET)))
#define I2S_RXDMA (*((volatile unsigned int*)(I2S_BASE+RXDMA_OFFSET)))
#define I2S_RRXDMA (*((volatile unsigned int*)(I2S_BASE+RRXDMA_OFFSET)))
#define I2S_TXDMA (*((volatile unsigned int*)(I2S_BASE+TXDMA_OFFSET)))
#define I2S_RTXDMA (*((volatile unsigned int*)(I2S_BASE+RTXDMA_OFFSET)))
#define I2S_COMP_PARAM_2 (*((volatile unsigned int*)(I2S_BASE+COMP_PARAM_2_OFFSET)))
#define I2S_COMP_PARAM_1 (*((volatile unsigned int*)(I2S_BASE+COMP_PARAM_1_OFFSET)))
#define I2S_COMP_VERSION (*((volatile unsigned int*)(I2S_BASE+COMP_VERSION_OFFSET)))
#define I2S_COMP_TYPE (*((volatile unsigned int*)(I2S_BASE+COMP_TYPE_OFFSET)))


void i2s_init();


#endif

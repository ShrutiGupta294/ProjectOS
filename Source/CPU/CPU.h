#ifndef CPU_H
#define CPU_H 

#include "library.h"

extern void AP_startup_Code();
extern void AP_startup_Code_end();
extern void rmode_AP_code();
extern void rmode_AP_code_end();
extern void pmode_AP_code();
extern void pmode_AP_code_end();

uint32_t total_CPU_Cores = 0;

uint32_t BSP_id;
uint32_t AP_startup_Code_sz;
uint32_t pmode_code_size;
uint32_t rmode_code_size;

uint32_t* cpu_get_apic_base();

void BasicCPU_Init();

void BootAPs();

#endif 
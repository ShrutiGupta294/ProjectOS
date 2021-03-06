#ifndef DESC_TABLES_H
#define DESC_TABLES_H 

#include "library.h"

uintptr_t desc_malloc(uint32_t size);

extern void switcher();
extern void switcher_manual();
extern void lgdt(void *);
extern void lidt(void *);
extern void tss_flush();

typedef uint64_t gdt_entry_t;

typedef uint16_t gdt_ptr_t[3];

void init_descriptor_tables();

typedef uint64_t idt_entry_t;

typedef uint16_t idt_ptr_t[3];

uint32_t cs_TallyTbl[] = {0x8, 0x8, 0x1B, 0x1B};
uint32_t ds_TallyTbl[] = {0x10, 0x23, 0x10, 0x23};


//extern void Test_Timer();

//Interrupt handlers
void divByZero_handler();
void debug_handler();
void NMI_handler();
void breakpoint_handler();
void overflow_handler();
void outOfBounds_handler();
void invalidInstr_handler();
void noCoprocessor_handler();
void doubleFault_handler();
void coprocessor_handler();
void badTSS_handler();
void segmentNotPresent_handler();
void stackFault_handler();
void generalProtectionFault_handler();
void pageFault_handler();
void unknownInterrupt_handler();
void coprocessorFault_handler();
void alignmentCheck_handler();
void machineCheck_handler();
void reserved_handler();

//#ifdef PIC
extern void PIT_handler();
extern void kb_handle();
extern void switch_ToUserspace();
extern void switch_ToKernelspace();
//extern void Scheduler_Promoter_assistance();
extern void switcher_ksp();
extern void switcher_ksp2();
void keyboardInterrupt_handler();
void cascade_handler();//This particular interrupt is never raised
void COM2_handler();
void COM1_handler();
void LPT2_handler();
void floppyDisk_handler();
void LPT1_handler();
void RTC_handler();
void periph1_handler();
void periph2_handler();
void periph3_handler();
void mouse_handle();
void FPU_handler();
void primaryHDD_handler();//P -> Primary
void secondaryHDD_handler();//S -> Secondary
//#endif

typedef volatile struct __tss_struct
{
    unsigned short   link;
    unsigned short   link_h;

    unsigned long   esp0;
    unsigned short   ss0;
    unsigned short   ss0_h;

    unsigned long   esp1;
    unsigned short   ss1;
    unsigned short   ss1_h;

    unsigned long   esp2;
    unsigned short   ss2;
    unsigned short   ss2_h;

    unsigned long   cr3;
    unsigned long   eip;
    unsigned long   eflags;

    unsigned long   eax;
    unsigned long   ecx;
    unsigned long   edx;
    unsigned long    ebx;

    unsigned long   esp;
    unsigned long   ebp;

    unsigned long   esi;
    unsigned long   edi;

    unsigned short   es;
    unsigned short   es_h;

    unsigned short   cs;
    unsigned short   cs_h;

    unsigned short   ss;
    unsigned short   ss_h;

    unsigned short   ds;
    unsigned short   ds_h;

    unsigned short   fs;
    unsigned short   fs_h;

    unsigned short   gs;
    unsigned short   gs_h;

    unsigned short   ldt;
    unsigned short   ldt_h;

    unsigned short   trap;
    unsigned short   iomap;

} tss_struct_t;


tss_struct_t tss_tmp, **tss_entries = (tss_struct_t**)&tss_tmp;
uint32_t total_tss = 0;

void gdt_set_gate(int num,uint32_t base,uint32_t limit,uint8_t access,uint16_t gran, uint64_t* gdt_base);

static void idtSetEntry(int num, uint32_t base, uint32_t sel, uint32_t flags, uint64_t* idt_base);

void APpmode_gdt_Setup(uint32_t* gdt, uint32_t* gdtr);

void AP_idt_Setup(uint32_t* idt, uint32_t* idtr);

uintptr_t  pmode_GDT_init(uint32_t APIC_id);
uintptr_t  pmode_IDT_init(uint32_t APIC_id);
uintptr_t  pmode_IDT_initP(uint32_t APIC_id);
void pmode_GDT_lgdt(uint32_t APIC_id, uintptr_t gdt_new);
void pmode_IDT_lidt(uint32_t APIC_id, uintptr_t idt_new);
 void pmode_TSS_ltr(uint32_t APIC_id, uintptr_t tss_off);
void pmode_GDT_lgdt_Vec(uint32_t vector_addr, uintptr_t gdt_new);
void pmode_IDT_lidt_Vec(uint32_t vector_addr, uintptr_t idt_new);

extern void pmode_AP_code();
extern void pmode_AP_code_end();
extern void INTbasedPmodeTrampoline();
void test_handler();

void tss_set_esp0(uint32_t stack, uint32_t i); //this will update the ESP0 stack used when an interrupt occurs


#endif 
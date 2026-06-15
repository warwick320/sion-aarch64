#include "core/include/kernel_output/kernel_output.hpp"
#include "core/include/sion_pmm/sion_pmm.hpp"
using namespace sion64;

#define _asm_r(cmd, op, val) do { \
    asm volatile(cmd " %0, " #op : "=r"(val)); \
    printSL("cmd : %-4s | op : %-10s | read", cmd, #op); \
} while(0)

#define _asm_w(cmd, op, val) do { \
    asm volatile(cmd " " #op ", %0" :: "r"(val)); \
    printSL("cmd : %-4s | op : %-10s | write", cmd, #op); \
} while(0)

#define _csrr(op, val) _asm_r("csrr ", op, val)
#define _csrw(op, val) _asm_w("csrw ", op, val)

extern "C" void interrupt_trap(void);

static void set_timer(u64 time) {
    *MTIMECMP_ADDR = *MTIME_ADDR + time;
    printSI("success to write mtimecmp reg (value : %x)", *MTIMECMP_ADDR);
}

static void enable_interrupt_reg(bool enabled = true) {
    u64 mstatus, mie;

    enabled ? printSI("enabled interrupt_reg"): printSI("disabled interrupt_reg");

    _csrr(mstatus, mstatus);
    _csrr(mie, mie);
    printSL("[interrupt_reg][csrr result] mstatus : %x , mie : %x", mstatus, mie);

    enabled ? (mstatus |= (1 << 3)) : (mstatus &= ~(1 << 3));
    enabled ? (mie    |= (1 << 7)) : (mie    &= ~(1 << 7));

    _csrw(mstatus, mstatus);
    _csrw(mie, mie);
}

static void add_interrupt_handler(void* handler) {
    _csrw(mtvec, handler);
    printSI("mtvec added handler success (handler addr : 0x%x)", (u64)handler);
}

extern "C" void interrupt_handler(void) {
    printSI("interrupt_handler hit!");

    u64 reason;
    _csrr(mcause, reason);
    printSL("interrupt reason code : %x", reason);

    if (reason == INTERRUPT_REASON_TIMER)
        printSI("interrupt by timer!");

    enable_interrupt_reg(false);
    set_timer(10000000);
}


extern "C" void kernel_main(void) {
    printSL("Sion64(s64) kernel ver %s + build %s", S64_VER, S64_VER_BUILD);
    printSL("init sion_pmm");
    mem::pmm::pmm_init();
    printSI("sucessfuly init sion_pmm");
    printSL("init interrupt");
    add_interrupt_handler((void*)interrupt_trap);
    set_timer(10000000);
    enable_interrupt_reg();
    printSL("sucessfuly init interrupt");
    for (;;) {}
}

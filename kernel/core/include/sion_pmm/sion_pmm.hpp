#pragma once
#include "../framework.h"
#include "../kernel_output/kernel_output.hpp"

#define PAGE_SIZE 0x1000 // 4kb for matching hardware mmu
#define MEM_START 0x80000000
#define MEM_END 0x88000000
#define TOTAL_PAGE ((MEM_END - MEM_START) / PAGE_SIZE)
#define PMM_BITMAP_SIZE (TOTAL_PAGE / 8)


namespace sion64::mem {
    class pmm{
        public:
        pmm();

        static void pmm_init(void);
        [[nodiscard]]static u64 pmm_alloc(void);
        static void pmm_free(u64 addr);
        [[nodiscard]]static u8* get_pmm_status_bitmap(void);
        private:

        static u8 pmm_status_bitmap[PMM_BITMAP_SIZE];
        [[nodiscard]]static bool is_used(u32 page);
        static void mark_free(u32 page);
        static void mark_used(u32 page);

    };
}
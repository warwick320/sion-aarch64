#include "core/include/sion_pmm/sion_pmm.hpp"
#include "core/include/framework.h"
#include "core/include/kernel_output/kernel_output.hpp"

#define GET_PAGE_ADDR_BY_INDEX(idx) (MEM_START + ((idx) * PAGE_SIZE))
#define GET_PAGE_INDEX_BY_ADDR(addr) (((addr) - MEM_START) / PAGE_SIZE)
using namespace sion64::mem;

extern u64 kernel_end; // kernel size is already allocate
u8 pmm::pmm_status_bitmap[PMM_BITMAP_SIZE];

pmm::pmm(void){
    pmm_init();
}

void pmm::pmm_init(void){
    for(int i = 0; i<PMM_BITMAP_SIZE; i++) pmm_status_bitmap[i] = u8(0);
    u32 kernel_pages = ((u64)&kernel_end - MEM_START) / PAGE_SIZE;
    for (u32 i = 0; i <= kernel_pages; i++) mark_used(i);
    printSL("sion_pmm init success");
    return;
}

[[nodiscard]]u64 pmm::pmm_alloc(void){
    for (u32 i = 0; i< TOTAL_PAGE; i++) {
        if(is_used(i)) continue;
        else {
            mark_used(i); printSI("page:%d | allocated",i);
            return GET_PAGE_ADDR_BY_INDEX(i);//PAGE start addr
        }
    } printSE("NO MEMORY !!");
    return u64(0);
}

void pmm::pmm_free(u64 addr){
    u32 page =GET_PAGE_INDEX_BY_ADDR(addr);
    mark_free(page); printSI("Freed Page: %d (addr : 0x%x)",page,addr);
}
// inside helper
[[nodiscard]]bool pmm::is_used(u32 page){
    return (pmm_status_bitmap[page/8] >> (page % 8)) & 1;
}

void pmm::mark_used(u32 page){
    pmm_status_bitmap[page/8] |= ( 1 << (page % 8));
}
void pmm::mark_free(u32 page){
    pmm_status_bitmap[page/8] &= ~(1 << (page % 8));
}
// extern helper
[[nodiscard]]u8* pmm::get_pmm_status_bitmap(void){
    return pmm_status_bitmap;
}
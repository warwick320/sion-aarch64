ENTRY(_start)

SECTIONS {
    . = 0x80000000;
    .text : {
        *(.text)
    }
    .data : {
        *(.data)
    }
    .bss : {
        *(.bss)
    }

    . = ALIGN(16); /* 현재 주소(0x80000000)을 16배수로 정렬 즉 ~10으로 끝.
    cpu는 4바이트씩 읽기 때문에 비정렬된 데이터를 읽거을때 값이 짤려서 두번 읽어야하거나 에러가 날수있음. 따라서 정렬이 필수적임*/
    /* risc v 스택 정렬 규약 16바이트 */
    stack_bottom = .;
    . = . + 0x10000; /* stack size 64kb*/
    stack_top = .;
    kernel_end = .;
    

}
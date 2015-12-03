ENTRY(_start)
SECTIONS
{
  . = 0x20000000;
  .init : { *(.init) }
    . = 0x200000D0;
  .text : { *(.text) }
  .rodata : { *(.rodata) }
}

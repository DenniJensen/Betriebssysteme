.section .ivt, "a"
  @LDR     PC, =handle_abort_error
  @LDR     PC, =handle_swi_error
  @LDR     PC, =handle_prefetch_error

.section .text
hand_swi_error:
  MRS     R0, SPSR
  MSR     CPSR, R0
  LDR     R0, =handle_swi
  BX      R0

handle_prefetch_error:
  MRS     R0, SPSR
  MSR     CPSR, R0
  LDR     R0, =handle_prefetch
  BX      R0

handle_abort_error:
  MRS     R0, SPSR
  MSR     CPSR, R0
  BL      handle_abort

  SUB    PC, LR, #8

.section .ivt, "a"
  @LDR     PC, =handle_abort

handle_abort:
  MRS     R0, SPSR
  MSR     CPSR, R0
  BL      handle_abort_error

  SUB    PC, LR, #8

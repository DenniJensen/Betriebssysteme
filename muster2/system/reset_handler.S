.section .ivt

  ORR cpsr, cpsr, #31
  b handle_abort

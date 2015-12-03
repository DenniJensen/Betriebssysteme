.global _exception_vectors_begin
_exception_vectors_begin:
  LDR     PC, _asm_unhandled       /* Reset*/
  LDR     PC, _asm_undef           /* Undefined Intruction */
  LDR     PC, _asm_swi             /* Software Interrupt */
  LDR     PC, _asm_handle_prefetch /* Prefetch Abort */
  LDR     PC, _asm_handle_abort    /* Data Abort */
  LDR     PC, _asm_unhandled       /* Reserved */
  LDR     PC, _asm_handle_irq      /* Interrupt */
  LDR     PC, _asm_handle_fiq      /* Fast Interrupt */

_asm_undef:           .word asm_undef
_asm_swi:             .word asm_swi
_asm_handle_prefetch: .word asm_handle_prefetch
_asm_handle_abort:    .word asm_handle_abort
_asm_unhandled:       .word asm_unhandled
_asm_handle_irq:      .word asm_handle_irq
_asm_handle_fiq:      .word asm_handle_fiq

.global _exception_vectors_end
_exception_vectors_end:


asm_undef:
  STMDB   SP, {R0-R15}
  SUB     SP, SP, #(16*4)

  MOV     R0, SP
  B       handle_undef

asm_swi:
  STMDB   SP, {R0-R15}
  SUB     SP, SP, #(16*4)

  MOV     R0, SP
  B       handle_swi

asm_handle_prefetch:
  STMDB   SP, {R0-R15}
  SUB     SP, SP, #(16*4)

  MOV     R0, SP
  B       handle_prefetch

asm_handle_abort:
  STMDB   SP, {R0-R15}
  SUB     SP, SP, #(16*4)

  MOV     R0, SP
  B       handle_abort

asm_unhandled:
  STMDB   SP, {R0-R15}
  SUB     SP, SP, #(16*4)

  MOV     R0, SP
  B       unhandled

asm_handle_irq:
  STMDB   SP, {R0-R15}
  SUB     SP, SP, #(16*4)

  MOV     R0, SP
  B       handle_irq

asm_handle_fiq:
  STMDB   SP, {R0-R15}
  SUB     SP, SP, #(16*4)

  MOV     R0, SP
  B       handle_fiq


.global enable_irq
enable_irq:

  MRS R7, CPSR
  BIC R7,R7,#0x80
  MSR CPSR_c, R7
  MOV PC, LR

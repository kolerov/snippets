#include "riscv_relocations_data.h"

	.data
	.align 3

	.globl r_riscv_jal_target_behind
	.type r_riscv_jal_target_behind, @object
	.size r_riscv_jal_target_behind, 4
	.align 2
r_riscv_jal_target_behind:
	.zero 4

/* R_RISCV_32 */

	.globl r_riscv_32_add
	.type r_riscv_32_add, @object
	.size r_riscv_32_add, 4
	.align 2
r_riscv_32_add:
	.word r_riscv_32_target + R_RISCV_32_ADDEND

	.globl r_riscv_32_sub
	.type r_riscv_32_sub, @object
	.size r_riscv_32_sub, 4
	.align 2
r_riscv_32_sub:
	.word r_riscv_32_target - R_RISCV_32_ADDEND

/* R_RISCV_64 */

	.globl r_riscv_64_add
	.type r_riscv_64_add, @object
	.size r_riscv_64_add, 8
	.align 3
r_riscv_64_add:
	.dword r_riscv_64_target + R_RISCV_64_ADDEND

	.globl r_riscv_64_sub
	.type r_riscv_64_sub, @object
	.size r_riscv_64_sub, 8
	.align 3
r_riscv_64_sub:
	.dword r_riscv_64_target - R_RISCV_64_ADDEND

/* R_RISCV_PCREL_HI20 */

	.set r_riscv_pcrel_hi20_target_behind, R_RISCV_PCREL_HI20_TARGET_BEHIND
	.set r_riscv_pcrel_hi20_target_ahead, R_RISCV_PCREL_HI20_TARGET_AHEAD

	.globl r_riscv_pcrel_hi20_ahead
	.type r_riscv_pcrel_hi20_ahead, @object
	.size r_riscv_pcrel_hi20_ahead, 4
	.align 2
r_riscv_pcrel_hi20_ahead:
	auipc a0, %pcrel_hi(r_riscv_pcrel_hi20_target_ahead)

	.globl r_riscv_pcrel_hi20_behind
	.type r_riscv_pcrel_hi20_behind, @object
	.size r_riscv_pcrel_hi20_behind, 4
	.align 2
r_riscv_pcrel_hi20_behind:
	auipc a0, %pcrel_hi(r_riscv_pcrel_hi20_target_behind)

	.globl r_riscv_pcrel_hi20_ahead_add
	.type r_riscv_pcrel_hi20_ahead_add, @object
	.size r_riscv_pcrel_hi20_ahead_add, 4
	.align 2
r_riscv_pcrel_hi20_ahead_add:
	auipc a0, %pcrel_hi(r_riscv_pcrel_hi20_target_ahead + R_RISCV_PCREL_HI20_ADDEND)

	.globl r_riscv_pcrel_hi20_ahead_sub
	.type r_riscv_pcrel_hi20_ahead_sub, @object
	.size r_riscv_pcrel_hi20_ahead_sub, 4
	.align 2
r_riscv_pcrel_hi20_ahead_sub:
	auipc a0, %pcrel_hi(r_riscv_pcrel_hi20_target_ahead - R_RISCV_PCREL_HI20_ADDEND)

	.globl r_riscv_pcrel_lo12_i_behind
	.type r_riscv_pcrel_lo12_i_behind, @object
	.size r_riscv_pcrel_lo12_i_behind, 4
	.align 2
r_riscv_pcrel_lo12_i_behind:
	lw a0, %pcrel_lo(r_riscv_pcrel_hi20_behind)(a0)

	.globl r_riscv_pcrel_lo12_i_ahead
	.type r_riscv_pcrel_lo12_i_ahead, @object
	.size r_riscv_pcrel_lo12_i_ahead, 4
	.align 2
r_riscv_pcrel_lo12_i_ahead:
	lw a0, %pcrel_lo(r_riscv_pcrel_hi20_ahead)(a0)

	.globl r_riscv_pcrel_lo12_s_behind
	.type r_riscv_pcrel_lo12_s_behind, @object
	.size r_riscv_pcrel_lo12_s_behind, 4
	.align 2
r_riscv_pcrel_lo12_s_behind:
	sw a1, %pcrel_lo(r_riscv_pcrel_hi20_behind)(a0)

	.globl r_riscv_pcrel_lo12_s_ahead
	.type r_riscv_pcrel_lo12_s_ahead, @object
	.size r_riscv_pcrel_lo12_s_ahead, 4
	.align 2
r_riscv_pcrel_lo12_s_ahead:
	sw a1, %pcrel_lo(r_riscv_pcrel_hi20_ahead)(a0)

/* R_RISCV_HI20 */

	.globl r_riscv_hi20
	.type r_riscv_hi20, @object
	.size r_riscv_hi20, 4
	.align 2
r_riscv_hi20:
	lui a0, %hi(r_riscv_hi20_target)
	sw a1, %lo(r_riscv_hi20_target)(a0)

	.globl r_riscv_hi20_add
	.type r_riscv_hi20_add, @object
	.size r_riscv_hi20_add, 4
	.align 2
r_riscv_hi20_add:
	lui a0, %hi(r_riscv_hi20_target + R_RISCV_HI20_ADDEND)

	.globl r_riscv_hi20_sub
	.type r_riscv_hi20_sub, @object
	.size r_riscv_hi20_sub, 4
	.align 2
r_riscv_hi20_sub:
	lui a0, %hi(r_riscv_hi20_target - R_RISCV_HI20_ADDEND)

	.globl r_riscv_lo12_i
	.type r_riscv_lo12_i, @object
	.size r_riscv_lo12_i, 4
	.align 2
r_riscv_lo12_i:
	lw a0, %lo(r_riscv_hi20_target)(a0)

	.globl r_riscv_lo12_i_add
	.type r_riscv_lo12_i_add, @object
	.size r_riscv_lo12_i_add, 4
	.align 2
r_riscv_lo12_i_add:
	lw a0, %lo(r_riscv_hi20_target + R_RISCV_HI20_ADDEND)(a0)

	.globl r_riscv_lo12_i_sub
	.type r_riscv_lo12_i_sub, @object
	.size r_riscv_lo12_i_sub, 4
	.align 2
r_riscv_lo12_i_sub:
	lw a0, %lo(r_riscv_hi20_target - R_RISCV_HI20_ADDEND)(a0)

	.globl r_riscv_lo12_s
	.type r_riscv_lo12_s, @object
	.size r_riscv_lo12_s, 4
	.align 2
r_riscv_lo12_s:
	sw a1, %lo(r_riscv_hi20_target)(a0)

	.globl r_riscv_lo12_s_add
	.type r_riscv_lo12_s_add, @object
	.size r_riscv_lo12_s_add, 4
	.align 2
r_riscv_lo12_s_add:
	sw a1, %lo(r_riscv_hi20_target + R_RISCV_HI20_ADDEND)(a0)

	.globl r_riscv_lo12_s_sub
	.type r_riscv_lo12_s_sub, @object
	.size r_riscv_lo12_s_sub, 4
	.align 2
r_riscv_lo12_s_sub:
	sw a1, %lo(r_riscv_hi20_target - R_RISCV_HI20_ADDEND)(a0)

/* R_RISCV_BRANCH */

	.globl r_riscv_branch_ahead
	.type r_riscv_branch_ahead, @object
	.size r_riscv_branch_ahead, 4
	.align 2
r_riscv_branch_ahead:
	beq x1, x0, r_riscv_branch_behind

	.globl r_riscv_branch_behind
	.type r_riscv_branch_behind, @object
	.size r_riscv_branch_behind, 4
	.align 2
r_riscv_branch_behind:
	beq x1, x0, r_riscv_branch_ahead

/* R_RISCV_JAL */

	.globl r_riscv_jal_behind
	.type r_riscv_jal_behind, @object
	.size r_riscv_jal_behind, 4
	.align 2
r_riscv_jal_behind:
	j r_riscv_jal_target_behind

	.globl r_riscv_jal_ahead
	.type r_riscv_jal_ahead, @object
	.size r_riscv_jal_ahead, 4
	.align 2
r_riscv_jal_ahead:
	j r_riscv_jal_target_ahead

/* R_RISCV_CALL_TLP */

	.globl r_riscv_call_tlp
	.type r_riscv_call_tlp, @object
	.size r_riscv_call_tlp, 4
	.align 2
r_riscv_call_tlp:
	call r_riscv_call_tlp_target

/* Targets */

	.org 0x5000

	.globl r_riscv_32_target
	.type r_riscv_32_target, @object
	.size r_riscv_32_target, 4
	.align 2
r_riscv_32_target:
	.zero 4

	.globl r_riscv_64_target
	.type r_riscv_64_target, @object
	.size r_riscv_64_target, 4
	.align 2
r_riscv_64_target:
	.zero 4

	.globl r_riscv_hi20_target
	.type r_riscv_hi20_target, @object
	.size r_riscv_hi20_target, 4
	.align 2
r_riscv_hi20_target:
	.zero 4

	.globl r_riscv_jal_target_ahead
	.type r_riscv_jal_target_ahead, @object
	.size r_riscv_jal_target_ahead, 4
	.align 2
r_riscv_jal_target_ahead:
	.zero 4

	.globl r_riscv_call_tlp_target
	.type r_riscv_call_tlp_target, @object
	.size r_riscv_call_tlp_target, 4
	.align 2
r_riscv_call_tlp_target:
	.zero 4

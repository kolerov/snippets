#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <inttypes.h>

#include "riscv_relocations_data.h"

/*
 * Helper functions.
 */

void print_hex_32(uint32_t value)
{
    printf("0x%" PRIx32 "\n", value);
}

void print_hex_max(uintmax_t value)
{
    printf("0x%jx\n", value);
}

/*
 * Decoders of immediate values for different instruction formats. According to
 * ISA of RISC-V all immediate values must be treated as signed values (except
 * for the 5-bit immediates used in CSR instructions).
 */

int32_t get_u_imm(uint32_t instruction)
{
    return (instruction >> 12) << 12;
}

int32_t get_i_imm(uint32_t instruction)
{
    return ((int32_t) instruction) >> 20;
}

int32_t get_s_imm(uint32_t instruction)
{
    int32_t imm_4_0 = (instruction >> 7) & 0x1F;
    int32_t imm_11_5 = (((int32_t) instruction) >> 20) & 0xFFFFFFE0;
    return imm_11_5 | imm_4_0;
}

int32_t get_b_imm(uint32_t instruction)
{
    int32_t imm_12 = (((int32_t) instruction) >> 31) << 12;
    int32_t imm_11 = ((instruction >> 7) & 0x1) << 11;
    int32_t imm_10_5 = ((instruction >> 25) & 0x3F) << 5;
    int32_t imm_4_1 = ((instruction >> 8) & 0xF) << 1;
    return imm_12 | imm_11 | imm_10_5 | imm_4_1;
}

int32_t get_j_imm(uint32_t instruction)
{
    int32_t imm_20 = (((int32_t) instruction) >> 31) << 20;
    int32_t imm_19_12 = instruction & 0xFF000;
    int32_t imm_11 = ((instruction >> 20) & 0x1) << 11;
    int32_t imm_10_1 = ((instruction >> 21) & 0x3FF) << 1;
    return imm_20 | imm_19_12 | imm_11 | imm_10_1;
}

int32_t calculate_r_riscv_pcrel_hi20(uintmax_t symbol, int32_t addend, uintmax_t position)
{
    intmax_t result = ((symbol + addend - position + 0x800) >> 12) << 12;
    assert(result > INT32_MIN && result < INT32_MAX);
    return result;
}

int32_t calculate_r_riscv_hi20(uintmax_t symbol, int32_t addend)
{
    intmax_t result = ((symbol + addend + 0x800) >> 12) << 12;
    assert(result > INT32_MIN && result < INT32_MAX);
    return result;
}

/*
 * R_RISCV_32
 *
 * word32, S + A
 */

extern uint32_t r_riscv_32_add;
extern uint32_t r_riscv_32_sub;
extern uint32_t r_riscv_32_target;

void test_r_riscv_32()
{
    assert(((uintmax_t) r_riscv_32_add) == ((uintmax_t) (&r_riscv_32_target) + R_RISCV_32_ADDEND));
    assert(((uintmax_t) r_riscv_32_sub) == ((uintmax_t) (&r_riscv_32_target) - R_RISCV_32_ADDEND));
}

/*
 * R_RISCV_64
 *
 * word64, S + A
 */

extern uint64_t r_riscv_64_add;
extern uint64_t r_riscv_64_sub;
extern uint32_t r_riscv_64_target;

void test_r_riscv_64()
{
    assert(((uintmax_t) r_riscv_64_add) == ((uintmax_t) (&r_riscv_64_target) + R_RISCV_64_ADDEND));
    assert(((uintmax_t) r_riscv_64_sub) == ((uintmax_t) (&r_riscv_64_target) - R_RISCV_64_ADDEND));
}

/*
 * R_RISCV_PCREL_HI20
 *
 * U-type, S + A - P
 *
 * High 20 bits of 32-bit PC-relative reference, %pcrel_hi(symbol). This
 * relocation calculates an immediate value for AUIPC instruction in
 * R_RISCV_PCREL_HI20 + R_RISCV_PCREL_LO12_I/S pair. Note that the relocation
 * requires adding extra 0x800 value to make it compatible with LO12 part:
 *
 *     PCREL_HI20 = (symbol_address - hi20_reloc_offset + 0x800) >> 12
 *     PCREL_LO12 = (symbol_address - hi20_reloc_offset) & 0xFFF
 *     Full offset = (PCREL_HI20 << 12) + PCREL_LO12
 *
 * Here is an example of loading a value from a symbol:
 * 
 * .Ltmp0:
 *     auipc a0, %pcrel_hi(symbol)    <--- R_RISCV_PCREL_HI20
 *     lw a0, %pcrel_lo(.Ltmp0)(a0)   <--- R_RISCV_PCREL_LO12_I
 * 
 * Here is an example of storing a value to a symbol:
 *
 * .Ltmp1:
 *     auipc a0, %pcrel_hi(symbol)    <--- R_RISCV_PCREL_HI20
 *     sw a1, %pcrel_lo(.Ltmp1)(a0)   <--- R_RISCV_PCREL_LO12_S
 *
 * Calculate an address for a symbol:
 *
 * .Ltmp2:
 *     auipc a0, %pcrel_hi(symbol)    <--- R_RISCV_PCREL_HI20
 *     addi a0, a0, %pcrel_lo(.Ltmp2) <--- R_RISCV_PCREL_LO12_I
 */

extern uint32_t r_riscv_pcrel_hi20_behind;
extern uint32_t r_riscv_pcrel_hi20_ahead;
extern uint32_t r_riscv_pcrel_hi20_ahead_add;
extern uint32_t r_riscv_pcrel_hi20_ahead_sub;

void test_r_riscv_pcrel_hi20()
{
    int32_t stored, calculated;

    /* R_RISCV_PCREL_HI20 with a 0 addend and a target behind */
    stored = get_u_imm(r_riscv_pcrel_hi20_behind);
    calculated = calculate_r_riscv_pcrel_hi20(
        R_RISCV_PCREL_HI20_TARGET_BEHIND,
        0,
        (uintmax_t) &r_riscv_pcrel_hi20_behind);
    assert(stored == calculated);

    /* R_RISCV_PCREL_HI20 with a 0 addend and a target ahead */
    stored = get_u_imm(r_riscv_pcrel_hi20_ahead);
    calculated = calculate_r_riscv_pcrel_hi20(
        R_RISCV_PCREL_HI20_TARGET_AHEAD,
        0,
        (uintmax_t) &r_riscv_pcrel_hi20_ahead);
    assert(stored == calculated);

    /* R_RISCV_PCREL_HI20 with a positive addend */
    stored = get_u_imm(r_riscv_pcrel_hi20_ahead_add);
    calculated = calculate_r_riscv_pcrel_hi20(
        R_RISCV_PCREL_HI20_TARGET_AHEAD,
        R_RISCV_PCREL_HI20_ADDEND,
        (uintmax_t) &r_riscv_pcrel_hi20_ahead_add);
    assert(stored == calculated);

    /* R_RISCV_PCREL_HI20 with a negative addend */
    stored = get_u_imm(r_riscv_pcrel_hi20_ahead_sub);
    calculated = calculate_r_riscv_pcrel_hi20(
        R_RISCV_PCREL_HI20_TARGET_AHEAD,
        -R_RISCV_PCREL_HI20_ADDEND,
        (uintmax_t) &r_riscv_pcrel_hi20_ahead_sub);
    assert(stored == calculated);
}

/*
 * R_RISCV_PCREL_LO12_I
 *
 * I-type, S - P
 */

extern uint32_t r_riscv_pcrel_lo12_i_behind;
extern uint32_t r_riscv_pcrel_lo12_i_ahead;

void test_r_riscv_pcrel_lo12_i()
{
    int32_t offset_hi20, offset_lo12;
    uintmax_t address;

    /* R_RISCV_PCREL_LO12_I with a target behind */
    offset_hi20 = get_u_imm(r_riscv_pcrel_hi20_behind);
    offset_lo12 = get_i_imm(r_riscv_pcrel_lo12_i_behind);
    address = ((uintmax_t) &r_riscv_pcrel_hi20_behind) + offset_hi20 + offset_lo12;
    assert(address == R_RISCV_PCREL_HI20_TARGET_BEHIND);

    /* R_RISCV_PCREL_LO12_I with a target ahead */
    offset_hi20 = get_u_imm(r_riscv_pcrel_hi20_ahead);
    offset_lo12 = get_i_imm(r_riscv_pcrel_lo12_i_ahead);
    address = ((uintmax_t) &r_riscv_pcrel_hi20_ahead) + offset_hi20 + offset_lo12;
    assert(address == R_RISCV_PCREL_HI20_TARGET_AHEAD);
}

/*
 * R_RISCV_PCREL_LO12_S
 *
 * S-type, S - P
 */

extern uint32_t r_riscv_pcrel_lo12_s_behind;
extern uint32_t r_riscv_pcrel_lo12_s_ahead;

void test_r_riscv_pcrel_lo12_s()
{
    int32_t offset_hi20, offset_lo12;
    uintmax_t address;

    /* R_RISCV_PCREL_LO12_S with a target behind */
    offset_hi20 = get_u_imm(r_riscv_pcrel_hi20_behind);
    offset_lo12 = get_s_imm(r_riscv_pcrel_lo12_s_behind);
    address = ((uintmax_t) &r_riscv_pcrel_hi20_behind) + offset_hi20 + offset_lo12;
    assert(address == R_RISCV_PCREL_HI20_TARGET_BEHIND);

    /* R_RISCV_PCREL_LO12_S with a target ahead */
    offset_hi20 = get_u_imm(r_riscv_pcrel_hi20_ahead);
    offset_lo12 = get_s_imm(r_riscv_pcrel_lo12_s_ahead);
    address = ((uintmax_t) &r_riscv_pcrel_hi20_ahead) + offset_hi20 + offset_lo12;
    assert(address == R_RISCV_PCREL_HI20_TARGET_AHEAD);
}

/*
 * R_RISCV_HI20
 *
 * U-type, S + A
 *
 * High 20 bits of 32-bit absolute address, %hi(symbol). This relocation
 * calculates an immediate value for LUI instruction in R_RISCV_HI20 +
 * R_RISCV_LO12_I/S pair. Note that the relocation requires adding extra 0x800
 * value to make it compatible with LO12 part:
 *
 *     HI20 = (symbol_address + 0x800) >> 12
 *     LO12 = symbol_address & 0xFFF
 *     Full address = (HI20 << 12) + LO12
 *
 * Here is an example of loading a value from a symbol:
 * 
 *     lui a0, %hi(symbol)      <--- R_RISCV_HI20
 *     lw a0, %lo(symbol)(a0)   <--- R_RISCV_LO12_I
 * 
 * Here is an example of storing a value to a symbol:
 *
 *     lui a0, %hi(symbol)      <--- R_RISCV_HI20
 *     sw a1, %lo(symbol)(a0)   <--- R_RISCV_LO12_S
 *
 * Calculate an address for a symbol:
 *
 *     lui a0, %hi(symbol)      <--- R_RISCV_HI20
 *     addi a0, a0, %lo(symbol) <--- R_RISCV_LO12_S
 */

extern uint32_t r_riscv_hi20;
extern uint32_t r_riscv_hi20_add;
extern uint32_t r_riscv_hi20_sub;
extern uint32_t r_riscv_hi20_target;

void test_r_riscv_hi20()
{
    /* R_RISCV_PCREL_HI20 with a 0 addend */
    assert(get_u_imm(r_riscv_hi20) == calculate_r_riscv_hi20((uintmax_t) &r_riscv_hi20_target, 0));

    /* R_RISCV_PCREL_HI20 with a positive addend */
    assert(get_u_imm(r_riscv_hi20_add) == calculate_r_riscv_hi20((uintmax_t) &r_riscv_hi20_target, R_RISCV_HI20_ADDEND));

    /* R_RISCV_PCREL_HI20 with a negative addend */
    assert(get_u_imm(r_riscv_hi20_sub) == calculate_r_riscv_hi20((uintmax_t) &r_riscv_hi20_target, -R_RISCV_HI20_ADDEND));
}

/*
 * R_RISCV_LO12_I
 *
 * I-type, S + A
 */

extern uint32_t r_riscv_lo12_i;
extern uint32_t r_riscv_lo12_i_add;
extern uint32_t r_riscv_lo12_i_sub;

void test_r_riscv_lo12_i()
{
    int32_t offset_hi20, offset_lo12;

    /* R_RISCV_LO12_I with a zero addend */
    offset_hi20 = get_u_imm(r_riscv_hi20);
    offset_lo12 = get_i_imm(r_riscv_lo12_i);
    assert((uintmax_t) (offset_hi20 + offset_lo12) == (uintmax_t) &r_riscv_hi20_target);

    /* R_RISCV_LO12_I with a positive addend */
    offset_hi20 = get_u_imm(r_riscv_hi20_add);
    offset_lo12 = get_i_imm(r_riscv_lo12_i_add);
    assert((uintmax_t) (offset_hi20 + offset_lo12) == ((uintmax_t) &r_riscv_hi20_target + R_RISCV_HI20_ADDEND));

    /* R_RISCV_LO12_I with a negative addend */
    offset_hi20 = get_u_imm(r_riscv_hi20_sub);
    offset_lo12 = get_i_imm(r_riscv_lo12_i_sub);
    assert((uintmax_t) (offset_hi20 + offset_lo12) == ((uintmax_t) &r_riscv_hi20_target - R_RISCV_HI20_ADDEND));
}

/*
 * R_RISCV_LO12_S
 *
 * S-type, S + A
 */

extern uint32_t r_riscv_lo12_s;
extern uint32_t r_riscv_lo12_s_add;
extern uint32_t r_riscv_lo12_s_sub;

void test_r_riscv_lo12_s()
{
    int32_t offset_hi20, offset_lo12;

    /* R_RISCV_LO12_S with a zero addend */
    offset_hi20 = get_u_imm(r_riscv_hi20);
    offset_lo12 = get_s_imm(r_riscv_lo12_s);
    assert((uintmax_t) (offset_hi20 + offset_lo12) == (uintmax_t) &r_riscv_hi20_target);

    /* R_RISCV_LO12_S with a positive addend */
    offset_hi20 = get_u_imm(r_riscv_hi20_add);
    offset_lo12 = get_s_imm(r_riscv_lo12_s_add);
    assert((uintmax_t) (offset_hi20 + offset_lo12) == ((uintmax_t) &r_riscv_hi20_target + R_RISCV_HI20_ADDEND));

    /* R_RISCV_LO12_S with a negative addend*/
    offset_hi20 = get_u_imm(r_riscv_hi20_sub);
    offset_lo12 = get_s_imm(r_riscv_lo12_s_sub);
    assert((uintmax_t) (offset_hi20 + offset_lo12) == ((uintmax_t) &r_riscv_hi20_target - R_RISCV_HI20_ADDEND));
}

/*
 * R_RISCV_BRANCH
 *
 * B-type, S + A - P
 */

extern uint32_t r_riscv_branch_behind;
extern uint32_t r_riscv_branch_ahead;

void test_r_riscv_branch()
{
    assert(get_b_imm(r_riscv_branch_behind) == -4);
    assert(get_b_imm(r_riscv_branch_ahead) == 4);
}

/*
 * R_RISCV_JAL
 *
 * J-type, S + A - P
 */

extern uint32_t r_riscv_jal_behind;
extern uint32_t r_riscv_jal_target_behind;
extern uint32_t r_riscv_jal_ahead;
extern uint32_t r_riscv_jal_target_ahead;

void test_r_riscv_jal()
{
    assert(get_j_imm(r_riscv_jal_behind) == (int32_t) (((intmax_t) &r_riscv_jal_target_behind) - ((intmax_t) &r_riscv_jal_behind)));
    assert(get_j_imm(r_riscv_jal_ahead) == (int32_t) (((intmax_t) &r_riscv_jal_target_ahead) - ((intmax_t) &r_riscv_jal_ahead)));
}

/*
 * R_RISCV_CALL_TLP (same as R_RISCV_CALL for static non-TLP calls)
 *
 * U+I-Type, S + A - P
 */

extern uint32_t r_riscv_call_tlp;
extern uint32_t r_riscv_call_tlp_target;

void test_r_riscv_call_tlp()
{
    int32_t u_imm = get_u_imm(r_riscv_call_tlp);
    int32_t i_imm = get_i_imm(*(&r_riscv_call_tlp + 1));
    int32_t relative = u_imm + i_imm;
    uintmax_t absolute = ((uintmax_t) relative) + ((uintmax_t) &r_riscv_call_tlp);
    assert(absolute == (uintmax_t) &r_riscv_call_tlp_target);
}

int main()
{
    test_r_riscv_32();
    test_r_riscv_64();
    test_r_riscv_pcrel_hi20();
    test_r_riscv_pcrel_lo12_i();
    test_r_riscv_pcrel_lo12_s();
    test_r_riscv_hi20();
    test_r_riscv_lo12_i();
    test_r_riscv_lo12_s();
    test_r_riscv_branch();
    test_r_riscv_jal();
    test_r_riscv_call_tlp();
    return 0;
}

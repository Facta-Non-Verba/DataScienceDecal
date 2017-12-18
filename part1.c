#include <stdio.h> // for stderr
#include <stdlib.h> // for exit()
#include "types.h"
#include "utils.h"

void print_rtype(char *, Instruction);
void print_itype_except_load(char *, Instruction, int);
void print_load(char *, Instruction);
void print_store(char *, Instruction);
void print_branch(char *, Instruction);
void write_rtype(Instruction);
void write_itype_except_load(Instruction); 
void write_load(Instruction);
void write_store(Instruction);
void write_branch(Instruction);
void write_lui(Instruction);
void write_jal(Instruction);
void write_ecall(Instruction);


void decode_instruction(Instruction instruction) {
    /* YOUR CODE HERE: COMPLETE THE SWITCH STATEMENTS */
    switch(instruction.opcode) { // What do we switch on?
        /* YOUR CODE HERE */
        case 0x33:
            write_rtype(instruction);
            break;

        case 0x03: //I type with load
            write_load(instruction);
            break;

        case 0x13: //I type without load
            write_itype_except_load(instruction);
            break;

        case 0x73: //ecall
            write_ecall(instruction);
            break;

        case 0x23: //S type
            write_store(instruction);
            break;

        case 0x63: //SB type, branch instructions
            write_branch(instruction);
            break;

        case 0x37: //lui instruction
            write_lui(instruction);
            break;

        case 0x6f: //UJ type, jal instruction
            write_jal(instruction);
            break;

    	default: // undefined opcode
            handle_invalid_instruction(instruction);
    	    break;
    }
}

void write_rtype(Instruction instruction) {
    char* name = NULL;
	switch(instruction.rtype.funct3) { // What do we switch on?
        /* YOUR CODE HERE */
        case 0x0:
            switch(instruction.rtype.funct7) {
                case 0x00:
                    name = "add";
                    break;
                case 0x01:
                    name = "mul";
                    break;
                case 0x20:
                    name = "sub";
                    break;
                default:
                    handle_invalid_instruction(instruction);
                    break;
            }
        break;

        case 0x1:
            switch(instruction.rtype.funct7) {
                case 0x0:
                    name = "sll";
                    break;
                case 0x1:
                    name = "mulh";
                    break;
                default:
                    handle_invalid_instruction(instruction);
                    break;
            }
        break;

        case 0x2:
            name = "slt";
            break;

        case 0x4:
            switch(instruction.rtype.funct7) {
                case 0x0:
                    name = "xor";
                    break;
                case 0x1:
                    name = "div";
                    break;
                default:
                    handle_invalid_instruction(instruction);
                    break;
            }
        break;

        case 0x5:
            switch(instruction.rtype.funct7) {
                case 0x0:
                    name = "srl";
                    break;
                case 0x20:
                    name = "sra";
                    break;
                default:
                    handle_invalid_instruction(instruction);
                    break;
            }
        break;

        case 0x6:
            switch(instruction.rtype.funct7) {
                case 0x0:
                    name = "or";
                    break;
                case 0x1:
                    name = "rem";
                    break;
                default:
                    handle_invalid_instruction(instruction);
                    break;
            }
        break;

        case 0x7:
            name = "and";
            break;

	    default:
            handle_invalid_instruction(instruction);
            break;
	}
    print_rtype(name, instruction);
}

void write_itype_except_load(Instruction instruction) {
    char* name = NULL;
    int shiftOp;
    int srai = 0;
    unsigned int temp;
    shiftOp = -1;
    switch(instruction.itype.funct3) { // What do we switch on?
        /* YOUR CODE HERE */
        case 0x0:
            name = "addi";
            break;

        case 0x1:
            name = "slli";
            break;

        case 0x2:
            name = "slti";
            break;

        case 0x4:
            name = "xori";
            break;

        case 0x5:
            temp = instruction.itype.imm;
            temp = temp >> 5;
            if (temp > 0) {
                name = "srai";
                srai = 1;
            } else if (temp == 0) {
                name = "srli";
            } else {
                handle_invalid_instruction(instruction);
            }
            break;

        case 0x6:
            name = "ori";
            break;

        case 0x7:
            name = "andi";
            break;

        default:
            handle_invalid_instruction(instruction);
            break;  
    }
    temp = instruction.itype.imm;
    if (srai == 1) {
        temp = ~(((unsigned int) (~0)) << 5) & temp;
    }
    print_itype_except_load(name, instruction, bitSigner(temp, 12));
}

void write_load(Instruction instruction) {
    char* name = NULL;
    switch(instruction.itype.funct3) { // What do we switch on?
        /* YOUR CODE HERE */
        case 0x0:
            name = "lb";
            break;

        case 0x1:
            name = "lh";
            break;

        case 0x2:
            name = "lw";
            break;

        default:
            handle_invalid_instruction(instruction);
            break;
    }
    print_load(name, instruction);
}

void write_store(Instruction instruction) {
    char* name = NULL;
    switch(instruction.stype.funct3) { // What do we switch on?
        /* YOUR CODE HERE */
        case 0x0:
            name = "sb";
            break;

        case 0x1:
            name = "sh";
            break;

        case 0x2:
            name = "sw";
            break;

        default:
            handle_invalid_instruction(instruction);
            break;
    }
    print_store(name, instruction);
}

void write_branch(Instruction instruction) {
    char* name = NULL;
    switch(instruction.sbtype.funct3) { // What do we switch on?
        /* YOUR CODE HERE */
        case 0x0:
            name = "beq";
            break;

        case 0x1:
            name = "bne";
            break;

        default:
            handle_invalid_instruction(instruction);
            break;
    }

    print_branch(name, instruction);
}

/* For the writes, probably a good idea to take a look at utils.h */

void write_lui(Instruction instruction) {
    /* YOUR CODE HERE */

}

void write_jal(Instruction instruction) {
    /* YOUR CODE HERE */
}

void write_ecall(Instruction instruction) {
    /* YOUR CODE HERE */
    printf(ECALL_FORMAT);
}

void print_rtype(char *name, Instruction instruction) {
    /* YOUR CODE HERE */
    printf(RTYPE_FORMAT, name, instruction.rtype.rd, instruction.rtype.rs1, instruction.rtype.rs2);
}

void print_itype_except_load(char *name, Instruction instruction, int imm) {
    /* YOUR CODE HERE */
    printf(ITYPE_FORMAT, name, instruction.itype.rd, instruction.itype.rs1, imm);
}

void print_load(char *name, Instruction instruction) {
    /* YOUR CODE HERE */
    printf(MEM_FORMAT, name, instruction.itype.rd, instruction.itype.imm, instruction.itype.rs1);
}

void print_store(char *name, Instruction instruction) {
    /* YOUR CODE HERE */
    int imm = get_store_offset(instruction);
    printf(MEM_FORMAT, name, instruction.stype.rs2, imm, instruction.stype.rs1);
}

void print_branch(char *name, Instruction instruction) {
    /* YOUR CODE HERE */
}

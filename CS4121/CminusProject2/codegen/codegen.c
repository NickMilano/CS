#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <util/string_utils.h>
#include <util/symtab.h>
#include <util/dlink.h>
#include "reg.h"
#include "codegen.h"
#include "symfields.h"
#include "types.h"

int numStrings = 0;
DLinkNode *textNode;

void generateProlouge(DList instList, DList globalList){
char* inst = ssave("\t.data ");
dlinkAppend(instList,dlinkNodeAlloc(inst));

if(!dlinkListEmpty(globalList))
  dlinkJoin(instList, instList, globalList);

inst = nssave(4,".newl: .asciiz ", "\"", "\\n", "\"");
dlinkAppend(instList,dlinkNodeAlloc(inst));

inst = nssave(1,"\t.text ");
dlinkAppend(instList,dlinkNodeAlloc(inst));

textNode = dlinkTail(instList);

inst = nssave(1,"\t.globl main ");
dlinkAppend(instList,dlinkNodeAlloc(inst));


inst = nssave(1,"main:\tnop");
dlinkAppend(instList,dlinkNodeAlloc(inst));

}

void generateTerminate(DList instList){
  char* inst = ssave("\tli $v0, 10");
  dlinkAppend(instList,dlinkNodeAlloc(inst));

  inst = ssave("\tsyscall");
  dlinkAppend(instList,dlinkNodeAlloc(inst));
}

void addString(DList instList, SymTable symtab, char* str, int ind) {
  char temp[5];
  sprintf(temp, "%d", numStrings);
  char* inst = nssave(6, ".string", temp, ": .asciiz ", "\"", str, "\"");
  dlinkInsertBefore(dlinkNodeAlloc(inst), textNode);
  inst = nssave(2, ".string", temp);
  SymPutFieldByIndex(symtab, ind, "variable", (Generic)inst);
  numStrings++;
}

void globalVar(DList globalList, int num) {
  char temp[5];
  sprintf(temp, "%d", num);
  char* inst = nssave(3, "var", temp, ":\t.word 100");
  dlinkAppend(globalList,dlinkNodeAlloc(inst));
}

void readVariable(DList instList, SymTable symtab, int ind) {
  char *label = SymGetFieldByIndex(symtab, ind, "label");
  char *inst= ssave("\tli $v0, 5");
  dlinkAppend(instList,dlinkNodeAlloc(inst));
  inst= ssave("\tsyscall");
  dlinkAppend(instList,dlinkNodeAlloc(inst));
  inst = nssave(2, "\tsw $v0, ", label);
  dlinkAppend(instList,dlinkNodeAlloc(inst));

}

int loadVariable(DList instList, SymTable symtab, int ind) {
  char* label = SymGetFieldByIndex(symtab, ind, "label");
  int reg = SymGetFieldByIndex(symtab, ind, "register");
  char temp[5];
  sprintf(temp, "%d", reg);
  char *inst = nssave(4, "\tlw ", getIntegerRegisterName(reg), ", ", label);
  dlinkAppend(instList,dlinkNodeAlloc(inst));

  return reg;

}

void integerPrint(DList instList, SymTable symtab, int ind) {
  char *inst = nssave(2, "\tmove $a0, ", getIntegerRegisterName(ind));
  dlinkAppend(instList,dlinkNodeAlloc(inst));
  inst = ssave("\tli $v0, 1");
  dlinkAppend(instList,dlinkNodeAlloc(inst));
  inst = ssave("\tsyscall");
  dlinkAppend(instList,dlinkNodeAlloc(inst));
  ind = 0;
  for(ind; ind < 17; ind++) {
    freeIntegerRegister(ind);
  }
  inst = ssave("\tla $a0, .newl");
  dlinkAppend(instList,dlinkNodeAlloc(inst));
  inst = ssave("\tli $v0, 4");
  dlinkAppend(instList,dlinkNodeAlloc(inst));
  inst = ssave("syscall");
  dlinkAppend(instList,dlinkNodeAlloc(inst));
}

int integerConstant(int num, SymTable symtab, DList instList, int varInd) {
  int reg = getFreeIntegerRegisterIndex(symtab);
  char* label = SymGetFieldByIndex(symtab, (int)varInd, "label");
  char temp[5];
  sprintf(temp, "%d", num);
  char *inst = nssave(4, "\tli ", getIntegerRegisterName(reg), ", ", temp);
  dlinkAppend(instList,dlinkNodeAlloc(inst));
  return reg;
}

void assignExpression(int lhs, int rhsRegister, SymTable symtab, DList instList) {
  char* label = SymGetFieldByIndex(symtab, (int)lhs, "label");
  char *inst = nssave(4, "\tsw ", getIntegerRegisterName(rhsRegister), ", ", label);
  dlinkAppend(instList,dlinkNodeAlloc(inst));
  freeIntegerRegister(rhsRegister);
}

static int expressionMaker(DList instList, SymTable symtab, int leftOperand, int rightOperand, char* opcode) {
  int reg = getFreeIntegerRegisterIndex(symtab);
  char temp[5];
	char* inst = nssave(8,"\t", opcode , " ", getIntegerRegisterName(reg), ", ", getIntegerRegisterName(leftOperand), ", ", getIntegerRegisterName(rightOperand));
	dlinkAppend(instList,dlinkNodeAlloc(inst));
  freeIntegerRegister(leftOperand);
	return reg;
}

static int expressionMakerFactor(DList instList, SymTable symtab, int leftOperand, int rightOperand, char* opcode) {
  int reg = getFreeIntegerRegisterIndex(symtab);
  char temp[5];
  sprintf(temp, "%d", reg);
	char* inst = nssave(6,"\t", opcode , " ", getIntegerRegisterName(leftOperand), ", ", getIntegerRegisterName(rightOperand));
	dlinkAppend(instList,dlinkNodeAlloc(inst));
  inst = nssave(2, "\tmflo ", getIntegerRegisterName(reg));
  dlinkAppend(instList,dlinkNodeAlloc(inst));
  freeIntegerRegister(rightOperand);
  freeIntegerRegister(leftOperand);
	return reg;
}

int notExpression(DList instList, SymTable symtab, int ind1) {
  int reg = getFreeIntegerRegisterIndex(symtab);
  char temp[5];
  sprintf(temp, "%d", reg);
  char* inst = nssave(5,"\tsltiu ", getIntegerRegisterName(reg), ", ", getIntegerRegisterName(ind1), ", 1");
  dlinkAppend(instList,dlinkNodeAlloc(inst));
  freeIntegerRegister(ind1);
  return reg;
}

int addExpression(DList instList, SymTable symtab, int ind1, int ind2) {
  return expressionMaker(instList, symtab, ind1, ind2, "add");
}

int subExpression(DList instList, SymTable symtab, int ind1, int ind2) {
  return expressionMaker(instList, symtab, ind1, ind2, "sub");
}

int andExpression(DList instList, SymTable symtab, int ind1, int ind2) {
  return expressionMaker(instList, symtab, ind1, ind2, "and");
}

int orExpression(DList instList, SymTable symtab, int ind1, int ind2) {
  return expressionMaker(instList, symtab, ind1, ind2, "or");
}

int equalExpression(DList instList, SymTable symtab, int ind1, int ind2) {
  return expressionMaker(instList, symtab, ind1, ind2, "seq");
}

int notEqualExpression(DList instList, SymTable symtab, int ind1, int ind2) {
  return expressionMaker(instList, symtab, ind1, ind2, "sne");
}

int lessThanExpression(DList instList, SymTable symtab, int ind1, int ind2) {
  return expressionMaker(instList, symtab, ind1, ind2, "slt");
}

int lessEqualThanExpression(DList instList, SymTable symtab, int ind1, int ind2) {
  return expressionMaker(instList, symtab, ind1, ind2, "sle");
}

int greaterThanExpression(DList instList, SymTable symtab, int ind1, int ind2) {
  return expressionMaker(instList, symtab, ind1, ind2, "sgt");
}

int greaterEqualThanExpression(DList instList, SymTable symtab, int ind1, int ind2) {
  return expressionMaker(instList, symtab, ind1, ind2, "sge");
}

int multExpression(DList instList, SymTable symtab, int ind1, int ind2) {
  return expressionMakerFactor(instList, symtab, ind1, ind2, "mult");
}

int divExpression(DList instList, SymTable symtab, int ind1, int ind2) {
  return expressionMakerFactor(instList, symtab, ind1, ind2, "div");
}

void writeString(DList instList, SymTable symtab, char *str) {
    int i = SymIndex(symtab, str);
    char *temp = SymGetFieldByIndex(symtab, i, "variable");
    char *inst = nssave(2,"\tla $a0, ", temp);
    dlinkAppend(instList,dlinkNodeAlloc(inst));
    inst = ssave("\tli $v0, 4");
    dlinkAppend(instList,dlinkNodeAlloc(inst));
    inst = ssave("syscall");
    dlinkAppend(instList,dlinkNodeAlloc(inst));
    inst = ssave("\tla $a0, .newl");
    dlinkAppend(instList,dlinkNodeAlloc(inst));
    inst = ssave("\tli $v0, 4");
    dlinkAppend(instList,dlinkNodeAlloc(inst));
    inst = ssave("syscall");
    dlinkAppend(instList,dlinkNodeAlloc(inst));

}

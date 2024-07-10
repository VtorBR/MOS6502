#pragma once

struct CPU;

void BRK(struct CPU*);
void CLC(struct CPU*);
void CLD(struct CPU*);
void CLI(struct CPU*);
void CLV(struct CPU*);
void DEX(struct CPU*);
void DEY(struct CPU*);
void INX(struct CPU*);
void INY(struct CPU*);
void JMP(struct CPU*);
void LDA(struct CPU*);
void LDX(struct CPU*);
void LDY(struct CPU*);
void NOP(struct CPU*);
void PHA(struct CPU*);
void PHP(struct CPU*);
void PLA(struct CPU*);
void PLP(struct CPU*);
void RTI(struct CPU*);
void RTS(struct CPU*);
void SEC(struct CPU*);
void SED(struct CPU*);
void SEI(struct CPU*);
void TAX(struct CPU*);
void TAY(struct CPU*);
void TSX(struct CPU*);
void TXA(struct CPU*);
void TXS(struct CPU*);
void TYA(struct CPU*);

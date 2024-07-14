#pragma once

struct CPU;

void ADC(struct CPU*);
void AND(struct CPU*);
void ASL_A(struct CPU*);
void ASL(struct CPU*);
void BCC(struct CPU*);
void BCS(struct CPU*);
void BEQ(struct CPU*);
void BIT(struct CPU*);
void BMI(struct CPU*);
void BNE(struct CPU*);
void BPL(struct CPU*);
void BRK(struct CPU*);
void BVC(struct CPU*);
void BVS(struct CPU*);
void CLC(struct CPU*);
void CLD(struct CPU*);
void CLI(struct CPU*);
void CLV(struct CPU*);
void CMP(struct CPU*);
void CPX(struct CPU*);
void CPY(struct CPU*);
void DEC(struct CPU*);
void DEX(struct CPU*);
void DEY(struct CPU*);
void EOR(struct CPU*);
void INC(struct CPU*);
void INX(struct CPU*);
void INY(struct CPU*);
void JMP(struct CPU*);
void JSR(struct CPU*);
void LDA(struct CPU*);
void LDX(struct CPU*);
void LDY(struct CPU*);
void LSR_A(struct CPU*);
void LSR(struct CPU*);
void NOP(struct CPU*);
void ORA(struct CPU*);
void PHA(struct CPU*);
void PHP(struct CPU*);
void PLA(struct CPU*);
void PLP(struct CPU*);
void ROL_A(struct CPU*);
void ROL(struct CPU*);
void ROR_A(struct CPU*);
void ROR(struct CPU*);
void RTI(struct CPU*);
void RTS(struct CPU*);
void SEC(struct CPU*);
void SED(struct CPU*);
void SEI(struct CPU*);
void STA(struct CPU*);
void STX(struct CPU*);
void STY(struct CPU*);
void TAX(struct CPU*);
void TAY(struct CPU*);
void TSX(struct CPU*);
void TXA(struct CPU*);
void TXS(struct CPU*);
void TYA(struct CPU*);

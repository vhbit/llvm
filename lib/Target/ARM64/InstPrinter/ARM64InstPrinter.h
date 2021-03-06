//===-- ARM64InstPrinter.h - Convert ARM64 MCInst to assembly syntax ------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This class prints an ARM64 MCInst to a .s file.
//
//===----------------------------------------------------------------------===//

#ifndef ARM64INSTPRINTER_H
#define ARM64INSTPRINTER_H

#include "MCTargetDesc/ARM64MCTargetDesc.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCSubtargetInfo.h"

namespace llvm {

class MCOperand;

class ARM64InstPrinter : public MCInstPrinter {
public:
  ARM64InstPrinter(const MCAsmInfo &MAI, const MCInstrInfo &MII,
                   const MCRegisterInfo &MRI, const MCSubtargetInfo &STI);

  virtual void printInst(const MCInst *MI, raw_ostream &O, StringRef Annot);
  virtual void printRegName(raw_ostream &OS, unsigned RegNo) const;

  // Autogenerated by tblgen.
  virtual void printInstruction(const MCInst *MI, raw_ostream &O);
  virtual bool printAliasInstr(const MCInst *MI, raw_ostream &O);
  virtual StringRef getRegName(unsigned RegNo) const {
    return getRegisterName(RegNo);
  }
  static const char *getRegisterName(unsigned RegNo,
                                     unsigned AltIdx = ARM64::NoRegAltName);

protected:
  bool printSysAlias(const MCInst *MI, raw_ostream &O);
  // Operand printers
  void printOperand(const MCInst *MI, unsigned OpNo, raw_ostream &O);
  void printPostIncOperand(const MCInst *MI, unsigned OpNo, unsigned Imm,
                           raw_ostream &O);
  void printPostIncOperand1(const MCInst *MI, unsigned OpNo, raw_ostream &O);
  void printPostIncOperand2(const MCInst *MI, unsigned OpNo, raw_ostream &O);
  void printPostIncOperand3(const MCInst *MI, unsigned OpNo, raw_ostream &O);
  void printPostIncOperand4(const MCInst *MI, unsigned OpNo, raw_ostream &O);
  void printPostIncOperand6(const MCInst *MI, unsigned OpNo, raw_ostream &O);
  void printPostIncOperand8(const MCInst *MI, unsigned OpNo, raw_ostream &O);
  void printPostIncOperand12(const MCInst *MI, unsigned OpNo, raw_ostream &O);
  void printPostIncOperand16(const MCInst *MI, unsigned OpNo, raw_ostream &O);
  void printPostIncOperand24(const MCInst *MI, unsigned OpNo, raw_ostream &O);
  void printPostIncOperand32(const MCInst *MI, unsigned OpNo, raw_ostream &O);
  void printPostIncOperand48(const MCInst *MI, unsigned OpNo, raw_ostream &O);
  void printPostIncOperand64(const MCInst *MI, unsigned OpNo, raw_ostream &O);
  void printVRegOperand(const MCInst *MI, unsigned OpNo, raw_ostream &O);
  void printSysCROperand(const MCInst *MI, unsigned OpNo, raw_ostream &O);
  void printAddSubImm(const MCInst *MI, unsigned OpNum, raw_ostream &O);
  void printLogicalImm32(const MCInst *MI, unsigned OpNum, raw_ostream &O);
  void printLogicalImm64(const MCInst *MI, unsigned OpNum, raw_ostream &O);
  void printShifter(const MCInst *MI, unsigned OpNum, raw_ostream &O);
  void printShiftedRegister(const MCInst *MI, unsigned OpNum, raw_ostream &O);
  void printExtendedRegister(const MCInst *MI, unsigned OpNum, raw_ostream &O);
  void printExtend(const MCInst *MI, unsigned OpNum, raw_ostream &O);
  void printCondCode(const MCInst *MI, unsigned OpNum, raw_ostream &O);
  void printDotCondCode(const MCInst *MI, unsigned OpNum, raw_ostream &O);
  void printAlignedBranchTarget(const MCInst *MI, unsigned OpNum,
                                raw_ostream &O);
  void printAMIndexed(const MCInst *MI, unsigned OpNum, unsigned Scale,
                      raw_ostream &O);
  void printAMIndexedWB(const MCInst *MI, unsigned OpNum, unsigned Scale,
                        raw_ostream &O);
  void printAMIndexed128(const MCInst *MI, unsigned OpNum, raw_ostream &O) {
    printAMIndexed(MI, OpNum, 16, O);
  }
  void printAMIndexed128WB(const MCInst *MI, unsigned OpNum, raw_ostream &O) {
    printAMIndexedWB(MI, OpNum, 16, O);
  }

  void printAMIndexed64(const MCInst *MI, unsigned OpNum, raw_ostream &O) {
    printAMIndexed(MI, OpNum, 8, O);
  }
  void printAMIndexed64WB(const MCInst *MI, unsigned OpNum, raw_ostream &O) {
    printAMIndexedWB(MI, OpNum, 8, O);
  }

  void printAMIndexed32(const MCInst *MI, unsigned OpNum, raw_ostream &O) {
    printAMIndexed(MI, OpNum, 4, O);
  }
  void printAMIndexed32WB(const MCInst *MI, unsigned OpNum, raw_ostream &O) {
    printAMIndexedWB(MI, OpNum, 4, O);
  }

  void printAMIndexed16(const MCInst *MI, unsigned OpNum, raw_ostream &O) {
    printAMIndexed(MI, OpNum, 2, O);
  }
  void printAMIndexed16WB(const MCInst *MI, unsigned OpNum, raw_ostream &O) {
    printAMIndexedWB(MI, OpNum, 2, O);
  }

  void printAMIndexed8(const MCInst *MI, unsigned OpNum, raw_ostream &O) {
    printAMIndexed(MI, OpNum, 1, O);
  }
  void printAMIndexed8WB(const MCInst *MI, unsigned OpNum, raw_ostream &O) {
    printAMIndexedWB(MI, OpNum, 1, O);
  }
  void printAMUnscaled(const MCInst *MI, unsigned OpNum, raw_ostream &O) {
    printAMIndexed(MI, OpNum, 1, O);
  }
  void printAMUnscaledWB(const MCInst *MI, unsigned OpNum, raw_ostream &O) {
    printAMIndexedWB(MI, OpNum, 1, O);
  }
  void printAMNoIndex(const MCInst *MI, unsigned OpNum, raw_ostream &O);
  void printImmScale4(const MCInst *MI, unsigned OpNum, raw_ostream &O);
  void printImmScale8(const MCInst *MI, unsigned OpNum, raw_ostream &O);
  void printImmScale16(const MCInst *MI, unsigned OpNum, raw_ostream &O);
  void printPrefetchOp(const MCInst *MI, unsigned OpNum, raw_ostream &O);
  void printMemoryPostIndexed(const MCInst *MI, unsigned OpNum, raw_ostream &O);
  void printMemoryPostIndexed32(const MCInst *MI, unsigned OpNum,
                                raw_ostream &O);
  void printMemoryPostIndexed64(const MCInst *MI, unsigned OpNum,
                                raw_ostream &O);
  void printMemoryPostIndexed128(const MCInst *MI, unsigned OpNum,
                                 raw_ostream &O);
  void printMemoryRegOffset(const MCInst *MI, unsigned OpNum, raw_ostream &O,
                            int LegalShiftAmt);
  void printMemoryRegOffset8(const MCInst *MI, unsigned OpNum, raw_ostream &O);
  void printMemoryRegOffset16(const MCInst *MI, unsigned OpNum, raw_ostream &O);
  void printMemoryRegOffset32(const MCInst *MI, unsigned OpNum, raw_ostream &O);
  void printMemoryRegOffset64(const MCInst *MI, unsigned OpNum, raw_ostream &O);
  void printMemoryRegOffset128(const MCInst *MI, unsigned OpNum,
                               raw_ostream &O);

  void printFPImmOperand(const MCInst *MI, unsigned OpNum, raw_ostream &O);

  void printVectorList(const MCInst *MI, unsigned OpNum, raw_ostream &O,
                       StringRef LayoutSuffix);

  /// Print a list of vector registers where the type suffix is implicit
  /// (i.e. attached to the instruction rather than the registers).
  void printImplicitlyTypedVectorList(const MCInst *MI, unsigned OpNum,
                                      raw_ostream &O);

  template <unsigned NumLanes, char LaneKind>
  void printTypedVectorList(const MCInst *MI, unsigned OpNum, raw_ostream &O);

  void printVectorIndex(const MCInst *MI, unsigned OpNum, raw_ostream &O);
  void printAdrpLabel(const MCInst *MI, unsigned OpNum, raw_ostream &O);
  void printBarrierOption(const MCInst *MI, unsigned OpNum, raw_ostream &O);
  void printMSRSystemRegister(const MCInst *MI, unsigned OpNum, raw_ostream &O);
  void printMRSSystemRegister(const MCInst *MI, unsigned OpNum, raw_ostream &O);
  void printSystemCPSRField(const MCInst *MI, unsigned OpNum, raw_ostream &O);
  void printSIMDType10Operand(const MCInst *MI, unsigned OpNum, raw_ostream &O);
};

class ARM64AppleInstPrinter : public ARM64InstPrinter {
public:
  ARM64AppleInstPrinter(const MCAsmInfo &MAI, const MCInstrInfo &MII,
                        const MCRegisterInfo &MRI, const MCSubtargetInfo &STI);

  virtual void printInst(const MCInst *MI, raw_ostream &O, StringRef Annot);

  virtual void printInstruction(const MCInst *MI, raw_ostream &O);
  virtual bool printAliasInstr(const MCInst *MI, raw_ostream &O);
  virtual StringRef getRegName(unsigned RegNo) const {
    return getRegisterName(RegNo);
  }
  static const char *getRegisterName(unsigned RegNo,
                                     unsigned AltIdx = ARM64::NoRegAltName);
};
}

#endif

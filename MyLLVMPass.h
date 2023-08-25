#ifndef MY_LLVM_PASS_H
#define MY_LLVM_PASS_H

#include "llvm/Pass.h"

namespace llvm {
  class MyLLVMPass : public llvm::FunctionPass {
  public:
    static char ID;
    MyLLVMPass() : llvm::FunctionPass(ID) {}

    bool runOnFunction(llvm::Function &F) override;
  };
} // namespace llvm

#endif // MY_LLVM_PASS_H


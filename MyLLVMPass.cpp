#include<stdio.h>
#include<stdlib.h>
#include "MyLLVMPass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/IR/Attributes.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include <memory>
#include "llvm/IR/DebugLoc.h"

struct FragileCluster {
    llvm::DebugLoc start;
    llvm::DebugLoc end;
};

llvm::DebugLoc dl;
llvm::DebugLoc startLoc = dl.get();
std::unique_ptr<llvm::DebugLoc> start = std::make_unique<llvm::DebugLoc>(startLoc.operator->());

llvm::DebugLoc endLoc = dl.get();
std::unique_ptr<llvm::DebugLoc> end = std::make_unique<llvm::DebugLoc>(endLoc.operator->());


const char *LLVM_CUSTOM_ATTR_IsFragile = "is_fragile";

void markFragileFunctions(llvm::Module &M, llvm::DebugLoc start, llvm::DebugLoc end) {
    for (llvm::Function &F : M) {
        if (F.isDeclaration())
            continue;

        for (llvm::BasicBlock &BB : F) {
            llvm::DebugLoc BBStart = BB.getTerminator()->getDebugLoc();
            if (BBStart && BBStart->getLine() >= start->getLine() && BBStart->getLine() <= end->getLine()) {
    	    	F.addFnAttr(llvm::Attribute::get(F.getContext(), LLVM_CUSTOM_ATTR_IsFragile, "true"));
             	break;
           }
        }
    }
}

void collectAndDisplayFragileFunctions(llvm::Module &M) {
    llvm::outs() << "Fragile Functions:\n";
    llvm::outs() << "--------------------------------------------------\n";

    for (llvm::Function &F : M) {
    	
        if (F.hasFnAttribute(LLVM_CUSTOM_ATTR_IsFragile)) {
            //llvm::outs() << "---------------------------------------------hhhh-----\n";
            llvm::outs() << "Function: " << F.getName() << "\n";
            llvm::outs() << "Signature: " << *F.getReturnType() << " " << F.getName() << "(";
            bool isFirstParam = true;
            for (llvm::Argument &Arg : F.args()) {
                if (!isFirstParam)
                    llvm::outs() << ", ";
                isFirstParam = false;
                llvm::outs() << *Arg.getType() << " " << Arg.getName();
            }
            llvm::outs() << ")\n";

            unsigned functionSize = 0;
            for (llvm::BasicBlock &BB : F)
                functionSize++;

            llvm::outs() << "Function Size: " << functionSize << " lines of code\n";

            if (llvm::DISubprogram *SP = F.getSubprogram()) {
                llvm::outs() << "Source File: " << SP->getFilename() << "\n";
            }

            llvm::outs() << "--------------------------------------------------\n";
        }
    }
}

int main() {
    llvm::LLVMContext context;
    std::unique_ptr<llvm::Module> M = std::make_unique<llvm::Module>("MyModule", context);

    llvm::SMDiagnostic Err;
    M = llvm::parseIRFile("exp3.bc", Err, context);

    if (!M) {
        Err.print("MyLLVMPass", llvm::errs());
        return 1;
    }

    llvm::DebugLoc start;
    llvm::DebugLoc end;

    markFragileFunctions(*M, start, end);
    collectAndDisplayFragileFunctions(*M);

    return 0;
}


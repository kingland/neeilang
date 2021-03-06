#ifndef _NL_BACKENDS_LLVM_TYPE_BUILDER_H_
#define _NL_BACKENDS_LLVM_TYPE_BUILDER_H_

#include <map>
#include <memory>

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"

#include "primitives.h"
#include "type.h"

class TypeBuilder {
public:
  explicit TypeBuilder(llvm::LLVMContext &ctx) : ctx(ctx) {
    ll_types[Primitives::Int()] = llvm::Type::getInt32Ty(ctx);
    ll_types[Primitives::Float()] = llvm::Type::getDoubleTy(ctx);
    ll_types[Primitives::Void()] = llvm::Type::getVoidTy(ctx);
    ll_types[Primitives::Bool()] = llvm::Type::getInt1Ty(ctx);
    ll_types[Primitives::String()] =
        llvm::PointerType::getUnqual(llvm::Type::getInt8Ty(ctx));
  }

  llvm::Type *to_llvm(NLType t);
  llvm::FunctionType *to_llvm(std::shared_ptr<FuncType>, NLType receiver);
  llvm::Type *build_vtable(NLType t, std::vector<llvm::FunctionType *> methods);
  llvm::Type *array_type(NLType type);

private:
  llvm::LLVMContext &ctx;
  std::map<NLType, llvm::Type *> ll_types;
  llvm::Type *vtable_type(NLType t);
  std::map<NLType, llvm::Type *> vtabs;
};

#endif // _NL_BACKENDS_LLVM_TYPE_BUILDER_H_

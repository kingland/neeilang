#ifndef _NL_TYPE_H_
#define _NL_TYPE_H_

#include <cassert>
#include <memory>
#include <string>
#include <vector>

#include "field.h"
#include "functype.h"
#include "nltype.h"

struct FuncType;

class Type {
public:
  Type(std::string name) : name(name) {}

  bool superclass_of(const Type *other) const {
    const Type *super = other;
    while (super != nullptr && super != this) {
      super = super->supertype.get();
    }
    return super == this;
  }

  bool subclass_of(const Type *other) const {
    return other->superclass_of(this);
  }

  bool is_function_type() { return functype != nullptr; }

  int num_methods() { return get_methods().size(); }

  std::vector<std::shared_ptr<FuncType>> get_methods();

  int method_idx(const std::string &name) {
    auto m = get_method(name);
    auto methods = get_methods();

    for (int i = 0; i < methods.size(); i++) {
      if (methods[i] == m)
        return i;
    }

    return -1;
  }

  bool has_field(const std::string &name);
  Field get_field(const std::string &name);
  int field_idx(const std::string &name);
  bool has_method(const std::string &name);
  std::shared_ptr<FuncType> get_method(const std::string &name);

  std::string name;
  std::shared_ptr<Type> supertype;
  std::vector<Field> fields;
  std::vector<std::shared_ptr<FuncType>> methods;
  int arr_depth = 0;
  std::shared_ptr<Type> element_type = nullptr;
  std::shared_ptr<FuncType> functype = nullptr;
};

#endif // _NL_TYPE_H_

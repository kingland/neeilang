#ifndef _NL_PRIMITIVES_H_
#define _NL_PRIMITIVES_H_

#include "type.h"

namespace Primitives {
NLType Array(NLType elem_type, int dims);
NLType Class();
NLType String();
NLType Int();
NLType Float();
NLType Bool();
NLType Void();
NLType TypeError();
} // namespace Primitives

#endif // _NL_PRIMITIVES_H_

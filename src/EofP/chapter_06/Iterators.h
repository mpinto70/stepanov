#pragma once

#include <iterator>

namespace EofP {
namespace chapter_06 {

template <typename I>
I Find(I f, I l, const typename std::iterator_traits<I>::value_type& x) {
    while (f != l && *f != x)
        ++f;
    return f;
}
}
}

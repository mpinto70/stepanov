#pragma once

#include <iterator>

namespace EofP {
namespace chapter_06 {

template <typename I, typename P>
P ForEach(I f, I l, P p) {
    while (f != l) {
        p(*f);
        ++f;
    }
    return p;
}

template <typename I>
I Find(I f, I l, const typename std::iterator_traits<I>::value_type& x) {
    while (f != l && *f != x)
        ++f;
    return f;
}

template <typename I, typename P>
I FindIf(I f, I l, P p) {
    while (f != l && not p(*f))
        ++f;
    return f;
}
}
}

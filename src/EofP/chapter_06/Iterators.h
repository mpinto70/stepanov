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

template <typename I, typename P, typename J>
J CountIf(I f, I l, P p, J j) {
    while (f != l) {
        if (p(*f))
            ++j;
        ++f;
    }
    return j;
}

template <typename I, typename Op, typename F>
auto ReduceNonEmpty(I f, I l, Op op, F fun) -> std::result_of_t<F(I)> {
    // precondition f != l
    std::result_of_t<F(I)> r = fun(f);
    ++f;
    while (f != l) {
        r = op(r, fun(f));
        ++f;
    }
    return r;
}
}
}

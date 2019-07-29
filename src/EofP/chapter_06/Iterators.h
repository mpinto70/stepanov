#pragma once

#include <iterator>

namespace EofP {

// Section 6.4

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

template <typename I, typename Op, typename F>
auto Reduce(I f, I l, Op op, F fun, const std::result_of_t<F(I)>& z) -> std::result_of_t<F(I)> {
    if (f == l)
        return z;

    return ReduceNonEmpty(f, l, op, fun);
}

template <typename I0, typename I1, typename R>
std::pair<I0, I1> FindMismatch(I0 f0, I0 l0, I1 f1, I1 l1, R r) {
    while (f0 != l0 && f1 != l1 && r(*f0, *f1)) {
        ++f0;
        ++f1;
    }
    return std::make_pair(f0, f1);
}

template <typename I, typename R>
I FindAdjacentMismatch(I f, I l, R r) {
    if (f == l)
        return l;
    typename std::iterator_traits<I>::value_type x = *f;
    ++f;
    while (f != l && r(x, *f)) {
        x = *f;
        ++f;
    }
    return f;
}
}

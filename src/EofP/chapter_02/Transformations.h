#pragma once

#include <cmath>
#include <cstddef>
#include <utility>

namespace EofP {

// Section 2.1

template <typename T>
T Abs(T t) {
    return (t < T{ 0 }) ? -t : t;
}

template <typename T>
T EuclideanNorm(T x, T y) {
    return std::sqrt(x * x + y * y);
}

template <typename T>
T EuclideanNorm(T x, T y, T z) {
    return std::sqrt(x * x + y * y + z * z);
}
}

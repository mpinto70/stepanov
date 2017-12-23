#pragma once

#include <cmath>
#include <cstddef>
#include <utility>

namespace EofP {
namespace chapter_02 {

template<typename T>
T abs(T t) {
    return (t < T{0}) ? -t : t;
}

template<typename T>
T euclidean_norm(T x, T y) {
    return std::sqrt(x * x + y * y);
}

template<typename T>
T euclidean_norm(T x, T y, T z) {
    return std::sqrt(x * x + y * y + z * z);
}

}
}

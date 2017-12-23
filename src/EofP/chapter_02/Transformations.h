#pragma once
// based in work from Alex Stepanov https://www.youtube.com/watch?v=aIHAEYyoTUc&list=PLHxtyCq_WDLXryyw91lahwdtpZsmo4BGD

#include <cstddef>
#include <utility>

namespace EofP {
namespace chapter_02 {

template<typename T>
T abs(T t) {
    return (t < T{0}) ? -t : t;
}
}
}

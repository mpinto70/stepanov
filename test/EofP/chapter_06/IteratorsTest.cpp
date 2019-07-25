#include "EofP/chapter_06/Iterators.h"

#include <gtest/gtest.h>

#include <vector>

namespace EofP {
namespace chapter_06 {

TEST(IteratorsTest, find_with_vector_int) {
    const std::vector<int> v = { 21, 22, 23, 24, 25 };
    EXPECT_EQ(Find(begin(v), end(v), 23), begin(v) + 2);
    EXPECT_EQ(Find(begin(v), end(v), 21), begin(v));
    EXPECT_EQ(Find(begin(v), end(v), 25), begin(v) + 4);

    EXPECT_EQ(Find(begin(v), end(v), 26), end(v));
}
}
}

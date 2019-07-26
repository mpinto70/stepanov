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

TEST(IteratorsTest, find_with_set_int) {
    const std::set<int> v = { 21, 22, 23, 24, 25 };
    EXPECT_EQ(Find(begin(v), end(v), 23), v.find(23));
    EXPECT_EQ(Find(begin(v), end(v), 21), v.find(21));
    EXPECT_EQ(Find(begin(v), end(v), 25), v.find(25));

    EXPECT_EQ(Find(begin(v), end(v), 26), end(v));
}

TEST(IteratorsTest, find_with_vector_string) {
    const std::vector<std::string> v = { "21", "22", "23", "24", "25" };
    EXPECT_EQ(Find(begin(v), end(v), "23"), begin(v) + 2);
    EXPECT_EQ(Find(begin(v), end(v), "21"), begin(v));
    EXPECT_EQ(Find(begin(v), end(v), "25"), begin(v) + 4);

    EXPECT_EQ(Find(begin(v), end(v), "26"), end(v));
    EXPECT_EQ(Find(begin(v), end(v), ""), end(v));
}

TEST(IteratorsTest, find_with_set_string) {
    const std::set<std::string> v = { "21", "22", "23", "24", "25" };
    EXPECT_EQ(Find(begin(v), end(v), "23"), v.find("23"));
    EXPECT_EQ(Find(begin(v), end(v), "21"), v.find("21"));
    EXPECT_EQ(Find(begin(v), end(v), "25"), v.find("25"));

    EXPECT_EQ(Find(begin(v), end(v), "26"), end(v));
}

template <typename T>
struct IsEqualTo {
    explicit constexpr IsEqualTo(T t)
          : t_(std::move(t)) {}
    constexpr bool operator()(const T& t) const { return t_ == t; }

private:
    const T t_;
};

TEST(IteratorsTest, find_if_with_vector_int) {
    const std::vector<int> v = { 21, 22, 23, 24, 25 };
    EXPECT_EQ(FindIf(begin(v), end(v), IsEqualTo(23)), begin(v) + 2);
    EXPECT_EQ(FindIf(begin(v), end(v), IsEqualTo(21)), begin(v));
    EXPECT_EQ(FindIf(begin(v), end(v), IsEqualTo(25)), begin(v) + 4);

    EXPECT_EQ(FindIf(begin(v), end(v), IsEqualTo(20)), end(v));
}
}
}

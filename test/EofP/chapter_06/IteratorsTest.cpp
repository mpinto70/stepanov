#include "EofP/chapter_06/Iterators.h"

#include <gtest/gtest.h>

#include <vector>

namespace EofP {
namespace chapter_06 {

template <typename T>
struct Accumulator {
    void operator()(const T& t) { t_ += t; }
    T t_ = {};
};

TEST(IteratorsTest, for_each_with_vector_int) {
    const std::vector<int> v = { 21, 22, 23, 24, 25 };
    EXPECT_EQ(ForEach(begin(v), end(v), Accumulator<int>()).t_, 115);
}

TEST(IteratorsTest, for_each_with_vector_string) {
    const std::vector<std::string> v = { "21", "22", "23", "24", "25" };
    EXPECT_EQ(ForEach(begin(v), end(v), Accumulator<std::string>()).t_, "2122232425");
}

TEST(IteratorsTest, for_each_with_vector_string_reverse) {
    const std::set<std::string> v = { "21", "22", "23", "24", "25" };
    EXPECT_EQ(ForEach(rbegin(v), rend(v), Accumulator<std::string>()).t_, "2524232221");
}

TEST(IteratorsTest, for_each_with_set_string) {
    const std::set<std::string> v = { "25", "22", "24", "23", "21" };
    EXPECT_EQ(ForEach(begin(v), end(v), Accumulator<std::string>()).t_, "2122232425");
}

struct Counter {
    template <typename T>
    void operator()(const T&) { ++cnt; }
    int cnt = 0;
};

TEST(IteratorsTest, for_each_to_count_ints) {
    const std::vector<int> v = { 21, 22, 23, 24, 25 };
    EXPECT_EQ(ForEach(begin(v), end(v), Counter()).cnt, 5);
    const std::vector<int> u = { 23, 24, 25 };
    EXPECT_EQ(ForEach(begin(u), end(u), Counter()).cnt, 3);
}

TEST(IteratorsTest, for_each_to_count_strings) {
    const std::vector<std::string> v = { "21", "22", "23", "24", "25" };
    EXPECT_EQ(ForEach(begin(v), end(v), Counter()).cnt, 5);
    const std::vector<std::string> u = { "21", "22", "23", "24", "25", "" };
    EXPECT_EQ(ForEach(begin(u), end(u), Counter()).cnt, 6);
}

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

TEST(IteratorsTest, count_if_vector_int) {
    const std::vector<int> v = { 1, 2, 1, 3, 7 };
    EXPECT_EQ(CountIf(begin(v), end(v), IsEqualTo(1), 0), 2);
    EXPECT_EQ(CountIf(begin(v), end(v), IsEqualTo(2), 0), 1);
    EXPECT_EQ(CountIf(begin(v), end(v), IsEqualTo(7), 0), 1);
    EXPECT_EQ(CountIf(begin(v), end(v), IsEqualTo(8), 0), 0);

    EXPECT_EQ(CountIf(begin(v), end(v), IsEqualTo(1), 1), 3);
    EXPECT_EQ(CountIf(begin(v), end(v), IsEqualTo(2), 2), 3);
    EXPECT_EQ(CountIf(begin(v), end(v), IsEqualTo(7), 3), 4);
    EXPECT_EQ(CountIf(begin(v), end(v), IsEqualTo(8), 4), 4);
}

template <typename I>
int CountDigits(I i) {
    int val = *i;
    int res = 0;
    while (val != 0) {
        val /= 10;
        ++res;
    }
    return res;
}

int Accumulate(int base, int increment) {
    return base + increment;
}

TEST(IteratorsTest, reduce_non_zero_count_digits) {
    const std::vector<int> v = { 21, 2, 123 };
    EXPECT_EQ(ReduceNonEmpty(begin(v), end(v), Accumulate, CountDigits<std::vector<int>::const_iterator>), 6);
    const std::vector<int> u = { 1234, 56789 };
    EXPECT_EQ(ReduceNonEmpty(begin(u), end(u), Accumulate, CountDigits<std::vector<int>::const_iterator>), 9);
}

TEST(IteratorsTest, reduce_count_digits) {
    const std::vector<int> v = { 21, 2, 123 };
    EXPECT_EQ(Reduce(begin(v), end(v), Accumulate, CountDigits<std::vector<int>::const_iterator>, 0), 6);
    const std::vector<int> u = { 1234, 56789 };
    EXPECT_EQ(Reduce(begin(u), end(u), Accumulate, CountDigits<std::vector<int>::const_iterator>, 0), 9);
    const std::vector<int> empty;
    EXPECT_EQ(Reduce(begin(empty), end(empty), Accumulate, CountDigits<std::vector<int>::const_iterator>, -7), -7);
}

TEST(IteratorsTest, find_mismatch_int_equal_to_float) {
    const std::vector<int> v0 = { 21, 2, 123 };
    const std::vector<float> v1 = { 21, 2, 124 };
    auto relation = [](int x, float y) { return static_cast<float>(x) == y; };
    const auto expected = std::make_pair(begin(v0) + 2, begin(v1) + 2);
    EXPECT_EQ(FindMismatch(begin(v0), end(v0), begin(v1), end(v1), relation), expected);
}

TEST(IteratorsTest, find_mismatch_int_greater_than_float) {
    const std::vector<int> v0 = { 5, 7, 9, 12 };
    const std::vector<float> v1 = { 4.999, 6.999, 8.999, 12 };
    auto relation = [](int x, float y) { return static_cast<float>(x) > y; };
    const auto expected = std::make_pair(begin(v0) + 3, begin(v1) + 3);
    EXPECT_EQ(FindMismatch(begin(v0), end(v0), begin(v1), end(v1), relation), expected);
}

TEST(IteratorsTest, find_adjacent_mismatch_increase) {
    const std::vector<int> v = { 5, 7, 9, 9 };
    auto relation = [](int x, int y) { return x < y; };
    const auto expected = begin(v) + 3;
    EXPECT_EQ(FindAdjacentMismatch(begin(v), end(v), relation), expected);
}

TEST(IteratorsTest, find_adjacent_mismatch_increase_not_found) {
    const std::vector<int> v = { 5, 7, 9, 10 };
    auto relation = [](int x, int y) { return x < y; };
    const auto expected = end(v);
    EXPECT_EQ(FindAdjacentMismatch(begin(v), end(v), relation), expected);
}
}
}

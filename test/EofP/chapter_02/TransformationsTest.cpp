#include "EofP/chapter_02/Transformations.h"

#include <gtest/gtest.h>

#include <functional>
#include <random>

namespace EofP {
namespace chapter_02 {

TEST(TransformationTest, abs) {
    EXPECT_EQ(abs(2.3), 2.3);
    EXPECT_EQ(abs(-2.3), 2.3);
    EXPECT_EQ(abs(78), 78);
    EXPECT_EQ(abs(-78), 78);
}

TEST(TransformationTest, euclidean_norm_2) {
    EXPECT_EQ(euclidean_norm(3.0, 4.0), 5.0);
}

TEST(TransformationTest, euclidean_norm_3) {
    EXPECT_EQ(euclidean_norm(3.0, 4.0, 5.0), std::sqrt(50.0));
}

namespace {
double generate() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(-1000.0, 1000.0);
    return dis(gen);
}
}

TEST(TransformationTest, lemma_2_1) {
    for (size_t i = 0; i < 10000; ++i) {
        const auto x = generate();
        const auto y = generate();
        const auto z = generate();
        const auto e_xyz = euclidean_norm(x, y, z);
        const auto e_xy = euclidean_norm(x, y);
        const auto e_xz = euclidean_norm(x, z);
        const auto e_yz = euclidean_norm(y, z);
        const std::string msg = std::to_string(x) + " / " + std::to_string(y) + " / " + std::to_string(z);
        EXPECT_DOUBLE_EQ(e_xyz, euclidean_norm(e_xy, z)) << msg;
        EXPECT_DOUBLE_EQ(e_xyz, euclidean_norm(e_xz, y)) << msg;
        EXPECT_DOUBLE_EQ(e_xyz, euclidean_norm(e_yz, x)) << msg;
    }
}
}
}

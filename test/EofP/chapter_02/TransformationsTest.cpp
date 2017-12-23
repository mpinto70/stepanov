#include "EofP/chapter_02/Transformations.h"

#include <gtest/gtest.h>

namespace EofP {
namespace chapter_02 {

TEST(TransformationTest, abs) {
    EXPECT_EQ(abs(2.3), 2.3);
    EXPECT_EQ(abs(-2.3), 2.3);
}

TEST(TransformationTest, euclidean_norm_2) {
    EXPECT_EQ(euclidean_norm(3.0, 4.0), 5.0);
}

TEST(TransformationTest, euclidean_norm_3) {
    EXPECT_EQ(euclidean_norm(3.0, 4.0, 5.0), std::sqrt(50.0));
}

}
}

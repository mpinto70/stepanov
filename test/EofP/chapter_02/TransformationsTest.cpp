#include "EofP/chapter_02/Transformations.h"

#include <gtest/gtest.h>

namespace EofP {
namespace chapter_02 {

TEST(TransformationTest, abs) {
    EXPECT_EQ(abs(2.3), 2.3);
    EXPECT_EQ(abs(-2.3), 2.3);

}

}
}

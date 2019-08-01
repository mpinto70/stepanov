#include "EofP/chapter_06/Iterators.h"

#include <gtest/gtest.h>

#include <EofP/chapter_07/CoordinateStructures.h>
#include <vector>

namespace EofP {

TEST(CoordinateStructuresTest, build_empty_tree_string) {
    using bc = BifurcateCoordinate<BinaryNode<std::string>>;
    const BinaryNode<std::string> root("root string");

    EXPECT_TRUE(bc::empty(root));
    EXPECT_FALSE(bc::HasLeftSuccessor(root));
    EXPECT_FALSE(bc::HasRightSuccessor(root));

    EXPECT_EQ(*root, "root string");
}

TEST(CoordinateStructuresTest, build_empty_tree_int) {
    using bc = BifurcateCoordinate<BinaryNode<int>>;
    const BinaryNode<int> root(1);

    EXPECT_TRUE(bc::empty(root));
    EXPECT_FALSE(bc::HasLeftSuccessor(root));
    EXPECT_FALSE(bc::HasRightSuccessor(root));

    EXPECT_EQ(*root, 1);
}

TEST(CoordinateStructuresTest, build_tree_1_level_string) {
    using bc = BifurcateCoordinate<BinaryNode<std::string>>;
    BinaryNode<std::string> root("root string");

    bc::AddLeftSuccessor(root, "left 1");
    bc::AddRightSuccessor(root, "right 1");

    EXPECT_FALSE(bc::empty(root));
    EXPECT_TRUE(bc::HasLeftSuccessor(root));
    EXPECT_TRUE(bc::HasRightSuccessor(root));

    EXPECT_EQ(*root, "root string");
    EXPECT_EQ(*bc::LefgSuccessor(root), "left 1");
    EXPECT_EQ(*bc::RightSuccessor(root), "right 1");
}

TEST(CoordinateStructuresTest, build_tree_1_level_int) {
    using bc = BifurcateCoordinate<BinaryNode<int>>;
    BinaryNode<int> root(1);

    bc::AddLeftSuccessor(root, 2);
    bc::AddRightSuccessor(root, 3);

    EXPECT_FALSE(bc::empty(root));
    EXPECT_TRUE(bc::HasLeftSuccessor(root));
    EXPECT_TRUE(bc::HasRightSuccessor(root));

    EXPECT_EQ(*root, 1);
    EXPECT_EQ(*bc::LefgSuccessor(root), 2);
    EXPECT_EQ(*bc::RightSuccessor(root), 3);
}

TEST(CoordinateStructuresTest, weight_recursive_for_empty) {
    const BinaryNode<std::string> root("root string");

    EXPECT_EQ(WeightRecursive(root), 0);
}

TEST(CoordinateStructuresTest, weight_recursive_for_1_level_right) {
    using bc = BifurcateCoordinate<BinaryNode<std::string>>;
    BinaryNode<std::string> root("root string");

    bc::AddRightSuccessor(root, "right 1");

    EXPECT_EQ(WeightRecursive(root), 1);
}

TEST(CoordinateStructuresTest, weight_recursive_for_1_level_left_right) {
    using bc = BifurcateCoordinate<BinaryNode<std::string>>;
    BinaryNode<std::string> root("root string");

    bc::AddLeftSuccessor(root, "left 1");
    bc::AddRightSuccessor(root, "right 1");

    EXPECT_EQ(WeightRecursive(root), 1);
}

TEST(CoordinateStructuresTest, weight_recursive_for_2_levels) {
    using bc = BifurcateCoordinate<BinaryNode<std::string>>;
    BinaryNode<std::string> root("root string");

    auto& l = bc::AddLeftSuccessor(root, "l");
    auto& r = bc::AddRightSuccessor(root, "r");

    bc::AddLeftSuccessor(l, "l l");
    bc::AddRightSuccessor(l, "l r");
    bc::AddLeftSuccessor(r, "r l");
    bc::AddRightSuccessor(r, "r r");

    EXPECT_EQ(WeightRecursive(root), 3);
}
}

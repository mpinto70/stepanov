#include "EofP/chapter_06/Iterators.h"

#include <gtest/gtest.h>

#include <EofP/chapter_07/CoordinateStructures.h>
#include <vector>

namespace EofP {

TEST(CoordinateStructuresTest, build_empty_tree_string) {
    using bc = BifurcateCoordinate<BinaryNode<std::string>>;
    const BinaryNode<std::string> root("root string");

    EXPECT_TRUE(bc::empty(root));
    EXPECT_FALSE(bc::has_left_successor(root));
    EXPECT_FALSE(bc::has_right_successor(root));

    EXPECT_EQ(*root, "root string");
}

TEST(CoordinateStructuresTest, build_empty_tree_int) {
    using bc = BifurcateCoordinate<BinaryNode<int>>;
    const BinaryNode<int> root(1);

    EXPECT_TRUE(bc::empty(root));
    EXPECT_FALSE(bc::has_left_successor(root));
    EXPECT_FALSE(bc::has_right_successor(root));

    EXPECT_EQ(*root, 1);
}

TEST(CoordinateStructuresTest, build_tree_1_level_string) {
    using bc = BifurcateCoordinate<BinaryNode<std::string>>;
    BinaryNode<std::string> root("root string");

    bc::add_left_successor(root, "left 1");
    bc::add_right_successor(root, "right 1");

    EXPECT_FALSE(bc::empty(root));
    EXPECT_TRUE(bc::has_left_successor(root));
    EXPECT_TRUE(bc::has_right_successor(root));

    EXPECT_EQ(*root, "root string");
    EXPECT_EQ(*bc::left_successor(root), "left 1");
    EXPECT_EQ(*bc::right_successor(root), "right 1");
}

TEST(CoordinateStructuresTest, build_tree_1_level_int) {
    using bc = BifurcateCoordinate<BinaryNode<int>>;
    BinaryNode<int> root(1);

    bc::add_left_successor(root, 2);
    bc::add_right_successor(root, 3);

    EXPECT_FALSE(bc::empty(root));
    EXPECT_TRUE(bc::has_left_successor(root));
    EXPECT_TRUE(bc::has_right_successor(root));

    EXPECT_EQ(*root, 1);
    EXPECT_EQ(*bc::left_successor(root), 2);
    EXPECT_EQ(*bc::right_successor(root), 3);
}

TEST(CoordinateStructuresTest, weight_recursive_for_empty) {
    const BinaryNode<std::string> root("root string");

    EXPECT_EQ(WeightRecursive(root), 0);
}

TEST(CoordinateStructuresTest, weight_recursive_for_1_level_right) {
    using bc = BifurcateCoordinate<BinaryNode<std::string>>;
    BinaryNode<std::string> root("root string");

    bc::add_right_successor(root, "right 1");

    EXPECT_EQ(WeightRecursive(root), 1);
}

TEST(CoordinateStructuresTest, weight_recursive_for_1_level_left_right) {
    using bc = BifurcateCoordinate<BinaryNode<std::string>>;
    BinaryNode<std::string> root("root string");

    bc::add_right_successor(root, "right 1");
    bc::add_left_successor(root, "left 1");

    EXPECT_EQ(WeightRecursive(root), 1);
}
}

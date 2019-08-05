#include "EofP/chapter_07/CoordinateStructures.h"
#include "EofP/chapter_06/Iterators.h"

#include <gtest/gtest.h>

#include <vector>

namespace EofP {

TEST(BifurcateCoordinateTest, build_empty_tree_string) {
    using bc = BifurcateCoordinate<BinaryNode<std::string>>;
    const BinaryNode<std::string> root("root string");

    EXPECT_TRUE(bc::empty(root));
    EXPECT_FALSE(bc::HasLeftSuccessor(root));
    EXPECT_FALSE(bc::HasRightSuccessor(root));

    EXPECT_EQ(*root, "root string");
}

TEST(BifurcateCoordinateTest, build_empty_tree_int) {
    using bc = BifurcateCoordinate<BinaryNode<int>>;
    const BinaryNode<int> root(1);

    EXPECT_TRUE(bc::empty(root));
    EXPECT_FALSE(bc::HasLeftSuccessor(root));
    EXPECT_FALSE(bc::HasRightSuccessor(root));

    EXPECT_EQ(*root, 1);
}

TEST(BifurcateCoordinateTest, build_tree_1_level_string) {
    using bc = BifurcateCoordinate<BinaryNode<std::string>>;
    BinaryNode<std::string> root("root string");

    bc::AddLeftSuccessor(root, "left 1");
    bc::AddRightSuccessor(root, "right 1");

    EXPECT_FALSE(bc::empty(root));
    EXPECT_TRUE(bc::HasLeftSuccessor(root));
    EXPECT_TRUE(bc::HasRightSuccessor(root));

    EXPECT_EQ(*root, "root string");
    EXPECT_EQ(*bc::LeftSuccessor(root), "left 1");
    EXPECT_EQ(*bc::RightSuccessor(root), "right 1");
}

TEST(BifurcateCoordinateTest, build_tree_1_level_int) {
    using bc = BifurcateCoordinate<BinaryNode<int>>;
    BinaryNode<int> root(1);

    bc::AddLeftSuccessor(root, 2);
    bc::AddRightSuccessor(root, 3);

    EXPECT_FALSE(bc::empty(root));
    EXPECT_TRUE(bc::HasLeftSuccessor(root));
    EXPECT_TRUE(bc::HasRightSuccessor(root));

    EXPECT_EQ(*root, 1);
    EXPECT_EQ(*bc::LeftSuccessor(root), 2);
    EXPECT_EQ(*bc::RightSuccessor(root), 3);
}

TEST(BifurcateCoordinateTest, weight_and_height_recursive_for_empty) {
    const BinaryNode<std::string> root("root string");

    EXPECT_EQ(WeightRecursive(root), 0);
    EXPECT_EQ(HeightRecursive(root), 0);
}

TEST(BifurcateCoordinateTest, weight_and_height_recursive_for_1_level_right) {
    using bc = BifurcateCoordinate<BinaryNode<std::string>>;
    BinaryNode<std::string> root("root string");

    bc::AddRightSuccessor(root, "right 1");

    EXPECT_EQ(WeightRecursive(root), 1);
    EXPECT_EQ(HeightRecursive(root), 1);
}

TEST(BifurcateCoordinateTest, weight_and_height_recursive_for_1_level_left_right) {
    using bc = BifurcateCoordinate<BinaryNode<std::string>>;
    BinaryNode<std::string> root("root string");

    bc::AddLeftSuccessor(root, "left 1");
    bc::AddRightSuccessor(root, "right 1");

    EXPECT_EQ(WeightRecursive(root), 1);
    EXPECT_EQ(HeightRecursive(root), 1);
}

TEST(BifurcateCoordinateTest, weight_and_height_recursive_for_2_levels) {
    using bc = BifurcateCoordinate<BinaryNode<std::string>>;
    BinaryNode<std::string> root("root string");

    auto& l = bc::AddLeftSuccessor(root, "l");
    auto& r = bc::AddRightSuccessor(root, "r");

    bc::AddLeftSuccessor(l, "l l");
    bc::AddRightSuccessor(l, "l r");
    bc::AddLeftSuccessor(r, "r l");
    bc::AddRightSuccessor(r, "r r");

    EXPECT_EQ(WeightRecursive(root), 3);
    EXPECT_EQ(HeightRecursive(root), 2);
}

template <typename Node>
struct VisitCounter {
    void operator()(Visit visit, const Node& t) {
        count[*t].push_back(visit);
    }
    std::map<typename Node::Type, std::vector<Visit>> count;
};

TEST(BifurcateCoordinateTest, traverse_nonempty_counting_int) {
    using bc = BifurcateCoordinate<BinaryNode<int>>;
    BinaryNode<int> root(0);

    auto& l = bc::AddLeftSuccessor(root, 1);
    auto& r = bc::AddRightSuccessor(root, 2);

    bc::AddLeftSuccessor(l, 11);
    bc::AddRightSuccessor(l, 12);
    bc::AddLeftSuccessor(r, 21);
    bc::AddRightSuccessor(r, 22);

    auto proc = TraverseNonempty(root, VisitCounter<BinaryNode<int>>());
    EXPECT_EQ(proc.count.size(), 7);
    const std::vector<Visit> expected_visits = { Visit::PRE, Visit::IN, Visit::POST };
    for (const auto& it : proc.count) {
        EXPECT_EQ(it.second.size(), 3) << it.first;
        EXPECT_EQ(it.second, expected_visits);
    }
    EXPECT_NE(proc.count.find(0), proc.count.end());
    EXPECT_NE(proc.count.find(1), proc.count.end());
    EXPECT_NE(proc.count.find(2), proc.count.end());
    EXPECT_NE(proc.count.find(11), proc.count.end());
    EXPECT_NE(proc.count.find(12), proc.count.end());
    EXPECT_NE(proc.count.find(21), proc.count.end());
    EXPECT_NE(proc.count.find(22), proc.count.end());
}

TEST(BifurcateCoordinateTest, traverse_nonempty_counting_strings) {
    using bc = BifurcateCoordinate<BinaryNode<std::string>>;
    BinaryNode<std::string> root("root string");

    auto& l = bc::AddLeftSuccessor(root, "l");
    auto& r = bc::AddRightSuccessor(root, "r");

    bc::AddLeftSuccessor(l, "l l");
    bc::AddRightSuccessor(l, "l r");
    bc::AddLeftSuccessor(r, "r l");
    bc::AddRightSuccessor(r, "r r");

    auto proc = TraverseNonempty(root, VisitCounter<BinaryNode<std::string>>());
    EXPECT_EQ(proc.count.size(), 7);
    const std::vector<Visit> expected_visits = { Visit::PRE, Visit::IN, Visit::POST };
    for (const auto& it : proc.count) {
        EXPECT_EQ(it.second.size(), 3) << it.first;
        EXPECT_EQ(it.second, expected_visits);
    }
    EXPECT_NE(proc.count.find("root string"), proc.count.end());
    EXPECT_NE(proc.count.find("l"), proc.count.end());
    EXPECT_NE(proc.count.find("r"), proc.count.end());
    EXPECT_NE(proc.count.find("l r"), proc.count.end());
    EXPECT_NE(proc.count.find("l l"), proc.count.end());
    EXPECT_NE(proc.count.find("r l"), proc.count.end());
    EXPECT_NE(proc.count.find("r r"), proc.count.end());
}

TEST(BidirectionalBifurcateCoordinateTest, build_tree_2_levels_string) {
    using bc = BidirectionalBifurcateCoordinate<BidirectionalBinaryNode<std::string>>;
    BidirectionalBinaryNode<std::string> root("root string");

    bc::AddLeftSuccessor(root, "left 1");
    bc::AddRightSuccessor(root, "right 1");

    EXPECT_FALSE(bc::empty(root));
    EXPECT_TRUE(bc::HasLeftSuccessor(root));
    EXPECT_TRUE(bc::HasRightSuccessor(root));

    ASSERT_TRUE(bc::HasPredecessor(bc::LeftSuccessor(root)));
    EXPECT_TRUE(bc::IsLeftSuccessor(bc::LeftSuccessor(root)));
    ASSERT_TRUE(bc::HasPredecessor(bc::RightSuccessor(root)));
    EXPECT_TRUE(bc::IsRightSuccessor(bc::RightSuccessor(root)));
}
}

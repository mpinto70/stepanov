#include "EofP/chapter_07/CoordinateStructures.h"
#include "EofP/chapter_06/Iterators.h"

#include <gtest/gtest.h>

#include <vector>

namespace EofP {

TEST(BifurcateCoordinateTest, build_empty_tree) {
    const BifurcateCoordinate<std::string> s;
    EXPECT_TRUE(s.Empty());

    const BifurcateCoordinate<int> i;
    EXPECT_TRUE(i.Empty());
}

TEST(BifurcateCoordinateTest, build_tree_string_one_element) {
    BinaryNode<std::string> root("root string");
    const BifurcateCoordinate<std::string> i(root);

    EXPECT_FALSE(i.Empty());
    EXPECT_FALSE(i.HasLeftSuccessor());
    EXPECT_FALSE(i.HasRightSuccessor());

    EXPECT_EQ(*i, "root string");
}

TEST(BifurcateCoordinateTest, build_tree_int_one_element) {
    BinaryNode<int> root(42);
    const BifurcateCoordinate<int> i(root);

    EXPECT_FALSE(i.Empty());
    EXPECT_FALSE(i.HasLeftSuccessor());
    EXPECT_FALSE(i.HasRightSuccessor());

    EXPECT_EQ(*i, 42);
}

TEST(BifurcateCoordinateTest, build_tree_1_level_string) {
    BinaryNode<std::string> root("root string");
    const BifurcateCoordinate<std::string> i(root);

    root.AddLeftSuccessor("left 1");
    root.AddRightSuccessor("right 1");

    EXPECT_FALSE(i.Empty());
    EXPECT_TRUE(i.HasLeftSuccessor());
    EXPECT_TRUE(i.HasRightSuccessor());

    EXPECT_EQ(*i, "root string");
    EXPECT_EQ(*i.LeftSuccessor(), "left 1");
    EXPECT_EQ(*i.RightSuccessor(), "right 1");
}

TEST(BifurcateCoordinateTest, build_tree_1_level_int) {
    BinaryNode<int> root(42);
    const BifurcateCoordinate<int> i(root);

    root.AddLeftSuccessor(51);
    root.AddRightSuccessor(69);

    EXPECT_FALSE(i.Empty());
    EXPECT_TRUE(i.HasLeftSuccessor());
    EXPECT_TRUE(i.HasRightSuccessor());

    EXPECT_EQ(*i, 42);
    EXPECT_EQ(*i.LeftSuccessor(), 51);
    EXPECT_EQ(*i.RightSuccessor(), 69);
}

TEST(BifurcateCoordinateTest, weight_and_height_recursive_for_empty) {
    const BifurcateCoordinate<std::string> i;

    EXPECT_EQ(WeightRecursive(i), 0);
    EXPECT_EQ(HeightRecursive(i), 0);
}

TEST(BifurcateCoordinateTest, weight_and_height_recursive_for_1_level) {
    BinaryNode<std::string> root("root string");
    const BifurcateCoordinate<std::string> i(root);

    EXPECT_EQ(WeightRecursive(i), 1);
    EXPECT_EQ(HeightRecursive(i), 1);
}

TEST(BifurcateCoordinateTest, weight_and_height_recursive_for_2_levels_right) {
    BinaryNode<std::string> root("root string");
    const BifurcateCoordinate<std::string> i(root);

    root.AddRightSuccessor("right 1");

    EXPECT_EQ(WeightRecursive(i), 2);
    EXPECT_EQ(HeightRecursive(i), 2);
}

TEST(BifurcateCoordinateTest, weight_and_height_recursive_for_1_level_left_right) {
    BinaryNode<std::string> root("root string");
    const BifurcateCoordinate<std::string> i(root);

    root.AddLeftSuccessor("left 1");
    root.AddRightSuccessor("right 1");

    EXPECT_EQ(WeightRecursive(i), 3);
    EXPECT_EQ(HeightRecursive(i), 2);
}

TEST(BifurcateCoordinateTest, weight_and_height_recursive_for_2_levels) {
    BinaryNode<std::string> root("root string");
    const BifurcateCoordinate<std::string> i(root);

    auto& l = root.AddLeftSuccessor("l");
    auto& r = root.AddRightSuccessor("r");

    l.AddLeftSuccessor("l l");
    l.AddRightSuccessor("l r");
    r.AddLeftSuccessor("r l");
    r.AddRightSuccessor("r r");

    EXPECT_EQ(WeightRecursive(i), 7);
    EXPECT_EQ(HeightRecursive(i), 3);
}

template <typename I>
struct VisitCounter {
    void operator()(Visit visit, I t) {
        count[*t].push_back(visit);
    }
    std::map<typename I::Type, std::vector<Visit>> count;
};

TEST(BifurcateCoordinateTest, traverse_nonempty_counting_int) {
    BinaryNode<int> root(0);
    const BifurcateCoordinate<int> i(root);

    auto& l = root.AddLeftSuccessor(1);
    auto& r = root.AddRightSuccessor(2);

    l.AddLeftSuccessor(11);
    l.AddRightSuccessor(12);
    r.AddLeftSuccessor(21);
    r.AddRightSuccessor(22);

    auto proc = TraverseNonempty(i, VisitCounter<BifurcateCoordinate<int>>());
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
    BinaryNode<std::string> root("root string");
    const BifurcateCoordinate<std::string> i(root);

    auto& l = root.AddLeftSuccessor("l");
    auto& r = root.AddRightSuccessor("r");

    l.AddLeftSuccessor("l l");
    l.AddRightSuccessor("l r");
    r.AddLeftSuccessor("r l");
    r.AddRightSuccessor("r r");

    auto proc = TraverseNonempty(i, VisitCounter<BifurcateCoordinate<std::string>>());
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
    BidirectionalBinaryNode<std::string> root("root string");
    const BidirectionalBifurcateCoordinate<std::string> i(root);

    root.AddLeftSuccessor("left 1");
    root.AddRightSuccessor("right 1");

    EXPECT_FALSE(i.Empty());
    EXPECT_TRUE(i.HasLeftSuccessor());
    EXPECT_TRUE(i.HasRightSuccessor());

    EXPECT_FALSE(i.HasPredecessor());
    EXPECT_TRUE(i.LeftSuccessor().HasPredecessor());
    EXPECT_TRUE(i.LeftSuccessor().IsLeftSuccessor());
    EXPECT_TRUE(i.RightSuccessor().HasPredecessor());
    EXPECT_TRUE(i.RightSuccessor().IsRightSuccessor());

    EXPECT_FALSE(i.LeftSuccessor().IsRightSuccessor());
    EXPECT_FALSE(i.RightSuccessor().IsLeftSuccessor());
}

TEST(BidirectionalBifurcateCoordinateTest, traverse_step_string) {
    BidirectionalBinaryNode<std::string> root("root string");
    BidirectionalBifurcateCoordinate<std::string> i(root);

    root.AddLeftSuccessor("left 1");
    root.AddRightSuccessor("right 1");

    Visit v = Visit::PRE;

    EXPECT_EQ(*i, "root string");

    EXPECT_EQ(TraverseStep(v, i), 1);
    EXPECT_EQ(*i, "left 1");
    EXPECT_EQ(v, Visit::PRE);

    EXPECT_EQ(TraverseStep(v, i), 0);
    EXPECT_EQ(*i, "left 1");
    EXPECT_EQ(v, Visit::IN);

    EXPECT_EQ(TraverseStep(v, i), 0);
    EXPECT_EQ(*i, "left 1");
    EXPECT_EQ(v, Visit::POST);

    EXPECT_EQ(TraverseStep(v, i), -1);
    EXPECT_EQ(*i, "root string");
    EXPECT_EQ(v, Visit::IN);

    EXPECT_EQ(TraverseStep(v, i), 1);
    EXPECT_EQ(*i, "right 1");
    EXPECT_EQ(v, Visit::PRE);

    EXPECT_EQ(TraverseStep(v, i), 0);
    EXPECT_EQ(*i, "right 1");
    EXPECT_EQ(v, Visit::IN);

    EXPECT_EQ(TraverseStep(v, i), 0);
    EXPECT_EQ(*i, "right 1");
    EXPECT_EQ(v, Visit::POST);

    EXPECT_EQ(TraverseStep(v, i), -1);
    EXPECT_EQ(*i, "root string");
    EXPECT_EQ(v, Visit::POST);
}

namespace {
BidirectionalBinaryNode<std::string> create_tree(const std::string& name = "") {
    BidirectionalBinaryNode<std::string> root(name + " root");
    auto& l = root.AddLeftSuccessor(name + " l");
    auto& r = root.AddRightSuccessor(name + " r");

    l.AddLeftSuccessor(name + " l l");
    l.AddRightSuccessor(name + " l r");
    r.AddLeftSuccessor(name + " r l");
    r.AddRightSuccessor(name + " r r");

    return root;
}
}

TEST(BidirectionalBifurcateCoordinateTest, reachable_same_tree) {
    BidirectionalBinaryNode<std::string> root = create_tree();
    BidirectionalBifurcateCoordinate<std::string> iroot(root);

    auto x = iroot;
    Visit v = Visit::PRE;
    while (v != Visit::POST || x != iroot) {
        TraverseStep(v, x);
        EXPECT_TRUE(Reachable(iroot, x)) << *iroot << " --> " << *x;
        EXPECT_EQ(Reachable(x, iroot), x == iroot) << *x << " --> " << *iroot;
    }
}

TEST(BidirectionalBifurcateCoordinateTest, reachable_empty) {
    BidirectionalBinaryNode<std::string> root = create_tree();
    BidirectionalBifurcateCoordinate<std::string> iroot(root);
    BidirectionalBifurcateCoordinate<std::string> empty;

    EXPECT_FALSE(Reachable(iroot, empty));
    EXPECT_FALSE(Reachable(empty, iroot));
}

namespace {
template <typename I>
void check_unreachable(I i1, I i2) {
    auto x = i1;
    Visit v = Visit::PRE;
    while (v != Visit::POST || x != i1) {
        TraverseStep(v, x);
        EXPECT_FALSE(Reachable(i2, x)) << *i2 << " --> " << *x;
        EXPECT_FALSE(Reachable(x, i2)) << *x << " --> " << *i2;
    }
}
}

TEST(BidirectionalBifurcateCoordinateTest, reachable_different_tree) {
    BidirectionalBinaryNode<std::string> root1 = create_tree("1");
    BidirectionalBinaryNode<std::string> root2 = create_tree("2");
    BidirectionalBifurcateCoordinate<std::string> iroot1(root1);
    BidirectionalBifurcateCoordinate<std::string> iroot2(root2);

    EXPECT_FALSE(Reachable(iroot1, iroot2));
    EXPECT_FALSE(Reachable(iroot2, iroot1));

    check_unreachable(iroot1, iroot2);
    check_unreachable(iroot2, iroot1);
}
}

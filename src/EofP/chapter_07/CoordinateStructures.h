#pragma once

#include <algorithm>
#include <iterator>
#include <memory>

namespace EofP {

// Section 7.1

template <typename T>
struct BifurcateCoordinate;

template <typename T>
struct BinaryNode {
    using Type = T;
    explicit BinaryNode(T t)
          : value(std::move(t)) {}
    T& operator*() {
        return value;
    }
    const T& operator*() const {
        return value;
    }

private:
    T value;
    std::unique_ptr<BinaryNode<T>> left;
    std::unique_ptr<BinaryNode<T>> right;

    friend class BifurcateCoordinate<BinaryNode<T>>;
};

template <typename Node>
struct BifurcateCoordinate {
    static bool empty(const Node& node) {
        return not HasLeftSuccessor(node) && not HasRightSuccessor(node);
    }
    static bool HasLeftSuccessor(const Node& node) {
        return node.left != nullptr;
    }
    static bool HasRightSuccessor(const Node& node) {
        return node.right != nullptr;
    }
    static const Node& LeftSuccessor(const Node& node) {
        return *node.left;
    }
    static const Node& RightSuccessor(const Node& node) {
        return *node.right;
    }
    static Node& LefgSuccessor(Node& node) {
        return *node.left;
    }
    static Node& RightSuccessor(Node& node) {
        return *node.right;
    }
    static Node& AddLeftSuccessor(Node& node, typename Node::Type value) {
        node.left = std::make_unique<Node>(std::move(value));
        return *node.left;
    }
    static Node& AddRightSuccessor(Node& node, typename Node::Type value) {
        node.right = std::make_unique<Node>(std::move(value));
        return *node.right;
    }
};

template <typename Node>
int WeightRecursive(const Node& node) {
    using BC = BifurcateCoordinate<Node>;

    if (BC::empty(node))
        return 0;

    int l = 0;
    int r = 0;
    if (BC::HasLeftSuccessor(node))
        l = WeightRecursive(BC::LeftSuccessor(node));
    if (BC::HasRightSuccessor(node))
        r = WeightRecursive(BC::RightSuccessor(node));

    return l + r + 1;
}

template <typename Node>
int HeightRecursive(const Node& node) {
    using BC = BifurcateCoordinate<Node>;

    if (BC::empty(node))
        return 0;

    int l = 0;
    int r = 0;
    if (BC::HasLeftSuccessor(node))
        l = HeightRecursive(BC::LeftSuccessor(node));
    if (BC::HasRightSuccessor(node))
        r = HeightRecursive(BC::RightSuccessor(node));

    return std::max(l, r) + 1;
}

enum class Visit {
    PRE,
    IN,
    POST
};

template <typename Node, typename Proc>
Proc TraverseNonempty(const Node& node, Proc proc) {
    using BC = BifurcateCoordinate<Node>;

    proc(Visit::PRE, node);
    if (BC::HasLeftSuccessor(node))
        proc = TraverseNonempty(BC::LeftSuccessor(node), proc);
    proc(Visit::IN, node);
    if (BC::HasRightSuccessor(node))
        proc = TraverseNonempty(BC::RightSuccessor(node), proc);
    proc(Visit::POST, node);

    return proc;
}
}

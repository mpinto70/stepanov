#pragma once

#include <algorithm>
#include <iterator>
#include <memory>
#include <utility>

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
    static Node& LeftSuccessor(Node& node) {
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

// Section 7.2

template <typename T>
struct BidirectionalBifurcateCoordinate;

template <typename T>
struct BidirectionalBinaryNode {
    using Type = T;
    explicit BidirectionalBinaryNode(T t)
          : value(std::move(t)), predecessor(nullptr) {}
    T& operator*() {
        return value;
    }
    const T& operator*() const {
        return value;
    }

private:
    T value;
    std::unique_ptr<BidirectionalBinaryNode<T>> left;
    std::unique_ptr<BidirectionalBinaryNode<T>> right;
    BidirectionalBinaryNode<T>* predecessor;

    friend class BidirectionalBifurcateCoordinate<BidirectionalBinaryNode<T>>;
    friend class BifurcateCoordinate<BidirectionalBinaryNode<T>>;
};

template <typename Node>
struct BidirectionalBifurcateCoordinate : public BifurcateCoordinate<Node> {
    static Node& AddLeftSuccessor(Node& node, typename Node::Type value) {
        using BASE = BifurcateCoordinate<Node>;
        auto& new_node = BASE::AddLeftSuccessor(node, value);
        new_node.predecessor = &node;
        return new_node;
    }
    static Node& AddRightSuccessor(Node& node, typename Node::Type value) {
        using BASE = BifurcateCoordinate<Node>;
        auto& new_node = BASE::AddRightSuccessor(node, value);
        new_node.predecessor = &node;
        return new_node;
    }
    static bool HasPredecessor(const Node& node) {
        return node.predecessor != nullptr;
    }
    static bool IsLeftSuccessor(const Node& node) {
        using BASE = BifurcateCoordinate<Node>;
        const Node* i = node.predecessor;
        return BASE::HasLeftSuccessor(*i) && &BASE::LeftSuccessor(*i) == &node;
    }
    static bool IsRightSuccessor(const Node& node) {
        using BASE = BifurcateCoordinate<Node>;
        const Node* i = node.predecessor;
        return BASE::HasRightSuccessor(*i) && &BASE::RightSuccessor(*i) == &node;
    }
};
}

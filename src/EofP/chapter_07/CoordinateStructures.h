#pragma once

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
        return not has_left_successor(node) && not has_right_successor(node);
    }
    static bool has_left_successor(const Node& node) {
        return node.left != nullptr;
    }
    static bool has_right_successor(const Node& node) {
        return node.right != nullptr;
    }
    static const Node& left_successor(const Node& node) {
        return *node.left;
    }
    static const Node& right_successor(const Node& node) {
        return *node.right;
    }
    static Node& left_successor(Node& node) {
        return *node.left;
    }
    static Node& right_successor(Node& node) {
        return *node.right;
    }
    static void add_left_successor(Node& node, typename Node::Type value) {
        node.left = std::make_unique<Node>(std::move(value));
    }
    static void add_right_successor(Node& node, typename Node::Type value) {
        node.right = std::make_unique<Node>(std::move(value));
    }
};

template <typename Node>
int WeightRecursive(const Node& node) {
    using BC = BifurcateCoordinate<Node>;

    if (BC::empty(node))
        return 0;

    int l = 0;
    int r = 0;
    if (BC::has_left_successor(node))
        l = WeightRecursive(BC::left_successor(node));
    if (BC::has_right_successor(node))
        r = WeightRecursive(BC::right_successor(node));

    return l + r + 1;
}
}

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
    BinaryNode& AddLeftSuccessor(T t) {
        left = std::make_unique<BinaryNode>(std::move(t));
        return *left;
    }
    BinaryNode& AddRightSuccessor(T t) {
        right = std::make_unique<BinaryNode>(std::move(t));
        return *right;
    }

private:
    T value;
    std::unique_ptr<BinaryNode<T>> left;
    std::unique_ptr<BinaryNode<T>> right;

    friend class BifurcateCoordinate<T>;
};

template <typename T>
struct BifurcateCoordinate {
    using Node = BinaryNode<T>;
    using Type = T;
    BifurcateCoordinate()
          : node_(nullptr) {}
    explicit BifurcateCoordinate(Node& node)
          : node_(&node) {}
    T& operator*() const {
        return node_->value;
    }
    [[nodiscard]] bool Empty() const {
        return node_ == nullptr;
    }
    [[nodiscard]] bool HasLeftSuccessor() const {
        return bool(node_->left);
    }
    [[nodiscard]] bool HasRightSuccessor() const {
        return bool(node_->right);
    }
    BifurcateCoordinate LeftSuccessor() const {
        return BifurcateCoordinate(*(node_->left));
    }
    BifurcateCoordinate RightSuccessor() const {
        return BifurcateCoordinate(*(node_->right));
    }

private:
    Node* node_;
};

template <typename C>
int WeightRecursive(C c) {
    if (c.Empty())
        return 0;

    int l = 0;
    int r = 0;
    if (c.HasLeftSuccessor())
        l = WeightRecursive(c.LeftSuccessor());
    if (c.HasRightSuccessor())
        r = WeightRecursive(c.RightSuccessor());

    return l + r + 1;
}

template <typename C>
int HeightRecursive(C c) {
    if (c.Empty())
        return 0;

    int l = 0;
    int r = 0;
    if (c.HasLeftSuccessor())
        l = HeightRecursive(c.LeftSuccessor());
    if (c.HasRightSuccessor())
        r = HeightRecursive(c.RightSuccessor());

    return std::max(l, r) + 1;
}

enum class Visit {
    PRE,
    IN,
    POST
};

template <typename C, typename Proc>
Proc TraverseNonempty(C c, Proc proc) {
    proc(Visit::PRE, c);
    if (c.HasLeftSuccessor())
        proc = TraverseNonempty(c.LeftSuccessor(), proc);
    proc(Visit::IN, c);
    if (c.HasRightSuccessor())
        proc = TraverseNonempty(c.RightSuccessor(), proc);
    proc(Visit::POST, c);

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
    BidirectionalBinaryNode& AddLeftSuccessor(T t) {
        left = std::make_unique<BidirectionalBinaryNode>(std::move(t));
        left->predecessor = this;
        return *left;
    }
    BidirectionalBinaryNode& AddRightSuccessor(T t) {
        right = std::make_unique<BidirectionalBinaryNode>(std::move(t));
        right->predecessor = this;
        return *right;
    }

private:
    T value;
    std::unique_ptr<BidirectionalBinaryNode<T>> left;
    std::unique_ptr<BidirectionalBinaryNode<T>> right;
    BidirectionalBinaryNode<T>* predecessor;

    friend class BidirectionalBifurcateCoordinate<T>;
};

template <typename T>
struct BidirectionalBifurcateCoordinate {
    using Node = BidirectionalBinaryNode<T>;
    using Type = T;
    BidirectionalBifurcateCoordinate()
          : node_(nullptr) {}
    explicit BidirectionalBifurcateCoordinate(Node& node)
          : node_(&node) {}
    T& operator*() const {
        return node_->value;
    }
    [[nodiscard]] bool Empty() const {
        return node_ == nullptr;
    }
    [[nodiscard]] bool HasLeftSuccessor() const {
        return bool(node_->left);
    }
    [[nodiscard]] bool HasRightSuccessor() const {
        return bool(node_->right);
    }
    [[nodiscard]] bool HasPredecessor() const {
        return node_->predecessor != nullptr;
    }
    BidirectionalBifurcateCoordinate LeftSuccessor() const {
        return BidirectionalBifurcateCoordinate(*(node_->left));
    }
    BidirectionalBifurcateCoordinate RightSuccessor() const {
        return BidirectionalBifurcateCoordinate(*(node_->right));
    }
    BidirectionalBifurcateCoordinate Predecessor() const {
        return BidirectionalBifurcateCoordinate(*node_->predecessor);
    }
    [[nodiscard]] bool IsLeftSuccessor() const {
        return HasPredecessor() && Predecessor().LeftSuccessor().node_ == node_;
    }
    [[nodiscard]] bool IsRightSuccessor() const {
        return HasPredecessor() && Predecessor().RightSuccessor().node_ == node_;
    }

private:
    Node* node_;
};

template <typename I>
int TraverseStep(Visit& v, I& c) {
    switch (v) {
        case Visit::PRE:
            if (c.HasLeftSuccessor()) {
                c = c.LeftSuccessor();
                return 1;
            } else {
                v = Visit::IN;
                return 0;
            }
        case Visit::IN:
            if (c.HasRightSuccessor()) {
                v = Visit::PRE;
                c = c.RightSuccessor();
                return 1;
            } else {
                v = Visit::POST;
                return 0;
            }
        case Visit::POST:
            if (c.IsLeftSuccessor())
                v = Visit::IN;
            c = c.Predecessor();
            return -1;
    }
    return 0;
}
}

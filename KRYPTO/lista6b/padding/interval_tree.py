# interval_tree_avl.py
from __future__ import annotations
from dataclasses import dataclass
from typing import Optional, List, Tuple, Iterator


@dataclass
class Interval:
    low: int
    high: int

    def __post_init__(self):
        if self.low > self.high:
            raise ValueError("Interval low must be <= high")

    def overlaps(self, other: "Interval") -> bool:
        # closed intervals [low, high]
        return not (self.high < other.low or other.high < self.low)

    def contains_point(self, x: int) -> bool:
        return self.low <= x <= self.high

    def __repr__(self):
        return f"[{self.low}, {self.high}]"


class _Node:
    __slots__ = ("interval", "max_end", "height", "left", "right")

    def __init__(self, interval: Interval):
        self.interval = interval
        self.max_end = interval.high
        self.height = 1
        self.left: Optional[_Node] = None
        self.right: Optional[_Node] = None

    def recalc(self):
        left_max = self.left.max_end if self.left else self.interval.high
        right_max = self.right.max_end if self.right else self.interval.high
        self.max_end = max(
            self.interval.high,
            self.left.max_end if self.left else self.interval.high,
            self.right.max_end if self.right else self.interval.high,
        )
        left_h = self.left.height if self.left else 0
        right_h = self.right.height if self.right else 0
        self.height = 1 + max(left_h, right_h)


class IntervalTree:
    def __init__(self):
        self.root: Optional[_Node] = None

    # --- AVL helpers ---
    @staticmethod
    def _height(n: Optional[_Node]) -> int:
        return n.height if n else 0

    @staticmethod
    def _balance_factor(n: Optional[_Node]) -> int:
        if not n:
            return 0
        return (n.left.height if n.left else 0) - (n.right.height if n.right else 0)

    def _rotate_right(self, y: _Node) -> _Node:
        x = y.left
        assert x is not None
        T2 = x.right
        x.right = y
        y.left = T2
        y.recalc()
        x.recalc()
        return x

    def _rotate_left(self, x: _Node) -> _Node:
        y = x.right
        assert y is not None
        T2 = y.left
        y.left = x
        x.right = T2
        x.recalc()
        y.recalc()
        return y

    def _rebalance(self, node: _Node) -> _Node:
        node.recalc()
        bf = self._balance_factor(node)
        # Left heavy
        if bf > 1:
            if self._balance_factor(node.left) < 0:
                # Left-Right
                node.left = self._rotate_left(node.left)
            return self._rotate_right(node)
        # Right heavy
        if bf < -1:
            if self._balance_factor(node.right) > 0:
                # Right-Left
                node.right = self._rotate_right(node.right)
            return self._rotate_left(node)
        return node

    # --- Insert ---
    def insert(self, low: int, high: int):
        interval = Interval(low, high)
        self.root = self._insert_node(self.root, interval)

    def _insert_node(self, node: Optional[_Node], interval: Interval) -> _Node:
        if node is None:
            return _Node(interval)
        # BST by interval.low, tie-breaker by interval.high
        if interval.low < node.interval.low or (
            interval.low == node.interval.low and interval.high < node.interval.high
        ):
            node.left = self._insert_node(node.left, interval)
        else:
            node.right = self._insert_node(node.right, interval)
        return self._rebalance(node)

    # --- Remove ---
    def remove(self, low: int, high: int):
        interval = Interval(low, high)
        self.root = self._remove_node(self.root, interval)

    def _remove_node(
        self, node: Optional[_Node], interval: Interval
    ) -> Optional[_Node]:
        if node is None:
            return None
        if interval.low < node.interval.low or (
            interval.low == node.interval.low and interval.high < node.interval.high
        ):
            node.left = self._remove_node(node.left, interval)
        elif interval.low > node.interval.low or (
            interval.low == node.interval.low and interval.high > node.interval.high
        ):
            node.right = self._remove_node(node.right, interval)
        else:
            # found exact interval to delete
            if node.left is None:
                return node.right
            elif node.right is None:
                return node.left
            else:
                # replace with inorder successor (smallest in right subtree)
                succ = node.right
                while succ.left:
                    succ = succ.left
                node.interval = succ.interval
                node.right = self._remove_node(node.right, succ.interval)
        return self._rebalance(node) if node else None

    # --- Queries ---
    def search_any_overlapping(self, low: int, high: int) -> Optional[Interval]:
        target = Interval(low, high)
        node = self.root
        while node:
            if node.interval.overlaps(target):
                return node.interval
            if node.left and node.left.max_end >= target.low:
                node = node.left
            else:
                node = node.right
        return None

    def overlaps_exist(self, low: int, high: int) -> bool:
        return self.search_any_overlapping(low, high) is not None

    def search_all_overlapping(self, low: int, high: int) -> List[Interval]:
        out: List[Interval] = []
        target = Interval(low, high)
        self._search_all(self.root, target, out)
        return out

    def _search_all(self, node: Optional[_Node], target: Interval, out: List[Interval]):
        if node is None:
            return
        if node.interval.overlaps(target):
            out.a

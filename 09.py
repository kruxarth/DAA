# P9: Huffman coding
import heapq
from itertools import count


def huffman_codes(frequencies):
    serial = count()
    heap = []
    for symbol, frequency in frequencies.items():
        heapq.heappush(heap, (frequency, next(serial), symbol, None, None))

    if len(heap) == 1:
        return {heap[0][2]: "0"}

    while len(heap) > 1:
        f1, _, s1, left1, right1 = heapq.heappop(heap)
        f2, _, s2, left2, right2 = heapq.heappop(heap)
        # A leaf is represented by its symbol with no children.
        left_node = (s1, left1, right1)
        right_node = (s2, left2, right2)
        heapq.heappush(heap, (f1 + f2, next(serial), None,
                              left_node, right_node))

    _, _, _, left_root, right_root = heap[0]
    codes = {}

    def walk(node, prefix):
        symbol, left, right = node
        if left is None and right is None:
            codes[symbol] = prefix or "0"
            return
        if left is not None:
            walk(left, prefix + "0")
        if right is not None:
            walk(right, prefix + "1")

    walk((None, left_root, right_root), "")
    return codes


n = int(input("Enter number of symbols: "))
frequencies = {}
for _ in range(n):
    symbol, frequency = input("Enter symbol and frequency: ").split()
    frequencies[symbol] = int(frequency)

if not frequencies or any(f <= 0 for f in frequencies.values()):
    raise ValueError("Enter at least one symbol with positive frequencies.")

codes = huffman_codes(frequencies)
print("Huffman codes:")
for symbol in sorted(codes):
    print(f"{symbol}: {codes[symbol]}")

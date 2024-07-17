import bisect
import numpy as np


def is_the_number_k_or_more(mid, k, As, Bs):
    num = 0
    for a in As:
        num += bisect.bisect_right(Bs, mid // a)

    return num >= k


def solve():
    _, k = [int(v) for v in input().rstrip().split()]
    As = [int(v) for v in input().rstrip().split()]
    Bs = [int(v) for v in input().rstrip().split()]

    As.sort()
    Bs.sort()

    left = 0
    right = As[-1] * Bs[-1]
    mid = (left + right) // 2
    while (right - left > 1):
        if is_the_number_k_or_more(mid, k, As, Bs):
            right = mid
        else:
            left = mid
        mid = (left + right) // 2

    print(right)


if __name__ == '__main__':
    solve()

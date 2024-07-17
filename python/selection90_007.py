import bisect
import numpy as np


def solve():
    n = int(input().rstrip())

    As = [int(v) for v in input().rstrip().split()]

    q = int(input().rstrip())
    Bs = np.empty(q, dtype=int)
    for i in range(q):
        Bs[i] = int(input().rstrip())

    As = sorted(As)

    for i in range(q):
        idx = bisect.bisect_left(As, Bs[i])
        compls = []
        if idx > 0:
            compls.append(abs(Bs[i] - As[idx - 1]))
        if idx < len(As):
            compls.append(abs(As[idx] - Bs[i]))
        print(min(compls))


if __name__ == '__main__':
    solve()

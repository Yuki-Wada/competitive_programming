import numpy as np

def solve():
    A, B, X = map(int, input().split())
    
    if A * 10 ** 9 + B * 10 <= X:
        res = 10 ** 9

    elif A + B > X:
        res = 0

    else:
        N = 10 ** 9
        d = len(str(N))

        while A * N + B * d > X:
            N //= 10
            d = len(str(N))
        
        res = min((X - B * d) // A, N * 10 - 1)

    print(res)

if __name__ == '__main__':
    solve()

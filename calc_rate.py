import argparse
import math

def get_args():
    parser = argparse.ArgumentParser()

    parser.add_argument('--mode', default='adjusted_value')
    parser.add_argument('--scores', nargs='+', type=float, default=[1199, 1546, 2197])
    parser.add_argument('--target_rate', type=float, default=1600)
    parser.add_argument('--participation_count', type=int, default=3)

    args = parser.parse_args()

    return args

def forward(score):
    return 2 ** (score / 800)

def inverse(score):
    return math.log2(score) * 800

def adjusted_value(participation_count):
    return (((1 - (0.81 ** participation_count)) ** 0.5) / (1 - (0.9 ** participation_count)) - 1) / \
        ((19 ** 0.5) - 1) * 1200

def calc_rate(scores):
    result = 0
    for i, score in enumerate(scores[::-1]):
        result += forward(score) * (0.9 ** i)
    
    result /= 10 * (1 - (0.9 ** len(scores)))
    result = inverse(result)

    return result

def calc_next_score(scores, target_rate):
    min_score = 0
    max_score = 10000

    while max_score - min_score > 0.001:
        mid_score = (min_score + max_score) / 2
        rate = calc_rate(scores + [mid_score])
        rate -= adjusted_value(len(scores) + 1)
        if target_rate > rate:
            min_score = mid_score
        else:
            max_score = mid_score

    return mid_score

def run():
    args = get_args()
    if args.mode == 'score':
        scores = args.scores
        rate = calc_rate(scores)
        print(rate)
        return rate

    if args.mode == 'adjusted_score':
        scores = args.scores
        rate = calc_rate(scores)
        rate -= adjusted_value(len(scores))
        print(rate)
        return rate
    
    if args.mode == 'next_score':
        scores = args.scores
        target_rate = args.target_rate
        next_score = calc_next_score(scores, target_rate)
        print(next_score)
        return next_score

    if args.mode == 'adjusted_value':
        participation_count = args.participation_count
        adjust = adjusted_value(participation_count)
        print(adjust)
        return adjust

if __name__ == '__main__':
    run()


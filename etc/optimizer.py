import numpy as np
from subprocess import Popen, PIPE
from hyperopt import fmin, tpe, hp

# constants defining search space
INSTANCESIZE = 5000
STEPSTART = 10000
STEPEND = 100000
STEPSTEP = 1000

T0START = 0.0
T0END = 1.0
T0STEP = 0.01

ALPHASTART = 0
ALPHAEND = 1
ALPHASTEP = 0.0001


def sa(args):


    # print(val)
    print(args)

    # for c in case:
    #     if case == "steps":
    #         steps = c
    alpha = str(args['alpha'])
    steps = str(100000)
    t0 = str(args['t0'])
    process = Popen(["./PointLabeler",  "-in", "../dat/random/5000_ran0.txt",
                     "-out", "test.txt", "-alpha", alpha, "-steps", steps, "-t", t0], stdout=PIPE)
    (output, err) = process.communicate()
    output = output.decode()
    output = output.replace('\n', "").split('\t')
    number_labeled = int(output[0])
    used_time = float(output[1])
    print(number_labeled)
    return INSTANCESIZE - number_labeled


space = {
    # 'steps': STEPSTART + hp.randint('steps', STEPEND - STEPSTART),
    'alpha': hp.uniform('alpha', ALPHASTART, ALPHAEND),
    't0': hp.uniform('t0', T0START, T0END)
}

best = fmin(sa, space=space, algo=tpe.suggest, max_evals=10)
print(best)


# end = time() + 60
# while time() < end:
#     pass

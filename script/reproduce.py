import json
import io
import random

random.seed(20191025)

with io.open('Output.out') as f:
    data = json.load(f)

def getErrorList(i):
    funcIndex = str(i)
    if funcIndex in data:
        inputs = data[funcIndex]['input_list']
        errList = [item['relative_err'] for item in inputs]
        return errList
    else:
        return []

def rankingInfo():
    rand = [0,0,0,0,0,0]
    rank = [0,0,0,0,0,0]
    for i in range(107):
        funcIndex = str(i)
        if funcIndex not in data:
            continue
        inputs = data[funcIndex]['input_list']
        # Ranked
        inputs.sort(key=lambda x: x['count_to_end'])
        for k in range(1,6):
            errListTopK = [item['relative_err'] for item in inputs[:k]]
            maxTopK = max(errListTopK, default=0)
            if maxTopK >= 1e-3:
                rank[k] += 1
        # Random
        random.shuffle(inputs)
        for k in range(1,6):
            errListTopK = [item['relative_err'] for item in inputs[:k]]
            maxTopK = max(errListTopK, default=0)
            if maxTopK >= 1e-3:
                rand[k] += 1
    print('----------------------')
    print('Line Chart Info in Fig.4')
    print('Prioritized:', rank)
    print('Random:     ', rand)
    print('----------------------')

def histogramInfo():
    hist = [0,0,0,0,0,0,0,0]
    for i in range(107):
        funcIndex = str(i)
        if funcIndex not in data:
            continue
        errList = getErrorList(i)
        maxErr = max(errList, default=0)
        if maxErr < 1e-15:
            hist[0] += 1
        elif maxErr < 1e-12:
            hist[1] += 1
        elif maxErr < 1e-9:
            hist[2] += 1
        elif maxErr < 1e-6:
            hist[3] += 1
        elif maxErr < 1e-3:
            hist[4] += 1
        elif maxErr< 1:
            hist[5] += 1
        elif maxErr < 1e3:
            hist[6] += 1
        else:
            hist[7] += 1
    print('----------------------')
    print('Histogram Info in Fig.3')
    print('[0,1e-15)    ', hist[0])
    print('[1e-15,1e-12)', hist[1])
    print('[1e-12,1e-9) ', hist[2])
    print('[1e-9,1e-6)  ', hist[3])
    print('[1e-6,1e-3)  ', hist[4])
    print('   Insignificant Error:', sum(hist[:5]))
    print('----------------------')
    print('[1e-3,1)     ', hist[5])
    print('[1, 1e3)     ', hist[6])
    print('[1e3, +inf)  ', hist[7])
    print('   Significant Error:  ', sum(hist[5:]))
    print('----------------------')
    print('   Total:              ', sum(hist))
    print('----------------------')

histogramInfo()
rankingInfo()

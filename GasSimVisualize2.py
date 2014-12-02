from visual import *
from random import randrange

data = open("/Users/akyle/Developer/MatterAndInteractionsIProject/cData.txt","r")

vscale = 0.1
particle = []
pos = 0
prevLineTime = 0
diff = True
lineNotNull = True

while diff:
    currentLine = data.readline()
    currentLineData = currentLine.split(",")
    for i in xrange(0,4):
        currentLineData[i] = float(currentLineData[i])
    particle.append(sphere(pos=(currentLineData[1],currentLineData[2],currentLineData[3]), radius=0.5, color=color.red))
    if prevLineTime != currentLineData[0]:
        diff = False
    prevLineTime = currentLineData[0]

while lineNotNull:
    rate(100)
    pos = 0
    diff = True
    while diff:
        currentLine = data.readline()
        if currentLine:
            currentLineData = currentLine.split(",")
            for i in xrange(0,4):
                currentLineData[i] = float(currentLineData[i])
            particle[pos].pos = vector(currentLineData[1],currentLineData[2],currentLineData[3])
            if prevLineTime != currentLineData[0]:
                diff = False
            prevLineTime = currentLineData[0]
            pos = pos+1
        else:
            diff = False
            lineNotNull = False
print "done"

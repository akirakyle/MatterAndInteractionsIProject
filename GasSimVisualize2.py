from visual import *
from random import randrange

data = open("/Users/akyle/Developer/MatterAndInteractionsIProject/gasSimData.txt","r")
scene.autoscale = False

vscale = 0.1
particle = []
pos = 0
prevLineTime = 0
diff = True
lineNotNull = True
first = True

while diff:
    currentLine = data.readline()
    currentLineData = currentLine.split(",")
    for i in xrange(0,4):
        currentLineData[i] = float(currentLineData[i])
    if first:
        particle.append(sphere(pos=(currentLineData[1],currentLineData[2],currentLineData[3]), radius=0.2, color=color.blue))
        first = False
    particle.append(sphere(pos=(currentLineData[1],currentLineData[2],currentLineData[3]), radius=0.2, color=color.red))
    if prevLineTime != currentLineData[0]:
        diff = False
    prevLineTime = currentLineData[0]

while lineNotNull:
    rate(50)
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

from visual import *
from visual.graph import *
from random import randrange 

data = open("/Users/akyle/Developer/MatterAndInteractionsIProject/gasSimData.txt","r")
scene = display(title = "GasSimVisualize", width = 1000, height = 400, range = 80)
scene.autoscale = False

gdisplay(x = 0, y = 400, xmin = 0, xmax = 5,ymin = 0, ymax = 500, title = "Number of Particles at wall vs Time",
xtitle = "Time", ytitle = "Number of Particles")
drawPt = gcurve(color = color.red)

vscale = 0.1
particle = []

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
    particle.append(sphere(pos=(currentLineData[1],currentLineData[2],currentLineData[3]), radius=0.1, color=color.red))
    if prevLineTime != currentLineData[0]:
        diff = False
    prevLineTime = currentLineData[0]

while lineNotNull:
    rate(80)
    pos = 0
    numParticles = 0
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

            if currentLineData[1] < -9:
                numParticles = numParticles + 1
        else:
            diff = False
            lineNotNull = False
    
    drawPt.plot( pos = (currentLineData[0], numParticles) )
print "done"

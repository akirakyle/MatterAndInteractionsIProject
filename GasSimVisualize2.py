from visual import *
from visual.graph import *
from random import randrange

vscale = 0.1
maxVel = 10

data = open("/Users/akyle/Developer/MatterAndInteractionsIProject/gasSimData.txt","r")
scene = display(title = "GasSimVisualize", width = 1400, height = 300, range = 12)
scene.autoscale = False

gdisplay(x = 0, y = 300, width = 700, height = 200, xmin = 0, xmax = 5,
ymin = 0, ymax = 150, title = "Number of Particles at wall vs Time", xtitle = "Time", ytitle = "Number of Particles")
drawPos = gcurve(color = color.red)

gdisplay(x = 700, y = 300, width = 700, height = 400, xmin = 0, xmax = 30,
ymin = 0, ymax = 120, title = "Boltzmann Distribution", xtitle = "particle velocity", ytitle = "Number of Particles")
drawVel = gcurve(color = color.blue)

resolution = []
for i in xrange(0,maxVel*3):
    resolution.append(i)

gdisplay(x = 0, y = 500, width = 700, height = 400, xmin = 0, xmax = 30,
ymin = 0, ymax = 120, title = "Boltzmann Distribution", xtitle = "particle velocity", ytitle = "Number of Particles")
drawVelH = ghistogram(bins = arange(0,maxVel*3,.2), color = color.blue)

particle = []
velMags = []
velDistribution = []
pos = 0
prevLineTime = 0
diff = True
lineNotNull = True
first = True

for i in xrange(0,maxVel*3):
    velDistribution.append(0)
    drawVel.plot( pos = (i, velDistribution[i]) )

while diff:
    currentLine = data.readline()
    currentLineData = currentLine.split(",")
    for i in xrange(0,7):
        currentLineData[i] = float(currentLineData[i])
    if pos == 30:
        particle.append(sphere(pos=(currentLineData[1],currentLineData[2],currentLineData[3]), radius=0.2, color=color.blue))
        first = False
    else:
        particle.append(sphere(pos=(currentLineData[1],currentLineData[2],currentLineData[3]), radius=0.1, color=color.red))
    particle[-1].vel = vector(currentLineData[4],currentLineData[5],currentLineData[6])
    velMags.append(mag(particle[-1].vel))
    if prevLineTime != currentLineData[0]:
        diff = False
    prevLineTime = currentLineData[0]
    pos = pos +1
print "number of particles:"+str(len(particle))

drawVelH.plot(data = velMags)

while lineNotNull:
    rate(100)
    pos = 0
    numParticles = 0
    diff = True
    while diff:
        currentLine = data.readline()
        if currentLine:
            currentLineData = currentLine.split(",")
            for i in xrange(0,7):
                currentLineData[i] = float(currentLineData[i])
            particle[pos].pos = vector(currentLineData[1],currentLineData[2],currentLineData[3])
            particle[pos].vel = vector(currentLineData[4],currentLineData[5],currentLineData[6])
            
            if prevLineTime != currentLineData[0]:
                diff = False
            prevLineTime = currentLineData[0]
            pos = pos+1

            if currentLineData[1] < 1 and currentLineData[1] > -1:
                numParticles = numParticles + 1

            velMags[pos] = mag(particle[pos].vel)
            #print int(round(mag(particle[pos].vel)))
            velDistribution[int(round(mag(particle[pos].vel)))] = velDistribution[int(round(mag(particle[pos].vel)))] +1
            
        else:
            diff = False
            lineNotNull = False
    
    drawPos.plot( pos = (currentLineData[0], numParticles) )
    drawVelH.plot(data = velMags)
    for i in xrange(0,maxVel*3):
        drawVel.gcurve.pos[i] = (i, velDistribution[i],0)
        velDistribution[i] = 0
print "done"

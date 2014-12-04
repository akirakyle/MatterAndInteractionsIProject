from visual import *
from visual.graph import *
from random import randrange

maxVel = 10
resolution = .5
cylinderHeight = 40

particle = []
velMags = []
pos = 0
prevLineTime = 0
diff = True
first = True

while True:

    data = open("/Users/akyle/Developer/MatterAndInteractionsIProject/gasSimData.txt","r")
    data.seek(0)
    scene = display(title = "GasSimVisualize", width = 1400, height = 300, range = cylinderHeight+2)
    scene.autoscale = False

    gdisplay(x = 0, y = 300, width = 700, height = 250, xmin = 0, xmax = 5,
    ymin = 0, ymax = 150, title = "Number of Particles at wall vs Time", xtitle = "Time", ytitle = "Number of Particles")
    drawPos = gcurve(color = color.red)

    gdisplay(x = 0, y = 550, width = 700, height = 250, xmin = 0, xmax = 5,
    ymin = -150, ymax = 150, title = "Avg x velocity of Particles at wall vs Time", xtitle = "Time", ytitle = "Avg x velocity")
    drawVel = gcurve(color = color.green)

    gdisplay(x = 700, y = 300, width = 700, height = 500, xmin = 0, xmax = 20,
    ymin = 0, ymax = 100, title = "Boltzmann Distribution", xtitle = "particle velocity", ytitle = "Number of Particles")
    drawBoltzman = ghistogram(bins = arange(0,maxVel*3,resolution), color = color.blue)

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

    lineNotNull = True
    while lineNotNull:
        rate(100)
        pos = 0
        numParticles = 0
        avgVel = 0
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
                if currentLineData[1] < 1 and currentLineData[1] > -1:
                    avgVel = avgVel + currentLineData[4]
    
                velMags[pos] = mag(particle[pos].vel)
                            
            else:
                diff = False
                lineNotNull = False
        
        drawPos.plot( pos = (currentLineData[0], numParticles) )
        drawVel.plot( pos = (currentLineData[0], avgVel) )
        drawBoltzman.plot(data = velMags)

    print "done, press enter to restart"
    scene.waitfor("click keydown")

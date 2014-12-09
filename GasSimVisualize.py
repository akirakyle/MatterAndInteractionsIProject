from visual import *
from visual.graph import *
from random import randrange

resolution = .5
particle = []
velMags = []
pos = 0
prevLineTime = 0
diff = True

while True:

    data = open("/Users/akyle/Developer/MatterAndInteractionsIProject/Data/gasSimData2.txt","r")
    data.seek(0)
    currentLine = data.readline()
    currentLineData = currentLine.split(",")
    paramDesc = currentLineData
    currentLine = data.readline()
    currentLineData = currentLine.split(",")
    for i in xrange(0,12):
        currentLineData[i] = float(currentLineData[i])
        print paramDesc[i] + ": " + str(currentLineData[i])

    cylinderHeight = currentLineData[0]
    time = currentLineData[3]
    maxVel = currentLineData[11]
    
    scene.autoscale = False
    scene = display(title = "GasSimVisualize", width = 1450, height = 300, range = cylinderHeight/2+2)
    scene.autoscale = False

    gdisplay(x = 0, y = 300, width = 725, height = 450, xmin = 0, xmax = time,
    ymin = -150, ymax = 150, title = "Avg X Velocity of Particles at Wall vs Time", xtitle = "Time", ytitle = "Avg X Velocity at Wall (nm/sec)")
    drawVel = gcurve(color = color.green)

    gdisplay(x = 0, y = 750, width = 725, height = 150, xmin = 0, xmax = time,
    ymin = 0, ymax = 50, title = "Number of Particles at Wall vs Time", xtitle = "Time", ytitle = "Number of Particles at Wall")
    drawPos = gcurve(color = color.red)

    gdisplay(x = 725, y = 750, width = 725, height = 150, xmin = 0, xmax = time,
    ymin = -0, ymax = 8000, title = "Total Sum of Velocies of All Particles vs Time", xtitle = "Time", ytitle = "Sum of Velocities")
    drawTemp = gcurve(color = color.orange)

    gdisplay(x = 725, y = 300, width = 725, height = 450, xmin = 0, xmax = maxVel*2,
    ymin = 0, ymax = 50, title = "Boltzmann Distribution", xtitle = "Particle Velocity", ytitle = "Number of Particles")
    drawBoltzman = ghistogram(bins = arange(0,maxVel*2,maxVel/30), color = color.blue)

    while diff:
        currentLine = data.readline()
        currentLineData = currentLine.split(",")
        for i in xrange(0,7):
            currentLineData[i] = float(currentLineData[i])
    
        if pos == 30:
            particle.append(sphere(pos=(currentLineData[1],currentLineData[2],currentLineData[3]), radius=1, color=color.blue))
            #particle[30].tral = []
            #print "hey"
            particle[30].trail = curve(color=particle[30].color)
            first = False
        else:
            particle.append(sphere(pos=(currentLineData[1],currentLineData[2],currentLineData[3]), radius=0.5, color=color.red))
    
        particle[-1].vel = vector(currentLineData[4],currentLineData[5],currentLineData[6])
        velMags.append(mag(particle[-1].vel))
    
        if prevLineTime != currentLineData[0]:
            diff = False
        prevLineTime = currentLineData[0]
        pos = pos +1
    print "number of particles:"+str(len(particle)) 

    lineNotNull = True
    while lineNotNull:
        rate(1000)
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

        particle[30].trail.append(pos=particle[30].pos)
        drawPos.plot( pos = (currentLineData[0], numParticles) )
        drawVel.plot( pos = (currentLineData[0], avgVel) )
        drawTemp.plot( pos = (currentLineData[0], sum(velMags)))
        drawBoltzman.plot(data = velMags)

    print "done, press enter to restart"
    #scene.waitfor("click keydown")

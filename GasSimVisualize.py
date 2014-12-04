from visual import *
from random import randrange
from visual.graph import *
numBalls = 200
vscale = 0.1
ball = []
varr = []

for i in xrange(0,numBalls):
    ball.append(sphere(pos=(0,0,0), radius= 139e-12, color=color.cyan))
#    ball[i].trail = curve(color=ball[i].color)
    ball[i].velocity = vector(randrange(-30,30,1),randrange(-30,30,1),randrange(-30,30,1))
#    varr.append(arrow(pos=ball[i].pos, axis=vscale*ball[i].velocity, color=color.yellow))

rod = cylinder(pos=(0,0,0), axis=(5e-8,0,0), radius=1e-8, color=color.white, opacity=0.1)

wallR = box(pos=(5.1e-8,0,0), size=(1e-10,1e-8,1e-8), color=color.blue, opacity=0)
wallL = box(pos=(0,0,0), size=(1e-10,1e-8,1e-8), color=color.blue, opacity=0)
wallU = box(pos=(0,1.1e-8,0), size=(1e-8,1e-10,1e-8), color=color.blue, opacity=0)
wallD = box(pos=(0,-1.1e-8,0), size=(5e-10,1e-10,1e-8), color=color.blue, opacity=0)
wallB = box(pos=(2.505e-8,0,-1.1e-8), size=(5.1e-8,2.2e-8,5e-10), color=color.blue, opacity=0)

vmax = 5000

deltat = 0.000000000005
t = 0
d1 = gdisplay(x = 0, y = 200, height = 400, width = 800, xmin = 0, xmax = vmax, ymin = -0.3,
              ymax = 5000, title = "Boltzmann Distribution", xtitle = "Velocity (m/s)",
              ytitle = "Number of Molecules")

drawb = gcurve(color = color.red)


#d2 = gdisplay(x = 0, y = 600, height = 400, width = 800, xmin = 0, xmax = 1000, ymin = -0.3,
#              ymax = 5000, title = "Gas Properties", xtitle = "Time (s)",
#              ytitle = "Scaled Gas Properties (Energy, Volume, Pressure)")
#drawke = gcurve(color = color.yellow)
#drawv = gcurve (color = color.blue)
#drawp = gcurve (color = color.red)

# interatomic distance = 109.76e-12 m, atomic radius = 56e-12 so long part is
# 221.76e-12 m and the short is 56e-12. Options: take average of these, or
# just double the radius of the nitrogen atom. Either radius of 112 or radius
# 139


scene.autoscale = True

while t < 1000:
    rate(200)
    for i in xrange(0,numBalls):
        if (ball[i].pos.x > wallR.pos.x) or (ball[i].pos.x < wallL.pos.x):
            ball[i].velocity.x = -ball[i].velocity.x     
        if (ball[i].pos.y > wallU.pos.y) or (ball[i].pos.y < wallD.pos.y):
            ball[i].velocity.y = -ball[i].velocity.y
        if (ball[i].pos.z > 10) or (ball[i].pos.z < wallB.pos.z):
            ball[i].velocity.z = -ball[i].velocity.z
        for j in xrange (0, numBalls):
            if ((ball[i].pos.x - ball[j].pos.x) < 1e-12):
                ball[i].velocity.x = -ball[i].velocity.x
                ball[j].velocity.x = -ball[j].velocity.x
            if ((ball[i].pos.y - ball[j].pos.y) < 1e-12):
                ball[i].velocity.y = -ball[i].velocity.y
                ball[j].velocity.y = -ball[j].velocity.y
            if ((ball[i].pos.z - ball[j].pos.z) < 1e-12):
                ball[i].velocity.z = -ball[i].velocity.z
                ball[j].velocity.z = -ball[j].velocity.z
                
        ball[i].pos = ball[i].pos + ball[i].velocity*deltat

#        drawb.plot(pos = (mag(ball[i].velocity), 

        
#        ball[i].trail.append(pos=ball[i].pos)
#        varr[i].pos = ball[i].pos
#        varr[i].axis=vscale*ball[i].velocity
    t = t + deltat

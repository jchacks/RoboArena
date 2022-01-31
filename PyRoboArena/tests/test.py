from telnetlib import DO
from RoboArena.app import App, Battle
from RoboArena.bots import *

robots = [RandomRobot(), DoNothing()]

app = App(size=(300, 300), fps_target=60)
app.child = Battle(robots, app.size)
app.child.set_tick_rate(30)
app.run()

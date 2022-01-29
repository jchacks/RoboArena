from RoboArena.app import App, Battle
from RoboArena.bots import RandomRobot

robots = [RandomRobot(), RandomRobot()]

app = App(size=(300, 300), fps_target=15)
app.child = Battle(robots, app.size)
app.child.set_tick_rate(60)
app.run()
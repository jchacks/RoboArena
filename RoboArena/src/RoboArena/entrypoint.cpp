#include "rapch.h"

#include "RoboArena/core.h"
#include "RoboArena/log.h"
#include "RoboArena/Engine/engine.h"
#include "RoboArena/Engine/robot.h"


int main(int argc, char **argv)
{
	Log::Init();
	WARN("Initialized Log!");
	int a = 5;
	INFO("Hello! Var={0}", a);

	Robot r1 = Robot();
	Robot r2 = Robot();
	r1.should_fire = true;
	TRACE("shouldfire {}", r1.should_fire);

	TRACE("TEST NUMBER_ROBOTS {}", NUMBER_ROBOTS);
	Engine eng = Engine(600, 400);
	eng.add_robot(r1);
	eng.add_robot(r2);
	TRACE("TEST NUMBER_ROBOTS {}", NUMBER_ROBOTS);

	eng.init();
	INFO("This is {0}", r1);
	INFO("This is {0}", r2);
	TRACE("TEST NUMBER_ROBOTS {}", NUMBER_ROBOTS);

	for (int i = 0; i < 1; i++)
	{
		eng.step();
		INFO("This is {0}", eng.get_robot(0));
	}
	TRACE("TEST NUMBER_ROBOTS {}", NUMBER_ROBOTS);
}

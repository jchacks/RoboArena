#include "rapch.h"

#include "RoboArena/core.h"
#include "RoboArena/log.h"
#include "RoboArena/Engine/engine.h"
#include "RoboArena/Engine/robot.h"

#include "RoboArena/application.h"


int main(int argc, char **argv)
{
	Log::Init();
	WARN("Initialized Log!");
	int a = 5;
	INFO("Hello! Var={0}", a);

	auto app = new Application();
	app->run();
	delete app;

	// Robot r1 = Robot();
	// Robot r2 = Robot();

	// Engine eng = Engine();
	// eng.add_robot(r1);
	// eng.add_robot(r2);
	// INFO("This is {0}", r1);

	// for (int i = 0; i < 10; i++)
	// {
	// 	eng.step();
	// 	INFO("This is {0}", eng.get_robot(0));
	// }
}

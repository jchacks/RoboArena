#include "core.h"
#include "log.h"

int main(int argc, char** argv)
{
	Log::Init();
	WARN("Initialized Log!");
	int a = 5;
	INFO("Hello! Var={0}", a);
}

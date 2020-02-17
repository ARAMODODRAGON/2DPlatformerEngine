#include <SDL.h>
#include "Engine/Engine.h"

int main(int argc, char* argv[]) {

	Engine::GetSingleton()->Run();

	return 0;
}
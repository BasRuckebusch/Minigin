#include <SDL.h>
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#endif
#endif

#include "Minigin.h"

using namespace dae;

void load()
{

}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}
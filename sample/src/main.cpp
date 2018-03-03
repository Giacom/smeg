#include "app.hpp"
#include "io/image.hpp"
#include "io/file.hpp"
#include "math/vector2.hpp"
#include "math/rect.hpp"

#include "test_screen.hpp"

#include <memory>
#include <algorithm>

using namespace smeg;

i32 main(i32, char**) {
	App app;
	app.Init("SMEG Sample", 800, 600);

	ScreenPtr testScreen = std::make_unique<TestScreen>();

	app.AddScreen(testScreen);

	app.Start();
	return 0;
}

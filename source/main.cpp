#include "window.h"

int main(void)
{
	SCOP::Window window(800, 600);
	while(!window.isClosed())
	{
		window.checkKeysInputs();	
		glClearColor(0, 0, 1, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		window.update();
	}
	return 0;
}

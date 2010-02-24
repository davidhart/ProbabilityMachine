#include "MathsTests.h"
#include "window.h"

#include "Line2f.h"

#include <Gl/gl.h>

#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char ** argv)
{
	cout<<"Tests Start" << endl;
	MathsLibTests::DoAllTests(cout);
	cout<<"All Tests Complete"<<endl;

	Line2f l(Vector2f(0,0), Vector2f(1,1));

	Window w;
	w.SetSize(1150,620);
	w.SetTitle("Test...");

	if (!w.Create())
		return 1;

	while (w.IsOpen())
	{
		w.Clear();

		glBegin(GL_LINES);

		glVertex2f(l.Point().X(), l.Point().Y());

		glVertex2f(l.Point().X() + l.Direction().X(), l.Point().Y() + l.Direction().Y());

		glEnd();

		// draw

		w.Present();

		w.DoEvents();
	}

	return 0;
}

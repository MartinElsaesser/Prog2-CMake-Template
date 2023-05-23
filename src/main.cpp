#include <stdio.h>
#include "MathMatrix.h"
#include "Color.h"
#include "ViewPortGL/ViewPortGL.h"
#include <iostream>
#include <math.h>

void drawRectangle(int x, int y, int width, int height, float angle, ViewPortGL& vp, Color color) {
	auto middle = MathVec2<float>(0);
	middle.set(0,x);
	middle.set(1,y);

	auto left_top = MathVec2<float>(0);
	left_top.set(0,-width/2.0f);
	left_top.set(1,-height/2.0f);

	left_top = rotate2dVec(left_top, angle);
	left_top = left_top+middle;

	auto right_top = MathVec2<float>(0);
	right_top.set(0,width/2.0f);
	right_top.set(1,-height/2.0f);

	right_top = rotate2dVec(right_top, angle);
	right_top = right_top+middle;

	auto left_bottom = MathVec2<float>(0);
	left_bottom.set(0,-width/2.0f);
	left_bottom.set(1,height/2.0f);

	left_bottom = rotate2dVec(left_bottom, angle);
	left_bottom = left_bottom+middle;

	auto right_bottom = MathVec2<float>(0);
	right_bottom.set(0,width/2.0f);
	right_bottom.set(1,height/2.0f);

	right_bottom = rotate2dVec(right_bottom, angle);
	right_bottom = right_bottom+middle;

	vp.prepareTriangle(left_top.get(0), left_top.get(1), left_bottom.get(0), left_bottom.get(1), right_bottom.get(0), right_bottom.get(1),
	 color.getRed(), color.getGreen() , color.getBlue());
	vp.prepareTriangle(left_top.get(0), left_top.get(1), right_top.get(0), right_top.get(1), right_bottom.get(0), right_bottom.get(1), 
		color.getRed(), color.getGreen() , color.getBlue());
	vp.sendTriangles();
}

int main() {
  int width = 1024;
	int height = 512;
	ViewPortGL vp = ViewPortGL("Rotate rectangle", width, height);


	auto middle = MathVec2<float>(0);
	middle.set(0,width/2);
	middle.set(1,height/2);

	auto rotated = MathVec2<float>(0);
	float step = .005;

	bool isRunning = true;
	float angle = 0;
	while (isRunning) {
		isRunning = !vp.windowShouldClose();
		float middle_x = middle.get(0);
		float middle_y = middle.get(1);
		
		vp.clearViewPort();
		drawRectangle(width/2, height/2, 200, 300, angle, vp, Color(0,100,255));
		vp.swapBuffers();
		if(angle < 0 ||angle > 2*M_PI) {
			step *= -1;
		}
		angle+=step;
	}
}




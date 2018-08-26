#include <provided/tgaimage.h>
#include <provided/model.h>
#include <provided/geometry.h>
#include <vector>
#include <cmath>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
Model *model = NULL;
using namespace std;
const int width = 800;
const int height = 800;



void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
	bool steepLine = false;
	if (abs(x0 - x1) < abs(y0 - y1)) {
		swap(x0, y0);
		swap(x1, y1);
		steepLine = true;
	}
	if (x0 > x1) {
		swap(x0, x1);
		swap(y0, y1);
	}
	int deltaX = x1 - x0;
	int deltaY = y1 - y0;
//	float deltaError = abs(deltaY/(float)deltaX);
//	float error = 0;
	int deltaError = abs(deltaY) * 2;
	int error = 0;
	int y = y0;
	for (int x = x0; x <= x1; x++) {
		if (steepLine)
			image.set(y, x, color);
		else
			image.set(x, y, color);
//		float t = (x - x0) / deltaError;
//		float y = y0 * (1.0 - t) + y1 * t;
		error += deltaError;
		if (error > deltaX) {
			y += (y1 > y0 ? 1 : -1);
			error-= deltaX * 2;
		}
	}
}

int main(int argc, char** argv) {
	if (2 == argc) {
		model = new Model(argv[1]);
	}
	else {
		model = new Model("src/objs/african_head.obj");
	}

	TGAImage image(width, height, TGAImage::RGB);

	for (int i = 0; i < model->nfaces(); i++) {
		vector<int> face = model->face(i);
		for (int j = 0; j < 3; j++) {
			Vec3f v0 = model->vert(face[j]);
			Vec3f v1 = model->vert(face[(j + 1) % 3]);
			int x0, x1, y0, y1;
			x0 = (v0.x + 1.0f) * width / 2.0f;
			y0 = (v0.y + 1.0f) * height / 2.0f;
			x1 = (v1.x + 1.0f) * width / 2.0f;
			y1 = (v1.y + 1.0f) * height / 2.0f;
			line(x0, y0, x1, y1, image, red);
		}
	}
	

	image.flip_vertically(); // origin placed int the left bottom corner of the image
	image.write_tga_file("output.tga"); 
//	std::system("Pause");
	return 0;
}


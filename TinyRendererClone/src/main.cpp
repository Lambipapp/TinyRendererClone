#include <provided/tgaimage.h>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
using namespace std;
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
	TGAImage image(100, 100, TGAImage::RGB);
	//image.set(52, 41, red);
	//line(20, 20, 50, 50, image, white);
	line(13, 20, 80, 40, image, white);
	line(20, 13, 40, 80, image, red);
	line(80, 40, 13, 20, image, red);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga"); 
//	std::system("Pause");
	return 0;
}


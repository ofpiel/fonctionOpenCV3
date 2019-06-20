#include "pch.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <opencv2/text.hpp>

#include <fstream>
#include "ListeFonctions.h"

using namespace std;
using namespace cv;
using namespace text;


int main()
{
	//ListeFonctions::lecturePlusieursFlux();
	ListeFonctions::captureImageVideo();

	return 0;
}
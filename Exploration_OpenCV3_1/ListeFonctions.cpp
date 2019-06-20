#include "pch.h"
#include "ListeFonctions.h"
#include <map>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

ListeFonctions::ListeFonctions()
{
}


ListeFonctions::~ListeFonctions()
{
}

void ListeFonctions::lecteurImage()
{
	Mat image = imread("lena_color.jpg");
	if (!image.empty()) {
		namedWindow("Affichage", WINDOW_AUTOSIZE);
		imshow("Affichage", image);
		waitKey(0);
		destroyWindow("Affichage");
	}
	else {
		cout << "Ne peut pas ouvrir le fichier" << endl;
	}
}

void ListeFonctions::lecteurVideo()
{
	int idCamera = 0;
	VideoCapture video = NULL;
	Mat frame;
	video.open(idCamera);
	namedWindow("Video", WINDOW_AUTOSIZE);
	while (video.isOpened()) {
		video >> frame;
		if (!frame.empty()) {
			imshow("Video", frame);
			if (waitKey(33) >= 0) {
				destroyWindow("Affichage");
				break;
			}
				
		}
		else {
			cout << "Ne peut pas ouvrir le flux" << endl;
		}
	}
}

void ListeFonctions::captureImageVideo()
{
	int idCamera = 0;
	string fichierVideo = "anime.mp4";
	VideoCapture video = NULL;
	Mat frame;

	string extention = ".jpg";
	int i = 0;
	string dossier = "frames\\";
	string str1;

	video.open(fichierVideo);
	namedWindow("Video", WINDOW_AUTOSIZE);
	while (video.isOpened()) {
		i++;
		str1 = dossier + to_string(i) + extention;
		video >> frame;
		if (!frame.empty()) {
			imshow("Video", frame);
			imwrite(str1, frame);
			if (waitKey(3) >= 0) {
				destroyWindow("Affichage");
				break;
			}
		}
		else {
			cout << "Ne peut pas ouvrir le flux" << endl;
		}
	}
}

void ListeFonctions::lecturePlusieursFlux()
{
	const int NBCAMERA = 3;

	map <int, VideoCapture> v;
	for (int i = 0; i < NBCAMERA; i++) {
		VideoCapture vid(i);
		if (!vid.isOpened())
			cout << "La camera " << i << " ne peut etre ouverte." << endl;
		else
			v.insert(make_pair(i, vid));
	}

	vector<Mat> frame(v.size());
	char c = 0;
	for (; c != 27;) {
		map<int, VideoCapture>::iterator ite = v.begin();
		for (int i = 0; i < v.size(); i++, ite++) {
			if (ite->second.isOpened()) {
				ite->second >> frame[static_cast<int>(i)];
				imshow(format("Main WebCam %d", i), frame[static_cast<int>(i)]);
			}
		}
		c = waitKey(1);
	}
	map<int, VideoCapture>::iterator ite = v.begin();
	for (size_t i = 0; i < v.size(); i++) {
		ite->second.release();
	}
}

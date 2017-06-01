#include <opencv2\opencv.hpp>
#include<iostream>
#include <string>
#include <vector>
using namespace std;

using namespace cv;

// Grafica el rectangulo 
void dibujador(Mat img, int IN[2], int OUT[2], int xMax, int yMax, int xMin, int yMin) {

	int posx = 0;
	int a = 110;// vertice opuesto a xIn YIn
	int b = 110;
	int min = 100;
	cout << "\nxMax: " << xMax << " yMax:  " << yMax << " Entrada:  (" << IN[0]<<" , " <<IN[1] << ")  Salida:  (" << OUT[0] << " , " <<OUT[1] <<") xMin"<< xMin << " yMin:  " << yMin << ".....";

	Point desX;	// desplazamiento en X

	while ((posx * 100 + a) < xMax*1.4  ) { // desplazamiento horizontal

		rectangle(img, Point((posx*min)+xMin, IN[1] * 2), Point((posx*100+a), b), CV_RGB(0, 255, 0));

	//	rectangle(img, Point( xMin, (IN[1] * 2+100*posx)), Point((posx * 100 + a), b), CV_RGB(0, 255, 0));

		posx ++;

	}

}

void main()
{
	int rows = 600;
	int cols = 800;
	int rec = 150;
	int posy = 0, posx = 0;
	int c = 0;
	int IN[2];				// Coordenadas de la Entrada
	int OUT[2];				// coodenadas de la Salida
	int xMax, yMax;
	int xIN=0, yIN = 0;		// desplazamientos de la entrada inicial al borde

	//crear una imagen de 800x600 pixeles
	//canal BGR de tipo CV_8U( valores de 0 a 255)
	//inicializamos a 0 (color negro)
	Mat binary, hsv, wtr;
	Mat img = imread("laberinto.jpg");

	xMax= img.size().height;
	yMax= img.size().width;
	cout << img;
	cvtColor(img, hsv, CV_BGR2HSV);
	int sensitivity = 15;
	inRange(hsv, Scalar(110, 50, 50), Scalar(130,255,255), binary);  //Detecta Color Azul
//	inRange(wtr, Scalar(0, 0, 255 - sensitivity), Scalar(255, sensitivity, 255), binary); // detecta blanco
	Point anchor = Point(-1, -1);

	Mat element = getStructuringElement(MORPH_RECT,Size(10,10), anchor);
	erode(binary, binary, element);
	dilate(binary, binary, element);

	vector<vector<Point>> contours;
	findContours(binary, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	drawContours(binary, contours, -1, Scalar(255), CV_FILLED);

	for (vector<Point> contour : contours) {
		// dibujar rectangulo
		
		Rect r = boundingRect(contour);
		rectangle(img, r, CV_RGB(255, 0, 0), 2, CV_AA, 0);
		
		if (c == 1) { 
			yIN = r.y; xIN = r.x; 
			cout << "\nRx: " << r.x << " Rwidth:  " << r.width << " Ry:  " << r.y << " r.height:  " << r.height << "....."; 
		}
		Point center(r.x + (r.width / 2), r.y + (r.height / 2));
		

		ostringstream str;
		str << "E/S; " << center.x << "," << center.y;
		putText(img, str.str(), center, FONT_HERSHEY_COMPLEX_SMALL, 0.60, CV_RGB(0, 255, 0), 1, CV_AA);
	
		if (c < 1) {
			c++;
			OUT[0] = center.x; OUT[1] = center.y;
//			cout << "\n" << OUT[0] << " - " << OUT[1];
			
		}

		if (c < 2) {
			
			IN[0] = center.x;  IN[1] = center.y;
//			cout << "\n" << c << " - " << IN[0] << " - " << IN[1];
			
		}
	}

	c = 0;
	dibujador(img, IN, OUT,xMax,yMax,xIN,yIN);	

	imshow("Original", img);
	//imshow("HSV", hsv);
	imshow("Binary", binary);
//	//Rect r = boundingRect(contour);

	waitKey(0);
	posx = 0;
}


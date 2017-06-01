#include <opencv2\opencv.hpp>
#include<iostream>
#include <string>
#include <vector>
using namespace std;

using namespace cv;

// Grafica el rectangulo 

// Variables GLOBALES
const Scalar Blanco		=	Scalar(255.0, 255.0, 255.0);
const Scalar Negro		=	Scalar(0.0, 0.0, 0.0);
const Scalar Azul		=	Scalar(255.0, 0.0, 0.0);
const Scalar Verde		=	Scalar(0.0, 255.0, 0.0);
const Scalar Rojo		=	Scalar(0.0, 0.0, 255.0);

Point Centro(Rect r) {

		Point center(r.x + (r.width / 2), r.y + (r.height / 2));
		return center;
	}

void VerificaColor() {


}

void dibujador(Mat img, int xMax, int yMax, int xMin,int yMin) {

	cout << "\nxMax: " << xMax << " yMax:  " << yMax << " xmin: " << xMin << "  Ymin  " << yMin<<"...."<<endl;

	int lado = 100; // lado del Cuadrado de referencia

// Elementos Necesarios Para el Rectangulo
	int VSIx = xMin;		// Coordenadas superior IZQ
	int VSIy = yMin;

	int VIDx = xMin + 100;	//	Coordenadas Vertice Opuesto al anterior
	int VIDy = yMin + 100;	

	int Sx = 0, Sy = 0, Ix = 0, Iy =0;
	//rectangle(img, Point(0, 0), Point(100, 100), Verde);
/*
	rectangle(img, Point(37, 46), Point(137, 146), Verde);
	rectangle(img, Point(37, 146), Point(137, 246), Verde);
	rectangle(img, Point(37, 246), Point(137, 346), Verde);
	rectangle(img, Point(37, 346), Point(137, 446), Verde);
	rectangle(img, Point(37, 446), Point(137, 546), Verde);
	rectangle(img, Point(37, 546), Point(137, 646), Verde);
	rectangle(img, Point(37, 646), Point(137, 746), Verde);
	*/

	for (int i= 0; i<(xMax/lado)+1; i++)
	{ 
		for (int j = 0; j < (yMax / lado)+1; j++)
		{
			cout << "i: " << i << " , " << " j: " << j << endl;
			cout << "VSI (" << Sx << "," << Sy << " ) " << "VID (" << Ix << "," << Iy << " ) " << endl;
			
			rectangle(img, Point(Sx,Sy), Point(Ix, Iy), Verde);
			Sx = VSIx + 100 * i; Sy = VSIy + 100 * j;
			Ix = VIDx + 100 * i; Iy = VIDy + 100 * j;
		}

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
	int xIN = 0, yIN = 0;		// desplazamientos de la entrada inicial al borde

								//crear una imagen de 800x600 pixeles
								//canal BGR de tipo CV_8U( valores de 0 a 255)
								//inicializamos a 0 (color negro)
	Mat binary, hsv, wtr;
	Mat img_0 = imread("laberinto.jpg");
	Mat img;
	resize(img_0, img, Size(800, 600), 0, 0, INTER_LINEAR);  // ya es de 800x600 por defecto
	imwrite("LABv2.jpg", img);



	xMax = img.size().height;
	yMax = img.size().width;
	//	cout << img;

	cvtColor(img, hsv, CV_BGR2HSV);
	int sensitivity = 15;
	inRange(hsv, Scalar(110, 50, 50), Scalar(130, 255, 255), binary);  //Detecta Color Azu
	//inRange(hsv, Scalar(255, 255, 255), binary); // detecta blanco
	Point
		anchor = Point(-1, -1);

	Mat element = getStructuringElement(MORPH_RECT, Size(10, 10), anchor);
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
			yIN = r.y + r.height; xIN = r.x;
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

	dibujador(img, xMax, yMax, xIN, yIN);

	imshow("Original", img);
	//imshow("BIniraio", binary);

	waitKey(0);
	posx = 0;
}


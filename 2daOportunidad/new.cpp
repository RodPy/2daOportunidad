	/* PARA USAR LA CAMARA
	VideoCapture cap(0);

	// verificar si se ha podido acceder a la web cam
	if (!cap.isOpened()) {
	cout << "Error al acceder a la web cam." << endl;
	system("pause");
	return -1;
	}

	*/ // Para Usar la Camara

	/*
	while (true)
	{
		// obtener frame de la web cam
		//	cap >> img;

		img1 = imread("maze0.jpg");
		img = imread("maze0.jpg");


		// convertir imagen RGB a HSV 
		cvtColor(img, hsv, CV_BGR2HSV);

		// aplicar filtro para color deseado

		inRange(hsv, Scalar(110, 50, 50), Scalar(130, 255, 255), binary);

		// aplicar tranformaciones morfologicas (extrae la region de interes)
		Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
		erode(binary, binary, element);
		dilate(binary, binary, element);

		// buscar contornos en la imagen binaria
		vector< vector<Point> > contours;
		
		findContours(binary, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
		
		// dibujar todos los contornos encontrados
		drawContours(binary, contours, -1, Scalar(255), CV_FILLED);

		// dibujar rectangulo y texto con coordenadas (x, y)
		for (vector<Point> contour : contours) {
			// dibujar rectangulo
			Rect r = boundingRect(contour);
			rectangle(img, r, CV_RGB(255, 0, 0), 2, CV_AA, 0);

			Point center(r.x + (r.width / 2), r.y + (r.height / 2));

			ostringstream str;
			str << "E/S; " << center.x << "," << center.y;
			
			if (c < 1) {
				c++;
				INx = center.x;  INy= center.y;
			}

			if (c < 2) {
				c++;
				OUTx = center.x; OUTy= center.y;
			}
			// mostrar texto (x, y)
			putText(img, str.str(), center, FONT_HERSHEY_COMPLEX_SMALL, 0.60, CV_RGB(0, 255, 0), 1, CV_AA);
		}
		imshow("ORIGNAL", img1);
	//	imshow("ORIGNAL2", img1.cross(1,1));

		imshow("Deteccion de Entrada Salida", img);
		imshow("Track Color - Binary", binary);

		// terminar la aplicacion con la tecla ESC
		if (waitKey(30) == 27) break;
		cout << "\nEntrada" << "x: " << INx+1 << ", y: " << INy;
		cout << "\nSalida" << "x: " << OUTx+300 << ", y: " << OUTy;;
	}
*/
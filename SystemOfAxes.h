#ifndef SYSTEMOFAXES_H
#define SYSTEMOFAXES_H

#include <vector>
#include <math.h>

using std::vector;

class SystemOfAxes
{
	public:

	SystemOfAxes()
	:vertexCount(0)
	{

    }
	// Нарисовать сцену
	void RenderScene(TForm *frm)
	{
		widthFormX = frm->Width;
		heightFormY = frm->Height;

		_centerX = widthFormX / 2;
		_centerY = heightFormY  / 2;

		Graphics::TBitmap*   gBitmap = new Graphics::TBitmap;

		gBitmap->Width = widthFormX;
		gBitmap->Height = heightFormY;

		systemOfAxes(gBitmap);
		DrawPoints(gBitmap);
		DrawTriangles(gBitmap);

		frm->Canvas->Draw(0,0, gBitmap);
	}

	// нарисовать систему координат
	void systemOfAxes(TBitmap *btm)
	{
		// Рисуем ось X
		btm->Canvas->MoveTo(_centerX, 0);
		btm->Canvas->LineTo(_centerX, heightFormY);
		for(int xp = _centerX, xm = _centerX; (xp < widthFormX) || (xm > widthFormX); xp+=5, xm-=5)
			{
			   btm->Canvas->MoveTo(xp, _centerY-3);
			   btm->Canvas->LineTo(xp, _centerY+4);

			   btm->Canvas->MoveTo(xm, _centerY-3);
			   btm->Canvas->LineTo(xm, _centerY+4);
			}

		// рисуем оси Y
		btm->Canvas->MoveTo(0, _centerY);
		btm->Canvas->LineTo(widthFormX, _centerY);
		for(int yp = _centerY, ym = _centerY; (yp < heightFormY) || (ym > heightFormY); yp+=5, ym-=5)
			{
			   btm->Canvas->MoveTo(_centerX-3, yp);
			   btm->Canvas->LineTo(_centerX+4, yp);

			   btm->Canvas->MoveTo(_centerX-3, ym);
			   btm->Canvas->LineTo(_centerX+4, ym);;
			}
	}

	// Вывести координаты
	void coordnets(TForm *frm, int X, int Y)
	{
		AnsiString str;

		str +=  X - _centerX;
		str +=  " ";
		str +=  -Y + _centerY;

		frm->Canvas->TextOut(X+20, Y, str);
	}

	// нарисовать точки
	void DrawPoints(TBitmap *bitmap)
	{
		char ch = 'A';

			for(int i = 0; i < XY.size(); i+=2)
			{
			bitmap->Canvas->Brush->Color = clRed;
			bitmap->Canvas->Ellipse(XY[i]-3, XY[i+1]-3, XY[i]+3, XY[i+1]+3);
			bitmap->Canvas->Brush->Color = clWhite;
			bitmap->Canvas->TextOut(XY[i]+3, XY[i+1]+3, ch);
			ch++;
			}
	}

	// добавить вершину треугольника
	void AddPoint(int X, int Y)
	{
		XY.push_back(X);
		XY.push_back(Y);
		vertexCount++;

		if(vertexCount > 3)
		{
			std::vector<int>().swap(XY);
			vertexCount = 0;
        }
	}

	// Нарисовать треугольник
	void DrawTriangles(TBitmap *btm)
	{
	   if(vertexCount >= 3)
	   {
			btm->Canvas->Pen->Width = 2;
			btm->Canvas->Pen->Color = clBlue;
		   for(int i = 0; i < XY.size(); i+= 6)
		   {
			btm->Canvas->MoveTo(XY[i], XY[i+1]);
			btm->Canvas->LineTo(XY[i+2], XY[i+3]);

			btm->Canvas->MoveTo(XY[i+2], XY[i+3]);
			btm->Canvas->LineTo(XY[i+4], XY[i+5]);

			btm->Canvas->MoveTo(XY[i+4], XY[i+5]);
			btm->Canvas->LineTo(XY[i], XY[i+1]);
		   }

			computeAgnles(btm);
			btm->Canvas->Pen->Width = 1;
			btm->Canvas->Pen->Color = clBlack;
		}
    }

	void computeAgnles(TBitmap *btm)
	{
		int string = 0;
		double AB, AC, BC;
		AnsiString str = "";

		str = "Сторона:\n";
		AB = sqrt(pow(XY[2] - XY[0],2.0) + pow(XY[3] - XY[1], 2.0));
		str += "AB = ";
		str += AB;
		btm->Canvas->TextOut(0,string, str);

		str = "Сторона:\n";
		AC = sqrt(pow(XY[4] - XY[0],2.0) + pow(XY[5] - XY[1], 2.0));
		str += "AC = ";
		str += AC;
		string +=15;
		btm->Canvas->TextOut(0,string, str);

		str = "Сторона:\n";
		BC = sqrt(pow(XY[4] - XY[2],2.0) + pow(XY[5] - XY[3], 2.0));
		str += "BC = ";
		str += BC;
		string+=15;
		btm->Canvas->TextOut(0,string, str);

		double A_angle, B_angle, C_angle, cosine;

		string+=15;
		str = "Угол:\n";
		A_angle = acos((pow(AB,2.0) + pow(AC, 2.0) - pow(BC,2.0)) /( 2 * AB * AC)) * 180.0 / 3.14159;
		str += "A = ";
		str += A_angle;
		string+=15;
		btm->Canvas->TextOut(0,string, str);

		str = "Угол:\n";
		B_angle = acos((pow(AB,2.0) + pow(BC, 2.0) - pow(AC,2.0)) /( 2 * AB * BC)) * 180.0 / 3.14159;
		str += "B = ";
		str += B_angle;
		string+=15;
		btm->Canvas->TextOut(0,string, str);

		str = "Угол:\n";
		C_angle = acos((pow(AC,2.0) + pow(BC, 2.0) - pow(AB,2.0)) /( 2 * AC * BC)) * 180.0 / 3.14159;
		str += "C = ";
		str += C_angle;
		string+=15;
		btm->Canvas->TextOut(0,string, str);
		//savePic(btm);
	}

	void savePic(TBitmap *btm)
	{
		AnsiString file = "Vertex ";

		file +=XY[0];
		file +=XY[1];
		file += " ";

		file +=XY[2];
		file +=XY[3];
		file += " ";

		file +=XY[4];
		file +=XY[5];

		btm->SaveToFile(file + ".bmp");
	}

	private:
	int _centerX;
	int _centerY;
	int widthFormX;
	int heightFormY;

	int vertexCount;

	vector<int> XY;
};

#endif
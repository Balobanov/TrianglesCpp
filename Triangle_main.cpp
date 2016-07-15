//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Triangle_main.h"
#include   "SystemOfAxes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
SystemOfAxes soa;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormPaint(TObject *Sender)
{
	soa.RenderScene(Form1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)

{
	 soa.RenderScene(Form1);
	 soa.coordnets(Form1, X, Y);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	if(Button == mbLeft)
	soa.AddPoint(X, Y);

	//soa.AddPoint(-6,1);
	//soa.AddPoint(6,-2);
}
//---------------------------------------------------------------------------






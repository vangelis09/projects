//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button2Click(TObject *Sender)
{
	Form2->Color = clRed;
	Form1->Color = clYellow;
	Form1->Panel1->Color = clRed;
	Form1->Shape1->Brush->Color = clBlue;
	RadioButton1->Checked = true;
	RadioButton2->Checked = false;
	RadioButton3->Checked = true;
	Form1->sound = true;
	Form1->MediaPlayer1->FileName ="easy.mp3";
	Form1->MediaPlayer1->Open();
	Form1->MediaPlayer1->Play();

}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button3Click(TObject *Sender)
{


	if(RadioButton3->Checked == true)
	{
	 easy = true;
	 energy = false;
	 pantera = false;
	 no_sound = false;
	}
	if(RadioButton4->Checked == true)
	{
	 easy = false;
	 energy = true;
	 pantera = false;
	 no_sound = false;
	}
	if(RadioButton5->Checked == true)
	{
	 easy = false;
	 energy = false;
	 pantera = true;
	 no_sound = false;
	}
	if(RadioButton6->Checked == true)
	{
	 easy = false;
	 energy = false;
	 pantera = false;
	 no_sound = true;
	}

    Form2->Close();
}
//---------------------------------------------------------------------------

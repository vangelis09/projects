//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	jump_height = 20;
	step = 5;
	score = 0;
	jump = false;
	fall = false;
	N = 0;
	M = 0;
	interval = 10;
	end = false;
	speed = 10;
	sound = true;
	MediaPlayer1->Open();
    MediaPlayer1->Play();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
	if(N < 50 && end == false)
	{
		bars[N] = new TShape(Form1);
		bars[N]->Parent = Form1;

		bars[N]->Shape = stRectangle;
		bars[N]->Height = 45;
		bars[N]->Width = 25;
		bars[N]->Brush->Color = clGreen;
		bars[N]->Top = Panel1->Top - bars[N]->Height;
		bars[N]->Left = ClientWidth - 10;
		bars[N]->Visible = true;
		way[N] = ClientWidth + 10;

		t[N] = new TTimer(this);
		t[N]->Interval = interval;
		t[N]->OnTimer = tTimer;

		N++;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer3Timer(TObject *Sender)
{
	if(M < 50 && end == false)
	{
		bars1[M] = new TShape(Form1);
		bars1[M]->Parent = Form1;

		bars1[M]->Shape = stRectangle;
		bars1[M]->Height = 25;
		bars1[M]->Width = 25;
		bars1[M]->Brush->Color = clRed;
		bars1[M]->Top = Panel1->Top - bars1[M]->Height;
		bars1[M]->Left = ClientWidth - 10 - rand()%15;
		bars1[M]->Visible = true;
		way1[M] = ClientWidth + 25;

		t1[M] = new TTimer(this);
		t1[M]->Interval = interval;
		t1[M]->OnTimer = t1Timer;

		M++;

	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::tTimer(TObject *Sender)
{
	for(int i = 0; i < N; i++)
	{
		if(Sender == t[i])
		{
			if(way[i] > 0)
			{
				int Y = bars[i]->Top;
				int X = bars[i]->Left;

				bars[i]->Left = bars[i]->Left - 10;
				way[i]-=10;
				if(Y >= Shape1->Top && Y <= Shape1->Top + Shape1->Height &&
				X >= Shape1->Left && X <= Shape1->Left + Shape1->Width)
				{
					end = true;
					Timer1->Enabled = false;
					Timer2->Enabled = false;
					Label1->Caption = "GAME OVER!";

				}
				if(Shape1->Left == bars[i]->Left + bars[i]->Width + 3 && end == false){
					score++;
					Label2->Caption = "SCORE: " + IntToStr(score);
				}
				if(i == 49 && end == false)
				{
					end = true;
					Timer1->Enabled = false;
					Timer2->Enabled = false;
					Label1->Caption = "!!!YOU WIN!!!";
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::t1Timer(TObject *Sender)
{
	for(int i = 0; i < M; i++)
	{
		if(Sender == t1[i])
		{
			if(way1[i] > 0)
			{
				int Y = bars1[i]->Top;
				int X = bars1[i]->Left;

				bars1[i]->Left = bars1[i]->Left - 10;
				way1[i]-=10;
				if(Y >= Shape1->Top && Y <= Shape1->Top + Shape1->Height &&
				X >= Shape1->Left && X <= Shape1->Left + Shape1->Width)
				{
					end = true;
					Timer1->Enabled = false;
					Timer2->Enabled = false;
					Label1->Caption = "GAME OVER!";

					MediaPlayer1->FileName = "explosion.mp3";
					MediaPlayer1->Open();
					MediaPlayer1->Play();

				}
				if(Shape1->Left == bars1[i]->Left + bars1[i]->Width && end == false){
					score++;
					Label2->Caption = "SCORE: " + IntToStr(score);
				}
				if(i == 49 && end == false)
				{
					end = true;
					Timer1->Enabled = false;
					Timer2->Enabled = false;
					Label1->Caption = "!!!YOU WIN!!!";

				}
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Panel1Click(TObject *Sender)
{
	 if(Shape1->Top > 220) jump = true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	if(jump == true && fall == false)
	{
		jump_height--;
		if(jump_height > 0)
		{
			Shape1->Top = Shape1->Top - step;

		}
		if(jump_height == 0)
		{
			jump = false;
            fall = true;
        }
	}
	if(fall == true && jump == false)
	{
		jump_height++;
		if(jump_height < 20)
		{
			Shape1->Top = Shape1->Top + step;
		}
		if(jump_height == 20)
		{
			fall = false;
		}
	}
}




void __fastcall TForm1::Button2Click(TObject *Sender)
{

	Timer2->Interval = 1800;
	Timer2->Enabled = true;
	Timer3->Enabled = true;
	Timer1->Enabled = true;

	jump = false;
	fall = false;
	N = 0;
	end = false;
	pause = false;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	 if(pause == false)
	 {
		 pause = true;
		 Button3->Caption = "Continue";
		 Timer2->Enabled = false;
		 Timer1->Enabled = false;
		 Timer3->Enabled = false;

         for(int i = 0; i < N; i++)
		 {
			 t[i]->Enabled = false;
		 }
	 }
	 else
	 {
		 pause = false;
		 Button3->Caption = "Pause";
		 Timer2->Enabled = true;
		 Timer1->Enabled = true;
		 Timer3->Enabled = true;
         for(int i = 0; i < N; i++)
		 {
			 t[i]->Enabled = true;
		 }
	 }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormCanResize(TObject *Sender, int &NewWidth, int &NewHeight,
          bool &Resize)
{
	if (NewWidth != ClientWidth || NewHeight != ClientHeight) {
		NewWidth = 700;
		NewHeight = 455;
	}
}
//---------------------------------------------------------------------------



void __fastcall TForm1::N4Click(TObject *Sender)
{
    Form2->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N5Click(TObject *Sender)
{

	if (Form2->RadioButton1->Checked == true) {
		Form2->Color = clRed;
		Form1->Color = clYellow;
		Form1->Panel1->Color = clRed;
		Form1->Shape1->Brush->Color = clBlue;
	}
	else{
		Form2->Color = clBlue;
		Form1->Color = clBlue;
		Form1->Panel1->Color = clBlack;
		Form1->Shape1->Brush->Color = clYellow;
	}


	if (Form2->easy == true) {
		MediaPlayer1->FileName = "easy.mp3";
		MediaPlayer1->Open();
		MediaPlayer1->Play();
	}
	if (Form2->energy == true) {
		MediaPlayer1->FileName = "energy.mp3";
		MediaPlayer1->Open();
		MediaPlayer1->Play();
	}
	if (Form2->pantera == true) {
		MediaPlayer1->FileName = "pantera.mp3";
		MediaPlayer1->Open();
		MediaPlayer1->Play();
	}
	if (Form2->no_sound == true) {
		MediaPlayer1->Stop();
	}
}
//---------------------------------------------------------------------------


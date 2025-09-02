//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.MPlayer.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TShape *Shape1;
	TTimer *Timer1;
	TTimer *Timer2;
	TButton *Button2;
	TButton *Button3;
	TLabel *Label1;
	TTimer *Timer3;
	TLabel *Label2;
	TMainMenu *MainMenu1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMediaPlayer *MediaPlayer1;
	TMenuItem *N4;
	TMenuItem *N5;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Timer2Timer(TObject *Sender);
	void __fastcall Timer3Timer(TObject *Sender);
	void __fastcall tTimer(TObject *Sender);
    void __fastcall t1Timer(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Panel1Click(TObject *Sender);
	void __fastcall FormCanResize(TObject *Sender, int &NewWidth, int &NewHeight, bool &Resize);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	TShape* bars[50];
	TTimer* t[50];
	TShape* bars1[50];
	TTimer* t1[50];

	int jump_height;
	int step;
    int score;
	int way[50];
	int way1[50];
	int speed;
	bool jump;
	bool fall;
	int N, M;
	bool end;
	int interval;
	bool pause;
    bool sound;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

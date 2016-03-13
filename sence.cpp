#include "game.h"
#include <playsoundapi.h>//paly background music


//主场景的实现
void home_senc(void)
{ 
	cleardevice();
	setcaption("game!");
	PIMAGE imag = newimage();
	getimage(imag,"bg_s.png");
	putimage(0,-1,imag);
	PlaySound(TEXT("1.wav"), NULL, SND_FILENAME | SND_ASYNC| SND_LOOP);
	button_start();
	delimage(imag);
	getch();
}

//开始按钮的实现
void button_start(){
	int x,y;
	bool isrespon = false;
	mouse_msg msg;
	//bar(280,430,350,454);//设置
	//bar(182,430,252,454);//问题
	//bar(280,610,380,650);//设置
	//bar(380,430,450,454);//退出
	do
	{
	msg = getmouse();
	mousepos(&x,&y);
	if(msg.msg == mouse_msg_up){
			//开始
		if(x>240 && x<400 && y>310 && y<358){
			cleardevice();
			play();
			isrespon = true;
		}else if(x>182 && x<252 && y>430 && y<454){
			//设置
			cleardevice();
			button_Set();
			isrespon = true;
		}else if(x>280 && x<350 && y>430 && y<454){
			//问题
			cleardevice();
			button_Question();
			isrespon = true;
		}else if(x>380 && x<450 && y>430 && y<454){
			//退出
			//cleardevice();
			//button_Exit();
			//isrespon = true;
		}
		continue;	
	}
	}while(!isrespon);
}

//设置按钮的实现
void button_Set(){
	setfont(20,0,"宋体");
	setbkcolor(0);
	setcolor(WHITE);
	PIMAGE img = newimage();
	getimage(img,"rest_no.png");
	putimage(170,150,img);
	outtextxy(195,150,"Input anykey back to home... please!");
	//setfont(20,0,"宋体");
	outtextxy(270,200,"(Working......)");
	setbkcolor(EGERGB(56,54,53));
	getch();
	home_senc();
}

//问题按钮的实现
void button_Question(){
	setfont(40,0,"宋体");
	setcolor(WHITE);
	outtextxy(290,30,"Tips");
	setbkcolor(0);
	setcolor(WHITE);
	PIMAGE item = newimage();
	getimage(item,"rest_no.png");
	putimage(60,100,item);
	setfont(20,0,"宋体");
	outtextxy(80,100,"using 'w' 's' 'a' 'd' hotkey to controll....");
	setfont(10,0,"宋体");
	outtextxy(60,440,"Version 0.01 snake game");
	outtextxy(60,450,"Copyright@ 2015 wonly");
	setbkcolor(EGERGB(56,54,53));
	getch();
	home_senc();

}

//退出按钮的实现
void button_Exit(){
	//char *string = "game";
	/*HWND hWnd=::GetActiveWindow();
	::SendMessage(hWnd,WM_CLOSE,0,0);*/
}
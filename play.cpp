#include "game.h"

#define  LEN  50
#define SPEED 200

//蛇结构体
struct Snake
{
	int x[LEN];
	int y[LEN];
	int node;
	int life_s;
	int direction;
	int score;
	char *sna_hed_na;
 }snake = {{220},{220},3,3,1,0,"snake_l.png"};

//食物结构体
 struct Food
 {
	bool haveFood;
	int fx;
	int fy;
 }apple;

 //障碍物
 struct Object
 {
	int ox;
	int oy;
	int obj_num;
	bool have_obj;
 }obje;

//全局定义
mouse_msg ms;
char move;


//画网格
void draw_gre(){
	setcolor(EGERGB(34,35,36));
	for(int i = 60; i < 580;i +=20){
		for(int j = 20; j < 460;j +=20){
			line(i,j,580,j);
			line(i,j,i,460);
		}
	}
}

//更新蛇的位置
void move_snake(){
	for(int i = snake.node-1; i > 0;i--){
		snake.x[i] = snake.x[i-1];
		snake.y[i] = snake.y[i-1];
	}
}

//画蛇
void paint_snake(){

	PIMAGE imag1 = newimage();
	PIMAGE imag2 = newimage(); 

	getimage(imag1,snake.sna_hed_na);
	getimage(imag2,"body.png");
	for(int i = 0; i < snake.node-1; i ++){
		if(i==0){
			putimage(snake.x[i],snake.y[i],imag1);
		}else{
			putimage(snake.x[i],snake.y[i],imag2);
		}
	}
	
	//delay(1000000);//debug```````````````````````````````````````````````````````````````````
	setcolor(EGERGB(56,54,53));
	bar(snake.x[snake.node-1],snake.y[snake.node-1],snake.x[snake.node-1]+20,snake.y[snake.node-1]+20);
	draw_gre();
	delay(SPEED);

	delimage(imag1);
	delimage(imag2);
}

//画围墙
void paint_fence(int width,int height,int space){
	PIMAGE imag_score = newimage();
	PIMAGE imag_bacg = newimage(); 
	PIMAGE imag_w = newimage();
	getimage(imag_w,"wall.png");
	getimage(imag_score,"apple20.png");
	putimage(610,20,imag_score);
	for(int j = space; j <= width+20;j += 20){
		putimage(j,0,imag_w);
		putimage(j,height-20,imag_w);
	}
	for(int i = height; i >= 0; i -= 20){
		putimage(space,i,imag_w);
		putimage(width+20,i,imag_w);
	}

	delimage(imag_w);
}

//随机产生苹果
void creat_apple(){
	PIMAGE imag_f = newimage();
	getimage(imag_f,"apple.png");
	if(apple.haveFood){
		do{
		apple.fx = random(640-120)+60;
		apple.fy = random(480-80)+40;
		//						框格x							框格y							蛇x										蛇y									障碍物x							障碍物x+30						障碍物y							障碍物y+30
		}while(apple.fx%20!= 0 || apple.fy%20 != 0 /*|| apple.fx != snake.x[0] || apple.fy != snake.y[0]);|| apple.fx != obje.ox || apple.fx != obje.ox+30 || apple.fy != obje.oy || apple.fy != obje.oy+30*/);
		apple.haveFood = false;
	}
	if(!apple.haveFood){
		putimage(apple.fx,apple.fy,imag_f);
	}
	delimage(imag_f);
}

//识别当前行走方向
void recognition_dir(){
	//1-L ,2-R,3-U,4-D
	switch(snake.direction)
	{
	case 1:
		snake.x[0] -= 20;
		break;
	case 2:
		snake.x[0] += 20;
		break;
	case 3:
		snake.y[0] -= 20;
		break;
	case 4:
		snake.y[0] += 20;
		break;
	default:
		break;
	}
}

//响应按钮改变方向
void respons_button(){
	char move = getch();
	switch(move){
	case 'w':
		if(snake.direction != 4)
			snake.direction = 3;
			change_Image();
			break;
	case 's':
		if(snake.direction != 3)
			snake.direction = 4;
			change_Image();
			break;
	case 'a':
		if(snake.direction != 2)
			snake.direction = 1;
			change_Image();
			break;
	case 'd':
		if(snake.direction != 1)
			snake.direction = 2;
			change_Image();
			break;
	default:
			break;
	}


}
 
//适时旋转头像!
void change_Image(){
	//1-L ,2-R,3-U,4-D
	/*PIMAGE img_h = newimage(30,30);*/
	switch(snake.direction)
	{
	case 1:
		snake.sna_hed_na = "snake_l.png";
		break;
	case 2:
		snake.sna_hed_na = "snake_r.png";
		break;
	case 3:
		snake.sna_hed_na = "snake_u.png";
		break;
	case 4:
		snake.sna_hed_na = "snake_d.png";
		break;
	}
}

//游戏结束 ----------------------------------------------------------------------------
void game_over(){   
	//LOGFONT font;
	char score[100];
	itoa(snake.score,score,10);
	int x,y;
	cleardevice();
	PIMAGE over_im = newimage();
	getimage(over_im,"rest.png");
	putimage(271.5,40,over_im);
	bool isback = false;
	do
	{
		setbkcolor(EGERGB(56,54,53));
		setcolor(WHITE);
		setfont(50,0,"宋体");
		outtextxy(240,180,"Score:");
		outtextxy(390,180,score);
		setcolor(BLUE);
		setfont(30,0,"宋体");
		outtextxy(290,260,"back");
		ms = getmouse();
		mousepos(&x,&y);
		if(ms.msg == mouse_msg_up){
			if(x >=290 && x <= 340 && y >= 260 && y <=290){
				isback = true;
				snake.life_s = 3;
				home_senc();
				}
			}
	}while(!isback);
}

// 撞到墙
void opinion_coli(){
	//1-L ,2-R,3-U,4-D
	if(snake.direction ==1){
		//					left				right					up					down
			if(snake.x[0] <= 60){
					collition_blink();
					snake.life_s --;
					print_life();
					play();
					//left											right										up								down
			}else if(obje.have_obj){
				if(((obje.ox+20 == snake.x[0]) &&  (obje.oy == snake.y[0])) || ((obje.ox+20 == snake.x[0]) && (obje.oy+20 == snake.y[0]))){
					collition_blink();
					snake.life_s --;
					print_life();
					play();
				}
			}
	}else if(snake.direction == 2){
			//left											right										up								down
			 if(snake.x[0] >= 560){
					collition_blink();
					snake.life_s --;
					print_life();
					play();
			}else if(obje.have_obj){
				  if((obje.ox == snake.x[0] && obje.oy == snake.y[0]) || (obje.ox == snake.x[0] && obje.oy+20 == snake.y[0])){
					collition_blink();
					snake.life_s --;
					print_life();
					play();
				}
			}
	}else if(snake.direction == 3){
			//left									right									up								down
			  if(snake.y[0] <= 20){
					collition_blink();
					snake.life_s --;
					print_life();
					play();
			}else if(obje.have_obj){
					if(((obje.ox == snake.x[0]) &&  (obje.oy+20 == snake.y[0])) || ((obje.ox+20 == snake.x[0]) && (obje.oy+20 == snake.y[0]))){
					collition_blink();
					snake.life_s --;
					print_life();
					play();
					}
			}
	}else if(snake.direction == 4){
			//left								right									up								down
			if(snake.y[0] >= 440){
					collition_blink();
					snake.life_s --;
					print_life();
					play();
			}else if(obje.have_obj){
				if(((obje.ox == snake.x[0]) &&  (obje.oy == snake.y[0])) || ((obje.ox+20 == snake.x[0]) && (obje.oy == snake.y[0]))){
					collition_blink();
					snake.life_s --;
					print_life();
					play();
				}
			}
	}
		
}

//吃到食物
void opinion_eatFood(){
	  if(snake.x[0] == apple.fx && snake.y[0] == apple.fy){
		apple.haveFood = true;
		eat_blink();
		setcolor(0);
		bar(apple.fx,apple.fy,apple.fx+20,apple.fy+20);
		creat_apple();
		snake.node ++;
		snake.score ++;
		if(snake.life_s < 3){
			snake.life_s++;
			print_life();
		}
		print_score();
	
	}
}

//闪烁
void collition_blink(){
		setcolor(RED);
		//bar(snake.x[0],snake.y[0],snake.x[snake.node-1]+30,snake.y[snake.node-1]+30);
		for(int i = 0; i < snake.node-1;i++){
			bar(snake.x[i],snake.y[i],snake.x[i]+20,snake.y[i]+20);
		}
		delay(100);
		paint_snake();
		delay(100);
		for(int i = 0; i < snake.node-1;i++){
			bar(snake.x[i],snake.y[i],snake.x[i]+20,snake.y[i]+20);
		}
		delay(100);
		paint_snake();
		delay(100);
		for(int i = 0; i < snake.node-1;i++){
			bar(snake.x[i],snake.y[i],snake.x[i]+20,snake.y[i]+20);
		}
		delay(100);
		paint_snake();

}

//吃到食物闪烁
void eat_blink(){
	if(snake.node %3 != 0)
	{
		setcolor(BROWN);
		bar(snake.x[0],snake.y[0],snake.x[0]+20,snake.y[0]+20);
		delay(100);
		paint_snake();
		delay(100);
		bar(snake.x[0],snake.y[0],snake.x[0]+20,snake.y[0]+20);
		delay(100);
		paint_snake();
	}else{
		char *alert = "Challenge is coming! Any key to continue ....";
		setcolor(CYAN);
		setfont(15,0,"宋体");
		outtextxy(200,240,alert);
			getch();
			setcolor(0);
			bar(200,240,440,255);
			draw_gre();
			win();
		}
}

//吃到自己
void eat_self(void){
	for(int i =3; i < snake.node-1;i++){
		if(snake.x[0] == snake.x[i] && snake.y[0] == snake.y[i]){
			snake.life_s --;
			play();
			break;
		}
	}
}

//游戏执行主函数
void play(){
            cleardevice();
			setbkcolor(EGERGB(0,0,0));//背景有更改
			snake.x[0] = 220;
			snake.y[0] = 220;
			snake.x[1] = 240;
			snake.y[1] = 220;
			snake.direction = 1;
			snake.node =3;
			snake.sna_hed_na = "snake_l.png";
			apple.haveFood = true;
			paint_fence(560,480,40);
			print_score();
			print_life();
			obje.have_obj = false;
			draw_gre();
		do
			{
				while(!kbhit())
				{
					creat_apple();
					paint_snake();
					opinion_coli();
					move_snake();
					recognition_dir();
					opinion_eatFood();
					eat_self();
					//setbkcolor(EGERGB(56,54,53));
					if(snake.life_s == 0)
								game_over();
				}
				respons_button();
			}while(move != 'q');	
}

//随机产生障碍物
void random_object(){

}

//提示框 显示生命值
void print_life(){
	PIMAGE img_life = newimage();
	switch(snake.life_s){
	case 1:
		getimage(img_life,"cry.png");
		break;
	case 2:
		getimage(img_life,"sad.png");
		break;
	case 3:
		getimage(img_life,"smal.png");
		break;
	default:
		break;
	}
	setcolor(WHITE);
	char life_number[100];
	itoa(snake.life_s,life_number,10);
	setfont(25,0,"宋体");
	outtextxy(615,100,life_number);
	putimage(612,80,img_life);

	delimage(img_life);
}

//模糊背景
void blur_bag(){
	PIMAGE img_bg = newimage();
	PIMAGE img_rest = newimage();
	getimage(img_rest,"rest.png");
	getimage(img_bg,"bg.png");
	//burll 0~127  alph 0~255
	imagefilter_blurring(img_bg,50,125,0,0,0,0);
	putimage(0,0,img_bg);
	
	getch();
	delimage(img_bg);
}

//进入下一关
void enter_next(){
	PIMAGE img_next = newimage();
	getimage(img_next,"congratulation.png");
	putimage(0,0,img_next);
	getch();
	delimage(img_next);
}

//输出snake的分数
void print_score(){
	char score_number [100];
	itoa(snake.score,score_number,10);
	setcolor(WHITE);
	setfont(25,0,"Arial");
	if(snake.score > 9){
		outtextxy(608,40,score_number);
	}else{
		outtextxy(614,40,score_number);
	}
	//outtextxy(910,70,"个");
}


//------------------------产生障碍物
//随机产生障碍物坐标
void creat_new_ob_position(){
	do
	{
		obje.ox = random(640-140)+60;
		obje.oy = random(480-60) +20;
	}while(obje.ox % 40 != 0 || obje.oy % 40 != 0);
	
}


//创建障碍物
void creat_obje(){
	//obje.have_obj = false;
	obje.obj_num = 1;
	PIMAGE obj_img = newimage();
	getimage(obj_img,"obj1.png");
	for(int ob = 0;ob < obje.obj_num;ob++){
		creat_new_ob_position();
		putimage(obje.ox+1,obje.oy+1,obj_img);
	}
	delimage(obj_img);
}

//判断是否通关
void win(){
//	PIMAGE img_win = newimage();
	//bool isnext = true;
	//mouse_msg msge;
	//getimage(img_win,"congratulation.png");
	//if(snake.node != 4){
		//cleardevice();
		//putimage(0,0,img_win);
	
	//msge = getmouse();
//	if(msge.msg == mouse_msg_up){
				/*	putimage_transparent(img_win,img_win,0,0,0,0,NULL);*/
					creat_obje();
					obje.obj_num ++;
					obje.have_obj = true;
//	}

}
	
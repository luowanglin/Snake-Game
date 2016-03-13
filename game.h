#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

/*开始页面----------------------------------------------------------------
*主场景通过开始按钮响应 游戏场景 play（）方法 实现游戏的开始
*游戏结束页 通过响应返回按钮 调用home_senc()方法 回到主页
*/
//设置开始界面的及布局
void home_senc(void);

//开始按钮的响应
void button_start();

//设置按钮的实现
void button_Set();

//问题按钮的实现
void button_Question();

//退出按钮的实现
void button_Exit();


/*游戏场景------------------------------------------------------------------
*通过在play（）赋予相关初始值，调用各模块方法已实现各功能
*/
//画网格背景
void draw_gre();

//画蛇
void paint_snake();

//移动蛇
void move_snake();

//画围墙
void paint_fence(int width,int height,int space);

//随机产生苹果
void creat_apple();

//响应控制方向键
void respons_button();

//识别移动方向
void recognition_dir();

//游戏场景方法调用集合（主函数）
void play();

//根据移动方向旋转头像
void change_Image();

// 撞到围墙或障碍物
void opinion_coli();

//吃到食物
void opinion_eatFood();

//撞到墙或障碍物--闪烁
void collition_blink();

//吃到食物闪烁
void eat_blink();

//吃到自己
void eat_self(void);

//随机创建对象
void random_object();

//模糊背景
void blur_bag();

//进入下一页
void enter_next();

//打印游戏分值
void print_score();
//打印生命值
void print_life();

//----------------------------------------------------------Creat object
//生成障碍物地址
void creat_new_ob_position();

//创建障碍物
void creat_obje();

//游戏胜利调用
void win();

//游戏结束页--------------------------------------------------------
void game_over();
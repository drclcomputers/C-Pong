#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<windows.h>


using namespace std;

//Configuration
bool running=true;
bool playing=true;
int speed=2;
int score=0;
char arr[10000], dif1[1];
int menu_y=230;
char text1[]={"PING PONG for 1"}, text2[]="by DRCLComputers", text3[]="Select Difficulty:", text4[]="Easy", text5[]="Medium", text6[]="Hard", text7[]="Press ENTER to start or SPACE to exit.", text8[]="SCORE: ", text9[]="You didn't catch the ball. Retry by pressing UP key or SPACE to exit.";

//-----------------Variables-------------------

//Window
const int WINDOW_HEIGHT=500;
const int WINDOW_FULL_HEIGHT=580;
const int WINDOW_WITDH=500;
const char title[]="My Game";

//Player
const int PLAYER_HEIGHT=20;
const int PLAYER_WITDH=100;
int PLAYER_X=WINDOW_WITDH/2-PLAYER_WITDH/2;
int PLAYER_Y=WINDOW_HEIGHT-PLAYER_HEIGHT-10;

//Ball
const int BALL_RADIUS=20;
int BALL_X=WINDOW_WITDH/2-BALL_RADIUS/2;
int BALL_Y=WINDOW_HEIGHT/2-BALL_RADIUS/2;
int BALL_moveup_speed=rand()%4+5;
int BALL_moveright_speed=rand()%9;
bool move_up=rand()%3%2;
bool move_right=rand()%3%2;

//Game Functions Declaration
void windowinit();
void playerinit();
void playermovement();
void ballinit();
void ballmovement();



//---------------Main Function------------------
int main()
{
    windowinit();
    return 0;
}



//----------------Game Logic-----------------

//Window Drawing and Main drawing function
void windowinit(){
    //window instance creation
    initwindow(WINDOW_WITDH, WINDOW_FULL_HEIGHT, title);

    //main menu
    while(running){
        //UI Interface
        outtextxy(WINDOW_WITDH/3+10, 100, text1);
        outtextxy(WINDOW_WITDH/2, 130, text2);

        outtextxy(WINDOW_WITDH/3, 200, text3);

        sprintf(dif1, "%d", 1);
        outtextxy(WINDOW_WITDH/3+20, 220, dif1);
        outtextxy(WINDOW_WITDH/3+40, 220, text4);

        sprintf(dif1, "%d", 2);
        outtextxy(WINDOW_WITDH/3+20, 240, dif1);
        outtextxy(WINDOW_WITDH/3+40, 240, text5);

        sprintf(dif1, "%d", 3);
        outtextxy(WINDOW_WITDH/3+20, 260, dif1);
        outtextxy(WINDOW_WITDH/3+40, 260, text6);

        outtextxy(WINDOW_WITDH/5, 500, text7);

        circle(WINDOW_WITDH/3+8, menu_y-2, 4);

        //Input Detection
        if(GetAsyncKeyState(VK_RETURN))
            break;
        if(GetAsyncKeyState(VK_SPACE))
            running=false;
        if(GetAsyncKeyState(49)){
            speed=1;
            menu_y=230;
        }
        if(GetAsyncKeyState(50)){
            speed=2;
            menu_y=250;
        }
        if(GetAsyncKeyState(51)){
            speed=3;
            menu_y=270;
        }
        Sleep(200);
        cleardevice();
    }

    //game running
    while(running){
        if(playing){
            //setcolor(WHITE);
            //clearing
            cleardevice();
            //text
            outtextxy(20, WINDOW_HEIGHT+40, text8);
            sprintf(arr, "%d", score);
            outtextxy(90, WINDOW_HEIGHT+40, arr);
            //drawing functions
            ballinit();
            playerinit();
            //movement
            playermovement();
            ballmovement();
            //fps controller
            Sleep(50);
        }
        else{
            outtextxy(28, 100, text9);
            //input after losing the ball
            if(GetAsyncKeyState(VK_UP))
                playing=true;
            if(GetAsyncKeyState(VK_SPACE))
                running=false;
            Sleep(1000);
        }
    }
}


//Player Drawing
void playerinit(){
    rectangle(PLAYER_X, PLAYER_Y, PLAYER_X+PLAYER_WITDH, PLAYER_Y+PLAYER_HEIGHT);
    //setfillstyle(SOLID_FILL, 15);
    //floodfill(PLAYER_Y, PLAYER_X, 15);
}

//Ball Drawing
void ballinit(){
    circle(BALL_X, BALL_Y, BALL_RADIUS);
    //setfillstyle(SOLID_FILL, 15);
    //floodfill(BALL_Y, BALL_X, 15);
}


//Player Movement
void playermovement(){
    //if(key=='a' && PLAYER_X>11)
    if(GetAsyncKeyState(VK_LEFT) && PLAYER_X>11)
        PLAYER_X-=10*speed;
    //if(key=='d' && PLAYER_X<WINDOW_WITDH-11-PLAYER_WITDH)
    if(GetAsyncKeyState(VK_RIGHT) && PLAYER_X<WINDOW_WITDH-11-PLAYER_WITDH)
        PLAYER_X+=10*speed;
    if(GetAsyncKeyState(VK_SPACE))
        running=false;
}

//Ball Movement
void ballmovement(){
    //Actual Movement
    if(move_up)
        BALL_Y-=BALL_moveup_speed*speed;
    else
        BALL_Y+=BALL_moveup_speed*speed;

    if(move_right)
        BALL_X+=BALL_moveright_speed*speed;
    else
        BALL_X-=BALL_moveright_speed*speed;

    //Hit Info
    if(BALL_Y-BALL_RADIUS<0)
        move_up=0, BALL_moveup_speed=rand()%4+5;
    if(BALL_Y+BALL_RADIUS>=WINDOW_HEIGHT-15){
        if(BALL_X+BALL_RADIUS/2>=PLAYER_X && BALL_X+BALL_RADIUS/2<=PLAYER_X+PLAYER_WITDH){
            Beep(900, 30);
            move_up=1;
            score++;
            BALL_moveright_speed=rand()%9+1;
        }
        else{
            playing=false;
            PLAYER_X=WINDOW_WITDH/2-PLAYER_WITDH/2;
            PLAYER_Y=WINDOW_HEIGHT-PLAYER_HEIGHT-10;
            BALL_X=WINDOW_WITDH/2-BALL_RADIUS/2;
            BALL_Y=WINDOW_HEIGHT/2-BALL_RADIUS/2;
            move_up=rand()%2-1;
            move_right=rand()%2;
            score-=5;
        }
    }

    if(BALL_X-20<0)
        move_right=1;
    if(BALL_X+20>WINDOW_WITDH)
        move_right=0;
}

//END

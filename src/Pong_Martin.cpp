#include <Arduino.h>
#include "cyberpi.h"

CyberPi cyber;
uint16_t w = 0XFFFF;
int scoreA=0;
int scoreB=0;

u_int16_t playerImage[16][4]={
w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,
w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,
w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,
w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,
};
u_int16_t ballImage[4][4]={
w,w,w,w,
w,w,w,w,
w,w,w,w,
w,w,w,w,
};
Sprite player;
Sprite player2;
Sprite ball;
Sprite score1;
Sprite score2;


void setup(){
cyber.begin();
Serial.begin(115200);

player.x=0;
player.y=60;
player.height = 16;
player.width =4;
player.buffer = (u_int16_t *) playerImage;

player2.x=124;
player2.y=60;
player2.height = 16;
player2.width =4;
player2.buffer = (u_int16_t *) playerImage;

ball.x=20;
ball.y=60;
ball.xSpeed=1;
ball.ySpeed=1;
ball.height = 4;
ball.width =4;
ball.buffer = (u_int16_t *) ballImage;


}
void loop(){
    cyber.clean_lcd();
    if (cyber.get_joystick_y()<0)
    {
        player.y=player.y-2;
    }
      if (cyber.get_joystick_y()>0)
    {
        player.y=player.y+2;
    }
      if (cyber.get_button_a()>0)
    {
        player2.y-=2;
    }
      if (cyber.get_button_b()>0)
    {
        player2.y+=2;
    }
    
    ball.x+=ball.xSpeed;
    ball.y+=ball.ySpeed;
    Serial.print("Y=");
    Serial.print(ball.y);
    Serial.print("YSpeed=");
    Serial.print((ball.ySpeed));
    if (ball.y<=0||ball.y>=128){
        ball.ySpeed*=-1;
        ball.y+=ball.ySpeed*2;
    
    }
   if (ball.x+4>=128-4)
    {
        if (ball.y- 2 >=player2.y && ball.y <=player2.y+16 )
        {
            ball.xSpeed*=-1;
        }
        else
        {
            ball.x=20;
            ball.y=60;
            scoreB++;
        }
    } 
    if (ball.x-3<=0)
    {
        if (ball.y- 2 >=player.y && ball.y <=player.y+16 )
        {
            ball.xSpeed*=-1;
        }
        else
        {
            ball.x=20;
            ball.y=60;
            scoreA++;
        } 
    } 
    
cyber.set_bitmap(player.x,player.y,&player);
cyber.set_bitmap(player2.x,player2.y,&player2);
cyber.set_bitmap(ball.x,ball.y,&ball);
Sprite score1 = cyber.create_text(cyber.num_to_text(scoreA), 0xFFFF, 14);
  cyber.set_bitmap(50, 5, &score1);
  Sprite score2 = cyber.create_text(cyber.num_to_text(scoreB), 0xFFFF, 14);
  cyber.set_bitmap(70, 5, &score2);

cyber.render_lcd();
delay(2);
}
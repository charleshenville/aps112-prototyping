#include <TouchScreen.h> //touch library
#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_KBV.h> //Hardware-specific library
#include <stdio.h>
#include <stdlib.h>

LCDWIKI_KBV my_lcd(ILI9486,A3,A2,A1,A0,A4);

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

//param calibration from kbv
//res 480 x 320
#define TS_MINX 906
#define TS_MAXX 116

#define TS_MINY 92 
#define TS_MAXY 952

#define MINPRESSURE 10
#define MAXPRESSURE 1000

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define L_GRAY  0xD5D5
#define D_GRAY  0x5D5D

uint16_t color_mask[] = {0xF800,0xFFE0,0x07E0,0x07FF,0x001F,0xF81F}; //color select

#define COLORBOXSIZE my_lcd.Get_Display_Width()/6
#define PENBOXSIZE my_lcd.Get_Display_Width()/4

int points = 0;
int16_t userFlag = 0;
int16_t adminFlag = 0;
int16_t menuFlag = 1;
boolean show_flag = true;

char buffer [sizeof(int)*8+1];

void showString(uint8_t *str,int16_t x,int16_t y,uint8_t csize,uint16_t fc, uint16_t bc, boolean mode)
{
  my_lcd.Set_Text_Mode(mode);
  my_lcd.Set_Text_Size(csize);
  my_lcd.Set_Text_colour(fc);
  my_lcd.Set_Text_Back_colour(bc);
  my_lcd.Print_String(str,x,y);
}

void showMainMenu(void){
  my_lcd.Set_Draw_color(L_GRAY);
  showString("* Welcome, Please Select a Profile *",27,100,2,L_GRAY, L_GRAY,1);
  my_lcd.Fill_Round_Rectangle(50, 150, 200, 200, 5);
  showString("USER",103,168,2,BLACK, BLACK,1);
  my_lcd.Fill_Round_Rectangle(280, 150, 430, 200, 5);
  showString("ADMIN",327,168,2,BLACK, BLACK,1);
}

void showHelpMenu(void){
  showString("* Pinging a Caretaker For Help... *",27,150,2,BLACK, BLACK,1);
  delay(5000);
}

void updatePoints(void){
  my_lcd.Set_Draw_color(L_GRAY);
  my_lcd.Fill_Rectangle(158, 40, 300, 47);
  char *intStr = itoa(points,buffer,10);
  // string str = string(intStr);
  showString(intStr,158,40,1,BLACK, BLACK,1);
}

void showUserMenu(void){
  my_lcd.Set_Draw_color(BLACK);

  my_lcd.Fill_Circle(50,50,30);
  my_lcd.Fill_Circle(50,20,10);
  my_lcd.Fill_Circle(20,50,10);
  my_lcd.Fill_Circle(30,30,10);
  my_lcd.Fill_Circle(30,70,10);
  my_lcd.Fill_Circle(80,50,10);
  my_lcd.Fill_Circle(50,80,10);
  my_lcd.Fill_Circle(70,70,10);
  my_lcd.Fill_Circle(70,30,10);

  my_lcd.Fill_Circle(420,50,40);

  my_lcd.Fill_Rectangle(165, 60, 320, 67);

  my_lcd.Set_Draw_color(BLUE);

  my_lcd.Fill_Rectangle(20, 100, 460, 170);

  my_lcd.Set_Draw_color(MAGENTA);

  my_lcd.Fill_Rectangle(20, 190, 460, 260);

  my_lcd.Set_Draw_color(L_GRAY);

  my_lcd.Fill_Circle(50,50,15);

  my_lcd.Fill_Circle(420,50,38);

  my_lcd.Fill_Rectangle(166, 61, 319, 66);

  my_lcd.Fill_Rectangle(22, 102, 102, 168);
  my_lcd.Fill_Rectangle(180, 102, 300, 168);
  my_lcd.Fill_Rectangle(378, 102, 458, 168);

  my_lcd.Fill_Rectangle(22, 192, 102, 258);
  my_lcd.Fill_Rectangle(180, 192, 300, 258);
  my_lcd.Fill_Rectangle(378, 192, 458, 258);

  showString("HELP", 399, 42, 2, BLACK, BLACK, 1);

  showString("Points: 0",110,40,1,BLACK, BLACK,1);
  showString("Progress",110,60,1,BLACK, BLACK,1);
  showString("Goal",330,60,1,BLACK, BLACK,1);

  showString("Eat",45,125,2,BLACK, BLACK,1);
  showString("Bathroom",195,125,2,BLACK, BLACK,1);
  showString("Hurt",395,125,2,BLACK, BLACK,1);

  showString("Play",35,215,2,BLACK, BLACK,1);
  showString("Want",215,215,2,BLACK, BLACK,1);
  showString("Hello",390,215,2,BLACK, BLACK,1);

  showString("Hi, Phoebe!",175,280,2,BLACK, BLACK,1);
}

void showAdminMenu(){
  my_lcd.Set_Draw_color(L_GRAY);
  my_lcd.Fill_Circle(50,50,30);
  my_lcd.Fill_Circle(50,20,10);
  my_lcd.Fill_Circle(20,50,10);
  my_lcd.Fill_Circle(30,30,10);
  my_lcd.Fill_Circle(30,70,10);
  my_lcd.Fill_Circle(80,50,10);
  my_lcd.Fill_Circle(50,80,10);
  my_lcd.Fill_Circle(70,70,10);
  my_lcd.Fill_Circle(70,30,10);

  my_lcd.Set_Draw_color(BLACK);
  my_lcd.Fill_Circle(50,50,15);

}

void setup() 
{
  Serial.begin(9600);
  my_lcd.Init_LCD();
  Serial.println(my_lcd.Read_ID(), HEX);
  my_lcd.Fill_Screen(0x0);  
  my_lcd.Set_Rotation(1);
  showMainMenu();
  pinMode(13, OUTPUT);
}

void loop() 
{
comme:
  digitalWrite(13, HIGH);
  TSPoint cursor = ts.getPoint();
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  int tmp = 0;
  if (cursor.z > MINPRESSURE && cursor.z < MAXPRESSURE) 
  {
    
    //Portrait to landscape mapping
    int cursory = 320-map(cursor.x, TS_MINX, TS_MAXX, my_lcd.Get_Display_Height(), 0);
    int cursorx = map(cursor.y, TS_MINY, TS_MAXY, my_lcd.Get_Display_Width(),0);

    if(menuFlag != 0){
      //If y is in range of 2 main buttons
      if((cursory>150)&&(cursory<200)){

        //case: USER
        if((cursorx>50)&&(cursorx<200)){
          my_lcd.Fill_Screen(L_GRAY);
          showUserMenu();
          userFlag = 1;
          menuFlag = 0;
        }

        //case: ADMIN
        else if((cursorx>280)&&(cursorx<430)){
          my_lcd.Fill_Screen(0x0);
          showAdminMenu();
          adminFlag = 1;
          menuFlag = 0;
        }      
      }
    }
    

    if(userFlag != 0)// User menu case
    {
      if((cursorx>10)&&(cursorx<90)&&(cursory>10)&&(cursory<90)) // Settings Case
      {
        my_lcd.Fill_Screen(0x0);
        showMainMenu();
        userFlag = 0;
        menuFlag = 1;
      }
      else if((cursorx>390)&&(cursorx<470)&&(cursory>10)&&(cursory<90)){// Help Case
        my_lcd.Fill_Screen(L_GRAY);
        showHelpMenu();
        my_lcd.Fill_Screen(0x0);
        showMainMenu();
        userFlag = 0;
        menuFlag = 1;
      }
      //Rectangle (button) cases
      else if((cursorx>22)&&(cursorx<102)&&(cursory>102)&&(cursory<168)){
        my_lcd.Set_Draw_color(GREEN);
        my_lcd.Draw_Rectangle(22,102,102,168);
        points++;
        updatePoints();
        delay(1000);
        my_lcd.Draw_Rectangle(22,102,102,168);
      }
      else if((cursorx>180)&&(cursorx<300)&&(cursory>102)&&(cursory<168)){
        my_lcd.Set_Draw_color(GREEN);
        my_lcd.Draw_Rectangle(180,102,300,168);
        points++;
        updatePoints();
        delay(1000);
        my_lcd.Draw_Rectangle(180,102,300,168);
      }
      else if((cursorx>378)&&(cursorx<458)&&(cursory>102)&&(cursory<168)){
        my_lcd.Set_Draw_color(GREEN);
        my_lcd.Draw_Rectangle(378,102,458,168);
        points++;
        updatePoints();
        delay(1000);
        my_lcd.Draw_Rectangle(378,102,458,168);
      }
      else if((cursorx>22)&&(cursorx<102)&&(cursory>192)&&(cursory<258)){
        my_lcd.Set_Draw_color(GREEN);
        my_lcd.Draw_Rectangle(22,192,102,258);
        points++;
        updatePoints();
        delay(1000);
        my_lcd.Draw_Rectangle(22,192,102,258);
      }
      else if((cursorx>180)&&(cursorx<300)&&(cursory>192)&&(cursory<258)){
        my_lcd.Set_Draw_color(GREEN);
        my_lcd.Draw_Rectangle(180,192,300,258);
        points++;
        updatePoints();
        delay(1000);
        my_lcd.Draw_Rectangle(180,192,300,258);
      }
      else if((cursorx>378)&&(cursorx<458)&&(cursory>192)&&(cursory<258)){
        my_lcd.Set_Draw_color(GREEN);
        my_lcd.Draw_Rectangle(378,192,458,258);
        points++;
        updatePoints();
        delay(1000);
        my_lcd.Draw_Rectangle(378,192,458,258);
      }
    }
    
  }
}

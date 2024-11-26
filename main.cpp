#include <simulator_libraries\FEHLCD.h>
#include "simulator_libraries\FEHUtility.h"
#include "simulator_libraries\FEHFile.h"
#include "simulator_libraries\FEHImages.h"
#include "simulator_libraries\FEHRandom.h"
#include "simulator_libraries\FEHSD.h"
#include "simulator_libraries\LCDColors.h"
#include "String.h"
#include <cstring>
#include <windows.h>
#include <winuser.h>
#include "simulator_libraries\FEHRandom.h"

using namespace std;



#define WM_KEYDOWN 0x0100


struct pairCoords {
    float x;
    float y;
    
};

struct rectangle {
    //Top left
    struct pairCoords pairCoords1;
    //Bottom right
    struct pairCoords pairCoords2;
    
};



//Protypes
void Start_Menu();

class BackGround_DayNight {
    private:
        
    public:
        BackGround_DayNight();
        void DayNight();
        void Main_BackGround();
        int randomForDayNight;
        int torchAnimationStage;
        float startTime;
        int map;
        int zone;
        int currentBackGround[5][3];
        bool day;
        bool inCombat;
};



class sprite {
    private:
        float health;
        //Sprite position
        struct pairCoords spritePosition;
        string name;
        string spriteFile;
        //press position
        float x_direction, y_direction;

    public:
        sprite(float spriteHealth, string spriteName, string spriteFile, float x_start, float y_start);
        void drawSprites();
        int getPressPositionForMovement();
        void characterMovement(class BackGround_DayNight* backdrop, class HitBox walls[], class HitBox* player, int pressPosition);
};

//For collisions
class HitBox {
    private:
        rectangle rectangle1;
    public:
        HitBox();
        HitBox(rectangle newRectangle);
        bool colliding(HitBox OtherHitBox);
        rectangle getRectangleCoords();
        void setCoordinates(rectangle newRectangle);

};






int main() {

    //Test for position
    // BackGround_DayNight backGroundDayNight;
    // backGroundDayNight.DayNight();
    // backGroundDayNight.Main_BackGround();
    // FEHImage base1;
    // base1.Open("Sprites/Knight_Back.png");
    // base1.Draw(100, 100);

    // float xtest, ytest;
    // while (1) {
    //     while(!LCD.Touch(&xtest,&ytest)) {};
    //     while(LCD.Touch(&xtest,&ytest)) {};
    //     LCD.Write(xtest);
    //     LCD.Write(",");
    //     LCD.WriteLine(ytest);
    //     Sleep(2.0);

    // }


    // rectangle testRectangle = {{5, 10}, {7, 20}};
    // rectangle testRectangle2 = {{6,19}, {9,31}};
    // HitBox hitbox1(testRectangle);
    // LCD.WriteLine(hitbox1.colliding(testRectangle2));

    
    while (1) {
        Start_Menu();
        LCD.Clear(BLACK);
        //Creates background object
        BackGround_DayNight backGroundDayNight;
        bool inCombat = false;
        backGroundDayNight.day = false;
        backGroundDayNight.map = 0;
        backGroundDayNight.zone = 1;
        backGroundDayNight.DayNight();

        //////////////////////////////////////////////////////
        /*
        currentBackGround[0][0] = 111;
        currentBackGround[0][1] = 121;
        currentBackGround[0][2] = 111;
        */
        backGroundDayNight.currentBackGround[0][1] = 111;
        backGroundDayNight.map = 0;
        backGroundDayNight.zone = 1;
        backGroundDayNight.currentBackGround[backGroundDayNight.map][backGroundDayNight.zone] = 121;
        //////////////////////////////////////////////////////

        backGroundDayNight.Main_BackGround();
        //Creates player object
        sprite playerSprite(100, "Lord Arthur", "Sprites/Knight_front.png", 120, 120);
        playerSprite.drawSprites();
        //Creates player hitbox
        rectangle playerRectangle = {{131,135}, {138, 148}};
        HitBox playerHitBox(playerRectangle);
        //Creates Hitbox for walls for base map
        HitBox walls[7][12];
        //Creates all the rectangles for the walls

        /*
        0_121
        */
        rectangle wall1_0_121 = {{25,19}, {299, 116}};
        rectangle wall2_0_121 = {{25,19}, {279, 149}};
        rectangle wall3_0_121 = {{28,150}, {299, 224}};
        //extra
        rectangle wall4_0_121 = {{28,150}, {299, 224}};
        rectangle wall5_0_121 = {{28,150}, {299, 224}};
        rectangle wall6_0_121 = {{28,150}, {299, 224}};
        rectangle wall7_0_121 = {{28,150}, {299, 224}};
        rectangle wall8_0_121 = {{28,150}, {299, 224}};
        //new maps
        //to 0_112
        rectangle wall9_0_121 = {{298,117}, {310, 150}};
        //extra
        rectangle wall10_0_121 = {{0,0}, {1, 1}};
        rectangle wall11_0_121 = {{0,0}, {1, 1}};
        rectangle wall12_0_121 = {{0,0}, {1, 1}};
        walls[0][0].setCoordinates(wall1_0_121);
        walls[0][1].setCoordinates(wall2_0_121);
        walls[0][2].setCoordinates(wall3_0_121);
        walls[0][3].setCoordinates(wall4_0_121);
        walls[0][4].setCoordinates(wall5_0_121);
        walls[0][5].setCoordinates(wall6_0_121);
        walls[0][6].setCoordinates(wall7_0_121);
        walls[0][7].setCoordinates(wall8_0_121);
        walls[0][8].setCoordinates(wall9_0_121);
        walls[0][9].setCoordinates(wall10_0_121);
        walls[0][10].setCoordinates(wall11_0_121);
        walls[0][11].setCoordinates(wall12_0_121);

        /*
        0_112
        */
        rectangle wall1_0_112 = {{21,15}, {295, 117}};
        rectangle wall2_0_112 = {{168,116}, {295, 223}};
        rectangle wall3_0_112 = {{21,149}, {58, 224}};
        //extra
        rectangle wall4_0_112 = {{21,149}, {58, 224}};
        rectangle wall5_0_112 = {{21,149}, {58, 224}};
        rectangle wall6_0_112 = {{21,149}, {58, 224}};
        rectangle wall7_0_112 = {{21,149}, {58, 224}};
        rectangle wall8_0_112 = {{21,149}, {58, 224}};
        //new maps
        //to 0_121
        rectangle wall9_0_112 = {{11,117}, {21, 150}};
        //to 1_112
        rectangle wall10_0_112 = {{58,224}, {168, 235}};
        //extra
        rectangle wall11_0_112 = {{0,0}, {1, 1}};
        rectangle wall12_0_112 = {{0,0}, {1, 1}};
        walls[1][0].setCoordinates(wall1_0_112);
        walls[1][1].setCoordinates(wall2_0_112);
        walls[1][2].setCoordinates(wall3_0_112);
        walls[1][3].setCoordinates(wall4_0_112);
        walls[1][4].setCoordinates(wall5_0_112);
        walls[1][5].setCoordinates(wall6_0_112);
        walls[1][6].setCoordinates(wall7_0_112);
        walls[1][7].setCoordinates(wall8_0_112);
        walls[1][8].setCoordinates(wall9_0_112);
        walls[1][9].setCoordinates(wall10_0_112);
        walls[1][10].setCoordinates(wall11_0_112);
        walls[1][11].setCoordinates(wall12_0_112);

        /*
        1_211
        */
        rectangle wall1_1_211 = {{25,19}, {162, 118}};
        rectangle wall2_1_211 = {{145,19}, {298, 38}};
        rectangle wall3_1_211 = {{272,38}, {298, 69}};
        rectangle wall4_1_211 = {{23,103}, {119, 217}};
        rectangle wall5_1_211 = {{24,217}, {140, 224}};
        rectangle wall6_1_211 = {{228,137}, {261, 200}};
        //extra
        rectangle wall7_1_211 = {{24,217}, {140, 224}};
        rectangle wall8_1_211 = {{24,217}, {140, 224}};
        //new maps
        //to 2_211
        rectangle wall9_1_211 = {{141,223}, {307, 237}};
        //to 1_121
        rectangle wall10_1_211 = {{297,70}, {315, 237}};
        //extra
        rectangle wall11_1_211 = {{0,0}, {1, 1}};
        rectangle wall12_1_211 = {{0,0}, {1, 1}};
        walls[2][0].setCoordinates(wall1_1_211);
        walls[2][1].setCoordinates(wall2_1_211);
        walls[2][2].setCoordinates(wall3_1_211);
        walls[2][3].setCoordinates(wall4_1_211);
        walls[2][4].setCoordinates(wall5_1_211);
        walls[2][5].setCoordinates(wall6_1_211);
        walls[2][6].setCoordinates(wall7_1_211);
        walls[2][7].setCoordinates(wall8_1_211);
        walls[2][8].setCoordinates(wall9_1_211);
        walls[2][9].setCoordinates(wall10_1_211);
        walls[2][10].setCoordinates(wall11_1_211);
        walls[2][11].setCoordinates(wall12_1_211);

        /*
        1_121
        */
        rectangle wall1_1_121 = {{20,15}, {300, 70}};
        rectangle wall2_1_121 = {{93,69}, {150, 135}};
        rectangle wall3_1_121 = {{150,107}, {180, 135}};
        rectangle wall4_1_121 = {{150,69}, {209, 90}};
        rectangle wall5_1_121 = {{202,99}, {267, 135}};
        rectangle wall6_1_121 = {{202,77}, {298, 99}};
        rectangle wall7_1_121 = {{40,170}, {160, 223}};
        rectangle wall8_1_121 = {{269,198}, {298, 223}};
        //new maps
        //to 1_211
        rectangle wall9_1_121 = {{0,21}, {21, 223}};
        //to 2_121
        rectangle wall10_1_121 = {{0,223}, {41, 235}};
        rectangle wall11_1_121 = {{160,223}, {270, 233}};
        //to 1_112
        rectangle wall12_1_121 = {{298,98}, {319, 200}};
        walls[3][0].setCoordinates(wall1_1_121);
        walls[3][1].setCoordinates(wall2_1_121);
        walls[3][2].setCoordinates(wall3_1_121);
        walls[3][3].setCoordinates(wall4_1_121);
        walls[3][4].setCoordinates(wall5_1_121);
        walls[3][5].setCoordinates(wall6_1_121);
        walls[3][6].setCoordinates(wall7_1_121);
        walls[3][7].setCoordinates(wall8_1_121);
        walls[3][8].setCoordinates(wall9_1_121);
        walls[3][9].setCoordinates(wall10_1_121);
        walls[3][10].setCoordinates(wall11_1_121);
        walls[3][11].setCoordinates(wall12_1_121);

        /*
        1_112
        */
        rectangle wall1_1_112 = {{15,12}, {58, 99}};
        rectangle wall2_1_112 = {{19,198}, {295, 220}};
        rectangle wall3_1_112 = {{168,16}, {295, 220}};
        //extra
        rectangle wall4_1_112 = {{168,16}, {295, 220}};
        rectangle wall5_1_112 = {{168,16}, {295, 220}};
        rectangle wall6_1_112 = {{168,16}, {295, 220}};
        rectangle wall7_1_112 = {{168,16}, {295, 220}};
        rectangle wall8_1_112 = {{168,16}, {295, 220}};
        //new maps
        //to 1_121
        rectangle wall9_1_112 = {{13,100}, {21, 198}};
        //to 0_112
        rectangle wall10_1_112 = {{58,7}, {168, 15}};
        //extra
        rectangle wall11_1_112 = {{0,0}, {1, 1}};
        rectangle wall12_1_112 = {{0,0}, {1, 1}};
        walls[4][0].setCoordinates(wall1_1_112);
        walls[4][1].setCoordinates(wall2_1_112);
        walls[4][2].setCoordinates(wall3_1_112);
        walls[4][3].setCoordinates(wall4_1_112);
        walls[4][4].setCoordinates(wall5_1_112);
        walls[4][5].setCoordinates(wall6_1_112);
        walls[4][6].setCoordinates(wall7_1_112);
        walls[4][7].setCoordinates(wall8_1_112);
        walls[4][8].setCoordinates(wall9_1_112);
        walls[4][9].setCoordinates(wall10_1_112);
        walls[4][10].setCoordinates(wall11_1_112);
        walls[4][11].setCoordinates(wall12_1_112);

        /*
        2_211
        */
        rectangle wall1_2_211 = {{24,16}, {75, 121}};
        rectangle wall2_2_211 = {{24,16}, {141, 45}};
        rectangle wall3_2_211 = {{134,144}, {298, 219}};
        rectangle wall4_2_211 = {{186,122}, {298, 219}};
        rectangle wall5_2_211 = {{294,26}, {299, 90}};
        rectangle wall6_2_211 = {{17,121}, {25, 219}};
        rectangle wall7_2_211 = {{25,219}, {134, 223}};
        //extra
        rectangle wall8_2_211 = {{25,219}, {134, 223}};
        //new maps
        //to 1_211
        rectangle wall9_2_211 = {{140,9}, {298, 15}};
        //to 2_121
        rectangle wall10_2_211 = {{298,15}, {306, 25}};
        //to 2_121
        rectangle wall11_2_211 = {{299,89}, {308, 124}};
        //extra
        rectangle wall12_2_211 = {{0,0}, {1, 1}};
        walls[5][0].setCoordinates(wall1_2_211);
        walls[5][1].setCoordinates(wall2_2_211);
        walls[5][2].setCoordinates(wall3_2_211);
        walls[5][3].setCoordinates(wall4_2_211);
        walls[5][4].setCoordinates(wall5_2_211);
        walls[5][5].setCoordinates(wall6_2_211);
        walls[5][6].setCoordinates(wall7_2_211);
        walls[5][7].setCoordinates(wall8_2_211);
        walls[5][8].setCoordinates(wall9_2_211);
        walls[5][9].setCoordinates(wall10_2_211);
        walls[5][10].setCoordinates(wall11_2_211);
        walls[5][11].setCoordinates(wall12_2_211);

        /*
        2_121
        */
        rectangle wall1_2_121 = {{21,25}, {158, 89}};
        rectangle wall2_2_121 = {{41,16}, {158, 89}};
        rectangle wall3_2_121 = {{21,123}, {295, 219}};
        rectangle wall4_2_121 = {{269,15}, {295, 219}};
        //extra
        rectangle wall5_2_121 = {{269,15}, {295, 219}};
        rectangle wall6_2_121 = {{269,15}, {295, 219}};
        rectangle wall7_2_121 = {{269,15}, {295, 219}};
        rectangle wall8_2_121 = {{269,15}, {295, 219}};
        //new maps
        //to 2_211
        rectangle wall9_2_121 = {{13,16}, {21, 24}};
        //to 1_121
        rectangle wall10_2_121 = {{20,8}, {41, 16}};
        //to 2_211
        rectangle wall11_2_121 = {{12,90}, {21, 122}};
        //to 1_121
        rectangle wall12_2_121 = {{159,5}, {269, 15}};
        walls[6][0].setCoordinates(wall1_2_121);
        walls[6][1].setCoordinates(wall2_2_121);
        walls[6][2].setCoordinates(wall3_2_121);
        walls[6][3].setCoordinates(wall4_2_121);
        walls[6][4].setCoordinates(wall5_2_121);
        walls[6][5].setCoordinates(wall6_2_121);
        walls[6][6].setCoordinates(wall7_2_121);
        walls[6][7].setCoordinates(wall8_2_121);
        walls[6][8].setCoordinates(wall9_2_121);
        walls[6][9].setCoordinates(wall10_2_121);
        walls[6][10].setCoordinates(wall11_2_121);
        walls[6][11].setCoordinates(wall12_2_121);
        
        //Continuous cycle, update multiple times per second
        while (1) {
            
            int pressPosition = playerSprite.getPressPositionForMovement();
            //class BackGround_DayNight* backdrop, class HitBox* walls[12], class HitBox* player
            playerSprite.characterMovement(&backGroundDayNight, walls[3], &playerHitBox, pressPosition);
            
            //LCD.Update();
            Sleep(31);
            
        }


        // float xtest, ytest;
        // while (1) {
        //     while(!LCD.Touch(&xtest,&ytest)) {};
        //     while(LCD.Touch(&xtest,&ytest)) {};
        //     LCD.Write(xtest);
        //     LCD.Write(",");
        //     LCD.WriteLine(ytest);
        //     Sleep(2.0);

        // }


    }
    return 0;
}


//Start menu
void Start_Menu() {
    char menu_labels[4][20] = {"START", "HELP", "CREDITS", "STATISTICS"};
    FEHIcon::Icon menu[4];
    while (1) {
        //Clear Back Ground of Display
        LCD.SetBackgroundColor(BLACK);
        LCD.Clear(BLACK);
        //Creates menu for game
        FEHIcon::DrawIconArray(menu, 2, 2, 10, 10, 5, 5, menu_labels, GOLD, GREEN);
        LCD.Update();


        float x_position, y_position;
        //Checks for touch
        while(!LCD.Touch(&x_position,&y_position)) {};
        while(LCD.Touch(&x_position,&y_position)) {};
 
        if ((5 <= x_position) && (x_position < 160) && (10 <= y_position) && (y_position < 120)) {
            //Start
            break;
        } else if ((160 <= x_position) && (x_position <= 315) && (10 <= y_position) && (y_position <= 120)) {
            //Help
            LCD.Clear(BLACK);
            LCD.WriteLine("Tap the top/right/left/bottom of the screen to move in that direction");
            LCD.WriteLine("Talk to NPC's and progress through the story");
            LCD.WriteLine("Fight monsters and obtain points");
            LCD.Update();
            while(!LCD.Touch(&x_position,&y_position)) {};
            while(LCD.Touch(&x_position,&y_position)) {};
        } else if ((5 <= x_position) && (x_position < 160) && (120 <= y_position) && (y_position < 230)) {
            //Credits
            LCD.Clear(BLACK);
            LCD.WriteLine("Coded by Jason Yang and Andy Zhang");
            LCD.WriteLine("Inspired by pokemon");
            LCD.Update();
            while(!LCD.Touch(&x_position,&y_position)) {};
            while(LCD.Touch(&x_position,&y_position)) {};
        } else if ((160 <= x_position) && (x_position <= 315) && (120 <= y_position) && (y_position <= 230)) {
            //Statistics
            LCD.Clear(BLACK);
            LCD.WriteLine("TOTAL Points: 0");
            LCD.Update();
            while(!LCD.Touch(&x_position,&y_position)) {};
            while(LCD.Touch(&x_position,&y_position)) {};
        }
    }
}

///////////////////////////////////////////////////
//Width of Screen for background
//LCD.DrawLine(20, 15, 300, 225);
///////////////////////////////////////////////////


BackGround_DayNight::BackGround_DayNight() {
    randomForDayNight = Random.RandInt() + 1;
    startTime = TimeNow();
    torchAnimationStage = 0;
    //Base map
    currentBackGround[0][0] = 111;
    currentBackGround[0][1] = 121;
    currentBackGround[0][2] = 111;
    //General map 1
    currentBackGround[1][0] = 1;
    currentBackGround[1][1] = 1;
    currentBackGround[1][2] = 1;
    //General map 2
    currentBackGround[2][0] = 1;
    currentBackGround[2][1] = 1;
    currentBackGround[2][2] = 1;
    //Boss map
    currentBackGround[3][0] = 1;
    currentBackGround[3][1] = 1;
    currentBackGround[3][2] = 1;
    //Combat maps
    //map = 4 here
    //zone 1 is map 1, zone 2 is map 2 vice versa
    currentBackGround[4][0] = 1;
    currentBackGround[4][1] = 1;
    currentBackGround[4][2] = 1;

    map = 0;
    zone = 1;
    inCombat = false;
}

//Define functions for backgrounds
void BackGround_DayNight::Main_BackGround() {
    LCD.Clear(BLACK);
    if (!inCombat) {
        if (map == 0) {
            if (day) {
                if (currentBackGround[map][zone] == 211) {
                    string mapIdentifierString = "Images/base_" + to_string(zone) + "_211.png";
                    const char* mapIdentifier = mapIdentifierString.c_str();
                        
                    FEHImage base1;
                    base1.Open(mapIdentifier);
                    base1.Draw(20, 15);
                }

                if (currentBackGround[map][zone] == 121) {
                    string mapIdentifierString = "Images/base_" + to_string(zone) + "_121.png";
                    const char* mapIdentifier = mapIdentifierString.c_str();
                        
                    FEHImage base1;
                    base1.Open(mapIdentifier);
                    base1.Draw(20, 15);
                }

                if (currentBackGround[map][zone] == 112) {
                    string mapIdentifierString = "Images/base_" + to_string(zone) + "_112.png";
                    const char* mapIdentifier = mapIdentifierString.c_str();
                        
                    FEHImage base1;
                    base1.Open(mapIdentifier);
                    base1.Draw(20, 15);
                }
            } else {
                if (torchAnimationStage == 0) {
                    if (currentBackGround[map][zone] == 211) {
                        string mapIdentifierString = "Images/torch_" + to_string(zone) + "_211(0).png";
                        const char* mapIdentifier = mapIdentifierString.c_str();
                            
                        FEHImage base1;
                        base1.Open(mapIdentifier);
                        base1.Draw(20, 15);
                    }

                    if (currentBackGround[map][zone] == 121) {
                        string mapIdentifierString = "Images/torch_" + to_string(zone) + "_121(0).png";
                        const char* mapIdentifier = mapIdentifierString.c_str();
                            
                        FEHImage base1;
                        base1.Open(mapIdentifier);
                        base1.Draw(20, 15);
                    }

                    if (currentBackGround[map][zone] == 112) {
                        string mapIdentifierString = "Images/torch_" + to_string(zone) + "_112(0).png";
                        const char* mapIdentifier = mapIdentifierString.c_str();
                            
                        FEHImage base1;
                        base1.Open(mapIdentifier);
                        base1.Draw(20, 15);
                    }
                    torchAnimationStage = 1;
                } else if (torchAnimationStage == 1) {
                    if (currentBackGround[map][zone] == 211) {
                        string mapIdentifierString = "Images/torch_" + to_string(zone) + "_211(1).png";
                        const char* mapIdentifier = mapIdentifierString.c_str();
                            
                        FEHImage base1;
                        base1.Open(mapIdentifier);
                        base1.Draw(20, 15);
                    }

                    if (currentBackGround[map][zone] == 121) {
                        string mapIdentifierString = "Images/torch_" + to_string(zone) + "_121(1).png";
                        const char* mapIdentifier = mapIdentifierString.c_str();
                            
                        FEHImage base1;
                        base1.Open(mapIdentifier);
                        base1.Draw(20, 15);
                    }

                    if (currentBackGround[map][zone] == 112) {
                        string mapIdentifierString = "Images/torch_" + to_string(zone) + "_112(1).png";
                        const char* mapIdentifier = mapIdentifierString.c_str();
                            
                        FEHImage base1;
                        base1.Open(mapIdentifier);
                        base1.Draw(20, 15);
                    }
                    torchAnimationStage = 2;
                } else if (torchAnimationStage == 2) {
                    if (currentBackGround[map][zone] == 211) {
                        string mapIdentifierString = "Images/torch_" + to_string(zone) + "_211(2).png";
                        const char* mapIdentifier = mapIdentifierString.c_str();
                            
                        FEHImage base1;
                        base1.Open(mapIdentifier);
                        base1.Draw(20, 15);
                    }

                    if (currentBackGround[map][zone] == 121) {
                        string mapIdentifierString = "Images/torch_" + to_string(zone) + "_121(2).png";
                        const char* mapIdentifier = mapIdentifierString.c_str();
                            
                        FEHImage base1;
                        base1.Open(mapIdentifier);
                        base1.Draw(20, 15);
                    }

                    if (currentBackGround[map][zone] == 112) {
                        string mapIdentifierString = "Images/torch_" + to_string(zone) + "_112(2).png";
                        const char* mapIdentifier = mapIdentifierString.c_str();
                            
                        FEHImage base1;
                        base1.Open(mapIdentifier);
                        base1.Draw(20, 15);
                    }
                    torchAnimationStage = 0;
                }
            }


        } else {


            if (currentBackGround[map][zone] == 2) {
                string mapIdentifierString = "Images/" + to_string(map) + "_" + to_string(zone) + ".png";
                const char* mapIdentifier = mapIdentifierString.c_str();
                    
                FEHImage base1;
                base1.Open(mapIdentifier);
                base1.Draw(20, 15);
            }
        }
    } else {
        map = 4;
        if (currentBackGround[map][zone] == 2) {
            string mapIdentifierString = "Images/Combat_" + to_string(map) + "_" + to_string(zone) + ".png";
            const char* mapIdentifier = mapIdentifierString.c_str();
                
            FEHImage base1;
            base1.Open(mapIdentifier);
            base1.Draw(20, 15);
        }
    }
}


sprite::sprite(float spriteHealth, string spriteName, string givenSpriteFile, float x_start, float y_start) {
    health = spriteHealth;
    spritePosition.x = x_start;
    spritePosition.y = y_start;
    name = spriteName;
    spriteFile = givenSpriteFile;
}

void sprite::drawSprites() {
    
    const char* mapIdentifier = spriteFile.c_str();
    
    FEHImage sprite;
    sprite.Open(mapIdentifier);
    sprite.Draw(spritePosition.x, spritePosition.y);
}

int sprite::getPressPositionForMovement() {
    
    if (GetAsyncKeyState(VK_UP) & 0x8000) {
        return 1;
    } else if (GetAsyncKeyState(VK_RIGHT) & 0x8000){
        return 2;
    } else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        return 3;
    } else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        return 4;
    } else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
        Start_Menu();
    }
    return 0;

}

//Movement
//Only run method when user touch display to move
//Updates arrayCharacterPosition
void sprite::characterMovement(class BackGround_DayNight* backdrop, class HitBox walls[12], class HitBox* player, int pressPosition) {
    /*
    Checks the current Map and section of each map creating regions arrayCharacterPosition
    can't be located in

    Also checks which button pressPosition activate and move character appropriately
    */   
    LCD.Clear(BLACK);
    rectangle playerTempHitBox = player->getRectangleCoords();
    switch (pressPosition) {
        case 1:
            //up
            spriteFile = "Sprites/Knight_back.png";
            spritePosition.y -= 3;
            playerTempHitBox.pairCoords1.y -= 3;
            playerTempHitBox.pairCoords2.y -= 3;
            for (int i = 0; i < 12; i++) {
                if (walls[i].colliding(*player)) {
                    spritePosition.y += 7;
                    playerTempHitBox.pairCoords1.y += 7;
                    playerTempHitBox.pairCoords2.y += 7;
                    i = 24;
                }
            }
            break;
        case 2:
            //right
            spriteFile = "Sprites/Knight_right.png";
            spritePosition.x += 3;
            playerTempHitBox.pairCoords1.x += 3;
            playerTempHitBox.pairCoords2.x += 3;
            for (int i = 0; i < 12; i++) {
                if (walls[i].colliding(*player)) {
                    spritePosition.x -= 7;
                    playerTempHitBox.pairCoords1.x -= 7;
                    playerTempHitBox.pairCoords2.x -= 7;
                    i = 24;
                }
            }
            break;
        case 3:
            //down
            spriteFile = "Sprites/Knight_front.png";
            spritePosition.y += 3;
            playerTempHitBox.pairCoords1.y += 3;
            playerTempHitBox.pairCoords2.y += 3;
            for (int i = 0; i < 12; i++) {
                if (walls[i].colliding(*player)) {
                    spritePosition.y -= 7;
                    playerTempHitBox.pairCoords1.y -= 7;
                    playerTempHitBox.pairCoords2.y -= 7;
                    i = 24;
                }
            }
            break;
        case 4:
            //left
            spriteFile = "Sprites/Knight_left.png";
            spritePosition.x -= 3;
            playerTempHitBox.pairCoords1.x -= 3;
            playerTempHitBox.pairCoords2.x -= 3;
            for (int i = 0; i < 12; i++) {
                if (walls[i].colliding(*player)) {
                    spritePosition.x += 7;
                    playerTempHitBox.pairCoords1.x += 7;
                    playerTempHitBox.pairCoords2.x += 7;
                    i = 24;
                }
            }
            break;
    }
    player->setCoordinates(playerTempHitBox);
    backdrop->Main_BackGround();
    drawSprites();

}

//DayNight System
void BackGround_DayNight::DayNight() {
    int timeMarker = TimeNow();
    
    
    if ((BackGround_DayNight::randomForDayNight % 2) != 1) {
        if ((timeMarker % 2) != 1) {
            day = true;
            BackGround_DayNight::Main_BackGround();
        } else {
            day = false;
            BackGround_DayNight::Main_BackGround();
        }
    } else {
        if ((timeMarker % 2) == 1) {
            day = true;
            BackGround_DayNight::Main_BackGround();
        } else {
            day = false;
            BackGround_DayNight::Main_BackGround();
        }
    }
}



HitBox::HitBox(rectangle newRectangle) {
    rectangle1 = newRectangle;
}

HitBox::HitBox() {
    
}

void HitBox::setCoordinates(rectangle newRectangle) {
    rectangle1 = newRectangle;
}

rectangle HitBox::getRectangleCoords() {
    return rectangle1;
}

bool HitBox::colliding(HitBox OtherHitBox) {
    if ((rectangle1.pairCoords1.x > OtherHitBox.rectangle1.pairCoords1.x) && (OtherHitBox.rectangle1.pairCoords2.x > rectangle1.pairCoords1.x)) {
        if ((rectangle1.pairCoords1.y > OtherHitBox.rectangle1.pairCoords1.y) && (OtherHitBox.rectangle1.pairCoords2.y > rectangle1.pairCoords1.y)) {
            return true;
        } else if ((rectangle1.pairCoords2.y > OtherHitBox.rectangle1.pairCoords1.y) && (OtherHitBox.rectangle1.pairCoords1.y > rectangle1.pairCoords1.y)) {
            return true;
        } else {
            return false;
        }
    } else if ((rectangle1.pairCoords2.x > OtherHitBox.rectangle1.pairCoords1.x) && (OtherHitBox.rectangle1.pairCoords1.x > rectangle1.pairCoords1.x)) {
        if ((rectangle1.pairCoords1.y > OtherHitBox.rectangle1.pairCoords1.y) && (OtherHitBox.rectangle1.pairCoords2.y > rectangle1.pairCoords1.y)) {
            return true;
        } else if ((rectangle1.pairCoords2.y > OtherHitBox.rectangle1.pairCoords1.y) && (OtherHitBox.rectangle1.pairCoords1.y > rectangle1.pairCoords1.y)) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

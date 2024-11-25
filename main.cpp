#include <simulator_libraries\FEHLCD.h>
#include "simulator_libraries\FEHUtility.h"
#include "simulator_libraries\FEHFile.h"
#include "simulator_libraries\FEHImages.h"
#include "simulator_libraries\FEHRandom.h"
#include "simulator_libraries\FEHSD.h"
#include "simulator_libraries\LCDColors.h"
#include "String.h"
#include <cstring>
#include <Windows.h>
#include "simulator_libraries\FEHRandom.h"

using namespace std;






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
        backGroundDayNight.Main_BackGround();
        //Creates player object
        sprite playerSprite(100, "Lord Arthur", "Sprites/Knight_front.png", 120, 120);
        playerSprite.drawSprites();
        //Creates player hitbox
        rectangle playerRectangle = {{120,120}, {130, 130}};
        HitBox playerHitBox(playerRectangle);
        //Creates Hitbox for walls
        HitBox walls[4][12];
        //Creates all the rectangles for the walls
        //rectangle wall1 = {{120,120}, {130, 130}}; e.g.
        rectangle wall1 = {{12,12}, {13, 13}};
        rectangle wall2 = {{12,12}, {13, 13}};
        rectangle wall3 = {{12,12}, {13, 13}};
        rectangle wall4 = {{12,12}, {13, 13}};
        rectangle wall5 = {{12,12}, {13, 13}};
        rectangle wall6 = {{12,12}, {13, 13}};
        rectangle wall7 = {{12,12}, {13, 13}};
        rectangle wall8 = {{12,12}, {13, 13}};
        rectangle wall9 = {{12,12}, {13, 13}};
        rectangle wall10 = {{12,12}, {13, 13}};
        rectangle wall11 = {{12,12}, {13, 13}};
        rectangle wall12 = {{12,12}, {13, 13}};
        walls[0][0].setCoordinates(wall1);
        walls[0][1].setCoordinates(wall2);
        walls[0][2].setCoordinates(wall3);
        walls[0][3].setCoordinates(wall4);
        walls[0][4].setCoordinates(wall5);
        walls[0][5].setCoordinates(wall6);
        walls[0][6].setCoordinates(wall7);
        walls[0][7].setCoordinates(wall8);
        walls[0][8].setCoordinates(wall9);
        walls[0][9].setCoordinates(wall10);
        walls[0][10].setCoordinates(wall11);
        walls[0][11].setCoordinates(wall12);
        
        //Continuous cycle, update multiple times per second
        while (1) {
            
            int pressPosition = playerSprite.getPressPositionForMovement();
            //class BackGround_DayNight* backdrop, class HitBox* walls[12], class HitBox* player
            playerSprite.characterMovement(&backGroundDayNight, walls[0], &playerHitBox, pressPosition);
            LCD.Update();
            Sleep(62);

            
            
            
        }


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
    LCD.Update();
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


    
    // // float x_direction, y_direction;
    // // int pressPosition;
    
    // while (!LCD.Touch(&x_direction, &y_direction)) {};
    // while (LCD.Touch(&x_direction, &y_direction)) {};
    // //LCD.DrawLine(20, 15, 300, 225);
    // //below y 15 is menu button
    // if ((((0.75 * (x_direction - 20.0)) + 15.0) < y_direction) && (((-0.75 * (x_direction - 300.0)) + 15.0) < y_direction) && (y_direction > 15)) {
    //     //down
    //     pressPosition = 3;
    // } else if ((((0.75 * (x_direction - 20.0)) + 15.0) > y_direction) && (((-0.75 * (x_direction - 300.0)) + 15.0) > y_direction) && (y_direction > 15)) {
    //     //up
    //     pressPosition = 1;
    // } else if ((((0.75 * (x_direction - 20.0)) + 15.0) < y_direction) && (((-0.75 * (x_direction - 300.0)) + 15.0) > y_direction) && (y_direction > 15)) {
    //     //left
    //     pressPosition = 4;
    // } else if ((((0.75 * (x_direction - 20.0)) + 15.0) > y_direction) && (((-0.75 * (x_direction - 300.0)) + 15.0) < y_direction) && (y_direction > 15)) {
    //     //right
    //     pressPosition = 2;
    // } else if (y_direction < 15) {
    //     Start_Menu();
    // }


    if (GetKeyState('w') & 0x8000) {
        LCD.WriteLine("w");
        return 1;
    } else if (GetKeyState('d') & 0x8000){
        LCD.WriteLine("d");
        return 2;
    } else if (GetKeyState('s') & 0x8000) {
        LCD.WriteLine("s");
        return 3;
    } else if (GetKeyState('a') & 0x8000) {
        LCD.WriteLine("a");
        return 4;
    } else if (GetKeyState('m') & 0x8000) {
        Start_Menu();
    }
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
            spritePosition.y -= 5;
            playerTempHitBox.pairCoords1.y -= 5;
            playerTempHitBox.pairCoords2.y -= 5;
            for (int i = 0; i < 12; i++) {
                if (walls[i].colliding(*player)) {
                    spritePosition.y += 5;
                    playerTempHitBox.pairCoords1.y += 5;
                    playerTempHitBox.pairCoords2.y += 5;
                }
            }
            break;
        case 2:
            //right
            spriteFile = "Sprites/Knight_right.png";
            spritePosition.x += 5;
            playerTempHitBox.pairCoords1.x += 5;
            playerTempHitBox.pairCoords2.x += 5;
            for (int i = 0; i < 12; i++) {
                if (walls[i].colliding(*player)) {
                    spritePosition.x -= 5;
                    playerTempHitBox.pairCoords1.x -= 5;
                    playerTempHitBox.pairCoords2.x -= 5;
                }
            }
            break;
        case 3:
            //down
            spriteFile = "Sprites/Knight_front.png";
            spritePosition.y += 5;
            playerTempHitBox.pairCoords1.y += 5;
            playerTempHitBox.pairCoords2.y += 5;
            for (int i = 0; i < 12; i++) {
                if (walls[i].colliding(*player)) {
                    spritePosition.y -= 5;
                    playerTempHitBox.pairCoords1.y -= 5;
                    playerTempHitBox.pairCoords2.y -= 5;
                }
            }
            break;
        case 4:
            //left
            spriteFile = "Sprites/Knight_left.png";
            spritePosition.x -= 5;
            playerTempHitBox.pairCoords1.x -= 5;
            playerTempHitBox.pairCoords2.x -= 5;
            for (int i = 0; i < 12; i++) {
                if (walls[i].colliding(*player)) {
                    spritePosition.x += 5;
                    playerTempHitBox.pairCoords1.x += 5;
                    playerTempHitBox.pairCoords2.x += 5;
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
}

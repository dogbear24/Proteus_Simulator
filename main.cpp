#include <simulator_libraries\FEHLCD.h>
#include "simulator_libraries\FEHUtility.h"
#include "simulator_libraries\FEHFile.h"
#include "simulator_libraries\FEHImages.h"
#include "simulator_libraries\FEHRandom.h"
#include "simulator_libraries\FEHSD.h"
#include "simulator_libraries\LCDColors.h"
#include "String.h"
#include <cstring>
#include <string>
#include <windows.h>
#include <winuser.h>
#include "simulator_libraries\FEHRandom.h"

using namespace std;

//Creates struct to model coordinate pairs
//Andy
struct pairCoords {
    float x;
    float y;
    
};

//Creates struct to model rectangle
//Andy
struct rectangle {
    //Top left
    struct pairCoords pairCoords1;
    //Bottom right
    struct pairCoords pairCoords2;
    
};

//Prototypes for functions
//Andy
void Start_Menu(int points);

//Creates class for backgrounds
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


//Creates class for sprites
class sprite {
    private:
        float health;
        //Sprite position
        struct pairCoords spritePosition;
        string name;
        string spriteFile;
        //press position
        float x_direction, y_direction;
        int oldPressPosition;
        int oldPress;
        bool canMoveUp;
        bool canMoveRight;
        bool canMoveDown;
        bool canMoveLeft;
    public:
        sprite(float spriteHealth, string spriteName, string spriteFile, float x_start, float y_start);
        void drawSprites();
        int getPressPositionForMovement(int points);
        void characterMovement(class BackGround_DayNight* backdrop, class HitBox walls[], class HitBox* player, int pressPosition);
        void changeBackGround(class BackGround_DayNight* backdrop, class HitBox*& walls, class HitBox* player, class sprite* playerSprite, HitBox baseWalls[7][12]);
        void changeCoordinates(float newXCoord, float newYCoord);
        void changeSpriteFile(string newFile);
};

//Creates class for collisions
//Andy
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

    //Creates variables to record points
    int points = 0;
 
    while (1) {

        //Creates the start menu
        Start_Menu(points);

        //Creates background object and randomizes day or night
        LCD.Clear(BLACK);
        BackGround_DayNight backGroundDayNight;
        backGroundDayNight.DayNight();

        //Draws the background
        backGroundDayNight.Main_BackGround();

        //Creates player object and draws the player
        sprite playerSprite(100, "Knight", "Sprites/Knight_front.png", 120, 128);
        playerSprite.drawSprites();

        //Creates player hitbox
        rectangle playerRectangle = {{131,143}, {138, 156}};
        HitBox playerHitBox(playerRectangle);


        //Andy
        //Creates Hitbox for walls for base map
        HitBox walls[7][12];

        //Creates all the rectangles for the walls of base map, extra array entries are kept so length is always constant
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


        HitBox winterWalls[4];
        //Creates Hitbox for walls for winter map
        //Creates rectangles for all the walls of the winter map

        rectangle winterWall_top = {{20,15}, {300, 70}};
        rectangle winterWall_right = {{300,70}, {330, 165}};
        rectangle winterWall_left = {{2,70}, {20, 165}};
        rectangle winterWall_bottom = {{20,165}, {300, 225}};
        winterWalls[0].setCoordinates(winterWall_top);
        winterWalls[1].setCoordinates(winterWall_right);
        winterWalls[2].setCoordinates(winterWall_bottom);
        winterWalls[3].setCoordinates(winterWall_left);


        HitBox desertWalls[4];
        //Creates Hitbox for walls for desert map
        //Creates rectangles for all the walls of the desert map

        rectangle desertWall_top = {{140,0}, {219, 15}};
        rectangle desertWall_right = {{219,15}, {300, 224}};
        rectangle desertWall_bottom = {{140,224}, {219, 238}};
        rectangle desertWall_left = {{20,15}, {140, 224}};
        desertWalls[0].setCoordinates(desertWall_top);
        desertWalls[1].setCoordinates(desertWall_right);
        desertWalls[2].setCoordinates(desertWall_bottom);
        desertWalls[3].setCoordinates(desertWall_left);


        HitBox finalBossRoom[4];
        //Creates HittBox for walls of final map
        //Creates rectangles for all the walls of the final map

        rectangle finalBossWal_top = {{20, 5}, {300, 15}};
        rectangle finalBossWal_right = {{300, 15}, {330, 225}};
        rectangle finalBossWal_bottom = {{20, 225}, {300, 235}};
        rectangle finalBossWal_left = {{5, 15}, {20, 225}};
        finalBossRoom[0].setCoordinates(finalBossWal_top);
        finalBossRoom[1].setCoordinates(finalBossWal_right);
        finalBossRoom[2].setCoordinates(finalBossWal_bottom);
        finalBossRoom[3].setCoordinates(finalBossWal_left);


        //Creates pointer to the set of current walls needed
        HitBox* wallptr;
        wallptr = walls[3];


        //not all entries of arrays may be used
        //tracks progress of the entire game
        int gameProgress[] = {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        //track progress for forest goblin combat
        int forestMonosterCombatProgress[] = {2, 1, 1, 1, 1,1, 1, 1, 1,1, 1};
        //track progress for forest boss combat
        int forestBossCombatProgress[] = {2, 1, 1, 1, 1,1, 1, 1, 1,1, 1};
        //track progress for winter snowman combat
        int winterMonsterCombatProgress[] = {2, 1, 1, 1, 1,1, 1, 1, 1,1, 1};
        //track progress for winter boss combat
        int winterBossCombatProgress[] = {2, 1, 1, 1, 1,1, 1, 1, 1,1, 1};
        //track progress for desert skeleton combat
        int desertSkeletonCombatProgress[] = {2, 1, 1, 1, 1,1, 1, 1, 1,1, 1};
        //track progress for desert boss combat
        int desertBossCombatProgress[] = {2, 1, 1, 1, 1,1, 1, 1, 1,1, 1};
        //track progress for final boss combat
        int finalBossCombatProgress[] = {2, 1, 1, 1, 1,1, 1, 1, 1,1, 1};


        //Create loop counters for speech bubbles and combat animation
        int startTexts = 0;
        int forestNarrator = 0;
        int winterNarrator = 0;
        int desertNarrator = 0;
        int evilWizardSpeech = 0;
        int startCombat = 0;

        bool passed = false;
        float xClick, yClick;


        //tracks if the player lost
        bool stillAlive = true;


        //Continuous cycle, one cycle is a frame
        while (1) {
            if (backGroundDayNight.map == 0) {
                //runs while your on the base map

                //tracks game progress
                if (gameProgress[0] == 2) {
                    //resets points in case your replaying the game
                    points = 0;

                    //shows texts and images based on the number of loops that occured
                    if (startTexts < 200) {
                        FEHImage happyKingdom0;
                        happyKingdom0.Open("more_images/kingdom_background_transformed.png");
                        happyKingdom0.Draw(20, 15);


                        FEHImage startNarratorText;
                        startNarratorText.Open("Texts/Narrator_Text_1.png");
                        startNarratorText.Draw(20, 15);

                        passed = true;
                    }

                    if (205 <= startTexts && startTexts < 410) {
                        FEHImage notHappyKingdom0;
                        notHappyKingdom0.Open("more_images/dark_arts_transformed.png");
                        notHappyKingdom0.Draw(20, 15);


                        FEHImage startNarratorText2;
                        startNarratorText2.Open("Texts/Narrator_text_2.png");
                        startNarratorText2.Draw(20, 15);

                        passed = true;
                    }

                    if (410 <= startTexts && startTexts < 620) {
                        FEHImage ripKingdom0;
                        ripKingdom0.Open("more_images/burning_kingdom_transformed.png");
                        ripKingdom0.Draw(20, 15);


                        FEHImage startNarratorText3;
                        startNarratorText3.Open("Texts/Narrator_3.png");
                        startNarratorText3.Draw(20, 15);
                        
                        passed = true;
                    }

                    if (610 <= startTexts && startTexts < 820) {
                        FEHImage paimon1;
                        paimon1.Open("Sprites/Nice_wizard.png");
                        paimon1.Draw(120, 105);

                        FEHImage startPaimonText;
                        startPaimonText.Open("Texts/Paimon_text.png");
                        startPaimonText.Draw(20, 15);
                        
                        passed = true;
                    }

                    if (820 <= startTexts && startTexts < 1000) {
                        FEHImage paimon2;
                        paimon2.Open("Sprites/Nice_wizard.png");
                        paimon2.Draw(120, 105);

                        FEHImage startPaimonText1;
                        startPaimonText1.Open("Texts/Paimon_2.png");
                        startPaimonText1.Draw(20, 15);

                        passed = true;
                    }

                    if (1005 <= startTexts && startTexts < 1200) {
                        FEHImage paimon3;
                        paimon3.Open("Sprites/Nice_wizard.png");
                        paimon3.Draw(120, 105);

                        FEHImage startPaimonText2;
                        startPaimonText2.Open("Texts/Paimon_3.png");
                        startPaimonText2.Draw(20, 15);

                        passed = true;
                    }

                    if (startTexts > 1195) {
                        gameProgress[0] = 1;
                        gameProgress[1] = 2;
                    }

                } else if (gameProgress[1] == 2) {
                    //before defeating forest monster

                    //movements
                    int pressPosition = playerSprite.getPressPositionForMovement(points);
                    playerSprite.characterMovement(&backGroundDayNight, wallptr, &playerHitBox, pressPosition);
                    playerSprite.changeBackGround(&backGroundDayNight, wallptr, &playerHitBox, &playerSprite, walls);
                    backGroundDayNight.Main_BackGround();
                    playerSprite.drawSprites();

                    //checks if your in the right location
                    if (backGroundDayNight.zone == 1 && backGroundDayNight.currentBackGround[backGroundDayNight.map][backGroundDayNight.zone] == 211) {
                        //draws monster
                        sprite forestMonster(100, "Forest Monster", "Sprites/Goblin.png", 138, 96);
                        forestMonster.drawSprites();
                        //create monster hitbox
                        rectangle forestMonsterRectangle = {{88, 46}, {188, 146}};
                        HitBox forestMonsterHitBox(forestMonsterRectangle);
                        if (forestMonsterHitBox.colliding(playerHitBox) && pressPosition == 5) {
                            //Start combat animation
                            if (startCombat >= 66) {
                                startCombat = 0;
                                //reset progress
                                gameProgress[1] = 1;
                                //update progress
                                gameProgress[2] = 2;
                                //update other stats
                                backGroundDayNight.currentBackGround[0][0] = 111;
                                backGroundDayNight.currentBackGround[0][1] = 111;
                                backGroundDayNight.currentBackGround[0][2] = 111;
                                backGroundDayNight.map = 4;
                                backGroundDayNight.zone = 0;
                                backGroundDayNight.currentBackGround[4][0] = 2;
                                backGroundDayNight.inCombat = true;
                            }

                            if (startCombat < 16) {
                                playerSprite.changeSpriteFile("Sprites/Right_knight_swing.png");
                                startCombat++;
                            }

                            if (14 < startCombat && startCombat < 17) {
                                startCombat++;
                            }

                            if (15 <= startCombat && startCombat < 33) {
                                playerSprite.changeSpriteFile("Sprites/Knight_right_swing_2.png");
                                startCombat++;
                            }

                            if (30 <= startCombat && startCombat < 66) {
                                FEHImage combat;
                                combat.Open("Combat_Background/BattleStart.png");
                                combat.Draw(20, 15);
                                startCombat++;
                            }                            
                        }
                    }
                    /*
                    Redirects program to combat
                    */
                } else if (gameProgress[3] == 2) {
                    //before defeating forest boss

                    //movements
                    int pressPosition = playerSprite.getPressPositionForMovement(points);
                    playerSprite.characterMovement(&backGroundDayNight, wallptr, &playerHitBox, pressPosition);
                    playerSprite.changeBackGround(&backGroundDayNight, wallptr, &playerHitBox, &playerSprite, walls);
                    backGroundDayNight.Main_BackGround();
                    playerSprite.drawSprites();
                    
                    //Checks if your in the right location
                    if (backGroundDayNight.zone == 2 && backGroundDayNight.currentBackGround[backGroundDayNight.map][backGroundDayNight.zone] == 211) {
                        //draws boss
                        sprite forestBoss(100, "Forest Boss", "Sprites/Forest_Boss.png", 40, 190);
                        forestBoss.drawSprites();
                        //create boss hitbox
                        rectangle forestBossRectangle = {{0, 140}, {90, 240}};
                        HitBox forestMonsterHitBox(forestBossRectangle);
                        if (forestMonsterHitBox.colliding(playerHitBox) && pressPosition == 5) {

                            //Plays the start combat animation
                            if (startCombat >= 66) {
                                startCombat = 0;

                                //reset progress
                                gameProgress[3] = 1;
                                //update progress
                                gameProgress[4] = 2;
                                //update other stats
                                backGroundDayNight.currentBackGround[0][0] = 111;
                                backGroundDayNight.currentBackGround[0][1] = 111;
                                backGroundDayNight.currentBackGround[0][2] = 111;
                                backGroundDayNight.map = 4;
                                backGroundDayNight.zone = 0;
                                backGroundDayNight.currentBackGround[4][0] = 2;
                                backGroundDayNight.inCombat = true;
                            }

                            if (startCombat < 16) {
                                playerSprite.changeSpriteFile("Sprites/Right_knight_swing.png");
                                startCombat++;
                            }

                            if (14 < startCombat && startCombat < 17) {
                                startCombat++;
                            }

                            if (15 <= startCombat && startCombat < 33) {
                                playerSprite.changeSpriteFile("Sprites/Knight_right_swing_2.png");
                                startCombat++;
                            }

                            if (30 <= startCombat && startCombat < 66) {
                                FEHImage combat;
                                combat.Open("Combat_Background/BattleStart.png");
                                combat.Draw(20, 15);
                                startCombat++;
                            }
                        }
                    }
                    /*
                    Redirects program to combat
                    */
                } else if (gameProgress[13] == 2) {
                    //Narator texts

                    if (desertNarrator < 193) {
                        FEHImage desertNarratorText;
                        desertNarratorText.Open("Texts/Narrator_6.png");
                        desertNarratorText.Draw(20, 15);

                        desertNarrator++;
                    }

                    //Moves the story to the next part
                    gameProgress[13] = 1;
                    gameProgress[14] = 2;

                } else if (gameProgress[15] == 2) {
                    //Open Gate scene

                    string gateIdentifierString = "Gates/Open_gate.png";
                    const char* gateIdentifier = gateIdentifierString.c_str();
                                
                    FEHImage gate4;
                    gate4.Open(gateIdentifier);
                    gate4.Draw(20, 15);

                    gameProgress[15] = 1;
                    gameProgress[16] = 2;

                } else if (gameProgress[17] == 2) {
                    //before final boss fight

                    //Prevents you from moving while the text is on the screen
                    int pressPosition = playerSprite.getPressPositionForMovement(points);
                    if (evilWizardSpeech == 0) {
                        playerSprite.characterMovement(&backGroundDayNight, wallptr, &playerHitBox, pressPosition);
                        playerSprite.changeBackGround(&backGroundDayNight, wallptr, &playerHitBox, &playerSprite, walls);
                    }
                    backGroundDayNight.Main_BackGround();
                    playerSprite.drawSprites();

                    //Checks if you're in the correct section
                    if (backGroundDayNight.zone == 0 && backGroundDayNight.currentBackGround[backGroundDayNight.map][backGroundDayNight.zone] == 121) {
                        
                        //draws monster
                        sprite finalBoss(100, "Evil Wizard", "Sprites/Evil_wizard.png", 130, 90);
                        finalBoss.drawSprites();

                        //create monster hitbox
                        rectangle finalBossRectangle = {{0, 0}, {300, 225}};
                        HitBox finalBossHitBox(finalBossRectangle);
                        if (finalBossHitBox.colliding(playerHitBox)) {

                            //Evil wizard speech
                            if (evilWizardSpeech < 193) {
                                FEHImage evilWizardSpeechText;
                                evilWizardSpeechText.Open("Texts/Impano_text.png");
                                evilWizardSpeechText.Draw(20, 15);

                                evilWizardSpeech++;
                            }

                            if (190 <= evilWizardSpeech && evilWizardSpeech < 400) {
                                FEHImage evilWizardSpeechText2;
                                evilWizardSpeechText2.Open("Texts/Impano_2.png");
                                evilWizardSpeechText2.Draw(20, 15);

                                evilWizardSpeech++;
                            }

                            if (evilWizardSpeech > 380) {
                                //reset progress
                                gameProgress[17] = 1;
                                //update progress
                                gameProgress[18] = 2;
                                //update other stats
                                backGroundDayNight.currentBackGround[0][0] = 111;
                                backGroundDayNight.currentBackGround[0][1] = 111;
                                backGroundDayNight.currentBackGround[0][2] = 111;
                                backGroundDayNight.currentBackGround[3][0] = 2;
                                backGroundDayNight.map = 3;
                                backGroundDayNight.zone = 0;
                                wallptr = finalBossRoom;

                                //Adjusts player position
                                rectangle playerTempHitBox1 = playerHitBox.getRectangleCoords();
                                playerTempHitBox1.pairCoords1.x = 151;
                                playerTempHitBox1.pairCoords1.y = 205;
                                playerTempHitBox1.pairCoords2.x = 158;
                                playerTempHitBox1.pairCoords2.y = 218;
                                playerHitBox.setCoordinates(playerTempHitBox1);

                                playerSprite.changeCoordinates(120, 190);
                            }
                        }
                    }
                }
            } else if (backGroundDayNight.map == 1) {
                //winter map

                if (gameProgress[5] == 2) {
                    //before defeating winter monster

                    //movements
                    int pressPosition = playerSprite.getPressPositionForMovement(points);
                    if (forestNarrator >= 180) {
                        playerSprite.characterMovement(&backGroundDayNight, wallptr, &playerHitBox, pressPosition);
                        playerSprite.changeBackGround(&backGroundDayNight, wallptr, &playerHitBox, &playerSprite, walls);
                    }
                    backGroundDayNight.Main_BackGround();
                    playerSprite.drawSprites();


                    if (forestNarrator < 193) {
                        FEHImage forestNarratorText;
                        forestNarratorText.Open("Texts/Narrator_4.png");
                        forestNarratorText.Draw(20, 15);

                        forestNarrator++;
                    }
                    

                    if (backGroundDayNight.zone == 0 && backGroundDayNight.map == 1) {
                        //draws monster
                        sprite winterMonster(100, "Snowman", "Sprites/Snowman.png", 140, 100);
                        winterMonster.drawSprites();
                        //create boss hitbox
                        rectangle winterMonsterRectangle = {{90, 50}, {190, 150}};
                        HitBox winterMonsterHitBox(winterMonsterRectangle);
                        if (winterMonsterHitBox.colliding(playerHitBox) && pressPosition == 5) {

                            //Start Combat animation
                            if (startCombat >= 66) {
                                startCombat = 0;

                                //reset progress
                                gameProgress[5] = 1;
                                //update progress
                                gameProgress[6] = 2;
                                //update other stats
                                backGroundDayNight.currentBackGround[1][0] = 1;
                                backGroundDayNight.map = 4;
                                backGroundDayNight.zone = 0;
                                backGroundDayNight.currentBackGround[4][0] = 2;
                                backGroundDayNight.inCombat = true;
                            }

                            if (startCombat < 16) {
                                playerSprite.changeSpriteFile("Sprites/Right_knight_swing.png");
                                startCombat++;
                            }

                            if (14 < startCombat && startCombat < 17) {
                                startCombat++;
                            }

                            if (15 <= startCombat && startCombat < 33) {
                                playerSprite.changeSpriteFile("Sprites/Knight_right_swing_2.png");
                                startCombat++;
                            }

                            if (30 <= startCombat && startCombat < 66) {
                                FEHImage combat;
                                combat.Open("Combat_Background/BattleStart.png");
                                combat.Draw(20, 15);
                                startCombat++;
                            }
                        }
                    }
                    /*
                    Redirects to combat
                    */
                } else if (gameProgress[7] == 2) {
                    //before defeating winter boss

                    //movements
                    int pressPosition = playerSprite.getPressPositionForMovement(points);
                    playerSprite.characterMovement(&backGroundDayNight, wallptr, &playerHitBox, pressPosition);
                    playerSprite.changeBackGround(&backGroundDayNight, wallptr, &playerHitBox, &playerSprite, walls);
                    backGroundDayNight.Main_BackGround();
                    playerSprite.drawSprites();

                    if (backGroundDayNight.zone == 0 && backGroundDayNight.map == 1) {
                        //draws monster
                        sprite winterBoss(100, "Snow Boss", "Sprites/Snow_boss.png", 220, 100);
                        winterBoss.drawSprites();
                        //create boss hitbox
                        rectangle winterBossRectangle = {{170, 50}, {270, 150}};
                        HitBox winterBossHitBox(winterBossRectangle);
                        if (winterBossHitBox.colliding(playerHitBox) && pressPosition == 5) {

                            //Start combat animation
                            if (startCombat >= 66) {
                                startCombat = 0;

                                //reset progress
                                gameProgress[7] = 1;
                                //update progress
                                gameProgress[8] = 2;
                                //update other stats
                                backGroundDayNight.currentBackGround[1][0] = 1;
                                backGroundDayNight.map = 4;
                                backGroundDayNight.zone = 0;
                                backGroundDayNight.currentBackGround[4][0] = 2;
                                backGroundDayNight.inCombat = true;
                            }

                            if (startCombat < 16) {
                                playerSprite.changeSpriteFile("Sprites/Right_knight_swing.png");
                                startCombat++;
                            }

                            if (14 < startCombat && startCombat < 17) {
                                startCombat++;
                            }

                            if (15 <= startCombat && startCombat < 33) {
                                playerSprite.changeSpriteFile("Sprites/Knight_right_swing_2.png");
                                startCombat++;
                            }

                            if (30 <= startCombat && startCombat < 66) {
                                FEHImage combat;
                                combat.Open("Combat_Background/BattleStart.png");
                                combat.Draw(20, 15);
                                startCombat++;
                            } 
                        }
                    }
                }
                /*
                Redirects to combat
                */
            } else if (backGroundDayNight.map == 2) {
                //desert map

                if (gameProgress[9] == 2) {
                    //before defeating desert monster
                    wallptr = desertWalls;

                    //Allows combat after text is finished
                    int pressPosition = playerSprite.getPressPositionForMovement(points);
                    if (winterNarrator >= 380) {
                        playerSprite.characterMovement(&backGroundDayNight, wallptr, &playerHitBox, pressPosition);
                    }
                    backGroundDayNight.Main_BackGround();
                    playerSprite.drawSprites();

                    //Checks if location is correct
                    if (backGroundDayNight.zone == 0 && backGroundDayNight.map == 2) {
                        //draws monster
                        sprite desertMonster(100, "Skeleton", "Sprites/Skeleton.png", 160, 140);
                        desertMonster.drawSprites();
                        //create boss hitbox
                        rectangle desertMonsterRectangle = {{110, 90}, {210, 170}};
                        HitBox desertMonsterHitBox(desertMonsterRectangle);
                        if (desertMonsterHitBox.colliding(playerHitBox) && pressPosition == 5) {

                            //Start combat animation
                            if (startCombat >= 66) {
                                startCombat = 0;

                                //reset progress
                                gameProgress[9] = 1;
                                //update progress
                                gameProgress[10] = 2;
                                //update other stats
                                backGroundDayNight.currentBackGround[2][0] = 1;
                                backGroundDayNight.map = 4;
                                backGroundDayNight.zone = 0;
                                backGroundDayNight.currentBackGround[4][0] = 2;
                                backGroundDayNight.inCombat = true;
                            }

                            if (startCombat < 16) {
                                playerSprite.changeSpriteFile("Sprites/Right_knight_swing.png");
                                startCombat++;
                            }

                            if (14 < startCombat && startCombat < 17) {
                                startCombat++;
                            }

                            if (15 <= startCombat && startCombat < 33) {
                                playerSprite.changeSpriteFile("Sprites/Knight_right_swing_2.png");
                                startCombat++;
                            }

                            if (30 <= startCombat && startCombat < 66) {
                                FEHImage combat;
                                combat.Open("Combat_Background/BattleStart.png");
                                combat.Draw(20, 15);
                                startCombat++;
                            } 
                        }
                    }

                    if (winterNarrator < 193) {
                        FEHImage winterNarratorText;
                        winterNarratorText.Open("Texts/Narrator_5.png");
                        winterNarratorText.Draw(20, 15);

                        winterNarrator++;
                    }

                    if (190 <= winterNarrator && winterNarrator < 400) {
                        FEHImage winterNarratorText;
                        winterNarratorText.Open("Texts/Paimon_4.png");
                        winterNarratorText.Draw(20, 15);

                        winterNarrator++;
                    }
                    /*
                    Redirects to combat
                    */
                } else if (gameProgress[11] == 2) {
                    //before defeating desert boss

                    //Change walls to desert walls
                    wallptr = desertWalls;

                    //Movement
                    int pressPosition = playerSprite.getPressPositionForMovement(points);
                    playerSprite.characterMovement(&backGroundDayNight, wallptr, &playerHitBox, pressPosition);
                    backGroundDayNight.Main_BackGround();
                    playerSprite.drawSprites();

                    if (backGroundDayNight.zone == 0 && backGroundDayNight.map == 2) {
                        //draws monster
                        sprite desertBoss(100, "Desert Boss", "Sprites/Desert_Boss.png", 165, 40);
                        desertBoss.drawSprites();
                        //create boss hitbox
                        rectangle desertBossRectangle = {{115, 0}, {215, 90}};
                        HitBox desertBossHitBox(desertBossRectangle);
                        if (desertBossHitBox.colliding(playerHitBox) && pressPosition == 5) {

                            
                            if (startCombat >= 66) {
                                startCombat = 0;

                                //reset progress
                                gameProgress[11] = 1;
                                //update progress
                                gameProgress[12] = 2;
                                //update other stats
                                backGroundDayNight.currentBackGround[2][0] = 1;
                                backGroundDayNight.map = 4;
                                backGroundDayNight.zone = 0;
                                backGroundDayNight.currentBackGround[4][0] = 2;
                                backGroundDayNight.inCombat = true;
                            }

                            if (startCombat < 16) {
                                playerSprite.changeSpriteFile("Sprites/Right_knight_swing.png");
                                startCombat++;
                            }

                            if (14 < startCombat && startCombat < 17) {
                                startCombat++;
                            }

                            if (15 <= startCombat && startCombat < 33) {
                                playerSprite.changeSpriteFile("Sprites/Knight_right_swing_2.png");
                                startCombat++;
                            }

                            if (30 <= startCombat && startCombat < 66) {
                                FEHImage combat;
                                combat.Open("Combat_Background/BattleStart.png");
                                combat.Draw(20, 15);
                                startCombat++;
                            }                            
                        }
                    }
                }
                /*
                Redirects to combat
                */                
            } else if (backGroundDayNight.map == 3) {
                //final boss map

                if (gameProgress[19] == 2) {
                    //movements
                    int pressPosition = playerSprite.getPressPositionForMovement(points);
                    playerSprite.characterMovement(&backGroundDayNight, wallptr, &playerHitBox, pressPosition);
                    playerSprite.changeBackGround(&backGroundDayNight, wallptr, &playerHitBox, &playerSprite, walls);
                    backGroundDayNight.Main_BackGround();
                    playerSprite.drawSprites();


                    //Checks if player is in the right location
                    if (backGroundDayNight.zone == 1 && backGroundDayNight.currentBackGround[backGroundDayNight.map][backGroundDayNight.zone] == 2) {
                        //draws monster
                        sprite finalBoss(100, "Evil Wizard", "Sprites/Evil_wizard.png", 130, 90);
                        finalBoss.drawSprites();
                        //create monster hitbox
                        rectangle finalBossRectangle = {{120, 80}, {180, 140}};
                        HitBox finalBossHitBox(finalBossRectangle);
                        if (finalBossHitBox.colliding(playerHitBox) && pressPosition == 5) {

                            //Start combat animation
                            if (startCombat >= 66) {
                                startCombat = 0;

                                //reset progress
                                gameProgress[19] = 1;
                                //update progress
                                gameProgress[20] = 2;
                                //update other stats
                                backGroundDayNight.currentBackGround[3][1] = 1;
                                backGroundDayNight.map = 4;
                                backGroundDayNight.zone = 1;
                                backGroundDayNight.currentBackGround[4][1] = 2;
                                backGroundDayNight.inCombat = true;
                            }

                            if (startCombat < 16) {
                                playerSprite.changeSpriteFile("Sprites/Right_knight_swing.png");
                                startCombat++;
                            }

                            if (14 < startCombat && startCombat < 17) {
                                startCombat++;
                            }

                            if (15 <= startCombat && startCombat < 33) {
                                playerSprite.changeSpriteFile("Sprites/Knight_right_swing_2.png");
                                startCombat++;
                            }

                            if (30 <= startCombat && startCombat < 66) {
                                FEHImage combat;
                                combat.Open("Combat_Background/BattleStart.png");
                                combat.Draw(20, 15);
                                startCombat++;
                            }
                        }
                    }
                }
            } else if (backGroundDayNight.map == 4) {
                //combat

                if (backGroundDayNight.zone == 0) {
                    //Normal combat

                    if (gameProgress[2] == 2) {
                        //Forest Monster Combat

                        //Draws monster
                        sprite forestMonster(100, "Forest Monster", "Sprites/Goblin.png", 246, 41);

                        //checks which answer the player chooses
                        int pressPosition = playerSprite.getPressPositionForMovement(points);

                        //moves sprites to right location on combat screen
                        playerSprite.characterMovement(&backGroundDayNight, wallptr, &playerHitBox, pressPosition);

                        backGroundDayNight.Main_BackGround();
                        playerSprite.drawSprites();
                        forestMonster.drawSprites();

                        //Progress through combat
                        if (forestMonosterCombatProgress[0] == 2) {
                            LCD.WriteLine("What is 417 + 194?");
                            LCD.WriteLine("Choices: 511 and 611");
                            Sleep(100);

                            //Receive player input
                            int pressPosition = playerSprite.getPressPositionForMovement(points);

                            //Checks if answer is right
                            if (pressPosition == 2) {
                                //Next stage
                                forestMonosterCombatProgress[0] = 1;
                                forestMonosterCombatProgress[1] = 2;
                            } else if (pressPosition == 4) {
                                stillAlive = false;
                            }
                        } else if (forestMonosterCombatProgress[1] == 2) {
                            LCD.WriteLine("What is 4147 + 924?");
                            LCD.WriteLine("Choices: 5071 and 5171");
                            Sleep(100);

                            //Receive input
                            int pressPosition = playerSprite.getPressPositionForMovement(points);

                            //Checks if answer is right
                            if (pressPosition == 4) {
                                //Next stage
                                forestMonosterCombatProgress[1] = 1;
                                forestMonosterCombatProgress[2] = 2;
                            } else if (pressPosition == 2) {
                                //back a stage
                                forestMonosterCombatProgress[1] = 1;
                                forestMonosterCombatProgress[0] = 2;
                            }
                        } else if (forestMonosterCombatProgress[2] == 2) {
                            LCD.Clear();
                            //Show goblin text
                            FEHImage goblinText;
                            goblinText.Open("Texts/Goblin_text.png");
                            goblinText.Draw(20, 15);
                            
                            //Increase points
                            points++;

                            //Progress to next stage
                            forestMonosterCombatProgress[2] = 1;
                            forestMonosterCombatProgress[3] = 2;

                            //Exits combat
                            //reset progress
                            gameProgress[2] = 1;
                            //update progress
                            gameProgress[3] = 2;
                            //update other stats
                            backGroundDayNight.currentBackGround[0][0] = 111;
                            backGroundDayNight.currentBackGround[0][1] = 121;
                            backGroundDayNight.currentBackGround[0][2] = 111;
                            backGroundDayNight.map = 0;
                            backGroundDayNight.zone = 1;
                            backGroundDayNight.currentBackGround[4][0] = 1;
                            backGroundDayNight.inCombat = false;
                            wallptr = walls[3];

                            backGroundDayNight.DayNight();
                            
                            rectangle playerTempHitBox1 = playerHitBox.getRectangleCoords();
                            playerTempHitBox1.pairCoords1.x = 131;
                            playerTempHitBox1.pairCoords1.y = 143;
                            playerTempHitBox1.pairCoords2.x = 138;
                            playerTempHitBox1.pairCoords2.y = 156;
                            playerHitBox.setCoordinates(playerTempHitBox1);

                            playerSprite.changeCoordinates(120, 128);
                        } 
                    }
                    if (gameProgress[4] == 2) {
                        //Forest Boss Combat

                        //Draws boss
                        sprite forestBoss(100, "Forest Boss", "Sprites/Forest_Boss.png", 236, 21);

                        //checks which answer the player chooses
                        int pressPosition = playerSprite.getPressPositionForMovement(points);

                        //moves sprites to right location on combat screen
                        playerSprite.characterMovement(&backGroundDayNight, wallptr, &playerHitBox, pressPosition);

                        backGroundDayNight.Main_BackGround();
                        playerSprite.drawSprites();
                        forestBoss.drawSprites();

                        if (forestBossCombatProgress[0] == 2) {
                            //Boss beginning text
                            
                            FEHImage forestGuardText;
                            forestGuardText.Open("Texts/Forest_guard_text.png");
                            forestGuardText.Draw(20, 15);

                            forestBossCombatProgress[0] = 1;
                            forestBossCombatProgress[1] = 2;


                        } else if (forestBossCombatProgress[2] == 2) {
                            LCD.WriteLine("What is 5710947 + 12470?");
                            LCD.WriteLine("Choices: 1351378 and 5723417");
                            Sleep(100);
                            
                            //Checks input
                            int pressPosition = playerSprite.getPressPositionForMovement(points);

                            //Checks answer
                            if (pressPosition == 2) {
                                //Next stage
                                forestBossCombatProgress[2] = 1;
                                forestBossCombatProgress[3] = 2;
                            } else if (pressPosition == 4) {
                                stillAlive = false;
                            }
                        } else if (forestBossCombatProgress[3] == 2) {
                            LCD.WriteLine("What is 1415 + 1489?");
                            LCD.WriteLine("Choices: 2904 and 2104");
                            Sleep(100);

                            //Checks input
                            int pressPosition = playerSprite.getPressPositionForMovement(points);

                            //Checks answer
                            if (pressPosition == 4) {
                                //Next stage
                                forestBossCombatProgress[3] = 1;
                                forestBossCombatProgress[4] = 2;
                            } else if (pressPosition == 2) {
                                //back a stage
                                forestBossCombatProgress[3] = 1;
                                forestBossCombatProgress[2] = 2;
                            }
                        } else if (forestBossCombatProgress[4] == 2) {
                            LCD.Clear();
                            //Show end boss text and narrator stuff consider adding more to the bossCombatProgress array
                            FEHImage forestGuardText2;
                            forestGuardText2.Open("Texts/Forest_guard_2.png");
                            forestGuardText2.Draw(20, 15);

                            //Increments points
                            points++;
                            points++;
                            points++;

                            //Move to next section
                            forestBossCombatProgress[4] = 1;
                            forestBossCombatProgress[5] = 2;

                        } else if (forestBossCombatProgress[6] == 2) {
                            LCD.Clear();

                            //Show gate screen
                            string gateIdentifierString = "Gates/Gate_with_forest_orb.png";
                            const char* gateIdentifier = gateIdentifierString.c_str();
                                
                            FEHImage gate1;
                            gate1.Open(gateIdentifier);
                            gate1.Draw(20, 15);

                            //Progress to next stage
                            forestBossCombatProgress[6] = 1;
                            forestBossCombatProgress[7] = 2;


                            //Exits combat
                            //reset progress
                            gameProgress[4] = 1;
                            //update progress
                            gameProgress[5] = 2;
                            //update other stats
                            backGroundDayNight.currentBackGround[0][0] = 111;
                            backGroundDayNight.currentBackGround[0][1] = 111;
                            backGroundDayNight.currentBackGround[0][2] = 111;
                            backGroundDayNight.currentBackGround[1][0] = 2;
                            backGroundDayNight.map = 1;
                            backGroundDayNight.zone = 0;
                            //Pulls out of combat
                            backGroundDayNight.currentBackGround[4][0] = 1;
                            backGroundDayNight.inCombat = false;
                            wallptr = winterWalls;

                            //Adjusts player position
                            rectangle playerTempHitBox1 = playerHitBox.getRectangleCoords();
                            playerTempHitBox1.pairCoords1.x = 51;
                            playerTempHitBox1.pairCoords1.y = 115;
                            playerTempHitBox1.pairCoords2.x = 58;
                            playerTempHitBox1.pairCoords2.y = 128;
                            playerHitBox.setCoordinates(playerTempHitBox1);

                            playerSprite.changeCoordinates(40, 100);
                        }
                    }

                    if (gameProgress[6] == 2) {
                        //Snowman Combat

                        //Draws monster
                        sprite winterMonster(100, "Snowman", "Sprites/Snowman.png", 236, 21);

                        //checks which answer the player chooses
                        int pressPosition = playerSprite.getPressPositionForMovement(points);

                        //moves sprites to right location on combat screen
                        playerSprite.characterMovement(&backGroundDayNight, wallptr, &playerHitBox, pressPosition);

                        backGroundDayNight.Main_BackGround();
                        playerSprite.drawSprites();
                        winterMonster.drawSprites();


                        if (winterMonsterCombatProgress[0] == 2) {
                            LCD.WriteLine("What is the root of 9?");
                            LCD.WriteLine("Choices: 1 and 3");
                            Sleep(100);

                            //Receive input
                            int pressPosition = playerSprite.getPressPositionForMovement(points);

                            //Checks answer
                            if (pressPosition == 2) {
                                //Next stage
                                winterMonsterCombatProgress[0] = 1;
                                winterMonsterCombatProgress[1] = 2;
                            } else if (pressPosition == 4) {
                                stillAlive = false;
                            }
                        } else if (winterMonsterCombatProgress[1] == 2) {
                            LCD.WriteLine("What is the root of 256?");
                            LCD.WriteLine("Choices: 16 and 18");
                            Sleep(100);

                            //Receives input
                            int pressPosition = playerSprite.getPressPositionForMovement(points);

                            //Checks answer
                            if (pressPosition == 4) {
                                //Next stage
                                winterMonsterCombatProgress[1] = 1;
                                winterMonsterCombatProgress[2] = 2;
                            } else if (pressPosition == 2) {
                                //back a stage
                                winterMonsterCombatProgress[1] = 1;
                                winterMonsterCombatProgress[0] = 2;
                            }
                        } else if (winterMonsterCombatProgress[2] == 2) {
                            LCD.Clear();
                            //show end snowman text
                            FEHImage snowmanText;
                            snowmanText.Open("Texts/Snowman_text.png");
                            snowmanText.Draw(20, 15);

                            //Increments points
                            points++;

                            winterMonsterCombatProgress[2] = 1;
                            winterMonsterCombatProgress[3] = 2;


                            //Exits combat
                            //reset progress
                            gameProgress[6] = 1;
                            //update progress
                            gameProgress[7] = 2;
                            //update other stats
                            backGroundDayNight.currentBackGround[0][0] = 111;
                            backGroundDayNight.currentBackGround[0][1] = 111;
                            backGroundDayNight.currentBackGround[0][2] = 111;
                            backGroundDayNight.currentBackGround[1][0] = 2;
                            backGroundDayNight.map = 1;
                            backGroundDayNight.zone = 0;
                            //Pulls out of combat
                            backGroundDayNight.currentBackGround[4][0] = 1;
                            backGroundDayNight.inCombat = false;
                            wallptr = winterWalls;

                            //Adjusts player position
                            rectangle playerTempHitBox1 = playerHitBox.getRectangleCoords();
                            playerTempHitBox1.pairCoords1.x = 51;
                            playerTempHitBox1.pairCoords1.y = 115;
                            playerTempHitBox1.pairCoords2.x = 58;
                            playerTempHitBox1.pairCoords2.y = 128;
                            playerHitBox.setCoordinates(playerTempHitBox1);

                            playerSprite.changeCoordinates(40, 100);
                        }

                    }

                    if (gameProgress[8] == 2) {
                        //Snow Boss Combat

                        //Draws boss
                        sprite winterBoss(100, "Snow Boss", "Sprites/Snow_boss.png", 236, 21);

                        //checks which answer the player chooses
                        int pressPosition = playerSprite.getPressPositionForMovement(points);

                        //moves sprites to right location on combat screen
                        playerSprite.characterMovement(&backGroundDayNight, wallptr, &playerHitBox, pressPosition);

                        backGroundDayNight.Main_BackGround();
                        playerSprite.drawSprites();
                        winterBoss.drawSprites();

                        if (winterBossCombatProgress[0] == 2) {
                            //Boss beginning text

                            FEHImage snowGuardText;
                            snowGuardText.Open("Texts/Snow_guard_text.png");
                            snowGuardText.Draw(20, 15);
                            
                            winterBossCombatProgress[0] = 1;
                            winterBossCombatProgress[1] = 2;

                        } else if (winterBossCombatProgress[2] == 2) {
                            LCD.WriteLine("What is the root of 361?");
                            LCD.WriteLine("Choices: 19 and 20");
                            Sleep(100);

                            //Receives input
                            int pressPosition = playerSprite.getPressPositionForMovement(points);

                            //Checks answer
                            if (pressPosition == 4) {
                                //Next stage
                                winterBossCombatProgress[2] = 1;
                                winterBossCombatProgress[3] = 2;
                            } else if (pressPosition == 2) {
                                stillAlive = false;
                            }
                        } else if (winterBossCombatProgress[3] == 2) {
                            LCD.WriteLine("What is the root of 8281?");
                            LCD.WriteLine("Choices: 91 and 93");
                            Sleep(100);

                            //Receives input
                            int pressPosition = playerSprite.getPressPositionForMovement(points);

                            //Checks answer
                            if (pressPosition == 4) {
                                //Next stage
                                winterBossCombatProgress[3] = 1;
                                winterBossCombatProgress[4] = 2;
                            } else if (pressPosition == 2) {
                                //back a stage
                                winterBossCombatProgress[3] = 1;
                                winterBossCombatProgress[2] = 2;
                            }
                        } else if (winterBossCombatProgress[4] == 2) {
                            LCD.Clear();
                            //Show end boss text and narrator stuff consider adding more to the bossCombatProgress array

                            FEHImage snowmanText2;
                            snowmanText2.Open("Texts/Snow_guard_2.png");
                            snowmanText2.Draw(20, 15);

                            //Increment points
                            points++;
                            points++;
                            points++;

                            winterBossCombatProgress[4] = 1;
                            winterBossCombatProgress[5] = 2;

                        } else if (winterBossCombatProgress[6] == 2) {
                            LCD.Clear();

                            string gateIdentifierString = "Gates/Gate_with_snow_orb.png";
                            const char* gateIdentifier = gateIdentifierString.c_str();
                                
                            FEHImage gate2;
                            gate2.Open(gateIdentifier);
                            gate2.Draw(20, 15);

                            winterBossCombatProgress[6] = 1;
                            winterBossCombatProgress[7] = 2;

                            //Exits combat
                            //reset progress
                            gameProgress[8] = 1;
                            //update progress
                            gameProgress[9] = 2;
                            //update other stats
                            backGroundDayNight.currentBackGround[0][0] = 111;
                            backGroundDayNight.currentBackGround[0][1] = 111;
                            backGroundDayNight.currentBackGround[0][2] = 111;
                            backGroundDayNight.currentBackGround[2][0] = 2;
                            backGroundDayNight.map = 2;
                            backGroundDayNight.zone = 0;
                            //Pulls out of combat
                            backGroundDayNight.currentBackGround[4][0] = 1;
                            backGroundDayNight.inCombat = false;
                            wallptr = desertWalls;

                            //Adjusts player position
                            rectangle playerTempHitBox1 = playerHitBox.getRectangleCoords();
                            playerTempHitBox1.pairCoords1.x = 151;
                            playerTempHitBox1.pairCoords1.y = 205;
                            playerTempHitBox1.pairCoords2.x = 158;
                            playerTempHitBox1.pairCoords2.y = 218;
                            playerHitBox.setCoordinates(playerTempHitBox1);

                            playerSprite.changeCoordinates(140, 190);
                        }
                    }

                    if (gameProgress[10] == 2) {
                        //desert Monster Combat

                        //Draws monster
                        sprite desertMonster(100, "Desert Monster", "Sprites/Skeleton.png", 246, 41);

                        //checks which answer the player chooses
                        int pressPosition = playerSprite.getPressPositionForMovement(points);

                        //moves sprites to right location on combat screen
                        playerSprite.characterMovement(&backGroundDayNight, wallptr, &playerHitBox, pressPosition);

                        backGroundDayNight.Main_BackGround();
                        playerSprite.drawSprites();
                        desertMonster.drawSprites();

                        
                        if (desertSkeletonCombatProgress[0] == 2) {
                            LCD.WriteLine("What is 3!?");
                            LCD.WriteLine("Choices: 6 and 5");
                            Sleep(100);

                            //Receives input
                            int pressPosition = playerSprite.getPressPositionForMovement(points);

                            //Checks answer
                            if (pressPosition == 4) {
                                //Next stage
                                desertSkeletonCombatProgress[0] = 1;
                                desertSkeletonCombatProgress[1] = 2;
                            } else if (pressPosition == 2) {
                                stillAlive = false;
                            }
                        } else if (desertSkeletonCombatProgress[1] == 2) {
                            LCD.WriteLine("What is 6!?");
                            LCD.WriteLine("Choices: 560 and 720");
                            Sleep(100);

                            //Receives input
                            int pressPosition = playerSprite.getPressPositionForMovement(points);

                            //Checks answer
                            if (pressPosition == 2) {
                                //Next stage
                                desertSkeletonCombatProgress[1] = 1;
                                desertSkeletonCombatProgress[2] = 2;
                            } else if (pressPosition == 4) {
                                //back a stage
                                desertSkeletonCombatProgress[1] = 1;
                                desertSkeletonCombatProgress[0] = 2;
                            }
                        } else if (desertSkeletonCombatProgress[2] == 2) {
                            LCD.Clear();
                            //Show skeleton text
                            FEHImage skeletonText;
                            skeletonText.Open("Texts/Skeleton_text.png");
                            skeletonText.Draw(20, 15);

                            //Increments points
                            points++;

                            desertSkeletonCombatProgress[2] = 1;
                            desertSkeletonCombatProgress[3] = 2;

                            //Exits combat
                            //reset progress
                            gameProgress[10] = 1;
                            //update progress
                            gameProgress[11] = 2;
                            //update other stats
                            backGroundDayNight.currentBackGround[0][0] = 111;
                            backGroundDayNight.currentBackGround[0][1] = 111;
                            backGroundDayNight.currentBackGround[0][2] = 111;
                            backGroundDayNight.currentBackGround[2][0] = 2;
                            backGroundDayNight.map = 2;
                            backGroundDayNight.zone = 0;
                            //Pulls out of combat
                            backGroundDayNight.currentBackGround[4][0] = 1;
                            backGroundDayNight.inCombat = false;
                            wallptr = desertWalls;

                            //Adjusts player position
                            rectangle playerTempHitBox1 = playerHitBox.getRectangleCoords();
                            playerTempHitBox1.pairCoords1.x = 151;
                            playerTempHitBox1.pairCoords1.y = 205;
                            playerTempHitBox1.pairCoords2.x = 158;
                            playerTempHitBox1.pairCoords2.y = 218;
                            playerHitBox.setCoordinates(playerTempHitBox1);

                            playerSprite.changeCoordinates(140, 190);
                        }
                    }

                    if (gameProgress[12] == 2) {
                        //Desert Boss Combat

                        //Draws boss
                        sprite desertBoss(100, "Desert Boss", "Sprites/Desert_Boss.png", 236, 21);

                        //checks which answer the player chooses
                        int pressPosition = playerSprite.getPressPositionForMovement(points);

                        //moves sprites to right location on combat screen
                        playerSprite.characterMovement(&backGroundDayNight, wallptr, &playerHitBox, pressPosition);

                        backGroundDayNight.Main_BackGround();
                        playerSprite.drawSprites();
                        desertBoss.drawSprites();

                        if (desertBossCombatProgress[0] == 2) {
                            //Boss beginning text
                            
                            FEHImage desertGuardText;
                            desertGuardText.Open("Texts/Desert_guard_text.png");
                            desertGuardText.Draw(20, 15);

                            desertBossCombatProgress[0] = 1;
                            desertBossCombatProgress[1] = 2;

                        } else if (desertBossCombatProgress[2] == 2) {
                            LCD.WriteLine("What is 7!?");
                            LCD.WriteLine("Choices: 5110 and 5040");
                            Sleep(100);

                            //Checks input
                            int pressPosition = playerSprite.getPressPositionForMovement(points);

                            //Checks answer
                            if (pressPosition == 2) {
                                //Next stage
                                desertBossCombatProgress[2] = 1;
                                desertBossCombatProgress[3] = 2;
                            } else if (pressPosition == 4) {
                                stillAlive = false;
                            }
                        } else if (desertBossCombatProgress[3] == 2) {
                            LCD.WriteLine("What is 16!/13!?");
                            LCD.WriteLine("Choices: 3360 and 5171");
                            Sleep(100);

                            //Checks input
                            int pressPosition = playerSprite.getPressPositionForMovement(points);

                            //Checks answer
                            if (pressPosition == 4) {
                                //Next stage
                                desertBossCombatProgress[3] = 1;
                                desertBossCombatProgress[4] = 2;
                            } else if (pressPosition == 2) {
                                //back a stage
                                desertBossCombatProgress[3] = 1;
                                desertBossCombatProgress[2] = 2;
                            }
                        } else if (desertBossCombatProgress[4] == 2) {
                            LCD.Clear();
                            //Show end boss text and narrator stuff
                            
                            FEHImage desertGuardText2;
                            desertGuardText2.Open("Texts/Desert_guard_2.png");
                            desertGuardText2.Draw(20, 15);

                            points++;
                            points++;
                            points++;

                            desertBossCombatProgress[4] = 1;
                            desertBossCombatProgress[5] = 2;

                        } else if (desertBossCombatProgress[6] == 2) {
                            LCD.Clear();

                            //Shows the gate screen
                            string gateIdentifierString = "Gates/Gate_with_desert_orb.png";
                            const char* gateIdentifier = gateIdentifierString.c_str();
                                
                            FEHImage gate3;
                            gate3.Open(gateIdentifier);
                            gate3.Draw(20, 15);

                            desertBossCombatProgress[6] = 1;
                            desertBossCombatProgress[7] = 2;

                            //Exits combat
                            //reset progress
                            gameProgress[12] = 1;
                            //update progress
                            gameProgress[13] = 2;
                            //update other stats
                            backGroundDayNight.currentBackGround[0][0] = 111;
                            backGroundDayNight.currentBackGround[0][1] = 121;
                            backGroundDayNight.currentBackGround[0][2] = 111;
                            backGroundDayNight.map = 0;
                            backGroundDayNight.zone = 1;
                            backGroundDayNight.currentBackGround[4][0] = 1;
                            backGroundDayNight.inCombat = false;
                            wallptr = walls[3];

                            backGroundDayNight.DayNight();
                            
                            rectangle playerTempHitBox1 = playerHitBox.getRectangleCoords();
                            playerTempHitBox1.pairCoords1.x = 131;
                            playerTempHitBox1.pairCoords1.y = 143;
                            playerTempHitBox1.pairCoords2.x = 138;
                            playerTempHitBox1.pairCoords2.y = 156;
                            playerHitBox.setCoordinates(playerTempHitBox1);

                            playerSprite.changeCoordinates(120, 128);
                            
                        }
                    }
                    
                } else if (backGroundDayNight.zone == 1) {
                    //final boss combat

                    if (gameProgress[20] == 2) {
                        //Draws boss

                        //checks which answer the player chooses
                        int pressPosition = playerSprite.getPressPositionForMovement(points);

                        //moves sprites to right location on combat screen
                        playerSprite.characterMovement(&backGroundDayNight, wallptr, &playerHitBox, pressPosition);

                        backGroundDayNight.Main_BackGround();
                        playerSprite.drawSprites();

                        if (finalBossCombatProgress[0] == 2) {
                            //Boss beginning text
                            
                            FEHImage finalBossText;
                            finalBossText.Open("Texts/Impano_2.png");
                            finalBossText.Draw(20, 15);

                            finalBossCombatProgress[0] = 1;
                            finalBossCombatProgress[1] = 2;


                        } else if (finalBossCombatProgress[2] == 2) {
                            LCD.WriteLine("What is the surface");
                            LCD.WriteLine("integral of 1 over");
                            LCD.WriteLine("a sphere of radius 2?");
                            LCD.WriteLine("Choices: 16pi/3 and 16pi");
                            Sleep(100);

                            //Receives input
                            int pressPosition = playerSprite.getPressPositionForMovement(points);

                            //Checks answer
                            if (pressPosition == 2) {
                                //Next stage
                                finalBossCombatProgress[2] = 1;
                                finalBossCombatProgress[3] = 2;
                            } else if (pressPosition == 4) {
                                stillAlive = false;
                            }
                        } else if (finalBossCombatProgress[3] == 2) {
                            LCD.WriteLine("Gimme the inverse");
                            LCD.WriteLine("matrix of");
                            LCD.WriteLine("[1, 2; 3, 4]?  :)");
                            LCD.WriteLine("Choices:");
                            LCD.WriteLine("[4, 1; -1.5, -0.5] (left)");
                            LCD.WriteLine("and");
                            LCD.WriteLine("[-2, 1; 1.5, -0.5] (right)");
                            Sleep(100);

                            //Receives input
                            int pressPosition = playerSprite.getPressPositionForMovement(points);

                            //Checks answer
                            if (pressPosition == 2) {
                                //Next stage
                                finalBossCombatProgress[3] = 1;
                                finalBossCombatProgress[4] = 2;
                            } else if (pressPosition == 4) {
                                //back a stage
                                finalBossCombatProgress[3] = 1;
                                finalBossCombatProgress[2] = 2;
                            }
                        } else if (finalBossCombatProgress[4] == 2) {
                            LCD.Clear();
                            //paimon texts
                            
                            FEHImage paimonSpirit;
                            paimonSpirit.Open("Sprites/Nice_wizard.png");
                            paimonSpirit.Draw(120, 105);
                            
                            FEHImage paimonSpiritText;
                            paimonSpiritText.Open("Texts/Paimon_spirit.png");
                            paimonSpiritText.Draw(20, 15);

                            //Increment points
                            points++;
                            points++;
                            points++;
                            points++;
                            points++;
                            points++;
                            points++;
                            points++;
                            points++;
                            points++;

                            finalBossCombatProgress[4] = 1;
                            finalBossCombatProgress[5] = 2;

                        } else if (finalBossCombatProgress[6] == 2) {
                            LCD.Clear();
                            
                            FEHImage happyKingdom;
                            happyKingdom.Open("more_images/kingdom_background_transformed.png");
                            happyKingdom.Draw(20, 15);

                            FEHImage finalNarratorText;
                            finalNarratorText.Open("Texts/Narrator_7.png");
                            finalNarratorText.Draw(20, 15);

                            //end game
                            finalBossCombatProgress[6] = 1;
                            finalBossCombatProgress[7] = 2;
                        }
                    }
                }
            }

            //Show warning
            rectangle temp = playerHitBox.getRectangleCoords();
            if (temp.pairCoords1.x < 10) {
                LCD.WriteLine("Danger!!!");
                LCD.WriteLine("Danger!!!");
                LCD.WriteLine("Danger!!!");
                LCD.WriteLine("    The dark arts are");
                LCD.WriteLine("    destroying the fabric");
                LCD.WriteLine("    of reality");
                LCD.WriteLine("   Consider going back");
                LCD.WriteLine("Danger!!!");
                LCD.WriteLine("Danger!!!");
            }
            playerHitBox.setCoordinates(temp);

            //Death screen
            if (stillAlive == false) {
                LCD.Clear();
                FEHImage deadScreen;
                deadScreen.Open("more_images/game_over.png");
                deadScreen.Draw(20, 15);
            }

            //Updates and sleeps
            LCD.Update();
            Sleep(1);

            //Implements pauses in the program
            if (stillAlive == false) {
                Sleep(3.);
                LCD.Clear();
                break;
            }

            if (passed) {
                while(!LCD.Touch(&xClick,&yClick)) {};
                while(LCD.Touch(&xClick,&yClick)) {};
                passed = false;

                if (startTexts == 0) {
                    startTexts = 300;
                } else if (startTexts == 300) {
                    startTexts = 500;
                } else if (startTexts == 500) {
                    startTexts = 700;
                } else if (startTexts == 700) {
                    startTexts = 900;
                } else if (startTexts == 900) {
                    startTexts = 1100;
                } else if (startTexts == 1100) {
                    startTexts = 1300;
                }
            }

            if (forestMonosterCombatProgress[3] == 2) {
                Sleep(3.);
                forestMonosterCombatProgress[3] = 1;
            }

            if (forestBossCombatProgress[1] == 2) {
                Sleep(3.);
                forestBossCombatProgress[1] = 1;
                forestBossCombatProgress[2] = 2;
            }

            if (forestBossCombatProgress[5] == 2) {
                Sleep(7.);
                forestBossCombatProgress[5] = 1;
                forestBossCombatProgress[6] = 2;
            }

            if (forestBossCombatProgress[7] == 2) {
                Sleep(7.);
                forestBossCombatProgress[7] = 1;
            }

            if (winterMonsterCombatProgress[3] == 2) {
                Sleep(3.);
                winterMonsterCombatProgress[3] = 1;
            }

            if (winterBossCombatProgress[1] == 2) {
                Sleep(3.);
                winterBossCombatProgress[1] = 1;
                winterBossCombatProgress[2] = 2;
            }

            if (winterBossCombatProgress[5] == 2) {
                Sleep(7.);
                winterBossCombatProgress[5] = 1;
                winterBossCombatProgress[6] = 2;
            }

            if (winterBossCombatProgress[7] == 2) {
                Sleep(7.);
                winterBossCombatProgress[7] = 1;
            }

            if (desertSkeletonCombatProgress[3] == 2) {
                Sleep(3.);
                desertSkeletonCombatProgress[3] = 1;
            }

            if (desertBossCombatProgress[1] == 2) {
                Sleep(3.);
                desertBossCombatProgress[1] = 1;
                desertBossCombatProgress[2] = 2;
            }

            if (desertBossCombatProgress[5] == 2) {
                Sleep(7.);
                desertBossCombatProgress[5] = 1;
                desertBossCombatProgress[6] = 2;
            }

            if (desertBossCombatProgress[7] == 2) {
                Sleep(7.);
                desertBossCombatProgress[7] = 1;
            }

            if (gameProgress[14] == 2) {
                Sleep(7.);
                gameProgress[14] = 1;
                gameProgress[15] = 2;
            }

            if (gameProgress[16] == 2) {
                Sleep(7.);
                gameProgress[16] = 1;
                gameProgress[17] = 2;
            }

            if (gameProgress[18] == 2) {
                Sleep(7.);
                gameProgress[18] = 1;
                gameProgress[19] = 2;
                wallptr = finalBossRoom;
            }

            if (finalBossCombatProgress[1] == 2) {
                Sleep(3.);
                finalBossCombatProgress[1] = 1;
                finalBossCombatProgress[2] = 2;
            }

            if (finalBossCombatProgress[5] == 2) {
                Sleep(7.);
                finalBossCombatProgress[5] = 1;
                finalBossCombatProgress[6] = 2;
            }

            if (finalBossCombatProgress[7] == 2) {
                Sleep(6.);
                finalBossCombatProgress[7] = 1;
                points = 22;
                break;
            }

            LCD.Clear();
        }
    }
    return 0;
}


//Start menu
//Andy
void Start_Menu(int points) {
    while (1) {
        //Clear Back Ground of Display
        LCD.Clear(BLACK);
        //Creates menu for game
        FEHImage menuScreen;
        menuScreen.Open("Menu_screen/Menu.png");
        menuScreen.Draw(20, 15);

        LCD.Update();

        float x_position, y_position;
        //Checks for touch
        while(!LCD.Touch(&x_position,&y_position)) {};
        while(LCD.Touch(&x_position,&y_position)) {};
 
        if (((y_position > (-1.68421*(x_position-158)) + 69) && (x_position < 177) && (y_position < (1.68421*(x_position-158)) + 69)) || ((x_position > 177) && (x_position < 214) && (y_position > 35) && (y_position < 100)) || ((y_position < (-1.631579 * (x_position - 233)) + 69) && (x_position > 214) && (y_position > (1.631579*(x_position-233))+69))) {
            //Start
            break;
        } else if (((y_position > (-1.68421*(x_position-218)) + 172) && (x_position < 237) && (y_position < (1.68421*(x_position-218)) + 172)) || ((x_position > 237) && (x_position < 275) && (y_position > 139) && (y_position < 203)) || ((y_position < (-1.631579 * (x_position - 293)) + 172) && (x_position > 275) && (y_position > (1.631579*(x_position-293))+172))) {
            //Help
            LCD.Clear(BLACK);
            LCD.WriteLine("Use arrow keys to move and hold left shift to fight");
            LCD.WriteLine("progress through the story");
            LCD.WriteLine("Fight monsters and obtain points");
            LCD.Update();
            while(!LCD.Touch(&x_position,&y_position)) {};
            while(LCD.Touch(&x_position,&y_position)) {};
        } else if (((y_position > (-1.68421*(x_position-159)) + 138) && (x_position < 177) && (y_position < (1.68421*(x_position-159)) + 138)) || ((x_position > 177) && (x_position < 215) && (y_position > 106) && (y_position < 169)) || ((y_position < (-1.631579 * (x_position - 233)) + 137) && (x_position > 215) && (y_position > (1.631579*(x_position-233))+137))) {
            //Credits
            LCD.Clear(BLACK);
            LCD.WriteLine("Coded by Jason Yang and Andy Zhang");
            LCD.WriteLine("Inspired by pokemon and star rail");
            LCD.WriteLine("Game Over Screen: Tefbuck on Reddit");
            LCD.WriteLine("Dark wizard art: Wan Der on artStation");
            LCD.WriteLine("Kingdom background: Tyler Edlin Art on facebook");
            LCD.WriteLine("Burning kingdom: 吴彦祖 on artStation");

            LCD.Update();
            while(!LCD.Touch(&x_position,&y_position)) {};
            while(LCD.Touch(&x_position,&y_position)) {};
        } else if (((y_position > (-1.68421*(x_position-218)) + 103) && (x_position < 237) && (y_position < (1.68421*(x_position-218)) + 103)) || ((x_position > 237) && (x_position < 274) && (y_position > 71) && (y_position < 135)) || ((y_position < (-1.631579 * (x_position - 293)) + 103) && (x_position > 274) && (y_position > (1.631579*(x_position-293))+103))) {
            //Statistics
            LCD.Clear(BLACK);
            LCD.Write("TOTAL Points: ");
            LCD.WriteLine(to_string(points));
            LCD.Update();
            while(!LCD.Touch(&x_position,&y_position)) {};
            while(LCD.Touch(&x_position,&y_position)) {};
        }
    }
}

//Constructor for bacground class
//Andy
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
    //first combat map
    currentBackGround[4][0] = 1;
    //second combat map
    currentBackGround[4][1] = 1;
    //extra space in array, dont use
    currentBackGround[4][2] = 1;

    map = 0;
    zone = 1;
    inCombat = false;
}

//Define functions for backgrounds
//Display appropriate background image based on combat, map, and day
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
                string mapIdentifierString = "Other_maps/" + to_string(map) + "_" + to_string(zone) + ".png";
                const char* mapIdentifier = mapIdentifierString.c_str();
                    
                FEHImage base1;
                base1.Open(mapIdentifier);
                base1.Draw(20, 15);
            }
        }
    } else {
        //in combat
        map = 4;
        if (currentBackGround[map][zone] == 2) {
            string mapIdentifierString = "Combat_Background/Combat_" + to_string(map) + "_" + to_string(zone) + ".png";
            const char* mapIdentifier = mapIdentifierString.c_str();
                
            FEHImage base1;
            base1.Open(mapIdentifier);
            base1.Draw(20, 15);
        }
    }
}

//Constructor for sprite class
//Andy
sprite::sprite(float spriteHealth, string spriteName, string givenSpriteFile, float x_start, float y_start) {
    health = spriteHealth;
    spritePosition.x = x_start;
    spritePosition.y = y_start;
    name = spriteName;
    spriteFile = givenSpriteFile;
    canMoveUp = true;
    canMoveRight = true;
    canMoveDown = true;
    canMoveLeft = true;
    oldPress = 1;
    oldPressPosition = 1;
}

//Draw sprite method
//Andy
void sprite::drawSprites() {
    
    const char* mapIdentifier = spriteFile.c_str();
    
    FEHImage sprite;
    sprite.Open(mapIdentifier);
    sprite.Draw(spritePosition.x, spritePosition.y);
}

//Receive key inputs
int sprite::getPressPositionForMovement(int points) {
    oldPressPosition = oldPress;
    if (GetAsyncKeyState(VK_UP) & 0x8000) {
        oldPress = 1;
        return 1;
    } else if (GetAsyncKeyState(VK_RIGHT) & 0x8000){
        oldPress = 2;
        return 2;
    } else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        oldPress = 3;
        return 3;
    } else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        oldPress = 4;
        return 4;
    } else if (GetAsyncKeyState(VK_LSHIFT) & 0x8000) {
        return 5;
    } else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
        Start_Menu(points);
    }
    return 0;
}


//Movement
void sprite::characterMovement(class BackGround_DayNight* backdrop, class HitBox walls[12], class HitBox* player, int pressPosition) {
    
    //Checks for user input and any collisions and adjust position based on that
    LCD.Clear(BLACK);
    rectangle playerTempHitBox = player->getRectangleCoords();
    if (backdrop->map == 0) {
        switch (pressPosition) {
            case 1:
                //up
                if (canMoveUp) {
                    canMoveRight = true;
                    canMoveDown = true;
                    canMoveLeft = true;
                    spriteFile = "Sprites/Knight_back.png";
                    spritePosition.y -= 1;
                    playerTempHitBox.pairCoords1.y -= 1;
                    playerTempHitBox.pairCoords2.y -= 1;
                    for (int i = 0; i < 8; i++) {
                        if (walls[i].colliding(*player)) {
                            spritePosition.y += 2;
                            playerTempHitBox.pairCoords1.y += 2;
                            playerTempHitBox.pairCoords2.y += 2;
                            if (oldPressPosition == 1) {
                                canMoveUp = false;
                                canMoveRight = true;
                                canMoveDown = true;
                                canMoveLeft = true;
                            } else if (oldPressPosition == 2) {
                                canMoveUp = true;
                                canMoveRight = false;
                                canMoveDown = true;
                                canMoveLeft = true;
                            } else if (oldPressPosition == 3) {
                                canMoveUp = true;
                                canMoveRight = true;
                                canMoveDown = false;
                                canMoveLeft = true;
                            } else if (oldPressPosition == 4) {
                                canMoveUp = true;
                                canMoveRight = true;
                                canMoveDown = true;
                                canMoveLeft = false;
                            }
                            i = 24;
                        } else {
                            canMoveUp = true;
                            canMoveRight = true;
                            canMoveDown = true;
                            canMoveLeft = true;
                        }
                    }
                }
                break;
            case 2:
                //right
                if (canMoveRight) {
                    canMoveUp = true;
                    canMoveDown = true;
                    canMoveLeft = true;
                    spriteFile = "Sprites/Knight_right.png";
                    spritePosition.x += 1;
                    playerTempHitBox.pairCoords1.x += 1;
                    playerTempHitBox.pairCoords2.x += 1;
                    for (int i = 0; i < 8; i++) {
                        if (walls[i].colliding(*player)) {
                            spritePosition.x -= 2;
                            playerTempHitBox.pairCoords1.x -= 2;
                            playerTempHitBox.pairCoords2.x -= 2;
                            if (oldPressPosition == 1) {
                                canMoveUp = false;
                                canMoveRight = true;
                                canMoveDown = true;
                                canMoveLeft = true;
                            } else if (oldPressPosition == 2) {
                                canMoveUp = true;
                                canMoveRight = false;
                                canMoveDown = true;
                                canMoveLeft = true;
                            } else if (oldPressPosition == 3) {
                                canMoveUp = true;
                                canMoveRight = true;
                                canMoveDown = false;
                                canMoveLeft = true;
                            } else if (oldPressPosition == 4) {
                                canMoveUp = true;
                                canMoveRight = true;
                                canMoveDown = true;
                                canMoveLeft = false;
                            }
                            i = 24;
                        } else {
                            canMoveUp = true;
                            canMoveRight = true;
                            canMoveDown = true;
                            canMoveLeft = true;
                        }
                    }
                }
                break;
            case 3:
                //down
                if (canMoveDown) {
                    canMoveUp = true;
                    canMoveRight = true;
                    canMoveLeft = true;
                    spriteFile = "Sprites/Knight_front.png";
                    spritePosition.y += 1;
                    playerTempHitBox.pairCoords1.y += 1;
                    playerTempHitBox.pairCoords2.y += 1;
                    for (int i = 0; i < 8; i++) {
                        if (walls[i].colliding(*player)) {
                            spritePosition.y -= 2;
                            playerTempHitBox.pairCoords1.y -= 2;
                            playerTempHitBox.pairCoords2.y -= 2;
                            if (oldPressPosition == 1) {
                                canMoveUp = false;
                                canMoveRight = true;
                                canMoveDown = true;
                                canMoveLeft = true;
                            } else if (oldPressPosition == 2) {
                                canMoveUp = true;
                                canMoveRight = false;
                                canMoveDown = true;
                                canMoveLeft = true;
                            } else if (oldPressPosition == 3) {
                                canMoveUp = true;
                                canMoveRight = true;
                                canMoveDown = false;
                                canMoveLeft = true;
                            } else if (oldPressPosition == 4) {
                                canMoveUp = true;
                                canMoveRight = true;
                                canMoveDown = true;
                                canMoveLeft = false;
                            }
                            i = 24;
                        } else {
                            canMoveUp = true;
                            canMoveRight = true;
                            canMoveDown = true;
                            canMoveLeft = true;
                        }
                    }
                }
                break;
            case 4:
                //left
                if (canMoveLeft) {
                    canMoveUp = true;
                    canMoveRight = true;
                    canMoveDown = true;
                    spriteFile = "Sprites/Knight_left.png";
                    spritePosition.x -= 1;
                    playerTempHitBox.pairCoords1.x -= 1;
                    playerTempHitBox.pairCoords2.x -= 1;
                    for (int i = 0; i < 8; i++) {
                        if (walls[i].colliding(*player)) {
                            spritePosition.x += 2;
                            playerTempHitBox.pairCoords1.x += 2;
                            playerTempHitBox.pairCoords2.x += 2;
                            if (oldPressPosition == 1) {
                                canMoveUp = false;
                                canMoveRight = true;
                                canMoveDown = true;
                                canMoveLeft = true;
                            } else if (oldPressPosition == 2) {
                                canMoveUp = true;
                                canMoveRight = false;
                                canMoveDown = true;
                                canMoveLeft = true;
                            } else if (oldPressPosition == 3) {
                                canMoveUp = true;
                                canMoveRight = true;
                                canMoveDown = false;
                                canMoveLeft = true;
                            } else if (oldPressPosition == 4) {
                                canMoveUp = true;
                                canMoveRight = true;
                                canMoveDown = true;
                                canMoveLeft = false;
                            }
                            i = 24;
                        } else {
                            canMoveUp = true;
                            canMoveRight = true;
                            canMoveDown = true;
                            canMoveLeft = true;
                        }
                    }
                }
                break;
        }
    } else if (backdrop->map == 4) {
        spriteFile = "Sprites/Knight_back.png";
        spritePosition.x = 80;
        spritePosition.y = 163;
    } else {
        switch (pressPosition) {
            case 1:
                //up
                if (canMoveUp) {
                    canMoveRight = true;
                    canMoveDown = true;
                    canMoveLeft = true;
                    spriteFile = "Sprites/Knight_back.png";
                    spritePosition.y -= 1;
                    playerTempHitBox.pairCoords1.y -= 1;
                    playerTempHitBox.pairCoords2.y -= 1;
                    for (int i = 0; i < 3; i++) {
                        if (walls[i].colliding(*player)) {
                            spritePosition.y += 2;
                            playerTempHitBox.pairCoords1.y += 2;
                            playerTempHitBox.pairCoords2.y += 2;
                            if (oldPressPosition == 1) {
                                canMoveUp = false;
                                canMoveRight = true;
                                canMoveDown = true;
                                canMoveLeft = true;
                            } else if (oldPressPosition == 2) {
                                canMoveUp = true;
                                canMoveRight = false;
                                canMoveDown = true;
                                canMoveLeft = true;
                            } else if (oldPressPosition == 3) {
                                canMoveUp = true;
                                canMoveRight = true;
                                canMoveDown = false;
                                canMoveLeft = true;
                            } else if (oldPressPosition == 4) {
                                canMoveUp = true;
                                canMoveRight = true;
                                canMoveDown = true;
                                canMoveLeft = false;
                            }
                            i = 24;
                        } else {
                            canMoveUp = true;
                            canMoveRight = true;
                            canMoveDown = true;
                            canMoveLeft = true;
                        }
                    }
                }
                break;
            case 2:
                //right
                if (canMoveRight) {
                    canMoveUp = true;
                    canMoveDown = true;
                    canMoveLeft = true;
                    spriteFile = "Sprites/Knight_right.png";
                    spritePosition.x += 1;
                    playerTempHitBox.pairCoords1.x += 1;
                    playerTempHitBox.pairCoords2.x += 1;
                    for (int i = 0; i < 3; i++) {
                        if (walls[i].colliding(*player)) {
                            spritePosition.x -= 2;
                            playerTempHitBox.pairCoords1.x -= 2;
                            playerTempHitBox.pairCoords2.x -= 2;
                            if (oldPressPosition == 1) {
                                canMoveUp = false;
                                canMoveRight = true;
                                canMoveDown = true;
                                canMoveLeft = true;
                            } else if (oldPressPosition == 2) {
                                canMoveUp = true;
                                canMoveRight = false;
                                canMoveDown = true;
                                canMoveLeft = true;
                            } else if (oldPressPosition == 3) {
                                canMoveUp = true;
                                canMoveRight = true;
                                canMoveDown = false;
                                canMoveLeft = true;
                            } else if (oldPressPosition == 4) {
                                canMoveUp = true;
                                canMoveRight = true;
                                canMoveDown = true;
                                canMoveLeft = false;
                            }
                            i = 24;
                        } else {
                            canMoveUp = true;
                            canMoveRight = true;
                            canMoveDown = true;
                            canMoveLeft = true;
                        }
                    }
                }
                break;
            case 3:
                //down
                if (canMoveDown) {
                    canMoveUp = true;
                    canMoveRight = true;
                    canMoveLeft = true;
                    spriteFile = "Sprites/Knight_front.png";
                    spritePosition.y += 1;
                    playerTempHitBox.pairCoords1.y += 1;
                    playerTempHitBox.pairCoords2.y += 1;
                    for (int i = 0; i < 3; i++) {
                        if (walls[i].colliding(*player)) {
                            spritePosition.y -= 2;
                            playerTempHitBox.pairCoords1.y -= 2;
                            playerTempHitBox.pairCoords2.y -= 2;
                            if (oldPressPosition == 1) {
                                canMoveUp = false;
                                canMoveRight = true;
                                canMoveDown = true;
                                canMoveLeft = true;
                            } else if (oldPressPosition == 2) {
                                canMoveUp = true;
                                canMoveRight = false;
                                canMoveDown = true;
                                canMoveLeft = true;
                            } else if (oldPressPosition == 3) {
                                canMoveUp = true;
                                canMoveRight = true;
                                canMoveDown = false;
                                canMoveLeft = true;
                            } else if (oldPressPosition == 4) {
                                canMoveUp = true;
                                canMoveRight = true;
                                canMoveDown = true;
                                canMoveLeft = false;
                            }
                            i = 24;
                        } else {
                            canMoveUp = true;
                            canMoveRight = true;
                            canMoveDown = true;
                            canMoveLeft = true;
                        }
                    }
                }
                break;
            case 4:
                //left
                if (canMoveLeft) {
                    canMoveUp = true;
                    canMoveRight = true;
                    canMoveDown = true;
                    spriteFile = "Sprites/Knight_left.png";
                    spritePosition.x -= 1;
                    playerTempHitBox.pairCoords1.x -= 1;
                    playerTempHitBox.pairCoords2.x -= 1;
                    for (int i = 0; i < 3; i++) {
                        if (walls[i].colliding(*player)) {
                            spritePosition.x += 2;
                            playerTempHitBox.pairCoords1.x += 2;
                            playerTempHitBox.pairCoords2.x += 2;
                            if (oldPressPosition == 1) {
                                canMoveUp = false;
                                canMoveRight = true;
                                canMoveDown = true;
                                canMoveLeft = true;
                            } else if (oldPressPosition == 2) {
                                canMoveUp = true;
                                canMoveRight = false;
                                canMoveDown = true;
                                canMoveLeft = true;
                            } else if (oldPressPosition == 3) {
                                canMoveUp = true;
                                canMoveRight = true;
                                canMoveDown = false;
                                canMoveLeft = true;
                            } else if (oldPressPosition == 4) {
                                canMoveUp = true;
                                canMoveRight = true;
                                canMoveDown = true;
                                canMoveLeft = false;
                            }
                            i = 24;
                        } else {
                            canMoveUp = true;
                            canMoveRight = true;
                            canMoveDown = true;
                            canMoveLeft = true;
                        }
                    }
                }
                break;
        }
    }
    player->setCoordinates(playerTempHitBox);
}


//Changes background when you move to new section of the base map
void sprite::changeBackGround(class BackGround_DayNight* backdrop, class HitBox*& wallptr, class HitBox* player, class sprite* playerSprite, HitBox baseWalls[7][12]) {
    rectangle playerTempHitBox = player->getRectangleCoords();
    switch (backdrop->map) {
        case 0:
            //base
            switch (backdrop->zone) {
                case 0:
                    //top 2
                    if (backdrop->currentBackGround[backdrop->map][backdrop->zone] == 121) {
                        //0_121
                        if (wallptr[8].colliding(*player)) {
                            backdrop->currentBackGround[backdrop->map][backdrop->zone] = 112;
                            playerSprite->spritePosition.x -= 260;
                            playerTempHitBox.pairCoords1.x -= 260;
                            playerTempHitBox.pairCoords2.x -= 260;
                            player->setCoordinates(playerTempHitBox);
                            wallptr = baseWalls[1];
                            break;
                        }
                    } else if (backdrop->currentBackGround[backdrop->map][backdrop->zone] == 112) {
                        //0_112
                        if (wallptr[8].colliding(*player)) {
                            backdrop->currentBackGround[backdrop->map][backdrop->zone] = 121;
                            playerSprite->spritePosition.x += 260;
                            playerTempHitBox.pairCoords1.x += 260;
                            playerTempHitBox.pairCoords2.x += 260;
                            player->setCoordinates(playerTempHitBox);
                            wallptr = baseWalls[0];
                            break;
                        }
                        if (wallptr[9].colliding(*player)) {
                            //resets current
                            backdrop->currentBackGround[backdrop->map][backdrop->zone] = 111;
                            //sets new
                            backdrop->currentBackGround[backdrop->map][1] = 112;
                            backdrop->zone = 1;
                            playerSprite->spritePosition.y -= 190;
                            playerTempHitBox.pairCoords1.y -= 190;
                            playerTempHitBox.pairCoords2.y -= 190;
                            player->setCoordinates(playerTempHitBox);
                            wallptr = baseWalls[4];
                            break;
                        }
                    }
                    player->setCoordinates(playerTempHitBox);
                    break;
                case 1:
                    //middle 3
                    if (backdrop->currentBackGround[backdrop->map][backdrop->zone] == 211) {
                        //1_211
                        if (wallptr[8].colliding(*player)) {
                            //resets current
                            backdrop->currentBackGround[backdrop->map][backdrop->zone] = 111;
                            //sets new
                            backdrop->currentBackGround[backdrop->map][2] = 211;
                            backdrop->zone = 2;
                            playerSprite->spritePosition.y -= 190;
                            playerTempHitBox.pairCoords1.y -= 190;
                            playerTempHitBox.pairCoords2.y -= 190;
                            player->setCoordinates(playerTempHitBox);
                            wallptr = baseWalls[5];
                            break;
                        }
                        if (wallptr[9].colliding(*player)) {
                            //resets current
                            backdrop->currentBackGround[backdrop->map][backdrop->zone] = 111;
                            //sets new
                            backdrop->currentBackGround[backdrop->map][1] = 121;
                            backdrop->zone = 1;
                            playerSprite->spritePosition.x -= 260;
                            playerTempHitBox.pairCoords1.x -= 260;
                            playerTempHitBox.pairCoords2.x -= 260;
                            player->setCoordinates(playerTempHitBox);
                            wallptr = baseWalls[3];
                            break;
                        }
                    } else if (backdrop->currentBackGround[backdrop->map][backdrop->zone] == 121) {
                        //1_121
                        if (wallptr[8].colliding(*player)) {
                            //resets current
                            backdrop->currentBackGround[backdrop->map][backdrop->zone] = 111;
                            //sets new
                            backdrop->currentBackGround[backdrop->map][1] = 211;
                            backdrop->zone = 1;
                            playerSprite->spritePosition.x += 260;
                            playerTempHitBox.pairCoords1.x += 260;
                            playerTempHitBox.pairCoords2.x += 260;
                            player->setCoordinates(playerTempHitBox);
                            wallptr = baseWalls[2];
                            break;
                        }
                        if (wallptr[9].colliding(*player)) {
                            //resets current
                            backdrop->currentBackGround[backdrop->map][backdrop->zone] = 111;
                            //sets new
                            backdrop->currentBackGround[backdrop->map][2] = 121;
                            backdrop->zone = 2;
                            playerSprite->spritePosition.y -= 190;
                            playerTempHitBox.pairCoords1.y -= 190;
                            playerTempHitBox.pairCoords2.y -= 190;
                            player->setCoordinates(playerTempHitBox);
                            wallptr = baseWalls[6];
                            break;
                        }
                        if (wallptr[10].colliding(*player)) {
                            //resets current
                            backdrop->currentBackGround[backdrop->map][backdrop->zone] = 111;
                            //sets new
                            backdrop->currentBackGround[backdrop->map][2] = 121;
                            backdrop->zone = 2;
                            playerSprite->spritePosition.y -= 190;
                            playerTempHitBox.pairCoords1.y -= 190;
                            playerTempHitBox.pairCoords2.y -= 190;
                            player->setCoordinates(playerTempHitBox);
                            wallptr = baseWalls[6];
                            break;
                        }
                        if (wallptr[11].colliding(*player)) {
                            //resets current
                            backdrop->currentBackGround[backdrop->map][backdrop->zone] = 111;
                            //sets new
                            backdrop->currentBackGround[backdrop->map][1] = 112;
                            backdrop->zone = 1;
                            playerSprite->spritePosition.x -= 260;
                            playerTempHitBox.pairCoords1.x -= 260;
                            playerTempHitBox.pairCoords2.x -= 260;
                            player->setCoordinates(playerTempHitBox);
                            wallptr = baseWalls[4];
                            break;
                        }
                    } else if (backdrop->currentBackGround[backdrop->map][backdrop->zone] == 112) {
                        //1_112
                        if (wallptr[8].colliding(*player)) {
                            //resets current
                            backdrop->currentBackGround[backdrop->map][backdrop->zone] = 111;
                            //sets new
                            backdrop->currentBackGround[backdrop->map][1] = 121;
                            backdrop->zone = 1;
                            playerSprite->spritePosition.x += 260;
                            playerTempHitBox.pairCoords1.x += 260;
                            playerTempHitBox.pairCoords2.x += 260;
                            player->setCoordinates(playerTempHitBox);
                            wallptr = baseWalls[3];
                            break;
                        }
                        if (wallptr[9].colliding(*player)) {
                            //resets current
                            backdrop->currentBackGround[backdrop->map][backdrop->zone] = 111;
                            //sets new
                            backdrop->currentBackGround[backdrop->map][0] = 112;
                            backdrop->zone = 0;
                            playerSprite->spritePosition.y += 190;
                            playerTempHitBox.pairCoords1.y += 190;
                            playerTempHitBox.pairCoords2.y += 190;
                            player->setCoordinates(playerTempHitBox);
                            wallptr = baseWalls[1];
                            break;
                        }
                    }
                    player->setCoordinates(playerTempHitBox);
                    break;
                case 2:
                    //bottom 2
                    if (backdrop->currentBackGround[backdrop->map][backdrop->zone] == 211) {
                        //2_211
                        if (wallptr[8].colliding(*player)) {
                            //resets current
                            backdrop->currentBackGround[backdrop->map][backdrop->zone] = 111;
                            //sets new
                            backdrop->currentBackGround[backdrop->map][1] = 211;
                            backdrop->zone = 1;
                            playerSprite->spritePosition.y += 190;
                            playerTempHitBox.pairCoords1.y += 190;
                            playerTempHitBox.pairCoords2.y += 190;
                            player->setCoordinates(playerTempHitBox);
                            wallptr = baseWalls[2];
                            break;
                        }
                        if (wallptr[9].colliding(*player)) {
                            //resets current
                            backdrop->currentBackGround[backdrop->map][backdrop->zone] = 111;
                            //sets new
                            backdrop->currentBackGround[backdrop->map][2] = 121;
                            backdrop->zone = 2;
                            playerSprite->spritePosition.x -= 260;
                            playerTempHitBox.pairCoords1.x -= 260;
                            playerTempHitBox.pairCoords2.x -= 260;
                            player->setCoordinates(playerTempHitBox);
                            wallptr = baseWalls[6];
                            break;
                        }
                        if (wallptr[10].colliding(*player)) {
                            //resets current
                            backdrop->currentBackGround[backdrop->map][backdrop->zone] = 111;
                            //sets new
                            backdrop->currentBackGround[backdrop->map][2] = 121;
                            backdrop->zone = 2;
                            playerSprite->spritePosition.x -= 260;
                            playerTempHitBox.pairCoords1.x -= 260;
                            playerTempHitBox.pairCoords2.x -= 260;
                            player->setCoordinates(playerTempHitBox);
                            wallptr = baseWalls[6];
                            break;
                        }
                    } else if (backdrop->currentBackGround[backdrop->map][backdrop->zone] == 121) {
                        //2_121
                        if (wallptr[8].colliding(*player)) {
                            //resets current
                            backdrop->currentBackGround[backdrop->map][backdrop->zone] = 111;
                            //sets new
                            backdrop->currentBackGround[backdrop->map][2] = 211;
                            backdrop->zone = 2;
                            playerSprite->spritePosition.x += 260;
                            playerTempHitBox.pairCoords1.x += 260;
                            playerTempHitBox.pairCoords2.x += 260;
                            player->setCoordinates(playerTempHitBox);
                            wallptr = baseWalls[5];
                            break;
                        }
                        if (wallptr[9].colliding(*player)) {
                            //resets current
                            backdrop->currentBackGround[backdrop->map][backdrop->zone] = 111;
                            //sets new
                            backdrop->currentBackGround[backdrop->map][1] = 121;
                            backdrop->zone = 1;
                            playerSprite->spritePosition.y += 190;
                            playerTempHitBox.pairCoords1.y += 190;
                            playerTempHitBox.pairCoords2.y += 190;
                            player->setCoordinates(playerTempHitBox);
                            wallptr = baseWalls[3];
                            break;
                        }
                        if (wallptr[10].colliding(*player)) {
                            //resets current
                            backdrop->currentBackGround[backdrop->map][backdrop->zone] = 111;
                            //sets new
                            backdrop->currentBackGround[backdrop->map][2] = 211;
                            backdrop->zone = 2;
                            playerSprite->spritePosition.x += 260;
                            playerTempHitBox.pairCoords1.x += 260;
                            playerTempHitBox.pairCoords2.x += 260;
                            player->setCoordinates(playerTempHitBox);
                            wallptr = baseWalls[5];
                            break;
                        }
                        if (wallptr[11].colliding(*player)) {
                            //resets current
                            backdrop->currentBackGround[backdrop->map][backdrop->zone] = 111;
                            //sets new
                            backdrop->currentBackGround[backdrop->map][1] = 121;
                            backdrop->zone = 1;
                            playerSprite->spritePosition.y += 190;
                            playerTempHitBox.pairCoords1.y += 190;
                            playerTempHitBox.pairCoords2.y += 190;
                            player->setCoordinates(playerTempHitBox);
                            wallptr = baseWalls[3];
                            break;
                        }
                    }
                    player->setCoordinates(playerTempHitBox);
                    break;
            }
            player->setCoordinates(playerTempHitBox);
            break;
        case 1:
            //unused since its a single section
            break;
        case 2:
            //unused since its a single section
            break;
        case 3:
            //final boss
            if (backdrop->zone == 0) {
                if (wallptr[0].colliding(*player)) {
                    backdrop->currentBackGround[backdrop->map][backdrop->zone] = 1;
                    backdrop->zone = 1;
                    backdrop->currentBackGround[backdrop->map][backdrop->zone] = 2;
                    playerSprite->spritePosition.y += 190;
                    playerTempHitBox.pairCoords1.y += 190;
                    playerTempHitBox.pairCoords2.y += 190;
                    player->setCoordinates(playerTempHitBox);
                }
            }
            if (backdrop->zone == 1) {
                if (wallptr[2].colliding(*player)) {
                    backdrop->currentBackGround[backdrop->map][backdrop->zone] = 1;
                    backdrop->zone = 0;
                    backdrop->currentBackGround[backdrop->map][backdrop->zone] = 2;
                    playerSprite->spritePosition.y -= 190;
                    playerTempHitBox.pairCoords1.y -= 190;
                    playerTempHitBox.pairCoords2.y -= 190;
                    player->setCoordinates(playerTempHitBox);
                }
            }
            break;
    }
}


//change sprite coordinates
//Andy
void sprite::changeCoordinates(float newXCoord, float newYCoord) {
    spritePosition.x = newXCoord;
    spritePosition.y = newYCoord;
}


//change sprite file
//Andy
void sprite::changeSpriteFile(string newFile) {
    spriteFile = newFile;
}


//DayNight System
void BackGround_DayNight::DayNight() {
    int timeMarker = TimeNow();

    //Randomizes day and night
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

//Constructor for hitbox with arugments
//Andy
HitBox::HitBox(rectangle newRectangle) {
    rectangle1 = newRectangle;
}

//No argument constructor for hitbox class
//Andy
HitBox::HitBox() {
    
}

//Sets new cooridnates for hitbox
//Andy
void HitBox::setCoordinates(rectangle newRectangle) {
    rectangle1 = newRectangle;
}

//returns old coordinates of hitbox
//Andy
rectangle HitBox::getRectangleCoords() {
    return rectangle1;
}

//Checks if 2 hitboxes are colliding
bool HitBox::colliding(HitBox OtherHitBox) {
    if ((rectangle1.pairCoords1.x >= OtherHitBox.rectangle1.pairCoords1.x) && (OtherHitBox.rectangle1.pairCoords2.x >= rectangle1.pairCoords1.x)) {
        if ((rectangle1.pairCoords1.y >= OtherHitBox.rectangle1.pairCoords1.y) && (OtherHitBox.rectangle1.pairCoords2.y >= rectangle1.pairCoords1.y)) {
            return true;
        } else if ((rectangle1.pairCoords2.y >= OtherHitBox.rectangle1.pairCoords1.y) && (OtherHitBox.rectangle1.pairCoords1.y >= rectangle1.pairCoords1.y)) {
            return true;
        } else {
            return false;
        }
    } else if ((rectangle1.pairCoords2.x >= OtherHitBox.rectangle1.pairCoords1.x) && (OtherHitBox.rectangle1.pairCoords1.x >= rectangle1.pairCoords1.x)) {
        if ((rectangle1.pairCoords1.y >= OtherHitBox.rectangle1.pairCoords1.y) && (OtherHitBox.rectangle1.pairCoords2.y >= rectangle1.pairCoords1.y)) {
            return true;
        } else if ((rectangle1.pairCoords2.y >= OtherHitBox.rectangle1.pairCoords1.y) && (OtherHitBox.rectangle1.pairCoords1.y >= rectangle1.pairCoords1.y)) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 100000

bool exitFlag;

//initialize variables to call on classes
objPos myObj;  
Player *myplayer;
GameMechs *myGM;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false && myGM->getLoseFlagStatus() == false) //determines if the game is running
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    //allocating memory/spaces for the new class variables
    myGM = new GameMechs();
    myplayer = new Player(myGM);
    myGM->generateFood(myplayer->getPlayerPos()); //generating food
   
}

void GetInput(void)
{
   if(MacUILib_hasChar()!= 0){
        myGM->setInput(MacUILib_getChar());
    }  
}

void RunLogic(void)
{
    myplayer->updatePlayerDir();
    myplayer->movePlayer();
    myGM-> clearInput();    
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 

    //initializing variables and calling classes
    objPosArrayList* playerPos = myplayer->getPlayerPos();
    objPos foodPos = myGM->getFoodPosition();
    int playsize = playerPos->getSize();
    int SizeY = myGM->getBoardSizeY();
    int SizeX = myGM->getBoardSizeX();

    //deciding what to draw on speific location of the screen
    for(int i = 0; i < SizeY; i++){
        for(int j = 0; j < SizeX; j++){
            //draws boarder of the game
            if(i == 0 || j == 0 || i == SizeY - 1 || j == SizeX - 1){
                MacUILib_printf("#");
            //generates food in matching location
            }else if(foodPos.pos->x == j && foodPos.pos->y == i){
                MacUILib_printf("%c", foodPos.symbol);
            //Drawing player//
            }else{
                bool printed = false; //a boolean that decides if player was printed in a specific location
                for(int k = 0; k < playsize; k++){ //checks if each body part of player matches a location
                    objPos currentPlayerPos = playerPos->getElement(k);
                    //prints @ if player location matches 
                    if(currentPlayerPos.pos->x == j && currentPlayerPos.pos->y == i){
                        MacUILib_printf("%c", currentPlayerPos.symbol);
                        printed = true; 
                        break;
                    }
                }
                //if printed is false then put blank space
                if(!printed){
                    MacUILib_printf(" ");
                }
            }
        }
        MacUILib_printf("\n");
    }
        MacUILib_printf("Score: %d\n", myGM->getScore()); //prints score
        MacUILib_printf("WASD to move, Backspace to exit.\n");   
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();
    //display when user exits 
    if(myGM->getExitFlagStatus() == true){
        MacUILib_printf("You have exited the game.");
    }

    //display when user loses the game
    if(myGM->getLoseFlagStatus() == true){
        MacUILib_printf("YOU LOSE\n");  
        MacUILib_printf("Your total score: %d", myGM->getScore());     
    }
    
    delete myplayer;
    delete myGM; //cleaning memory

    MacUILib_uninit();
}

#include "GameMechs.h"
#include "MacUILib.h"
#include <time.h>

GameMechs::GameMechs()
{
    input =0;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = 20;
    boardSizeY = 10;  
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input =0;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = boardX;
    boardSizeY = boardY;    
}

// do you need a destructor?
GameMechs::~GameMechs()
{
   
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag; 
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput()
{
    if(MacUILib_hasChar() != 0){
        input = MacUILib_getChar();
    }
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;    
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;    
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

// More methods should be added here
void GameMechs::generateFood(objPosArrayList *blockOff)
{
    srand(time(NULL));
    bool Done = false; //a variable to determine when the loop stops
    int x,y;

    while(!Done){
        //picking random integers for x and y
        x = (rand()%(boardSizeX-2))+1;
        y = (rand()%(boardSizeY-2))+1;

        int playsize = blockOff->getSize(); //determining the snake size
        bool hit = false; //variable to determine if the player has been hit

        //checking if the coordinates match any part of the players body
        for(int k = 0; k < playsize; k++){
            objPos tempPos = blockOff->getElement(k); //the current snake body position 
            if(x == tempPos.pos->x && y == tempPos.pos->y) {
            hit = true;
            break;
            }
        }
        //if coordinates dont match loop is closed
        if(!hit){
            Done = true;
        }
    }
    food.setObjPos(x, y, 'o'); //generate the food on board
}


objPos GameMechs::getFoodPosition() const
{
    return food;
}
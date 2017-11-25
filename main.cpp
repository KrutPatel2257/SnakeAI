#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <time.h>
using namespace std;
bool gameOver; // Boolean for checking if game over.

const int width = 40; // Window width.
const int height = 20; // Window height.
int x, y; // Snakes x and y coordinates.
int fruitX, fruitY; // Fruits x and y coordinates.
int score; // Score value holder.
enum eDirection {STOP = 0, LEFT, RIGHT,UP, DOWN}; // Direction for snake.
eDirection dir; // variable of eDirection.

int tailX[100], tailY[100]; // TailX and TailY coordinates.
int nTail; // Length of the tail holder.

void Setup(){
    system("color 0a");
    srand(time(0)); // seed random based on current time.
    gameOver = false;
    dir = STOP; // Initial stat of snake is STOP.

    // Set snake to center of window.
    x = width / 2;
    y = width / 2;

    // Set position of fruit within the bounds of the window.
    fruitY = rand() % (height-2) + 1;
    fruitX = rand() % (width-2) + 1;

    // Initialize score to 0.
    score = 0;

    // Initialize length of tail to 0.
    nTail = 0;
}

void Draw(){
    system("cls"); // Clear console window.

    // Print upper boundary of the game.
    for (int i = 0; i < width; i++){
        cout<<"#"; // # is the wall.
    }
    cout<<endl; // Move to next row after upper boundary row.

    // Print the map of the game.
    for (int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(j == 0 || j == width-1){ // If j is on the left or right boundary column print the wall #.
                cout<<"#";
            }
            else { // Else if it is not the boundary we will print the game area.
                if(i == y && j == x)
                    cout<<"O"; // O is the snake.
                else if(i == fruitY && j == fruitX)
                    cout<<"F"; // F is the fruit.
                else{
                    bool isTail = false;
                    for(int k = 0; k < nTail; k++){
                        if(tailX[k] == j && tailY[k] == i){
                            cout<<"0";
                            isTail = true;
                        }
                    }
                    if(!isTail)
                        cout<<" ";
                }
            }
        }
        cout<<endl; // Move to next row.
    }

    // Print the bottom boundary of the game.
    for (int i = 0; i < width; i++){
        cout<<"#";
    }
    cout<<endl<<endl;
    cout<<"Score: "<<score;
}

void Input(){
    if(_kbhit()){ // If keyboard is pressed _kbhit() returns true.
        switch(_getch()){ // Get the character pressed.
        case 'a':
            if (dir == RIGHT && nTail!= 0) // if current direction is opposite then just return.
                return;
            dir = LEFT; // Set dir to LEFT.
            break;
        case 'd':
            if (dir == LEFT && nTail!= 0) // if current direction is opposite then just return.
                return;
            dir = RIGHT; // Set dir to RIGHT.
            break;
        case 'w':
            if (dir == DOWN && nTail!= 0) // if current direction is opposite then just return.
                return;
            dir = UP; // Set dir to UP.
            break;
        case 's':
            if (dir == UP && nTail!= 0) // if current direction is opposite then just return.
                return;
            dir = DOWN; // Set dir to DOWN.
            break;
        case 'x': // x for quit game.
            gameOver = true;
            break;
        default: // if anything else is pressed do nothing.
            break;
        }
    }
}

void Logic(){
    int prevX = tailX[0]; // Previous tail X coordinate.
    int prevY = tailY[0]; // Previous tail Y coordinate.
    int tempX, tempY;
    tailX[0] = x;
    tailY[0] = y;
    for(int i = 1; i < nTail; i++){
        tempX = tailX[i];
        tempY = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = tempX;
        prevY = tempY;
    }
    // Logic for moving the snake based on the input.
    switch(dir){
    case STOP:
        break;
    case LEFT:
        x--; // Decrease x coordinate of snake;
        break;
    case RIGHT:
        x++; // Increase x coordinate of snake;
        break;
    case UP:
        y--; // Decrease y coordinate of snake;
        break;
    case DOWN:
        y++; // Increase y coordinate of snake;
        break;
    default:
        break;
    }

    // If snakes moves out of map bounds then game over.
//    if(x < 1 || x > width-2 || y < 0 || y > height-1){
//        gameOver = true;
//    }

    // Make the snake appear from other side
    if(x > width - 2) x = 1; else if (x<1) x = width - 2;
    if(y > height-1) y = 0; else if (y<0) y = height - 1;

    for(int i = 0; i < nTail; i++){
        if(tailX[i] == x && tailY[i] == y){
            gameOver = true;
        }
    }
    // if snake gets on the fruits position increase score.
    if(x == fruitX && y == fruitY){
        nTail++; // Increase tail by 1.
        score += 10; // Increase score by 10.
        // Set new random position of the fruit.
        fruitY = rand() % (height-2) + 1;
        fruitX = rand() % (width-2) + 1;
    }
}

// Function for Snake AI.
void MoveSnake(){
    if(x != fruitX){
        if(fruitX - x < 0 && dir != RIGHT) // "dir != RIGHT" to avoid back collision.
            dir = LEFT;
        else
            dir = RIGHT;
    }else if(y != fruitY && dir != DOWN){ // "dir != RIGHT" to avoid back collision.
        if(fruitY - y < 0)
            dir = UP;
        else
            dir = DOWN;
    }
}

// Function for making a pause.
void sleep(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

int main()
{
    while(true){
        Setup(); // Reset game.
        while(!gameOver){ // Play game until gameOver is true.
            Draw();
            //Input();
            MoveSnake();
            Logic();
            if(dir == UP || dir == DOWN){
                sleep(10);
            }
        }
    }
    return 0;
}

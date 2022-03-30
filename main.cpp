#include <bits/stdc++.h>
#include<conio.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x,y, fruitX, fruitY, score;
int tailX[100],tailY[100];
vector<int> conX, conY;
int con;
int nTail;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void Setup(){
	gameOver = false;
	dir = STOP;
	x = width/2;
	y = height/2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw(){
	system("clear");
	for(int i = 0; i<width+1; i++){
		cout<<"#";
	}
	cout<<endl;

	for(int i = 0; i<height; i++){
		for(int j = 0; j<width; j++){
			if(j==0){
				cout<<"#";
			}
			if(i==y && j == x){
				cout<<"O";
			}else if(i==fruitY && j==fruitX){
				cout<<"*";
			}else{
				bool print = false;
				for(int k = 0; k<nTail; k++){
					if(i == tailY[k] && j==tailX[k]){
						cout<<"o";
						print = true;
					}
				}
				for(int l = 0; l<con; l++){
					if(i == conY[l] && j==conX[l]){
						cout<<"C";
						print = true;
					}
				}
				if(!print){
					cout<<" ";
				}
			}
			if(j == width-1){
				cout<<"#";
			}
		}
		cout<<endl;
	}



	for(int i = 0; i<width+1; i++){
		cout<<"#";
	}
	cout<<endl;
	cout<<"score: "<<score<<endl;
}

void Input(){
	if(_kbhit()){
		switch(_getche()){
			case 'a':
				if(dir != RIGHT){
					dir = LEFT;
					break;
				}
				break;	
			case 's':
				if(dir != UP){
					dir = DOWN;
					break;
				}
				break;
			case 'd':
				if(dir != LEFT){
					dir = RIGHT;
					break;
				}
				break;
			case 'w':
				if(dir != DOWN){
					dir = UP;
					break;
				}
				break;
			case 'x':
				gameOver = true;
				break;
		}
	}
}

void Logic(){
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;

	for(int i = 1; i<nTail; i++){
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i]  = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch(dir){
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
	}
	// if(x>width -1 || x<0 || y>height -1 || y<0){
	// 	gameOver = true;
	// }
	if(x>width-1) x=0;
	if(x<0) x = width-1;
	if(y>width-1) y=0;
	if(y<0) y = height-1;

	for(int i = 0; i<nTail; i++){
		if(tailX[i] == x && tailY[i] == y){
			gameOver = true;
		}
	}

	for(int i = 0; i<con; i++){
		if(conX[i] == x && conY[i] == y){
			gameOver = true;
		}
	}

	if(x == fruitX && y == fruitY){
		score += 1;
		fruitX = rand() % width;
		fruitY = rand() % height;
		if(con < 10){
			int tempX = rand() % width;
			int tempY = rand() % height;
			while(tempX == x && tempY == y){
				tempX = rand() % width;
				tempY = rand() % height;
			}
			conX.push_back(tempX);
			conY.push_back(tempY);
			con++;
		}
		nTail++;
	}
}

int main(){
	Setup();
	while(!gameOver){
		Draw();
		Input();
		Logic();
		this_thread::sleep_for(chrono::milliseconds(100));
	}
	system("clear");
	cout<<"GAME OVER"<<endl;
	cout<<"Score: "<<score<<endl;
	return 0;
}
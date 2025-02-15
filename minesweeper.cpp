#include<iostream>
#include<cstdlib>
#include<ctime>
#include<windows.h>
#include<iomanip>
using namespace std;
#define row 9
#define col 9
void initializeBoard(char [][col]);  
void placeMines(char [][col],int);
void displayBoard(char [][col], bool [][col]);
void playTurn(char [][col],bool [][col]);
bool checkMine(char [][col],int , int);
void openBox(char [][col],bool [][col],int , int);
void floodflow(char [][col],bool [][col],int , int);
bool winCheck(bool [][col], char [][col], int );
int main()
{
int mines=10;
char board[row][col];    // it will contain the values i.e. M for mines,0 means no mines on adjacent and 1 means 1 mine on adjacent and so on
bool opened[row][col];  //this will keep record of which tile is opened by the player or not  i.e. 1 means opened and 0 means closed
for(int i=0;i<row;i++)
for(int j=0;j<col;j++)
opened[i][j]=0;  //closing all the tiles from start
initializeBoard(board);
placeMines(board,mines);
while(true)
{
displayBoard(board,opened);
playTurn(board,opened);
int win=winCheck (opened,board,mines); 
if(win==1)
{
	system("CLS");
	displayBoard(board,opened);
	Sleep(5000);
	system("CLS");
	cout<<"You won the game !\nCongratulations !";
	exit(0);
}
}
}
void initializeBoard(char board[row][col])  //nitializing board with zero
{
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			board[i][j]='0';
		}
	}
}
void placeMines(char board[row][col],int mines)  //placing mines randomly on the board
{
	int p,h;
	srand(time(0));
	for(int k=0;k<mines;k++)
	{
	p=rand()%row;  //randomly generating boxes
	h=rand()%col;
	if(board[p][h]=='M') //if a box is generated in which a mineis already placed so another box is generated
	{
		k--;
		continue;
	}
	board[p][h]='M';  //placing the mine
	}
	
	for(int i=0;i<row;i++)  //assigning values to boxes with adjacent mines i.e. 1 to box with one mine on adjacent boxes,2 to box with two mines on adjacent and so on.
	{
		for(int j=0;j<col;j++)
		{
			if(board[i][j]=='M') // if a mine appears increase values of all its adjacents by 1 but the adjacent must not be another mine
			{
				if(i!=0 && board[i-1][j]!='M')
				board[i-1][j]+=1;
				if(i!=row-1 && board[i+1][j]!='M')
				board[i+1][j]+=1;
				if(j!=0 && board[i][j-1]!='M')
				board[i][j-1]+=1;
				if(j!=col-1 && board[i][j+1]!='M')
				board[i][j+1]+=1;
				if(i!=0 && j!=0 && board[i-1][j-1]!='M')
				board[i-1][j-1]+=1;
				if(i!=row-1 && j!=col-1 && board[i+1][j+1]!='M')
				board[i+1][j+1]+=1;
				if(i!=0 && j!=col-1 && board[i-1][j+1]!='M')
				board[i-1][j+1]+=1;
				if(i!=row-1 && j!=0 && board[i+1][j-1]!='M')
				board[i+1][j-1]+=1;
				
			}
			
			
		}
	}
}
void displayBoard(char board[row][col] ,bool opened[row][col])  //displaying the board to the user
{
	system("CLS");
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			cout<<"  |";
			if(opened[i][j]==1){
			cout<<setw(3)<<board[i][j];  //if a box is opened display it otherwise show empty box
			}
			else
			cout<<setw(3)<<"-";
		}
		cout<<"  |";
		cout<<endl;
		cout<<"_________________________________________________________"<<endl;
	}
}
void playTurn(char board[row][col] ,bool opened[row][col])
{
	
	static int a=0;
		int open_row,open_col;
	while(true)
	{
		cout<<"\n\nEnter row index of box to open : ";
		cin>>open_row;
		while(open_row<0 || open_row>=row)
		{
			cout<<"\nInvalid\n";
			cout<<"Enter row index of box to open : ";
			cin>>open_row;
		}
		cout<<"Enter col index of box to open : ";
		cin>>open_col;
		while(open_col<0 || open_col>=col)
		{
			cout<<"\nInvalid\n";
			cout<<"Enter col index of box to open : ";
			cin>>open_col;			
		}
		if(opened[open_row][open_col]==1)
		{
		cout<<"\nBox already opened\n";
		continue;
		}
		break;	
	}
	int minecheck=checkMine(board,open_row,open_col);
	if(minecheck==1 && a==0)
	{
		int o,u;
		while(true)
		{
		o=rand()%row;
		u=rand()%col;
		if(board[o][u]=='M')
		continue;
		open_row=o;
		open_col=u;
		minecheck=0;
		break;
		}
		
	}
	if(minecheck==1)
	{
	system("CLS");
	cout<<"You Pressed on a Mine !\nGame Over!";
	exit(0);	
	}	
	openBox(board,opened,open_row,open_col);
	a++;
}
bool checkMine(char board [row][col],int open_row, int open_col)
{
	if ( board [open_row][open_col]=='M')
	return 1;
	else
	return 0;
}
void openBox(char board [row][col], bool opened [row][col],int open_row, int open_col)
{
	
	if(board[open_row][open_col]=='0')
	floodflow(board,opened,open_row,open_col);
	opened[open_row][open_col]=1;
}
void floodflow(char board [row][col], bool opened [row][col],int open_row, int open_col)
{
	int temp1=open_row,temp2=open_col;
	while(true)
	{
		temp1++;
		if(temp1==row-1 || board[temp1][temp2]!='0')
			break;
		if(opened[temp1+1][temp2]==0  && board[temp1+1][temp2]!='M' && temp1<row-1)
			opened[temp1+1][temp2]=1;
		if(opened[temp1][temp2+1]==0 && board[temp1][temp2+1]!='M'&&  temp2<col-1)
			opened[temp1][temp2+1]=1;
		if(opened[temp1-1][temp2]==0 && board[temp1-1][temp2]!='M' &&temp1>0)
			opened[temp1-1][temp2]=1;
		if(opened[temp1][temp2-1]==0 &&  board[temp1][temp2-1]!='M' && temp2>0)
			opened[temp1][temp2-1]=1;
		if(opened[temp1+1][temp2+1]==0 && board[temp1+1][temp2+1]!='M' && temp1<row-1 && temp2<col-1)
			opened[temp1+1][temp2+1]=1;
		if(opened[temp1-1][temp2-1]==0 &&  board[temp1-1][temp2-1]!='M' &&  temp1>0 && temp2>0)
			opened[temp1-1][temp2-1]=1;
		if(opened[temp1-1][temp2+1]==0 && board[temp1-1][temp2+1]!='M' && temp1>0 && temp2<col-1)
			opened[temp1-1][temp2+1]=1;
		if(opened[temp1+1][temp2-1]==0 && board[temp1+1][temp2-1]!='M' && temp1<row-1 && temp2>0)
			opened[temp1+1][temp2-1]=1;	
	}
	temp1=open_row,temp2=open_col;
	while(true)
	{
		temp2++;
		if(temp2==col-1 || board[temp1][temp2]!='0')
			break;
		if(opened[temp1+1][temp2]==0  && board[temp1+1][temp2]!='M' && temp1<row-1)
			opened[temp1+1][temp2]=1;
		if(opened[temp1][temp2+1]==0 && board[temp1][temp2+1]!='M'&&  temp2<col-1)
			opened[temp1][temp2+1]=1;
		if(opened[temp1-1][temp2]==0 && board[temp1-1][temp2]!='M' &&temp1>0)
			opened[temp1-1][temp2]=1;
		if(opened[temp1][temp2-1]==0 &&  board[temp1][temp2-1]!='M' && temp2>0)
			opened[temp1][temp2-1]=1;
		if(opened[temp1+1][temp2+1]==0 && board[temp1+1][temp2+1]!='M' && temp1<row-1 && temp2<col-1)
			opened[temp1+1][temp2+1]=1;
		if(opened[temp1-1][temp2-1]==0 &&  board[temp1-1][temp2-1]!='M' &&  temp1>0 && temp2>0)
			opened[temp1-1][temp2-1]=1;
		if(opened[temp1-1][temp2+1]==0 && board[temp1-1][temp2+1]!='M' && temp1>0 && temp2<col-1)
			opened[temp1-1][temp2+1]=1;
		if(opened[temp1+1][temp2-1]==0 && board[temp1+1][temp2-1]!='M' && temp1<row-1 && temp2>0)
			opened[temp1+1][temp2-1]=1;	
	}
	temp1=open_row,temp2=open_col;
	while(true)
	{
		temp1--;
		if(temp1==0 || board[temp1][temp2]!='0')
			break;
		if(opened[temp1+1][temp2]==0  && board[temp1+1][temp2]!='M' && temp1<row-1)
			opened[temp1+1][temp2]=1;
		if(opened[temp1][temp2+1]==0 && board[temp1][temp2+1]!='M'&&  temp2<col-1)
			opened[temp1][temp2+1]=1;
		if(opened[temp1-1][temp2]==0 && board[temp1-1][temp2]!='M' &&temp1>0)
			opened[temp1-1][temp2]=1;
		if(opened[temp1][temp2-1]==0 &&  board[temp1][temp2-1]!='M' && temp2>0)
			opened[temp1][temp2-1]=1;
		if(opened[temp1+1][temp2+1]==0 && board[temp1+1][temp2+1]!='M' && temp1<row-1 && temp2<col-1)
			opened[temp1+1][temp2+1]=1;
		if(opened[temp1-1][temp2-1]==0 &&  board[temp1-1][temp2-1]!='M' &&  temp1>0 && temp2>0)
			opened[temp1-1][temp2-1]=1;
		if(opened[temp1-1][temp2+1]==0 && board[temp1-1][temp2+1]!='M' && temp1>0 && temp2<col-1)
			opened[temp1-1][temp2+1]=1;
		if(opened[temp1+1][temp2-1]==0 && board[temp1+1][temp2-1]!='M' && temp1<row-1 && temp2>0)
			opened[temp1+1][temp2-1]=1;	
	}
	temp1=open_row,temp2=open_col;
	while(true)
	{
		temp2--;
		if(temp2==0 || board[temp1][temp2]!='0')
			break;
	if(opened[temp1+1][temp2]==0  && board[temp1+1][temp2]!='M' && temp1<row-1)
			opened[temp1+1][temp2]=1;
		if(opened[temp1][temp2+1]==0 && board[temp1][temp2+1]!='M'&&  temp2<col-1)
			opened[temp1][temp2+1]=1;
		if(opened[temp1-1][temp2]==0 && board[temp1-1][temp2]!='M' &&temp1>0)
			opened[temp1-1][temp2]=1;
		if(opened[temp1][temp2-1]==0 &&  board[temp1][temp2-1]!='M' && temp2>0)
			opened[temp1][temp2-1]=1;
		if(opened[temp1+1][temp2+1]==0 && board[temp1+1][temp2+1]!='M' && temp1<row-1 && temp2<col-1)
			opened[temp1+1][temp2+1]=1;
		if(opened[temp1-1][temp2-1]==0 &&  board[temp1-1][temp2-1]!='M' &&  temp1>0 && temp2>0)
			opened[temp1-1][temp2-1]=1;
		if(opened[temp1-1][temp2+1]==0 && board[temp1-1][temp2+1]!='M' && temp1>0 && temp2<col-1)
			opened[temp1-1][temp2+1]=1;
		if(opened[temp1+1][temp2-1]==0 && board[temp1+1][temp2-1]!='M' && temp1<row-1 && temp2>0)
			opened[temp1+1][temp2-1]=1;	
	}
	temp1=open_row,temp2=open_col;
	while(true)
	{
		temp1++;
		temp2++;
		if(temp1==row-1 || temp2==col-1 || board[temp1][temp2]!='0')
			break;
	if(opened[temp1+1][temp2]==0  && board[temp1+1][temp2]!='M' && temp1<row-1)
			opened[temp1+1][temp2]=1;
		if(opened[temp1][temp2+1]==0 && board[temp1][temp2+1]!='M'&&  temp2<col-1)
			opened[temp1][temp2+1]=1;
		if(opened[temp1-1][temp2]==0 && board[temp1-1][temp2]!='M' &&temp1>0)
			opened[temp1-1][temp2]=1;
		if(opened[temp1][temp2-1]==0 &&  board[temp1][temp2-1]!='M' && temp2>0)
			opened[temp1][temp2-1]=1;
		if(opened[temp1+1][temp2+1]==0 && board[temp1+1][temp2+1]!='M' && temp1<row-1 && temp2<col-1)
			opened[temp1+1][temp2+1]=1;
		if(opened[temp1-1][temp2-1]==0 &&  board[temp1-1][temp2-1]!='M' &&  temp1>0 && temp2>0)
			opened[temp1-1][temp2-1]=1;
		if(opened[temp1-1][temp2+1]==0 && board[temp1-1][temp2+1]!='M' && temp1>0 && temp2<col-1)
			opened[temp1-1][temp2+1]=1;
		if(opened[temp1+1][temp2-1]==0 && board[temp1+1][temp2-1]!='M' && temp1<row-1 && temp2>0)
			opened[temp1+1][temp2-1]=1;	
	}
	temp1=open_row,temp2=open_col;
	while(true)
	{
		temp1--;
		temp2--;
		if(temp1==0 || temp2==0 || board[temp1][temp2]!='0')
			break;
if(opened[temp1+1][temp2]==0  && board[temp1+1][temp2]!='M' && temp1<row-1)
			opened[temp1+1][temp2]=1;
		if(opened[temp1][temp2+1]==0 && board[temp1][temp2+1]!='M'&&  temp2<col-1)
			opened[temp1][temp2+1]=1;
		if(opened[temp1-1][temp2]==0 && board[temp1-1][temp2]!='M' &&temp1>0)
			opened[temp1-1][temp2]=1;
		if(opened[temp1][temp2-1]==0 &&  board[temp1][temp2-1]!='M' && temp2>0)
			opened[temp1][temp2-1]=1;
		if(opened[temp1+1][temp2+1]==0 && board[temp1+1][temp2+1]!='M' && temp1<row-1 && temp2<col-1)
			opened[temp1+1][temp2+1]=1;
		if(opened[temp1-1][temp2-1]==0 &&  board[temp1-1][temp2-1]!='M' &&  temp1>0 && temp2>0)
			opened[temp1-1][temp2-1]=1;
		if(opened[temp1-1][temp2+1]==0 && board[temp1-1][temp2+1]!='M' && temp1>0 && temp2<col-1)
			opened[temp1-1][temp2+1]=1;
		if(opened[temp1+1][temp2-1]==0 && board[temp1+1][temp2-1]!='M' && temp1<row-1 && temp2>0)
			opened[temp1+1][temp2-1]=1;	
	}
	temp1=open_row,temp2=open_col;
	while(true)
	{
		temp1++;
		temp2--;
		if(temp1==row-1 || temp2==0 || board[temp1][temp2]!='0')
			break;
	if(opened[temp1+1][temp2]==0  && board[temp1+1][temp2]!='M' && temp1<row-1)
			opened[temp1+1][temp2]=1;
		if(opened[temp1][temp2+1]==0 && board[temp1][temp2+1]!='M'&&  temp2<col-1)
			opened[temp1][temp2+1]=1;
		if(opened[temp1-1][temp2]==0 && board[temp1-1][temp2]!='M' &&temp1>0)
			opened[temp1-1][temp2]=1;
		if(opened[temp1][temp2-1]==0 &&  board[temp1][temp2-1]!='M' && temp2>0)
			opened[temp1][temp2-1]=1;
		if(opened[temp1+1][temp2+1]==0 && board[temp1+1][temp2+1]!='M' && temp1<row-1 && temp2<col-1)
			opened[temp1+1][temp2+1]=1;
		if(opened[temp1-1][temp2-1]==0 &&  board[temp1-1][temp2-1]!='M' &&  temp1>0 && temp2>0)
			opened[temp1-1][temp2-1]=1;
		if(opened[temp1-1][temp2+1]==0 && board[temp1-1][temp2+1]!='M' && temp1>0 && temp2<col-1)
			opened[temp1-1][temp2+1]=1;
		if(opened[temp1+1][temp2-1]==0 && board[temp1+1][temp2-1]!='M' && temp1<row-1 && temp2>0)
			opened[temp1+1][temp2-1]=1;	
	}
	temp1=open_row,temp2=open_col;
	while(true)
	{
		temp1--;
		temp2++;
		if(temp1==0 || temp2==col-1 || board[temp1][temp2]!='0')
			break;
	if(opened[temp1+1][temp2]==0  && board[temp1+1][temp2]!='M' && temp1<row-1)
			opened[temp1+1][temp2]=1;
		if(opened[temp1][temp2+1]==0 && board[temp1][temp2+1]!='M'&&  temp2<col-1)
			opened[temp1][temp2+1]=1;
		if(opened[temp1-1][temp2]==0 && board[temp1-1][temp2]!='M' &&temp1>0)
			opened[temp1-1][temp2]=1;
		if(opened[temp1][temp2-1]==0 &&  board[temp1][temp2-1]!='M' && temp2>0)
			opened[temp1][temp2-1]=1;
		if(opened[temp1+1][temp2+1]==0 && board[temp1+1][temp2+1]!='M' && temp1<row-1 && temp2<col-1)
			opened[temp1+1][temp2+1]=1;
		if(opened[temp1-1][temp2-1]==0 &&  board[temp1-1][temp2-1]!='M' &&  temp1>0 && temp2>0)
			opened[temp1-1][temp2-1]=1;
		if(opened[temp1-1][temp2+1]==0 && board[temp1-1][temp2+1]!='M' && temp1>0 && temp2<col-1)
			opened[temp1-1][temp2+1]=1;
		if(opened[temp1+1][temp2-1]==0 && board[temp1+1][temp2-1]!='M' && temp1<row-1 && temp2>0)
			opened[temp1+1][temp2-1]=1;	
	}
}
bool winCheck(bool opened [row][col],char board [row][col], int mines)
{
	int count=0;
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			if(opened[i][j]==1 && board[i][j]!='M')
			count++;	
		}
	}
	if(count==row*col-mines)
	return 1;
	else 
	return 0;
}


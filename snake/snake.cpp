#include<iostream>
#include<windows.h>
#include<conio.h>

#include <chrono>
using namespace std::chrono;

int height = 28;
int width = 95;

int gameover = 0, counter, gameover2 = 0, choice, counter2, computerc;
int lflag = 0, rflag = 0, uflag = 0, dflag = 0;
int lflag2 = 0, rflag2 = 0, uflag2 = 0, dflag2 = 0;
short fcount;

using namespace std;
class train                     // game functions
{

	int x, y, fx, fy, x2, y2, x3, y3;
	char playername[50], playername2[50];;  // store player name

	struct node               // logic of train by singly linked list
	{
		int nx, ny;
		struct node *next;
		struct node *back;
	};

	struct node *head = NULL;
	struct node *head2 = NULL;  // 2 trains designed

	void gotoxy(int x, int y)    // to locate position of train in 2D
	{
		COORD pos = { x,y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}

	void nameandscore()   // to displays all information during game
	{
		gotoxy(96, 0);
		textcolour(10);
		cout << "MADE BY group";
		textcolour(6);
		gotoxy(96, 2);
		cout << playername << "'s SCORE =" << counter * 100;
		if (choice == 2)  // in case of 2 players
		{
			gotoxy(96, 4);
			cout << playername2 << "'s SCORE =" << counter2 * 100;
			gotoxy(96, 6);
			cout << "Remained Fruit :";
			gotoxy(112, 6);
			cout << "  ";
			gotoxy(112, 6);
			cout << fcount;
		}
		else          // in case of playing with computer
		{
			gotoxy(96, 4);
			cout << "computer's SCORE =" << computerc * 100;
			gotoxy(96, 6);
			cout << "Remained Fruit :";
			gotoxy(112, 6);
			cout << "  ";
			gotoxy(112, 6);
			cout << fcount;
		}
	}



	void textcolour(int k)  // to choose colour
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, k);
	}

public:

	void window()       // to choose colour and design of box
	{
		if (choice == 1)
			textcolour(4);
		else
			textcolour(1);
		for (int i = 0; i <= width; i++)
		{
			gotoxy(i, 0);
			cout << "Û";
			gotoxy(i, height);
			cout << "Û";
		}

		for (int i = 0; i <= height; i++)
		{
			gotoxy(0, i);
			cout << "Û";
			gotoxy(width, i);
			cout << "Û";
		}
	}


	void setup()  // to locate location of train in three cases
	{
		counter = 0;
		gameover = 0;
		window();
		resetflag();     //at first train not move until input is given
		nameandscore();
		head = new node;
		head->nx = width / 2;      // initial location
		head->ny = height / 2;
		head->next = NULL;
		head->back = NULL;
		x = width / 2;
		y = height / 2;
	label1:
		fx = rand() % width;
		if (fx == 0 || fx == width)      // fruit location
			goto label1;
	label2:
		fy = rand() % height;
		if (fy == 0 || fy == height)
			goto label2;
	}

	void setup2()     //to locate second train in case of 2 players
	{
		resetflag2();
		gameover2 = 0;
		counter2 = 0;
		fcount = 25;
		head2 = new node;
		head2->nx = width / 2 + 5;
		head2->ny = height / 2 + 5;
		head2->next = NULL;
		head2->back = NULL;
		x2 = width / 2 + 5;
		y2 = height / 2 + 5;

	}

	void setup3()   //to locate computer's train
	{
		computerc = 0;
		fcount = 25;
		head2 = new node;
		head2->nx = width / 2 + 5;
		head2->ny = height / 2 + 5;
		head2->next = NULL;
		head2->back = NULL;
		x3 = width / 2 + 5;
		y3 = height / 2 + 5;

	}
	void drawlist(struct node *h, int k)  // to draw train and choose colour of train
	{
		textcolour(k);
		struct node *ptr;
		ptr = h;
		while (ptr != NULL)
		{
			gotoxy(ptr->nx, ptr->ny);
			cout << "Û";
			ptr = ptr->next;
		}
	}


	void destroylist(struct node *h)   //to clear train from it's position after moving .
	{
		struct node *ptr;
		ptr = h;
		while (ptr != NULL)
		{
			gotoxy(ptr->nx, ptr->ny);
			cout << " ";
			ptr = ptr->next;
		}
	}



	void draw() // to draw all trains and fruit
	{

		drawlist(head, 2);
		drawlist(head2, 5);
		gotoxy(fx, fy);
		textcolour(4);
		cout << "@";      // fruit's design
		Sleep(70);      //to delay moving to be seen
		destroylist(head);
		destroylist(head2);
	}

	void resetflag()    // start from rest for first train
	{
		uflag = 0;  // up direction
		dflag = 0;   // down direction
		lflag = 0;   // left direction
		rflag = 0;    // right direction
	}

	void resetflag2()  //start from rest for second train.
	{
		uflag2 = 0;
		dflag2 = 0;
		lflag2 = 0;
		rflag2 = 0;
	}

	void play()
	{

		int h;
		char ch;
		if (_kbhit())     // function will not wair to a key is pressed or not
		{

			ch = _getch();   // function basically stands for 'get character'.
			h = ch;

			switch (h)
			{
			case 72:if (dflag != 1) { resetflag(); uflag = 1; }      // when press up arrow  moves up
					break;
			case 80:if (uflag != 1) { resetflag(); dflag = 1; }       // when press down arrow  moves down
					break;
			case 75:if (rflag != 1) { resetflag(); lflag = 1; }        // when press left arrow  moves left
					break;
			case 77:if (lflag != 1) { resetflag(); rflag = 1; }        // when press right arrow  moves right
					break;
					if (choice == 2) {
			case 119:if (dflag2 != 1) { resetflag2(); uflag2 = 1; }   // when press "W"  moves up
					 break;
			case 115:if (uflag2 != 1) { resetflag2(); dflag2 = 1; }    // when press "S"  moves down
					 break;
			case 97:if (rflag2 != 1) { resetflag2(); lflag2 = 1; }      // when press "A"  moves left
					break;
			case 100:if (lflag2 != 1) { resetflag2(); rflag2 = 1; }     // when press "D"  moves right
					 break;
					}
			default:break;
			}
		}
	}

	void play3() {              // in case of playing against computer

		node*h = head2;
		if (h->nx != fx) { x3++; }      //computer's train moves to right until x matching
		if (h->ny != fy) { y3++; }      //computer's train moves to down until y matching

	}


	void box(int m1, int n1, int m2, int n2)   // to display and choose design of welcome box
	{
		for (int i = m1; i <= m2; i++)
		{
			gotoxy(i, n1);
			cout << "//";
			gotoxy(i, n2);
			cout << "//";
		}

		for (int i = n1; i <= n2; i++)
		{
			gotoxy(m1, i);
			cout << "//";
			gotoxy(m2, i);
			cout << "//";
		}
	}

	void welcome()  // welcome design at first of game
	{
		textcolour(5);
		box(width / 2 - width / 4, height / 2 - height / 4, width / 2 + width / 4, height / 2 + height / 4);
		textcolour(10);
		gotoxy(width / 2 - 20, height / 2 - 10);
		cout << "*** WELCOME TO TRAIN GAME BY group *** ";
		textcolour(9);
		gotoxy(width / 2 - 16, height / 2 - 3);
		cout << "Press 1 For Single player \n";   // to play lonely
		gotoxy(width / 2 - 16, height / 2 - 2);
		cout << "Press 2 For Multiplayer \n";     //to 2 players play together
		gotoxy(width / 2 - 16, height / 2 - 1);
		cout << "Press 3 to play computer \n";     // to play against computer
		gotoxy(width / 2 - 16, height / 2);
		cin >> choice;
		system("cls");
	}



	void welcome1()   // box of single player design
	{
		textcolour(5);
		box(width / 2 - width / 4, height / 2 - height / 4, width / 2 + width / 4, height / 2 + height / 4);
		textcolour(6);
		gotoxy(width / 2 - 18, height / 2 - 3);
		cout << "WELCOME TO TRAIN GAME SINGLE PLAYER MODE ";
		textcolour(8);
		gotoxy(width / 2 - 13, height / 2);
		cout << "Enter Your Name : ";
		cin >> playername;
		system("cls");
	}

	void welcome2()    // box of multiplayer player design
	{
		textcolour(5);
		box(width / 2 - width / 4, height / 2 - height / 4, width / 2 + width / 4, height / 2 + height / 4);
		textcolour(6);
		gotoxy(width / 2 - 18, height / 2 - 3);
		cout << "WELCOME TO TRAIN GAME MULTIPLAYER MODE ";
		textcolour(8);
		gotoxy(width / 2 - 13, height / 2);
		cout << "Enter Player1 Name : ";
		gotoxy(width / 2 - 13, height / 2 + 2);
		cout << "Enter Player2 Name : ";
		gotoxy(width / 2 + 7, height / 2);
		cin >> playername;
		gotoxy(width / 2 + 7, height / 2 + 2);
		cin >> playername2;
		system("cls");
	}

	void welcome3()
	{
		textcolour(5);
		box(width / 2 - width / 4, height / 2 - height / 4, width / 2 + width / 4, height / 2 + height / 4);
		textcolour(6);
		gotoxy(width / 2 - 18, height / 2 - 3);
		cout << "WELCOME TO TRAIN GAME against computer ";
		textcolour(8);
		gotoxy(width / 2 - 13, height / 2);
		cout << "Enter Player Name : ";
		gotoxy(width / 2 + 7, height / 2);
		cin >> playername;
		system("cls");
	}


	char end()  // at the end of game to announce results
	{
		char c;
		gotoxy(width / 2 - 5, height / 2 - 4);
		cout << "GAME OVER \n";
		textcolour(5);
		box(width / 2 - width / 4, height / 2 - height / 4, width / 2 + width / 4, height / 2 + height / 4);
		if (choice == 1) {
			textcolour(1);
			gotoxy(width / 2 - 15, height / 2 - 2);
			cout << playername << " You Scored : " << counter * 100;
		}
		else if (choice == 2)
		{
			gotoxy(width / 2 - 15, height / 2);
			cout << playername2 << " You Scored : " << counter2 * 100;
			textcolour(4);
			if (gameover != 0)
			{
				gotoxy(width / 2 - 15, height / 2 + 2);
				cout << playername << " has lost !";
			}
			else
			{
				gotoxy(width / 2 - 15, height / 2 + 2);
				cout << playername2 << " has lost !";
			}
			if (fcount == 0)
			{
				textcolour(4);
				gotoxy(width / 2 - 15, height / 2 + 2);
				if (counter > counter2)
				{
					cout << playername << " has WON !";
				}
				else
				{
					cout << playername2 << " has WON !";
				}
			}
		}
		else
		{
			textcolour(1);
			gotoxy(width / 2 - 15, height / 2 - 2);
			cout << playername << " You Scored : " << counter * 100;
			if (gameover != 0)
			{
				gotoxy(width / 2 - 15, height / 2 + 2);
				cout << playername << " has lost !";
			}
			if (fcount == 0)
			{
				textcolour(4);
				gotoxy(width / 2 - 15, height / 2 + 2);
				if (counter > computerc)
				{
					cout << playername << " has WON !";
				}
				else
				{
					cout << "computer has WON !";
				}
			}
		}
		textcolour(6);
		gotoxy(width / 2 - 15, height / 2 + 4);
		cout << "Want To Play Again ? (Y/N) : ";   // to ask to play again
		cin >> c;
		system("cls");
		return c;

	}



	void run()     // to be in same case until change takes place
	{
		if (uflag == 1)
			y--;
		else if (dflag == 1)
			y++;
		else if (lflag == 1)
			x--;
		else if (rflag == 1)
			x++;


		if (uflag2 == 1)
			y2--;
		else if (dflag2 == 1)
			y2++;
		else if (lflag2 == 1)
			x2--;
		else if (rflag2 == 1)
			x2++;


	}

	void dolist(struct node *h, int pp, int qq)  // to make sure train moves in its direction
	{
		struct node *ptr, *prev;
		ptr = h;
		prev = h;

		while (ptr->next != NULL)
		{
			prev = ptr;
			ptr = ptr->next;
		}
		while (prev != h)
		{
			ptr->nx = prev->nx;
			ptr->ny = prev->ny;
			prev = prev->back;
			ptr = ptr->back;
		}
		ptr->nx = prev->nx;
		ptr->ny = prev->ny;
		prev->nx = pp;
		prev->ny = qq;
	}


	void drawagain2()  // in case of multiplayer if reached boundary ; draw again from opposite boundary
	{
		if (x2 == width)
		{
			x2 = 1;
		}
		if (x2 == 0)
		{
			x2 = width - 1;
		}
		if (y2 == 0)
		{
			y2 = height - 1;
		}
		if (y2 == height)
		{
			y2 = 1;
		}
	}


	void drawagain3()   // in case of playing against computer if reached boundary ; draw again from opposite boundary
	{
		if (x3 == width)
		{
			x3 = 1;
		}
		if (x3 == 0)
		{
			x3 = width - 1;
		}
		if (y3 == 0)
		{
			y3 = height - 1;
		}
		if (y3 == height)
		{
			y3 = 1;
		}
	}
	void generatefruit()  // locate position of fruit randomly in box
	{
	label1:
		fx = rand() % width;
		if (fx == 0 || fx == width)
			goto label1;
	label2:
		fy = rand() % height;
		if (fy == 0 || fy == height)
			goto label2;
	}

	void checkfcount()
	{
		if (fcount == 0)  // in case of train eats 25 fruits stop game
		{
			gameover = 1;
			gameover2 = 1;
		}
	}

	void checkup()
	{
		if (choice == 1)        // in case train hit boundary ends game
		{
			if (x == width || x == 0)
				gameover = 1;
			if (y == height || y == 0)
				gameover = 1;
		}

		struct node *h;      // to make sure train didn't hit itself
		h = head->next;
		while (h != NULL)
		{
			if (x == h->nx&&y == h->ny)
			{
				gameover = 1;
				break;
			}
			h = h->next;
		}

		if (x == fx && y == fy)
		{
			if (choice == 2)  // in case of multiplayer check no. of fruits
			{
				fcount--;
				checkfcount();
			}
			struct node *t, *ptr, *prev;
			t = new node;
			t->next = NULL;
			t->back = NULL;
			ptr = head;
			prev = head;
			while (ptr->next != NULL)    //to increase train size if eat fruit
			{
				ptr = ptr->next;
			}
			ptr->next = t;
			t->back = ptr;
			generatefruit();
			counter++;
			nameandscore();
		}
		dolist(head, x, y);
	}


	void checkup2()
	{
		drawagain2();
		struct node *h;
		h = head2->next;
		while (h != NULL)     //to check train didn't hit itself
		{
			if (x2 == h->nx&&y2 == h->ny)
			{
				gameover2 = 1;
				break;
			}
			h = h->next;
		}

		if (x2 == fx && y2 == fy)
		{
			fcount--;
			checkfcount();
			struct node *t, *ptr, *prev;
			t = new node;
			t->next = NULL;
			t->back = NULL;
			ptr = head2;
			prev = head2;
			while (ptr->next != NULL)    //to increase second train size if eat fruit
			{
				ptr = ptr->next;
			}
			ptr->next = t;
			t->back = ptr;
			generatefruit();
			counter2++;
			nameandscore();
		}
		dolist(head2, x2, y2);
	}

	void checkup3()
	{
		drawagain3();
		if (x3 == fx && y3 == fy)     //to increase computer's train size if eat fruit
		{
			fcount--;
			checkfcount();
			struct node *t, *ptr, *prev;
			t = new node;
			t->next = NULL;
			t->back = NULL;
			ptr = head2;
			prev = head2;
			while (ptr->next != NULL)
			{
				ptr = ptr->next;
			}
			ptr->next = t;
			t->back = ptr;
			generatefruit();
			computerc++;
			nameandscore();
		}
		dolist(head2, x3, y3);
	}
	void game1()
	{
		char ch;
		welcome1();
		do {
			setup();
			window();
			while (!gameover)
			{
				draw();
				play();
				run();
				checkup();
			}
			ch = end();
		} while (ch == 'y' || ch == 'Y');
	}

	void game2()
	{
		char ch;
		welcome2();
		do {

			setup2();
			setup();
			window();
			while (gameover != 1 && gameover2 != 1)
			{
				draw();
				play();
				run();
				checkup();
				checkup2();
			}ch = end();
		} while (ch == 'y' || ch == 'Y');
	}
	void game3()
	{
		char ch;
		welcome3();
		do {

			setup3();
			setup();
			window();
			while (gameover != 1)
			{
				draw();
				play();
				play3();
				run();
				checkup();
				checkup3();
			}ch = end();
		} while (ch == 'y' || ch == 'Y');
	}

};
int main()
{
	auto start = high_resolution_clock::now();

	train s;
	s.welcome();
	if (choice == 1)
	{
		s.game1();
	}
	if (choice == 2)
	{
		s.game2();
	}
	if (choice == 3)
	{
		s.game3();
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(stop - start);

	cout << "time of the program in seconds " << duration.count() << " :second" << endl;


	system("exit");
}

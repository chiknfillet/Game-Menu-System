#include <fstream.h>
#include <iostream.h>
#include <dos.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <ctype.h>

struct userStruct //Struct for the User's all information, a Linked List
{
	int keyNum;
	char username[50];
	char password[50];
	int gamesPlayed[10];
	int mostPlayed;
	int ban;
	int fnum;
	int rnum;
	userStruct *friends[50];
	userStruct *request[50];
	userStruct *next;
};

struct adminStruct
{
	char adminname[50];
	char password[50];
}admin[10];


struct gameStruct
{
	int ban;
	int played;
}gameInfo[5];

// System Global Variables
userStruct *head; 
int usernum, gamenum, adminnum, opt, i;
char in[10];
char gameNames[][20] = {"No Data         ","Hangman         ", "Guess the Number", "Connect Four    ", "Gobblet Gobblers"};

// CONNECT FOUR VARIABLES
const int width = 7, len = 6;
char table[width][len];
char nameCF[2][20];

// GOBBLET GOBBLERS VARIABLES
struct player 
{
    char emblem;
    char name[50];
    int pieces[3];
};
player players[2];
char board[3][3][20];
int turn = 0;

// DATA HANDLING
void load(); 
void unload(); 
void save(); 

// MENUS
void mainMenu(); 
void userMenu(userStruct *log); 
void adminMenu(int adminlogged);

// UNDER USER MENU
void manageFriends(userStruct *log); 
void playGames(userStruct *log); 
void gameStats(userStruct *log);
void manageAccount(userStruct *log);

// UNDER MANAGE ACCOUNT
void changePass(userStruct *log);
void changeName(userStruct *log);

// UNDER ADMIN MENU
void manageGame();
void manageUser();
void adminList();
void adminGameStats();
userStruct *adminSearch();

// UNDER OF MANAGE FRIENDS
userStruct *search(userStruct *log); 
void list(userStruct *log); 
void friendList(userStruct *log); 
void viewFR(userStruct *log); 
void sendFR(userStruct *log); 
void friends(userStruct *log);
void removeFriend(userStruct *log);

// LOGIN REGISTER
void login(); 
void reg(); 

// HANGMAN
void hangman(userStruct *log);
void generateword(char *word, char *category);
void draw(int tries);
void howToPlayHangman();

// GUESS THE NUMBER
void guessNumber(userStruct *log);
void howToPlayGuessNumber();

// CONNECT FOUR
void connectFour(userStruct *log);
void initialize();
void drawBoard();
int input(int turn);
int checker();
void howToPlayConnectFour();

// GOBBLET GOBBLERS
void gobblet(userStruct *log);
int inputGetter(const char *message);
void initialization(userStruct *log);
void gameBoard();
int gameplay(int turn);
int movePiece(int turn);
int movablePiece(int turn);
void turnChecker(int turn);
void printWinner(char winner);
char winCondition();
char surrender(int turn);
char *getSubStr(const char* line, int start, int len);
void howToPlayGobbletGobllers();

void upperCase(char* word); 

int main() // Main Function
{
	srand((time(0)));
	system("CLS");
	load();
	mainMenu();
	return 0;
}

void upperCase(char* word)
{
	int len = strlen(word);
	for (i = 0; i < len; i++)
	{
		word[i] = toupper(word[i]);
	}
	return;
}

// MENU START
void mainMenu() // The Starting Menu
{
	while(1)
	{
		save();
		system("CLS");
		cout<<"\nWelcome to Press Start"<< endl;
		cout<<"1. Login"<< endl;
		cout<<"2. Register"<< endl;
		cout<<"3. Exit"<< endl;
		opt = inputGetter("Input: ");
		switch(opt)
		{
			case 1:
				login();
				break;
			case 2:
				reg();
				break;
			case 3:
				save();
				unload();
				cout<<endl<<"Exiting Press Start..."<<endl;
				exit(0);
				break;
			default:
				cout<<endl<<"Invalid Input"<<endl;
				system("pause");
				break;
		}
	}
}

void adminMenu(int adminlogged)
{
	while(1)
	{
		system("CLS");
		cout<<"\nWelcome "<<admin[adminlogged].adminname<<endl;
		cout<<"1. Manage Accounts"<<endl;
		cout<<"2. Manage Games"<<endl;
		cout<<"3. Back"<<endl;
		opt = inputGetter("Input: ");
		switch(opt)
		{
			case 1: 
				manageUser();
				break;
			case 2:
				manageGame();
				break;
			case 3:
				return;
				break;
			default:
				cout<<"\nInvalid Input"<<endl;
				system("pause");
				break;
		}
	}
}

void manageUser()
{
	while(1)
	{
		system("CLS");
		cout<<"\nManage Users"<<endl;
		cout<<"1. List of Users"<<endl;
		cout<<"2. Search User"<<endl;
		cout<<"3. Restrict User"<<endl;
		cout<<"4. Unrestrict User"<<endl;
		cout<<"5. Back"<<endl;
		opt = inputGetter("Input: ");
		userStruct *search;
		system("CLS");
		switch(opt)
		{
			case 1: 
				adminList();
				break;
			case 2:
				search = adminSearch();
				break;
			case 3:
				search = adminSearch();
				if (search != NULL)
				{
					if (search->ban == 0 )
					{
						search->ban = 1;
						cout<<endl<<search->username<<" is Successfully Restricted"<<endl;
					}
					else 
					{
						cout<<endl<<search->username<<" is Already Restricted"<<endl;
					}
				}
				break;
			case 4:
				search = adminSearch();
				if (search != NULL)
				{
					if (search->ban == 1)
					{
						search->ban = 0;
						cout<<endl<<search->username<<" is Successfully Unrestricted"<<endl;
					}
					else 
					{
						cout<<endl<<search->username<<" is Already Unrestricted"<<endl;
					}
				}
				break;
			case 5:
				return;
				break;
			default:
				cout<<"\nInvalid Input"<<endl;
				break;
		}
		cout<<endl;
		system("pause");
	}
}

void manageGame()
{
	while(1)
	{
		adminGameStats();
		cout<<"\n1. Restict Game"<<endl;
		cout<<"2. Unrestrict Game"<<endl;
		cout<<"3. Back"<<endl;
		opt = inputGetter("Input: ");
		if (opt == 1 || opt == 2)
		{
			system("CLS");
			cout<<"\nGames"<<endl;
			cout<<"1. Hangman"<<endl;
			cout<<"2. Guess the Number"<<endl;
			cout<<"3. Connect Four"<<endl;
			cout<<"4. Hangman"<<endl<<endl;
			cout<<"Input Game's Number: ";
			cin>>in;
			i = atoi(in);
			if (i > 0 && i < 5)
				opt = opt;
			else 
				opt = 4;
		}
		switch(opt)
		{
			case 1:
				gameInfo[i - 1].ban = 1;
				cout<<"\nSuccessfully Restricted "<<gameNames[i]<<endl;
				break;
			case 2:
				gameInfo[i - 1].ban = 0;
				cout<<"\nSuccessfully Unrestricted "<<gameNames[i]<<endl;
				break;
			case 3:
				return;
				break;
			default:
				cout<<"Invalid Input"<<endl;
				break;
		}
		cout<<endl;
		system("pause");
	}
}

void userMenu(userStruct *log) // Menu for the Users
{
	while(1)
	{
		save();
		system("CLS");
		cout<<"\nHello "<<log->username<<endl;
		cout<<"1. Play Mini Games"<<endl;
		cout<<"2. Game Stats"<<endl;
		cout<<"3. Manage Friends"<<endl;
		cout<<"4. Manage Account"<<endl;
		cout<<"5. Logout"<<endl;
		opt = inputGetter("Input: ");
		switch(opt)
		{
			case 1:
				playGames(log);
				break;
			case 2:
				gameStats(log);
				break;
			case 3:
				manageFriends(log);
				break;
			case 4: 
				manageAccount(log);
				break;
			case 5:
				return;
				break;
			default:
				cout<<endl<<"Invalid Input"<<endl;
				system("pause");
				break;
		}
	}
}

void manageAccount(userStruct *log)
{
	while(1)
	{
		system("CLS");
		cout<<"\nManage Account"<<endl;
		cout<<"1. Change Username"<<endl;
		cout<<"2. Change Password"<<endl;
		cout<<"3. Back"<<endl;
		opt = inputGetter("Input: ");
		switch(opt)
		{
			case 1:
				changeName(log);
				break;
			case 2:
				changePass(log);
				break;
			case 3:
				return;
				break;
			default:
				cout<<"\nInvalid Input";
				break;
		}
		cout<<"\n\n";
		system("pause");
	}
}

void changeName(userStruct *log)
{
	char temp[20], confirm[20];
	system("CLS");
	cout<<"\nChange Username"<<endl;
	cout<<"\nInput New Username: ";
	gets(temp);
	for (i = 0; i < strlen(temp); i++)
	{
		if (temp[i] == ' ')
		{
			cout<<"Username Cannot Contain Spaces"<<endl;
			return;
		}
	}
	for (userStruct *find = head; find != NULL; find = find->next)
	{
		if (strcmp(find->username, temp) == 0)
		{
			cout<<"\nUsername Unavailable";
			return;
		}	
	}
	cout<<"\nConfirm New Username: ";
	gets(confirm);
	if(strcmp(temp, confirm) == 0)
	{
		cout<<"\nUsername Changed Successfully";
		strcpy(log->username, temp);
	}
	else
	{
		cout<<"\nUsername Does Not Match";
	}
	return;
}

void changePass(userStruct *log)
{
	char tempP[20], confirmP[20];
	system("CLS");
	cout<<"\nChange Password"<<endl;
	cout<<"\nEnter Current Password: ";
	gets(tempP);
	if(strcmp(tempP, log->password) != 0)
	{
		cout<<"\nPassword Does Not Match";
		return;
	}
	cout<<"\nInput New Password: ";
	gets(tempP);
	cout<<"\nConfirm New Password: ";
	gets(confirmP);
	if(strcmp(tempP, confirmP) == 0)
	{
		cout<<"\nPassword Changed Successfully";
		strcpy(log->password, tempP);
	}
	else
	{
		cout<<"\nPassword Does Not Match";
	}
	return;
}

void gameStats(userStruct *log)
{
	system("CLS");
	cout<<"\n====================================GAME STATS================================="<<endl;
	cout<<"Games\t\t\t\tGames Played"<<endl;
	cout<<"==============================================================================="<<endl;
	for (i = 0; i < gamenum; i++)
	{
		cout<<gameNames[i+1]<<"\t\t"<<log->gamesPlayed[i]<<"\t\t\t";
		if (log->mostPlayed == i + 1)
			cout<<"Most PLayed Game";
		cout<<endl;
	}
	cout<<"==============================================================================="<<endl;
	cout<<endl;
	system("pause");
}

void adminGameStats()
{
	system("CLS");
	cout<<"\nGame Stats"<<endl<<endl;
	cout<<"Games\t\t\tTotal Plays\t\tRestriction Status"<<endl;
	for (i = 0; i < gamenum; i++)
	{
		cout<<gameNames[i+1]<<"\t"<<gameInfo[i].played<<"\t\t\t";
		if (gameInfo[i].ban == 0)
			cout<<"Not Restricted";
		else
			cout<<"Restricted";
		cout<<endl;
	}
}

void manageFriends(userStruct *log) //Menu for Managing Friends
{
	while(1)
	{
		system("CLS");
		cout<<"\nManage Friends"<<endl;
		cout<<"1. My Friend"<<endl;
		cout<<"2. Friend Requests"<<endl;
		cout<<"3. List of Users"<<endl;
		cout<<"4. Search Users"<<endl;
		cout<<"5. Back"<<endl;
		opt = inputGetter("Input: ");
		switch(opt)
		{
			case 1:
				friends(log);
				break;
			case 2:
				viewFR(log);
				break;
			case 3:
				list(log);
				break;
			case 4:
				search(log);
				system("pause");
				break;
			case 5:
				return;
				break;
			default:
				cout<<"Invalid Input"<<endl;
				system("pause");
				break;
		}
	}
}

void friends(userStruct *log)
{
	while(1)
	{
		system("CLS");
		cout<<"\nFriends"<<endl;
		friendList(log);
		cout<<"1. Add Friend"<<endl;
		cout<<"2. Remove Friend"<<endl;
		cout<<"3. Back"<<endl;
		opt = inputGetter("Input: ");
		switch(opt)
		{
			case 1:
				sendFR(log);
				break;
			case 2:
				removeFriend(log);
				break;
			case 3:
				return;
				break;
			default:
				cout<<"Invalid Input"<<endl;
				system("pause");
				break;
		}
	}
}

void playGames(userStruct *log)
{
	while(1)
	{
		save();
		system("CLS");
		cout<<"\nPress Start Games"<<endl;
		cout<<"1. Hangman "; if (gameInfo[0].ban == 1) cout << "(Restricted)"; cout << endl;
		cout<<"2. Guess the Number "; if (gameInfo[1].ban == 1) cout << "(Restricted)"; cout << endl;
		cout<<"3. Connect Four "; if (gameInfo[2].ban == 1) cout << "(Restricted)"; cout << endl;
		cout<<"4. Gobblet Gobblers "; if (gameInfo[3].ban == 1) cout << "(Restricted)"; cout << endl;
		cout<<"5. Back"<<endl; 
		opt = inputGetter("Input: ");
		if (opt > 0 && opt < 5)
		{
			log->gamesPlayed[opt - 1]++;
			gameInfo[opt - 1].played++;
		}
		switch(opt)
		{
			case 1:
				if (gameInfo[0].ban == 1)
				{
					cout << "Hangman is Restricted" << endl;
					break;	
				}
				hangman(log);
				break;
			case 2:
				if (gameInfo[1].ban == 1)
				{
					cout << "Guess the Number is Restricted" << endl;
					break;	
				}
				guessNumber(log);
				break;
			case 3:
				if (gameInfo[2].ban == 1)
				{
					cout << "Connect Four is Restricted" << endl;
					break;	
				}
				connectFour(log);
				break;
			case 4:
				if (gameInfo[3].ban == 1)
				{
					cout << "Gobblet Gobblers is Restricted" << endl;
					break;	
				}
				gobblet(log);
				break;
			case 5:
				return;
				break;
			default:
				cout<<"Invalid Input";
				break;
		}
		system("pause");
	}

}

void login() // Login Funciton
{
	cin.ignore();
	int attempt = 0, key;
	system("CLS");
	char tempU[50], tempP[50];
	cout<<"\nEnter username: ";
	gets(tempU);
	// Loop for the admin
	for (i = 0; i < adminnum; i++)
	{
		if (strcmp(admin[i].adminname, tempU) == 0)
		while (1)
		{
			cout<<"\nEnter password: ";
			gets(tempP);
			if (strcmp(tempP, admin[i].password) == 0)
			{
				cout<<"\nLogin Successful"<<endl;
				adminMenu(i);
				return;
			}
			else
			{
				cout<<"\nIncorrect password"<<endl;
				attempt++;	
			}
			if (attempt == 3)
			{
				cout<<"\nToo Many Attempts"<<endl<<endl;;
				system("pause");
				return;	
			}
		}

	}
	// Loop for the users
	for (userStruct *find = head; find != NULL; find = find->next)
	{
		if (strcmp(tempU, find->username) == 0)
		{
			if (find->ban == 1)
			{
				cout<<"\nAccount Restricted"<<endl;
				system("pause");
				return;
			}
			while (attempt < 3)
			{
				cout<<"\nEnter password: ";
				gets(tempP);
				
				if (strcmp(tempP, find->password) == 0)
				{
					cout<<"\nLogin Successful"<<endl;
					userMenu(find);
					return;
				}
				else
				{
					cout<<"\nIncorrect password"<<endl;
					attempt++;	
				}
			}
			cout<<"\nToo Many Attempts, Account Restricted"<<endl;
			find->ban = 1;
			system("pause");
			return;	
		}
	} 
	cout<<"\nInvalid Username"<<endl;
	system("pause");
}

void reg() // Register Funciton
{
	cin.ignore();
	system("CLS");
	char tempU[50], tempP[50], confirmP[50];
	cout<<"\nEnter Username: ";
	gets(tempU);
	// Check for Blank Spaces in Input
	for (i = 0; i < strlen(tempU); i++)
	{
		if (tempU[i] == ' ')
		{
			cout<<"\nUsername Cannot Contain Spaces"<<endl;
			system("pause");
			return;
		}
	}
	// Check for Matching Username among admins
	for (i = 0; i < adminnum; i++)
	{
		if (strcmp(admin[i].adminname, tempU) == 0)
		{
			cout<<"\nUsername Unavailable"<<endl;
			system("pause");
			return;
		}
	}
		// Check for Matching Username among users
	for (userStruct *find = head; find != NULL; find = find->next)
	{
		if (strcmp(find->username, tempU) == 0)
		{
			cout<<"\nUsername Unavailable"<<endl;
			system("pause");
			return;
		}	
	}
	cout<<"\nEnter Password: ";
	gets(tempP);
	// Confirm the Password
	for (i = 0; i < 3; i++)
	{
		cout<<"\nConfirm Password: ";
		gets(confirmP);
		if(strcmp(tempP, confirmP) == 0)
			break;
		cout<<"\nPassword Does Not Match"<<endl;
		if (i == 2)
		{
			cout<<"\nToo Many Attempts\n\n";
			system("pause");
			return;
		}
	}
	// Create a node for the new user and input all info
	userStruct *temp = new userStruct;
    if (temp == NULL)
    {
        cout<<"Memory Leak";
        system("pause");
	}	
	else
	{
		strcpy(temp->username, tempU);
	    strcpy(temp->password, tempP);
		temp->ban = 0;
		temp->keyNum = usernum;
		temp->fnum = 0;
		temp->rnum = 0;
		temp->mostPlayed = 0;
		for (i = 0; i < gamenum; i++)
		{
			temp->gamesPlayed[i] = 0;
		}
	    	
	    userStruct	*last = head;
		while (last->next != NULL) 
		{
		    last = last->next;
		}
		last->next = temp;
		temp->next = NULL;
	    usernum++;
		cout<<"\nUser successfully added!"<<endl;
	}
	save();
	cout<<endl;
	system("pause");	
	return;
}

// MENU END

// DATA START
void load() //Get all the fies from storage in a separate file and laod into a linked list
{
	// open files
	ifstream load("C:\\TURBOC3\\BIN\\DATABASE.TXT");
	ifstream friends("C:\\TURBOC3\\BIN\\friends.txt");
	ifstream request("C:\\TURBOC3\\BIN\\request.txt");
	ifstream games("C:\\TURBOC3\\BIN\\games.txt");
	ifstream admins("C:\\TURBOC3\\BIN\\admin.txt");
	if (!load)
    {
		cout << "Failed to Open Database\n";
		system("pause");
		return;
    }
    else if(!friends)
    {
    	cout << "Failed to Open Friends\n";
		system("pause");
    	return;
	}
	else if(!request)
    {
    	cout << "Failed to Open Requests\n";
		system("pause");
    	return;
	}
	else if(!games)
    {
    	cout << "Failed to Open Games\n";
		system("pause");
    	return;
	}
	else if(!admins)
    {
    	cout << "Failed to Open Admin\n";
		system("pause");
    	return;
	}
    else
    {
	    // Get the numbers of users, games, admins
		load >> usernum;
		games >> gamenum;
		admins >> adminnum;
		// Loop to get he admin username and password
		for (i = 0; i < adminnum; i++)
		{
			admins >> admin[i].adminname;
			admins >> admin[i].password;
		}
		// Loop to get the ban/ restriction status of games
		for (i = 0; i < gamenum; i++)
		{	
			games >> gameInfo[i].ban;
		}
		// Loop to get the user's info
		for (i = 0; i < usernum; i++)
		{
			// Create new node for the linked list of users
			userStruct *temp = new userStruct;
			// Check for memory leak
			if (temp == NULL)
	        {
	           	cout<<"Memory Leak";
	           	system("pause");
	           	break;
			}	
			
	        load >> temp->username; 
	        load >> temp->password;
			load >> temp->ban;
			load >> temp->fnum;
			load >> temp->rnum;
			temp->keyNum = i; 
			// Loop to get the count for games played for each game
			for (int j = 0; j < gamenum; j++)
			{
				games >> temp->gamesPlayed[j];
			}
			games >> temp->mostPlayed;
				
			// Set the head if the this is the first node of the linked list
			if (head == NULL)
			{
		        head = temp;
		        continue;
		   	}
		    
		    // Get to the last node of the linked list to attached the present node
	    	userStruct	*last = head;
		    while (last->next != NULL) 
			{
		        last = last->next;
		    }
			last->next = temp;
			temp->next = NULL;
		}
		int fr;
		// Loop to assign the pointers based on the key number in the database
		for (userStruct *temp = head; temp != NULL; temp = temp->next)
	    {
	    	// Loop for the friend list
			for (i = 0; i < temp->fnum; i++)
		    {
	        	friends >> fr;
	        	for (userStruct *frie = head; frie != NULL; frie = frie->next)
	        	{
	        		if(fr == frie->keyNum)
	        		{
	        			temp->friends[i] = frie;
					}
				}
			}
			// Loop for the friend requests
			for (i = 0; i < temp->rnum; i++)
			{
		       	request >> fr;
		       	for (userStruct *frie = head; frie != NULL; frie = frie->next)
		       	{
		        	if(fr == frie->keyNum)
		       		{
		       			temp->request[i] = frie;
					}
				}
			}
		} 
    }
    // Loop to get the total games played for each game
    for (i = 0; i < gamenum; i++)
    {
    	games >> gameInfo[i].played;
	}
    admins.close();
    games.close();
    request.close();
    load.close();
    friends.close();
    return;
}	

void save()
{
	ofstream save("C:\\TURBOC3\\BIN\\DATABASE.TXT");
	ofstream friends("C:\\TURBOC3\\BIN\\friends.txt");
	ofstream request("C:\\TURBOC3\\BIN\\request.txt");
	ofstream games("C:\\TURBOC3\\BIN\\games.txt");
	
	games << gamenum << endl;
	save << usernum << endl;

	// Loop to save the ban/ restriction status of games
	for (i = 0; i < gamenum; i++)
	{
		games << gameInfo[i].ban<<"\t";
		if (i == gamenum - 1)
			games << endl;
	}
	
	// Save the users' info
	userStruct *saver = head;
	for (i = 0; i < usernum; i++)
	{
		save << saver->username<<"\t"; 
	    save << saver->password<<"\t"; 
		save << saver->ban<<"\t"; 
		save << saver->fnum<<"\t"; 
		save << saver->rnum<<endl; 
		// Loop to save the games played for each game
		for (int j = 0; j < gamenum; j++)
		{
			games << saver->gamesPlayed[j]<<"\t";	
			// Check which game has the most played among all of the games
			if (saver->gamesPlayed[j] > saver->gamesPlayed[saver->mostPlayed - 1])
			{
				saver->mostPlayed = j + 1;
			}		
		}
		games << saver->mostPlayed;
		games << endl;
		saver = saver->next; // Set the pointer for the next user to be saved
	}
	// Save the total number of played for each game
	for (i = 0; i < gamenum; i++)
	{
		games << gameInfo[i].played<<"\t";
	}
	int fr;
	// Loop to save the key numbers based on the pointers
	for (userStruct *temp = head; temp != NULL; temp = temp->next)
    {
    	// Loop for the friend lsit
		for (i = 0; i < temp->fnum; i++)
		{
			friends << temp->friends[i]->keyNum<<"\t";
		}
		friends << endl;
		// Loop for the friend request list
		if (temp->rnum != 0)
		{
			for (i = 0; i < temp->rnum; i++)
			{
				request << temp->request[i]->keyNum<<"\t";
			}
			request << endl;	
		}
	} 
	games.close();
	request.close();
    save.close();
    friends.close();
	return;
}

void unload() // Free the memory
{
	userStruct* current = head;
    while (current != NULL)
    {
        userStruct* temp = current;
        current = current->next;
        delete temp;
    }
    head = NULL;
    return;
}

// DATA END

// FRIENDS START
userStruct *search(userStruct *log) // Search a user with the username and return the pointer for the searched user
{
	cin.ignore();
	char temp[50];
	cout<<"\nEnter Username: ";
	gets(temp);
	for (userStruct *ptr = head; ptr != NULL; ptr = ptr->next)
	{
		if (strcmp(temp, ptr->username) == 0)
		{
			cout<<"\nUsername\tMost Played Games\tFriends Status"<<endl;
			cout<<ptr->username<<"\t\t"<<gameNames[ptr->mostPlayed]<<"\t";
			if (strcmp(ptr->username, log->username) == 0)
			{
				cout<<"Your Account";
			}
			for (i = 0; i < log->fnum; i++) // Lopp to check if the user is in the logged user's friends list
			{
				if(strcmp(log->friends[i]->username, ptr->username) == 0)
				{
					cout<<"Friends";
					break;
				}
			}
			for (i = 0; i < log->rnum; i++) // Lopp to check if the user is in the logged user's friend request list
			{
				if(strcmp(log->request[i]->username, ptr->username) == 0)
				{
					cout<<"Pending Friend Request";
					break;
				}
			}
			for (i = 0; i < ptr->rnum; i++) // Lopp to check if the logged user is in the user's friend request list
			{
				if (strcmp(ptr->request[i]->username, log->username) == 0)
				{
					cout<<"Outgoing Friend Request";
					break;
				}
			}			
			cout<<endl<<endl;
			return ptr;
		}
	}
	cout<<"\nUser Not Found\n\n";
	return NULL;
}

userStruct *adminSearch() // Search a user with the username and return the pointer for the searched user
{
	char temp[50];
	cout<<"\nEnter Username: ";
	gets(temp);
	userStruct *ptr = NULL;
	for (ptr = head; ptr != NULL; ptr = ptr->next)
	{
		if (strcmp(temp, ptr->username) == 0)
		{
			cout<<"\nUsername\tPassword\tRestriction\tMost Played Game\tFriends"<<endl;
			cout<<ptr->username<<"\t\t"<<ptr->password<<"\t\t";
			if (ptr->ban == 0)
				cout<<"False";
			else
				cout<<"True";
			cout<<"\t\t"<<gameNames[ptr->mostPlayed]<<"\t"<<ptr->fnum;
			cout<<endl;
			return ptr;
		}
	}
	cout<<endl<<"User Not Found"<<endl;
	return NULL;
}

void list(userStruct *log) // Show the List of all users
{
	userStruct* prev[100];  
    int prevIndex = -1;  
	userStruct *current = head;
	userStruct *next = NULL;
	int page = 1;
	int totalPage = usernum / 10;
	if (usernum % 10 != 0)
		totalPage++;
	while(1)
	{
		int showing = 0;
		system("CLS");
		cout<<"\n=================================VIEWING USERS================================="<<endl;
		cout<<"Username\t\tMost Played Game\t\tFriend Status"<<endl;
		cout<<"==============================================================================="<<endl;
		for (userStruct *ptr = current; ptr != NULL && showing < 10; ptr = ptr->next)
		{
			cout<<ptr->username<<"\t\t\t"<<gameNames[ptr->mostPlayed]<<"\t\t";
			if (strcmp(ptr->username, log->username) == 0)
			{
				cout<<"Your Account";
			}
			for (i = 0; i < log->fnum; i++) // Lopp to check if the user is in the logged user's friends list
			{
				if(strcmp(log->friends[i]->username, ptr->username) == 0)
				{
					cout<<"Friends";
					break;
				}
			}
			for (i = 0; i < log->rnum; i++) // Lopp to check if the user is in the logged user's friend request list
			{
				if(strcmp(log->request[i]->username, ptr->username) == 0)
				{
					cout<<"Pending Friend Request";
					break;
				}
			}
			for (i = 0; i < ptr->rnum; i++) // Lopp to check if the logged user is in the user's friend request list
			{
				if (strcmp(ptr->request[i]->username, log->username) == 0)
				{
					cout<<"Outgoing Friend Request";
					break;
				}
			}
			showing++;
			cout<<endl;
			next = ptr->next;
		}
		cout<<"==============================================================================="<<endl;
		cout<<"Showing Page "<<page<<" / "<<totalPage<<endl;
		cout<<"1. Next Page"<<endl;
		cout<<"2. Previous Page"<<endl;
		cout<<"3. Back"<<endl;
		opt = inputGetter("Input: ");		
		switch(opt)
		{
			case 1:
				if (page != totalPage)
				{
					prev[++prevIndex] = current; 
					current = next;
					page++;
				}
				else 
				{
					cout<<"\nYou Have Reached the End\n\n";
					system("pause");
				}
				break;
			case 2:
				if (page != 1)
				{
					current = prev[prevIndex--];
					page--;
			
				}
				else 
				{
					cout<<"\nYou Have Reached the Start\n\n";
					system("pause");
				}
				break;
			case 3:
				return;
				break;
			default:
				cout<<"Invlid Input"<<endl;
				system("pause");
				break;
		}
	}
}

void adminList() 
{
	userStruct* prev[100]; 
    int prevIndex = -1;   
	userStruct *current = head;
	userStruct *next = NULL;
	int page = 1;
	int totalPage = usernum / 10;
	if (usernum % 10 != 0)
		totalPage++;
	while(1)
	{
		system("CLS");
		cout<<"\n============================VIEWING USER'S DETAILS============================="<<endl;
		cout<<"Username\tPassword\tRestriction\tMost Played Game\tFriends"<<endl;
		cout<<"==============================================================================="<<endl;
		int showing = 0;
		
		for (userStruct *ptr = current; ptr != NULL && showing < 10; ptr = ptr->next)
		{
			cout<<ptr->username<<"\t\t"<<ptr->password<<"\t\t";
			if (ptr->ban == 0)
				cout<<"False";
			else
				cout<<"True";
			cout<<"\t\t"<<gameNames[ptr->mostPlayed]<<"\t"<<ptr->fnum;
			cout<<endl;
			showing++;
			next = ptr->next;
		}
		cout<<"==============================================================================="<<endl;
		cout<<"Showing Page "<<page<<" / "<<totalPage<<endl;
		cout<<"1. Next Page"<<endl;
		cout<<"2. Previous Page"<<endl;
		cout<<"3. Back"<<endl;
		opt = inputGetter("Input: ");		
		switch(opt)
		{
			case 1:
				if (page != totalPage)
				{
					prev[++prevIndex] = current; 
					current = next;
					page++;
				}
				else 
				{
					cout<<"\nYou Have Reached the End\n\n";
					system("pause");
				}
				break;
			case 2:
				if (page != 1)
				{
					current = prev[prevIndex--];
					page--;
			
				}
				else 
				{
					cout<<"\nYou Have Reached the Start\n\n";
					system("pause");
				}
				break;
			case 3:
				return;
				break;
			default:
				cout<<"Invlid Input"<<endl;
				system("pause");
				break;
		}
	}
}

void friendList(userStruct *log) //Show the Friend List of the logged User
{
	system("CLS");
	if (log->fnum == 0)
	{
		cout<<"\nFind Friends"<<endl;
	}
	else
	{
		cout<<"\nFriend List: "<<"\n\n";
		cout<<"Username\t\tMost Played Game"<<endl; 
		for (i = 0; i < log->fnum; i++)
		{
			cout<<log->friends[i]->username<<"\t\t\t"<<gameNames[log->friends[i]->mostPlayed]<<endl;
		}
	}
	cout<<"\n";
	return;
}

void viewFR(userStruct *log) //Show all Friend Requests of the logged User
{
	while(1)
	{
		system("CLS");
		i = 0;
		char search[50];
		if (log->request[i] == NULL)
		{
			cout<<"\nNo Pending Requests"<<endl;
		}
		else
		{
			cout<<"\nUsername"<<endl;
			while (log->request[i] != NULL)
			{
				cout<<log->request[i]->username<<endl;
				i++;
			}
		}
		cout<<"\n1. Accept Friend Request"<<endl;
		cout<<"2. Remove Friend Request"<<endl;
		cout<<"3. Exit"<<endl;
		opt = inputGetter("Input: ");
		if (opt == 1 || opt == 2)
		{
			if (log->rnum == 0 && opt != 3)
			{
				cout<<"\nNo Pending Requests"<<endl;
				system("pause");
				continue;
			}
			cin.ignore();
			cout<<"Input Username:";
			gets(search);
		}
		switch(opt)
		{
			case 1:
				// Loop to check if the searched is in the logged friend request
				for (i = 0; log->request[i] != NULL; i++)
				{
					// Condition that check for the matching username for the logged and searched user
					if (strcmp(search, log->request[i]->username) == 0)
					{
						// Add the searched into the logged friend list
						cout<<endl<<log->request[i]->username<<" Added Successfully"<<"\n\n";	
						int position = log->request[i]->fnum++;
						log->request[i]->friends[position] = log;
						log->friends[log->fnum] = log->request[i];
						log->request[i] = NULL;
						log->fnum++;
						log->rnum--;
						// Loop to rearrange the logged friend request after accepting the friend request
						for (int k = i; log->request[k + 1] != NULL; k++)
						{
							log->request[k] = log->request[k+1]; 
							log->request[k+1] = NULL;  
						}
						system("pause");
						break;
					}
					if (i == log->rnum - 1)
					{
						cout<<"User Not Found"<<endl;
						system("pause");
					}
				}
				break;
			case 2:
				// Loop to check if the searched is in the logged friend request list
				for (i = 0; log->request[i] != NULL; i++)
				{
					// Condition that check the searched and logged user
					if (strcmp(search, log->request[i]->username) == 0)
					{
						cout<<endl<<log->request[i]->username<<" Removed Successfully"<<"\n\n";
						log->request[i] = NULL;
						// Rearrange the logged friend request list after removing
						for (int k = i; log->request[k + 1] != NULL; k++)
						{
							log->request[k] = log->request[k + 1]; 
							log->request[k + 1] = NULL; 
						}
						log->rnum--;
						system("pause");
						break;
					}
					if (i == log->rnum - 1)
					{
						cout<<"\nUser Not Found"<<endl;
						system("pause");
					}
				}
				break;
			case 3:
				return;
				break;
			default:
				cout<<"Invalid Input"<<endl;
				break;
		}
	}
	save();
}

void sendFR(userStruct *log) // Send a Friend Request to a User
{
	userStruct *temp = search(log);
	if (temp != NULL)
	{
		// Check if the searched user is the one that is logged in
		if (strcmp(log->username, temp->username) == 0)
		{
			cout<<"You Can't Send Friend Request to Yourself"<<endl<<endl;
			system("pause");
			return;
		}
		
		// Loop to check if searched user is already in friend list
		for (i = 0; i < temp->fnum + 1; i++)
		{
			if (strcmp(log->friends[i]->username, temp->username) == 0)
			{
				cout<<temp->username<<" is Already in Friend List"<<endl<<endl;
				system("pause");
				return;				
			}
		}
		// Loop to find the empty index in the searched friend request
		for (i = 0; i < temp->rnum + 1; i++)
		{
			// Condition to check if a friend request is already sent to searched user
			if (strcmp(temp->request[i]->username, log->username) == 0)
			{
				cout<<"Pending Friend Request to "<<temp->username<<endl<<endl;
				break;
			}
			// Send the friend request
			if (temp->request[i] == NULL)
			{
				temp->request[i] = log;	
				temp->rnum++;
				break;
			}	
		}
	}
	system("pause");
	return;
}

void removeFriend(userStruct* log)
{
	userStruct *temp = search(log);
	if (temp == NULL)
	{
		system("pause");
		return;
	}
	
	for (i = 0; log->friends[i] != NULL; i++)
	{
		if (strcmp(log->friends[i]->username, temp->username) == 0)
		{
			// Remove Friend From the Frien's Account
			for (int x = 0; temp->friends[x] != NULL; x++)
			{
				// Condition that check to match the logged user in the friend's friend list
				if(strcmp(temp->friends[x]->username, log->username) == 0)
				{
					// remove the user from the friends's fried list
					temp->friends[x] = NULL;
					// loop to rearrange the frien's friend list
					for (int k = x; k < temp->fnum + 1; k++)
					{
						temp->friends[k] =  temp->friends[k + 1];
						temp->friends[k + 1] = NULL; 
					}
					temp->fnum--;
				}
			}
			
			// Remove Friend from the Logged Account
			cout<<log->friends[i]->username<<" Successfully Removed"<<endl;
			log->friends[i] = NULL;
			// loop to rearrange the logged friend list
			for (int j = i; log->friends[j] != NULL; j++)
			{
				log->friends[j] =  log->friends[j + 1];
				log->friends[j + 1] = NULL; 
			}
			log->fnum--;
			system("pause");
			return;
		}
	}
	cout<<"User is Not on Friend List"<<endl;
	system("pause");
	return;
}
// FRIENDS END

// START GUESS NUMBER

void howToPlayGuessNumber()
{
	system("CLS");
	cout<<"\nHow To Play Guess the Number"<<endl;
	cout<<"\nSelect Difficulty Level: Begin by choosing a difficulty "<<endl;
	cout<<"level for the game: Easy, Medium, or Hard."<<endl;
	cout<<"\nMake a Guess: Enter your first guess for the randomly"<<endl;
	cout<<"generated number. After each guess, you will receive"<<endl;
	cout<<"a hint indicating whether the hidden number is higher"<<endl;
	cout<<"or lower than your previous guess. Use this feedback"<<endl;
	cout<<"to inform your next guess."<<endl;
	cout<<"\nContinue Guessing: You have 5 chances to guess"<<endl;
	cout<<"the number right."<<endl<<endl;
	system("pause");
}

void guessNumber(userStruct *log)
{
	howToPlayGuessNumber();
	int difficulty[] = {10, 50, 100};
	int level;
	while(1)
	{
		system("CLS");
		cout<<"\nWelcome to Guess the Number "<<log->username<<endl;
		cout<<"Choose Difficulty"<<endl;
		cout<<"1. Easy (1 - 10)"<<endl;
		cout<<"2. Medium (1 - 50)"<<endl;
		cout<<"3. Hard (1 - 100)"<<endl;
		opt = inputGetter("Input: ");
		if (opt > 0 && opt < 4)
		{
			break;
		}
		cout<<"Invalid Input"<<endl;
		system("pause");
	}
	level = difficulty[opt - 1];
	int attempts = 5, start = 1, end = level;
	level--;
	int secretNumber = (rand() % level) + 1, guessNumber;
	system("CLS");
	while (1)
	{
		cout<<"\nClue: The Number is between "<<start<<" and "<<end<<endl;
		cout<<"Attempts Left: "<<attempts<<endl;
		cout<<"Guess the Number: ";
		cin>>guessNumber;	
		system("CLS");
		if (guessNumber == secretNumber)
		{
			cout<<"\nYOU HAVE WON "<<log->username<<endl;
			cout<<"The Number is: "<<secretNumber<<endl;
			return;
		}
		else if (guessNumber < secretNumber)
		{ 
			cout<<"\nHIGHER!"<<endl;
			start = guessNumber;
		}
		else
		{
			cout<<"\nLOWER!"<<endl;
			end = guessNumber;
		}
		attempts--;
		if(attempts == 0)
		{
			cout<<"\nYOU HAVE LOST "<<log->username<<endl;
			cout<<"The Number is: "<<secretNumber<<endl;
			return;
		}
	}	
}
// END GUESS NUMBER

// START HANGMAN
void draw(int tries)
{
	cout<<endl;
	switch(tries)
	{
		case 0:
			cout << "   _____" << endl; 
            cout << "  |     |" << endl; 
            cout << "  |" << endl; 
            cout << "  |" << endl; 
            cout << "  |" << endl; 
            cout << "  |" << endl; 
            break;
        case 1:
        	cout << "   _____" << endl; 
            cout << "  |     |" << endl; 
            cout << "  |     O" << endl; 
            cout << "  |" << endl; 
            cout << "  |" << endl; 
            cout << "  |" << endl; 
            break;
        case 2:
        	cout << "   _____" << endl; 
            cout << "  |     |" << endl; 
            cout << "  |     O" << endl; 
            cout << "  |     |" << endl; 
            cout << "  |" << endl; 
            cout << "  |" << endl; 
            break;
		case 3:
        	cout << "   _____" << endl; 
            cout << "  |     |" << endl; 
            cout << "  |     O" << endl; 
            cout << "  |    /|" << endl; 
            cout << "  |" << endl; 
            cout << "  |" << endl; 
            break;
        case 4:
        	cout << "   _____" << endl; 
            cout << "  |     |" << endl; 
            cout << "  |     O" << endl; 
            cout << "  |    /|\\" << endl; 
            cout << "  |" << endl; 
            cout << "  |" << endl; 
            break;
        case 5:
        	cout << "   _____" << endl; 
            cout << "  |     |" << endl; 
            cout << "  |     O" << endl; 
            cout << "  |    /|\\" << endl; 
            cout << "  |    /" << endl; 
            cout << "  |" << endl; 
            break;
        case 6:
        	cout << "   _____" << endl; 
            cout << "  |     |" << endl; 
            cout << "  |     O" << endl; 
            cout << "  |    /|\\" << endl; 
            cout << "  |    / \\" << endl; 
            cout << "  |" << endl; 
            break;
	}
	cout<<endl;
	return;
}
void generateword(char *word, char *category)
{
	strcpy(category, "TTRY");
	char *words[][20] = {
        {"BLACK", "RED", "WHITE", "BLUE", "GREEN"},
        {"JEEP", "CAR", "MOTORCYCLE", "BUS", "TRUCK"},
        {"EARTH", "MARS", "JUPITER", "MERCURY", "VENUS"},
        {"CAT", "DOG", "BIRD", "HAMSTER", "FISH"},
        {"ROSE", "GUMAMELA", "SAMPAGUITA", "TULIP"}
    };
    char categ[][20] = {"COLORS", "VEHICLE", "PLANETS", "PET", "FLOWER"};

    int row = rand() % 5;  // Generate random row index (0-4)
    int col = rand() % 3;  // Generate random column index (0-2)
    
    strcpy(word, words[row][col]);
	strcpy(category, categ[row]);
}

void howToPlayHangman()
{
	system("CLS");
	cout<<"\nHow To Play Hangman"<<endl;
	cout<<"\n1. The player will be given a secret word based on a random"<<endl;
	cout<<"category and will be  displayed as a series of blank spaces,"<<endl;
	cout<<"each representing a letter in the word."<<endl;
	cout<<"\n2. The player will enter letter(s) as their guess."<<endl;
	cout<<"\n3. If the guessed letter is in the secret word, it will"<<endl;
	cout<<"be revealed in its correct position(s)."<<endl;
	cout<<"\n4.For each wrong guessed letter, a part of the stick"<<endl;
	cout<<"figure is drawn."<<endl;
	cout<<"\n5. You have six incorrect guesses before the stick"<<endl;
	cout<<"figure is completely drawn and hung."<<endl;
	cout<<"\n6. Guess the entire word correctly before making six"<<endl;
	cout<<"mistakes to win the game."<<endl<<endl;
	system("pause");
}

void hangman(userStruct *log)
{
	howToPlayHangman();
	system("CLS");
	char guess[20], input[20], secret[20], category[20];
	generateword(secret, category);
	for (i = 0; i < strlen(secret); i++)
	{
		guess[i] = '_';
	}
	guess[strlen(secret)] = '\0';
	int attempts = 0;
	while(1)
	{
		cout<<"\nCategory: "<<category<<endl;
		cout<<"Your Guess: "<<guess<<endl;
		cout<<"You have "<<(6 - attempts)<<" attempts left"<<endl;
		draw(attempts);
		cout<<"What is your guess? ";
		gets(input);
		upperCase(input);
		int match = 0;
		for (int i = 0; i < strlen(input); i++)
		{
			match = 0;
			for(int j = 0; j < strlen(secret); j++)
			{
				if (input[i] == secret[j])
				{
					guess[j] = input[i];
					match = 1;
				}
				if (!match && j == strlen(secret) - 1)
					attempts++;
			}
		}
		if (attempts > 5)
		{
			system("CLS");
			cout<<"\nYou Have Lost "<<endl;
			cout<<"Secret Word: "<<secret<<endl;
			draw(attempts);
			return;
		}
		if (strcmp(guess, secret) == 0)
		{
			system("CLS");
			draw(attempts);
			cout<<"\nYou Have Won with "<<(6 - attempts)<<" Attempts to Spare"<<endl;
			cout<<"Word: "<<secret<<endl;
			return;
		}
		system("CLS");
	}
}

// END HANGMAN

// START CONNECT FOUR
void howToPlayConnectFour()
{
	system("CLS");
	cout<<"\nHow To Play Connect Four"<<endl;
	cout<<"\n1. Players will decide who will be Player 1 and 2."<<endl;
	cout<<"\n2. Players will take turns putting pieces in a"<<endl;
	cout<<"7 x 6 grid"<<endl;	
	cout<<"\n3. Players' goal is to connect their respective"<<endl;
	cout<<"pieces (X,O) in a row"<<endl;
	cout<<"\n4. The row can be up and down (vertical),"<<endl; 
	cout<<"across (horizontal), or diagonal."<<endl;
	cout<<"\n5. The first player to make four connections"<<endl;
	cout<<"wins the game."<<endl<<endl;
	system("pause");
}

void connectFour(userStruct *log)
{
	howToPlayConnectFour();
	system("CLS");
	cout<<"\nWelcome to Connect Four "<<log->username<<endl;
	initialize();
	int turn = 0;
	while(1)
	{
		turn = input(turn);
		int check = checker();
		if(check == 1 || check == 2)
		{
			system("CLS");
			cout<<"\nYou Have Won "<<nameCF[check - 1]<<endl;
			drawBoard();
			break;
		}
		if (check == 3)
		{
			system("CLS");
			cout<<"DRAW!"<<endl;
			drawBoard();
			break;
		}
		system("pause");
		system("CLS");
	}
}

void initialize()
{
	cin.ignore();
	cout<<"\nEnter Player One's Name: ";
	gets(nameCF[0]);
	cout<<"Enter Player Two's Name: ";
	gets(nameCF[1]);
	upperCase(nameCF[0]);
	upperCase(nameCF[1]);
	for(int i = 0; i < width; i++)
	{
		for (int j = 0; j < len; j++)
		{
			table[i][j] = '_';
		}
	}
	system("CLS");
	return;
}

void drawBoard()
{
	cout<<"\n  1     2     3     4     5     6"<<endl;
	for(int i = 0; i < width; i++)
	{
		for (int j = 0; j < len; j++)
		{
			cout<<"| "<<table[i][j]<<" | ";
		}
		cout<<endl;
	}
	cout<<endl;
	return;
}

int input(int turn)
{
	int input;
	drawBoard();
	cout<<"Player "<<nameCF[turn]<<"'s Turn"<<endl;
	input = opt = inputGetter("Enter the Column Number: ");
	input--;
	if (input < 6 && input >= 0 && table[0][input] == '_')
	{
		for(int i = 0; i < width; i++)
		{
			if (table[i+1][input] == '_')
			{
				continue;
			}
			else
			{
				if (turn == 0)
				{
					table[i][input] = 'X';
					break;
				}	
				else 
				{
					table[i][input] = 'O';
					break;
				}
					
			} 
		}
		drawBoard();
		if (turn == 0)
			return 1;
		else 
			return 0;
	}
	cout<<"\nInvalid Input"<<endl;
	return turn;
	
}

int checker()
{
	for (i = 0; i < width; i++) 
	{
        for (int j = 0; j < len - 3; j++) 
		{
            if (table[i][j] != '_' &&  table[i][j] == table[i][j + 1] && table[i][j] == table[i][j + 2] && table[i][j] == table[i][j + 3]) 
			{
                return (table[i][j] == 'X') ? 1 : 2;
            }
        }
    }

    // Check vertical win
    for (i = 0; i < width - 3; i++) 
	{
        for (int j = 0; j < len; j++) 
		{
            if (table[i][j] != '_' && table[i][j] == table[i + 1][j] && table[i][j] == table[i + 2][j] && table[i][j] == table[i + 3][j]) 
			{
                return (table[i][j] == 'X') ? 1 : 2;
            }
        }
    }

    // Check diagonal win (bottom-left to top-right)
    for (i = 3; i < width; i++) 
	{
        for (int j = 0; j < len - 3; j++) 
		{
            if (table[i][j] != '_' && table[i][j] == table[i - 1][j + 1] && table[i][j] == table[i - 2][j + 2] && table[i][j] == table[i - 3][j + 3]) 
			{
                return (table[i][j] == 'X') ? 1 : 2;
            }
        }
    }

    // Check diagonal win (top-left to bottom-right)
    for (i = 0; i < width - 3; i++) 
	{
        for (int j = 0; j < len - 3; j++)
		 {
            if (table[i][j] != '_' && table[i][j] == table[i + 1][j + 1] && table[i][j] == table[i + 2][j + 2] && table[i][j] == table[i + 3][j + 3]) 
			{
                return (table[i][j] == 'X') ? 1 : 2;
            }
        }
    }

    // Check for a draw
    int draw = 0;
    for (int i = 0; i < len; i++) 
	{
        if (table[0][i] != '_') 
		{
            draw++;
        }
    }
    if (draw == len) 
	{
        return 3;
    }

    return 0;
}

// END CONNECT FOUR

// START OF GOBBLET GOBBLERS
void howToPlayGobbletGobblers()
{
	system("CLS");
	cout<<"\nHow To Play Gobblet Gobblers"<<endl;
	cout<<"\n1. Each player receives 2 pieces for each piece size"<<endl;
	cout<<"(small, medium, large), totalling to 6 pieces per player."<<endl;
	cout<<"\n2. Players take turns either placing a new piece from"<<endl;
	cout<<"their available piece(s) or moving one of their existing"<<endl;
	cout<<"piece(s) to another square."<<endl;
	cout<<"\n3. Larger pieces can gobble up or cover smaller enemy"<<endl;
	cout<<"pieces. A piece that has been gobbled can be revealed if"<<endl;
	cout<<"the covering piece is moved."<<endl;
	cout<<"\n4. The game continues until one player successfully aligns"<<endl;
	cout<<"three of their pieces in a row, either horizontally,"<<endl;
	cout<<"vertically, or diagonally."<<endl;
	cout<<"\n5. The player to first achieve this wins the game. If all"<<endl;
	cout<<"squares are filled and no player has three in a row,"<<endl;
	cout<<"the game ends in a draw."<<endl<<endl;
	system("pause"); 
}

void gobblet(userStruct *log)
{
	howToPlayGobbletGobblers();
	system("CLS");
	cout<<"\nWelcome to Gobblet Gobblers "<<log->username<<endl<<endl;
	initialization(log);
	gameBoard();
	turnChecker(turn);
}

int inputGetter(const char*message)
{
	cout<<message;
	cin>>in;
	opt = atoi(in);
	return opt;
}

void initialization(userStruct *log) 
{
    for (int i = 0; i < 3; i++) 
	{
        for (int j = 0; j < 3; j++) 
		{
            strcpy(board[i][j], " ");
        }
    }
    char player1[50], player2[50];
	cout<<"Enter Player One's Name: ";
	gets(player1);
	upperCase(player1);
	while (1)
	{
		cout<<"Enter Player Two's Name: ";
		gets(player2);
		upperCase(player2);
		if (player1[0] == player2[0])
			cout<<"Invalid Name, First Letter Must Not Match With Player 1"<<endl;
		else
			break;
	}
	strcpy(players[0].name, player1);
	strcpy(players[1].name, player2);
    players[0].emblem = player1[0];
	players[1].emblem = player2[0]; 
	
	for (i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			players[i].pieces[j] = 2;
		}
	}
}

void gameBoard() 
{
    system("CLS");
    for (int i = 0; i < 3; i++) 
    {
    	if (i == 0)
    	{
    		cout<<"----------------------"<<endl;
		}	
		cout<<"|      |      |      |"<<endl;
    	cout << "|  ";
        for (int j = 0; j < 3; j++) 
		{
            char *line = board[i][j];
            if (strlen(line) >= 2) 
            	cout<<getSubStr(line, strlen(line) - 2, 2);
            else 
            	cout << "  ";
            cout << "  |  ";
        }
		cout<<endl<<"|      |      |      |"<<endl;	
		cout<<"----------------------"<<endl;
	}
}

int gameplay(int turn)
{
	int row = 0, col = 0, choice = 0;
    char piece[20];
    
    while(1)
    {
    	inputAgain:
    	cout<<endl;
    	row = inputGetter("Input Row to Play: ") -1;
    	col = inputGetter("Input Column to Play: ") -1;
    	
    	if (row > 2 || row < 0 || col > 2 || col < 0)
    	{
    		cout<<"Invalid Input"<<endl;
    		continue;
		}
		char* boardPiece = board[row][col];
        int boardPiecePower = 0;
        boardPiecePower = boardPiece[strlen(boardPiece) - 1] - '0';
        if (boardPiece[strlen(boardPiece) - 2] == players[turn].emblem)
		{
			cout<<"You Already Have a Piece There"<<endl;
			continue;
		}
        if (boardPiecePower == 3) 
            cout << "This Position Contains a Large Piece " << endl;
        else
        	break; 
	}
	cin.ignore();
	cout<<"Choose Your Piece: ";
	gets(piece);
	piece[0] = toupper(piece[0]);
	choice = piece[1] - '0';
	if(strlen(piece) != 2 || piece[0] != players[turn].emblem || choice < 1 || choice > 3) 
	{
		cout<<"Invalid Piece"<<endl;
		goto inputAgain;
	}	
	if (players[turn].pieces[choice - 1] == 0)
	{
		cout<<"Both Pieces is Already on the Board"<<endl;
		goto inputAgain;
	}
	char* boardPiece = board[row][col];
	int sizeBoardPiece = 0;
	if (strlen(boardPiece) >= 2)
	{
		sizeBoardPiece = boardPiece[strlen(boardPiece) - 1] - '0';
	}
	if (choice <= sizeBoardPiece)
	{
		cout<<"This Piece's Power is Not Enough"<<endl;
		goto inputAgain;
	}
	strcat(board[row][col], piece);
	players[turn].pieces[choice - 1]--;
	gameBoard();
	
	if (turn == 0)
        return 1;
    else
        return 0;
}

int movePiece(int turn)
{
	int origRow, origCol, newRow, newCol, boardPiecePower;
	
	while(1)
	{
    	origRow = inputGetter("Input Row to Change: ") -1;
    	origCol = inputGetter("Input Column to Change: ") -1;
        
        if (origRow > 2 || origRow < 0 || origCol > 2 || origCol < 0)
    	{
    		cout<<"Invalid Input"<<endl;
    		continue;
		}
		char *boardPiece = board[origRow][origCol];
		if (strlen(boardPiece) < 2)
		{
			cout<<"Cell is Empty"<<endl;
			continue;
		}
		if (boardPiece[strlen(boardPiece) - 2] != players[turn].emblem)
		{
			cout<<"Piece Belongs to the Other Player"<<endl;
			continue;
		}
		
		boardPiecePower = boardPiece[strlen(boardPiece) - 1] - '0';
		break;
	}
	while(1)
	{
    	newRow = inputGetter("Input Row to Place: ") -1;
    	newCol = inputGetter("Input Column to Place: ") -1;
		
        if (newRow > 2 || newRow < 0 || newCol > 2 || origCol < 0)
    	{
    		cout<<"Invalid Input"<<endl;
    		continue;
		}
		char *targetPiece = board[newRow][newCol];
		int targetPiecePower = 0;
		if (strlen(targetPiece) >= 2)
		{
			targetPiecePower = targetPiece[strlen(targetPiece) - 1] - '0';
		}
		if (targetPiecePower >= boardPiecePower)
		{
			cout<<"This Piece's Power is Not Enough"<<endl;
			continue;
		}
		break;
	}
	char *origPiece = board[origRow][origCol];
	char toInputPiece[3];
	strcpy(toInputPiece, getSubStr(origPiece, strlen(origPiece) - 2, 2));
	strcpy(board[origRow][origCol], getSubStr(origPiece, 0, strlen(origPiece) - 2));
	strcat(board[newRow][newCol], toInputPiece);
	
	gameBoard();
    if (turn == 0)
        return 1;
    else 
        return 0;
}

int movablePiece(int turn)
{
	char boardPiece[3];
	int power = 0;
	int havePiece = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (strlen(board[i][j]) >= 2)
			{
				strcpy(boardPiece, getSubStr(board[i][j], strlen(board[i][j]) - 2, 2));
			}
			if (boardPiece[0] == players[turn].emblem)
			{
				if (power < boardPiece[1] - '0')
				{
					strcpy(boardPiece, getSubStr(board[i][j], strlen(board[i][j]) - 2, 2));
					power = boardPiece[1] - '0';
					havePiece = 1;
				}
			}
		}
	}
	if (havePiece == 1)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (strlen(board[i][j]) < 2)
				{
					return 1;
				}
				if (board[i][j][strlen(board[i][j]) - 2] != players[turn].emblem &&
                    power > board[i][j][strlen(board[i][j]) - 1] - '0')
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

void turnChecker(int turn)
{
	while(1)
	{
		char win = winCondition();
		if (win == players[0].emblem || win == players[1].emblem) 
		{
	        printWinner(win);
	        return;
	    }
		cout<<"Player "<<players[turn].name<<"'s Turn"<<endl;
		
		int availablePiece = 0;
	    for (int i = 0; i < 3; i++) 
		{
	        availablePiece += players[turn].pieces[i];
	    }
	    if (availablePiece != 0)
	    {
	    	cout<<"Available Pieces: "<<endl;
	    	for (int i = 0; i < 3; i++)
	    	{
	    		for (int j = 0; j < players[turn].pieces[i]; j++) 
				{
	                cout << players[turn].emblem << i + 1 << " ";
	            }
			}
			if (availablePiece < 6) 
			{
	            //while (1) 
				//{
					char win = winCondition();
					if (win == players[0].emblem || win == players[1].emblem) 
					{
				        printWinner(win);
				        return;
				    }
				    cout << "\nChoose Your Move" << endl;
	            	cout << "1. Play a New Piece." << endl;
	            	cout << "2. Play from the Board." << endl;
	            	cout << "3. Surrender" << endl;
	                opt = inputGetter("Input: ");
	                switch(opt)
	                {
	                	case 1:
	                		turn = gameplay(turn);
	                		break;
	                	case 2:
	                		if (movablePiece(turn) == 0)
	                		{
	                			cout<<"You Don't Have a Movable Piece on Board"<<endl;
	                			cout<<"Use New Piece: ";
	                			gameplay(turn);
	                			break;
							}
	                		turn = movePiece(turn);
	                		break;
	                	case 3:
	                		win = surrender(turn);
							if (win == players[0].emblem || win == players[1].emblem) 
							{
						        printWinner(win);
						        return;
						    }
	                		break;
	                	default:
	                		cout<<"Invalid Move"<<endl;
	                		break;
					//}
	            }
	        } 
			else 
			{
	            turn = gameplay(turn);
	        }
		}
		else 
		{
			cout<<"No Available Piece Outside the Board"<<endl<<"Play Pieces on the Board"<<endl;
			if (movablePiece(turn) == 0)
	        {
	        cout<<"You Don't Have a Movable Piece on Board"<<endl;
			}
	        turn = movePiece(turn);
		}
	}
}

void printWinner(char winner)
{
	gameBoard();
	cout<<endl;
	for (int i = 0; i < 2; i++)
	{
		if (winner == players[i].emblem)
		{
			cout<<"PLAYER "<<players[i].name<<" WON"<<endl;
		}
	}
}

char surrender(int turn)
{
	if (turn == 0)
		return players[1].emblem;
	else
		return players[0].emblem;
}

char winCondition()
{
	char currentBoard[3][3];
	for (i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (strlen(board[i][j]) < 2)
				currentBoard[i][j] = '_';
			else
				currentBoard[i][j] = board[i][j][strlen(board[i][j]) - 2];
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (currentBoard[i][0] == currentBoard[i][1] && currentBoard[i][1] == currentBoard[i][2])
		{
			if (currentBoard[i][0] != ' ')
			{
				return currentBoard[i][0];
			}
		}
		if (currentBoard[0][i] == currentBoard[1][i] && currentBoard[1][i] == currentBoard[2][i])
		{
			if (currentBoard[i][0] != ' ')
			{
				return currentBoard[0][i];
			}
		}
	}
	if (currentBoard[0][0] == currentBoard[1][1] && currentBoard[1][1] == currentBoard[2][2])
	{
		if (currentBoard[1][1] != ' ')
		{
			return currentBoard[1][1];
		}
	}
	if (currentBoard[0][2] == currentBoard[1][1] && currentBoard[1][1] == currentBoard[2][0])
	{
		if (currentBoard[1][1] != ' ')
		{
			return currentBoard[1][1];
		}
	}	
	return ' ';
}

char* getSubStr(const char *str, int start, int length) 
{
    static char res[20];
    strncpy(res, str + start, length);
    res[length] = '\0';
    return res;
}
// END OF GOBBLET GOBBLERS

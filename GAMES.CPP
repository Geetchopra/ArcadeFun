#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#include<dos.h>
#include<string.h>
#include<ctype.h>
#include<iomanip.h>

int z=0,i,j,n,chmast,chmenu,k,chance=10,flag=0,c,win=0,x,row=0,x1,y1,choice,num,letter,length,round,max;
char board[3][5]={"1 2 3","4 5 6","7 8 9"},n1[25],n2[25],pos1,pos2,guess,ch='y',code[4],gcode[10][4],ans[10][4];
char gword[100][15];
int count;


//--------------------------------------------------------------------------------
//-------------------------------Hangman------------------------------------------


class wordclass
{
char sword[15];
public:
char* getsword();
void getword();
void addword();
void delword();
void updateword();
void showword();
void checkword(char x);
void hangmanplay();
void getwordcount();
}word;

char* wordclass::getsword()
{
return sword;
}

void wordclass::getwordcount()
{
count=0;
fstream f1("words.txt",ios::binary|ios::in|ios::out);
f1.read((char*)this,sizeof(word));
while (!f1.eof())
{
if (stricmp(sword,"null")!=0)
count=count+1;
f1.read((char*)this,sizeof(word));
}
}



void main();
void hangmandev();

void wordclass::addword()
{
fstream f1;
int p;
f1.open("words.txt",ios::binary|ios::out|ios::in);
f1.read((char*)this,sizeof(word));
int flag=0,c;
while (!f1.eof())
{
if (stricmp(sword,"null")==0)
{
flag=1;
c=f1.tellp()-sizeof(word);
f1.seekp(c);
gotoxy(29,9);cout<<"Enter the word to be saved";
gotoxy(37,11);gets(sword);
fflush(stdin);
for (int i=0;i<strlen(sword);i++)
sword[i]=toupper(sword[i]);
f1.write((char*)this,sizeof(word));
f1.close();
break;
}
f1.read((char*)this,sizeof(word));
}
if (flag==0)
{
fstream f2("words.txt",ios::binary|ios::app);
gotoxy(29,9);cout<<"Enter the word to be saved";
gotoxy(39,11);gets(sword);
fflush(stdin);
for (int i=0;i<strlen(sword);i++)
sword[i]=toupper(sword[i]);
f2.write((char*)this,sizeof(word));
f2.close();
}
gotoxy(30,13);cout<<"Word added to database!";
getch();
hangmandev();
}

void wordclass::showword()
{
clrscr();
ifstream f1("words.txt",ios::binary);
if (!f1)
{
gotoxy(18,9);cout<<"Oops! File not present! Please add a word first...";
getch();
hangmandev();
}
f1.seekg(0);
gotoxy(21,1);cout<<"List of words present in the database";
f1.read((char*)this,sizeof(word));
int i=3;
while (!f1.eof())
{
if (stricmp(sword,"null")!=0)
{
gotoxy(35,i);cout<<sword;
i+=1;
}
f1.read((char*)this,sizeof(word));
}
gotoxy(15,i+1);cout<<"Please press any key to return to developer menu...";
getch();
hangmandev();
}

void wordclass::delword()
{
int p,c,flag=0,found=0;
char ch='y';
gotoxy(23,8);cout<<"Enter the word that you want to delete";
char newword[15];
gotoxy(37,10);gets(newword);
fflush(stdin);
fstream f("words.txt",ios::binary|ios::out|ios::in);
f.read((char*)this,sizeof(word));
while (!f.eof())
{
if (stricmp(newword,sword)==0)
{
found=1;
break;
}
f.read((char*)this,sizeof(word));
}
if (found==0)
{
gotoxy(34,12);cout<<"Oops! Word not found!";
gotoxy(21,13);cout<<"Please press 'y' to search again or any other key to exit.";
ch=getch();
if (ch=='y')
{
clrscr();
delword();
}
}
f.close();
fstream f1("words.txt",ios::binary|ios::in|ios::out);
fstream f2("words.txt",ios::binary|ios::in|ios::out);
f1.seekg(0);
f1.read((char*)this,sizeof(word));
while (!f1.eof())
{
	if (stricmp(newword,sword)==0)
		{
		c=f1.tellg()-sizeof(word);
			while (!f1.eof())
			{
				if (stricmp(sword,"null")==0)
					{
					flag=1;
					p=f1.tellg()-(2*sizeof(word));
					f1.seekg(p);
					f1.read((char*)this,sizeof(word));
					break;
					}
					f1.read((char*)this,sizeof(word));
			}
		strcpy(sword,word.sword);
		f2.seekp(c);
		f2.write((char*)this,sizeof(word));
		break;
		}
f1.read((char*)this,sizeof(word));
}
if (flag==0)
	{
		while (!f1.eof())
		{
		f1.read((char*)this,sizeof(word));
		}
		c=f1.tellg()-sizeof(word);
	}
else
	{
		while (!f1.eof())
		{
		f1.read((char*)this,sizeof(word));
		if (stricmp(sword,"null")==0)
			{
			c=f1.tellg()-(2*sizeof(word));
			break;
			}
		}
	}
strcpy(sword,"null");
f2.seekp(c);
f2.write((char*)this,sizeof(word));
f1.close();
f2.close();
gotoxy(21,12);cout<<"Word successfully deleted from the records!";
getch();
hangmandev();
}


void wordclass::updateword()
{
int c,found;
gotoxy(23,8);cout<<"Enter the word that you want to modify";
char newword[15];
gotoxy(37,10);gets(newword);
fflush(stdin);
fstream f("words.txt",ios::binary|ios::out|ios::in);
f.read((char*)this,sizeof(word));
while (!f.eof())
{
if (stricmp(newword,sword)==0)
{
found=1;
break;
}
f.read((char*)this,sizeof(word));
}
if (found==0)
{
gotoxy(34,12);cout<<"Oops! Word not found!";
gotoxy(21,13);cout<<"Please press 'y' to search again or any other key to exit.";
ch=getch();
if (ch=='y')
{
clrscr();
updateword();
}
}
f.close();
fstream f1("words.txt",ios::binary|ios::in|ios::out);
f1.seekp(0);
f1.read((char*)this,sizeof(word));
while (!f1.eof())
{
if (stricmp(newword,sword)==0)
{
c=f1.tellp()-sizeof(word);
f1.seekp(c);
gotoxy(26,12);cout<<"Enter the new word to be saved";
gotoxy(37,14);gets(sword);
fflush(stdin);
for (int i=0;i<strlen(sword);i++)
sword[i]=toupper(sword[i]);
f1.write((char*)this,sizeof(word));
break;
}
f1.read((char*)this,sizeof(word));
}
f1.close();
gotoxy(27,16);cout<<"Word updated successfully!";
getch();
hangmandev();
}

void wordclass::getword()
{
int k;
getwordcount();
randomize();
k=random(count-0)+0;
fstream f("words.txt",ios::binary|ios::in);
f.seekg(k*sizeof(word));
f.read((char*)this,sizeof(word));
chance=10;
clrscr();
n=strlen(word.sword);
for (j=0;j<n;j++)
	gword[z][j]='_';
}

void hangman();

void hangmandev()
{
char ch,pass[30];
clrscr();
gotoxy(30,11);cout<<"Authentication Required";
gotoxy(31,13);cout<<"Password : ";
gets(pass);
fflush(stdin);
if (stricmp(pass,"geetchopra")!=0)
{
gotoxy(27,15);cout<<"Incorrect password! Try Again?";
gotoxy(34,16);cout<<"Input y/n : ";
cin>>ch;
if (ch=='y')
hangmandev();
else
hangman();
}
fflush(stdin);
int choice;
clrscr();
gotoxy(21,11);cout<<"Please wait while you are logged in...";
delay(1000);
clrscr();
gotoxy(27,9);cout<<"Developer Maintenance Center";
gotoxy(33,11);cout<<"1.Add a word";
gotoxy(33,12);cout<<"2.Delete a word";
gotoxy(33,13);cout<<"3.Modify a word";
gotoxy(33,14);cout<<"4.Show all words";
gotoxy(33,15);cout<<"5.Hangman menu";
gotoxy(32,17);cout<<"Enter choice : ";
cin>>choice;
switch(choice)
{
case 1:clrscr();
       word.addword();
       break;
case 2:clrscr();
       word.delword();
       break;
case 3:clrscr();
       word.updateword();
       break;
case 4:clrscr();
       word.showword();
       break;
case 5:clrscr();
       hangman();
       break;
default:gotoxy(13,19);cout<<"Oops! Wrong Choice. Please press any key to enter again...";
	getch();
	hangmandev();
}
}

void tips()
{
clrscr();
gotoxy(28,8);cout<<"Remember the following tips-";
cout<<"\n\n    1.Always enter vowels first. They are most likely to be present.";
cout<<"\n    2.Do not input uncommon letters like 'z','x','q' etc. in the beginning.";
cout<<"\n    3.Some common letters include - 'm','n','s','p','r' etc.";
cout<<"\n    4.When in trouble, try to make a random, logical and an educated guess,\n      just like in a crossword";
cout<<"\n\n                    Now you will be able to guess the words in no time!";
getch();
hangman();
}


void hangmantutorial()
{
clrscr();
gotoxy(30,8);cout<<"Welcome to the Tutorial!";
cout<<"\n\n  The rules are simple. The computer will generate a word.";
cout<<"\n  You will then input letters which you think are present, to guess the word.";
cout<<"\n  At any point of time if you need to close the game during play please input 0.";
cout<<"\n  You have 10 chances with you. All The Best!!";
gotoxy(30,15);cout<<"Press any key to start...";
getch();
word.hangmanplay();
}


void hangmandisplay()
{
float q,len;
len=strlen(word.getsword());
q=len+(2*(len-1));
q/=2;
 for (i=0,j=1;i<n;i++)
	{
	gotoxy((40-q)+(i+j),8);cout<<gword[z][i];
	j=j+2;
	}
 gotoxy(33,2);cout<<"Chances left : "<<chance;
}


void wordclass::checkword(char x)
{
for (i=0;i<n;i++)
	{
	if (toupper(x)==word.sword[i])
	 {
		gword[z][i]=toupper(x);
		flag=1;
	 }
	}
}


void wordclass::hangmanplay()
{
flag=0;
word.getword();
do
 {
		clrscr();
		hangmandisplay();
		gotoxy(34,10);cout<<"Enter letter : ";
		guess=getchar();
		fflush(stdin);
		while (guess==10)
		{
		hangmandisplay();
		gotoxy(34,10);cout<<"Enter letter : ";
		guess=getchar();
		fflush(stdin);
		}
		if ((guess<97||guess>122)&&(guess<65||guess>90))
		 {
			if (guess=='0')
			 {
	clrscr();
	gotoxy(26,10);cout<<"Thank you for playing Hangman!!";
	delay(800);
	exit(0);
			 }
			else
			 {
	clrscr();
	hangmandisplay();
	gotoxy(31,10);cout<<"Invalid character:"<<"'"<<guess<<"'";
	gotoxy(26,11);cout<<"Press any key to enter again...";
	getch();
	continue;
			 }
		 }
	word.checkword(guess);
	if (flag==0)
	 {
		 chance--;
		 clrscr();
		 hangmandisplay();
		 gotoxy(32,10);cout<<"Letter not present!";
			 if (chance!=0)
	 {
		 gotoxy(21,11);cout<<"Press any key to enter another guess...";
	 }
		 getch();
	 }
	else
	 {
		 flag=0;
		 continue;
	 }
 } while ((chance>0)&&(stricmp(gword[z],word.sword)!=0));
if ((stricmp(gword[z],word.sword)==0))
 {
	 clrscr();
	 hangmandisplay();
	 gotoxy(36,11);cout<<"YOU WIN!!";
 }
else
 {
	 clrscr();
	 float q,len;
	 len=strlen(word.getsword());
	 q=len+(2*(len-1));
	 q/=2;
		for (i=0,j=1;i<n;i++)
		 {
			 gotoxy((40-q)+(i+j),8);cout<<word.sword[i];
			 j=j+2;
		 }
	 gotoxy(36,11);cout<<"YOU LOSE!!";
 }
getch();
z=z+1;
hangman();
}


void hangman()
{
clrscr();
gotoxy(32,8);cout<<"Welcome to Hangman!!";
gotoxy(37,9);cout<<"Game Menu";
gotoxy(35,11);cout<<"1.New Game";
gotoxy(35,12);cout<<"2.How To Play";
gotoxy(35,13);cout<<"3.Some Tips";
gotoxy(35,14);cout<<"4.Maintenence";
gotoxy(35,15);cout<<"5.Main Menu";
gotoxy(34,17);cout<<"Enter choice : ";
cin>>chmenu;
switch (chmenu)
 {
	 case 1:word.hangmanplay();
		break;
	 case 2:hangmantutorial();
		break;
	 case 3:tips();
		break;
	 case 4:hangmandev();
		break;
	 case 5:clrscr();
		gotoxy(26,10);cout<<"Thank you for playing Hangman!!";
		delay(1000);
		main();
		break;
	 default:gotoxy(13,19);cout<<"Oops! Wrong Choice. Please press any key to enter again...";
		 getch();
		 hangman();

 }
}

//----------------------------------------------------------------------------
//------------------------------Mastermind------------------------------------

void mastermind();

void colorscheme()
{
gotoxy(35,16);cout<<"COLOR SCHEME";
gotoxy(26,18);cout<<"Azur     - ";
textcolor(BLUE);
cputs("*");
cout<<"\tRed        - ";
textcolor(RED);
cputs("*");
gotoxy(26,19);cout<<"Yellow   - ";
textcolor(YELLOW);
cputs("*");
cout<<"\tLight Blue - ";
textcolor(LIGHTBLUE);
cputs("*");
gotoxy(26,20);cout<<"Green    - ";
textcolor(GREEN);
cputs("*");
cout<<"\tBlack      - ";
textcolor(DARKGRAY);
cputs("*");
gotoxy(26,21);cout<<"Magenta  - ";
textcolor(MAGENTA);
cputs("*");
cout<<"\tOrange     - ";
textcolor(LIGHTRED);
cputs("*");
gotoxy(26,22);cout<<"Turqoise - ";
textcolor(LIGHTCYAN);
cputs("*");
cout<<"\tWhite      - ";
textcolor(WHITE);
cputs("*");
getch();
}
struct color
{
int val;
char name;
}a={0,'a'},r={0,'r'},t={0,'t'},y={0,'y'},g={0,'g'},w={0,'w'},o={0,'o'},m={0,'m'},l={0,'l'},b={0,'b'};

void evalwin()
{
for (i=0;i<4;i++)
{
  if (gcode[row][i]==code[i])
  win=1;
  else
  {
  win=0;
  break;
  }
}
}

void check(color a)
{
if (a.val==0)
  {
  if (ans[row][x]!='r'&&ans[row][x]!='w')
  ans[row][x]=' ';
  }
else if (gcode[row][x]==code[x])
{
ans[row][x]='r';
flag=1;
}
else if (a.val>0)
{
for (i=0;i<n;i++)
{
   if (gcode[row][x]==code[i]&&gcode[row][x]==a.name&&gcode[row][i]!=code[i]&&a.val>0)
   {
    ans[row][x]='w';
    flag=1;
       }
}
}
}

void getcount()
{
for (i=0;i<4;i++)
ans[row][i]=' ';
a.val=0;
g.val=0;
r.val=0;
w.val=0;
y.val=0;
t.val=0;
o.val=0;
m.val=0;
l.val=0;
b.val=0;
for (i=0;i<4;i++)
{
if (code[i]=='a')
a.val++;
else if (code[i]=='r')
r.val++;
else if (code[i]=='t')
t.val++;
else if (code[i]=='y')
y.val++;
else if (code[i]=='g')
g.val++;
else if (code[i]=='w')
w.val++;
else if (code[i]=='o')
o.val++;
else if (code[i]=='m')
m.val++;
else if (code[i]=='l')
l.val++;
else if (code[i]=='b')
b.val++;
}
}

void eval(char c)
{
if (c=='a')
textcolor(BLUE);
else if (c=='r')
textcolor(RED);
else if (c=='t')
textcolor(LIGHTCYAN);
else if (c=='y')
textcolor(YELLOW);
else if (c=='g')
textcolor(GREEN);
else if (c=='w')
textcolor(WHITE);
else if (c=='o')
textcolor(LIGHTRED);
else if (c=='m')
textcolor(MAGENTA);
else if (c=='l')
textcolor(LIGHTBLUE);
else if (c=='b')
textcolor(DARKGRAY);
else if (c=='0')
exit(0);
}


void masterminddisplay()
{
for (i=1,j=2;i<5;i++)
  {
	gotoxy(10+i+j,n);cout<<"_";
	j=j+2;
  }
}


void getcode()
{
clrscr();
gotoxy(33,9);cout<<"Enter the code";
for (i=1,j=2;i<5;i++)
  {
	gotoxy(32+i+j,11);cout<<"_";
	j=j+2;
  }
for (i=1,j=2,k=0;i<5;i++,k++)
  {
	flag=0;
	gotoxy(32+i+j,11);code[k]=getch();
	code[k]=tolower(code[k]);
	while (code[k]!=8&&code[k]!='c'&&code[k]!='l'&&code[k]!='a'&&code[k]!='m'&&code[k]!='o'&&code[k]!='r'&&code[k]!='y'&&code[k]!='g'&&code[k]!='b'&&code[k]!='w'&&code[k]!='t'&&code[k]!='0')
	{gotoxy(32+i+j,11);code[k]=getch();code[k]=tolower(code[k]);}
	while (code[k]==8&&j==2)
	{gotoxy(32+i+j,11);code[k]=getch();code[k]=tolower(code[k]);}
	while (code[k]=='c'||code[k]==8)
	{
	while (code[k]=='c')
	{
	gotoxy(1,16);colorscheme();
	gotoxy(1,16);for (x1=0;x1<10;x1++)
		       {
			for (y1=0;y1<70;y1++)
			{
			cout<<" ";
			}
			}
	gotoxy(32+i+j,11);code[k]=getch();
	code[k]=tolower(code[k]);
	while (code[k]!=8&&code[k]!='c'&&code[k]!='l'&&code[k]!='a'&&code[k]!='m'&&code[k]!='o'&&code[k]!='r'&&code[k]!='y'&&code[k]!='g'&&code[k]!='b'&&code[k]!='w'&&code[k]!='t'&&code[k]!='0')
	{gotoxy(32+i+j,11);code[k]=getch();code[k]=tolower(code[k]);}
	while (code[k]==8&&j==2)
	{gotoxy(32+i+j,11);code[k]=getch();code[k]=tolower(code[k]);}
	}
	while (code[k]==8)
	{
	gotoxy(32+i+j,11);cout<<"_";
	i--;
	j=j-2;
	k--;
	gotoxy(32+i+j,11);cout<<"_";
	gotoxy(32+i+j,11);code[k]=getch();
	code[k]=tolower(code[k]);
	while (code[k]!=8&&code[k]!='c'&&code[k]!='l'&&code[k]!='a'&&code[k]!='m'&&code[k]!='o'&&code[k]!='r'&&code[k]!='y'&&code[k]!='g'&&code[k]!='b'&&code[k]!='w'&&code[k]!='t'&&code[k]!='0')
	{gotoxy(32+i+j,11);code[k]=getch();code[k]=tolower(code[k]);}
	while (code[k]==8&&j==2)
	{gotoxy(32+i+j,11);code[k]=getch();code[k]=tolower(code[k]);}
	}
	}
	eval(code[k]);
	gotoxy(32+i+j,11);cputs("*");
	j=j+2;
  }
textcolor(WHITE);
gotoxy(12,13);cout<<"Press 'c' to change code or press any other key to continue";
ch=getch();
while (ch=='c')
getcode();
}

void gencode()
{
randomize();
for (i=0;i<4;i++)
{
letter=random(9-0);
if (letter==0)
code[i]='r';
else if (letter==1)
code[i]='g';
else if (letter==2)
code[i]='a';
else if (letter==3)
code[i]='l';
else if (letter==4)
code[i]='y';
else if (letter==5)
code[i]='m';
else if (letter==6)
code[i]='b';
else if (letter==7)
code[i]='w';
else if (letter==8)
code[i]='o';
else if (letter==9)
code[i]='t';
}
}

void mastermindplay()
{
n=2;
flag=0;
win=0;
row=0;
if (num==1)
gencode();
else
getcode();
n++;
textcolor(WHITE);
clrscr();
cout<<"                                    GUESSES";
do
{
masterminddisplay();
for (i=1,j=2,k=0;i<5;i++,k++)
  {     flag=0;
	gotoxy(10+i+j,n);gcode[row][k]=getch();
	gcode[row][k]=tolower(gcode[row][k]);
	while (gcode[row][k]!=8&&gcode[row][k]!='c'&&gcode[row][k]!='l'&&gcode[row][k]!='a'&&gcode[row][k]!='m'&&gcode[row][k]!='o'&&gcode[row][k]!='r'&&gcode[row][k]!='y'&&gcode[row][k]!='g'&&gcode[row][k]!='b'&&gcode[row][k]!='w'&&gcode[row][k]!='t'&&gcode[row][k]!='0')
	{gotoxy(10+i+j,n);gcode[row][k]=getch();gcode[row][k]=tolower(gcode[row][k]);}
	while (gcode[row][k]==8&&j==2)
	{gotoxy(10+i+j,n);gcode[row][k]=getch();gcode[row][k]=tolower(gcode[row][k]);}
	while (gcode[row][k]=='c'||gcode[row][k]==8)
	{
	while (gcode[row][k]=='c')
	{
	gotoxy(1,16);colorscheme();
	gotoxy(20,16);for (x1=0;x1<10;x1++)
		       {
			for (y1=0;y1<70;y1++)
			{
			cout<<" ";
			}
			}
	gotoxy(10+i+j,n);gcode[row][k]=getch();
	gcode[row][k]=tolower(gcode[row][k]);
	while (gcode[row][k]!=8&&gcode[row][k]!='c'&&gcode[row][k]!='l'&&gcode[row][k]!='a'&&gcode[row][k]!='m'&&gcode[row][k]!='o'&&gcode[row][k]!='r'&&gcode[row][k]!='y'&&gcode[row][k]!='g'&&gcode[row][k]!='b'&&gcode[row][k]!='w'&&gcode[row][k]!='t'&&gcode[row][k]!='0')
	{gotoxy(10+i+j,n);gcode[row][k]=getch();gcode[row][k]=tolower(gcode[row][k]);}
	while (gcode[row][k]==8&&j==2)
	{gotoxy(10+i+j,n);gcode[row][k]=getch();gcode[row][k]=tolower(gcode[row][k]);}
	}
	while (gcode[row][k]==8)
	{
	textcolor(LIGHTGRAY);
	gotoxy(10+i+j,n);cout<<"_";
	i--;
	j=j-2;
	k--;
	gotoxy(10+i+j,n);cout<<"_";
	gotoxy(10+i+j,n);gcode[row][k]=getch();
	gcode[row][k]=tolower(gcode[row][k]);
	while (gcode[row][k]!=8&&gcode[row][k]!='c'&&gcode[row][k]!='l'&&gcode[row][k]!='a'&&gcode[row][k]!='m'&&gcode[row][k]!='o'&&gcode[row][k]!='r'&&gcode[row][k]!='y'&&gcode[row][k]!='g'&&gcode[row][k]!='b'&&gcode[row][k]!='w'&&gcode[row][k]!='t'&&gcode[row][k]!='0')
	{gotoxy(10+i+j,n);gcode[row][k]=getch();gcode[row][k]=tolower(gcode[row][k]);}
	while (gcode[row][k]==8&&j==2)
	{gotoxy(10+i+j,n);gcode[row][k]=getch();gcode[row][k]=tolower(gcode[row][k]);}
	}
	}
	eval(gcode[row][k]);
	gotoxy(10+i+j,n);cputs("*");
	j=j+2;
  }
cout<<"\t\t\t\t\t";
getcount();
for (x=0;x<4;x++)
{
flag=0;
if (gcode[row][x]=='a')
{
check(a);
if (flag!=0)
a.val--;
}
else if (gcode[row][x]=='y')
{
check(y);
if (flag!=0)
y.val--;
}
else if (gcode[row][x]=='l')
{
check(l);
if (flag!=0)
l.val--;
}
else if (gcode[row][x]=='m')
{
check(m);
if (flag!=0)
m.val--;
}
else if (gcode[row][x]=='r')
{
check(r);
if (flag!=0)
r.val--;
}
else if (gcode[row][x]=='g')
{
check(g);
if (flag!=0)
g.val--;
}
else if (gcode[row][x]=='w')
{
check(w);
if (flag!=0)
w.val--;
}
else if (gcode[row][x]=='t')
{
check(t);
if (flag!=0)
t.val--;
}
else if (gcode[row][x]=='o')
{
check(o);
if (flag!=0)
o.val--;
}
else if (gcode[row][x]=='b')
{
check(b);
if (flag!=0)
b.val--;
}
}
for (i=0;i<4;i++)
{
if (ans[row][i]=='r')
{
textcolor(RED);
cputs("*");
}
else if (ans[row][i]=='w')
{
textcolor(WHITE);
cputs("*");
}
else if (ans[row][i]==' ')
{
textcolor(DARKGRAY);
cputs("-");
}
cout<<" ";
}
evalwin();
n++;
row++;
}while (row!=10&&win==0);
if (win==1)
cout<<"\n\n                                   YOU WIN!!";
else
{
cout<<"\n\n                                   YOU LOSE!!\n\n                                      CODE";
for (i=4,j=5,k=0;i<8;i++,k++)
{
eval(code[k]);
gotoxy(26+i+j,n+5);cputs("*");
j=j+2;
}
}
getch();
mastermind();
}

void mastermindtutorial()
{
clrscr();
cout<<"                                   TUTORIAL\n";
cout<<"This is a strategy based game where a player has to guess";
cout<<" a code entered by the\nsecond player within 10 chances.";
cout<<"The codes are color generated and are entered\nby their respective";
cout<<" first letters, shown below. After the guess code has been\nentered by the player, ";
cout<<" an answer key is displayed consisting of 3 types of\ncolor *'s, red, white";
cout<<" and blank. A red * means that the respective * is in\nthe correct place and";
cout<<" shouldn't be moved. A white * means that the respective\n* is present,";
cout<<" but at a different place. A blank (-) means that the respective\n* is";
cout<<" not there in the code. Enter 'c' any time to view the color scheme,";
cout<<" or\nbackspace to re-enter an *. At any point if you wish to exit, enter 0.";
cout<<"\n                                  GOOD LUCK!!";
cout<<"\n                      Press any key to start the game...";
gotoxy(1,16);colorscheme();
clrscr();
gotoxy(30,9);cout<<"1 Player or 2 Player?";
gotoxy(33,11);cout<<"Enter choice : ";
cin>>num;
mastermindplay();
}

void mastermind()
{
textcolor(WHITE);
clrscr();
gotoxy(30,9);cout<<"Welcome to Mastermind!!";
gotoxy(37,10);cout<<"Game Menu";
gotoxy(36,12);cout<<"1.New Game";
gotoxy(36,13);cout<<"2.Tutorial";
gotoxy(36,14);cout<<"3.Main Menu";
gotoxy(34,16);cout<<"Enter Choice : ";
cin>>chmast;
switch(chmast)
{
case 1:clrscr();
       gotoxy(30,9);cout<<"1 Player or 2 Player?";
       gotoxy(33,11);cout<<"Enter choice : ";
       cin>>num;
       mastermindplay();
       break;
case 2:mastermindtutorial();
       break;
case 3:clrscr();
       gotoxy(25,9);cout<<"Thank You for playing Mastermind!!";
       delay(1000);
       main();
default:gotoxy(13,18);cout<<"Oops! Wrong Choice. Please press any key to enter again...";
	getch();
	mastermind();
}
}

//----------------------------------------------------------------------------
//-------------------------------Tic-Tac-Toe----------------------------------

void tictactoedisplay()
{
gotoxy(1,6);
cout<<"               |   |   ";
cout<<"\n             "<<board[0][0]<<" | "<<board[0][2]<<" | "<<board[0][4];
cout<<"\n            ___|___|___";
cout<<"\n               |   |   ";
cout<<"\n             "<<board[1][0]<<" | "<<board[1][2]<<" | "<<board[1][4];
cout<<"\n            ___|___|___";
cout<<"\n               |   |   ";
cout<<"\n             "<<board[2][0]<<" | "<<board[2][2]<<" | "<<board[2][4];
cout<<"\n               |   |   ";

}

void putval(int x)
{
if (x>=48&&x<=57)
{
if (x=='0')
exit(0);
else if (x=='1')
{
if (board[0][0]!='x'&&board[0][0]!='o')
{
board[0][0]='x';
flag=2;
}
else
flag=0;
}
else if (x=='2')
{
if (board[0][2]!='x'&&board[0][2]!='o')
{
board[0][2]='x';
flag=2;
}
else
flag=0;
}
else if (x=='3')
{
if (board[0][4]!='x'&&board[0][4]!='o')
{
board[0][4]='x';
flag=2;
}
else
flag=0;
}
else if (x=='4')
{
if (board[1][0]!='x'&&board[1][0]!='o')
{
board[1][0]='x';
flag=2;
}
else
flag=0;
}
else if (x=='5')
{
if (board[1][2]!='x'&&board[1][2]!='o')
{
board[1][2]='x';
flag=2;
}
else
flag=0;
}
else if (x=='6')
{
if (board[1][4]!='x'&&board[1][4]!='o')
{
board[1][4]='x';
flag=2;
}
else
flag=0;
}
else if (x=='7')
{
if (board[2][0]!='x'&&board[2][0]!='o')
{
board[2][0]='x';
flag=2;
}
else
flag=0;
}
else if (x=='8')
{
if (board[2][2]!='x'&&board[2][2]!='o')
{
board[2][2]='x';
flag=2;
}
else
flag=0;
}
else if (x=='9')
{
if (board[2][4]!='x'&&board[2][4]!='o')
{
board[2][4]='x';
flag=2;
}
else
flag=0;
}
}
else
{
clrscr();
tictactoedisplay();
gotoxy(46,12);cout<<"Invalid Character '"<<pos1<<"'";
gotoxy(44,13);cout<<"Enter position again : ";
pos1=getchar();
fflush(stdin);
putval(pos1);
}
}

void putval1(int x)
{
if (x>=48&&x<=57)
{
if (x=='0')
exit(0);
else if (x=='1')
{
if (board[0][0]!='o'&&board[0][0]!='x')
{
board[0][0]='o';
flag=2;
}
else
flag=0;
}
else if (x=='2')
{
if (board[0][2]!='o'&&board[0][2]!='x')
{
board[0][2]='o';
flag=2;
}
else
flag=0;
}
else if (x=='3')
{
if (board[0][4]!='o'&&board[0][4]!='x')
{
board[0][4]='o';
flag=2;
}
else
flag=0;
}
else if (x=='4')
{
if (board[1][0]!='o'&&board[1][0]!='x')
{
board[1][0]='o';
flag=2;
}
else
flag=0;
}
else if (x=='5')
{
if (board[1][2]!='o'&&board[1][2]!='x')
{
board[1][2]='o';
flag=2;
}
else
flag=0;
}
else if (x=='6')
{
if (board[1][4]!='o'&&board[1][4]!='x')
{
board[1][4]='o';
flag=2;
}
else
flag=0;
}
else if (x=='7')
{
if (board[2][0]!='o'&&board[2][0]!='x')
{
board[2][0]='o';
flag=2;
}
else
flag=0;
}
else if (x=='8')
{
if (board[2][2]!='o'&&board[2][2]!='x')
{
board[2][2]='o';
flag=2;
}
else
flag=0;
}
else if (x=='9')
{
if (board[2][4]!='o'&&board[2][4]!='x')
{
board[2][4]='o';
flag=2;
}
else
flag=0;
}
}
else
{
clrscr();
tictactoedisplay();
gotoxy(46,12);cout<<"Invalid Character '"<<pos2<<"'";
gotoxy(44,13);cout<<"Enter position again : ";
pos2=getchar();
fflush(stdin);
putval1(pos2);
}
}


void checkwin()
{
int t;
if (board[0][0]==board[1][2] && board[0][0]==board[2][4])
{
if (board[0][0]=='x')
win=1;
else if (board[0][0]=='o')
win=2;
}
else if (board[0][4]==board[1][2] && board[0][4]==board[2][0])
{
if (board[0][4]=='x')
win=1;
else if (board[0][4]=='o')
win=2;
}
else if (board[0][0]==board[0][2] && board[0][0]==board[0][4])
{
if (board[0][0]=='x')
win=1;
else if (board[0][0]=='o')
win=2;
}
else if (board[1][0]==board[1][2] && board[1][0]==board[1][4])
{
if (board[1][0]=='x')
win=1;
else if (board[1][0]=='o')
win=2;
}
else if (board[2][0]==board[2][2] && board[2][0]==board[2][4])
{
if (board[2][0]=='x')
win=1;
else if (board[2][0]=='o')
win=2;
}
else if (board[0][0]==board[1][0] && board[0][0]==board[2][0])
{
if (board[0][0]=='x')
win=1;
else if (board[0][0]=='o')
win=2;
}
else if (board[0][2]==board[1][2] && board[0][2]==board[2][2])
{
if (board[0][2]=='x')
win=1;
else if (board[0][2]=='o')
win=2;
}
else if (board[0][4]==board[1][4] && board[0][4]==board[2][4])
{
if (board[0][4]=='x')
win=1;
else if (board[0][4]=='o')
win=2;
}
else
{
for (i=0;i<3;i++)
  {
   for (j=0;j<5;)
    {
     if (board[i][j]!='x'&&board[i][j]!='o')
      {
       win=0;
       break;
      }
     else
      {
       win=3;
       j=j+2;
      }
    }
  }
}
}

void tictactoe()
{
clrscr();
char k='1';  win=0;
for (i=0;i<3;i++)
  {
   for (j=0;j<5;j=j+2)
    {
     board[i][j]=k;
     k+=1;
    }
  }
gotoxy(26,6);cout<<"Enter name of player 1 with 'x'";
gotoxy(39,8);gets(n1);
fflush(stdin);
gotoxy(26,10);cout<<"Enter name of player 2 with 'o'";
gotoxy(39,12);gets(n2);
fflush(stdin);
int i;
do
{
flag=0;
while (flag==0)
{
clrscr();
tictactoedisplay();
gotoxy(35,1);cout<<"TIC-TAC-TOE";
gotoxy(50,8);cout<<"Enter Position";
float q;
q=strlen(n1);
q/=2;
if (strlen(n1)%2==0)
{gotoxy((57-q),10);cout<<n1;}
else
{gotoxy((58-q),10);cout<<n1;}
gotoxy(57,12);pos1=getch();
while (pos1==13)
{
gotoxy(57,12);pos1=getch();
}
putval(pos1);
checkwin();
for (i=0;i<3;i++)
{
for (j=0;j<5;j++)
{
if (board[i][j]!='x'&&board[i][j]!='o')
board[i][j]=' ';
}
}
}
if (win!=0)
break;
flag=0;
while (flag==0)
{
clrscr();
tictactoedisplay();
gotoxy(35,1);cout<<"TIC-TAC-TOE";
gotoxy(50,8);cout<<"Enter Position";
float q;
q=strlen(n2);
q/=2;
if (strlen(n2)%2==0)
{gotoxy((57-q),10);cout<<n2;}
else
{gotoxy((58-q),10);cout<<n2;}
gotoxy(57,12);pos2=getch();
while (pos2==13)
{
gotoxy(57,12);pos2=getch();
}
putval1(pos2);
checkwin();
}
}
while (win==0);
clrscr();
tictactoedisplay();
gotoxy(35,1);cout<<"TIC-TAC-TOE";
for (i=0;i<strlen(n1);i++)
n1[i]=toupper(n1[i]);
for (i=0;i<strlen(n2);i++)
n2[i]=toupper(n2[i]);
if (win==1)
{gotoxy(35,16);cout<<n1<<" WINS!!";}
else if (win==2)
{gotoxy(35,16);cout<<n2<<" WINS!!";}
else if (win==3)
{gotoxy(35,16);cout<<"IT'S A DRAW!!";}
getch();
main();
}

//----------------------------------------------------------------------------
//------------------------------Lucky-7---------------------------------------


struct person
{
char name[25],guess;
int point;
void init() {point=0;};
} player[100];

int pbet,bet;

void lucky7tutorial()
{
clrscr();
cout<<"                                           TUTORIAL\n";
cout<<"You have 100 credits available to you and you have to achieve a target by winning. Your target is "<<pbet<<" as entered by you. Try and";
cout<<" guess the correct place of the number that comes out and you can double or triple your bet that you place and that will be added to your credit.";
cout<<" You will have 3 choices, higher or lower or equal to seven. For higher or lower, you will double your bet and for equal you will triple it. Go on, try your luck!";
cout<<"\n                                  Press any key to start";
getch();
}

void play1()
{      row=5;
       player[1].init();
       i=1;
       clrscr();
       player[1].point=100;
       gotoxy(10,8);cout<<"Enter your proposed target (Target should be greater than 100)";
       gotoxy(40,10);cin>>pbet;
       while (pbet<=100)
       {
       play1();
       }
       clrscr();
       gotoxy(30,9);cout<<"Do you want a tutorial?";
       gotoxy(35,11);cout<<"Enter y/n : ";
       cin>>ch;
       if (ch=='y')
       {lucky7tutorial();}
       clrscr();
       gotoxy(32,9);cout<<"All The Best To You!!";
      delay(1500);
do
{
player[1].guess=' ';
clrscr();
gotoxy(13,20);cout<<"Balance : "<<player[1].point<<"      ";
       gotoxy(53,20);cout<<"Target  : "<<pbet<<"      ";
       gotoxy(1,1);
num=random(12-2)+2;
cout<<"                                    Round "<<i;
cout<<"\n                     The Computer has generated a number. ";
cout<<"\n            Enter 'H' for higher, 'L' for lower and 'E' for equal";
while (player[1].guess!='h'&&player[1].guess!='e'&&player[1].guess!='l'&&player[1].guess!='H'&&player[1].guess!='L'&&player[1].guess!='E')
{
gotoxy(40,4);player[1].guess=getch();
}
player[1].guess=toupper(player[1].guess);
gotoxy(40,4);cout<<player[1].guess;
cout<<"\n\n                             Enter your bet : ";
gotoxy(47,6);cin>>bet;
while (bet>player[1].point)
{
gotoxy(47,6);cout<<"                                              ";
gotoxy(47,6);cin>>bet;
}
player[1].point=player[1].point-bet;
cout<<"\n                            And the number is....";
delay(1500);
if (num>7 && player[1].guess=='h'||num<7 && player[1].guess=='l')
{
cout<<num<<"\n                                   You won!";
player[1].point=player[1].point+(bet*2);
}
else if (num==7 && player[1].guess=='e')
{
cout<<num<<"\n                                   You won! ";
player[1].point=player[1].point+(bet*3);
}
else
cout<<num<<"\n                                   You lost!\n";
i++;
gotoxy(13,20);cout<<"Balance :"<<player[1].point<<"   ";
gotoxy(53,20);cout<<"Target  :"<<pbet<<"    ";
if (player[1].point>=pbet)
{
gotoxy(1,11);cout<<"                                    You Win!!";
getch();
ch='n';
}
if (player[1].point<=0)
{gotoxy(13,20);cout<<"Balance :"<<player[1].point<<"      ";
gotoxy(1,14);cout<<"                                   You Lose!!";
getch();
main();  }
if (ch!='n'||player[1].point<=pbet&&player[1].point>0)
{
gotoxy(13,20);cout<<"Balance :"<<player[1].point<<"   ";
gotoxy(53,20);cout<<"Target  :"<<pbet<<"    ";
gotoxy(1,11);cout<<"                                  Play Again?";
cout<<"\n                                 Enter y/n : ";
cin>>ch;
}
}
while (ch!='n'&&player[1].point<=pbet&&player[1].point>0);
if (player[1].point<=0||player[1].point<=pbet)
{gotoxy(13,20);cout<<"Balance :"<<player[1].point<<"      ";
gotoxy(1,14);cout<<"                                   You Lose!!";  }
getch();
main();
}



void lucky7()
{
randomize();
clrscr();

gotoxy(29,8);cout<<"Enter number of players";
gotoxy(40,10);cin>>n;
if (n<1||n>10)
{
gotoxy(11,12);cout<<"Oops! Incorrect value. Please press any key to enter again...";
getch();
lucky7();
}
if (n==1)
{
play1();
exit(0);
}

for (i=0;i<n;i++)
{
gotoxy(33,12+i);cout<<"Player "<<i+1<<" : ";
gets(player[i].name);
fflush(stdin);
player[i].init();
}
round=1;
do
{
clrscr();
cout<<"                                   Round "<<round;
cout<<"\n                     The Computer has generated a number.";
cout<<"\n            Enter 'H' for higher, 'L' for lower and 'E' for equal\n";

for (i=0;i<n;i++)
{
player[i].guess=' ';
}

for (i=0,row=5;i<n;i++,row++)
{
gotoxy(34,row);cout<<player[i].name<<setw(10-strlen(player[i].name))<<": ";
length=strlen(player[i].name)+2;
while (player[i].guess!='h'&&player[i].guess!='e'&&player[i].guess!='l'&&player[i].guess!='H'&&player[i].guess!='L'&&player[i].guess!='E')
{
gotoxy(44,row);player[i].guess=getch();
}
player[i].guess=toupper(player[i].guess);
gotoxy(44,row);cout<<player[i].guess;
cout<<endl;
}

cout<<"\n\n                            And the number is....";
delay(1000);
num=random(12)+1;

cout<<num<<"\n";
for (i=0;i<n;i++)
{
   player[i].guess=tolower(player[i].guess);
   if (num>7 && player[i].guess=='h'||num==7 && player[i].guess=='e'||num<7 && player[i].guess=='l')
	{
	player[i].point += 1;
	   for (j=0;j<n;j++)
		{
		if (tolower(player[j].guess)==player[i].guess)
			{
			if (i!=j)
			 {
			  flag=1;
			 }
			}
		else
			{
			flag=0;
			break;
			}
		}
	if (flag==1)
	{
	cout<<"                                Everybody Won!!";
	for (j=0;j<n;j++)
	{
	if (i!=j)
	player[j].point +=1;
	}
	break;
	}
	else
	{
	  cout<<"                                "<<player[i].name;
	   for (j=0;j<n;j++)
	     {
	       if (tolower(player[j].guess)==player[i].guess)
	       {
		if (i!=j)
		{
		 player[j].point +=1;
		 cout<<", "<<player[j].name;
		}
	       }
	     }
	  cout<<" Won!!";

	break;
	}
    }
    else
    flag=2;
}
if (flag==2)
cout<<"                                  Nobody Won!!";
getch();
cout<<"\n\n                                  Point Tally\n";
for (i=0;i<n;i++)
{
cout<<"                                 "<<player[i].name<<setw(12-strlen(player[i].name))<<": "<<player[i].point;
cout<<endl;
}
round++;
cout<<"\n                                  Play again?";
cout<<"\n                                 Enter y/n : ";
cin>>ch;
}while (ch!='n');
max=0;
for (i=0;i<n;i++)
{
for (j=0;j<n;j++)
{
if (player[j].point>player[i].point)
max=j;
}
}
int flag1=1;
for (i=0;i<n;i++)
{
for (j=0;j<n;j++)
{
if (player[j].point==player[max].point)
{
if (stricmp(player[j].name,player[max].name)!=0)
{
flag1=0;
cout<<endl<<"                                  It's a tie!";
getch();
main();
}
}
}
}
if (flag1!=0)
cout<<endl<<"                                 "<<player[max].name<<" wins!!";
getch();
main();
}

//--------------------------------------------------------------------
//--------------------------------MAIN--------------------------------

void main()
{
textcolor(LIGHTGRAY);
win=0;
clrscr();
gotoxy(28,8);cout<<"Welcome To 4 in 1 Games!!!!";
gotoxy(32,9);cout<<"Choose your option - ";
gotoxy(35,11);cout<<"1.Mastermind";
gotoxy(35,12);cout<<"2.Lucky 7";
gotoxy(35,13);cout<<"3.Hangman";
gotoxy(35,14);cout<<"4.Tic-Tac-Toe";
gotoxy(35,15);cout<<"5.Exit";
gotoxy(33,17);cout<<"Enter Choice : ";
cin>>choice;
switch (choice)
{
case 1:n=2;
       flag=0;
       row=0;
       mastermind();
       break;
case 2:row=5;
       lucky7();
       break;
case 3:flag=0;
       hangman();
       break;
case 4:tictactoe();
       break;
case 5:clrscr();
       gotoxy(28,10);cout<<"Thank you for visiting!!!";
       delay(2000);
       exit(0);
default:gotoxy(13,19);cout<<"Oops! Wrong Choice. Please press any key to enter again...";
	getch();
	main();

}
}
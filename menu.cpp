#include<graphics.h>
#include<iostream>
#include<sstream>

#include <conio.h>


using namespace std;


void color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}

void gotoxy(int x, int y)
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}


void loaad(){
		initwindow(600,500,"Loading",150,50);
	int text_width=textwidth("Loading...");
	int text_height=textheight("Loading...");
	int x=600/2-text_width/2;
	int y=500/2-text_height/2-20;
	int n=1;
	int page=0;
	while(n<=101)
	{
		setactivepage(page);
		setvisualpage(1-page);
		cleardevice();
	
	 outtextxy(x,y,"Loading...");
	 rectangle(600/2-101,500/2-2,600/2+102,500/2+20+2);
	 stringstream s;
	 s<<n<<'%';
	 char ch[5];
	 s>>ch;
	 outtextxy(600/2-20,500/2+30,ch);
	 for(int i=1;i<=n*2;i++)
	 {
	 	line(600/2-100+i,500/2,600/2-100+i,500/2+20);
	 }
	 n++;
	page=1-page;
	delay(100);
	
	}
	
	system("cls");
	
	int Set[] = {7,7,7,7,7,8,9}; 
    int counter = 3;
    char key;
     cout<<"------------Welcome To Weather App--------\n"<<endl;
        
        cout<<"\t\tweather data from api "<<endl;
        cout<<"\n";
        
        cout<<"---------MENU--------------- \n"<<endl;

    for(int i=0;;)
    {

		 //gotoxy(10,5);
        
       
		
        gotoxy(10,5);
        color(Set[0]);
        cout<<"1. Show Weather Info";

        gotoxy(10,6);
        color(Set[1]);
        cout<<"2. Show Weather At Address";

        gotoxy(10,7);
        color(Set[2]);
        cout<<"3. Edit Save Location";

        gotoxy(10,8);
        color(Set[3]);
        cout<<"4. Exit";

       

        key = _getch();

        if(key == 72 && (counter >=2 && counter <= 5))
        {
            counter--;
        }
        if(key == 80 && (counter >=1 && counter <= 4))
        {
            counter++;
        }
        if(key == '\r')
        {
            if(counter == 1)
            {
                
                cout<<"Menu 1 Function";
            }
            if(counter == 2)
            {
                cout<<"Menu 2 Function";
            }
            if(counter == 3)
            {
                cout<<"Menu 3 Function";
            }
            if(counter == 4)
            {
                exit(0);
            }
            
        }

        Set[0] = 7;
        Set[1] = 7;
        Set[2] = 7;
        Set[3] = 7;
        Set[4] = 7;

        if(counter == 1)
        {
            Set[0] = 12;
        }
        if(counter == 2)
        {
            Set[1] = 12;
        }
        if(counter == 3)
        {
            Set[2] = 12;
        }
        if(counter == 4)
        {
            Set[3] = 12;
        }
        if(counter == 5)
        {
            Set[4] = 12;
        }


    }

	getch();

	closegraph();
	
}


 // Loading bar //
int main()
{
	loaad();
//	system("cls");
//	menu();
}

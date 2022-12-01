#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <vector>  
#include <ctime>

using namespace std;

class mydate
{
public:
	int hours;
	int minutes ;
    int day;
    int month;
    int year;


	mydate()
	{
		hours = 0;
		minutes =0;
		day = 0;
		month = 0;
		year =0 ;
	}
	


	void generateDate()
{
		time_t t = std::time(0);   // get time now
		tm* now = std::localtime(&t);
		year = (now->tm_year + 1900) ;
		month = (now->tm_mon + 1) ;
		day = (now->tm_mday) ;
		hours = (now->tm_hour ) ;
		minutes = (now->tm_min ) ;

}

	string printdate()
	{
		char s[50];
		sprintf(s,"%d\\%d\\%d  %d:%d",day,month,year,hours,minutes);
		return (string) s;
	}
};


class report								// da el ms2ol 3n el reciept
{
public:
								// gwah eh ??

	mydate date [5] ;							   // a5r 5 twari5 
	string TType[5];							  // 5 mn el transaction tyb ( deposite or withdraw )
	int mBefore[5] ;                             //5 mn money befor
	int mAfter[5] ;								// 5 mn money  after
	int amount[5] ;							   // amount entered in transaction
	int size;								  // 3dad el transactions

	report()
	{
		size=0;				// ana msfro 3shan a2dr atl3 el 3mlyat eli et3mlt bs , say 2 trans.s
	}
	
	void fill(string t , int a ,int mb ,int ma)  // function ht5zen fl report
	{											// ba5od mno el ttype , amount , money befor and after 
		
		if(size< 5)		// lw el size a2l mn 5 , hyd5ol b2a mn awl el size=0 w y7ot el cins eli ana bd5lha
		{               // w hyfdl yzwed l7d ma hywsl l size=5
					      

			TType[size] = t ;						
			amount[size] = a ;
			date[size].generateDate();
			mBefore[size]= mb;
			mAfter[size]= ma;

			size++;

		}

		else
		{									// lw b2a el size>5 , el mtlop hna in ana a3ml shift b2a ll sizes
											// y3ni hy7ot size 1 fl 0 , w hakza b2a 3shan ytl3 a5r 5 bs

			for(int i=1 ; i<5 ;i++)
			{
				TType[i-1]= TType[i];
				amount[i-1] = amount[i] ;
				date[i-1]= date[i] ;
				mBefore[i-1]= mBefore[i];
				mAfter[i-1]= mAfter[i];
			}
			// l7d ma ywsl b2a l7d 4 ( a5r mkan fl array ) ,
			//y3mlha shift w tt7at f 3 w yigy el size el gdid yt7tbfl4
			TType[4]= t;    
			amount[4] = a ;
			date[4].generateDate();
			mBefore[4] = mb;
			mAfter[4] = ma;

			
		}

	}


	void print()
	{
					// hy3ml loop 3lehom klhom l7d ma ywsl ll size , lw homa 5 hytb3 l7d size 4
					
		ofstream op("transactions.txt"); // op da esmo  , of stream 3shan aft7 file w a save gwah
		if(size>0)
		{
			op << "Type \t\t" << "Amount \t" << "Date \t\t" << "Before \t" << "After \n" ;

			for(int i =0 ;i<size ;i++)
			{
				op << TType[i] <<"\t" << amount[i] <<"\t" << date[i].printdate() <<"\t" << mBefore[i] <<"\t" <<mAfter[i] << "\n" ;
			}
		}

		else
			cout<< "no history \n";
	}
	
};


class empreport 
{		// da 3shan ytl3 b2a kol el transactions eli 7slt fl youm kolo 
public:

	vector <mydate> date  ;
	vector<string> TType;
	vector<string> Uname;
	vector<int> mBefore;
	vector<int> mAfter;
	vector<int> amount;
	int size;

	empreport()
	{
		size=0;
	}
	
	void fill(string t , int a ,int mb ,int ma ,string un ) // btmla file el empreport
	{
		mydate temp;				// push_back : 3shan y2dr yd5l fl vector el data

			TType.push_back(t) ;
			amount.push_back(a) ;
			temp.generateDate();
			date.push_back(temp);
			mBefore.push_back(mb);
			mAfter.push_back(ma);
			Uname.push_back(un);

			size++;


	}


	void print()		// 3shan ytb3 fl file "Wholetransactions.txt"
	{
		ofstream op("Wholetransactions.txt");
		if(size>0)
		{
			op << "Type \t\t" << "Amount \t" << "Date \t\t" << "Before \t"<< "After \t" << "Name \n" ;

			for(int i =0 ;i<size ;i++)
			{
				op << TType[i] <<"\t" << amount[i] <<"\t" << date[i].printdate() <<"\t" << mBefore[i] <<"\t" <<mAfter[i] <<"\t" <<Uname[i] << "\n" ;
			}
		}

		else  // lw el size =0 da m3nah in el user m3mlsh ay trans 
			cout<< "no history \n";
	}
	
};

empreport WholeReport ;

class client  // hwa hwa el struct bs da 3amali aktar
{
public:          // m3naha eni ha3raf anadi el 7agat de fel main
	string name;
	string username;
	string password;
	double money ;
	report myreport ;

	void deposit(int amount)
	{
		money += amount ;
		myreport.fill("Deposit " ,amount,money-amount ,money);
		WholeReport.fill("Deposit " ,amount,money-amount ,money,username);
	}

	void withdraw(int amount)
	{
		if (amount<= money)
		{
			money -= amount ;
			myreport.fill("Withdraw" ,amount ,money+amount ,money);
			WholeReport.fill("Withdraw" ,amount ,money+amount ,money,username);
		}
		else 
			cout << "there's no enough money \n" ;
	}
};


class employee
{
public:
	string name;
	string username ;
	string password ;
	double money;
	bool available ;

};

template<class T>
void parsingFile(ifstream & infile , T &user)
{
	int i=0;
	string mo ;
	while (infile.good()&& i<6) ///.good() ya3ni el file lesa ma5elsh 
	{
		getline(infile,user[i].name,' ');
		getline(infile,user[i].username,' ');
		getline(infile,user[i].password,' ');
		getline(infile,mo,'\n');
		user[i].money= stoi(mo); // stod == string to double
		i++;
	}
}


int main()
{

	mydate date ;
	vector <employee> emp (6) ;
	vector <client> cli (6) ;
	client CurrentCli;
	employee CurrentEmp;
	string userNameEntered,nameIn,passEntered;
	char ch ;
	bool loggedInEmp = 0 , loggedInCli = 0;
	int count =0 ;
	ifstream in_client("client.txt");

	ifstream in_employee("employee.txt");

	parsingFile(in_client , cli);
	parsingFile(in_employee, emp);
	
	startingPoint:
	loggedInEmp = 0 ; 
	loggedInCli = 0;
	passEntered.clear();

	system("CLS");

	date.generateDate();
	cout<< date.printdate() <<endl ;

	cout<<"Welcome to ATM \n";
	cout<<"Please Enter your Username \n";
	cin>>userNameEntered;
	cout <<endl;

	tryagain:
	cout<<"Enter your Password" ;
	cout <<endl;

	ch = _getch();
	while(ch != 13) //character 13 is enter
	{
      passEntered.push_back(ch); // ya3ni bydef 3la el string
	  if(ch != 8)
       cout << '*';
      ch = _getch();
	}
	cout <<endl;

	
	for(int i=0 ; i<emp.size() ;i++)
	{
		if(userNameEntered == emp[i].username)
			if(passEntered == emp[i].password)
				{
					loggedInEmp = 1 ;
					nameIn = emp[i].name;
					CurrentEmp =emp[i] ;
				}
	}

	for(int i=0 ; i< cli.size() ;i++)
	{
		if(userNameEntered == cli[i].username)
			if(passEntered == cli[i].password)
			{
				loggedInCli = 1 ;
				nameIn = cli[i].name ;
				CurrentCli =cli[i] ;
			}
	}

	int typeOFEnq;
	if(loggedInCli == 1)
	{
		int xxx = 0;
		cout<<"welcome Client " << nameIn << endl;
		do
		{
			xxx = 0;
			cout<<" For : \n  deposit enter 0 \n  Withdraw enter 1 \n  Enquiry enter 2\n";
			cin>> typeOFEnq;
			if(typeOFEnq == 0)
			{
				int amountt ;
				cout <<"Enter amount of Money \n";
				cin >> amountt;
				CurrentCli.deposit(amountt);
				cout<< "your money now = " <<CurrentCli.money <<endl;
				CurrentCli.myreport.print();

				ofstream off_client("client.txt");

				for (int i = 0; i < cli.size(); i++)
				{
					if(cli[i].username != CurrentCli.username)
						off_client << cli[i].name<< " " << cli[i].username <<" " << cli[i].password << " " << cli[i].money <<endl ;
					else if (cli[i].username == CurrentCli.username)
					{
						cli[i]  = CurrentCli;
						off_client << cli[i].name<< " " << cli[i].username <<" " << cli[i].password << " " << cli[i].money <<endl ;
					}
				}

			}

			else if(typeOFEnq == 1)
			{
				int amountt ;
				cout <<"Enter amount of Money Or press 0 to logout  \n";
				cin >> amountt;
				CurrentCli.withdraw(amountt);
				CurrentCli.myreport.print();
				cout<< "your money now = " <<CurrentCli.money <<endl;

				ofstream off_client("client.txt");

				for (int i = 0; i < cli.size(); i++)
				{
					if(cli[i].username != CurrentCli.username)
						off_client << cli[i].name<< " " << cli[i].username <<" " << cli[i].password << " " << cli[i].money <<endl ;
					else if (cli[i].username == CurrentCli.username)
					{
						cli[i]  = CurrentCli;
						off_client << cli[i].name<< " " << cli[i].username <<" " << cli[i].password << " " << cli[i].money <<endl ;
					}
				}

			}

			else if(typeOFEnq == 2)
			{
				cout<< "your money now = " <<CurrentCli.money <<endl;
				CurrentCli.myreport.print();
			}

			cout << "for one more operation press 1 Or press 0 to logout  \n";
			cin>> xxx;
		} 
		while(xxx == 1);
		xxx = 0;
		if(xxx== 0)
			goto startingPoint;

	}

	
	else if(loggedInEmp == 1 )
	{
		int yyy= 0;
		cout<<"welcome Employee " << nameIn << endl;
		cout<<"your recipt is printed " << endl;
		WholeReport.print();

		cout<<"Press anything to logout " << endl;
		cin>>yyy;
		goto startingPoint ;
	}

	else
	{
		cout<<"wrong Password or Username " << endl;
		count++;

		if(count<3)
		{
			passEntered.clear();
			goto tryagain ; 
		}
		else
			cout<<"Failed to login" <<endl;
	}

	return 0;
	
}
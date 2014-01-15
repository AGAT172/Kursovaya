#include <iostream>
#include <winsock2.h>
 #include <conio.h>
using namespace std;
int matches=27;
void draw(int n){
	cout<<n<<'\t';
	for(int i=0;i<n;i++)
		cout<<'|'<<' ';
	cout<<endl;
}
int step(int d){
	if(d<5){
		if((matches-d)>=0){
			matches-=d;
			return matches;
		}
		else{
			cout<<"there is no more matches"<<endl;
			return -1;
		}
	}
	else {
		cout<<"Fuck you, cheater!"<<endl;
		return 0;
	}
	return matches;
}

int main()
{
    WORD ver = MAKEWORD(2,2);
    WSADATA wsaData;
    int retVal=0;
    WSAStartup(ver,(LPWSADATA)&wsaData);
    LPHOSTENT hostEnt;
    hostEnt = gethostbyname("localhost");
    if(!hostEnt)
    {
        cout<<"Unable to collect gethostbyname\n";
        WSACleanup();
        return 1;
    }
    //Создаем сокет
    SOCKET clientSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(clientSock == SOCKET_ERROR)
    {
        cout<<"Unable to create socket\n";
        WSACleanup();
        return 1;
    }
    SOCKADDR_IN serverInfo;
    serverInfo.sin_family = PF_INET;
    serverInfo.sin_addr = *((LPIN_ADDR)*hostEnt->h_addr_list);
    serverInfo.sin_port = htons(1111);
    retVal=connect(clientSock,(LPSOCKADDR)&serverInfo, sizeof(serverInfo));
    if(retVal==SOCKET_ERROR)
    {
        cout<<"Unable to connect\n";
        WSACleanup();
        return 1;
    }
    cout<<"Connection made sucessfully\nYOU ARE PLAYER#1"<<endl;
	while(1){
		char pBuf[8];
		int d=0, res,y=0;;
		draw(matches);
		cout<<"Your turn\n";
		cin>>d;
		while(step(d)<=0){
			if(matches==0){
				cout<<"PLAYER#2 WIN! YOU ARE LOSER! YOUR COCK IS SMALLER=)"<<endl;
				itoa(d,pBuf,10);
				retVal = send(clientSock, pBuf, strlen(pBuf), 0);//посылка хода
				goto out;
			}
			else{
				cout<<"Your turn\n";
				cin>>d;
			}
		}
		cout<<"Sending request...\n";
		itoa(d,pBuf,10);
		retVal = send(clientSock, pBuf, strlen(pBuf), 0);//посылка хода
		draw(matches);
		char cBuf[8];
		recv(clientSock, cBuf, 8, 0);//получение хода//retVal = ;
		cout<<"Got the request...>>"<<cBuf[0]<<endl;
		step(cBuf[0]-'0');
		if(matches==0){
			cout<<"PLAYER#1 WIN! Congratulations!"<<endl;
			goto out;
		}
	}
out:
	getch();
    closesocket(clientSock);
    WSACleanup();
	getch();
    return 0;
}
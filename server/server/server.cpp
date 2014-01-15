#include <winsock2.h>
#include <conio.h>
#include <iostream>
using namespace std;

void draw(int n){
	cout<<n<<'\t';
	for(int i=0;i<n;i++)
		cout<<'|'<<' ';
	cout<<endl;
}
int matches=27;
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

int main(void)
{
    WORD sockVer;
    WSADATA wsaData;
    int retVal; 
    sockVer = MAKEWORD(2,2);
     WSAStartup(sockVer, &wsaData);
     //Создаем сокет
    SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
     if(servSock == INVALID_SOCKET)
    {
        cout<<"Unable to create socket\n";
        WSACleanup();
        return SOCKET_ERROR;
    }
	SOCKADDR_IN sin;
    sin.sin_family = PF_INET;
    sin.sin_port = htons(1111);
    sin.sin_addr.s_addr = INADDR_ANY;
     retVal = bind(servSock, (LPSOCKADDR)&sin, sizeof(sin));//y
    if(retVal == SOCKET_ERROR)
    {
        cout<<"Unable to bind\n";
        WSACleanup();
        return SOCKET_ERROR;
    }
     //Пытаемся начать слушать сокет
    retVal = listen(servSock, 10);
    if(retVal == SOCKET_ERROR)
    {
        cout<<"Unable to listen\n";
        WSACleanup();
        return SOCKET_ERROR;
    }
    //Ждем клиента
    SOCKET clientSock;
    clientSock = accept(servSock, NULL, NULL);
    if(clientSock == INVALID_SOCKET)
    {
        cout<<"Unable to accept\n";
        WSACleanup();
        return SOCKET_ERROR;
    }
	cout<<"Connection made sucessfully\nYOU ARE PLAYER#2"<<endl;
	while(1){
		char pBuf[8];
		draw(matches);
		retVal = recv(clientSock, pBuf, 8, 0);////////////
		cout<<"Got the request>>";
		cout<<pBuf[0]<<endl;
		step(pBuf[0]-'0');
		if(matches==0){
				cout<<"PLAYER#2 WIN! Congratulations!"<<endl;
				goto out;
		}
		draw(matches);
		if(retVal == SOCKET_ERROR)
		{
			cout<<"Unable to recv\n";
			return SOCKET_ERROR;
		}
		char cBuf[8];
		int t=0,res;
		cout<<"You turn\n";
		cin>>t;
		while(step(t)<=0){
			if(matches==0){
				cout<<"PLAYER#1 WIN! YOU ARE LOSER! YOUR COCK IS SMALLER=)"<<endl;
				itoa(t,cBuf,10);
				retVal = send(clientSock, cBuf, strlen(cBuf), 0);
				goto out;
			}
			else{
				cout<<"Your turn\n";
				cin>>t;
			}
		}
		cout<<"Sending request...\n";
		itoa(t,cBuf,10);
		retVal = send(clientSock, cBuf, strlen(cBuf), 0);
 		if(retVal == SOCKET_ERROR)
		{
			cout<<"Unable to send\n";
			WSACleanup();
			return 1;
		}
	}
out:
	getch();
     //Закрываем сокет
    closesocket(clientSock);
    closesocket(servSock);
 
    WSACleanup();
    return 0;
	getch();
}
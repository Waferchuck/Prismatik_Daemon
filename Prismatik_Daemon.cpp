// Prismatik_Daemon.cpp : This application will first read in the COM port number from main.conf 
// and then keeps monitoring the COM status in backgroud and restart the Prismatik.exe if COM is avaliable.

#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup")
#include<windows.h>
#include<stdio.h>

using namespace std;

extern int read_conf_COM_port_string(char** port_num);


void restart_prismatic(void)
{
    system("taskkill /f /t /im Prismatik.exe");
    printf("Prismatik.exe has been killed\nRestarting \n");
    Sleep(3000);
    ShellExecute(NULL, L"open", L"C:\\Program Files\\Prismatik\\Prismatik.exe", NULL, NULL, SW_SHOW);
    HINSTANCE ShellExecute(
        HWND hwnd,
        LPCTSTR lpOperation,
        LPCTSTR lpFile,
        LPCTSTR lpParameters,
        LPCTSTR lpDirectory,
        INT nShowCmd
    );
    printf("\nPrismatik.exe has been restarted \n");
}

int main()
{
    HANDLE hComm;

    //char port_name[256] = "\\\\\\\\.\\\\";
    char port_name[256] = "\\\\.\\";
    char* port_str_read = NULL;
    if (read_conf_COM_port_string(&port_str_read) == 0)
    {
        printf("read back port_str is %s\n", port_str_read);
        strcat(port_name, port_str_read);
    }
    else
    {
        printf("Error readin main.conf, EXIT");
        return 1;
    }
    printf("full port_str is %s\n", port_name);

    while (true)
    {

        hComm = CreateFileA(port_name,  //port name
            GENERIC_READ | GENERIC_WRITE,   //Read/Write
            0,                              // No Sharing
            NULL,                           // No Security
            OPEN_EXISTING,                  // Open existing port only
            0,                              // Non Overlapped I/O
            NULL);                          // Null for Comm Devices

        if (hComm == INVALID_HANDLE_VALUE)
            printf("Cannot open port %s, probably in use or does not exist\n", port_str_read);
        else
        {
            printf("opening %s successfully, port idle, kick off Prismatik.exe\n", port_str_read);
            CloseHandle(hComm);//free the port
            Sleep(2000);
            restart_prismatic();
        }

        Sleep(3000); //check every 3 seconds
    }

    return 0;
}



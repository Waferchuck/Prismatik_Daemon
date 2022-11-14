// get_port_number.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <windows.h>
#include <stdio.h>
#include "./ini.h"

#pragma comment(lib, "Advapi32.lib")

typedef struct
{
    int device;
    const char* serial_number;
} configuration;

static int handler(void* user, const char* section, const char* name,
    const char* value)
{
    configuration* pconfig = (configuration*)user;

#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    if (MATCH("Adalight", "SerialPort")) {
        pconfig->serial_number = _strdup(value);
    }
    else {
        return 0;
    }
    return 1;
}

int read_conf_COM_port_string(char** port_num)
{

    char* user_name = getenv("username");
    // printf("user name is %s \n", user_name);
    char main_conf_path[256];
    strcpy(main_conf_path, "C:\\Users\\");
    strcat(main_conf_path, user_name);
    strcat(main_conf_path, "\\Prismatik\\main.conf");
    printf("main.conf path is %s \n", main_conf_path);

    configuration config;

    if (ini_parse(main_conf_path, handler, &config) < 0) {
        printf("Can't load '%s\n", main_conf_path);
        return 1;
    }
    //printf("Config loaded from %s : serial_number is %s\n", main_conf_path, config.serial_number);
    *port_num = (char*)malloc(100);
    strcpy(*port_num, config.serial_number);
    return 0;

}

int test()
{
    //int port_number;
    //read_conf_COM_port_value(&port_number);
    char* port_str = NULL;
    read_conf_COM_port_string(&port_str);
    //printf("return is %d\n", port_number);
    printf("return str is %s\n", port_str);
    return 0;
}


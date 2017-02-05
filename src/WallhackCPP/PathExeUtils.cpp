#include <windows.h>
#include <stdio.h>
#include <string.h>

#include "PathExeUtils.h"

void StringWithoutExtension(const char* pathToExe, char* output)
{
    int i;
    for(i = strlen(pathToExe); i >= 0; i--)
    {
        if(pathToExe[i] == '.')
        {
            strcpy(output, pathToExe);
            output[i] = '\0';
            break;
        }
    }
}

void GetExecutablePathName(char* output, unsigned int maxLength)
{
    HMODULE hModule = GetModuleHandle(NULL);
    if (hModule != NULL)
    {
        GetModuleFileNameA(hModule,output, maxLength);
    }
}

void GetCurrentDirectoryName(char* output, unsigned int maxLength)
{
    HMODULE hModule = GetModuleHandle(NULL);
    int i;

    if (hModule != NULL)
    {
        GetModuleFileNameA(hModule,output, maxLength);
    }

    for(i = strlen(output); i >= 0 && output[i] != '\\'; i--);
    if(i > 0)
    {
        output[i] = '\0';
    }
}

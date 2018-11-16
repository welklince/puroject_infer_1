#pragma once

#include<Windows.h>

class Error
{
public:
    static void showDialog( const char* Message )
    {
        MessageBox(
            NULL,
            Message,
            "Error",
            MB_OK | MB_ICONERROR
        );
    }
};
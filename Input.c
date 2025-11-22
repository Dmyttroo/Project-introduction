#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

#define Size 4
#define WinCondition 2048

void Scan(int game[Size][Size]) {
    int keyPressed = 0;
    while (!keyPressed) {
        if (GetAsyncKeyState('W') & 0x8000 || GetAsyncKeyState(VK_UP) & 0x8000) {
            InputW(game);
            keyPressed = 1;
            while (GetAsyncKeyState('W') & 0x8000 || GetAsyncKeyState(VK_UP) & 0x8000)
                Sleep(50);
        }
        else if (GetAsyncKeyState('A') & 0x8000 || GetAsyncKeyState(VK_LEFT) & 0x8000) {
            InputA(game);
            keyPressed = 1;
            while (GetAsyncKeyState('A') & 0x8000 || GetAsyncKeyState(VK_LEFT) & 0x8000)
                Sleep(50);
        }
        else if (GetAsyncKeyState('S') & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000) {
            InputS(game);
            keyPressed = 1;
            while (GetAsyncKeyState('S') & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000)
                Sleep(50);
        }
        else if (GetAsyncKeyState('D') & 0x8000 || GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            InputD(game);
            keyPressed = 1;
            while (GetAsyncKeyState('D') & 0x8000 || GetAsyncKeyState(VK_RIGHT) & 0x8000)
                Sleep(50);
        }
        Sleep(50);
    }
}

void InputW(int arr[Size][Size]) {
    for (int j = 0; j < Size; j++) {
        int line[Size];
        for (int i = 0; i < Size; i++)
            line[i] = arr[i][j];

        Logic(line);

        for (int i = 0; i < Size; i++)
            arr[i][j] = line[i];
    }
}

void InputA(int arr[Size][Size]) {
    for (int i = 0; i < Size; i++) {
        Logic(arr[i]);
    }
    
}

void InputS(int arr[Size][Size]) {
    for (int j = 0; j < Size; j++) {
        int line[Size];
        for (int i = 0; i < Size; i++)
            line[i] = arr[Size - i - 1][j];

        Logic(line);

        for (int i = 0; i < Size; i++)
            arr[Size - 1 - i][j] = line[i];
    }
}

void InputD(int arr[Size][Size]) {
    for (int i = 0; i < Size; i++) {
        int line[Size];

        for (int j = 0; j < Size; j++)
            line[j] = arr[i][Size - 1 - j];

        Logic(line);

        for (int j = 0; j < Size; j++)
            arr[i][Size - 1 - j] = line[j];
    }
}
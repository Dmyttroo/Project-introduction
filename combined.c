#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

#define Size 4
#define WinCondition 2048

void InputW(int arr[Size][Size]);
void InputA(int arr[Size][Size]);
void InputS(int arr[Size][Size]);
void InputD(int arr[Size][Size]);


int getColor(int value) { //ASCI colors 256 palette
    switch (value) {
        case 2: return 229; // світло-жовтий
        case 4: return 222; // пісочний 
        case 8: return 220; // жовтий 
        case 16: return 216; // світло-оранжевий
        case 32: return 208; // помаранчевий
        case 64: return 202; // темно-оранжевий
        case 128: return 196; // червоний
        case 256: return 160; // темно-червоний
        case 512: return 125; // рожевий 
        case 1024: return 93; // фіолетовий
        case 2048: return 56; // темно-фіолетовий
        default: return 236; // темно-сірий для пустих клітинок
    }
}

void Print(int arr[Size][Size]) {
    for (int i = 0; i < Size; i++) {
        for (int j = 0; j < Size; j++) {
            int color = getColor(arr[i][j]);
            printf("\033[48;5;%d;38;5;0m", color); // колір фону
            if (arr[i][j] == 0)
                printf("       "); // порожня клітинка
            else
                printf(" %4d  ", arr[i][j]);
            printf("\033[0m "); // скидання кольору + відступ
         }
        printf("\n\n");
    }
    printf("\033[0m");
}

void ClearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

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

void FlushKeyboard() {
    while (_kbhit()) {
        _getch();
    }
}

void Logic(int line[Size]) {
    int temp[Size] = {0};
    int pos = 0;

    for (int i = 0; i < Size; i++) {
        if (line[i] != 0)
            temp[pos++] = line[i];
    }

    for (int i = 0; i < Size - 1; i++) {
        if (temp[i] != 0 && temp[i] == temp[i+1]) {
            temp[i] *= 2;
            temp[i+1] = 0;
        }
    }

    int merged[Size] = {0};
    pos = 0;
    for (int i = 0; i < Size; i++) {
        if (temp[i] != 0)
            merged[pos++] = temp[i];
    }

    for (int i = 0; i < Size; i++)
        line[i] = merged[i];
}

void RandomNumber(int arr[Size][Size]) {
    int x, y;
    do {
        x = rand() % Size;
        y = rand() % Size;
    } while (arr[x][y] != 0);

    int RandomNumberValue = rand() % 100;
    int RandomInput;
    if (RandomNumberValue < 90) {
        RandomInput = 2;
    } else {
        RandomInput = 4;
    }
    arr[x][y] = RandomInput;
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

int Status(int arr[Size][Size]) {
    for (int i = 0; i < Size; i++)
        for (int j = 0; j < Size; j++)
            if (arr[i][j] == WinCondition)
                return 2;
    for (int i = 0; i < Size; i++)
        for (int j = 0; j < Size; j++)
            if (arr[i][j] == 0)
                return 1;
    return 0;
}

int main() {
    srand(time(NULL));
    int game[Size][Size] = {0};

    for (int i = 0; i < 2; i++) RandomNumber(game);

    while (1) {
        ClearScreen();
        Print(game);

        int status = Status(game);
        if (status == 2) {
            printf("Game won!\n");
            break;
        }
        if (status == 0) {
            printf("Game over!\n");
            break;
        }

        Scan(game);
       RandomNumber(game);
    }
    printf("Press any key to exit...\n");
    FlushKeyboard();
    _getch();
    return 0;
}
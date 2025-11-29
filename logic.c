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

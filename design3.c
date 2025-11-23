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
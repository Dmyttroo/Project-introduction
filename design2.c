void Print(int arr[Size][Size]) {
    for (int i = 0; i < Size; i++) {
        for (int j = 0; j < Size; j++) {
            int color = getColor(arr[i][j]);
            printf("\033[48;5;%d;38;5;0m", color); 
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
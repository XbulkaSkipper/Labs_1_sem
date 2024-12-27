#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <float.h>
#include <time.h>

void random_number(int n) {
    srand(time(NULL));
    FILE *file = fopen("lab3(10).bin", "wb+"); // открытие файла
    if (file == NULL) {
        fprintf(stderr, "Ошибка открытия файла!\n");
        exit(1);
    }

    // запись рандомных чисел в файл
    for (int i = 0; i < n; i++) {
        float num = (float)rand() / (float)RAND_MAX * 200 - 100; //[-100;100]
        fprintf(file, "%.2f\n", num);
    }
    fclose(file);
}

void eigen_number(int n) {
    // открываем файл
    FILE *file = fopen("lab3(10).bin", "wb+");
    if (file == NULL) {
        fprintf(stderr, "Ошибка открытия файла!\n");
        exit(1);
    }

    // записываем числа
    printf("Введите числа:\n");
    for(int i = 0; i < n; i++) {
        float num;
        if(scanf("%f", &num) != 1) {
            fprintf(stderr, "Ошибка! Необходимо вводить вещественные числа!!!\n");
            exit(1);
        }
        fprintf(file, "%.2f\n", num);
    }
    fclose(file);
}

void change_file(float min_num, float sum, int place) {
    FILE *file = fopen("lab3(10).bin", "rb+");
    if (file == NULL) {
        fprintf(stderr, "Ошибка открытия файла!\n");
        exit(1);
    }

    // Сначала считываем все данные в массив
    float numbers[100];
    int count = 0;
    while (fscanf(file, "%f", &numbers[count]) == 1 && count < 100) {
        count++;
    }
    fclose(file);

    // Открываем файл для записи
    file = fopen("lab3(10).bin", "wb");
    if (file == NULL) {
        fprintf(stderr, "Ошибка открытия файла!\n");
        exit(1);
    }

    // Записываем все числа обратно в файл
    for (int i = 0; i < count; i++) {
        if (i == place) {
            fprintf(file, "%.2f\n", sum); // Записываем сумму квадратов вместо минимального числа
        }
        fprintf(file, "%.2f\n", numbers[i]);
    }
    fclose(file);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    int choice;

    // узнаем кол-во чисел
    float n;
    printf("Сколько чисел хотите записать?: ");
    scanf("%f", &n);

    if ((int)n != n || n < 0) {
        fprintf(stderr, "Ошибка! Введите положительное целое число!\n");
        return 1;
    }

    printf("Как создаем файл:\n 1) Рандом \n 2) Самостоятельный ввод \n");
    printf("Ваш выбор: ");
    scanf("%d", &choice);

    n = (int)n;
    switch (choice) {
        case 1:
            random_number(n);
            break;
        case 2:
            eigen_number(n);
            break;
        default:
            fprintf(stderr,"Ошибка! Необходимо выбрать 1 или 2!\n");
            return 1;
    }

    FILE *file = fopen("lab3(10).bin", "rb");

    if (file == NULL) {
        fprintf(stderr, "Ошибка открытия файла!\n");
        return 1;
    }

    // ищем исходники для редактирования файла
    int count = 0;

    float min_num = FLT_MAX;
    float sum = 0.0f;
    float num;

    while(fscanf(file, "%f", &num) == 1) {
        count++;
        sum += num * num;

        if(num < min_num) {
            min_num = num;
        }
    }

   fclose(file);

   file = fopen("lab3(10).bin", "r+");

   int place = -1;

   for(int i = 0; i < count; i++) {
       fscanf(file, "%f", &num);
       if(min_num == num && place == -1) {
           place = i;
           break;
       }
   }

   fclose(file);

   change_file(min_num, sum, place); // Изменяем файл

   return 0;
}

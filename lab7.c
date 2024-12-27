#include <stdio.h>
#include <string.h>
#include <windows.h>

int check_num(const char *word)
{
    while (*word) {
        if (!isdigit(*word)) {
            return 0; // Если хотя бы один символ не является цифрой,вернуть0
        }
        word++;
    }
    return 1;
}

int main(void) {
    SetConsoleOutputCP(CP_UTF8);

    char words[331]; //создаем массив
    printf("Введите строку:");
    fgets(words,331,stdin); //записываем в массив строчки

    // нет точки - БАН
    if(strchr(words,'.') == 0) {
        printf("ERROR");
        return 1;
    }

    // проверка на кол-во слов
    int k = 0;
    int count_words = 1;
    while(words[k+1] != '.') {
        if(words[k] != ' ' && words[k+1] == ' ') {
            count_words++;
        }
        k++;
    }
    if(count_words > 30) {
        printf("ERROR");
        return 1;
    }


    // замена точки на конец
    for (int i = 0; i <= strlen(words); i++) {
        if (words[i] == '.') {
            words[i] = '\0';
            break; // Добавляем break, чтобы прекратить цикл при первой точке
        }
    }

    char *string = strtok(words, " ");

    while(string != NULL) // находим строки из цифр и выводим их
    {
        // проверка на кол-во букв в слове
        if(strlen(string) > 10) {
            printf("ERROR\n");
            return 1;
        }
        // проверка на посторонние символы
        if(strpbrk(string,"!@$%^&*()~-*/+?><{}][:;,") != 0) {
            printf("ERROR\n");
            return 1;
        }
        else {
            if(check_num(string))  //проверка состоит ли слово из цифр
            {
                printf("(%s) ", string); //окружаем слово скобками и выводим его
            }
            string = strtok(NULL, " "); //получаем следующее слово
        }
    }
    printf(".\n"); //добавляем точку в конце вывода


    return 0;
}

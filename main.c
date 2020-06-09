#define MAX_STRING_LENGTH 100
#define MAX_NUMBER_OF_BOOKS 5000

#include <stdio.h>
#include <windows.h>

// Структура книги
struct book{
    long long isbn;
    char author[MAX_STRING_LENGTH];
    char title[MAX_STRING_LENGTH];
    int number;
    int available;
};

int count_num_books(char name[]);

int main() {
    SetConsoleOutputCP(CP_UTF8);
    struct book books[MAX_NUMBER_OF_BOOKS];
    char name[] = "D:/bmstu_inf/sem2-DZ/books.csv";
    int num_books = count_num_books(name); // количество книг
    FILE *fp;
    fp = fopen(name, "r");
    // запись книг в массив
    for(int i =0; i<num_books;++i){
        char buff1[100] ={0};
        int n =0;
        char ch;
        while((ch =fgetc(fp)) !=';'){
            buff1[n] = ch;
            n++;
        }
        books[i].isbn = atoll(buff1);

        char buff2[100] ={0};
        n=0;
        while((ch =fgetc(fp)) != ';'){
            buff2[n] = ch;
            n++;
        }
        strcat(books[i].author,buff2);

        char buff3[100] ={0};
        n = 0;
        while((ch =fgetc(fp)) != ';'){
            buff3[n] = ch;
            n++;
        }
        strcat(books[i].title,buff3);

        char buff4[100] = {0};
        n=0;
        while((ch =fgetc(fp)) !=';'){
            buff4[n] = ch;
            n++;
        }
        books[i].number = atoi(buff4);

        char buff5[100] = {0};
        n=0;
        while((ch =fgetc(fp)) !='\n'){
            buff5[n] = ch;
            n++;
        }
        books[i].available = atoi(buff5);
    }
    fclose(fp);

    // Меню
    int action;
    do {
        printf("Menu:\n");
        printf("1 - Добавить новую книгу\n");
        printf("2 - Удалить книгу по номеру ISBN\n");
        printf("5 - Редактировать информацию о книге\n");
        printf("6 - Изменить количество книг в библиотеке по номеру ISBN\n");
        printf("12 - Завершить работу\n");
        scanf("%d", &action);


        if (action == 1) { // добавление новой книги
            printf("Ведите ISBN новой книги:");
            long long isbn_to_check;
            int check;
            do {
                check = 0;
                scanf("%lld", &isbn_to_check);
                for (int i = 0; i < num_books; ++i) {
                    if (isbn_to_check == books[i].isbn) {
                        check = 1;
                        break;
                    }
                }
                if(check == 1) {
                    printf("Книга с этим номером ISBN уже существует.\n");
                    printf("Ввведите другой номер:");
                }
            }while(check == 1);
            char author[MAX_STRING_LENGTH];
            char title[MAX_STRING_LENGTH];
            int num;
            printf("Введите авторов книги:");
            scanf("%s",author);
            printf("Ввведите название книги:");
            scanf("%s",title);
            printf("Введите количество книг");
            scanf("%d",&num);
            books[num_books].isbn = isbn_to_check;
            strcat(books[num_books].author,author);
            strcat(books[num_books].title,title);
            books[num_books].number = num;
            books[num_books].available =num;
            num_books++;
            putchar('\n');
        }

        if(action == 2){ // удаление по номеру isbn
            long long isbn;
            int check = 0;
            int num_of_delete;
            printf("Введите ISBN книги для удаления:");
            scanf("%lld",&isbn);
            for(int i =0; i<num_books;++i){ // поиск номера книги в массиве с данным isbn
                if(isbn == books[i].isbn){
                    check = 1;
                    num_of_delete = i;
                }
            }
            if(check == 0){
                printf("Книги с введенным ISBN нет в базе данных.\n");
                continue;
            }
            if(num_of_delete == num_books-1){
                num_books--;
                continue;
            }
            for(int i = num_of_delete; i<num_books-1;++i){
                books[i] = books[i+1];
            }
            num_books--;
        }

        // редактировать информацию о книге
        if(action == 5){
            long long isbn;
            printf("Введите ISBN книги для редактирования:");
            scanf("%lld",&isbn);
            int book_to_edit;
            for(int i =0; i<num_books;++i){ // поиск книги с данным isbn
                if(isbn == books[i].isbn){
                    book_to_edit = i;
                    break;
                }
            }
            char new_author[MAX_STRING_LENGTH];
            char new_title[MAX_STRING_LENGTH];
            printf("Введите новых авторов книги:");
            scanf("%s",new_author);
            printf("Введите новое название книги:");
            scanf("%s",new_title);
            strcpy(books[book_to_edit].author,new_author);
            strcpy(books[book_to_edit].title,new_title);
            putchar('\n');
        }
        // изменить количество книг в библиотеке по номеру ISBN
        if(action == 6){
            long long isbn;
            printf("Введите ISBN книги для изменения ее количества:");
            scanf("%lld",&isbn);
            int book_to_edit;
            for(int i =0; i<num_books;++i){ // поиск книги с данным isbn
                if(isbn == books[i].isbn){
                    book_to_edit = i;
                    break;
                }
            }
            int n;
            printf("Введите новое количетсво доступных экзапляров данной книги:");
            scanf("%d",&n);
            if(n> books[book_to_edit].number){
                printf("\nКоличество доступных книг не может быть больше общего количества.\n");
                continue;
            }
            books[book_to_edit].available = n;
            putchar('\n');

        }
    }while(action != 12);

    // Открытие файла для записи
    fp = fopen(name, "w");
    for(int i =0;i<num_books;++i){
        fprintf(fp,"%lld;%s;%s;%d;%d\n",books[i].isbn,books[i].author,books[i].title,books[i].number,books[i].available);
    }
    fclose(fp);

    return 0;
}

int count_num_books(char name[]){ // подсчет количества книг в файле
    FILE *fp;
    fp = fopen(name, "r");
    int num_books = 0;
    char c;
    while((c = fgetc(fp)) != EOF){
        if(c == '\n'){
            num_books++;
        }
    }
    fclose(fp);
    return num_books;
}
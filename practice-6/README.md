Практическая работа 6 Структуры и объединения

**Студент:** Смирнов Артём Валерьевич
**Группа:** ИВТ-123
**Дата:** 15 января 2026 г.

Задание 6.1: Адресная книга
Создайте систему управления контактами.

### Код программы

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <windows.h>
    
    // Типы телефонов
    typedef enum {
        PHONE_HOME,
        PHONE_MOBILE,
        PHONE_WORK
    } PhoneType;
    
    // Структура телефона
    typedef struct {
        PhoneType type;
        char number[20];
    } Phone;
    
    // Структура даты
    typedef struct {
        int day;
        int month;
        int year;
    } Date;
    
    // Структура контакта
    typedef struct {
        char first_name[30];
        char last_name[30];
        char email[50];
        Phone phones[3];   // до 3 телефонов
        int phone_count;   // сколько реально заполнено
        Date birthday;
    } Contact;
    
    // Адресная книга
    typedef struct {
        Contact contacts[100];
        int count;
    } AddressBook;
    
    // Инициализация книги
    void book_init(AddressBook *book) {
        book->count = 0;
        
    }
    
    // Добавление контакта (0 - успех, -1 - ошибка)
    int book_add(AddressBook *book, const Contact *contact) {
        if (book->count >= 100) return -1;
        book->contacts[book->count] = *contact;
        book->count++;
        return 0;
    }
    
    // Поиск по фамилии (возвращает индекс первого найденного, иначе -1)
    int book_find_by_lastname(const AddressBook *book, const char *lastname) {
        for (int i = 0; i < book->count; i++) {
            if (strcmp(book->contacts[i].last_name, lastname) == 0)
                return i;
        }
        return -1;
    }
    
    // Поиск по email
    int book_find_by_email(const AddressBook *book, const char *email) {
        for (int i = 0; i < book->count; i++) {
            if (strcmp(book->contacts[i].email, email) == 0)
                return i;
        }
        return -1;
    }
    
    // Удаление контакта по индексу (0 - успех, -1 - ошибка)
    int book_remove(AddressBook *book, int index) {
        if (index < 0 || index >= book->count) return -1;
        // Сдвигаем остальные влево
        for (int i = index; i < book->count - 1; i++) {
            book->contacts[i] = book->contacts[i + 1];
        }
        book->count--;
        return 0;
    }
    
    // Вывод всех контактов
    void book_print(const AddressBook *book) {
        if (book->count == 0) {
            printf("Адресная книга пуста.\n");
            return;
        }
        for (int i = 0; i < book->count; i++) {
            const Contact *c = &book->contacts[i];
            printf("%d. %s %s\n", i + 1, c->first_name, c->last_name);
            printf("   Email: %s\n", c->email);
            printf("   Телефоны:\n");
            for (int p = 0; p < c->phone_count; p++) {
                const char *type_str;
                switch (c->phones[p].type) {
                    case PHONE_HOME:   type_str = "Домашний"; break;
                    case PHONE_MOBILE: type_str = "Мобильный"; break;
                    case PHONE_WORK:   type_str = "Рабочий"; break;
                    default:           type_str = "Неизвестный";
                }
                printf("      [%s] %s\n", type_str, c->phones[p].number);
            }
            printf("   День рождения: %02d.%02d.%04d\n\n",
                   c->birthday.day, c->birthday.month, c->birthday.year);
        }
    }
    
    // Вывод контактов с днём рождения в указанном месяце
    void book_print_birthdays(const AddressBook *book, int month) {
        int found = 0;
        for (int i = 0; i < book->count; i++) {
            const Contact *c = &book->contacts[i];
            if (c->birthday.month == month) {
                printf("%s %s (%02d.%02d)\n",
                       c->first_name, c->last_name,
                       c->birthday.day, c->birthday.month);
                found = 1;
            }
        }
        if (!found) {
            printf("Нет контактов с днём рождения в этом месяце.\n");
        }
    }
    
    // Сортировка по фамилии (простой пузырёк)
    void book_sort_by_lastname(AddressBook *book) {
        for (int i = 0; i < book->count - 1; i++) {
            for (int j = 0; j < book->count - i - 1; j++) {
                if (strcmp(book->contacts[j].last_name,
                           book->contacts[j + 1].last_name) > 0) {
                    Contact tmp = book->contacts[j];
                    book->contacts[j] = book->contacts[j + 1];
                    book->contacts[j + 1] = tmp;
                }
            }
        }
    }
    
    // ========== Демонстрация работы ==========
    int main() {
        SetConsoleOutputCP(65001); 
        SetConsoleCP(65001);

    AddressBook myBook;
    book_init(&myBook);

    // Создаём несколько контактов
    Contact c1 = {
        .first_name = "Михаил",
        .last_name = "Петров",
        .email = "petrov@email.com",
        .phone_count = 2,
        .phones = {
            {PHONE_MOBILE, "+7-999-123-4567"},
            {PHONE_WORK,   "+7-495-123-4567"}
        },
        .birthday = {15, 3, 1990}
    };
    Contact c2 = {
        .first_name = "Мария",
        .last_name = "Сергеева",
        .email = "sidorova@email.com",   
        .phone_count = 1,
        .phones = {
            {PHONE_HOME, "+7-495-987-6543"}
        },
        .birthday = {22, 7, 1985}
    };
    Contact c3 = {
        .first_name = "Анна",
        .last_name = "Иванова",
        .email = "ivanova@mail.ru",
        .phone_count = 1,
        .phones = {
            {PHONE_MOBILE, "+7-916-111-2233"}
        },
        .birthday = {10, 3, 1995}
    };

    book_add(&myBook, &c1);
    book_add(&myBook, &c2);
    book_add(&myBook, &c3);

    printf("=== Адресная книга ===\n\n");
    book_print(&myBook);

    printf("\n=== Поиск по фамилии 'Сергеева' ===\n");
    int idx = book_find_by_lastname(&myBook, "Сергеева");
    if (idx != -1)
        printf("Найден контакт: %s %s\n",
               myBook.contacts[idx].first_name,
               myBook.contacts[idx].last_name);
    else
        printf("Не найден\n");

    printf("\n=== Контакты с днём рождения в марте (месяц 3) ===\n");
    book_print_birthdays(&myBook, 3);

    printf("\n=== Удаляем контакт с индексом 1 (Мария Сергеева) ===\n");
    book_remove(&myBook, 1);
    book_print(&myBook);

    printf("\n=== Сортировка по фамилии ===\n");
    book_sort_by_lastname(&myBook);
    book_print(&myBook);

    return 0;
    }

Задание 6.2: Геометрические фигуры (Tagged Union)
Реализуйте систему для работы с различными геометрическими фигурами.

### Код программы

Задание 6.3: Выражения калькулятора (AST)
Реализуйте структуру данных для представления математических выражений.

### Код программы

Задание 6.4: Система сообщений (Protocol Buffers style)
Реализуйте систему обмена сообщениями различных типов.

### Код программы

Задание 6.5: Битовые флаги
Реализуйте систему прав доступа с использованием битовых полей и флагов.

### Код программы

Задание 6.6: Конечный автомат
Реализуйте конечный автомат для разбора простого языка.

### Код программы

# Контрольные вопросы

## 1 Почему sizeof(struct) может быть больше суммы размеров полей?

sizeof(struct) больше суммы полей – из-за выравнивания: процессор быстрее читает данные по адресам, кратным размеру типа, поэтому компилятор добавляет пустые байты между полями.

## 2 Что такое padding и как его минимизировать?

Padding – пустые байты для выравнивания. Минимизация: располагать поля по убыванию размера (сначала double, потом int, потом char).

## 3 В чём отличие struct от union?

struct – каждое поле хранится отдельно (все сразу). union – поля используют одну память (только одно значение в момент времени).

## 4 Зачем нужен тег в tagged union?

Тег в tagged union – показывает, какое поле объединения сейчас активно, чтобы безопасно к нему обращаться.

## 5 Можно ли взять адрес битового поля?

Адрес битового поля взять нельзя – оно может занимать не целый байт, а несколько битов внутри байта.



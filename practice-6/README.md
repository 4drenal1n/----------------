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

    #define _USE_MATH_DEFINES
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include <stdbool.h>
    #include <windows.h>
    
    
    // Типы фигур 
    typedef enum {
        SHAPE_POINT,
        SHAPE_CIRCLE,
        SHAPE_RECTANGLE,
        SHAPE_TRIANGLE,
        SHAPE_POLYGON
    } ShapeType;
    
    // Точка
    typedef struct {
        double x, y;
    } Point;
    
    // Круг
    typedef struct {
        Point center;
        double radius;
    } Circle;
    
    // Прямоугольник
    typedef struct {
        Point top_left;
        double width, height;
    } RectShape;
    
    // Треугольник
    typedef struct {
        Point a, b, c;
    } Triangle;
    
    // Многоугольник
    typedef struct {
        Point *vertices;  // динамический массив
        int count;
    } PolyShape;
    
    // Размеченное объединение (tagged union)
    typedef struct {
        ShapeType type;
        union {
            Point point;
            Circle circle;
            RectShape rectangle;
            Triangle triangle;
            PolyShape polygon;
        } data;
    } Shape;
    
    // Конструкторы 
    Shape shape_point(double x, double y) {
        Shape s;
        s.type = SHAPE_POINT;
        s.data.point.x = x;
        s.data.point.y = y;
        return s;
    }
    
    Shape shape_circle(double cx, double cy, double radius) {
        Shape s;
        s.type = SHAPE_CIRCLE;
        s.data.circle.center.x = cx;
        s.data.circle.center.y = cy;
        s.data.circle.radius = radius;
        return s;
    }
    
    Shape shape_rectangle(double x, double y, double w, double h) {
        Shape s;
        s.type = SHAPE_RECTANGLE;
        s.data.rectangle.top_left.x = x;
        s.data.rectangle.top_left.y = y;
        s.data.rectangle.width = w;
        s.data.rectangle.height = h;
        return s;
    }
    
    Shape shape_triangle(Point a, Point b, Point c) {
        Shape s;
        s.type = SHAPE_TRIANGLE;
        s.data.triangle.a = a;
        s.data.triangle.b = b;
        s.data.triangle.c = c;
        return s;
    }
    
    Shape shape_polygon(Point *verts, int count) {
        Shape s;
        s.type = SHAPE_POLYGON;
        s.data.polygon.count = count;
        s.data.polygon.vertices = (Point*)malloc(count * sizeof(Point));
        for (int i = 0; i < count; i++)
            s.data.polygon.vertices[i] = verts[i];
        return s;
    }
    
    // Освобождение памяти для полигона
    void shape_free(Shape *s) {
        if (s->type == SHAPE_POLYGON) {
            free(s->data.polygon.vertices);
            s->data.polygon.vertices = NULL;
            s->data.polygon.count = 0;
        }
    }
    
    
    static double point_distance(Point a, Point b) {
        double dx = a.x - b.x;
        double dy = a.y - b.y;
        return sqrt(dx*dx + dy*dy);
    }
    
    static double triangle_area(Point a, Point b, Point c) {
        return fabs((a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y)) / 2.0);
    }
    
    static double triangle_perimeter(Point a, Point b, Point c) {
        return point_distance(a, b) + point_distance(b, c) + point_distance(c, a);
    }
    
    static Point triangle_center(Point a, Point b, Point c) {
        Point center = {(a.x + b.x + c.x)/3.0, (a.y + b.y + c.y)/3.0};
        return center;
    }
    
    static double polygon_area(Point *verts, int n) {
        double area = 0.0;
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            area += verts[i].x * verts[j].y;
            area -= verts[j].x * verts[i].y;
        }
        return fabs(area) / 2.0;
    }
    
    static double polygon_perimeter(Point *verts, int n) {
        double perim = 0.0;
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            perim += point_distance(verts[i], verts[j]);
        }
        return perim;
    }
    
    static Point polygon_center(Point *verts, int n) {
        Point c = {0.0, 0.0};
        for (int i = 0; i < n; i++) {
            c.x += verts[i].x;
            c.y += verts[i].y;
        }
        c.x /= n;
        c.y /= n;
        return c;
    }
    
    //Основные функции фигур 
    double shape_area(const Shape *s) {
        switch (s->type) {
            case SHAPE_POINT:      return 0.0;
            case SHAPE_CIRCLE:     return M_PI * s->data.circle.radius * s->data.circle.radius;
            case SHAPE_RECTANGLE:  return s->data.rectangle.width * s->data.rectangle.height;
            case SHAPE_TRIANGLE:   return triangle_area(s->data.triangle.a, s->data.triangle.b, s->data.triangle.c);
            case SHAPE_POLYGON:    return polygon_area(s->data.polygon.vertices, s->data.polygon.count);
            default:               return 0.0;
        }
    }
    
    double shape_perimeter(const Shape *s) {
        switch (s->type) {
            case SHAPE_POINT:      return 0.0;
            case SHAPE_CIRCLE:     return 2.0 * M_PI * s->data.circle.radius;
            case SHAPE_RECTANGLE:  return 2.0 * (s->data.rectangle.width + s->data.rectangle.height);
            case SHAPE_TRIANGLE:   return triangle_perimeter(s->data.triangle.a, s->data.triangle.b, s->data.triangle.c);
            case SHAPE_POLYGON:    return polygon_perimeter(s->data.polygon.vertices, s->data.polygon.count);
            default:               return 0.0;
        }
    }
    
    Point shape_center(const Shape *s) {
        Point c = {0.0, 0.0};
        switch (s->type) {
            case SHAPE_POINT:
                c = s->data.point;
                break;
            case SHAPE_CIRCLE:
                c = s->data.circle.center;
                break;
            case SHAPE_RECTANGLE: {
                RectShape r = s->data.rectangle;
                c.x = r.top_left.x + r.width/2.0;
                c.y = r.top_left.y - r.height/2.0;
                break;
            }
            case SHAPE_TRIANGLE:
                c = triangle_center(s->data.triangle.a, s->data.triangle.b, s->data.triangle.c);
                break;
            case SHAPE_POLYGON:
                c = polygon_center(s->data.polygon.vertices, s->data.polygon.count);
                break;
        }
        return c;
    }
    
    // Перемещение
    void shape_move(Shape *s, double dx, double dy) {
        switch (s->type) {
            case SHAPE_POINT:
                s->data.point.x += dx;
                s->data.point.y += dy;
                break;
            case SHAPE_CIRCLE:
                s->data.circle.center.x += dx;
                s->data.circle.center.y += dy;
                break;
            case SHAPE_RECTANGLE:
                s->data.rectangle.top_left.x += dx;
                s->data.rectangle.top_left.y += dy;
                break;
            case SHAPE_TRIANGLE:
                s->data.triangle.a.x += dx; s->data.triangle.a.y += dy;
                s->data.triangle.b.x += dx; s->data.triangle.b.y += dy;
                s->data.triangle.c.x += dx; s->data.triangle.c.y += dy;
                break;
            case SHAPE_POLYGON:
                for (int i = 0; i < s->data.polygon.count; i++) {
                    s->data.polygon.vertices[i].x += dx;
                    s->data.polygon.vertices[i].y += dy;
                }
                break;
        }
    }
    
    // Масштабирование относительно центра
    void shape_scale(Shape *s, double factor) {
        Point c = shape_center(s);
        switch (s->type) {
            case SHAPE_POINT:
            
            break;
        case SHAPE_CIRCLE:
            s->data.circle.radius *= factor;
            break;
        case SHAPE_RECTANGLE:
            s->data.rectangle.width *= factor;
            s->data.rectangle.height *= factor;
            
            s->data.rectangle.top_left.x = c.x - s->data.rectangle.width/2.0;
            s->data.rectangle.top_left.y = c.y + s->data.rectangle.height/2.0;
            break;
        case SHAPE_TRIANGLE:
            s->data.triangle.a.x = c.x + (s->data.triangle.a.x - c.x) * factor;
            s->data.triangle.a.y = c.y + (s->data.triangle.a.y - c.y) * factor;
            s->data.triangle.b.x = c.x + (s->data.triangle.b.x - c.x) * factor;
            s->data.triangle.b.y = c.y + (s->data.triangle.b.y - c.y) * factor;
            s->data.triangle.c.x = c.x + (s->data.triangle.c.x - c.x) * factor;
            s->data.triangle.c.y = c.y + (s->data.triangle.c.y - c.y) * factor;
            break;
        case SHAPE_POLYGON:
            for (int i = 0; i < s->data.polygon.count; i++) {
                s->data.polygon.vertices[i].x = c.x + (s->data.polygon.vertices[i].x - c.x) * factor;
                s->data.polygon.vertices[i].y = c.y + (s->data.polygon.vertices[i].y - c.y) * factor;
            }
            break;
    }
    }
    
    // Проверка, содержит ли фигура точку
    int shape_contains_point(const Shape *s, Point p) {
        switch (s->type) {
            case SHAPE_POINT:
                return (p.x == s->data.point.x && p.y == s->data.point.y);
            case SHAPE_CIRCLE: {
                Circle c = s->data.circle;
                double dx = p.x - c.center.x;
                double dy = p.y - c.center.y;
                return (dx*dx + dy*dy <= c.radius * c.radius);
            }
            case SHAPE_RECTANGLE: {
                RectShape r = s->data.rectangle;
                double left = r.top_left.x;
                double right = r.top_left.x + r.width;
                double top = r.top_left.y;
                double bottom = r.top_left.y - r.height;
                double ymin = (top < bottom) ? top : bottom;
                double ymax = (top > bottom) ? top : bottom;
                return (p.x >= left && p.x <= right && p.y >= ymin && p.y <= ymax);
            }
            case SHAPE_TRIANGLE: {
                Triangle t = s->data.triangle;
                double area = triangle_area(t.a, t.b, t.c);
                double a1 = triangle_area(p, t.b, t.c);
                double a2 = triangle_area(t.a, p, t.c);
                double a3 = triangle_area(t.a, t.b, p);
                return fabs(area - (a1 + a2 + a3)) < 1e-9;
            }
            case SHAPE_POLYGON: {
               const PolyShape *poly = &s->data.polygon;
                int inside = 0;
                for (int i = 0, j = poly->count-1; i < poly->count; j = i++) {
                    Point vi = poly->vertices[i];
                    Point vj = poly->vertices[j];
                    if (((vi.y > p.y) != (vj.y > p.y)) &&
                        (p.x < (vj.x - vi.x) * (p.y - vi.y) / (vj.y - vi.y) + vi.x))
                        inside = !inside;
                }
                return inside;
            }
            default: return 0;
        }
    }
    
    // Проверка пересечения двух фигур 
    int shapes_intersect(const Shape *a, const Shape *b) {
        // Если одна из фигур – точка
        if (a->type == SHAPE_POINT) return shape_contains_point(b, a->data.point);
        if (b->type == SHAPE_POINT) return shape_contains_point(a, b->data.point);
        // Круг-круг
        if (a->type == SHAPE_CIRCLE && b->type == SHAPE_CIRCLE) {
          const  Circle *c1 = &a->data.circle;
          const  Circle *c2 = &b->data.circle;
            double dist = point_distance(c1->center, c2->center);
            return dist <= c1->radius + c2->radius;
        }
        // Круг-прямоугольник
        if (a->type == SHAPE_CIRCLE && b->type == SHAPE_RECTANGLE) {
            RectShape r = b->data.rectangle;
            double left = r.top_left.x;
            double right = r.top_left.x + r.width;
            double top = r.top_left.y;
            double bottom = r.top_left.y - r.height;
            double ymin = (top < bottom) ? top : bottom;
            double ymax = (top > bottom) ? top : bottom;
            double cx = a->data.circle.center.x;
            double cy = a->data.circle.center.y;
            double closestX = (cx < left) ? left : (cx > right) ? right : cx;
            double closestY = (cy < ymin) ? ymin : (cy > ymax) ? ymax : cy;
            double dx = cx - closestX;
            double dy = cy - closestY;
            return (dx*dx + dy*dy) <= a->data.circle.radius * a->data.circle.radius;
        }
        if (a->type == SHAPE_RECTANGLE && b->type == SHAPE_CIRCLE)
            return shapes_intersect(b, a);
    
    Point ca = shape_center(a);
    Point cb = shape_center(b);
    return point_distance(ca, cb) < 1e-6; 
    }
    
    // Вывод фигуры
    void shape_print(const Shape *s) {
        switch (s->type) {
            case SHAPE_POINT:
                printf("Точка (%.2f, %.2f)", s->data.point.x, s->data.point.y);
                break;
            case SHAPE_CIRCLE:
                printf("Круг: центр (%.2f, %.2f), радиус %.2f",
                       s->data.circle.center.x, s->data.circle.center.y, s->data.circle.radius);
                break;
            case SHAPE_RECTANGLE:
                printf("Прямоугольник: левый верхний угол (%.2f, %.2f), ширина %.2f, высота %.2f",
                       s->data.rectangle.top_left.x, s->data.rectangle.top_left.y,
                       s->data.rectangle.width, s->data.rectangle.height);
                break;
            case SHAPE_TRIANGLE:
                printf("Треугольник: (%.2f,%.2f) (%.2f,%.2f) (%.2f,%.2f)",
                       s->data.triangle.a.x, s->data.triangle.a.y,
                       s->data.triangle.b.x, s->data.triangle.b.y,
                       s->data.triangle.c.x, s->data.triangle.c.y);
                break;
            case SHAPE_POLYGON:
                printf("Многоугольник (%d вершин)", s->data.polygon.count);
                break;
        }
    }
    
    
    int main() {
        SetConsoleOutputCP(CP_UTF8);
    
    // Круг
    Shape circle = shape_circle(0.0, 0.0, 5.0);
    printf("=== Круг ===\n");
    shape_print(&circle);
    printf("\nПлощадь: %.2f\n", shape_area(&circle));
    printf("Периметр: %.2f\n\n", shape_perimeter(&circle));

    // Прямоугольник
    Shape rect = shape_rectangle(0.0, 0.0, 4.0, 3.0);
    printf("=== Прямоугольник ===\n");
    shape_print(&rect);
    printf("\nПлощадь: %.2f\n", shape_area(&rect));
    printf("Периметр: %.2f\n\n", shape_perimeter(&rect));

    // Треугольник
    Point a = {0.0, 0.0}, b = {4.0, 0.0}, c = {2.0, 3.0};
    Shape triangle = shape_triangle(a, b, c);
    printf("=== Треугольник ===\n");
    shape_print(&triangle);
    printf("\nПлощадь: %.2f\n", shape_area(&triangle));
    printf("Периметр: %.2f\n\n", shape_perimeter(&triangle));

    // Перемещение и масштабирование
    printf("=== Перемещение круга на (1,1) и масштабирование в 2 раза ===\n");
    shape_move(&circle, 1.0, 1.0);
    shape_scale(&circle, 2.0);
    shape_print(&circle);
    printf("\nПлощадь: %.2f\n", shape_area(&circle));
    printf("Новый центр: (%.2f, %.2f)\n\n", shape_center(&circle).x, shape_center(&circle).y);

    // Проверка принадлежности точки
    Point test = {2.0, 2.0};
    printf("Точка (2,2) внутри круга? %s\n", shape_contains_point(&circle, test) ? "да" : "нет");
    printf("Точка (2,2) внутри прямоугольника? %s\n", shape_contains_point(&rect, test) ? "да" : "нет");

    // Проверка пересечения (круг и прямоугольник)
    printf("Круг и прямоугольник пересекаются? %s\n", shapes_intersect(&circle, &rect) ? "да" : "нет");

    
    shape_free(&circle);
    shape_free(&rect);
    shape_free(&triangle);

    return 0;
    }

Задание 6.3: Выражения калькулятора (AST)
Реализуйте структуру данных для представления математических выражений.

### Код программы

    #define _USE_MATH_DEFINES
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include <windows.h>
    #include <stdbool.h>
    
    // Типы выражений
    typedef enum {
        EXPR_NUMBER,
            EXPR_VARIABLE,
            EXPR_ADD,
            EXPR_SUB,
            EXPR_MUL,
            EXPR_DIV,
            EXPR_NEG,    // Унарный минус
            EXPR_SQRT,
            EXPR_POW
        } ExprType;
    
    // Структура выражения (объявление)
    typedef struct Expr Expr;
    
    // Структура выражения (определение)
    struct Expr {
            ExprType type;
            union {
                double number;              // Для EXPR_NUMBER
                char variable;              // Для EXPR_VARIABLE ('x', 'y', ...)
                struct {
                    Expr *left;
                    Expr *right;
                } binary;                   // Для бинарных операций
                Expr *operand;              // Для унарных операций
            } data;
        };
    
    // Контекст для переменных
    typedef struct {
        char name;
        double value;
    } Variable;
    
    typedef struct {
        Variable vars[26];  // a-z
        int count;
    } Context;

    //Конструкторы 
    
    Expr* expr_number(double value) {
        Expr *e = (Expr*)malloc(sizeof(Expr));
        if (!e) return NULL;
        e->type = EXPR_NUMBER;
        e->data.number = value;
        return e;
    }
    
    Expr* expr_variable(char name) {
        Expr *e = (Expr*)malloc(sizeof(Expr));
        if (!e) return NULL;
        // Проверка: имя переменной должно быть буквой a-z или A-Z
        if (!((name >= 'a' && name <= 'z') || (name >= 'A' && name <= 'Z'))) {
            free(e);
            return NULL;
        }
        e->type = EXPR_VARIABLE;
        e->data.variable = name;
        return e;
    }

    Expr* expr_add(Expr *left, Expr *right) {
        if (!left || !right) return NULL;
        Expr *e = (Expr*)malloc(sizeof(Expr));
        if (!e) return NULL;
        e->type = EXPR_ADD;
        e->data.binary.left = left;
        e->data.binary.right = right;
        return e;
    }
    
    Expr* expr_sub(Expr *left, Expr *right) {
        if (!left || !right) return NULL;
        Expr *e = (Expr*)malloc(sizeof(Expr));
        if (!e) return NULL;
        e->type = EXPR_SUB;
        e->data.binary.left = left;
        e->data.binary.right = right;
        return e;
    }
    
    Expr* expr_mul(Expr *left, Expr *right) {
        if (!left || !right) return NULL;
        Expr *e = (Expr*)malloc(sizeof(Expr));
        if (!e) return NULL;
        e->type = EXPR_MUL;
            e->data.binary.left = left;
            e->data.binary.right = right;
            return e;
    }
    
    Expr* expr_div(Expr *left, Expr *right) {
        if (!left || !right) return NULL;
        Expr *e = (Expr*)malloc(sizeof(Expr));
        if (!e) return NULL;
        e->type = EXPR_DIV;
        e->data.binary.left = left;
        e->data.binary.right = right;
        return e;
    }
    
    Expr* expr_neg(Expr *operand) {
        if (!operand) return NULL;
        Expr *e = (Expr*)malloc(sizeof(Expr));
        if (!e) return NULL;
        e->type = EXPR_NEG;
        e->data.operand = operand;
        return e;
        }
    
    Expr* expr_sqrt(Expr *operand) {
        if (!operand) return NULL;
        Expr *e = (Expr*)malloc(sizeof(Expr));
        if (!e) return NULL;
        e->type = EXPR_SQRT;
        e->data.operand = operand;
        return e;
    }
    
    Expr* expr_pow(Expr *base, Expr *exp) {
        if (!base || !exp) return NULL;
        Expr *e = (Expr*)malloc(sizeof(Expr));
        if (!e) return NULL;
        e->type = EXPR_POW;
        e->data.binary.left = base;
        e->data.binary.right = exp;
        return e;
        }
    
    // Контекст 
    
    void context_init(Context *ctx);
    void context_set(Context *ctx, char name, double value);
    double context_get(const Context *ctx, char name);
    
    // Освобождение памяти (объявление)
    void expr_free(Expr *e);
    
    void context_init(Context *ctx) {
        ctx->count = 0;
    }

    void context_set(Context *ctx, char name, double value) {
        // Ищем существующую переменную
        for (int i = 0; i < ctx->count; i++) {
            if (ctx->vars[i].name == name) {
                ctx->vars[i].value = value;
                return;
            }
            }
            // Добавляем новую
            if (ctx->count < 26) {
                ctx->vars[ctx->count].name = name;
                ctx->vars[ctx->count].value = value;
                ctx->count++;
            }
        }
    
    double context_get(const Context *ctx, char name) {
        for (int i = 0; i < ctx->count; i++) {
            if (ctx->vars[i].name == name) {
                return ctx->vars[i].value;
            }
        }
        return 0.0;  // Переменная не найдена
    }
    
    //  Вычисление выражения 
    
    double expr_eval(const Expr *e, const Context *ctx) {
        if (!e || !ctx) return 0.0;
    
    switch (e->type) {
        case EXPR_NUMBER:
            return e->data.number;
        case EXPR_VARIABLE:
            return context_get(ctx, e->data.variable);
        case EXPR_ADD:
            return expr_eval(e->data.binary.left, ctx) + expr_eval(e->data.binary.right, ctx);
        case EXPR_SUB:
            return expr_eval(e->data.binary.left, ctx) - expr_eval(e->data.binary.right, ctx);
        case EXPR_MUL:
            return expr_eval(e->data.binary.left, ctx) * expr_eval(e->data.binary.right, ctx);
        case EXPR_DIV: {
            double denom = expr_eval(e->data.binary.right, ctx);
            if (denom == 0.0) {
                printf("Ошибка: деление на ноль!\n");
                return 0.0;
            }
            return expr_eval(e->data.binary.left, ctx) / denom;
        }
        case EXPR_NEG:
            return -expr_eval(e->data.operand, ctx);
        case EXPR_SQRT: {
            double val = expr_eval(e->data.operand, ctx);
            if (val < 0.0) {
                printf("Ошибка: квадратный корень из отрицательного числа!\n");
                return 0.0;
            }
            return sqrt(val);
        }
        case EXPR_POW:
            return pow(expr_eval(e->data.binary.left, ctx), expr_eval(e->data.binary.right, ctx));
        default:
            return 0.0;
    }
    }
    
    // Вывод выражения 
    
    static void expr_print_recursive(const Expr *e, int precedence) {
        if (!e) return;
    
    int my_prec = 0;

    switch (e->type) {
        case EXPR_NUMBER:
            printf("%.2f", e->data.number);
            return;
        case EXPR_VARIABLE:
            printf("%c", e->data.variable);
            return;
        case EXPR_ADD:
        case EXPR_SUB:
            my_prec = 1;
            break;
        case EXPR_MUL:
        case EXPR_DIV:
            my_prec = 2;
            break;
        case EXPR_NEG:
        case EXPR_SQRT:
            my_prec = 3;
            break;
        case EXPR_POW:
            my_prec = 4;
            break;
        default:
            return;
    }

    int need_parens = (precedence > my_prec);

    if (need_parens) printf("(");

    switch (e->type) {
        case EXPR_ADD:
            expr_print_recursive(e->data.binary.left, my_prec);
            printf(" + ");
            expr_print_recursive(e->data.binary.right, my_prec + 1);
            break;
        case EXPR_SUB:
            expr_print_recursive(e->data.binary.left, my_prec);
            printf(" - ");
            expr_print_recursive(e->data.binary.right, my_prec + 1);
            break;
        case EXPR_MUL:
            expr_print_recursive(e->data.binary.left, my_prec);
            printf(" * ");
            expr_print_recursive(e->data.binary.right, my_prec + 1);
            break;
        case EXPR_DIV:
            expr_print_recursive(e->data.binary.left, my_prec);
            printf(" / ");
            expr_print_recursive(e->data.binary.right, my_prec + 1);
            break;
        case EXPR_NEG:
            printf("-");
            expr_print_recursive(e->data.operand, my_prec);
            break;
        case EXPR_SQRT:
            printf("sqrt(");
            expr_print_recursive(e->data.operand, 0);
            printf(")");
            break;
        case EXPR_POW:
            expr_print_recursive(e->data.binary.left, my_prec);
            printf(" ^ ");
            expr_print_recursive(e->data.binary.right, my_prec + 1);
            break;
        default:
            break;
    }

    if (need_parens) printf(")");
    }
    
    void expr_print(const Expr *e) {
        if (e) expr_print_recursive(e, 0);
    }
    
    // Дифференцирование 
    
    Expr* expr_derivative(const Expr *e, char var) {
        if (!e) return NULL;
    
    switch (e->type) {
        case EXPR_NUMBER:
            // d(c)/dx = 0
            return expr_number(0.0);

        case EXPR_VARIABLE:
            // d(x)/dx = 1, d(y)/dx = 0
            return (e->data.variable == var) ? expr_number(1.0) : expr_number(0.0);

        case EXPR_ADD: {
            // d(f+g)/dx = df/dx + dg/dx
            Expr *dl = expr_derivative(e->data.binary.left, var);
            Expr *dr = expr_derivative(e->data.binary.right, var);
            return expr_add(dl, dr);
        }

        case EXPR_SUB: {
            // d(f-g)/dx = df/dx - dg/dx
            Expr *dl = expr_derivative(e->data.binary.left, var);
            Expr *dr = expr_derivative(e->data.binary.right, var);
            return expr_sub(dl, dr);
        }

        case EXPR_MUL: {
            // d(f*g)/dx = df/dx * g + f * dg/dx (правило произведения)
            Expr *dl = expr_derivative(e->data.binary.left, var);
            Expr *dr = expr_derivative(e->data.binary.right, var);
            Expr *left = expr_mul(dl, e->data.binary.right);
            Expr *right = expr_mul(e->data.binary.left, dr);
            return expr_add(left, right);
        }

        case EXPR_DIV: {
            // d(f/g)/dx = (df*g - f*dg) / g^2 (правило частного)
            Expr *dl = expr_derivative(e->data.binary.left, var);
            Expr *dr = expr_derivative(e->data.binary.right, var);
            Expr *num = expr_sub(expr_mul(dl, e->data.binary.right),
                                  expr_mul(e->data.binary.left, dr));
            Expr *den = expr_mul(e->data.binary.right, e->data.binary.right);
            return expr_div(num, den);
        }

        case EXPR_NEG: {
            // d(-f)/dx = -df/dx
            return expr_neg(expr_derivative(e->data.operand, var));
        }

        case EXPR_SQRT: {
            // d(sqrt(f))/dx = (1/(2*sqrt(f))) * df/dx
            Expr *inner_deriv = expr_derivative(e->data.operand, var);
            Expr *sqrt_f = expr_sqrt(e->data.operand);
            Expr *two = expr_number(2.0);
            Expr *denom = expr_mul(two, sqrt_f);
            return expr_mul(expr_div(expr_number(1.0), denom), inner_deriv);
        }

        case EXPR_POW: {
            // d(f^g)/dx = f^g * (g' * ln(f) + g * f'/f)
            // Для простоты считаем, что степень - константа
            Expr *base = e->data.binary.left;
            Expr *exp = e->data.binary.right;
            Expr *db = expr_derivative(base, var);
            Expr *de = expr_derivative(exp, var);

            // Проверяем, является ли степень константой
            if (exp->type == EXPR_NUMBER) {
                double n = exp->data.number;
                if (n == 0.0) {
                    // d(c^0)/dx = 0
                    return expr_number(0.0);
                }
                // d(f^n)/dx = n * f^(n-1) * f'
                Expr *new_exp = expr_number(n - 1.0);
                Expr *new_pow = expr_pow(base, new_exp);
                Expr *coef = expr_mul(expr_number(n), new_pow);
                return expr_mul(coef, db);
            } else {
                // Общий случай: d(f^g)/dx = f^g * (g' * ln(f) + g * f'/f)
                Expr *pow_val = expr_pow(base, exp);
                Expr *ln_f = expr_number(log(2.718281828));  
                Expr *term1 = expr_mul(de, ln_f);
                Expr *term2 = expr_mul(exp, expr_div(db, base));
                return expr_mul(pow_val, expr_add(term1, term2));
            }
        }

        default:
            return expr_number(0.0);
    }
    }

    //  Упрощение выражения 
    
    Expr* expr_simplify(Expr *e) {
        if (!e) return NULL;

    // Сначала упрощаем (switch по тегу)
    switch (e->type) {
        case EXPR_ADD:
        case EXPR_SUB:
        case EXPR_MUL:
        case EXPR_DIV:
        case EXPR_POW:
            e->data.binary.left = expr_simplify(e->data.binary.left);
            e->data.binary.right = expr_simplify(e->data.binary.right);
            break;
        case EXPR_NEG:
        case EXPR_SQRT:
            e->data.operand = expr_simplify(e->data.operand);
            break;
        default:
            break;
    }

    // Применяем правила упрощения
    switch (e->type) {
        case EXPR_ADD: {
            // 0 + x = x, x + 0 = x
            if (e->data.binary.left->type == EXPR_NUMBER &&
                e->data.binary.left->data.number == 0.0) {
                Expr *right = e->data.binary.right;
                free(e);
                return right;
            }
            if (e->data.binary.right->type == EXPR_NUMBER &&
                e->data.binary.right->data.number == 0.0) {
                Expr *left = e->data.binary.left;
                free(e);
                return left;
            }
            // Числа: a + b = c
            if (e->data.binary.left->type == EXPR_NUMBER &&
                e->data.binary.right->type == EXPR_NUMBER) {
                double result = e->data.binary.left->data.number +
                               e->data.binary.right->data.number;
                expr_free(e->data.binary.left);
                expr_free(e->data.binary.right);
                e->type = EXPR_NUMBER;
                e->data.number = result;
            }
            break;
        }

        case EXPR_SUB: {
            // x - 0 = x
            if (e->data.binary.right->type == EXPR_NUMBER &&
                e->data.binary.right->data.number == 0.0) {
                Expr *left = e->data.binary.left;
                free(e);
                return left;
            }
            // 0 - x = -x
            if (e->data.binary.left->type == EXPR_NUMBER &&
                e->data.binary.left->data.number == 0.0) {
                Expr *right = e->data.binary.right;
                free(e);
                return expr_neg(right);
            }
            // Числа: a - b = c
            if (e->data.binary.left->type == EXPR_NUMBER &&
                e->data.binary.right->type == EXPR_NUMBER) {
                double result = e->data.binary.left->data.number -
                               e->data.binary.right->data.number;
                expr_free(e->data.binary.left);
                expr_free(e->data.binary.right);
                e->type = EXPR_NUMBER;
                e->data.number = result;
            }
            break;
        }

        case EXPR_MUL: {
            // 0 * x = 0, x * 0 = 0
            if ((e->data.binary.left->type == EXPR_NUMBER &&
                 e->data.binary.left->data.number == 0.0) ||
                (e->data.binary.right->type == EXPR_NUMBER &&
                 e->data.binary.right->data.number == 0.0)) {
                expr_free(e->data.binary.left);
                expr_free(e->data.binary.right);
                e->type = EXPR_NUMBER;
                e->data.number = 0.0;
                return e;
            }
            // 1 * x = x, x * 1 = x
            if (e->data.binary.left->type == EXPR_NUMBER &&
                e->data.binary.left->data.number == 1.0) {
                Expr *right = e->data.binary.right;
                free(e);
                return right;
            }
            if (e->data.binary.right->type == EXPR_NUMBER &&
                e->data.binary.right->data.number == 1.0) {
                Expr *left = e->data.binary.left;
                free(e);
                return left;
            }
            // Числа: a * b = c
            if (e->data.binary.left->type == EXPR_NUMBER &&
                e->data.binary.right->type == EXPR_NUMBER) {
                double result = e->data.binary.left->data.number *
                               e->data.binary.right->data.number;
                expr_free(e->data.binary.left);
                expr_free(e->data.binary.right);
                e->type = EXPR_NUMBER;
                e->data.number = result;
            }
            break;
        }

        case EXPR_DIV: {
            // 0 / x = 0 (x != 0)
            if (e->data.binary.left->type == EXPR_NUMBER &&
                e->data.binary.left->data.number == 0.0) {
                expr_free(e->data.binary.left);
                expr_free(e->data.binary.right);
                e->type = EXPR_NUMBER;
                e->data.number = 0.0;
                return e;
            }
            // x / 1 = x
            if (e->data.binary.right->type == EXPR_NUMBER &&
                e->data.binary.right->data.number == 1.0) {
                Expr *left = e->data.binary.left;
                free(e);
                return left;
            }
            // x / x = 1 (если одинаковые переменные)
            if (e->data.binary.left->type == EXPR_VARIABLE &&
                e->data.binary.right->type == EXPR_VARIABLE &&
                e->data.binary.left->data.variable == e->data.binary.right->data.variable) {
                expr_free(e->data.binary.left);
                expr_free(e->data.binary.right);
                e->type = EXPR_NUMBER;
                e->data.number = 1.0;
                return e;
            }
            // Числа: a / b = c
            if (e->data.binary.left->type == EXPR_NUMBER &&
                e->data.binary.right->type == EXPR_NUMBER) {
                if (e->data.binary.right->data.number != 0.0) {
                    double result = e->data.binary.left->data.number /
                                   e->data.binary.right->data.number;
                    expr_free(e->data.binary.left);
                    expr_free(e->data.binary.right);
                    e->type = EXPR_NUMBER;
                    e->data.number = result;
                }
            }
            break;
        }

        case EXPR_NEG: {
            // -(-x) = x
            if (e->data.operand->type == EXPR_NEG) {
                Expr *inner = e->data.operand->data.operand;
                free(e->data.operand);
                free(e);
                return inner;
            }
            // -(число) = новое число
            if (e->data.operand->type == EXPR_NUMBER) {
                double result = -e->data.operand->data.number;
                expr_free(e->data.operand);
                e->type = EXPR_NUMBER;
                e->data.number = result;
            }
            break;
        }

        case EXPR_SQRT: {
            // sqrt(число)
            if (e->data.operand->type == EXPR_NUMBER &&
                e->data.operand->data.number >= 0.0) {
                double result = sqrt(e->data.operand->data.number);
                expr_free(e->data.operand);
                e->type = EXPR_NUMBER;
                e->data.number = result;
            }
            break;
        }

        case EXPR_POW: {
            // x ^ 0 = 1
            if (e->data.binary.right->type == EXPR_NUMBER &&
                e->data.binary.right->data.number == 0.0) {
                expr_free(e->data.binary.left);
                expr_free(e->data.binary.right);
                e->type = EXPR_NUMBER;
                e->data.number = 1.0;
                return e;
            }
            // x ^ 1 = x
            if (e->data.binary.right->type == EXPR_NUMBER &&
                e->data.binary.right->data.number == 1.0) {
                Expr *left = e->data.binary.left;
                expr_free(e->data.binary.right);
                free(e);
                return left;
            }
            // 0 ^ x = 0 (x > 0)
            if (e->data.binary.left->type == EXPR_NUMBER &&
                e->data.binary.left->data.number == 0.0) {
                expr_free(e->data.binary.left);
                expr_free(e->data.binary.right);
                e->type = EXPR_NUMBER;
                e->data.number = 0.0;
                return e;
            }
            // 1 ^ x = 1
            if (e->data.binary.left->type == EXPR_NUMBER &&
                e->data.binary.left->data.number == 1.0) {
                expr_free(e->data.binary.left);
                expr_free(e->data.binary.right);
                e->type = EXPR_NUMBER;
                e->data.number = 1.0;
                return e;
            }
            // Числа: a ^ b = c
            if (e->data.binary.left->type == EXPR_NUMBER &&
                e->data.binary.right->type == EXPR_NUMBER) {
                double result = pow(e->data.binary.left->data.number,
                                   e->data.binary.right->data.number);
                expr_free(e->data.binary.left);
                expr_free(e->data.binary.right);
                e->type = EXPR_NUMBER;
                e->data.number = result;
            }
            break;
        }

        default:
            break;
    }

    return e;
    }
    
    //  Освобождение памяти 
    void expr_free(Expr *e) {
        if (!e) return;
    
    switch (e->type) {
        case EXPR_NUMBER:
        case EXPR_VARIABLE:
            
            break;
        case EXPR_ADD:
        case EXPR_SUB:
        case EXPR_MUL:
        case EXPR_DIV:
        case EXPR_POW:
            expr_free(e->data.binary.left);
            expr_free(e->data.binary.right);
            break;
        case EXPR_NEG:
        case EXPR_SQRT:
            expr_free(e->data.operand);
            break;
    }
    
    free(e);
    }
    
    // Демонстрация 
    
    int main() {
        SetConsoleOutputCP(CP_UTF8);
    
    printf("=== Калькулятор с AST ===\n\n");

    // Пример 1: (x + 3) * (x - 2) при x = 5
    printf("--- Пример 1: (x + 3) * (x - 2) ---\n");
    Expr *x = expr_variable('x');
    Expr *three = expr_number(3.0);
    Expr *two = expr_number(2.0);

    Expr *expr1 = expr_mul(expr_add(x, three), expr_sub(expr_variable('x'), two));
    
    printf("Выражение: ");
    expr_print(expr1);
    printf("\n");
    
    Context ctx;
    context_init(&ctx);
    context_set(&ctx, 'x', 5.0);
    
    double result = expr_eval(expr1, &ctx);
    printf("При x = 5: %.2f\n", result);
    printf("Ожидаемо: (5 + 3) * (5 - 2) = 8 * 3 = 24\n\n");
    
    // Пример 2: Производная
    printf("--- Пример 2: Производная ---\n");
    Expr *x2 = expr_variable('x');
    Expr *expr2 = expr_mul(expr_add(x2, expr_number(3.0)), 
                           expr_sub(expr_variable('x'), expr_number(2.0)));
    
    printf("Исходное выражение: ");
    expr_print(expr2);
    printf("\n");
    
    Expr *deriv = expr_derivative(expr2, 'x');
    printf("Производная по x: ");
    expr_print(deriv);
    printf("\n");
    
    Expr *deriv_simplified = expr_simplify(deriv);
    printf("Упрощённая производная: ");
    expr_print(deriv_simplified);
    printf("\n\n");
    
    // Пример 3: Упрощение
    printf("--- Пример 3: Упрощение выражений ---\n");
    
    // 0 + x = x
    Expr *simp1 = expr_add(expr_number(0.0), expr_variable('x'));
    printf("0 + x = ");
    expr_print(expr_simplify(simp1));
    printf("\n");
    
    // x * 1 = x
    Expr *simp2 = expr_mul(expr_variable('y'), expr_number(1.0));
    printf("y * 1 = ");
    expr_print(expr_simplify(simp2));
    printf("\n");
    
    // x / x = 1
    Expr *simp3 = expr_div(expr_variable('z'), expr_variable('z'));
    printf("z / z = ");
    expr_print(expr_simplify(simp3));
    printf("\n");
    
    // -(-x) = x
    Expr *simp4 = expr_neg(expr_neg(expr_variable('a')));
    printf("-(-a) = ");
    expr_print(expr_simplify(simp4));
    printf("\n");
    
    // sqrt(16) = 4
    Expr *simp5 = expr_sqrt(expr_number(16.0));
    printf("sqrt(16) = ");
    expr_print(expr_simplify(simp5));
    printf("\n\n");
    
    // Пример 4: Сложное выражение
    printf("--- Пример 4: Сложное выражение ---\n");
    Expr *complex = expr_add(
        expr_mul(expr_number(2.0), expr_pow(expr_variable('x'), expr_number(3.0))),
        expr_sub(expr_sqrt(expr_variable('x')), expr_number(5.0))
    );
    printf("Выражение: 2*x^3 + (sqrt(x) - 5)\n");
    printf("В AST: ");
    expr_print(complex);
    printf("\n");
    
    context_set(&ctx, 'x', 4.0);
    result = expr_eval(complex, &ctx);
    printf("При x = 4: %.2f\n", result);
    printf("Проверка: 2*64 + (2 - 5) = 128 - 3 = 125\n\n");
    
    // Очистка памяти
    expr_free(expr1);
    expr_free(deriv_simplified);
    expr_free(complex);
    
    return 0;
    }

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



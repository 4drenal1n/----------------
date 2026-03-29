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
<img width="981" height="509" alt="Снимок экрана 2026-03-29 154859" src="https://github.com/user-attachments/assets/b222155c-fa47-48a1-aa86-4e0f8ec3fca3" />

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
<img width="974" height="511" alt="Снимок экрана 2026-03-29 160559" src="https://github.com/user-attachments/assets/60a4fb69-ee9d-4b3b-87b4-5efcbe5c819c" />

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
<img width="982" height="510" alt="Снимок экрана 2026-03-29 163759" src="https://github.com/user-attachments/assets/51a1f823-7bb0-4e3a-9c46-02ef5056fe46" />

Задание 6.4: Система сообщений (Protocol Buffers style)
Реализуйте систему обмена сообщениями различных типов.

### Код программы

    #define _CRT_SECURE_NO_WARNINGS
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <time.h>
    #include <windows.h>
    
    // Типы сообщений
    typedef enum {
        MSG_TEXT,
        MSG_IMAGE,
        MSG_FILE,
        MSG_LOCATION,
        MSG_AUDIO
    } MessageType;
    
    // Текстовое сообщение
    typedef struct {
        char content[500];
        int is_edited;
    } TextMessage;
    
    // Изображение
    typedef struct {
        char filename[100];
        int width;
        int height;
        size_t size_bytes;
    } ImageMessage;
    
    // Файл
    typedef struct {
        char filename[100];
        char mime_type[50];
        size_t size_bytes;
    } FileMessage;
    
    // Локация
    typedef struct {
        double latitude;
        double longitude;
        char address[200];
    } LocationMessage;
    
    // Аудио
    typedef struct {
        char filename[100];
        int duration_seconds;
        size_t size_bytes;
    } AudioMessage;
    
    // Сообщение с tagged union
    typedef struct {
        unsigned int id;
        unsigned int sender_id;
        unsigned int chat_id;
        time_t timestamp;
        MessageType type;
        union {
            TextMessage text;
            ImageMessage image;
            FileMessage file;
            LocationMessage location;
            AudioMessage audio;
        } content;
    } Message;
    
    //сообщения
    
    Message create_text_message(unsigned int sender, unsigned int chat, const char *text) {
        Message msg = {0};
        msg.id = rand() % 100000;
        msg.sender_id = sender;
        msg.chat_id = chat;
        msg.timestamp = time(NULL);
        msg.type = MSG_TEXT;
        strncpy(msg.content.text.content, text, sizeof(msg.content.text.content) - 1);
        msg.content.text.is_edited = 0;
        return msg;
    }
    
    Message create_image_message(unsigned int sender, unsigned int chat,
                                 const char *filename, int w, int h, size_t size) {
        Message msg = {0};
        msg.id = rand() % 100000;
        msg.sender_id = sender;
        msg.chat_id = chat;
        msg.timestamp = time(NULL);
        msg.type = MSG_IMAGE;
        strncpy(msg.content.image.filename, filename, sizeof(msg.content.image.filename) - 1);
        msg.content.image.width = w;
        msg.content.image.height = h;
        msg.content.image.size_bytes = size;
        return msg;
    }
    
    Message create_file_message(unsigned int sender, unsigned int chat,
                                const char *filename, const char *mime, size_t size) {
        Message msg = {0};
        msg.id = rand() % 100000;
        msg.sender_id = sender;
        msg.chat_id = chat;
        msg.timestamp = time(NULL);
        msg.type = MSG_FILE;
        strncpy(msg.content.file.filename, filename, sizeof(msg.content.file.filename) - 1);
        strncpy(msg.content.file.mime_type, mime, sizeof(msg.content.file.mime_type) - 1);
        msg.content.file.size_bytes = size;
        return msg;
    }
    
    Message create_location_message(unsigned int sender, unsigned int chat,
                                    double lat, double lon, const char *address) {
        Message msg = {0};
        msg.id = rand() % 100000;
        msg.sender_id = sender;
        msg.chat_id = chat;
        msg.timestamp = time(NULL);
        msg.type = MSG_LOCATION;
        msg.content.location.latitude = lat;
        msg.content.location.longitude = lon;
        strncpy(msg.content.location.address, address, sizeof(msg.content.location.address) - 1);
        return msg;
    }
    
    Message create_audio_message(unsigned int sender, unsigned int chat,
                                 const char *filename, int duration, size_t size) {
        Message msg = {0};
        msg.id = rand() % 100000;
        msg.sender_id = sender;
        msg.chat_id = chat;
        msg.timestamp = time(NULL);
        msg.type = MSG_AUDIO;
        strncpy(msg.content.audio.filename, filename, sizeof(msg.content.audio.filename) - 1);
        msg.content.audio.duration_seconds = duration;
        msg.content.audio.size_bytes = size;
        return msg;
    }
    
    // Сериализация 
    
    size_t message_serialize(const Message *msg, unsigned char *buffer, size_t buffer_size) {
        if (!msg || !buffer) return 0;

    size_t offset = 0;
    size_t content_size = 0;

    // Определяем размер контента в зависимости от типа
    switch (msg->type) {
        case MSG_TEXT:
            content_size = sizeof(TextMessage);
            break;
        case MSG_IMAGE:
            content_size = sizeof(ImageMessage);
            break;
        case MSG_FILE:
            content_size = sizeof(FileMessage);
            break;
        case MSG_LOCATION:
            content_size = sizeof(LocationMessage);
            break;
        case MSG_AUDIO:
            content_size = sizeof(AudioMessage);
            break;
        default:
            return 0;
    }

    size_t total_size = 4 + 4 + 4 + 8 + 4 + 8 + content_size;
    if (total_size > buffer_size) return 0;

    // Копируем заголовок
    memcpy(buffer + offset, &msg->id, 4); offset += 4;
    memcpy(buffer + offset, &msg->sender_id, 4); offset += 4;
    memcpy(buffer + offset, &msg->chat_id, 4); offset += 4;
    memcpy(buffer + offset, &msg->timestamp, 8); offset += 8;
    memcpy(buffer + offset, &msg->type, 4); offset += 4;
    memcpy(buffer + offset, &content_size, sizeof(content_size)); offset += sizeof(content_size);

    // Копируем контент
    memcpy(buffer + offset, &msg->content, content_size);
    offset += content_size;

    return offset;
    }
    
    //Десериализация 
    
    int message_deserialize(const unsigned char *buffer, size_t size, Message *msg) {
        if (!buffer || !msg || size < 32) return -1;

    size_t offset = 0;

    memcpy(&msg->id, buffer + offset, 4); offset += 4;
    memcpy(&msg->sender_id, buffer + offset, 4); offset += 4;
    memcpy(&msg->chat_id, buffer + offset, 4); offset += 4;
    memcpy(&msg->timestamp, buffer + offset, 8); offset += 8;
    memcpy(&msg->type, buffer + offset, 4); offset += 4;

    size_t content_size;
    memcpy(&content_size, buffer + offset, sizeof(content_size)); offset += sizeof(content_size);

    if (offset + content_size > size) {
        return -1;
    }

    // Проверяем тип и копируем контент
    switch (msg->type) {
        case MSG_TEXT:
            if (content_size != sizeof(TextMessage)) return -1;
            memcpy(&msg->content.text, buffer + offset, content_size);
            break;
        case MSG_IMAGE:
            if (content_size != sizeof(ImageMessage)) return -1;
            memcpy(&msg->content.image, buffer + offset, content_size);
            break;
        case MSG_FILE:
            if (content_size != sizeof(FileMessage)) return -1;
            memcpy(&msg->content.file, buffer + offset, content_size);
            break;
        case MSG_LOCATION:
            if (content_size != sizeof(LocationMessage)) return -1;
            memcpy(&msg->content.location, buffer + offset, content_size);
            break;
        case MSG_AUDIO:
            if (content_size != sizeof(AudioMessage)) return -1;
            memcpy(&msg->content.audio, buffer + offset, content_size);
            break;
        default:
            return -1;
    }

    return 0;
    }
    
    // Вывод сообщения 
    
    const char* get_type_name(MessageType type) {
        switch (type) {
            case MSG_TEXT: return "Текст";
            case MSG_IMAGE: return "Изображение";
            case MSG_FILE: return "Файл";
            case MSG_LOCATION: return "Локация";
            case MSG_AUDIO: return "Аудио";
            default: return "Неизвестно";
        }
    }
    
    void message_print(const Message *msg) {
        if (!msg) return;

    struct tm *tm_info = localtime(&msg->timestamp);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%H:%M", tm_info);

    printf("[%s] User#%u: ", time_str, msg->sender_id);

    switch (msg->type) {
        case MSG_TEXT:
            printf("%s%s", msg->content.text.content,
                   msg->content.text.is_edited ? " (изменено)" : "");
            break;
        case MSG_IMAGE:
            printf("[Изображение: %s (%dx%d, %.1f MB)]",
                   msg->content.image.filename,
                   msg->content.image.width,
                   msg->content.image.height,
                   msg->content.image.size_bytes / (1024.0 * 1024.0));
            break;
        case MSG_FILE:
            printf("[Файл: %s (%s, %.1f KB)]",
                   msg->content.file.filename,
                   msg->content.file.mime_type,
                   msg->content.file.size_bytes / 1024.0);
            break;
        case MSG_LOCATION:
            printf("[Локация: %.4f, %.4f - %s]",
                   msg->content.location.latitude,
                   msg->content.location.longitude,
                   msg->content.location.address);
            break;
        case MSG_AUDIO:
            printf("[Аудио: %s (%d:%02d, %.1f KB)]",
                   msg->content.audio.filename,
                   msg->content.audio.duration_seconds / 60,
                   msg->content.audio.duration_seconds % 60,
                   msg->content.audio.size_bytes / 1024.0);
            break;
    }
    printf("\n");
    }
    
    //Фильтрация сообщений 
    
    size_t filter_messages_by_type(const Message *messages, size_t count,
                                   MessageType type, Message *result) {
        size_t found = 0;
        for (size_t i = 0; i < count; i++) {
            if (messages[i].type == type) {
                result[found++] = messages[i];
            }
        }
        return found;
    }
    
    size_t filter_messages_by_sender(const Message *messages, size_t count,
                                     unsigned int sender_id, Message *result) {
        size_t found = 0;
        for (size_t i = 0; i < count; i++) {
            if (messages[i].sender_id == sender_id) {
                result[found++] = messages[i];
            }
        }
        return found;
    }
    
    //Демонстрация 
    
    int main() {
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);

    srand((unsigned int)time(NULL));

    printf("=== Система сообщений (Protocol Buffers style) ===\n\n");

    // Создаём сообщения разных типов
    Message msg1 = create_text_message(1, 42, "Привет! Как дела?");
    Message msg2 = create_text_message(2, 42, "Отлично! Смотри что нашёл:");
    Message msg3 = create_image_message(2, 42, "photo.jpg", 1920, 1080, 2621440);
    Message msg4 = create_text_message(1, 42, "Круто! Где это?");
    Message msg5 = create_location_message(2, 42, 55.7558, 37.6173, "Москва, Красная площадь");
    Message msg6 = create_audio_message(1, 42, "voice_message.ogg", 45, 72000);
    Message msg7 = create_file_message(2, 42, "document.pdf", "application/pdf", 524288);

    // Массив всех сообщений
    Message messages[] = {msg1, msg2, msg3, msg4, msg5, msg6, msg7};
    size_t msg_count = sizeof(messages) / sizeof(messages[0]);

    // Вывод чата
    printf("=== Чат #42 ===\n");
    for (size_t i = 0; i < msg_count; i++) {
        message_print(&messages[i]);
    }

    // Фильтрация по типу
    printf("\n=== Только изображения ===\n");
    Message images[10];
    size_t img_count = filter_messages_by_type(messages, msg_count, MSG_IMAGE, images);
    for (size_t i = 0; i < img_count; i++) {
        message_print(&images[i]);
    }

    printf("\n=== Только локации ===\n");
    Message locations[10];
    size_t loc_count = filter_messages_by_type(messages, msg_count, MSG_LOCATION, locations);
    for (size_t i = 0; i < loc_count; i++) {
        message_print(&locations[i]);
    }

    // Фильтрация по отправителю
    printf("\n=== Сообщения от User#1 ===\n");
    Message from_user1[10];
    size_t user1_count = filter_messages_by_sender(messages, msg_count, 1, from_user1);
    for (size_t i = 0; i < user1_count; i++) {
        message_print(&from_user1[i]);
    }

    // Сериализация/десериализация
    printf("\n=== Проверка сериализации ===\n");
    unsigned char buffer[1024];
    size_t serialized_size = message_serialize(&msg5, buffer, sizeof(buffer));
    printf("Размер сериализованного сообщения: %zu байт\n", serialized_size);

    Message deserialized;
    if (message_deserialize(buffer, serialized_size, &deserialized) == 0) {
        printf("Десериализованное сообщение: ");
        message_print(&deserialized);
    } else {
        printf("Ошибка десериализации!\n");
    }

    return 0;
    }

<img width="979" height="507" alt="Снимок экрана 2026-03-29 184253" src="https://github.com/user-attachments/assets/f171ba20-f67c-41bd-81c3-597a7c55f8fd" />

Задание 6.5: Битовые флаги
Реализуйте систему прав доступа с использованием битовых полей и флагов.

### Код программы

    #define _CRT_SECURE_NO_WARNINGS
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <windows.h>
    
    //  Вариант 1: Битовые флаги через enum 
    
    typedef enum {
        PERM_NONE     = 0,
        PERM_READ     = 1 << 0,  // 00001
        PERM_WRITE    = 1 << 1,  // 00010
        PERM_EXECUTE  = 1 << 2,  // 00100
        PERM_DELETE   = 1 << 3,  // 01000
        PERM_ADMIN    = 1 << 4,  // 10000
        PERM_ALL      = PERM_READ | PERM_WRITE | PERM_EXECUTE | PERM_DELETE | PERM_ADMIN
    } Permission;
    
    //  Вариант 2: Битовые поля 
    
    typedef struct {
        unsigned int read     : 1;
        unsigned int write    : 1;
        unsigned int execute  : 1;
        unsigned int delete   : 1;
        unsigned int admin    : 1;
        unsigned int reserved : 27;  // Резерв для выравнивания
    } PermissionBits;
    
    //  Пользователь и ресурс 
    
    typedef struct {
        unsigned int id;
        char name[50];
        Permission permissions;
    } User;
    
    typedef struct {
        unsigned int id;
        char name[100];
        Permission required_permissions;
    } Resource;
    
    // Работа с правами
    
    void permission_add(Permission *p, Permission flag) {
        if (p) *p = (Permission)(*p | flag);
    }
    
    void permission_remove(Permission *p, Permission flag) {
        if (p) *p = (Permission)(*p & ~flag);
    }
    
    int permission_has(Permission p, Permission flag) {
        return (p & flag) == flag;
    }
    
    int permission_has_all(Permission p, Permission flags) {
        return (p & flags) == flags;
    }
    
    int permission_has_any(Permission p, Permission flags) {
        return (p & flags) != PERM_NONE;
    }
    
    //  Преобразование в строку 
    
    void permission_to_string(Permission p, char *buffer, size_t size) {
        if (!buffer || size < 6) return;

    buffer[0] = (p & PERM_READ)    ? 'r' : '-';
    buffer[1] = (p & PERM_WRITE)   ? 'w' : '-';
    buffer[2] = (p & PERM_EXECUTE) ? 'x' : '-';
    buffer[3] = (p & PERM_DELETE)  ? 'd' : '-';
    buffer[4] = (p & PERM_ADMIN)   ? 'a' : '-';
    buffer[5] = '\0';
    }
    
    //  Проверка доступа 
    
    int user_can_access(const User *user, const Resource *resource) {
        if (!user || !resource) return 0;
        // Пользователь имеет доступ, если у него есть ВСЕ требуемые права
        return permission_has_all(user->permissions, resource->required_permissions);
    }
    
    //  Вывод 
    
    void user_print(const User *user) {
        if (!user) return;

    char perm_str[10];
    permission_to_string(user->permissions, perm_str, sizeof(perm_str));

    printf("Пользователь: %s (ID: %u)\n", user->name, user->id);
    printf("Права: %s", perm_str);

    // Расшифровка прав
    printf(" (");
    int first = 1;
    if (user->permissions & PERM_READ)    { printf("%sчтение", first ? "" : ", "); first = 0; }
    if (user->permissions & PERM_WRITE)   { printf("%sзапись", first ? "" : ", "); first = 0; }
    if (user->permissions & PERM_EXECUTE) { printf("%sвыполнение", first ? "" : ", "); first = 0; }
    if (user->permissions & PERM_DELETE)  { printf("%sудаление", first ? "" : ", "); first = 0; }
    if (user->permissions & PERM_ADMIN)   { printf("%sадмин", first ? "" : ", "); first = 0; }
    if (user->permissions == PERM_NONE)   { printf("нет прав"); }
    printf(")\n\n");
    }
    
    void resource_print(const Resource *resource) {
        if (!resource) return;

    char perm_str[10];
    permission_to_string(resource->required_permissions, perm_str, sizeof(perm_str));

    printf("Ресурс: %s (ID: %u)\n", resource->name, resource->id);
    printf("Требуемые права: %s\n\n", perm_str);
    }
    
    //  Работа с битовыми полями 
    
    void permission_bits_init(PermissionBits *pb) {
        if (!pb) return;
        pb->read = pb->write = pb->execute = pb->delete = pb->admin = 0;
        pb->reserved = 0;
    }
    
    void permission_bits_set(PermissionBits *pb, Permission p) {
        if (!pb) return;
        pb->read    = (p & PERM_READ)    ? 1 : 0;
        pb->write   = (p & PERM_WRITE)   ? 1 : 0;
        pb->execute = (p & PERM_EXECUTE) ? 1 : 0;
        pb->delete  = (p & PERM_DELETE)  ? 1 : 0;
        pb->admin   = (p & PERM_ADMIN)   ? 1 : 0;
    }
    
    Permission permission_bits_to_enum(const PermissionBits *pb) {
        Permission p = PERM_NONE;
        if (!pb) return p;

    if (pb->read)    p |= PERM_READ;
    if (pb->write)   p |= PERM_WRITE;
    if (pb->execute) p |= PERM_EXECUTE;
    if (pb->delete)  p |= PERM_DELETE;
    if (pb->admin)   p |= PERM_ADMIN;
    return p;
    }
    
    //  Демонстрация 
    
    int main() {
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);

    printf("=== Система прав доступа с битовыми флагами ===\n\n");

    // Создаём пользователей
    User admin = {1, "admin", PERM_ALL};
    User editor = {2, "editor", (Permission)(PERM_READ | PERM_WRITE | PERM_EXECUTE)};
    User viewer = {3, "viewer", PERM_READ};
    User guest = {4, "guest", PERM_NONE};

    printf("--- Пользователи ---\n");
    user_print(&admin);
    user_print(&editor);
    user_print(&viewer);
    user_print(&guest);

    // Создаём ресурсы
    Resource public_file = {1, "/data/public.txt", PERM_READ};
    Resource edit_file = {2, "/data/edit.txt", (Permission)(PERM_READ | PERM_WRITE)};
    Resource secret_file = {3, "/data/secret.txt", (Permission)(PERM_READ | PERM_WRITE | PERM_ADMIN)};
    Resource exec_file = {4, "/bin/app.exe", (Permission)(PERM_READ | PERM_EXECUTE)};

    printf("--- Ресурсы ---\n");
    resource_print(&public_file);
    resource_print(&edit_file);
    resource_print(&secret_file);
    resource_print(&exec_file);

    // Проверка доступа
    printf("=== Проверка доступа ===\n\n");

    User* users[] = {&admin, &editor, &viewer, &guest};
    Resource* resources[] = {&public_file, &edit_file, &secret_file, &exec_file};
    const char* user_names[] = {"admin", "editor", "viewer", "guest"};

    for (size_t r = 0; r < sizeof(resources)/sizeof(resources[0]); r++) {
        printf("Ресурс: %s\n", resources[r]->name);
        char req_perm[10];
        permission_to_string(resources[r]->required_permissions, req_perm, sizeof(req_perm));
        printf("Требуемые права: %s\n", req_perm);

        for (size_t u = 0; u < sizeof(users)/sizeof(users[0]); u++) {
            int access = user_can_access(users[u], resources[r]);
            printf("  %s -> %s\n", user_names[u], access ? "разрешён" : "ЗАПРЕЩЁН");
        }
        printf("\n");
    }

    // Демонстрация операций с флагами
    printf("=== Операции с флагами ===\n\n");

    Permission user_perm = PERM_READ;
    char perm_str[10];

    printf("Начальные права: ");
    permission_to_string(user_perm, perm_str, sizeof(perm_str));
    printf("%s\n", perm_str);

    permission_add(&user_perm, PERM_WRITE);
    printf("После добавления WRITE: ");
    permission_to_string(user_perm, perm_str, sizeof(perm_str));
    printf("%s\n", perm_str);

    permission_add(&user_perm, PERM_DELETE);
    printf("После добавления DELETE: ");
    permission_to_string(user_perm, perm_str, sizeof(perm_str));
    printf("%s\n", perm_str);

    printf("Проверка наличия WRITE: %s\n", permission_has(user_perm, PERM_WRITE) ? "да" : "нет");
    printf("Проверка наличия ADMIN: %s\n", permission_has(user_perm, PERM_ADMIN) ? "да" : "нет");
    printf("Проверка наличия всех (READ|WRITE): %s\n",
           permission_has_all(user_perm, (Permission)(PERM_READ | PERM_WRITE)) ? "да" : "нет");
    printf("Проверка наличия любого из (DELETE|ADMIN): %s\n",
           permission_has_any(user_perm, (Permission)(PERM_DELETE | PERM_ADMIN)) ? "да" : "нет");

    permission_remove(&user_perm, PERM_DELETE);
    printf("После удаления DELETE: ");
    permission_to_string(user_perm, perm_str, sizeof(perm_str));
    printf("%s\n", perm_str);

    // Демонстрация битовых полей
    printf("\n=== Битовые поля ===\n\n");

    PermissionBits pb;
    permission_bits_init(&pb);
    permission_bits_set(&pb, (Permission)(PERM_READ | PERM_WRITE | PERM_EXECUTE));

    printf("Битовые поля: r=%d w=%d x=%d d=%d a=%d\n",
           pb.read, pb.write, pb.execute, pb.delete, pb.admin);

    Permission converted = permission_bits_to_enum(&pb);
    permission_to_string(converted, perm_str, sizeof(perm_str));
    printf("Преобразование в enum: %s\n", perm_str);

    printf("Размер Permission (enum): %zu байт\n", sizeof(Permission));
    printf("Размер PermissionBits (struct): %zu байт\n", sizeof(PermissionBits));

    return 0;
    }

<img width="1089" height="953" alt="Снимок экрана 2026-03-29 184542" src="https://github.com/user-attachments/assets/feba36f3-8901-4d36-8977-891f554185e0" />

Задание 6.6: Конечный автомат
Реализуйте конечный автомат для разбора простого языка.

### Код программы

    #define _CRT_SECURE_NO_WARNINGS
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    #include <windows.h>
    
    //  Типы токенов 
    
    typedef enum {
        TOK_NUMBER,
        TOK_IDENTIFIER,
        TOK_OPERATOR,
        TOK_LPAREN,
        TOK_RPAREN,
        TOK_EOF,
        TOK_ERROR
    } TokType;
    
    //  Токен 
    
    typedef struct {
        TokType type;
        union {
            double number;
            char identifier[64];
            char op;
        } value;
        int line;
        int column;
    } Token;
    
    //  Состояния лексера 
    
    typedef enum {
        STATE_START,
        STATE_IN_NUMBER,
        STATE_IN_IDENTIFIER,
        STATE_IN_OPERATOR,
        STATE_ERROR,
        STATE_DONE
    } LexerState;
    
    //  Лексер 
    
    typedef struct {
        const char *input;
        size_t pos;
        int line;
        int column;
        LexerState state;
        size_t input_len;
    } Lexer;
    
    //  Вспомогательные функции 
    
    static char current_char(const Lexer *lex) {
        if (lex->pos >= lex->input_len) return '\0';
        return lex->input[lex->pos];
    }
    
    static char peek_char(const Lexer *lex, int offset) {
        size_t pos = lex->pos + offset;
        if (pos >= lex->input_len) return '\0';
        return lex->input[pos];
    }
    
    static void advance(Lexer *lex) {
        if (lex->pos < lex->input_len) {
            if (lex->input[lex->pos] == '\n') {
                lex->line++;
                lex->column = 1;
            } else {
                lex->column++;
            }
            lex->pos++;
        }
    }
    
    static int is_operator_char(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' ||
               c == '=' || c == '<' || c == '>' || c == '!' ||
               c == '&' || c == '|' || c == '^' || c == '%' ||
               c == '(' || c == ')' || c == '{' || c == '}' ||
               c == '[' || c == ']' || c == ',' || c == ';';
    }
    
    static int is_identifier_start(char c) {
        return isalpha(c) || c == '_';
    }
    
    static int is_identifier_char(char c) {
        return isalnum(c) || c == '_';
    }
    
    static int is_digit(char c) {
        return c >= '0' && c <= '9';
    }
    
    // Инициализация 
    
    void lexer_init(Lexer *lex, const char *input) {
        if (!lex || !input) return;
        lex->input = input;
        lex->pos = 0;
        lex->line = 1;
        lex->column = 1;
        lex->state = STATE_START;
        lex->input_len = strlen(input);
    }
    
    //  Пропуск пробелов 
    
    void lexer_skip_whitespace(Lexer *lex) {
        while (current_char(lex) != '\0' && isspace(current_char(lex))) {
            advance(lex);
        }
    }
    
    //  Пропуск комментариев 
    
    static void lexer_skip_comment(Lexer *lex) {
        if (current_char(lex) == '/') {
            if (peek_char(lex, 1) == '/') {
                // Однострочный комментарий //
                while (current_char(lex) != '\0' && current_char(lex) != '\n') {
                    advance(lex);
                }
            } else if (peek_char(lex, 1) == '*') {
                // Многострочный комментарий /* */
                advance(lex); // пропускаем '*'
                while (current_char(lex) != '\0') {
                    if (current_char(lex) == '*' && peek_char(lex, 1) == '/') {
                        advance(lex); // '/'
                        advance(lex);
                        return;
                    }
                    advance(lex);
                }
            }
        }
    }
    
    // Создание токенов 
    
    static Token make_token(TokType type, int line, int column) {
        Token tok;
        tok.type = type;
        tok.line = line;
        tok.column = column;
        return tok;
    }
    
    static Token make_number_token(double value, int line, int column) {
        Token tok = make_token(TOK_NUMBER, line, column);
        tok.value.number = value;
        return tok;
    }
    
    static Token make_identifier_token(const char *str, int line, int column) {
        Token tok = make_token(TOK_IDENTIFIER, line, column);
        strncpy(tok.value.identifier, str, sizeof(tok.value.identifier) - 1);
        tok.value.identifier[sizeof(tok.value.identifier) - 1] = '\0';
        return tok;
    }
    
    static Token make_operator_token(char op, int line, int column) {
        Token tok = make_token(TOK_OPERATOR, line, column);
        tok.value.op = op;
        return tok;
    }
    
    static Token make_error_token(const char *msg, int line, int column) {
        Token tok = make_token(TOK_ERROR, line, column);
        strncpy(tok.value.identifier, msg, sizeof(tok.value.identifier) - 1);
        tok.value.identifier[sizeof(tok.value.identifier) - 1] = '\0';
        return tok;
    }
    
    // Получение следующего токена 
    
    Token lexer_next_token(Lexer *lex) {
        if (!lex) return make_error_token("NULL lexer", 0, 0);

    while (1) {
        // Пропускаем пробелы
        lexer_skip_whitespace(lex);

        // Пропускаем комментарии
        lexer_skip_comment(lex);

        // Если после пропуска снова пробелы - повторяем
        if (isspace(current_char(lex))) continue;

        break;
    }

    int start_line = lex->line;
    int start_col = lex->column;

    // Конец ввода
    if (current_char(lex) == '\0') {
        lex->state = STATE_DONE;
        return make_token(TOK_EOF, start_line, start_col);
    }

    char c = current_char(lex);

    // Числа (включая числа с плавающей точкой)
    if (is_digit(c) || (c == '.' && is_digit(peek_char(lex, 1)))) {
        char num_buf[64];
        int idx = 0;
        int has_dot = 0;

        while (current_char(lex) != '\0' &&
               (is_digit(current_char(lex)) ||
                (current_char(lex) == '.' && !has_dot))) {
            if (current_char(lex) == '.') has_dot = 1;
            if (idx < (int)sizeof(num_buf) - 1) {
                num_buf[idx++] = current_char(lex);
            }
            advance(lex);
        }
        num_buf[idx] = '\0';

        lex->state = STATE_IN_NUMBER;
        return make_number_token(atof(num_buf), start_line, start_col);
    }

    // Идентификаторы и ключевые слова
    if (is_identifier_start(c)) {
        char id_buf[64];
        int idx = 0;

        while (current_char(lex) != '\0' && is_identifier_char(current_char(lex))) {
            if (idx < (int)sizeof(id_buf) - 1) {
                id_buf[idx++] = current_char(lex);
            }
            advance(lex);
        }
        id_buf[idx] = '\0';

        lex->state = STATE_IN_IDENTIFIER;
        return make_identifier_token(id_buf, start_line, start_col);
    }

    // Операторы и скобки
    if (is_operator_char(c)) {
        advance(lex);

        // Проверка на двухсимвольные операторы
        char next = current_char(lex);
        char two_char[3] = {c, next, '\0'};

        int is_two_char_op = (strcmp(two_char, "==") == 0 ||
                              strcmp(two_char, "!=") == 0 ||
                              strcmp(two_char, "<=") == 0 ||
                              strcmp(two_char, ">=") == 0 ||
                              strcmp(two_char, "&&") == 0 ||
                              strcmp(two_char, "||") == 0 ||
                              strcmp(two_char, "++") == 0 ||
                              strcmp(two_char, "--") == 0);

        if (is_two_char_op && next != '\0') {
            advance(lex);
            
            return make_operator_token(c, start_line, start_col);
        }

        // Скобки
        if (c == '(') {
            return make_token(TOK_LPAREN, start_line, start_col);
        }
        if (c == ')') {
            return make_token(TOK_RPAREN, start_line, start_col);
        }

        lex->state = STATE_IN_OPERATOR;
        return make_operator_token(c, start_line, start_col);
    }

    // Нераспознанный символ
    lex->state = STATE_ERROR;
    return make_error_token("Неизвестный символ", start_line, start_col);
    }
    
    // Заглянуть в следующий токен 
    
    Token lexer_peek(Lexer *lex) {
        if (!lex) return make_error_token("NULL lexer", 0, 0);

    // Сохраняем состояние
    Lexer saved = *lex;
    Token tok = lexer_next_token(lex);
    // Восстанавливаем состояние
    *lex = saved;

    return tok;
    }
    
    //  Вывод токена 
    
    const char* token_type_name(TokType type) {
        switch (type) {
            case TOK_NUMBER:     return "NUMBER";
            case TOK_IDENTIFIER: return "IDENTIFIER";
            case TOK_OPERATOR:   return "OPERATOR";
            case TOK_LPAREN:     return "LPAREN";
            case TOK_RPAREN:     return "RPAREN";
            case TOK_EOF:        return "EOF";
            case TOK_ERROR:      return "ERROR";
            default:             return "UNKNOWN";
        }
    }
    
    void token_print(const Token *tok) {
        if (!tok) return;

    switch (tok->type) {
        case TOK_NUMBER:
            printf("[%s] %.6g (line %d, col %d)\n",
                   token_type_name(tok->type), tok->value.number,
                   tok->line, tok->column);
            break;
        case TOK_IDENTIFIER:
            printf("[%s] %s (line %d, col %d)\n",
                   token_type_name(tok->type), tok->value.identifier,
                   tok->line, tok->column);
            break;
        case TOK_OPERATOR:
            printf("[%s] %c (line %d, col %d)\n",
                   token_type_name(tok->type), tok->value.op,
                   tok->line, tok->column);
            break;
        case TOK_LPAREN:
            printf("[%s] ( (line %d, col %d)\n",
                   token_type_name(tok->type), tok->line, tok->column);
            break;
        case TOK_RPAREN:
            printf("[%s] ) (line %d, col %d)\n",
                   token_type_name(tok->type), tok->line, tok->column);
            break;
        case TOK_EOF:
            printf("[%s] (line %d, col %d)\n",
                   token_type_name(tok->type), tok->line, tok->column);
            break;
        case TOK_ERROR:
            printf("[%s] %s (line %d, col %d)\n",
                   token_type_name(tok->type), tok->value.identifier,
                   tok->line, tok->column);
            break;
    }
    }
    
    //  Токенизация всей строки 
    
    size_t tokenize(const char *input, Token *tokens, size_t max_tokens) {
        if (!input || !tokens || max_tokens == 0) return 0;

    Lexer lex;
    lexer_init(&lex, input);

    size_t count = 0;
    while (count < max_tokens) {
        tokens[count] = lexer_next_token(&lex);
        count++;

        if (tokens[count - 1].type == TOK_EOF ||
            tokens[count - 1].type == TOK_ERROR) {
            break;
        }
    }

    return count;
    }
    
    //  Демонстрация 
    
    int main() {
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);

    printf("=== Конечный автомат (Lexer) ===\n\n");

    // Пример 1: простое выражение
    const char *input1 = "x = 3.14 * (y + 2)";
    printf("Вход: \"%s\"\n", input1);
    printf("Токены:\n");

    Lexer lex1;
    lexer_init(&lex1, input1);
    Token tok;
    do {
        tok = lexer_next_token(&lex1);
        token_print(&tok);
    } while (tok.type != TOK_EOF && tok.type != TOK_ERROR);

    // Пример 2: сложное выражение с комментариями
    printf("\n");
    const char *input2 = "result = (a + b) * 2 // это комментарий";
    printf("Вход: \"%s\"\n", input2);
    printf("Токены:\n");

    Lexer lex2;
    lexer_init(&lex2, input2);
    do {
        tok = lexer_next_token(&lex2);
        token_print(&tok);
    } while (tok.type != TOK_EOF && tok.type != TOK_ERROR);

    // Пример 3: многострочный комментарий
    printf("\n");
    const char *input3 = "x = 10 /* комментарий\nмногострочный */ + y";
    printf("Вход: \"%s\"\n", input3);
    printf("Токены:\n");

    Lexer lex3;
    lexer_init(&lex3, input3);
    do {
        tok = lexer_next_token(&lex3);
        token_print(&tok);
    } while (tok.type != TOK_EOF && tok.type != TOK_ERROR);

    // Пример 4: токенизация в массив
    printf("\n");
    const char *input4 = "a + b * c - d / e";
    printf("Вход: \"%s\"\n", input4);

    Token tokens[50];
    size_t count = tokenize(input4, tokens, sizeof(tokens) / sizeof(tokens[0]));

    printf("Всего токенов: %zu\n", count);
    printf("Токены:\n");
    for (size_t i = 0; i < count; i++) {
        token_print(&tokens[i]);
    }

    // Пример 5: lexer_peek
    printf("\n");
    const char *input5 = "x + y";
    printf("Вход: \"%s\"\n", input5);

    Lexer lex5;
    lexer_init(&lex5, input5);

    Token peeked = lexer_peek(&lex5);
    printf("lexer_peek: ");
    token_print(&peeked);

    Token first = lexer_next_token(&lex5);
    printf("lexer_next_token (1): ");
    token_print(&first);

    peeked = lexer_peek(&lex5);
    printf("lexer_peek: ");
    token_print(&peeked);

    // Пример 6: ошибки
    printf("\n");
    const char *input6 = "x = 5 @ y";
    printf("Вход: \"%s\"\n", input6);

    Lexer lex6;
    lexer_init(&lex6, input6);
    do {
        tok = lexer_next_token(&lex6);
        token_print(&tok);
    } while (tok.type != TOK_EOF && tok.type != TOK_ERROR);

    return 0;
    }
<img width="975" height="505" alt="Снимок экрана 2026-03-29 184834" src="https://github.com/user-attachments/assets/1728f0c0-e17d-42cb-a259-af972b675b08" />


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



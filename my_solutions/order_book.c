#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

int on_clear = 1;

typedef struct {
    double price;
    int quantity;
} order;

typedef struct {
    int position;
    int action;
    double price;
    int quantity;
} operation;

typedef struct {
    int capacity;
    int count;
    order *o;
} book;

void init_app();
void exec_prompt(book *b);
void read_input(book *b);
void delete_order(book *b, int index);
int realloc_book_orders(book *b);

int main() {
    init_app();
    return 0;
}

void init_app() {
    book b;
    b.capacity = 10;
    b.count = 0;
    b.o = malloc(b.capacity * sizeof(order));

    exec_prompt(&b);

    free(b.o);
}
void exec_prompt(book *b) {
    printf("Welcome to Order Book\n\n");
    printf("Options: y = yes, q = quit\n\n");
    
    char buffer[8];
    while(1) {
        while(1) {
            printf("Input updates? (y or q): ");
            if(!fgets(buffer, sizeof(buffer), stdin)) {
                fprintf(stderr, "Invalid input.\n");
                continue;
            }
            if(strlen(buffer) == 2 && (buffer[0] == 'y' || buffer[0] == 'Y')) {
                printf("Input: ");
                break;
            } else if(strlen(buffer) == 2 && (buffer[0] == 'q' || buffer[0] == 'Q')) {
                printf("Goodbye!\n");
                return;
            } else {
                printf("Invalid option.\n");
                continue;
            }
        }
        on_clear = 1;
        read_input(b);
        if(on_clear) system(CLEAR);

        printf("Order Book\n");
        printf("+----------+-----------+----------+\n");
        printf("| Position |   Price   | Quantity |\n");
        printf("+----------+-----------+----------+\n");
        for(int i = 0; i < b->count; i++) {
            printf("| %8d | %9.2f | %8d |\n", (i + 1), b->o[i].price, b->o[i].quantity);
            printf("+----------+-----------+----------+\n");
        }
    }
}
void read_input(book *b) {
    char input[128];
    int round = 0;
    char *value;
    operation op;
    int line_number = 1;
    while(fgets(input, sizeof(input), stdin)) {
        char *endptr = NULL;
        input[strcspn(input, "\n")] = '\0';
        if(strlen(input) == 0) continue;

        if(round == 0) {
            round = strtol(input, &endptr, 10);
            if(endptr == input || *endptr != '\0') {
                fprintf(stderr, "Invalid round input: %s\n", input);
                on_clear = 0;
                return;
            }
        } else {
            value = strtok(input, ",");
            op.position = strtol(value, &endptr, 10);
            if(endptr == value || *endptr != '\0') {
                fprintf(stderr, "Invalid position input: %s\n", value);
                on_clear = 0;
                continue;
            }
            value = strtok(NULL, ",");
            op.action = strtol(value, &endptr, 10);
            if(endptr == value || *endptr != '\0') {
                fprintf(stderr, "Invalid action input: %s\n", value);
                on_clear = 0;
                continue;
            }
            value = strtok(NULL, ",");
            op.price = strtod(value, &endptr);
            if(endptr == value || *endptr != '\0') {
                fprintf(stderr, "Invalid price input: %s\n", value);
                on_clear = 0;
                continue;
            }
            value = strtok(NULL, ",");
            op.quantity = strtol(value, &endptr, 10);
            if(endptr == value || *endptr != '\0') {
                fprintf(stderr, "Invalid quantity input: %s\n", value);
                on_clear = 0;
                continue;
            }
            switch(op.action) {
                case 0:
                    if(realloc_book_orders(b) > 0) {
                        on_clear = 0;
                        break;
                    }
                    if(op.position != (b->count + 1)) {
                        fprintf(stderr, "\nInvalid position to insert: %d. Next available is %d. In line %d\n", op.position, (b->count + 1), line_number);
                        on_clear = 0;
                        break;
                    }
                    b->count++;
                case 1:
                    if(op.action == 1 && op.position > b->count) {
                        fprintf(stderr, "\nInvalid position to update: %d. Max used is %d. In line %d\n", op.position, b->count, line_number);
                        on_clear = 0;
                        break;
                    }
                    if(op.price > 0) b->o[op.position - 1].price = op.price;
                    if(op.quantity > 0) b->o[op.position - 1].quantity = op.quantity;
                    break;
                case 2:
                    if(op.position > b->count) {
                        fprintf(stderr, "\nInvalid position to delete: %d. Max used is %d. In line %d\n", op.position, b->count, line_number);
                        on_clear = 0;
                        break;
                    }
                    delete_order(b, op.position - 1);
                    break;
                default:
                    fprintf(stderr, "Invalid action: %d\n", op.action);
                    on_clear = 0;
            }
            if(--round == 0)  {
                line_number = 1;
                return;
            } else {
                line_number++;
            }
        }
    }
}
void delete_order(book *b, int index) {
    for(int i = index; i < b->count - 1; i++) {
        b->o[i] = b->o[i + 1];
    }
    b->count--;
}
int realloc_book_orders(book *b) {
    if(b->capacity > b->count) return 0;
    b->capacity += 10;
    order *temp = realloc(b->o, b->capacity * sizeof(order));
    if(!temp) {
        fprintf(stderr, "Memory reallocation failed.\n");
        return 1;
    }
    b->o = temp;
    return 0;
}
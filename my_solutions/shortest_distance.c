#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_prompt();
int input_values(int **arr, int *arr_len, int *arr_cap, int arr_num);
void get_smallest_distance(int arr_1_size, int *arr_1, int arr_2_size, int *arr_2, int *result);
int get_distance(int num_1, int num_2);

int main() {
    init_prompt();
    return 0;
}
void init_prompt() {
    int status = 0;
    int arr_1_cap;
    int *arr_1 = malloc(10 * sizeof(int));
    if(!arr_1) {
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }
    int arr_1_len;
    int arr_2_cap;
    int *arr_2 = malloc(10 * sizeof(int));
    if(!arr_2) {
        if(arr_1) free(arr_1);
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }
    int arr_2_len;
    char buffer[128];
    printf("Welcome to Shortest distance between two arrays\n");
    int cont = 1;
    while(cont) {
        arr_1_cap = 10;
        arr_1_len = 0;
        arr_2_cap = 10;
        arr_2_len = 0;
        status += input_values(&arr_1, &arr_1_len, &arr_1_cap, 1);
        if(status == 0 && input_values(&arr_2, &arr_2_len, &arr_2_cap, 2) > 0) {
            status++;
        }
        if(status == 0) {
            int result[3];
            get_smallest_distance(arr_1_len, arr_1, arr_2_len, arr_2, result);
            printf("\nMinimum distance: %d (betwween %d in array 1 and %d in array 2)\n", result[0], result[1], result[2]);
        }
        while(1) {
            printf("\nInput again(y), or quit(q)? ");
            if(!fgets(buffer, sizeof(buffer), stdin)) {
                fprintf(stderr, "Error reading input.\n");
                continue;
            }
            if(strlen(buffer) == 2 && (buffer[0] == 'y' || buffer[0] == 'Y' || buffer[0] == 'q' || buffer[0] == 'Q')) {
                if(buffer[0] == 'q' || buffer[0] == 'Q') {
                    printf("Goodbye!\n");
                    cont = 0;
                }
                break;
            } else {
                fprintf(stderr, "Invalid input.\n");
            }
        }
    }
    free(arr_1);
    free(arr_2);
}
int input_values(int **arr, int *arr_len, int *arr_cap, int arr_num) {
    char buffer[128];
    size_t buffer_len;
    size_t capacity = 128;
    char *input = malloc(capacity);
    if(!input) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }
    int input_pos = 0;
    char *stop = NULL;
    char *endptr = NULL;
    char *value;
    int arr_val;
    while(!stop) {
        printf("\nInput the numbers for array %d: ", arr_num);
        if(!fgets(buffer, sizeof(buffer), stdin)) {
            fprintf(stderr, "Error reading input.\n");
            continue;
        }
        if(buffer[0] == '\n') {
            fprintf(stderr, "No input provided.\n");
            continue;
        }
        stop = strchr(buffer, '\n');
        if(stop) {
            buffer[strcspn(buffer, "\n")] = '\0';
        }
        buffer_len = strlen(buffer);
        memcpy(input + input_pos, buffer, buffer_len);
        input_pos += buffer_len;
        if(!stop) {
            capacity += 128;
            input = realloc(input, capacity);
            if(!input) {
                fprintf(stderr, "Memory reallocation failed.\n");
                return 1;
            }
        } else {
            input[input_pos] = '\0';
        }
    }
    value = strtok(input, ",");
    do {
        arr_val = strtol(value, &endptr, 10);
        if(endptr == value || *endptr != '\0') {
            fprintf(stderr, "Invalid number input: %s\n", value);
            free(input);
            return 1;
        } else {
            if(*arr_len >= *arr_cap) {
                *arr_cap += 10;
                int *arr_temp = realloc(*arr, *arr_cap * sizeof(int));
                if(!arr_temp) {
                    fprintf(stderr, "Memory reallocation failed.\n");
                    *arr_cap -= 10;
                    break;
                }
                *arr = arr_temp;
            }
            (*arr)[(*arr_len)++] = arr_val;
        }
    } while(value = strtok(NULL, ","));
    free(input);
    return 0;
}
void get_smallest_distance(int arr_1_size, int *arr_1, int arr_2_size, int *arr_2, int *result) {
    int min = get_distance(arr_1[0], arr_2[0]);
    int arr_1_val = arr_1[0];
    int arr_2_val = arr_2[0];
    for(int i = 0; i < arr_1_size; i++) {
        for(int j = 0; j < arr_2_size; j++) {
            int dist = get_distance(arr_1[i], arr_2[j]);
            if(dist < min) {
                min = dist;
                arr_1_val = arr_1[i];
                arr_2_val = arr_2[j];
            }
        }
    }
    result[0] = min;
    result[1] = arr_1_val;
    result[2] = arr_2_val;
 }
 int get_distance(int num_1, int num_2) {
    return (num_1 > num_2) ? (num_1 - num_2) : (num_2 - num_1);
 }
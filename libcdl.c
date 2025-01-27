#define _GNU_SOURCE
#include "libcdl.h"
#include <stdio.h>


// Оригинальная функция dlopen
void *(*original_dlopen)(const char *, int) = NULL;


// Наша версия dlopen
void *dlopen(const char *filename, int flags) {
    // Получаем адрес оригинальной функции
    if (!original_dlopen) {
        original_dlopen = dlsym(RTLD_NEXT, "dlopen");
    }

    // Логируем вызов
    printf("Перехвачен dlopen: %s\n", filename);

    // Вызываем оригинальную функцию
    return original_dlopen(filename, flags);
}


__attribute__((constructor))
static void init(void) {

    printf(">>> libcdl\n");

    // Получаем адрес оригинальной функции
    if (!original_dlopen) {
        original_dlopen = dlsym(RTLD_NEXT, "dlopen");
    }
}


__attribute__((destructor))
static void fini(void) {
    printf("<<< libcdl\n");
}
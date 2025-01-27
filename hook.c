// Hooks examples. It's an idea source for hook for libcdl.c


#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>

extern struct dlfcn_hook {
    void *(*dlopen)(const char *, int, void *);
    int (*dlclose)(void *);
    void *(*dlsym)(void *, const char *, void *);
    void *(*dlvsym)(void *, const char *, const char *, void *);
    char *(*dlerror)(void);
    int (*dladdr)(const void *, Dl_info *);
    int (*dladdr1)(const void *, Dl_info *, void **, int);
    int (*dlinfo)(void *, int, void *, void *);
    void *(*dlmopen)(Lmid_t, const char *, int, void *);
    void *pad[4];
} *_dlfcn_hook;
static struct dlfcn_hook *old_dlfcn_hook, my_dlfcn_hook;

static int depth;
static void enter(void) { if (!depth++) _dlfcn_hook = old_dlfcn_hook; }
static void leave(void) { if (!--depth) _dlfcn_hook = &my_dlfcn_hook; }

void *my_dlopen(const char *file, int mode, void *dl_caller) {
    void *result;
    fprintf(stderr, "%s(%s, %d, %p)\n", func, file, mode, dl_caller);
    enter();
    result = dlopen(file, mode);
    leave();
    return result;
}

int my_dlclose(void *handle) {
    int result;
    fprintf(stderr, "%s(%p)\n", func, handle);
    enter();
    result = dlclose(handle);
    leave();
    return result;
}

void *my_dlsym(void *handle, const char *name, void *dl_caller) {
    void *result;
    fprintf(stderr, "%s(%p, %s, %p)\n", func, handle, name, dl_caller);
    enter();
    result = dlsym(handle, name);
    leave();
    return result;
}

void *my_dlvsym(void *handle, const char *name, const char *version, void *dl_caller) {
    void *result;
    fprintf(stderr, "%s(%p, %s, %s, %p)\n", func, handle, name, version, dl_caller);
    enter();
    result = dlvsym(handle, name, version);
    leave();
    return result;
}

char *my_dlerror(void) {
    char *result;
    fprintf(stderr, "%s()\n", func);
    enter();
    result = dlerror();
    leave();
    return result;
}

int my_dladdr(const void *address, Dl_info *info) {
    int result;
    fprintf(stderr, "%s(%p, %p)\n", func, address, info);
    enter();
    result = dladdr(address, info);
    leave();
    return result;
}

int my_dladdr1(const void *address, Dl_info *info, void **extra_info, int flags) {
    int result;
    fprintf(stderr, "%s(%p, %p, %p, %d)\n", func, address, info, extra_info, flags);
    enter();
    result = dladdr1(address, info, extra_info, flags);
    leave();
    return result;
}

int my_dlinfo(void *handle, int request, void *arg, void *dl_caller) {
    int result;
    fprintf(stderr, "%s(%p, %d, %p, %p)\n", func, handle, request, arg, dl_caller);
    enter();
    result = dlinfo(handle, request, arg);
    leave();
    return result;
}

void *my_dlmopen(Lmid_t nsid, const char *file, int mode, void *dl_caller) {
    void *result;
    fprintf(stderr, "%s(%lu, %s, %d, %p)\n", func, nsid, file, mode, dl_caller);
    enter();
    result = dlmopen(nsid, file, mode);
    leave();
    return result;
}

static struct dlfcn_hook my_dlfcn_hook = {
    .dlopen   = my_dlopen,
    .dlclose  = my_dlclose,
    .dlsym    = my_dlsym,
    .dlvsym   = my_dlvsym,
    .dlerror  = my_dlerror,
    .dladdr   = my_dladdr,
    .dlinfo   = my_dlinfo,
    .dlmopen  = my_dlmopen,
    .pad      = {0, 0, 0, 0},
};

__attribute__((__constructor__))
static void init(void) {
    old_dlfcn_hook = _dlfcn_hook;
    _dlfcn_hook = &my_dlfcn_hook;
}

__attribute__((__destructor__))
static void fini(void) {
    _dlfcn_hook = old_dlfcn_hook;
}
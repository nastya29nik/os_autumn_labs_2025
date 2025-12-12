#include <dlfcn.h>
#include <stdio.h>

#include "os.h"

LibHandle LibLoad(const char* path) {
    void* handle = dlopen(path, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error loading library '%s': %s\n", path, dlerror());
        return NULL;
    }
    return (LibHandle)handle;
}

void* LibGetSymbol(LibHandle lib, const char* symbol) {
    dlerror();
    void* sym = dlsym((void*)lib, symbol);
    char* error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "Error loading symbol '%s': %s\n", symbol, error);
        return NULL;
    }
    return sym;
}

void LibClose(LibHandle lib) {
    if (lib) {
        dlclose((void*)lib);
    }
}
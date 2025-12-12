#pragma once

typedef void* LibHandle;

LibHandle LibLoad(const char* path);
void* LibGetSymbol(LibHandle lib, const char* symbol);
void LibClose(LibHandle lib);
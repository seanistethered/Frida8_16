/*
 Frida16_32 Project
 
 MIT License

 Copyright (c) 2025 FridaDEV

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#include "RAM/mem.h"
#include "CPU/cpu.h"
#include "LZC/lazy_compiler.h"
#include "LZC/function_compiler.h"
#include "LZC/header_compiler.h"

int main(void)
{
    // compile code
    const char *args_print_func[][10] = {
        {"load", "a", "0"},
        {"loop"},
        {"isgreater", "p", "a", "6"},
        {"return"},
        {"output", "p"},
        {"end"},
        {NULL, NULL}
    };
    compile_function("print", args_print_func);
    
    const char *args_main[][10] = {
        {"call", "print", "Hello\n"},
        {NULL, NULL}
    };
    compile_function("main", args_main);
    
    // compile header
    compile_header();
    
    // initial code
    core_t *core = malloc(sizeof(core_t));
    
    // fixing execution the lazy compiler destroys currently
    core_setup(core, 0b00000001);
    core_run(core);
    free(core);
    return 0;
}

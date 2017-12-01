/*
    This file is part of Corrade.

    Copyright © 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016,
                2017 Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include "Corrade/configure.h"

#ifdef CORRADE_TARGET_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

extern "C" int main(int, char**);

/* extern "C" needed for MinGW -- https://sourceforge.net/p/mingw-w64/wiki2/Unicode%20apps/ */
extern "C" int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int);
extern "C" int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
   szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
   if( NULL == szArglist )
   {
      wprintf(L"CommandLineToArgvW failed\n");
      return 0;
   }
   else for( i=0; i<nArgs; i++) printf("%d: %ws\n", i, szArglist[i]);

// Free memory allocated for CommandLineToArgvW arguments.

   LocalFree(szArglist);

    return main(argc, argv);
}

extern "C" int wmain(int, wchar_t*);
extern "C" int wmain(int argc, wchar_t* wargv) {
    return main(argc, argv);
}
#endif

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>

#include "TextEditor.h"
#include "Console.h"
#include "FileHandler.h"
#include "Encryption.h"
#include "Caesar-Encryption-Algorithm-DLL.h"

using namespace std;

int main() {
    TextEditor editor{};
    Console console;
    FileHandler fileHandler;
    Encryption encryption{};

    console.run(editor, fileHandler, encryption);

    return 0;
}
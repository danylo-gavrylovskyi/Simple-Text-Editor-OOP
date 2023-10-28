#include <iostream>
#include <windows.h>
#include "Caesar-Encryption-Algorithm-DLL.h"
#include "Encryption.h"

using namespace std;

Encryption::Encryption() : handle(nullptr), encrypt_ptr(nullptr), decrypt_ptr(nullptr) {
    handle = LoadLibrary(TEXT("Caesar-Encryption-Algorithm-DLL.dll"));
    if (handle != nullptr && handle != INVALID_HANDLE_VALUE) {
        encrypt_ptr = (encrypt_ptr_t)GetProcAddress(handle, "encrypt");
        decrypt_ptr = (decrypt_ptr_t)GetProcAddress(handle, "decrypt");
    }
}

Encryption::~Encryption() {
    if (handle) {
        FreeLibrary(handle);
    }
}

void Encryption::encrypt(char textToEncrypt[256], int key) {
    if (key < 1 || key > 26) {
        key = key % 25 + 1;
    }
    encrypt_ptr(textToEncrypt, key);
}

void Encryption::decrypt(char textToDecrypt[256], int key) {
    if (key < 1 || key > 26) {
        key = key % 25 + 1;
    }
    decrypt_ptr(textToDecrypt, key);
}

#pragma once

#include <iostream>
#include <windows.h>
#include "Caesar-Encryption-Algorithm-DLL.h"

using namespace std;

class Encryption {
    HINSTANCE handle;
    typedef void(*encrypt_ptr_t)(char*, int);
    typedef void(*decrypt_ptr_t)(char*, int);
    encrypt_ptr_t encrypt_ptr;
    decrypt_ptr_t decrypt_ptr;
public:
    Encryption();

    ~Encryption();

    void encrypt(char textToEncrypt[256], int key);

    void decrypt(char textToDecrypt[256], int key);
};

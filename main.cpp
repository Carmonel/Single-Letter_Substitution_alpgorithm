#include "MyCipher.h"
#define N 256

int main() {
    MyCipher cipher;
    cipher.encode("C:\\Users\\Ярослав\\Documents\\Учеба\\Семестр 5\\Криптография\\in",
            "C:\\Users\\Ярослав\\Documents\\Учеба\\Семестр 5\\Криптография\\out");
    cipher.decode("C:\\Users\\Ярослав\\Documents\\Учеба\\Семестр 5\\Криптография\\out",
                  "C:\\Users\\Ярослав\\Documents\\Учеба\\Семестр 5\\Криптография\\new");

    // Check for changing keys
    cipher.printKeysFromFile("C:\\Users\\Ярослав\\Documents\\Учеба\\Семестр 5\\Криптография\\out");
    cipher.changeKeyInEcodedFile("C:\\Users\\Ярослав\\Documents\\Учеба\\Семестр 5\\Криптография\\out", 1, 2);
    cipher.printKeysFromFile("C:\\Users\\Ярослав\\Documents\\Учеба\\Семестр 5\\Криптография\\out");
    cipher.decode("C:\\Users\\Ярослав\\Documents\\Учеба\\Семестр 5\\Криптография\\out",
            "C:\\Users\\Ярослав\\Documents\\Учеба\\Семестр 5\\Криптография\\outNew");
}

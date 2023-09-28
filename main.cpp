#include "MyCipher.h"
#define N 256

int main() {
    MyCipher cipher;
    cipher.encode("C:\\Users\\Ярослав\\Documents\\Учеба\\Семестр 5\\Криптография\\in",
            "C:\\Users\\Ярослав\\Documents\\Учеба\\Семестр 5\\Криптография\\out");
    cipher.decode("C:\\Users\\Ярослав\\Documents\\Учеба\\Семестр 5\\Криптография\\out",
                  "C:\\Users\\Ярослав\\Documents\\Учеба\\Семестр 5\\Криптография\\new");
}

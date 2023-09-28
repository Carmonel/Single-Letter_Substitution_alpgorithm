#include "MyCipher.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::string byteToStr(unsigned char byte){
    std::ostringstream str;
    if (byte < 0x10) str << "0" << std::hex << std::uppercase << (int)byte;
    else str << std::hex << std::uppercase << (int)byte;

    return str.str();
}


MyCipher::MyCipher() {
    newRandomKeys();
}

void MyCipher::newRandomKeys() {
    srand(time(nullptr));
    bool checker[N] = {false};
    std::cout << "New table:" << std::endl;
    for (int i = 0; i < N; i++){
        int tmp = (int)(rand() % N);
        while (checker[tmp]){
            tmp = (int)(rand() % N);
        }
        alphabet[i] = tmp;
        checker[tmp] = true;

        std::cout << byteToStr(i) << " -> " << byteToStr(alphabet[i]) << std::endl;
    }
}

void MyCipher::encode(const std::string& inputPath, const std::string& outputPath) {
    std::ifstream inputFile;
    std::ofstream outputFile;
    try{
        inputFile.open(inputPath, std::ios::binary | std::ios::in);
    }
    catch(std::exception& e){
        std::cout << "inputFile.open() error: " << e.what() << std::endl;
        std::cout << std::endl << "inputPath: " << inputPath;
        exit(-1);
    }
    try{
        outputFile.open(outputPath, std::ios::binary | std::ios::out);
    }
    catch(std::exception& e){
        std::cout << "outputFile.open() error: " << e.what() << std::endl;
        std::cout << "outputPath: " << outputPath;
        exit(-1);
    }
    if (!inputFile.is_open()){
        std::cout << "inputFile.is_open() returned false." << std::endl;
        std::cout << std::endl << "inputPath: " << inputPath;
        exit(-1);
    }
    if (!outputFile.is_open()){
        std::cout << "outputFile.is_open() returned false." << std::endl;
        std::cout << "outputPath: " << outputPath;
        exit(-1);
    }

    // Write keys
    for (int i = 0; i < N; i++){
        outputFile.put(alphabet[i]);
    }
    // Write data
    unsigned char byte;
    while (inputFile.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
        outputFile.put(alphabet[byte]);
    }
    std::cout << "Encoded file created." << std::endl;

    inputFile.close();
    outputFile.close();
}

void MyCipher::decode(const std::string& inputPath, const std::string& outputPath) {
    std::ifstream inputFile;
    std::ofstream outputFile;
    try{
        inputFile.open(inputPath, std::ios::binary | std::ios::in);
    }
    catch(std::exception& e){
        std::cout << "inputFile.open() error: " << e.what() << std::endl;
        std::cout << std::endl << "inputPath: " << inputPath;
        exit(-1);
    }
    try{
        outputFile.open(outputPath, std::ios::binary | std::ios::out);
    }
    catch(std::exception& e){
        std::cout << "outputFile.open() error: " << e.what() << std::endl;
        std::cout << "outputPath: " << outputPath;
        exit(-1);
    }
    if (!inputFile.is_open()){
        std::cout << "inputFile.is_open() returned false." << std::endl;
        std::cout << std::endl << "inputPath: " << inputPath;
        exit(-1);
    }
    if (!outputFile.is_open()){
        std::cout << "outputFile.is_open() returned false." << std::endl;
        std::cout << "outputPath: " << outputPath;
        exit(-1);
    }

    // Read and save keys
    unsigned char byte;
    for (int i = 0; i < N; i++){
        inputFile.read(reinterpret_cast<char*>(&byte), sizeof(byte));
        alphabet[i] = byte;
    }
    // Write data
    while (inputFile.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
        int pos = 0;
        while (alphabet[pos] != byte){
            if (pos >= N){
                std::cout << "Not finded key from encoded file.";
                exit(-1);
            }
            pos++;
        }
        outputFile.put(pos);
    }
    std::cout << "Decoded file created." << std::endl;

    inputFile.close();
    outputFile.close();
}

void MyCipher::newCustomKeys() {
    std::cout << "Print keys:" << std::endl;
    for (int i = 0; i < N; i++){
        if (i < 0x10) std::cout << "0" << std::hex << std::uppercase << i;
        else std::cout << std::hex << std::uppercase << i;
        std::cout << " = ";
        std::cin >> alphabet[i];
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void MyCipher::changeKeyInEcodedFile(const std::string& filePath, unsigned char byte, unsigned char newByte) {
    std::cout << "Starting changing: " << byteToStr(byte) << " -> " << byteToStr(newByte) << "; and " << byteToStr(newByte) << " -> " << byteToStr(byte) << std::endl;

    std::fstream file;
    try{
        file.open(filePath, std::ios::binary | std::ios::in | std::ios::out);
    }
    catch(std::exception& e){
        std::cout << "file.open() error: " << e.what() << std::endl;
        std::cout << std::endl << "inputPath: " << filePath;
        exit(-1);
    }
    if (!file.is_open()){
        std::cout << "inputFile.is_open() returned false." << std::endl;
        std::cout << std::endl << "inputPath: " << filePath;
        exit(-1);
    }

    // alphabet[byte] = newByte
    unsigned char tmp;
    for (int i = 0; i < byte; i++) file.read(reinterpret_cast<char*>(&tmp), 1);
    file.put(newByte);
    file.seekg(std::ios::beg);
    // alphabet[newByte] = byte
    for (int i = 0; i < newByte; i++) file.read(reinterpret_cast<char*>(&tmp), 1);
    file.put(byte);
    file.seekg(std::ios::beg);
    for (int i = 0; i < N; i++) file.read(reinterpret_cast<char*>(&tmp), 1);
    // reading data and replacing bytes
    while (file.read(reinterpret_cast<char*>(&tmp), 1)){
        if (tmp == byte) file.put(newByte);
        else if (tmp == newByte) file.put(byte);
    }

    std::cout << "Replacing competed." << std::endl;

    file.close();
}

void MyCipher::printKeys() {
    std::cout << "Keys:" << std::endl;
    for (int i = 0; i < N; i++){
        std::cout << byteToStr(i) << " = " << byteToStr(alphabet[i]);
    }
}

void MyCipher::printKeysFromFile(const std::string &filePath) {
    std::cout << "Keys from file '" << filePath << "':" << std::endl;
    std::ifstream file;
    try{
        file.open(filePath, std::ios::binary | std::ios::in);
    }
    catch(std::exception& e){
        std::cout << "file.open() error: " << e.what() << std::endl;
        std::cout << std::endl << "inputPath: " << filePath;
        exit(-1);
    }
    if (!file.is_open()){
        std::cout << "inputFile.is_open() returned false." << std::endl;
        std::cout << std::endl << "inputPath: " << filePath;
        exit(-1);
    }

    unsigned char byte;
    for (int i = 0; i < N; i++){
        file.read(reinterpret_cast<char*>(&byte), 1);
        std::cout << byteToStr(i) << " = " << byteToStr(byte) << std::endl;
    }

    file.close();
}

MyCipher::~MyCipher() = default;

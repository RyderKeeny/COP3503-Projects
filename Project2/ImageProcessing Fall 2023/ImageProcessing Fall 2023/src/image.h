#pragma once
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Header {
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};
   
struct Pixel {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
};

class Image {

public:
    Header header;
    vector<Pixel> pixels;

    Image();
    void read(const string& inName);
    void write(const string& outName);
    // setting the return type to be a class instance, so it makes calling it in the main() easier
    Image multiply(const Image& file1, const Image& file2); 
    Image screen(const Image& file1, const Image& file2);
    Image subtract(const Image& file1, const Image& file2);
    Image addition(const Image& file1, const Image& file2);
    Image overlay(const Image& file1, const Image& file2);
    Image scaleBlue(const Image& file, int var);
    Image scaleGreen(const Image& file, int var);
    Image scaleRed(const Image& file, int var);
    Image addBlue(const Image& file, int var);
    Image addGreen(const Image& file, int var);
    Image addRed(const Image& file, int var);
    Image onlyBlue(const Image& file);
    Image onlyGreen(const Image& file);
    Image onlyRed(const Image& file);

    Image combine(const Image& file1, const Image& file2, const Image& file3);
    Image flip(const Image& file);



};

#include "image.h"
#include <iostream>


Image::Image() {}

void Image::read(const string& inName) {
    //(14) Read in the .tga file
    ifstream stream(inName, ios_base::binary);

    //(15) Check if the file is opening
    if (!stream.is_open()) {
        cout << "file is not open :(" << endl;
    }
    
    //(16) Read in each element of the .tga file
    stream.read(&header.idLength, sizeof(header.idLength));
    stream.read(&header.colorMapType, sizeof(header.colorMapType));
    stream.read(&header.dataTypeCode, sizeof(header.dataTypeCode));
    stream.read((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
    stream.read((char*)&header.colorMapLength, sizeof(header.colorMapLength));
    stream.read(&header.colorMapDepth, sizeof(header.colorMapDepth));
    stream.read((char*)&header.xOrigin, sizeof(header.xOrigin));
    stream.read((char*)&header.yOrigin, sizeof(header.yOrigin));
    stream.read((char*)&header.width, sizeof(header.width));
    stream.read((char*)&header.height, sizeof(header.height));
    stream.read(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
    stream.read(&header.imageDescriptor, sizeof(header.imageDescriptor));
    
    int imageSize = (int)(header.width * header.height);

    //(18) Create a for loop to read in all the pixels
    for (int i = 0; i < imageSize; i++) {
        Pixel pixel;

        stream.read((char*)& pixel.blue, sizeof(pixel.blue));
        stream.read((char*)& pixel.green, sizeof(pixel.green));
        stream.read((char*)& pixel.red, sizeof(pixel.red));

        pixels.push_back(pixel);
    }
    
}

void Image::write(const string& outName) {
    //(22) Create a .tga file
    ofstream stream(outName, ios_base::binary);

    //(23) Write out each .tga file header element
    stream.write(&header.idLength, sizeof(header.idLength));
    stream.write(&header.colorMapType, sizeof(header.colorMapType));
    stream.write(&header.dataTypeCode,sizeof(header.dataTypeCode));
    stream.write((char*)&header.colorMapOrigin,sizeof(header.colorMapOrigin));
    stream.write((char*)&header.colorMapLength,sizeof(header.colorMapLength));
    stream.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
    stream.write((char*)&header.xOrigin, sizeof(header.xOrigin));
    stream.write((char*)&header.yOrigin, sizeof(header.yOrigin));
    stream.write((char*)&header.width, sizeof(header.width));
    stream.write((char*)&header.height, sizeof(header.height));
    stream.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel) );
    stream.write(&header.imageDescriptor, sizeof(header.imageDescriptor));

    //(24) Create a for loop to write out each pixel
    for (int i = 0; i < pixels.size(); i++) {
        Pixel pixel = pixels[i];

        stream.write((char*)& pixel.blue, sizeof(pixel.blue));
        stream.write((char*)& pixel.green, sizeof(pixel.green));
        stream.write((char*)& pixel.red, sizeof(pixel.red));
    }
        
        //(25) Write out each image pixel

}

Image Image::multiply(const Image& file1, const Image& file2){
    if (file1.header.width != file2.header.width || file1.header.height != file2.header.height) {
        cout << "Images must be of the same dimensions to multiply." << endl;
        return Image();
    }

    Image result;
    result.header = file1.header;

    for (unsigned int i = 0; i < file1.pixels.size(); i++){
        Pixel color;
        float mulBlue = ((file1.pixels[i].blue / 255.0f) * (file2.pixels[i].blue / 255.0f));
        float mulGreen = ((file1.pixels[i].green / 255.0f) * (file2.pixels[i].green / 255.0f));
        float mulRed = ((file1.pixels[i].red / 255.0f) * (file2.pixels[i].red / 255.0f));

        color.blue = static_cast<unsigned char>((mulBlue * 255) + 0.5f);
        color.green = static_cast<unsigned char>((mulGreen * 255) + 0.5f);
        color.red = static_cast<unsigned char>((mulRed * 255) + 0.5f);

        result.pixels.push_back(color);
    }

    return result;
}

Image Image::screen(const Image& file1, const Image& file2){
    if (file1.header.width != file2.header.width || file1.header.height != file2.header.height) {
        cout << "Images must be of the same dimensions to screen blend." << endl;
        return Image();
    }

    Image result;
    result.header = file1.header;

    for (unsigned int i = 0; i < file1.pixels.size(); i++){
        Pixel color;
        float scrBlue = 1.0f - (1.0f - file1.pixels[i].blue/255.0f) * (1.0f - file2.pixels[i].blue/255.0f);
        float scrGreen = 1.0f - (1.0f - file1.pixels[i].green/255.0f) * (1.0f - file2.pixels[i].green/255.0f);
        float scrRed = 1.0f - (1.0f - file1.pixels[i].red/255.0f) * (1.0f - file2.pixels[i].red/255.0f);

        // Denormalize, round, and clamp to [0, 255]
        color.blue = static_cast<unsigned char>(max(0.0f, min(255.0f, ((scrBlue * 255) + 0.5f))));
        color.green = static_cast<unsigned char>(max(0.0f, min(255.0f, ((scrGreen * 255) + 0.5f))));
        color.red = static_cast<unsigned char>(max(0.0f, min(255.0f, ((scrRed * 255) + 0.5f))));

        result.pixels.push_back(color);
    }

    return result;
}

Image Image::subtract(const Image& file1, const Image& file2){
    if (file1.header.width != file2.header.width || file1.header.height != file2.header.height) {
        cout << "Images must be of the same dimensions to subtract." << endl; // Modified the error message
        return Image();
    }

    Image result;
    result.header = file1.header;

    for (unsigned int i = 0; i < file1.pixels.size(); i++){
        Pixel color; 
        
        // Blue channel
        int tempBlue = static_cast<int>(file1.pixels[i].blue) - static_cast<int>(file2.pixels[i].blue);
        color.blue = static_cast<unsigned char>(max(0, tempBlue));
        
        // Green channel
        int tempGreen = static_cast<int>(file1.pixels[i].green) - static_cast<int>(file2.pixels[i].green);
        color.green = static_cast<unsigned char>(max(0, tempGreen));

        // Red channel
        int tempRed = static_cast<int>(file1.pixels[i].red) - static_cast<int>(file2.pixels[i].red);
        color.red = static_cast<unsigned char>(max(0, tempRed));

        result.pixels.push_back(color);
    }

    return result;
}

Image Image::addition(const Image& file1, const Image& file2){
    if (file1.header.width != file2.header.width || file1.header.height != file2.header.height) {
        cout << "Images must be of the same dimensions to add together." << endl;
        return Image();
    }

    Image result;
    result.header = file1.header;

    for (unsigned int i = 0; i < file1.pixels.size(); i++){
        Pixel color;
        
        // Blue channel
        int tempBlue = static_cast<int>(file1.pixels[i].blue) + static_cast<int>(file2.pixels[i].blue);
        color.blue = static_cast<unsigned char>(min(255, max(0, tempBlue)));
        
        // Green channel
        int tempGreen = static_cast<int>(file1.pixels[i].green) + static_cast<int>(file2.pixels[i].green);
        color.green = static_cast<unsigned char>(min(255, max(0, tempGreen)));

        // Red channel
        int tempRed = static_cast<int>(file1.pixels[i].red) + static_cast<int>(file2.pixels[i].red);
        color.red = static_cast<unsigned char>(min(255, max(0, tempRed)));

        result.pixels.push_back(color);    
    }

    return result;
}

Image Image::overlay(const Image& file1, const Image& file2){
    if (file1.header.width != file2.header.width || file1.header.height != file2.header.height) {
        cout << "Images must be of the same dimensions to overlay blend." << endl;
        return Image();
    }

    Image result;
    result.header = file1.header;

    for (unsigned int i = 0; i < file1.pixels.size(); i++){
        Pixel color;
        
        // Blue channel
        float overBlue = (file2.pixels[i].blue/255.0f);
        float baseBlue = (file1.pixels[i].blue/255.0f);
        if (overBlue <= 0.5f) {
            color.blue = static_cast<unsigned char>(255 * (2 * baseBlue * overBlue) + 0.5f);
        } 
        
        else {
            color.blue = static_cast<unsigned char>(255 * (1 - 2 * (1 - baseBlue) * (1 - overBlue)) + 0.5f);
        }
        
        // Green channel
        float overGreen = (file2.pixels[i].green/255.0f);
        float baseGreen = (file1.pixels[i].green/255.0f);
        if (overGreen <= 0.5f) {
            color.green = static_cast<unsigned char>(255 * (2 * baseGreen * overGreen) + 0.5f);
        } 
        
        else {
            color.green = static_cast<unsigned char>(255 * (1 - 2 * (1 - baseGreen) * (1 - overGreen)) + 0.5f);
        }
        
        // Red channel
        float overRed = (file2.pixels[i].red/255.0f);
        float baseRed = (file1.pixels[i].red/255.0f);
        if (overRed <= 0.5f) {
            color.red = static_cast<unsigned char>(255 * (2 * baseRed * overRed) + 0.5f);
        } 
        
        else {
            color.red = static_cast<unsigned char>(255 * (1 - 2 * (1 - baseRed) * (1 - overRed)) + 0.5f);
        }

        result.pixels.push_back(color);
    }

    return result;
}

Image Image::scaleBlue(const Image& file, int var){
    Image result;
    result.header = file.header;

    Pixel color;
    for (unsigned int i = 0; i < file.pixels.size(); i++){
        int newBlue = (file.pixels[i].blue * var);
        color.blue = static_cast<unsigned char>(min(newBlue, 255));
        color.green = file.pixels[i].green;
        color.red = file.pixels[i].red;

        result.pixels.push_back(color);
    }
    
    return result;
}

Image Image::scaleGreen(const Image& file, int var){
    Image result;
    result.header = file.header;

    Pixel color;
    for (unsigned int i = 0; i < file.pixels.size(); i++){
        int newGreen = (file.pixels[i].green * var);
        color.blue = file.pixels[i].blue;
        color.green = static_cast<unsigned char>(min(newGreen, 255));
        color.red = file.pixels[i].red;

        result.pixels.push_back(color);
    }
    
    return result;
}

Image Image::scaleRed(const Image& file, int var){
    Image result;
    result.header = file.header;

    Pixel color;
    for (unsigned int i = 0; i < file.pixels.size(); i++){
        int newRed = (file.pixels[i].red * var);
        color.blue = file.pixels[i].blue;
        color.green = file.pixels[i].green;
        color.red = static_cast<unsigned char>(min(newRed, 255));

        result.pixels.push_back(color);
    }
    
    return result;
}

Image Image::addBlue(const Image& file, int var){
    Image result;
    result.header = file.header;

    Pixel color;
    for (unsigned int i = 0; i < file.pixels.size(); i++){
        int newBlue = (file.pixels[i].blue + var);
        color.blue = static_cast<unsigned char>(min(newBlue, 255));
        color.green = file.pixels[i].green;
        color.red = file.pixels[i].red;

        result.pixels.push_back(color);
    }
    
    return result;
}

Image Image::addGreen(const Image& file, int var){
    Image result;
    result.header = file.header;
    Pixel color;
    for (unsigned int i = 0; i < file.pixels.size(); i++){
        int newGreen = (file.pixels[i].green + var);
        color.blue = file.pixels[i].blue;
        color.green = static_cast<unsigned char>(min(newGreen, 255));
        color.red = file.pixels[i].red;

        result.pixels.push_back(color);
    }
    
    return result;
}

Image Image::addRed(const Image& file, int var){
    Image result;
    result.header = file.header;

    Pixel color;
    for (unsigned int i = 0; i < file.pixels.size(); i++){
        int newRed = (file.pixels[i].red + var);
        color.blue = file.pixels[i].blue;
        color.green = file.pixels[i].green;
        color.red = static_cast<unsigned char>(min(newRed, 255));

        result.pixels.push_back(color);
    }
    
    return result;
}

Image Image::onlyBlue(const Image& file){
    Image result;
    result.header = file.header;

    Pixel color;
    for (unsigned int i = 0; i < file.pixels.size(); i++){
        color.blue = file.pixels[i].blue;
        color.green = file.pixels[i].blue;
        color.red = file.pixels[i].blue;

        result.pixels.push_back(color);
    }
    
    return result;
}

Image Image::onlyGreen(const Image& file){
    Image result;
    result.header = file.header;

    Pixel color;
    for (unsigned int i = 0; i < file.pixels.size(); i++){
        color.blue = file.pixels[i].green;
        color.green = file.pixels[i].green;
        color.red = file.pixels[i].green;

        result.pixels.push_back(color);
    }
    
    return result;
}

Image Image::onlyRed(const Image& file){
    Image result;
    result.header = file.header;

    Pixel color;
    for (unsigned int i = 0; i < file.pixels.size(); i++){
        color.blue = file.pixels[i].red;
        color.green = file.pixels[i].red;
        color.red = file.pixels[i].red;

        result.pixels.push_back(color);
    }
    
    return result;
}

Image Image::combine(const Image& blueFile, const Image& greenFile, const Image& redFile){
    if (blueFile.header.width != greenFile.header.width || blueFile.header.height != greenFile.header.height || blueFile.header.width != redFile.header.width || blueFile.header.height != redFile.header.height) {
        cout << "Images must be of the same dimensions to combine." << endl;
        return Image();
    }

    Image result;
    result.header = blueFile.header;

    Pixel color;

    for (unsigned int i = 0; i < blueFile.pixels.size(); i++){
        color.blue = blueFile.pixels[i].blue;
        color.green = greenFile.pixels[i].green;
        color.red = redFile.pixels[i].red;

        result.pixels.push_back(color);
    }

    return result;
}

Image Image::flip(const Image& file){
    Image result;
    result.header = file.header; 

    for (int i = file.pixels.size() - 1; i >= 0; i--) {
        result.pixels.push_back(file.pixels[i]);
    }

    return result;
}

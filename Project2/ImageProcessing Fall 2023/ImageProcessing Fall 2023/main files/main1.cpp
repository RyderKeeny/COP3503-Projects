#include "image.h"
#include <iostream>
using namespace std;

int main() {
    // Define input image filenames
    const string layer1File = "input/layer1.tga";
    const string layer2File = "input/layer2.tga";
    const string pattern1File = "input/pattern1.tga";
    const string pattern2File = "input/pattern2.tga";
    const string carFile = "input/car.tga";
    const string circlesFile = "input/circles.tga";
    const string text1File = "input/text.tga";
    const string text2File = "input/text2.tga";
    const string greenFile = "input/layer_green.tga";
    const string blueFile = "input/layer_blue.tga";
    const string redFile = "input/layer_red.tga";

    Image layer1, layer2, pattern1, pattern2, car, circles, text1, text2, green, blue, red; 
    pattern1.read(pattern1File);
    pattern2.read(pattern2File);
    layer1.read(layer1File);
    layer2.read(layer2File);
    car.read(carFile);
    circles.read(circlesFile);
    text1.read(text1File);
    text2.read(text2File);
    green.read(greenFile);
    blue.read(blueFile);
    red.read(redFile);


    // task1
    Image multiplied = layer1.multiply(layer1, pattern1);
    multiplied.write("output/part1.tga");

    //task2
    Image task2 = car.subtract(car, layer2);
    task2.write("output/part2.tga");

    //task3
    Image task3a = layer1.multiply(layer1, pattern2);
    Image task3b = task3a.screen(task3a, text1);
    task3b.write("output/part3.tga");

    //task4
    Image task4a = layer2.multiply(layer2, circles);
    Image task4b = task4a.subtract(task4a, pattern2);
    task4b.write("output/part4.tga");

    //task5
    Image task5 = layer1.overlay(layer1, pattern1);
    task5.write("output/part5.tga");

    //task6 
    Image task6 = car.addGreen(car, 200);
    task6.write("output/part6.tga");

    //task7 
    Image task7a = car.scaleRed(car, 4);
    Image task7b = task7a.scaleBlue(task7a, 0);
    task7b.write("output/part7.tga");

    //task8 
    Image task8red = car.onlyRed(car);
    Image task8green = car.onlyGreen(car); 
    Image task8blue = car.onlyBlue(car);
    task8blue.write("output/part8_b.tga");
    task8green.write("output/part8_g.tga");
    task8red.write("output/part8_r.tga");

    //task9 
    Image task9 = blue.combine(blue, green, red);
    task9.write("output/part9.tga");

    //task10
    Image task10 = text2.flip(text2);
    task10.write("output/part10.tga");

    cout << "tasks completed. Check the output files for results." << std::endl;

    return 0;
}


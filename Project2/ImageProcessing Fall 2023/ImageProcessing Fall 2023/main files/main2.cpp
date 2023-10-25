#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include "image.h"
#include "image.cpp"
using namespace std;


int main(int argCount, const char* argValue[]) {

    if (argCount <= 1 || string(argValue[1]) == "--help") {
        cout << "Project 2: Image Processing, Fall 2023" << endl
             << endl
             << "Usage:" << endl
             << "\t" << "./project2.out [output] [firstImage] [method] [...]" << endl; 
        return 0;
    }

    string outDir = argValue[1];
    int outDirSize = outDir.size();
    string trackingFile = argValue[2];
    int trackingFileSize = trackingFile.size();

        //testing incorrect output file name w/out .tga
    if (outDir.substr((outDirSize - 4), 4) != ".tga") { 
        cout << "Invalid file name." << endl;
        return 0;
    }
        //testing incorrect tracking file name w/out .tga
    if (trackingFile.substr((trackingFileSize - 4), 4) != ".tga") { 
        cout << "Invalid file name." << endl;
        return 0;
    }
        //testing to see if it is a real file
    ifstream startingFile(argValue[2], ios_base::binary);
    if (!startingFile.is_open()) {
        cout << "Invalid argument, file does not exist." << endl;
        return 0;
    }


    if (string(argValue[3]) == "multiply") {
        Image mul1;
        Image mul2;
        mul1.read(argValue[2]);
        mul2.read(argValue[4]);
        Image outputFile;
        outputFile = mul1.multiply(mul1, mul2);
        outputFile.write(argValue[1]);
        cout << "Multiplying " << argValue[1] << " and " << argValue[4] << " ..." << endl;
    }

    else if (string(argValue[3]) == "subtract") {
        Image sub1;
        Image sub2;
        sub1.read(argValue[2]);
        sub2.read(argValue[4]);
        Image outputFile;
        outputFile = sub1.subtract(sub1, sub2);
        outputFile.write(argValue[1]);        
        cout << "Subtracting " << argValue[1] << " and " << argValue[4] << " ..." << endl;
    }

    else if (string(argValue[3]) == "overlay") {
        Image ovl1;
        Image ovl2;
        ovl1.read(argValue[2]);
        ovl2.read(argValue[4]);
        Image outputFile;
        outputFile = ovl1.overlay(ovl1, ovl2);
        outputFile.write(argValue[1]);        
    
    }

    else if (string(argValue[3]) == "screen") {
        Image scr1;
        Image scr2;
        scr1.read(argValue[2]);
        scr2.read(argValue[4]);
        Image outputFile;
        outputFile = scr1.screen(scr1, scr2);
        outputFile.write(argValue[1]);  

    }

    else if (string(argValue[3]) == "combine") {
        Image com1;
        Image com2;
        Image com3;
        com1.read(argValue[2]);
        com2.read(argValue[4]);
        com3.read(argValue[5]);
        Image outputFile;
        outputFile = com1.combine(com1, com2, com3);
        outputFile.write(argValue[1]);
    
    }

        //needs to be within its own for loop cause it doesnt take in any other input files for it so i can be back to back
    else if (string(argValue[3]) == "flip") {
        Image inputFile;
        Image outputFile;
        inputFile.read(argValue[2]);
        outputFile = inputFile.flip(inputFile);
        outputFile.write(argValue[1]);
        cout << "... and flipping output of previous step ..." << endl;
    }


    else if (string(argValue[3]) == "onlyred") {
        Image inputFile;
        Image outputFile;
        inputFile.read(argValue[2]);
        outputFile = inputFile.onlyRed(inputFile);
    }

    else if (string(argValue[3]) == "onlygreen") {
        Image inputFile;
        Image outputFile;
        inputFile.read(argValue[2]);
        outputFile = inputFile.onlyGreen(inputFile);        
    }

    else if (string(argValue[3]) == "onlyblue") {
        Image inputFile;
        Image outputFile;
        inputFile.read(argValue[3]);
        outputFile = inputFile.onlyBlue(inputFile);        
    }

    else if (string(argValue[3]) == "addred") {
        Image inputFile;
        Image outputFile;
        int colorVariable = stoi(string(argValue[4]));
        inputFile.read(argValue[2]);
        outputFile = inputFile.addRed(inputFile, colorVariable);
        cout << "... and adding +" << colorVariable << " to red channel of previous step ..." << endl;
    }

    else if (string(argValue[3]) == "addgreen") {
        Image inputFile;
        Image outputFile;
        int colorVariable = stoi(string(argValue[4]));
        inputFile.read(argValue[2]);
        outputFile = inputFile.addGreen(inputFile, colorVariable); 
        cout << "... and adding +" << colorVariable << " to green channel of previous step ..." << endl;       
    }

    else if (string(argValue[3]) == "addblue") {
        Image inputFile;
        Image outputFile;
        int colorVariable = stoi(string(argValue[4]));
        inputFile.read(argValue[2]);
        outputFile = inputFile.addBlue(inputFile, colorVariable);
        cout << "... and adding +" << colorVariable << " to blue channel of previous step ..." << endl;        
    }

    else if (string(argValue[3]) == "scalered") {
        Image inputFile;
        Image outputFile;
        int colorVariable = stoi(string(argValue[4]));

        inputFile.read(argValue[2]);
        outputFile = inputFile.scaleRed(inputFile, colorVariable);  
        cout << "Scaling the red channel of previous step by " << colorVariable << " ..." << endl;      

    }

    else if (string(argValue[3]) == "scalegreen") {
        Image inputFile;
        Image outputFile;
        int colorVariable = stoi(string(argValue[4]));
        inputFile.read(argValue[2]);
        outputFile = inputFile.scaleGreen(inputFile, colorVariable); 
        cout << "Scaling the green channel of previous step by " << colorVariable << " ..." << endl;      
    }    

    else if (string(argValue[3]) == "scaleblue") {
        Image inputFile;
        Image outputFile;
        int colorVariable = stoi(string(argValue[4]));

        inputFile.read(argValue[2]);
        outputFile = inputFile.scaleBlue(inputFile, colorVariable);   
        cout << "Scaling the blue channel of previous step by " << colorVariable << " ..." << endl;      

    }    

    else {
        cout << "Invalid method name." << endl;
        return 0;

    }

    for (size_t i = 4; i < argCount; i++) { // for loop to run through multiple methods after the first possible method that is called
        if (string(argValue[i]) == "multiply") {
            Image mul1;
            Image mul2;
            mul1.read(argValue[1]);
            mul2.read(argValue[i + 1]);
            Image outputFile;
            outputFile = mul1.multiply(mul1, mul2);
            outputFile.write(argValue[1]);
            cout << "Multiplying " << argValue[1] << " and " << argValue[i + 1] << " ..." << endl;
        }

        else if (string(argValue[i]) == "subtract") {
            Image sub1;
            Image sub2;
            sub1.read(argValue[1]);
            sub2.read(argValue[i + 1]);
            Image outputFile;
            outputFile = sub1.subtract(sub1, sub2);
            outputFile.write(argValue[1]);        
            cout << "Subtracting " << argValue[1] << " and " << argValue[i + 1] << " ..." << endl;
        }

        else if (string(argValue[i]) == "overlay") {
            Image ovl1;
            Image ovl2;
            ovl1.read(argValue[1]);
            ovl2.read(argValue[i + 1]);
            Image outputFile;
            outputFile = ovl1.overlay(ovl1, ovl2);
            outputFile.write(argValue[1]);        
        
        }

        else if (string(argValue[i]) == "screen") {
            Image scr1;
            Image scr2;
            scr1.read(argValue[1]);
            scr2.read(argValue[i + 1]);
            Image outputFile;
            outputFile = scr1.screen(scr1, scr2);
            outputFile.write(argValue[1]);  

        }

        else if (string(argValue[i]) == "combine") {
            Image com1;
            Image com2;
            Image com3;
            com1.read(argValue[1]);
            com2.read(argValue[i + 1]);
            com3.read(argValue[i + 2]);
            Image outputFile;
            outputFile = com1.combine(com1, com2, com3);
            outputFile.write(argValue[1]);
        
        }

            //needs to be within its own for loop cause it doesnt take in any other input files for it so i can be back to back
        else if (string(argValue[i]) == "flip") {
            Image inputFile;
            Image outputFile;
            inputFile.read(argValue[i]);
            outputFile = inputFile.flip(inputFile);
            outputFile.write(argValue[1]);
            cout << "... and flipping output of previous step ..." << endl;
        }


        else if (string(argValue[i]) == "onlyred") {
            Image inputFile;
            Image outputFile;
            inputFile.read(argValue[i]);
            outputFile = inputFile.onlyRed(inputFile);
        }

        else if (string(argValue[i]) == "onlygreen") {
            Image inputFile;
            Image outputFile;
            inputFile.read(argValue[i]);
            outputFile = inputFile.onlyGreen(inputFile);        
        }

        else if (string(argValue[i]) == "onlyblue") {
            Image inputFile;
            Image outputFile;
            inputFile.read(argValue[i]);
            outputFile = inputFile.onlyBlue(inputFile);        
        }

        else if (string(argValue[i]) == "addred") {
            Image inputFile;
            Image outputFile;
            int colorVariable = stoi(string(argValue[i + 1]));
            inputFile.read(argValue[i]);
            outputFile = inputFile.addRed(inputFile, colorVariable);
            cout << "... and adding +" << colorVariable << " to red channel of previous step ..." << endl;
        }

        else if (string(argValue[i]) == "addgreen") {
            Image inputFile;
            Image outputFile;
            int colorVariable = stoi(string(argValue[i + 1]));
            inputFile.read(argValue[i]);
            outputFile = inputFile.addGreen(inputFile, colorVariable); 
            cout << "... and adding +" << colorVariable << " to green channel of previous step ..." << endl;       
        }

        else if (string(argValue[i]) == "addblue") {
            Image inputFile;
            Image outputFile;
            int colorVariable = stoi(string(argValue[i + 1]));
            inputFile.read(argValue[i]);
            outputFile = inputFile.addBlue(inputFile, colorVariable);
            cout << "... and adding +" << colorVariable << " to blue channel of previous step ..." << endl;        
        }

        else if (string(argValue[i]) == "scalered") {
            Image inputFile;
            Image outputFile;
            int colorVariable = stoi(string(argValue[i + 1]));

            inputFile.read(argValue[i]);
            outputFile = inputFile.scaleRed(inputFile, colorVariable);  
            cout << "Scaling the red channel of previous step by " << colorVariable << " ..." << endl;      

        }

        else if (string(argValue[i]) == "scalegreen") {
            Image inputFile;
            Image outputFile;
            int colorVariable = stoi(string(argValue[i + 1]));
            inputFile.read(argValue[i]);
            outputFile = inputFile.scaleGreen(inputFile, colorVariable); 
            cout << "Scaling the green channel of previous step by " << colorVariable << " ..." << endl;      
        }    

        else if (string(argValue[i]) == "scaleblue") {
            Image inputFile;
            Image outputFile;
            int colorVariable = stoi(string(argValue[i + 1]));

            inputFile.read(argValue[i]);
            outputFile = inputFile.scaleBlue(inputFile, colorVariable);   
            cout << "Scaling the blue channel of previous step by " << colorVariable << " ..." << endl;      

        }    
    
        else {
            cout << "Invalid method name." << endl;
            return 0;

        }
    }

    return 0;
}



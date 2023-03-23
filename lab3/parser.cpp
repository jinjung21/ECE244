//
//  parser.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018-2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.


#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"

// This is the shape array, to be dynamically allocated
Shape** shapesArray;

// The number of shapes in the database, to be incremented
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

void checkNegative(int value, bool& valid);
void checkFewArgument(std::stringstream& lineStream, bool& valid);
void checkExistingName(string array_name, bool& valid);
bool checkDuplicatedName(Shape** array, string name);
void checkExistingType(string array_type, bool& valid);
void invalid(std::stringstream& lineStream, bool& valid);
void invalid2(std::stringstream& lineStream, bool& valid);
Shape* buildShape(int shapeCount, string name, string type, int xLocation, int yLocation, int xSize, int ySize, bool& valid);
void checkExistingShape(Shape** array, string name, bool&valid);
void checkAngle(int angle, bool& valid);
void draw(Shape** array, string name);
void drawWholeShapes(Shape** array);
void deleteAll(Shape** array);
void deleteShape(Shape** array, string name);
void checkCircleSize (string type, int xSize, int ySize, bool& valid);


int main() {

    string line;
    string command;
   
    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while (!cin.eof()) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);
       
        if (!lineStream.peek()){
            cout << "Error: invalid command\n";
        }

        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
       
       
        string array_type;
        string array_name;
        float xLocation,yLocation,xSize,ySize,angle;
        int value;
       
        // MaxShape
        if (command == keyWordsList[1]){
            for (int i = 0; i<shapeCount; i++){
                if (shapesArray[i] == NULL){
                    delete shapesArray[i];
                    shapesArray = NULL;
                   
                }
            }
            shapeCount=0;
            lineStream >> value;
            bool valid = true;
            if (lineStream.fail()){
                if (lineStream.eof()){
                    valid = false;
                    cout << "Error: too few arguments" << endl;
                }
                else{
                    valid = false;
                    cout << "Error: invalid arguments" << endl;
                }
            }
            else if (!lineStream.eof()){
                valid = false;
                cout << "Error: too many arguments" << endl;
            }
            checkNegative(value, valid);
            if (valid){
                max_shapes = value;
                cout << "New database: max shapes is " << value << endl;
                shapesArray = new Shape* [max_shapes];
                for (int i = 0; i<max_shapes; i++){
                    shapesArray[i] = NULL;
                }
            }
        }
       
       
        //Create
        else if (command == keyWordsList[2]){
            bool valid = true;
            checkFewArgument(lineStream, valid);
            if (valid){
                lineStream >> array_name;
                checkExistingName(array_name, valid);
                for (int i = 0; i<array_name.length(); i++){
                    if(array_name[i] == ' ' || array_name[i] == '\n' || array_name[i]=='\t'){
                        valid = false;
                        cout << "Error: invalid shape name" << endl;
                    }
                }
                bool duplicated = checkDuplicatedName(shapesArray, array_name);
                if (duplicated){
                    valid = false;
                    cout << "Error: shape " <<array_name<<" exists" << endl;
                }
                checkFewArgument(lineStream, valid);
                if (valid){
                    lineStream >> array_type;
                    checkExistingType(array_type, valid);
                    checkFewArgument(lineStream, valid);
                    if (valid){
                        lineStream >> xLocation;
                        if (xLocation - (int)(xLocation)!=0){
                            valid = false;
                            cout << "Error: invalid argument" << endl;
                        }
                        invalid(lineStream, valid);
                        checkNegative(xLocation, valid);
                        checkFewArgument(lineStream, valid);
                       
                        if (valid){
                            lineStream >> yLocation;
                            if (yLocation - (int)(yLocation)!=0){
                                valid = false;
                                cout << "Error: invalid argument" << endl;
                            }
                            invalid(lineStream, valid);
                            checkNegative(yLocation, valid);
                            checkFewArgument(lineStream, valid);
                           
                            if (valid){
                                lineStream >> xSize;
                                if (xSize - (int)(xSize)!=0){
                                    valid = false;
                                    cout << "Error: invalid argument" << endl;
                                }
                                invalid(lineStream, valid);
                                checkNegative(xSize, valid);
                                checkFewArgument(lineStream, valid);
                                if (valid){
                                    lineStream >> ySize;
                                    if (ySize - (int)(ySize)!=0){
                                    valid = false;
                                    cout << "Error: invalid argument" << endl;
                                    }
                                    invalid2(lineStream, valid);
                                    checkCircleSize(array_type, xSize, ySize, valid);
                                    checkNegative(ySize, valid);
                                }
                            }

                        }
                    }
                }
               

            }
            if (valid && !lineStream.eof()){
                valid = false;
                cout << "Error: too many arguments" << endl;
            }
            if (valid){
                Shape* final = buildShape(shapeCount, array_name, array_type, xLocation, yLocation, xSize, ySize, valid);
                if (valid){
                    shapesArray[shapeCount] = final;
                    shapeCount += 1;
                    final = NULL;
                }
            }
        }

        //Move
        else if (command == keyWordsList[3]){
            bool valid = true;
            checkFewArgument(lineStream, valid);
            if (valid){
                lineStream >> array_name;
                checkExistingName(array_name, valid);
                checkExistingShape(shapesArray, array_name, valid);
                checkFewArgument(lineStream, valid);
                if (valid){
                    lineStream >> xLocation;
                    invalid(lineStream, valid);
                    checkNegative(xLocation, valid);
                    checkFewArgument(lineStream, valid);
                    if (valid){
                        lineStream >> yLocation;
                        invalid2(lineStream, valid);
                        checkNegative(yLocation, valid);

                    }
       
                }
            }
            if (valid && !lineStream.eof()){
                valid = false;
                cout << "Error: too many arguments" << endl;
            }
            if (valid){
                string s;
                for (int i = 0; i<shapeCount; i++){
                    s = (*shapesArray[i]).getName();
                    if (s.compare(array_name) == 0){
                        (*shapesArray[i]).setXlocation(xLocation);
                        (*shapesArray[i]).setYlocation(yLocation);
                        cout << "Moved " << array_name << " to " << xLocation << " " << yLocation << endl;
                    }
                }

            }
        }


        //Rotate
        else if (command == keyWordsList[4]){
            bool valid = true;
            checkFewArgument(lineStream, valid);
            if (valid){
                lineStream >> array_name;
                checkExistingName(array_name, valid);
                checkExistingShape(shapesArray, array_name, valid);
                checkFewArgument(lineStream, valid);
                if (valid){
                    lineStream >> angle;
                    invalid2(lineStream, valid);
                    checkAngle(angle, valid);

                }
            }
            if (valid && !lineStream.eof()){
                valid = false;
                cout << "Error: too many arguments" << endl;
            }
            if (valid){
                cout << "Rotated " << array_name << " " << "by " << angle << " degrees" << endl;
            }
        }

        //Draw
        else if (command == keyWordsList[5]){
            bool valid = true;
            checkFewArgument(lineStream, valid);
            if (valid){
                lineStream >> array_name;
                invalid2(lineStream, valid);
                checkExistingShape(shapesArray, array_name, valid);
                if (valid && !lineStream.eof()){
                    valid = false;
                    cout << "Error: too many arguments" << endl;

                }
                if (valid && array_name=="all"){
                    cout << "Drew all shapes" << endl;
                    drawWholeShapes(shapesArray);
                }
                else{
                    checkExistingName(array_name, valid);
                    if (valid){
                        draw(shapesArray, array_name);
                    }
                }
            }
        }


        //Delete
        else if (command == keyWordsList[6]){
            bool valid = true;
            checkFewArgument(lineStream, valid);
            if (valid){
                lineStream >> array_name;
                if (valid){
                    if (lineStream.eof() && array_name == "all"){
                        cout << "Deleted: all shapes" << endl;
                        deleteAll(shapesArray);
                        shapeCount = 0;
                    }
                    else if (lineStream.eof() && checkDuplicatedName(shapesArray, array_name)){
                        deleteShape(shapesArray, array_name);
                        max_shapes -= 1;
                    }
                    else if (array_name != "all" && !checkDuplicatedName(shapesArray, array_name)){
                        valid = false;
                        cout << "Error: shape " << array_name << " not found" <<endl;
                    }
                }
                if (!lineStream.eof()&&valid){
                    cout << "Error: too many arguments" <<endl;
                }
            }
        }
       
       
        else{
            cout << "Error: invalid command" << endl;
        }      
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
       
    }  // End input loop until EOF.
   



    return 0;
}




void checkNegative(int value, bool& valid){
    if (valid){
        if (value<0){
            valid = false;
            cout<<"Error: invalid value"<<endl;
        }
    }
}

void checkFewArgument(std::stringstream& lineStream, bool& valid){
    if (valid){
        if (lineStream.eof() && valid){
            valid = false;
            cout << "Error: too few arguments" << endl;
        }
    }
}

void checkExistingName(string array_name, bool& valid){
    bool initial = false;
    if (valid){
        for (int i = 0; i<NUM_TYPES; i++){
            if (array_name == keyWordsList[i]){
                initial = true;
            }
        }
        for (int i = 0; i<NUM_TYPES; i++){
            if (array_name == shapeTypesList[i]){
                initial = true;
            }
        }
        if (initial){
            valid = false;
            cout << "Error: invalid shape name" << endl;
        }
    }
}

bool checkDuplicatedName(Shape** array, string name){
    string s;
    for (int i = 0; i<shapeCount; i++){
        s = (*array[i]).getName();
        if (s.compare(name) == 0){
            return true;
        }
    }
    return false;
}

void checkExistingType(string array_type, bool& valid){
    bool initial = true;
    if (valid){
        for (int i = 0; i<NUM_TYPES; i++){
            if (array_type == shapeTypesList[i]){
                initial = false;
            }
        }
        if (initial){
            valid = false;
            cout << "Error: invalid shape type" << endl;
        }
    }
}

void invalid(std::stringstream& lineStream, bool& valid){
    if (!lineStream.eof()&& valid && lineStream.fail()){
        valid = false;
        cout << "Error: invalid argument" << endl;
    }
}

void invalid2(std::stringstream& lineStream, bool& valid){
    bool initial = false;
    if (valid && lineStream.fail()){
        if(!lineStream.eof()){
            initial = true;
        }
        else{
            valid = false;
            cout << "Error: invalid argument" << endl;
        }
    }
    if (initial && valid){
        valid = false;
        cout << "Error: too many arguments" << endl;
    }
}

Shape* buildShape(int shapeCount, string name, string type, int xLocation, int yLocation, int xSize, int ySize, bool& valid){
    if (shapeCount < max_shapes){
        Shape* final = new Shape(name, type, xLocation, yLocation, xSize, ySize);
        cout << "Created " << name << ": " << type << " " << xLocation << " " << yLocation << " " << xSize << " " << ySize << endl;
        return final;
    }
    else if (valid){
        cout << "Error: shape array is full" << endl;
        valid = false;
    }
}

void checkExistingShape(Shape** array, string name, bool& valid){
    bool initial = checkDuplicatedName(array, name);
    if (name == "all" && valid){
        return;
    }
    if(!initial){
        valid = false;
        cout << "Error: shape " << name << " not found" << endl;
    }
}

void checkAngle(int angle, bool& valid){
    if (valid){
        if (angle >= 0 && angle <= 360){
            valid = true;
        }
        else{
            valid = false;
            cout << "Error: invalid value\n";
        }
    }
}

void draw(Shape** array, string name){
    string s;
    for (int i = 0; i<shapeCount; i++){
        s = (*array[i]).getName();
        if (s.compare(name) == 0){
            cout << "Drew ";
            (*array[i]).draw();
        }
    }
}

void drawWholeShapes(Shape** array){
    for (int i = 0; i<shapeCount; i++){
        (*array[i]).draw();
    }
}

void deleteAll(Shape** array){
    for (int i = 0; i<shapeCount; i++){
        delete array[i];
        array[i]==NULL;
    }
}



void deleteShape(Shape** array, string name){
    string s;
    for (int i = 0; i < shapeCount; i++){
        s = (*array[i]).getName();
        if (s.compare(name) == 0){
            shapeCount--;
            for (int j = i ; j < shapeCount;j++){
                (*array[j]).setXlocation((*array[j+1]).getXlocation());
                (*array[j]).setYlocation((*array[j+1]).getYlocation());
                (*array[j]).setXsize((*array[j+1]).getXsize());
                (*array[j]).setYsize((*array[j+1]).getYsize());
                (*array[j]).setName((*array[j+1]).getName());
                (*array[j]).setType((*array[j+1]).getType());
            }
        }
    }
    cout << "Deleted shape "<< name << endl;
    delete array[shapeCount];
    array[shapeCount] = NULL;
}

/*void deleteShape(Shape** array, string name){
    string s;
    for (int i = 0; i<shapeCount; i++){
        s = (*array[i]).getName();
        if (s.compare(name) == 0){
            delete (*array[i]);
            array[i] == NULL;
            cout << "Deleted shape "<< name << endl;
        }
    }
}*/

void checkCircleSize (string type, int xSize, int ySize, bool& valid){
    if (type == shapeTypesList[0]){
        if (xSize != ySize){
            valid = false;
            cout << "Error: invalid value" << endl;
        }
    }
}

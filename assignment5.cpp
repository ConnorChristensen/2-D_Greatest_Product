/******************************************************
 ** Program: assignment5.cpp
 ** Author: Connor Christensen
 ** Date: 3/5/2015
 ** Description: Creates an array and finds the largest sum in a veriety of ways
 ** Input: test.txt, manual input of row/col
 ** Output: colored arrays, greatest sums, starting points, snazzy formating
 ******************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cstring>

using namespace std;

struct total_info {
    int row, col, total_top;
    int xstart, ystart;
    string kind;
};

//prototypes
int isnumeric(string output);
int main(int argc, char *argv[]);
void text_file(total_info info);
void input(total_info info);
int** create_array(total_info info);
int** fill_array(total_info info, int **array);
void print(total_info info, int **array);
void print_color(total_info info, int **array, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int xstart, int ystart, string kind);
void greatest_product(total_info info, int **array, char text_import);
void product(total_info &info, int **array, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int boundry1, int boundry2, int &total_top, string kind);

/*************************************
 ** Description: New isdigit function takes anything and checks for int
 ** Pre-Conditions: Anything
 ** Post-Conditions: Returns valid int to be stored
  ** Lines: ~19
 **************************************/
int isnumeric(string output) {
    
    int variable;
    bool correct = true;
    char temporary[25];
    
    cout << output;
    cin >> temporary;
    
    do {
        correct = true;
        for (int y = 0; y < strlen(temporary); y++) {
            if (isdigit(temporary[y]) == false) {
                correct = false;
            }
        }
        if (correct == false) {
            cout << "Incorrect, try again: " << endl;
            cout << output;
            cin >> temporary;
        }
        else {
            variable = atoi(temporary);
            correct = true;
        }
    } while (correct == false);
    
    return variable;
}

/*************************************
 ** Description: checks arguments, manages input, error handles
 ** Pre-Conditions: Nothing
 ** Post-Conditions: Complete program
 ** Lines: ~6
 **************************************/
int main(int argc, char *argv[]) {
    
    struct total_info info;
    info.total_top = 0;
    
    if (argc == 1) {
        input(info);
    }
    else {
        if (!strcmp(argv[1], "-test")) {
            text_file(info);
        }
        else {
            cout << "Error. That is not -test. " << endl;
        }
    }
    return 0;
}

/*************************************
 ** Description: Inputs and runs off text file
 ** Pre-Conditions: text file import
 ** Post-Conditions: Complete program with test
 ** Lines: ~10
 **************************************/
void text_file(total_info info) {
    char text_import = 'y';
    cin >> info.row;
    cin >> info.col;
    int **array;
    array = create_array(info);
    for(int x = 0; x < info.row; x++) {
        for(int y = 0; y < info.col; y++) {
            cin >> array[x][y];
        }
    }
    print(info, array);
    greatest_product(info, array, text_import);
}

/*************************************
 ** Description: Creates arrays with user input
 ** Pre-Conditions: None
 ** Post-Conditions: Passes out row, col, array everywhere
 ** Lines: ~7
 **************************************/
void input(total_info info) {
    info.row = isnumeric("Row: ");
    info.col = isnumeric("Col: ");
    int **array;
    array = create_array(info);
    array = fill_array(info, array);
    print(info, array);
    greatest_product(info, array, 'n');
}

/*************************************
 ** Description: Alocates space for array
 ** Pre-Conditions: row, col
 ** Post-Conditions: Dynamic heap space array
 ** Lines: ~5
 **************************************/
int** create_array(total_info info) {
    int **array = NULL;
    array = new int *[info.row];
    for (int x = 0; x < info.row; x++) {
        array[x] = new int[info.col];
    }
    return array;
}

/*************************************
 ** Description: Fills array with "random" numbers
 ** Pre-Conditions: Array alocated, row, col defined
 ** Post-Conditions: Random array
 ** Lines: ~4
 **************************************/
int** fill_array(total_info info, int **array) {
    for (int y = 0; y < info.row; y++) {
        for (int x = 0; x < info.col; x++) {
            array[y][x] = rand() % 50 + 1;
        }
    }
    return array;
}

/*************************************
 ** Description: Prints out standard array
 ** Pre-Conditions: Created and filled array, defined row, col
 ** Post-Conditions: None (its just printed)
 ** Lines: ~10
 **************************************/
void print(total_info info, int **array) {
    cout << endl;
    cout << "The original array: " << endl;
    for (int y = 0; y < info.row; y++) {
        for (int x = 0; x < info.col; x++) {
            if (array[y][x] < 10) {
                cout << "0" << array[y][x] << "  ";
            }
            else{
                cout << array[y][x] << "  ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

/*************************************
 ** Description: Prints out array with shapes colored red
 ** Pre-Conditions: row, col, array, shape, start point, name
 ** Post-Conditions: None (its just printed)
 ** Lines: ~15
 **************************************/
void print_color(total_info info, int **array, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int xstart, int ystart, string kind){
    cout << "The array with the greatest " << kind << " products colored: " << endl;
    for (int y = 0; y < info.row; y++) {
        for (int x = 0; x < info.col; x++) {
            if (((x == x1+xstart) and (y == y1+ystart)) or
                ((x == x2+xstart) and (y == y2+ystart)) or
                ((x == x3+xstart) and (y == y3+ystart)) or
                ((x == x4+xstart) and (y == y4+ystart))) {
                    if (array[y][x] < 10) {
                        cout << "\033[0;31m0" << array[y][x] << "\033[0m" << "  ";
                    }
                    else {
                        cout << "\033[0;31m" << array[y][x] << "\033[0m" << "  ";
                    }
            }
            else {
                if (array[y][x] < 10) {
                    cout << "0" << array[y][x] << "  ";
                }
                else{
                    cout << array[y][x] << "  ";
                }
            }
        }
        cout << endl;
    }
    cout << endl;
}

/*************************************
 (This function is the center peice to the program)
 ** Description: Manager of universal shape creator and printer of top info
 ** Pre-Conditions: row, col, array, text import
 ** Post-Conditions: None (it just prints)
 ** Lines: ~13
 **************************************/
void greatest_product(total_info info, int **array, char text_import) {
    int x1, y1, x2, y2, x3, y3, x4, y4, boundry1, boundry2, total_top;
    //                       x  y  x  y  x  y  x  y  by bx               type
    if (text_import == 'y') {
        product(info, array, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, total_top, "Square");
    }
    else if ((info.row >= 4) and (info.col >= 4)) {
        product(info, array, 0, 0, 1, 0, 2, 0, 3, 0, 0, 3, total_top, "Horizontal");
        product(info, array, 0, 0, 0, 1, 0, 2, 0, 3, 3, 0, total_top, "Vertical");
        product(info, array, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, total_top, "Square");
        product(info, array, 0, 0, 1, 1, 2, 2, 3, 3, 3, 3, total_top, "Diagonal to the Right");
        product(info, array, 3, 0, 2, 1, 1, 2, 0, 3, 3, 3, total_top, "Diagonal to the Left");
        product(info, array, 0, 0, 1, 0, 1, 1, 2, 1, 1, 2, total_top, "Zig-zag");
        product(info, array, 0, 0, 1, 0, 2, 0, 1, 1, 2, 1, total_top, "T");
        product(info, array, 0, 0, 1, 0, 2, 0, 2, 1, 2, 2, total_top, "Down Horizontal L");
        product(info, array, 1, 0, 0, 0, 0, 1, 0, 2, 2, 1, total_top, "Backwards-upsidown L");
    }
    else {
        product(info, array, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, total_top, "Square");
        product(info, array, 0, 0, 1, 0, 1, 1, 2, 1, 1, 2, total_top, "Zig-zag");
        product(info, array, 0, 0, 1, 0, 2, 0, 1, 1, 2, 1, total_top, "T");
    }
    
    cout << "Top info: " << endl;
    cout << "Starting point:\t\tArray[" << info.ystart << "][" << info.xstart << "]" << endl;
    cout << "Kind:\t\t\t" << info.kind << endl;
    cout << "Product:\t\t" << info.total_top << endl;
}

/*************************************
 ** Description: universal multiplier and data collector
 ** Pre-Conditions: row, col, array, shape, boundry lines, top number, name
 ** Post-Conditions: None (it just prints)
 ** Lines: ~28 (Cant be made shorter without vastly increasing code and decreasing effeciency)
 **************************************/
void product(total_info &info, int **array, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int boundry1, int boundry2, int &total_top, string kind) {
    int num1, num2, num3, num4, xstart, ystart;
    num1 = num2 = num3 = num4 = 0;
    total_top = (num1 * num2 * num3 * num4);
    int total_new;
    for (int y = 0; y < info.row-boundry1; y++) {
        for (int x = 0; x < info.col-boundry2; x++) {
            num1 = array[y+y1][x+x1];
            num2 = array[y+y2][x+x2];
            num3 = array[y+y3][x+x3];
            num4 = array[y+y4][x+x4];
            total_new = (num1 * num2 * num3 * num4);
            if (total_top < total_new) {
                total_top = total_new;
                ystart = y;
                if (kind == "diagonal left") {
                    xstart = x+3;
                }
                else {
                    xstart = x;
                }
            }
        }
    }
    if (total_top > info.total_top) {
        info.total_top = total_top;
        info.kind = kind;
        info.xstart = xstart;
        info.ystart = ystart;
    }
    print_color(info, array, x1, y1, x2, y2, x3, y3, x4, y4, xstart, ystart, kind);
    cout << "Starting point:\t\tArray[" << ystart << "][" << xstart << "]" << endl;
    cout << "Orientation:\t\t" << kind << endl;
    cout << "Greatest Product:\t" << total_top << endl;
    cout << endl;
}
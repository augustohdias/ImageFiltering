/*
 * Linux Kernel coding style:
 *      https://www.kernel.org/doc/html/v4.10/process/coding-style.html
 */

#include <sys/time.h>
#include <sys/resource.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define IO_ERROR                (5)
#define X_DIMENSION             (1366)
#define Y_DIMENSION             (768)
#define C_DIMENSION             (3)
#define HEADER_SIZE             (3)
#define BODY_SIZE               (X_DIMENSION * Y_DIMENSION * C_DIMENSION)


void rgbParser(const string *imgBody, unsigned char rgbMatrix[X_DIMENSION][Y_DIMENSION][C_DIMENSION]);
void numericParser(const string *imgBody, unsigned char *numericBody);
int readImage(string fileName, string *imgHeader, string *imgBody);
void negativeFilter(const unsigned char rgbMatrix[X_DIMENSION][Y_DIMENSION][C_DIMENSION], string *header);
void grayScaleFilter(const unsigned char rgbMatrix[X_DIMENSION][Y_DIMENSION][C_DIMENSION], string *header);

int main()
{
        string fileName;
        cout << "File name: ";
        cin >> fileName;

        string imgHeader[HEADER_SIZE];
        string imgBody[BODY_SIZE];
        if(readImage(fileName, imgHeader, imgBody) == IO_ERROR)
                return IO_ERROR;

//        printInfo(imageData);

        unsigned char rgbMatrix[X_DIMENSION][Y_DIMENSION][C_DIMENSION];
        rgbParser(imgBody, rgbMatrix);

        negativeFilter(rgbMatrix, imgHeader);
        grayScaleFilter(rgbMatrix, imgHeader);

        return 0;
}

void negativeFilter(const unsigned char rgbMatrix[X_DIMENSION][Y_DIMENSION][C_DIMENSION], string *header)
{
        ofstream file("negative.pnm", ios::ate);
        string imgData;

        for (int i = 0; i < HEADER_SIZE; i++) {
                imgData += header[i] + "\n";
        }

        for (int i = 0; i < X_DIMENSION; i++) {
                for (int j = 0; j < Y_DIMENSION; j++) {
                        for (int c = 0; c < C_DIMENSION; c++) {
                                imgData += to_string((255 - rgbMatrix[i][j][c])) + "\n";
                        }
                }
        }
        file.write(imgData.c_str(), imgData.size());
        file.close();
}

void grayScaleFilter(const unsigned char rgbMatrix[X_DIMENSION][Y_DIMENSION][C_DIMENSION], string *header)
{
        ofstream file("gryscale.pnm", ios::ate);
        string imgData;

        for (int i = 0; i < HEADER_SIZE; i++) {
                imgData += header[i] + "\n";
        }

        for (int i = 0; i < X_DIMENSION; i++) {
                for (int j = 0; j < Y_DIMENSION; j++) {
                        int sum = 0, mean = 0;
                        for (int c = 0; c < C_DIMENSION; c++)
                                sum += rgbMatrix[i][j][c];

                        mean = sum/C_DIMENSION;
                        for (int c = 0; c < C_DIMENSION; c++)
                                imgData += to_string(mean) + "\n";
                }
        }
        file.write(imgData.c_str(), imgData.size());
        file.close();
}

int readImage(string fileName, string *imgHeader, string *imgBody)
{
        ifstream inputFile(fileName);

        if (!inputFile.is_open())
                return IO_ERROR;

        string line;
        int count = 0;
        while (getline(inputFile, line)) {
                if (line.find("#") != string::npos)
                        continue;
                if (count < 3)
                        imgHeader[count] = line;
                else
                        imgBody[count - HEADER_SIZE] = line;
                count++;
        }
        inputFile.close();

        return 0;
}


void numericParser(const string *imgBody, unsigned char *numericBody)
{
        int i = 0;
        while(i < BODY_SIZE) {
                numericBody[i] = (unsigned char) atoi(imgBody[i].c_str());
                i++;
        }
}

void rgbParser(const string *imgBody, unsigned char rgbMatrix[X_DIMENSION][Y_DIMENSION][C_DIMENSION])
{
        unsigned char numericBody[BODY_SIZE];
        numericParser(imgBody, numericBody);
        int k = 0;
        for (int i = 0; i < X_DIMENSION; i++) {
                for (int j = 0; j < Y_DIMENSION; j++) {
                        for (int c = 0; c < 3; c++) {
                                rgbMatrix[i][j][c] = numericBody[k];
                                k++;
                        }
                }
        }
}

void printInfo(const string *header, const string *body)
{
        cout << "#-*- Image Header -*-" << endl;
        for (int i = 0; i < HEADER_SIZE; i++) {
                cout << header[i] << endl;
        }

        cout << "#-*- Image Body -*-";
        for (int i = 0; i < 5 * C_DIMENSION; i++) {
                if (i % 3 == 0) cout << endl << "R: " << body[i];
                else if (i % 3 == 1) cout << " G: " << body[i];
                else cout << " B: " << body[i];
        }
        cout << endl << ". . ." << endl;
}


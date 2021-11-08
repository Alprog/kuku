
#include "LanguageServer.h"

#include <fstream>
#include <iostream>

void language_server::run()
{
    std::ifstream ifile;
 
    int pos = 0;
    while (true)
    {
        ifile.open("pipe.txt");

        ifile.seekg(pos);
        while (ifile.peek() != EOF)
        {
            char c;
            ifile >> c;

            pos = ifile.tellg();

            std::ofstream ofile;
            ofile.open("pipe2.txt", std::ios::app);
            ofile << c;
            ofile.close();
        }
        ifile.close();        
    }
}
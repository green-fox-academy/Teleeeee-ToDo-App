#include <iostream>
#include <vector>
#include "fstream"


void cutOutListItem(std::string  fileName, int index);
void readListItem(std::string  fileName);
void writeListOut(std::string  fileName, std::string input);
void printUsage();
int numerateInput(std::string input);
int getIndex(std::string input);

int main(int argc, char* argv[]) {


        switch (numerateInput(input)){
            case(0):printUsage();
                break;
            case(1):readListItem("my-text.txt");
                break;
            case(2):writeListOut("my-text.txt",  input.erase(0, 3));
                break;
            case(3):cutOutListItem("my-text.txt", index);
                break;
            case(4):
                break;
        }

    return 0;

}

void cutOutListItem(std::string  fileName, int index){
    std::ifstream myFileCut;
    myFileCut.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::vector<std::string> textToCutFrom;
    try {
        myFileCut.open(fileName);
        std::string textCut;
        while (!myFileCut.eof()) {
            getline(myFileCut, textCut);
            textToCutFrom.push_back(textCut);
        }

        myFileCut.close();
    }catch(std::ifstream::failure& e){

    }

    std::ofstream myFileCopy;
    myFileCopy.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    try {
        myFileCopy.open(fileName);
        for (int i = 0; i < textToCutFrom.size() ; ++i) {
            if(i != index - 1) {
                myFileCopy << textToCutFrom[i] << std::endl;
            }
        }
        myFileCopy.close();
    }catch(std::ofstream::failure& e){
        std::cout << e.what() << std::endl;
    }
}

void readListItem(std::string  fileName){
    bool empty = 1;
    std::ifstream myFileOut;
    myFileOut.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        myFileOut.open(fileName);
        while (!myFileOut.eof()) {
            std::string textOut;
            for (int i = 1;; ++i) {
                getline(myFileOut, textOut);
                std::cout << i << " - " << textOut << std::endl;
                empty = 0;
                if (myFileOut.eof()) {
                    break;
                }
            }
        }
        myFileOut.close();
    } catch (std::ifstream::failure &e) {
        //could have catch here but only getline would throw something here
    }
    if(empty){
        std::cout << "No todos for today! :)" << std::endl;
    }
}

void writeListOut(std::string  fileName, std::string input){

    std::ofstream myFile;
    myFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        myFile.open(fileName);
        if(input == "-a"){
            std::cout << "Unable to add: no task provided" << std::endl;
        }
        else {
            input.erase(0, 3);
            myFile << input;
        }
        myFile.close();
    }catch(std::ifstream::failure& e){
        std::cout << e.what() << std::endl;
    }
}

void printUsage(){
    std::cout << "Command Line Todo application" << std::endl;
    std::cout << "=============================" << std::endl << std::endl;
    std::cout << "Command line arguments:" << std::endl;
    std::cout << "     -l   Lists all the tasks" << std::endl;
    std::cout << "     -a   Adds a new task" << std::endl;
    std::cout << "     -r   Removes an task" << std::endl;
    std::cout << "     -c   Completes an task" << std::endl;
}

int numerateInput(std::string input){
    input.erase(2, input.length()-2);
    input.erase(0, 1);
    std::string r = "r";
    std::string l = "l";
    std::string a = "a";
    std::string c = "c";
    if(input == l){return 1;}
    if(input == a){return 2;}
    if(input == r){return 3;}
    if(input == c){return 4;}
    return  0;
}

int getIndex(std::string input){
    input.erase(0,3);
    input.erase(1,input.length()-1);
    return std::stoi(input);
}
#include <iostream>
#include <vector>
#include "fstream"


void cutOutListItem(std::string  fileName, int index);
void readListItem(std::string  fileName);
void writeListOut(std::string  fileName, std::string input);
void printUsage();

int main(int argc, char* argv[]) {
    bool flagForCorrectArgument = 0;
   if(argc == 1){
        printUsage();
    }
    else{
        if(argv[1] == std::string("-l")){
            flagForCorrectArgument = 1;
            readListItem("my-text.txt");
        }
        if(argv[1] == std::string("-a")){
            flagForCorrectArgument = 1;
            if(argc > 2) {
                writeListOut("my-text.txt", argv[2]);
            }else{
                std::cout << "Unable to add: no task provided" << std::endl;
            }
        }
        if(argv[1] == std::string("-r")){
            flagForCorrectArgument = 1;
            cutOutListItem("my-text.txt", std::stoi(argv[2]));
        }
        if(argv[1] == std::string("-c")){
            flagForCorrectArgument = 1;
        }
        if(!flagForCorrectArgument){
            std::cout << "Unsupported argument" << std::endl;
        }

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

    std::ifstream myFileCopy;
    myFileCopy.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::vector<std::string> textToCutFrom;
    try {
        myFileCopy.open(fileName);
        std::string textCopy;
        while (!myFileCopy.eof()) {
            for (int i = 1;; ++i) {
                getline(myFileCopy, textCopy);
                textToCutFrom.push_back(textCopy);
                if (myFileCopy.eof()) {
                    break;
                }
            }

        }
        myFileCopy.close();
    }catch(std::ifstream::failure& e){
        //getline trows exeptions when closes file
    }

    textToCutFrom.push_back(input);

    std::ofstream myFile;
    myFile.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    try {
        myFile.open(fileName);
        for(int i = 0 ; i < textToCutFrom.size() ; i++){
            myFile << textToCutFrom[i] << std::endl;
        }
        myFile.close();
    }catch(std::ofstream::failure& e){
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

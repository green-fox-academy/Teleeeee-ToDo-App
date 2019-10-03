#include <iostream>
#include <vector>
#include "fstream"
#include "cctype"


void cutOutListItem(std::string  fileName, int index);
void readListItem(std::string  fileName,  std::vector<int> doneItems);
void writeListOut(std::string  fileName, std::string input);
void printUsage();
void checkTask(std::string  fileName, int index);
std::vector<int> readafromFileIndex(std::string  fileName, std::vector<int>* doneItems );
void writeToFileIndex(std::string  fileName, int index);

int main(int argc, char* argv[]) {

    std::vector<int> doneItems ={};
    bool flagForCorrectArgument = 0;

    if(argc == 1){
         printUsage();
    }
    else{
         if(argv[1] == std::string("-l")){
             flagForCorrectArgument = 1;
             readListItem("my-text.txt", readafromFileIndex("checkedtasks", &doneItems ));
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
             if(!std::isdigit(argv[2][0])) {
                 std::cout << "Unable to remove: index is not a number" << std::endl;
                 if (argc > 2) {
                     cutOutListItem("my-text.txt", std::stoi(argv[2]));
                 }
                 if (argc == 2) {
                     std::cout << "Unable to remove: no index provided" << std::endl;
                 }
             }
         }
         if(argv[1] == std::string("-c")){
             flagForCorrectArgument = 1;
             if(!std::isdigit(argv[2][0])) {
                 std::cout << "Unable to check: index is not a number" << std::endl;
                 } else{
                 if (argc == 3) {
                     checkTask("my-text.txt", std::stoi(argv[2]) );
                 } else if (argc == 2) {
                     std::cout << "Unable to check: no index provided" << std::endl;
                 } else {
                     std::cout << "Too many argument provided. Try format: -c 2" << std::endl;
                 }
             }
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
    int counter = 0;
    try {
        myFileCut.open(fileName);
        std::string textCut;
        while (!myFileCut.eof()) {
            getline(myFileCut, textCut);
            textToCutFrom.push_back(textCut);
            counter++;
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
    if(counter < index){
        std::cout << "Unable to remove: index is out of bound" << std::endl;
    }
}

void readListItem(std::string  fileName, std::vector<int> doneItems){
    bool empty = 1;
    std::ifstream myFileOut;
    myFileOut.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        myFileOut.open(fileName);
        while (!myFileOut.eof()) {
            std::string textOut;
            for (int i = 1;; ++i) {
                int temp = 0;
                getline(myFileOut, textOut);
                if(!doneItems.empty()) {
                    for (int k = 0; k < doneItems.size(); k++) {
                        if (doneItems[k] == i) {
                            temp = i;
                        }
                    }
                }
                    if (temp == i) {
                        std::cout << i << " - " << "[X] " << textOut << std::endl;
                    } else {
                        std::cout << i << " - " << "[ ] " << textOut << std::endl;
                    }
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
            myFile <<textToCutFrom[i] << std::endl;
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

void checkTask(std::string  fileName, int index){

    bool empty = 1;
    int taskCounter = 0;
    std::ifstream myFileOut;
    myFileOut.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        myFileOut.open(fileName);
        while (!myFileOut.eof()) {
            std::string textOut;
            for (int i = 1;; ++i) {
                getline(myFileOut, textOut);
                taskCounter++;
                if(index == i) {
                    std::cout << i << " - " << "[X] " << textOut << std::endl;
                    writeToFileIndex("checkedtasks",index );
                }
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
    if(taskCounter < index){
        std::cout << "Unable to check: index is out of bound" << std::endl;
    }
}

std::vector<int> readafromFileIndex(std::string  fileName, std::vector<int>* doneItems ){

    std::ifstream myFileDoneItems;
    myFileDoneItems.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        myFileDoneItems.open(fileName);
        std::string textCut;
        while (!myFileDoneItems.eof()) {
            getline(myFileDoneItems, textCut);
            int temp = textCut[0] -'0';
            doneItems->push_back(temp);
        }

        myFileDoneItems.close();
    }catch(std::ifstream::failure& e){
        //only getline would throw exeption here
    }

    return *doneItems;
}

void writeToFileIndex(std::string  fileName, int index ){

    std::ofstream myFileDoneWrite;
    std::ifstream myFiledoneRead;
    myFiledoneRead.open(fileName);
    myFileDoneWrite.open(fileName,std::ios::app);
    if(myFiledoneRead.is_open()){
        myFileDoneWrite << index << std::endl;
    }
    myFiledoneRead.close();
    myFileDoneWrite.close();

}
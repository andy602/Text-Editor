
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>

// global variables
int spacerGlobal=0;
int verticalGlobal=0;
int countGlobal=0;
int cursorPosition=1;
bool inserted=false;
std::vector<std::string> fileVec;
std::vector<std::string> saveVec;
std::stack<std::vector<std::string>> undoStack;
std::stack<std::vector<std::string>> redoStack;

// functions
void setHorizontalCursor(int spacer){
  if(spacer>20){
    spacerGlobal=19;
  }
  if(spacer<0){
    spacerGlobal=0;
  }
  if(spacer>=0){
    for(int i=0;i<spacer;i++){
      std::cout<<" ";
    }
  }
  std::cout<<"     *"<<std::endl;
}

void insertToVector(std::string insertString){
  std::string line=fileVec.at(cursorPosition-1);
  std::string temp;
  std:: string temp2;
  std:: string temp3;
  std::string temp4=" ";
  int spacer=spacerGlobal+1;
  if((insertString.size()+spacer-1)>20){
    temp2=insertString.substr(20-spacerGlobal);
    insertString=insertString.substr(0,(20-spacerGlobal));
  }

    if(spacer==1){
          temp=insertString+line.substr(insertString.length());

      }else{
          temp=line.substr(0,spacer-1)+insertString+line.substr(insertString.length()+spacer-1);
      }

    temp=temp.substr(0,20);
    fileVec.erase(fileVec.begin()+(cursorPosition-1));
    fileVec.insert(fileVec.begin()+(cursorPosition-1), temp);
    if((temp2.empty()==0)&&(cursorPosition<=countGlobal)){
      if(cursorPosition==countGlobal){
        while(temp4.size()!=20){
          temp4+=" ";
        }
        fileVec.push_back(temp4);
      }
      line=fileVec.at(cursorPosition);
      temp=temp2+line.substr(temp2.length());
      spacer=1;
      fileVec.erase(fileVec.begin()+(cursorPosition));
      fileVec.insert(fileVec.begin()+(cursorPosition), temp);
      countGlobal+=1;
    }

    int stackLength=redoStack.size();
    for(int i=0;i<stackLength;++i){
        redoStack.pop();
    }
}

void printWindow(std::istream& fileInput, int height, int vertical, int spacer){
  setHorizontalCursor(spacer);
  std::vector<std::string> lineVector;
  std::cout<<"     12345678901234567890"<<std::endl;

  if(cursorPosition>countGlobal){
    cursorPosition=countGlobal;
  }
  if(cursorPosition<1){
    cursorPosition=1;
  }

  int count=0;
  std::string line;
  int temp=-1;

    if(vertical>((countGlobal-1)*2)){
      vertical=(countGlobal-1)*2;
      verticalGlobal=(countGlobal-1)*2;
    }

    if(vertical>(countGlobal+7)){

      vertical=countGlobal+8;
      verticalGlobal=countGlobal+8;
    }

  if(vertical<0){
    vertical=0;
    verticalGlobal=0;
  }


  if((verticalGlobal>=countGlobal)&&(countGlobal<10)){
    temp=(verticalGlobal+1)-countGlobal;
    height=height+temp;
  }else if((verticalGlobal>=10)&&(countGlobal>=10)){
    temp=(verticalGlobal+1)-10;
    height=height+temp;
  }

  int length=fileVec.size();
  for(int i=0; i<length; i++){

    if(count+1<=height){
      if((count+1)>temp){

        if(((count)==0)&&(cursorPosition!=1)){
          std::cout<<"   ";
        }
        if(((count+1)==0)&&(cursorPosition==0)){
          std::cout<<"*  ";

        }else if((count+1)==cursorPosition){
          if(cursorPosition<10){
            std::cout<<"*  ";
          }else{
            std::cout<<"* ";
          }
        }

        if(((count+1)<10)&&((count+1)!=cursorPosition)&&(count!=0)){
          std::cout<<"   ";
        }else if(((count+1)>=10)&&((count+1)!=cursorPosition)&&(count!=0)){
          std::cout<<"  ";
        }

            std::cout<<count+1<<"|"<<fileVec.at(count)<<std::endl;

      }
      count++;
    }
    }

  if(height>count){

    while((count+1)<=height){

      if(((count+1)<10)&&((count+1)<=countGlobal+9)){
        std::cout<<"   "<<count+1<<std::endl;
      }if(((count+1)>=10)&&((count+1)<=countGlobal+9)){
        std::cout<<"  "<<count+1<<std::endl;
      }
      if((count+1)>countGlobal+9){
        break;
      }

      count++;
    }

  }

  std::cout<<"     12345678901234567890"<<std::endl;
  fileInput.clear();
  fileInput.seekg(0);
}

//functions

std::vector<std::string> toVector(std::istream& fileN){
  std::vector<std::string> fileVector;
  std::string line;
int length=0;
  while(getline(fileN,line)){
    length=line.size();
    for(int i=0; i<length;++i){
      if(line[i]=='\r'){
        line.erase(i);
      }
      while(line.size()!=20){
        line+=" ";
      }
    }
    fileVector.push_back(line);

  }


  fileN.clear();
  fileN.seekg(0);
  return fileVector;
}
void numArgValidation(int arg){
  if(arg>2){
    std::cout<<"Too many command-line arguments."<<std::endl;
    exit(1);
  } else if(arg<=1){
    std::cout<<"Too few command-line arguments."<<std::endl;
    exit(1);
  }
}
void inputValidation(std::istream& fileN, std::string name1){
  std::string line;
  std::string str;
  int count=0;

  while(getline(fileN, line)){
    if(line.length()>20){
      std::cout<<"File "<<name1<<" has at least one too long line."<<std::endl;
      exit(2);
    }
    count++;
  }
  if(count>30){
    std::cout<<"File "<<name1<<" has too many lines."<<std::endl;
    exit(2);
  }
 countGlobal=count;
 fileN.clear();
 fileN.seekg(0);
}

void commandInput(std::istream& fileOriginal, std::vector<std::string> fileVector){
  std::string input1;
  std::string first;
  std::string second;
  std::string line;
  bool previous=true;
  std::string temp1;
  std::string temp2;
  std::string temp3;
  std::string insertStr;
  int length=fileVec.size();
  int counter=0;
  std::vector<std::string> undoVec;
  std::vector<std::string> redoVec;
  int check=0;
  bool saveQuit=false;
  std::string saveResponse;
  std::string lineNew;
  std::string new1;

  do {
    second="";
    first="";
    if(previous==true){

          std::cout<<"Enter command: ";


      getline(std::cin, input1);

      std::stringstream streamInput(input1);
      std::cout<<"\n";
      streamInput>>first>>second;
      if(first!=""){
        temp1=first;
        temp2=second;
        temp3=input1;
        counter=1;
      }
      first=temp1;
      second=temp2;
      input1=temp3;

    }
    previous=true;
    if(first=="save"){

      std::ofstream fileSave;
      fileSave.open(second);
      for(int i=0; i<length; i++){
        fileSave<<fileVec.at(i)<<"\n";
      }

      fileSave.close();
      fileOriginal.clear();
      fileOriginal.seekg(0);
      saveVec=fileVec;
      inserted=false;
      printWindow(fileOriginal, 10, verticalGlobal, spacerGlobal);
      previous=true;
    }
    if(first=="d"){
      if(second==""){
        spacerGlobal=spacerGlobal+1;
      }else{
        if((spacerGlobal+stoi(second)>=20)){
          spacerGlobal=19;
        }else{
          spacerGlobal=spacerGlobal+stoi(second);
        }

      }

      printWindow(fileOriginal, 10, verticalGlobal, spacerGlobal);
      previous=true;
    }
    if(first=="a"){
      if(second==""){
        spacerGlobal=spacerGlobal-1;
      }else{
        spacerGlobal=spacerGlobal-stoi(second);
      }
      printWindow(fileOriginal, 10, verticalGlobal, spacerGlobal);
      previous=true;
    }
    if(first=="s"){
      if(second==""){
        verticalGlobal=verticalGlobal+1;
        cursorPosition++;
      }else{
        verticalGlobal=verticalGlobal+stoi(second);
        cursorPosition=cursorPosition+stoi(second);
      }

    printWindow(fileOriginal, 10, verticalGlobal, spacerGlobal);
    previous=true;
    }
    if(first=="w"){
      if(second==""){
        verticalGlobal=verticalGlobal-1;
        cursorPosition--;
      }else{
        verticalGlobal=verticalGlobal-stoi(second);
        cursorPosition=cursorPosition-stoi(second);
      }

      printWindow(fileOriginal, 10, verticalGlobal, spacerGlobal);
      previous=true;
    }
    if(first=="i"){
      insertStr=input1.substr(2);
      insertToVector(insertStr);
      printWindow(fileOriginal, 10, verticalGlobal, spacerGlobal);
      undoStack.push(fileVec);
      previous=true;
      inserted=true;

    }
    if(first=="u"){
      if(undoStack.size()>1){
        redoStack.push(fileVec);
        redoVec=fileVec;
        undoVec=undoStack.top();
        undoStack.pop();
        fileVec=undoStack.top();
        check++;
        inserted=false;
      }else{
        std::cout<<"Cannot undo.\n"<<std::endl;
      }
      printWindow(fileOriginal, 10, verticalGlobal, spacerGlobal);
      previous=true;
    }
    if(first=="r"){
      if(redoStack.size()>0){
        fileVec=redoStack.top();
        undoStack.push(fileVec);
        redoStack.pop();
      }else{
        std::cout<<"Cannot redo.\n"<<std::endl;
      }
      printWindow(fileOriginal, 10, verticalGlobal, spacerGlobal);
      previous=true;
    }
    if(first==""){
      if(counter>=1){
        previous=false;
      }

    }
    if(first=="q"){
      previous=true;
      if((fileVec==saveVec)&&(inserted==false)){
        std::cout<<"Goodbye!"<<std::endl;
        exit(0);
      }
      if((fileVec!=saveVec)||(inserted==true)){
        std::cout<<"You have unsaved changes.\nAre you sure you want to quit (y or n)?\n";
        getline(std::cin, saveResponse);

        std::stringstream streamInputNew(saveResponse);

        streamInputNew>>new1;
        if(new1=="y"){
          std::cout<<"\nGoodbye!"<<std::endl;
          saveQuit=true;
        }
        if(new1=="n"){
          previous=true;
          saveQuit=false;
          saveResponse="";
          std::cout<<"\n";
          printWindow(fileOriginal, 10, verticalGlobal, spacerGlobal);

          first=" ";
          temp1=" ";
          input1=" ";

      }

    }

    }
  } while((saveQuit==false));

  exit(0);

  }

int main(int argc, char*argv[])
{
    numArgValidation(argc);
    std::ifstream fileName;
    fileName.open(argv[1]);
    if(!fileName.is_open()){
      std::cout<<"could not open"<<std::endl;
      exit(1);
    }
    std::string name=argv[1];
    if(fileName.is_open()){
        inputValidation(fileName, name);
    }

    fileVec=toVector(fileName);
    saveVec=fileVec;
    undoStack.push(fileVec);
    printWindow(fileName, 10, verticalGlobal, spacerGlobal);
    commandInput(fileName, fileVec);
    fileName.close();
    return 0;
}

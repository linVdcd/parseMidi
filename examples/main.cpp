//
// Created by lin on 17-11-17.
//
#include "parseMIDI.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include<stdlib.h>
using namespace std;

std::string getFileString(const std::string& filepath) {
    std::ifstream is(filepath.c_str());
    std::string filebuffer="";
    if (is.is_open()) {
        // get length of file:
        is.seekg (0, is.end);
        long long length = is.tellg();
        is.seekg (0, is.beg);
        char * buffer = new char [length];
        std::cout << "Reading " << filepath << " " << length << " characters... ";
        // read data as a block:
        is.read (buffer,length);
        if (is)
            std::cout << "all characters read successfully." << std::endl;
        else
            std::cout << "error: only " << is.gcount() << " could be read";
        is.close();
        // ...buffer contains the entire file...
        filebuffer = std::string(buffer,length);
        delete[] buffer;
    } else {
        std::cout << filepath << "open faild in getFileString" << std::endl;
    }
    return filebuffer;
}
void SplitString1(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}

void readLyris(const string &filename,vector<string> &lyris){
    string buffer = getFileString(filename);
    vector<string> split;
    SplitString1(buffer,split,"\n");
    for (vector<string>::iterator iter = split.begin();iter!=split.end();iter++){
        if(*iter!="")
            lyris.push_back(*iter);
    }
}
int main(int argc,char **argv){
    if (argc<4) {
        cout << "传入参数：midi文件 bmp 输出文件" << endl;
        return 0;
    }
    //string root="/home/lin/";
    //string name ="test";
    //string midif=root+"谢谢雅虎midi-BPM184.mid",tf=root+name+"MidiTemplate.txt";
    ofstream os(argv[3]);
    ParseMidi pm;
    FILE *f= fopen(argv[1],"r");

    vector<string> outLyris;
    vector<float> time,f0;
    int rate=48000,bmp=atoi(argv[2]);
    pm.ParseMidiKernelTemplate(f,bmp,rate,outLyris,f0,time);
    //fclose(f);
    for (int i =0;i<outLyris.size();i++){
        os<<outLyris[i]+" "<<time[i]<<" "<<f0[i]<<endl;

    }
    os<<". "<<0.25<<" "<<-1<<endl;

    return 0;
}
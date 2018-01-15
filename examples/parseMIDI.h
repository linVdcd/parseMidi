//
// Created by lin on 17-11-17.
//

#ifndef JDKSMIDI_PARSEMIDI_H
#define JDKSMIDI_PARSEMIDI_H

#include <vector>
#include <string>
#include <map>
class ParseMidi{


public:
    void ParseMidiKernel(FILE *midi,const int bmp,const int rate,const std::vector<std::string> &lyris,std::vector<std::string> &outLyris,std::vector<float> &f0,std::vector<float> &time);
    void ParseMidiKernelTemplate(FILE *midi,const int bmp,const int rate,std::vector<std::string> &outLyris,std::vector<float> &F0,std::vector<float> &time);

    };

#endif //JDKSMIDI_PARSEMIDI_H

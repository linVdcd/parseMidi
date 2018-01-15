
#include "jdksmidi/world.h"
#include "jdksmidi/filereadmultitrack.h"
#include <string>
#include <fstream>
#include <map>
#include "parseMIDI.h"
using namespace jdksmidi;
using namespace std;
std::map<int,float>Note2F0;

struct midi{
    midi(long t,float f0):t(t),f0(f0){}
    long t;
    float f0;
};

void DumpMIDIMultiTrack ( MIDIMultiTrack *mlt,int rt,int bmp,vector<midi>&f0,map<int,float> &Note2F0 )
{
    long delataT =rt*60/(bmp) ;
    MIDIMultiTrackIterator i ( mlt );
    const MIDITimedBigMessage *msg;
    fprintf ( stdout , "Clocks per beat: %d\n\n", mlt->GetClksPerBeat() );
    i.GoToTime ( 0 );
    float s=0,e=0;
    do
    {
        int trk_num;

        if ( i.GetCurEvent ( &trk_num, &msg ) )
        {

            //DumpMIDITimedBigMessage ( msg,time,f0 );
            if(msg){
                if(msg->IsNote()){
                    if(msg->IsNoteOn())
                    {
                        s = msg->GetTime();
                        //if((int)s%120!=0) s = (s/120+1)*120;
                        if (s-e>0.01){

                            f0.push_back(midi((s-e)/480*delataT,-1));


                        }
                    }
                    else if(msg->IsNoteOff())
                    {
                        e = msg->GetTime();
                        if(int(e)%60!=0) e = (e/60+1)*60 - int(e)%60;
                        float t = msg->GetNote();
                        if (t==122)
                            f0.push_back(midi((e-s)/480*delataT,-1));//加入空音
                        else if (t==120)
                            f0.push_back(midi((e-s)/480*delataT,-2));//rap，只控制时长
                        else if (t==124)
                            f0.push_back(midi((e-s)/480*delataT,1));
                        else

                            f0.push_back(midi((e-s)/480*delataT,Note2F0[int(t)]));

                    }
                }


            }
        }
    }
    while ( i.GoToNextEvent() );
}


void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
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






void readNote2F0(map<int,float> &Note2F0){
    string buffer;
    buffer="33:27.5\n34:29.135\n35:30.868\n36:32.703\n37:34.648\n38:36.708\n39:38.891\n40:41.203\n41:43.654\n42:46.249\n43:48.999\n";
    buffer+= "44:51.913\n45:55\n46:58.27\n47:61.735\n48:65.406\n49:69.296\n50:73.416\n51:77.782\n52:82.407\n53:87.307\n54:92.499\n55:97.999\n56:103.826\n";
    buffer+=  "57:110\n";
    buffer+="58:116.541\n";
    buffer+="59:123.471\n";
    buffer+="60:130.813\n";
    buffer+="61:138.591\n";
    buffer+="62:146.832\n";
    buffer+="63:155.563\n";
    buffer+="64:164.814\n";
    buffer+="65:174.614\n";
    buffer+="66:184.997\n";
    buffer+="67:195.998\n";
    buffer+="68:207.652\n";
    buffer+="69:220\n";
    buffer+="70:233.082\n";
    buffer+="71:246.942\n";
    buffer+="72:261.626\n";
    buffer+="73:277.183\n";
    buffer+="74:293.665\n";
    buffer+="75:311.127\n";
    buffer+="76:329.628\n";
    buffer+="77:349.228\n";
    buffer+="78:369.994\n";
    buffer+="79:391.995\n";
    buffer+="80:415.305\n";
    buffer+="81:440\n";
    buffer+="82:466.164\n";
    buffer+="83:493.883\n";
    buffer+="84:523.251\n";
    buffer+="85:554.365\n";
    buffer+="86:587.33\n";
    buffer+="87:622.254\n";
    buffer+="88:659.255\n";
    buffer+="89:698.456\n";
    buffer+="90:739.989\n";
    buffer+="91:783.991\n";
    buffer+="92:830.609\n";
    buffer+="93:880\n";
    buffer+="94:932.328\n";
    buffer+="95:987.767\n";
    buffer+="96:1046.502\n";
    buffer+="97:1108.731\n";
    buffer+="98:1174.659\n";
    buffer+="99:1244.508\n";
    buffer+="100:1318.51\n";
    buffer+="101:1396.913\n";
    buffer+="102:1479.978\n";
    buffer+="103:1567.982\n";
    buffer+="104:1661.219\n";
    buffer+="105:1760\n";
    buffer+="106:1864.655\n";
    buffer+="107:1975.533\n";
    buffer+="108:2093.005\n";
    buffer+="109:2217.461\n";
    buffer+="110:2349.318\n";
    buffer+="111:2489.016\n";
    buffer+="112:2637.02\n";
    buffer+="113:2793.826\n";
    buffer+="114:2959.955\n";
    buffer+="115:3135.963\n";
    buffer+="116:3322.438\n";
    buffer+="117:3520\n";
    buffer+="118:3729.31\n";
    buffer+="119:3951.066\n";
    buffer+="120:4186.009";
    vector<string> split;
    SplitString(buffer,split,"\n");
    for (vector<string>::iterator iter = split.begin();iter!=split.end();iter++){
        vector<string> NF;
        string line =*iter;
        SplitString(line,NF,":");
        if (NF.size()<=1)continue;
        Note2F0.insert(pair<int ,float>(atoi(NF[0].c_str()),atof(NF[1].c_str())));

    }


}









void ParseMidi::ParseMidiKernel(FILE *midi,const int bmp,const int rate,const std::vector<std::string> &lyris,std::vector<std::string> &outLyris,std::vector<float> &F0,std::vector<float> &time){
    readNote2F0(Note2F0);
    MIDIFileReadStreamFile rs ( midi );
    MIDIMultiTrack tracks;
    MIDIFileReadMultiTrack track_loader ( &tracks );
    MIDIFileRead reader ( &rs, &track_loader );
    reader.Parse();
    vector<struct midi> f0;
    DumpMIDIMultiTrack ( &tracks,rate,bmp,f0,Note2F0 );
    int index=0;
    for(int i=0;i<f0.size();i++){
        float tf0 = f0[i].f0;
        long times = f0[i].t;
        if(tf0==-1)
        {
            string t="，";
            outLyris.push_back(t);
            F0.push_back(-1);
            time.push_back(float(times)/float(rate));

        } else
        {
            outLyris.push_back(lyris[index]);
            F0.push_back(tf0);
            time.push_back(float(times)/float(rate));
            index++;
        }
    }
}


void ParseMidi::ParseMidiKernelTemplate(FILE *midi,const int bmp,const int rate,std::vector<std::string> &outLyris,std::vector<float> &F0,std::vector<float> &time){
    readNote2F0(Note2F0);
    MIDIFileReadStreamFile rs ( midi );
    MIDIMultiTrack tracks;
    MIDIFileReadMultiTrack track_loader ( &tracks );
    MIDIFileRead reader ( &rs, &track_loader );
    reader.Parse();
    vector<struct midi> f0;
    DumpMIDIMultiTrack ( &tracks,rate,bmp,f0,Note2F0 );
    int index=0;
    for(int i=0;i<f0.size();i++){
        float tf0 = f0[i].f0;
        long times = f0[i].t;
        if(tf0==-1)
        {
            string t=",";
            int s = outLyris.size();
            if(s>0&&outLyris[s-1]==",")
            {
                time[s-1]+=float(times)/float(rate);
                continue;
            }

            outLyris.push_back(t);
            F0.push_back(-1);
            time.push_back(float(times)/float(rate));


        } else
        {
            outLyris.push_back("+");
            F0.push_back(tf0);
            time.push_back(float(times)/float(rate));
            index++;
        }
    }
}


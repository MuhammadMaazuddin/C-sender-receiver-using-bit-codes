#include<iostream>
#include<fstream>
using namespace std;
void readCode(string *text)
{
    fstream file("code.txt");
    string line,text1="";
    while(getline(file,line))
    {
        for(int i=0;i<line.length();i++)
        {
            if(line[i]!='0' && line[i] != '1')
            {
                text1+=line[i];
            }
        }
    }
    *text = text1;
}
void readMsg(string *text)
{
    string line,text1="";
    fstream file("encodedMsg.txt");
    while(getline(file,line))
    {text1+=line;}
    *text = text1;
}
void save(string text)
{
    fstream file;
    file.open("decodedMsg.txt");
    file<<text;
}
void encodeMsg(string text ,string code)
{
    int num=0,iter=0;
    string msg;
    for(int i=0;i<text.length();i++)
    {
                num++;

        if(text[i] == '0')
        {
            msg+=code[num-1];
            num=0;
        }
      
    }
    save(msg);
}
int main()
{
    string msgCode,msg;
    readCode(&msgCode);
    readMsg(&msg);
    encodeMsg(msg,msgCode);

}
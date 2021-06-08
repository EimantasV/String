#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iomanip>

using namespace std;

int main()
{
    vector<string> links;
    unordered_map<string,vector<int>> zdzC; // zodziu count

    ifstream input("zodziai.txt");

    string txt;

    bool singleWord = false;
    bool isInserted = false;
    string wordBuild="";
    int lineID=1;
    while(!input.eof())
    {
        txt="";
        getline(input,txt);

        for(int i =0;i<txt.length();i++) // find words
        {
            singleWord = false;
            if((txt[i] >='A' &&txt[i] <='Z' )|| (txt[i] >='a' &&txt[i] <='z'))
            {
                singleWord = true;
                isInserted = false;
            }

            if(singleWord)
            {
                wordBuild+= txt[i];
            }
            else if(!isInserted)
            {
                if(zdzC.find(wordBuild) == zdzC.end()) // not found
                {
                    zdzC[wordBuild].push_back(1);
                    zdzC[wordBuild].push_back(lineID);
                }
                else
                {
                    zdzC[wordBuild][0] +=1;
                    zdzC[wordBuild].push_back(lineID);
                }
                isInserted=true;
                wordBuild="";
            }
            
            if((i==txt.length()-1) && !isInserted)
            {
                if(zdzC.find(wordBuild) == zdzC.end()) // not found
                {
                    zdzC[wordBuild].push_back(1);
                    zdzC[wordBuild].push_back(lineID);
                }
                else
                {
                    zdzC[wordBuild][0] +=1;
                    zdzC[wordBuild].push_back(lineID);
                }
            }
        }
        
        for(int i =0;i<txt.length();i++) // find URL
        {   
            string temp;
            if(txt[i]=='h')
            if(txt[i+1]=='t')
            if(txt[i+2]=='t')
            if(txt[i+3]=='p')
            if(txt[i+4]==':')
            if(txt[i+5]=='/')
            if(txt[i+6]=='/')// found http://
            {
                temp="http://";
                for(int a =i+7;a<txt.length();a++) // find URL
                {
                    if(txt[a]>32)
                    {
                        temp += txt[a];
                    }
                    else
                    {
                        links.push_back(temp);
                        break;
                    }
                    if(a==txt.length()-1)
                    {
                        links.push_back(temp);
                    }
                }
            }

            if(txt[i]=='h')
            if(txt[i+1]=='t')
            if(txt[i+2]=='t')
            if(txt[i+3]=='p')
            if(txt[i+4]=='s')
            if(txt[i+5]==':')
            if(txt[i+6]=='/')
            if(txt[i+7]=='/')// found https://
            {
                temp="https://";
                for(int a =i+8;a<txt.length();a++) // find URL
                {
                    if(txt[a]>32)
                    {
                        temp += txt[a];
                    }
                    else
                    {
                        links.push_back(temp);
                        break;
                    }
                    if(a==txt.length()-1)
                    {
                        links.push_back(temp);
                    }
                }
            }
            
            if(txt[i]=='w')
            if(txt[i+1]=='w')
            if(txt[i+2]=='w')
            if(txt[i+3]=='.')
            {
                temp="www.";
                for(int a =i+4;a<txt.length();a++) // find URL
                {
                    if(txt[a]>32)
                    {
                        temp += txt[a];
                    }
                    else
                    {
                        links.push_back(temp);
                        break;
                    }
                    if(a==txt.length()-1)
                    {
                        links.push_back(temp);
                    }
                }
            }
            
        }

        lineID++;
    }
    input.close();



    ofstream output1("WordsCount.txt");
    for( const auto& [key, value] : zdzC ) {
        if(value[0]>1)
        output1 << key << " " << value[0] << "\n";
    }
    output1.close();

    ofstream output3("Links.txt");
    for( const auto link : links ) {
        
        output3 << link << "\n";
    }
    output3.close();


    ofstream output2("Table.txt");
    output2 << setw(19) << left << "Word:" << "|  "; 
    for(int i=1;i<lineID;i++)
    {
        output2 << setw(3) << left << i << "|  ";
    }
    output2 << "\n";
    for( const auto& [key, value] : zdzC ) {
        if(value[0]>1)
        {
            output2 << setw(19) << left << key << "|";

            for(int i=1;i<lineID;i++)
            {
                bool exist= false;
                for(int a=1;a<value.size();a++)
                {
                    if(value[a]==i) 
                    {
                        exist=true; 
                        break; 
                    }
                }
                output2 << (exist?"  *  |": "     |");
            }

            // for(int i=1;i<value.size();i++)
            // {
            //     if(i==1 || (value[i-1]!=value[i]))
            //         output2  << value[i] << " ";
            // }
            output2 << "\n";
        }
    }
    output2.close();

    system("pause");
    return 0;
}
#include <stack>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// Check if a line is empty
bool lineEmpty(const string& line) {
    for (char c : line) {
        if (c != ' ' && c != '\t') return false;
    }
    return true;
}

// Function to check XML consistency and fix errors for command line
void checkXMLConsistencyCommandLine(const string& inputFile, const string& outputFile, bool fixErrors) {

// stacks and vectors
stack<char> tags;
stack<string> s;
vector<int> errors;
stack<string> wrong;

ifstream file(inputFile);
if (!file.is_open()) {
    cerr << "Error opening file!" << endl;
    return;
}
string line;
int lineNumber = 0, i = 0, j = 0, jLN, count = 0;
vector<string> output;
while (getline(file, line)) {
    if(lineEmpty(line)) continue;
    lineNumber++;
    i=0;
    while(line[i]){
        if(line[i]=='<'){
            if(!tags.empty()){
                int k=i+1;
                //first case: <....x        </....>
                if(line[k]=='/'){
                    while(line[k]!='>'){
                        k++;
                    }
                    output[jLN-1].insert(j+k-i-1,1,'>');
                    s.push(output[jLN-1].substr(j+1,k-i-2));
                    errors.push_back(jLN);
                    count++;
                }
                //second case: </....x      <****> && <....x  <....>
                else{
                    int k=i-1;
                    if(jLN==lineNumber){
                        while (!(line[k]!=' ')) k--;
                        line.insert(k+1,1,'>');
                        s.pop();
                        errors.push_back(lineNumber);
                        count--;
                    }
                    else{
                        k=output[jLN-1].size();
                        output[jLN-1].insert(k,1,'>');
                        while(output[jLN-1][--k]!='/'&&k!=-1);
                        if(k==-1){
                           s.push(output[jLN-1].substr(j+1,output[jLN-1].size()-j-2));
                        }
                        else s.pop();
                        errors.push_back(jLN);
                        count--;
                    }
                }
                tags.pop();
            }
            //third case: right sequence
            if(tags.empty()) tags.push('<');
            j=i,jLN=lineNumber;
        }
        if(line[i]=='>'){
            if(tags.empty()){
                int k=i;
                i++;
                while(line[k]!='/'&&k!=-1) k--;
                //first case: <....>     x/0...> && <....>  x....>
                if(line[k]=='/'){
                    line.insert(k,1,'<');
                    s.pop();
                    errors.push_back(lineNumber);
                    count--;
                }
                //second case: x....>        </....>
                else if(k==-1){
                    while(line[++k]=='\t');
                    line.insert(k,1,'<');
                    s.push(line.substr(k+1,i-k-1));
                    //cout<<s.top()<<" <<<<<<";
                    errors.push_back(lineNumber);
                    count++;
                }
            }
            else if (tags.top()=='<') tags.pop();
            string s1;
            if(line[j+1]=='/'){
                s1=line.substr(j+2,i-j-2);
                if(s1==s.top()){
                    s.pop();
                    count--;
                }
                else {
                    errors.push_back(lineNumber);
                    wrong.push(s1);
                    line=line.substr(0,line.size()-s1.size()-3);
                }
            }
            else{
                s1=line.substr(j+1,i-j-1);
                s.push(s1);
                count++;
            }
        }
        if((!s.empty())&&(!wrong.empty())&&(s.top()==wrong.top())){
            string s2="";
            count-=2;
            while(count--) s2+="\t";
            s2=s2+"</"+s.top()+">";
            output.push_back(line);
            line = s2;
            lineNumber++;
            //////////////////////s.pop();
            wrong.pop();
            i=-1;
        }
        i++;
    }
    output.push_back(line);
}

file.close();
    if (!errors.empty()) {
        cout << "Invalid XML detected with errors in lines: ";
        for (int errorLine : errors) cout << errorLine << " ";
        cout << endl;

        if (fixErrors && !outputFile.empty()) {
            ofstream outFile(outputFile);
            if (outFile.is_open()) {
                for (const auto& fixedLine : output) {
                    outFile << fixedLine << endl;
                }
                outFile.close();
                cout << "Errors fixed. Corrected XML written to: " << outputFile << endl;
            } else {
                cerr << "Failed to open output file: " << outputFile << endl;
            }
        }
    } else {
        cout << "The XML is valid." << endl;
    }
}




// Function to check XML consistency and fix errors for GUI
string checkXMLConsistencyGUI(const string& inputText, char flag) {

// stacks and vectors
stack<char> tags;
stack<string> s;
vector<int> errors;
stack<string> wrong;

istringstream stream(inputText);


string line;
int lineNumber = 0, i = 0, j = 0, jLN, count = 0;
vector<string> output;
while (getline(stream, line)) {
    if(lineEmpty(line)) continue;
    lineNumber++;
    i=0;
    while(line[i]){
        if(line[i]=='<'){
            if(!tags.empty()){
                int k=i+1;
                //first case: <....x        </....>
                if(line[k]=='/'){
                    while(line[k]!='>'){
                        k++;
                    }
                    output[jLN-1].insert(j+k-i-1,1,'>');
                    s.push(output[jLN-1].substr(j+1,k-i-2));
                    errors.push_back(jLN);
                    count++;
                }
                //second case: </....x      <****> && <....x  <....>
                else{
                    int k=i-1;
                    if(jLN==lineNumber){
                        while (!(line[k]!=' ')) k--;
                        line.insert(k+1,1,'>');
                        s.pop();
                        errors.push_back(lineNumber);
                        count--;
                    }
                    else{
                        k=output[jLN-1].size();
                        output[jLN-1].insert(k,1,'>');
                        while(output[jLN-1][--k]!='/'&&k!=-1);
                        if(k==-1){
                           s.push(output[jLN-1].substr(j+1,output[jLN-1].size()-j-2));
                        }
                        else s.pop();
                        errors.push_back(jLN);
                        count--;
                    }
                }
                tags.pop();
            }
            //third case: right sequence
            if(tags.empty()) tags.push('<');
            j=i,jLN=lineNumber;
        }
        if(line[i]=='>'){
            if(tags.empty()){
                int k=i;
                i++;
                while(line[k]!='/'&&k!=-1) k--;
                //first case: <....>     x/0...> && <....>  x....>
                if(line[k]=='/'){
                    line.insert(k,1,'<');
                    s.pop();
                    errors.push_back(lineNumber);
                    count--;
                }
                //second case: x....>        </....>
                else if(k==-1){
                    while(line[++k]=='\t');
                    line.insert(k,1,'<');
                    s.push(line.substr(k+1,i-k-1));
                    //cout<<s.top()<<" <<<<<<";
                    errors.push_back(lineNumber);
                    count++;
                }
            }
            else if (tags.top()=='<') tags.pop();
            string s1;
            if(line[j+1]=='/'){
                s1=line.substr(j+2,i-j-2);
                if(s1==s.top()){
                    s.pop();
                    count--;
                }
                else {
                    errors.push_back(lineNumber);
                    wrong.push(s1);
                    line=line.substr(0,line.size()-s1.size()-3);
                }
            }
            else{
                s1=line.substr(j+1,i-j-1);
                s.push(s1);
                count++;
            }
        }
        if((!s.empty())&&(!wrong.empty())&&(s.top()==wrong.top())){
            string s2="";
            count-=2;
            while(count--) s2+="\t";
            s2=s2+"</"+s.top()+">";
            output.push_back(line);
            line = s2;
            lineNumber++;
            //////////////////////s.pop();
            wrong.pop();
            i=-1;
        }
        i++;
    }
    output.push_back(line);
}

//file.close();
    if (!errors.empty()) {

        if(flag == 'f'){
            string out="";
            for(const auto& line : output){
                out+=line;
                out+='\n';
            }
            return out;
        }
        else if(flag=='c'){
            string out="";
            for (int errorLine : errors){
                out+=errorLine;
                out+=" ";
            }
        }

    } else {
        return "";
    }
}



// Main function
int main(int argc, char* argv[]) {
    /*if (argc < 4) {
        cerr << "Usage: xml_editor verify -i input_file.xml [-f] [-o output_file.xml]" << endl;
        return 1;
    }

    string inputFile, outputFile;
    bool fixErrors = false;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-i" && i + 1 < argc) {
            inputFile = argv[++i];
        } else if (arg == "-o" && i + 1 < argc) {
            outputFile = argv[++i];
        } else if (arg == "-f") {
            fixErrors = true;
        }
    }

    if (inputFile.empty()) {
        cerr << "Input file is required. Use -i <input_file.xml>" << endl;
        return 1;
    }
    */
    char flag; string text;
    cin>>flag>>text;
    cout<<checkXMLConsistencyGUI(text,flag);
    //checkXMLConsistencyCommandLine(inputFile, outputFile, fixErrors);
    return 0;
}

//inputs  : string xml, string flag
//outputs :

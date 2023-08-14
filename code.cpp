#include <iostream>
#include <fstream>
#include <string>


using namespace std;

void find_Pattern(ifstream& text_file , ifstream& pattern_file , int outputFileNo );
bool match_Pattern(const string& text_line, const string& pattern_line, int textPos , int patternPos);

int main()
{
   cout << "Enter the number of test cases :" << endl;
   int num_testCases;
   cin>>num_testCases;
   
  
   for (int i=1; i<=num_testCases; i++){
       
       ifstream text_file("text"+to_string(i)+".txt");
       

        ifstream pattern_file("pattern"+ to_string(i)+ ".txt");
        

       if(!text_file.is_open()){
            cerr << "There doesn't exist the text"<<i<<".txt" <<endl;
            continue;
       }

        

        else if(!pattern_file.is_open()){
            cerr << "There doesn't exist the pattern "<<i<<".txt" <<endl;
            continue;
            }

        else{
            find_Pattern(text_file,pattern_file,i);
        }
        text_file.close();
        pattern_file.close();



   }
   
   return 0;
}

void find_Pattern(ifstream& text_file , ifstream& pattern_file , int outputFileNo ){
    
    string text;
    string text_line;
    string pattern_line;

    // read the first line of the pattern file
    getline(pattern_file, pattern_line);

    // open an output file
    ofstream output_file;
    output_file.open("output "+to_string(outputFileNo)+".txt");
    if (!output_file.is_open()){
        cerr<< "There is no  output_file "<< outputFileNo << endl;
    }


    int line_number = 1;
    bool Pattern_is_found = false;

    while(getline(text_file, text_line)){
        text += text_line + "\n";
        }


    for (unsigned int i=0 ; i< text.length(); i++){
        if(match_Pattern (text, pattern_line,i, 0)){

            int position = i;
            for(unsigned int a =1; a<=i ; a++){
                if(text[a] == '\n'){
                    line_number ++;
                    position = i -a;
                }
            }

            cout << "Pattern is found at line " << line_number << " , position " << position << endl;
            output_file << "Pattern is found at line " << line_number << " , position " << position << endl;
            Pattern_is_found = true;
        }
    }

    output_file.close();

}

bool match_Pattern(const string& text, const string& pattern_line, int textPos , int patternPos){

    if(patternPos == pattern_line.length()){
        return true;
    }
    else if ((text[textPos] == '\n') && (pattern_line[patternPos] == ' ')){
        return match_Pattern (text, pattern_line , textPos+1 , patternPos+ 1);
    }
    else if( ( textPos< text.length()) && (text[textPos] == pattern_line[patternPos]) || ( pattern_line[patternPos] == '.' )){
        return match_Pattern(text,pattern_line,(textPos+1) ,patternPos+1);
    }
    else if( (patternPos+1 < pattern_line.length()) && ( pattern_line[patternPos+1] == '?') ){
        return match_Pattern(text,pattern_line,textPos,patternPos+2);
    }
    else if( (patternPos == 0) && ( pattern_line[patternPos] == '^') ){
        return  textPos==0 && match_Pattern(text,pattern_line,textPos,patternPos+1);
    }
    else if((textPos == text.length()-1) && (patternPos == pattern_line.length()-1) && ( pattern_line[patternPos] == '$')  ){
        return true;
    }
    else{
        return false;
    } 
}


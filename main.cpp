/*

2.0 Changes:
- Warnings now explain why 2 colors are hard to tell apart and give a tip
  on how to fix it (like add more blue, or make one color lighter/darker)
- Every check gets saved to colorResults.txt (new checks get added to the end)
- 3 New major functions:
    getColorValue - asks for one red, green, or blue value until its valid
    saveResultsToFile - writes the results of a check to the file
    getWhyAndHowToFix - builds the why & tip message for a warning
- New vector: resultMessages holds the results of each check before saving
- RGB value range now 0-255 instead of 0-256
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

//function prototypes
int getColorValue(string channelName);
void saveResultsToFile(ofstream &resultsFile, vector<string> &resultMessages);
string getWhyAndHowToFix(double differenceInRedGreenMix, int differenceInBlue);

int main()
{


int numberOfColorsToCheck;
  int redValue[3],greenValue[3],blueValue[3];
char userWantsToGoAgain='y';
int tooCloseLimit=90; //if the diffrence is less than this its too close. 90 seemed ok after testing
vector<string> resultMessages; //holds every result line from one check so it can be saved to the file
ofstream resultsFile("colorResults.txt", ios::app); //ios::app adds to the end of the file instead of erasing old results



cout<<"Color Blindness Pallete Checker"<<endl;
    cout<<"This program checks colors for Deuteranopia (red-green color blindness)."<<endl;
cout<<"Every check gets saved to colorResults.txt"<<endl;

if(!resultsFile)
{
    cout<<"Could not open colorResults.txt, results will not be saved."<<endl;
}





//main loop
while(userWantsToGoAgain=='y')
{
  resultMessages.clear(); //start fresh for this check

  cout<< endl << "How many colors do you want to check? (2 or 3): ";
  while(!(cin>>numberOfColorsToCheck) || numberOfColorsToCheck<2 || numberOfColorsToCheck>3){
      if(cin.eof()) return 0;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout<<"Please enter a number, 2 or 3: ";
  }

  //get the rgb for each color. has to be 0-255 or it makes u retype it
  for(int i=0;i<numberOfColorsToCheck;i++){
      cout<<endl<<"Color "<<i+1<<":"<<endl;

    redValue[i]=getColorValue("Red");
    if(redValue[i]==-1) return 0;
    greenValue[i]=getColorValue("Green");
    if(greenValue[i]==-1) return 0;
    blueValue[i]=getColorValue("Blue");
    if(blueValue[i]==-1) return 0;

    resultMessages.push_back("Color "+to_string(i+1)+": R="+to_string(redValue[i])+" G="+to_string(greenValue[i])+" B="+to_string(blueValue[i]));
  }


  /*
  how it works:
  deutaranopia = green cones dont work (most common type of color blindness)
  so red and green kind of blend together into one color for them

  so i make a "mix" of red and green for each color
  green doesnt work for them so it counts less (30%) and red counts more (70%)
  blue still works fine so that stays the same, I just found some rough estimate values online for CB colorshifts/transformations.
  */



  double redGreenMixForColorBlind[3];

  for(int i=0;i<numberOfColorsToCheck;i++){
      redGreenMixForColorBlind[i]=0.7*redValue[i]+0.3*greenValue[i];
  }

  cout<<endl<<"Results"<<endl;
int numberOfWarnings=0;



  //compare every color with every other color (1&2, 1&3, 2&3)
  //j starts at i+1 so it doesnt check the same pair twice or a color with itself
  for(int i=0;i<numberOfColorsToCheck;i++)
  {
    for(int j=i+1;j<numberOfColorsToCheck;j++){

    //how diffrent the 2 colors look = how diffrent the mix is + how diffrent the blue is
    //if its negative flip it to positive so negatives dont cancel out
      double differenceInRedGreenMix=redGreenMixForColorBlind[i]-redGreenMixForColorBlind[j];
    if(differenceInRedGreenMix<0) differenceInRedGreenMix=-differenceInRedGreenMix;

      int differenceInBlue=blueValue[i]-blueValue[j];
      if(differenceInBlue<0){
        differenceInBlue=-differenceInBlue;
      }



    double totalDifferenceBetweenTheTwoColors=differenceInRedGreenMix+differenceInBlue;
    string pairMessage;

      if(totalDifferenceBetweenTheTwoColors<tooCloseLimit){
          pairMessage="WARNING: Color "+to_string(i+1)+" and Color "+to_string(j+1)+" are hard to tell apart with Deuteranopia.";
        numberOfWarnings++;
      }
      else
      {
      pairMessage="Color "+to_string(i+1)+" and Color "+to_string(j+1)+" are easy to tell apart.";
      }

      cout<<pairMessage<<endl;
      resultMessages.push_back(pairMessage);

      //if its a warning tell the user why and how to fix it
      if(totalDifferenceBetweenTheTwoColors<tooCloseLimit){
          string feedback=getWhyAndHowToFix(differenceInRedGreenMix, differenceInBlue);
          cout<<feedback<<endl;
          resultMessages.push_back(feedback);
      }
    }
  }




  if(numberOfWarnings==0){
      cout<<"All good! These colors work for people with Deuteranopia."<<endl;
      resultMessages.push_back("All good! These colors work for people with Deuteranopia.");
  }
  else
  {
      cout<<"Total warnings: "<<numberOfWarnings<<endl;
      resultMessages.push_back("Total warnings: "+to_string(numberOfWarnings));
  }

  saveResultsToFile(resultsFile, resultMessages);

    cout<<endl<<"Do you want to check more colors? (y/n): ";
  if(!(cin>>userWantsToGoAgain)) break;
}

resultsFile.close();
cout<<"Goodbye!"<<endl;
  return 0;
}


//asks for one color channel (Red, Green, or Blue) and keeps asking until its 0-255
//channelName is pass by value because the function only needs to print it
//returns the valid number the user typed
int getColorValue(string channelName)
{
    int value;
    cout<<"  "<<channelName<<": ";
    while(!(cin>>value) || value<0 || value>255){
        if(cin.eof()) return -1;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"  Please enter a number between 0 and 255: ";
    }
    return value;
}


//writes every line from this check into colorResults.txt
//resultsFile is pass by reference because a file stream cant be copied, it has to write to the same open file
//resultMessages is pass by reference so it doesnt make a copy of the whole vector
//void because it just writes to the file and doesnt need to give anything back
void saveResultsToFile(ofstream &resultsFile, vector<string> &resultMessages)
{
    resultsFile<<"----- New Check -----"<<endl;
    for(int i=0;i<resultMessages.size();i++){
        resultsFile<<resultMessages[i]<<endl;
    }
    resultsFile<<endl;
}


//explains why 2 colors are too close and gives a tip on how to fix it
//both parameters are pass by value because it only reads them
//returns the message as a string so main can print it and save it to the file
string getWhyAndHowToFix(double differenceInRedGreenMix, int differenceInBlue)
{
    string message="  Why: to someone with Deuteranopia their red-green mix is only "+to_string((int)differenceInRedGreenMix)
        +" apart and their blue is only "+to_string(differenceInBlue)+" apart (together they need to be at least 90 apart).";

    //tell them to fix whichever one is smaller since thats the bigger problem
    if(differenceInBlue<differenceInRedGreenMix){
        message+="\n  Tip: they have almost the same amount of blue. Add a lot more blue to one of them (like turning it purple or teal), blue still shows up fine with Deuteranopia.";
    }
    else{
        message+="\n  Tip: changing red to green doesnt help since those look the same to them. Make one color a lot lighter or darker instead.";
    }

    return message;
}


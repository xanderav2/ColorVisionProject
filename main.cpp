#include <iostream>
using namespace std;

int main()
{

    
int numberOfColorsToCheck;
  int redValue[3],greenValue[3],blueValue[3];
char userWantsToGoAgain='y';
int tooCloseLimit=90; //if the diffrence is less than this its too close. 90 seemed ok after testing

    

cout<<"Color Blindness Pallete Checker"<<endl;
    cout<<"This program checks colors for Deuteranopia (red-green color blindness)."<<endl;




    
//main loop
while(userWantsToGoAgain=='y')
{

  cout<< endl << "How many colors do you want to check? (2 or 3): ";
    cin>>numberOfColorsToCheck;
  while(numberOfColorsToCheck<2 || numberOfColorsToCheck>3){ cout<<"Please enter 2 or 3: "; cin>>numberOfColorsToCheck; }

  //get the rgb for each color. has to be 0-256 or it makes u retype it
  for(int i=0;i<numberOfColorsToCheck;i++){
      cout<<endl<<"Color "<<i+1<<":"<<endl;

    cout<<"  Red: "; cin>>redValue[i];
      while(redValue[i]<0 || redValue[i]>256){
      cout<<"  That number has to be between 0 and 256. Try again: ";
        cin>>redValue[i];}

      cout<<"  Green: ";
    cin>>greenValue[i];
    while(greenValue[i]<0 || greenValue[i]>256)
    {
        cout<<"  That number has to be between 0 and 256. Try again: ";
      cin>>greenValue[i];
    }

    cout<<"  Blue: "; cin>>blueValue[i];
  while(blueValue[i]<0 || blueValue[i]>256){
        cout<<"  That number has to be between 0 and 256. Try again: "; cin>>blueValue[i];
  }
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

      if(totalDifferenceBetweenTheTwoColors<tooCloseLimit){
          cout<<"WARNING: Color "<<i+1<<" and Color "<<j+1<<" are hard to tell apart with Deuteranopia."<<endl;
        numberOfWarnings++;
      }
      else
      {
      cout<<"Color "<<i+1<<" and Color "<<j+1<<" are easy to tell apart."<<endl;
      }
    }
  }



    
  if(numberOfWarnings==0) cout<<"All good! These colors work for people with Deuteranopia."<<endl;
  else
  {
      cout<<"Total warnings: "<<numberOfWarnings<<endl;
  }

    cout<<endl<<"Do you want to check more colors? (y/n): ";
  cin>>userWantsToGoAgain;
}

cout<<"Goodbye!"<<endl;
  return 0;
}

Checks if 2 or 3 colors (entered as RGB values) can be told apart by someone with Deuteranopia (red-green color blindness). Prints a warning for any pair that looks too similar.

Version 2 changes:

-warnings now say why the colors are too close and how to fix it  
-saves every check to colorResults.txt  
-fixed bug where 256 was allowed, now its 0-255. (old range was 0-256)  
-added the getColorValue function (returns int, pass by value) for rgb input  
-added the  saveResultsToFile function (void, pass by reference) writes results to the file  
-added the  getWhyAndHowToFix function (returns string) makes the why/tip message  
- vector resultMessages holds the results before saving  
-arrays redValue, greenValue, blueValue still hold the rgb values  
-uses ofstream for file output  


Here is an example of the program running:

How many colors do you want to check? (2 or 3): 2

Color 1:  
Red: 255  
Green: 0  
Blue: 0

Color 2:  
Red: 200  
Green: 0  
Blue: 0

Results  
WARNING: Color 1 and Color 2 are hard to tell apart with Deuteranopia.  
Why: to someone with Deuteranopia their red-green mix is only 38 apart and their blue is only 0 apart (together they need to be at least 90 apart).  
Tip: they have almost the same amount of blue. Add a lot more blue to one of them (like turning it purple or teal), blue still shows up fine with Deuteranopia.  
Total warnings: 1

Do you want to check more colors? (y/n): n  
Goodbye!

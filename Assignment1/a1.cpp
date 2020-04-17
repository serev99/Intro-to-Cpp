//Name: Diyang Zhang
//McGill ID: 260796176


#include <iostream>
#include <string>

using namespace std;

/*
Question 1:
Write a function that asks the user to input a sentence, then it will ask the user to enter one
letter. The function will then count the number of occurrences of this letter in the provided
sentence. Don't forget that both uppercase and lowercase letters should be counted. 
*/
void countLetter() {
    string sentence; 
    string letter; 
    cout << "Please enter a sentence:" << endl;
    getline(cin, sentence);  //read full sentence
    cout << "Please enter a letter:" << endl;
    cin >> letter;  //read one word
    char obj = tolower(letter[0]);
    int count = 0;
    for (unsigned int i = 0; i < sentence.size(); i++) {
        if (tolower(sentence[i]) == obj) {
            count++;
        }
    }
    cout << "The letter " << obj << " is repeated " << count << " times in your sentence." << endl;
}


/*
Question 2:
According to wikipedia: The 26 code words in the NATO phonetic alphabet are assigned to
the 26 letters of the English alphabet in alphabetical order as follows: Alfa, Bravo, Charlie,
Delta, Echo, Foxtrot, Golf, Hotel, India, Juliett, Kilo, Lima, Mike, November, Oscar, Papa,
Quebec, Romeo, Sierra, Tango, Uniform, Victor, Whiskey, X-ray, Yankee, Zulu.
Write a function that takes a word and translate each letter into its corresponding phonetic
alphabet.
*/
string convertHelper(char letter) {
    switch (letter) {
        case 'a':
            return "Alfa";
        case 'b':
            return "Bravo";
        case 'c':
            return "Charlie";
        case 'd':
            return "Delta";
        case 'e':
            return "Echo";
        case 'f':
            return "Foxtrot";
        case 'g':
            return "Golf";
        case 'h':
            return "Hotel";
        case 'i':
            return "India";
        case 'j':
            return "Juliett";
        case 'k':
            return "Kilo";
        case 'l':
            return "Lima";
        case 'm':
            return "Mike";
        case 'n':
            return "November";
        case 'o':
            return "Oscar";
        case 'p':
            return "Papa";
        case 'q':
            return "Quebec";
        case 'r':
            return "Romeo";
        case 's':
            return "Sierra";
        case 't':
            return "Tango";
        case 'u':
            return "Uniform";
        case 'v':
            return "Victor";
        case 'w':
            return "Whiskey";
        case 'x':
            return "X-ray";
        case 'y':
            return "Yankee";
        case 'z':
            return "Zulu";
    }
    return "";
}

void convertPhonetic() {
    string word;
    string phonetic;
    cout << "Please enter a word:" << endl;
    cin >> word;
    for (unsigned int i = 0; i < word.size(); i++) {
        phonetic += convertHelper(tolower(word[i])) + " ";
    }
    cout << phonetic << endl;
}


/* Question 3
(A) 
Q: Research tail recursivity and explain in your own words why it is better to design
your recursive function this way.

A: The tail recursive functions considered better than normal recursive functions as they can be
optimized by compiler with space and execution efficiency. Since recurisve call is always the last 
statement in tail recursion, there is nothing left to do in the current function, so saving the 
current function's stack frame is of no use. In other words, the calling function will never get a
chance to do anything after the call if this optimization is performed. However, in normal recursion,
the computer usually uses stack to remember the call locations.

(B)
Q: Can any recursive function be designed to be tail recursive? Please develop your
answer by providing clear explanation

A: By modifying the function in serveral ways, we can write any recursive function in a tail-recursive
way. While local modification is sufficient, as in the next questions, we can often add an 
"accumulator" that builds some expression that is returned. Alternatively, modifying globally the
entire program may help to rewrite the function in a tail-recursive way. Each function takes as an
extra argument the function that contains future actions, the method called continuation passing, 
helping to rewrite the function.
 */


/*
Question 4:
Write a tail recursive factorial function.
*/
int factHelper(int number, int accumulator) {
    if (number == 0) return accumulator;
    return factHelper(number-1, number*accumulator);
}

void factorial() {
    string numInput;
    cout << "Please enter a number:" << endl;
    cin >> numInput;  //read one word(String)
    int number = stoi(numInput);
    int result = factHelper(number, 1);
    cout << "The factorial of " << number << " is " << result << endl;
}


/*
Question 5
Write an enhanced version of your recursive factorial function using an array that stores
the calculated factorial of the first 6 factorials. This means that the values for the first 6
factorials (1, 2, 6, 24, 120, 720) are already known and stored in an array so you don’t need
to recalculate them each time the function runs.
*/
int enhancedFactHelper(int number, int accumulator) {
    int array[6] = {1, 2, 6, 24, 120, 720};
    if (number == 0) {
        return accumulator;
    } else if (number <= 6) {
        return accumulator * array[number-1];
    }
    return enhancedFactHelper(number-1, number*accumulator);
}

void enhancedFactorial() {
    string numInput;
    cout << "Please enter a number:" << endl;
    cin >> numInput;  //read one word(String)
    int number = stoi(numInput);
    int result = enhancedFactHelper(number, 1);
    cout << "The factorial of " << number << " is " << result << endl;
}


/*
Main Function
*/
int main() {
    countLetter();
    convertPhonetic();
    factorial();
    enhancedFactorial();
}
# cheaterBee
## About
Cheater Bee can be used to "solve" the New York Times 'Spelling Bee' daily puzzle [here](https://www.nytimes.com/puzzles/spelling-bee). This puzzle involves finding all words made up of a given subset of letters. Here are the additional rules:
1. Each word must contain the indicated required character at least (but not limited to) once
2. Each word may NOT contain any letters other than the indicated subset of letters
3. Words may contain duplicates of the same letter

While the Spelling Bee consists of a single required letter and an additional 6 letter subset (for a total of 7 possible letters including the required letter), the Cheater Bee will solve for a larger or smaller subset  as well. 


## How To Run
Running the program requires 3 arguments, plus an optional 4th argument: 
1. Single letter required in word
2. Other characters that are allowed to be used in words - entered as a single string of characters. Minimum of 3, max of 25 (which would return all words in your dictionary file)
3. Dictionary file name - feel free to use the txt file here or provide your own

The order of arguments are as follows:
[required char] [additional chars] [dictionary file name] [optional minimum word length]

**Limitations**
- Assumes longest possible word is 45 characters (pneumonoultramicroscopicsilicovolcanoconiosis)
- Results will only be as good as the dictionary file used
- Assumes words in dictionary file are separated by either comma, new line or space

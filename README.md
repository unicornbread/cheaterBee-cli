# cheaterBee
## About
Cheater Bee can be used to "solve" the New York Times 'Spelling Bee' daily puzzle [here](https://www.nytimes.com/puzzles/spelling-bee). This puzzle involves finding all words made up of a given subset of letters. Here are the additional rules:
1. Each word must contain the indicated *required character* at least (but not limited to) once
2. Each word may NOT contain any letters other than the indicated subset of letters
3. Words may contain duplicates of the same letter

While the Spelling Bee consists of a single required letter and an additional 6 letter subset (for a total of 7 possible letters including the required letter), the Cheater Bee will solve for a larger or smaller subset  as well. 


## How To Run
Running the program requires 3 inputs:
1. Dictionary file name - feel free to use the txt file here or provide your own
2. Alpha character required in word
3. Other characters that are allowed to be used in words

The order of inputs are as follows:
spellerBee [required char] [additional chars] [dictionary file name]

**Limitations**

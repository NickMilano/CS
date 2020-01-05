/*Program 1 - Custom Sort
 *Nick Milano
 *CS3411
 *Reads a given file via command line and sorts each line
 *of the file by word, then sorts all lines together, both sorts
 *are done via bubblesort					*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Simple swap function to move around words*/
void swap(char *str1, char *str2) {
	char *temp= (char *) malloc((strlen(str1)+1*sizeof(char)));
	strcpy(temp,str1);
	strcpy(str1,str2);
	strcpy(str2,temp);
	free(temp);
}

/*Function for sorting each line indvidually
 *Uses bubblesort implementation	    */
void sortLine(char line[], int len2){
	/*Init some variables so we can manage data and keep count of stuff*/
	int len = len2;
	char *copyline=malloc((len+1) * sizeof(char));
	char s = ' ';
	int wordCount = 0, counter=0, counter2=0, n=0, fr=10;
	char **words = malloc(10 * sizeof(*words));
	/*setting memory to avoid errors*/
	memset(copyline,0,len+1);
	for(n=0; n < 10; n++) {
		words[n]=malloc((len+1)*sizeof(*(words[n])));	
		memset(words[n],0,(len+1)*sizeof(char));
	}
	n=0;
	/*getting a count of words by countings space characters*/
	for(counter = 0; counter<len; counter++) {
		if(line[counter] == s) 
			wordCount=wordCount+1;
	}
	wordCount = wordCount + 1;
	
	counter = 0;
	/*can realloc memory incase of more words*/
	if(wordCount >  10) {
		fr=wordCount;
		words=realloc(words,wordCount*sizeof(char*));
			for(n=10; n<wordCount;n++) {
				words[n]=malloc((len+1)*sizeof(char));
				memset(words[n],0,(len+1)*sizeof(char));
				}
	}

	n=0;
	/*simple for loop that moves each word into a section of the array*/
        for(counter=0; counter<len; counter++){
		/*break if new line to possibly prevent an OOB error*/
		if(line[counter]=='\n') {
			words[n][counter2]=' ';
			break;
		}
		/*if we get a space we move to the next row of the array and reset the column*/
		if(line[counter]==s){
			words[n][counter2]=line[counter];
			n = n+1;
			counter2=0;
		/*else we just keep adding columns*/
		} else {
			words[n][counter2]=line[counter];
			counter2=counter2+1;
		}
	}
	/*bubble sort to rearrange words in order*/
	for(counter=0;counter<wordCount-1;counter++) {
		for(counter2=0;counter2<wordCount-1;counter2++) {
			if(strcmp(words[counter2],words[counter2+1])>0) {
				swap(words[counter2],words[counter2+1]);
				}
		}
	}
	/*for loop to add all our words back into a string in order*/
	for(counter=0;counter<wordCount;counter++) {
		strcat(copyline,words[counter]);
	}
	/*copying the final string into our pointer*/
	strcpy(line,copyline);
	/*adding a return line at the end of the string*/
	n=strlen(line);
	line[n-1]='\n';
	/*freeing memory*/
	for(n=0;n<fr;n++) {
		free(words[n]);
	}
	free(words);
	free(copyline);
}
/*Function to sort all lines after they have been sorted
 * also removes duplicate lines				*/
void sortFull(char str[], int lines, int size) {
	/*init some variables*/
	int len = size;
        char *copyStr=malloc((len+1) * sizeof(char));
        char s = '\n';
        int n=0, counter=0, counter2=0;
        char **words = malloc((len+1)* sizeof(*words));
	/*setting memory for error protection*/
        memset(copyStr,0,len+1);
       
        for(n=0; n < len; n++) {
                words[n]=malloc((len+1)*sizeof(*(words[n])));
                memset(words[n],0,(len+1)*sizeof(char));
        }
	/*filling a 2d array with each string instead of word this time*/
        for(n=0; n<len; n++){
		if(str[n]==s) {
                        words[counter][counter2]=s;
			counter=counter+1;
			counter2=0;
                } else {
		        words[counter][counter2]=str[n];
                        counter2=counter2+1;
                }
        }	
	/*using bubble sort to organize each line in order
	 *if 2 strings match it gets moved to the very end and
	 *decrease the # of lines to read esentially cutting off
	 *that value						*/	 
	for(counter=0; counter<lines-1; counter++) {
		for(counter2=0; counter2<lines-1; counter2++) {
       			if(strcmp(words[counter2],words[counter2+1])>0) { 
                		swap(words[counter2],words[counter2+1]);
			} else if(strcmp(words[counter2],words[counter2+1])==0) {
				for(n=counter2+1;n<lines;n++){
					swap(words[n],words[n+1]);
					}
			lines=lines-1;
			}		
		}
	}
	/*copying each line back into the string*/
	for(n=0; n<lines; n++) {
		strcat(copyStr,words[n]);
	}
	/*copying result to our string*/
	strcpy(str,copyStr);
	/*freeing memory*/
	for(n=0;n<len;n++) {
                free(words[n]);
        }
	free(words);
	free(copyStr);	


}

int main(int argc, char *argv[]) {
	/*init some variables*/
	char *str = malloc(100 * sizeof(char));
	char *line=malloc(100 * sizeof(char));
	char *lineSorted=malloc(100 * sizeof(char));
	int file, wfile, size1, i=0,j=0;
	int lines = 0;
	/*some error checking to make sure we have correct
 	 *args and files open properly			 */ 
	if(argc != 2 && argc != 3) {
        	free(lineSorted);
        	free(line);
        	free(str);
		return 0;
	} else if(argc == 2) {
		file=open(argv[1], O_RDONLY);
	} else if(argc == 3) {
		file=open(argv[1], O_RDONLY);
		wfile=open(argv[2], O_WRONLY|O_TRUNC|O_CREAT,0666);
		if(wfile == -1) {
		        free(lineSorted);
       			free(line);
        		free(str);
			return 0;
		}
	}
	if(file == -1) {
        	free(lineSorted);
        	free(line);
        	free(str);
		return 0;
	}
	/*using lseek to determine how much space to allocate*/
	size1 = lseek(file, 0, SEEK_END);
	lseek(file,0,SEEK_SET);
	/*potential realloc if the size is bigger than the init value*/
	if(size1 > 100) {
		str = realloc(str, size1*sizeof(char));
		line = realloc(line, size1*sizeof(char));
		lineSorted= realloc(lineSorted, (size1+1)*sizeof(char));
	}
	/*setting memory for our vars to prevent errors*/
	memset(str,0,size1);
	memset(line,0,size1);
	memset(lineSorted,0,size1);
	/*reading in the entire file at once*/
	read(file,str,size1);
	/*loop through all characters and call our line sort method whenever we hit new line*/
	while(i < size1) {
		line[j]=str[i];
		if(str[i] == '\n') {
			/*sort line here as well as add the sorted line into memory*/
			sortLine(line,j+1);
			strcat(lineSorted,line);
			/*resetting values*/
			memset(line,0,strlen(line));
			j=-1;
			lines=lines+1;
				}
		j=j+1;
		i=i+1;
	}	
	/*simple check to skip sorting if we only have 1 line (its already sorted)*/
	if(lines > 1)
		sortFull(lineSorted,lines,size1);
	/*printing into our buffer with the entire sorted string*/
	sprintf(str, lineSorted);
	/*finding our new size then writing it to the terminal or file depending on args*/
	size1=strlen(str);	
	if(argc == 2){
		write(1, str, size1);
	} else {
		write(wfile, str, size1);
		close(wfile);
	}
	/*freeing memory and closing files*/
	free(lineSorted);	
	free(line);
	free(str);
	close(file);
	return 0;
}

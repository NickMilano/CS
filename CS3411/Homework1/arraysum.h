int dosum(int array[], int arraysize) {
    int sum, i;

    if(arraysize == 0) return 0;  

    for(i=0; i < arraysize; i++) {
	sum=sum+array[i];
    }
  
    return sum;
}

int domax(int array[], int arraysize) {
    int max, i;
    
    if(arraysize == 0) return 0;
    max=array[0];

    for(i=1; i < arraysize; i++){
	if(max<array[i]) max=array[i];
    }

    return max;
}

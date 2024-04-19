#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double mean(float *ptr, int count){ // Calculate the mean of the data
    int i;
    double sum=0,mean;
    for(i=0;i<count;i++){
        sum+=ptr[i];
    }
    mean = sum / count;
    return mean; 
}

void sort(float *ptr,int count){ // Sort the data in ascending order
    int i, j;
    float temp;
    for(i=0;i<count;i++){
        for(j=0;j<count;j++){
            if(ptr[i]<ptr[j]){
                temp=ptr[i];
                ptr[i]=ptr[j];
                ptr[j]=temp;
            }
        }
    }
    // printf("\n Sorted array:\n");
    // for(i=0;i<count;i++){
    //      printf("%f\n", ptr[i]);
    // }
}

void mode(float *ptr, int count) { //Calculate the mode of the data, i.e, count the occurances and then find the maximum occurance of a particular data

    // Dynamically allocate memory for storing values and their counts
    float *values = (float *)malloc(count * sizeof(float));
    int *occurrences = (int *)calloc(count, sizeof(int)); // Initialize to 0
    if (values == NULL || occurrences == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    // Count occurrences
    int unique_count = 0;
    for (int i = 0; i < count; i++) {
        int found = 0;
        for (int j = 0; j < unique_count; j++) {
            if (values[j] == ptr[i]) {
                occurrences[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            values[unique_count] = ptr[i];
            occurrences[unique_count]++;
            unique_count++;
        }
    }

    // Find the maximum occurrence count
    int max_count = 0;
    for (int i = 0; i < unique_count; i++) {
        if (occurrences[i] > max_count) {
            max_count = occurrences[i];
        }
    }

    // Print the datasets with maximum occurrences
    for (int i = 0; i < unique_count; i++) {
        if (occurrences[i] == max_count) {
            printf("%.2f (Occurrences: %d)\n", values[i], occurrences[i]);
        }
    }

    // Free allocated memory
    free(values);
    free(occurrences);
}

double median(float *ptr, int count){//Calculate the median of the data
    //sorting the data in ascending order
    sort(ptr,count);
    // Calculate median
    if (count % 2 == 0) { //Finding the middle point
        // If count is even, median is the average of the two middle elements
        return (ptr[count / 2 - 1] + ptr[count / 2]) / 2.0;
    } else {
        // If count is odd, median is the middle element
        return ptr[count / 2];
    }
}

double geometricMean(float *ptr, int count) { //Calculate the Geometric Mean of the data
    double product = 1.0;

    // Multiply all elements together
    for (int i = 0; i < count; i++) {
        product *= ptr[i];
    }

    // Calculate geometric mean
    return pow(product, 1.0 / count);
}

double harmonicMean(float *ptr, int count) { // Calculate the Harmonic Mean of the data
    double sum = 0.0;

    // Calculate the sum of reciprocals of elements
    for (int i = 0; i < count; i++) {
        sum += 1.0 / ptr[i];
    }

    // Calculate harmonic mean
    return count / sum;
}

double standardDeviation(float *ptr, int count, double mean) { //Calculate the Standard Deviation of the data
    float variance = 0.0;
    double stddev = 0.0;

    // Calculate variance
    for (int i = 0; i < count; i++) {
        variance += pow(ptr[i] - mean, 2);
    }
    variance /= count; //dividing it by count

    // Calculate standard deviation
    stddev = sqrt(variance); //square root

    return stddev;
}

void readFile(char *file) {
    FILE *fptr;
    int count = 1; // Number of elements or lines
    char ch;
    float f;
    int i;
    int m=20; //basic dynamic memory allocation

    // Opening file in read mode
    fptr = fopen(file, "r");
    if (fptr == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Counting lines
    while ((ch = fgetc(fptr)) != EOF) {
        if (ch == '\n') {
            ++count;
        }
    }

    printf("Number of Lines in File: %d\n", count); 

    int rem = count/m;
    // printf("\n %d \n",rem);
    m=(rem+1)*20; //Multiplying the memory to be allocated as per the size of the data 

    // Dynamically allocate memory using malloc()
    float *ptr = (float *)malloc(m * sizeof(float)); //allocating 20

    if (ptr == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }

    // Reset file pointer to beginning of file
    fseek(fptr, 0, SEEK_SET);

    // Get the elements of the array from the file
    for (i = 0; i < count; i++) {
        if (fscanf(fptr, "%f", &f) == 1) {
            ptr[i] = f;
        } else {
            printf("Error reading from file.\n");
            exit(0);
        }
    }

    // // Print the elements of the array
    // for (i = 0; i < count; i++) {
    //     printf("%f\n", ptr[i]);
    // }
    
    //Calculating Mean
    double mn;
    mn = mean(ptr,count);
    printf("\nMean : %f\n",mn); // printing mean

    //Calculating Median
    double med;
    med = median(ptr,count);
    printf("\nMedian : %f \n",med);

    //Calculating Mode
    printf("\nMode:\n");
    mode(ptr,count);
    
    //Calculating the Geometrice Mean
    double gm;
    gm = geometricMean(ptr,count);
    printf("\nGeometric Mean : %f \n",gm);

    //Calculating the Harmoic Mean
    double hm;
    hm = harmonicMean(ptr,count);
    printf("\nHarmonic Mean : %f \n",hm);

    //Calculating the Standard Deviation
    double stddev;
    stddev = standardDeviation(ptr,count,mn);
    printf("\nStandard Deviation : %f \n",stddev);

    //Calculating the Unused array capacity
    printf("\nUnused Array Capacity : %d \n", m-count);

    // Free dynamically allocated memory
    free(ptr);

    // Closing the file
    fclose(fptr);
}

int main() {
    char file[100];
    printf("Enter the name of the file you want to read: \n");
    scanf("%s", file);
    readFile(file);
    return 0;
}

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// When we call findNxtLoc it will return the tower location after 
// the one we are currently analyzing
int findNxtLoc(int * Arr, int start, int end) {
    int x = 0;
    for(x = start+1; x < end ; x++) {
        if(Arr[x] > 0) {
            return x;
        }
    }
    return -1;
}

// When we call findBackLoc it will return the tower location before the one we are currently analyzing
int findBackLoc(int * Arr, int start, int end) {
    int x = 0;
    for(x = start; x > end ; x--) {
        if(Arr[x] > 0) {
            return x;
        }
    }
    return -1;
}

// When we call sumOfArray_South it will return the addition of all widths 
double sumOfArray_South(int * Park, double * width, int L) {
    double sum = 0, diff = 0;

    for(int Loc = L;; Loc = findBackLoc(Park, diff, 0)) {
        if(Loc == -1) {break;}

        sum += width[Loc];
        diff = Loc - width[Loc];

        if(width[Loc] > Loc) {
            sum -= width[Loc];
            sum += Loc;
            sum -= fabs(diff);
            continue;
        }

        int startingLoc = Loc;
        Loc = findNxtLoc(Park, diff, Loc);

        while(Loc != -1) {
            if(width[Loc] > Loc) {
                sum += Loc;
                sum -= (Loc- diff);
            } else if(width[Loc] > (Loc-diff)){
                sum += width[Loc];
                sum -= (Loc- diff);
            } 

            Loc = findNxtLoc(Park, Loc, startingLoc);
        }
    }

    return sum;
}

// When we call sumOfArray_East it will return the addition of all widths 
double sumOfArray_East(int * Park, double * width, int L) {
    double sum = 0, diff = 0;
    int nxtLoc = 0;

    for(int Loc = 0; ; Loc = findNxtLoc(Park, Loc + width[Loc], L)) {

        if(Loc == -1) {break;}

        double farthestDiff = 0;
        int farthestLoc = 0;
        sum += width[Loc];

        if((Loc + width[Loc]) > L) {
            diff = L - diff;
        }

        nxtLoc = findNxtLoc(Park, nxtLoc, width[Loc] + Loc);
        while(nxtLoc != -1) {
            diff = (nxtLoc + width[nxtLoc]) - (width[Loc] + Loc);

            if((nxtLoc + width[nxtLoc]) > L) {
                diff = L - diff;
            }

            if(diff > farthestDiff) {
                farthestDiff = diff;
                farthestLoc = nxtLoc;
            }

            nxtLoc = findNxtLoc(Park, nxtLoc, width[Loc] + Loc);
        }

        if(farthestDiff > 0) {
            sum += width[farthestLoc];
            sum -= farthestDiff;
        }
    }

    return sum;
}



int main() {
    // First line inputs
    int N = 5, L = 100, P = 75;
    // Tower info inputs
    int x = 0, h = 0, lastX = 0;
    
    // // scan inputs for first line
    scanf("%d %d %d", &N, &L, &P);
    
    // Allocate memory
    int *Park = (int *)calloc(sizeof(int), L + 1);
    
    // Taking all the inputs in
    for(int a = 1; a <= N; a++) {
        scanf("%d %d", &x, &h);
        
        if(a == 0 && x != 0) {
            a--;
            continue;
        }
        
        if(a == N && x != L) {
            a--;
            continue;
        }
        
        if(x < lastX) {
            a--;
            continue;
        }
        
        Park[x] = h;
        lastX = x;
    }

    double ShadedArea = (double)P/100 * (double)L;
    double * width = (double *)calloc(sizeof(double), L+1);
    double currAngle = 0, startAngle = 1, endAngle = 89, sum = 0;
    double MostPrecisedVal = 0, leastDiff = MAXFLOAT, lastSum = 0;

    for(currAngle = (startAngle + endAngle) / 2; ; currAngle = (startAngle + endAngle) / 2) {
        for(int i = 1; i <= L; i++) {
            if(Park[i] != 0) {
                width[i] = (double) (Park[i]/tan(currAngle * (M_PI/180)));
            } else {
                width[i] = 0;
            }
        }

        sum = sumOfArray_South(Park, width, L);

        if((ShadedArea - sum > 0) && (ShadedArea - sum < leastDiff)) {
            leastDiff = ShadedArea - sum;
            MostPrecisedVal = currAngle;
        } else if(lastSum == sum) {
            break;
        }
        lastSum = sum;
        
        if(sum > ShadedArea) { // UPDATING ANGLES
            startAngle = currAngle;
        } else if(sum < ShadedArea) {
            endAngle = currAngle;
        }
    }

    printf("%.5f\n", MostPrecisedVal);

    width[L] = 0;
    currAngle = 0, startAngle = 91, endAngle = 179, sum = 0;
    MostPrecisedVal = 0, leastDiff = MAXFLOAT, lastSum = 0;

    for(currAngle = (startAngle + endAngle) / 2; ; currAngle = (startAngle + endAngle) / 2) {
        for(int i = 0; i < L; i++) {
            if(Park[i] != 0) {
                width[i] = (double) fabs((Park[i]/tan(currAngle * (M_PI/180))));
            } else {
                width[i] = 0;
            }
        }

        sum = sumOfArray_East(Park, width, L);

        if((ShadedArea - sum > 0) && (ShadedArea - sum < leastDiff)) {
            leastDiff = ShadedArea - sum;
            MostPrecisedVal = currAngle;
        } else if(lastSum == sum) {
            break;
        }
        lastSum = sum;
        
        if(sum < ShadedArea) { // UPDATING ANGLES
            startAngle = currAngle;
        } else if(sum > ShadedArea) {
            endAngle = currAngle;
        }
    }

    printf("%.5f\n", MostPrecisedVal);


}

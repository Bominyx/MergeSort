#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Merge(double* A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    int i,j,k;
    double *Links = malloc((n1+2)* sizeof(double));
    double *Rechts = malloc((n2+2)* sizeof(double));
    for (i = 1; i <= n1; ++i) {
        Links[i] = A[p + i - 1];
    }
    for (j = 1; j <= n2; j++) {
        Rechts[j] = A[q + j];
    }
    Links[n1 + 1] = 2;
    Rechts[n2 + 1] = 2;
    i = 1;
    j = 1;
    for (k = p; k <= r; k++) {
        if( Links[i] <= Rechts[j]){
            A[k] = Links[i];
            i = i + 1;
        }
        else {
            A[k] = Rechts[j];
            j = j + 1;
        }
    }
    free(Links);
    free(Rechts);
    return;
}

void Merge_Sort(double* A, int p, int r){
    int q;
    if (p<r){
        q = (p + r)/2;
        Merge_Sort(A, p, q);
        Merge_Sort(A, q + 1, r);
        Merge(A, p, q, r);
    }
    return;
}

void drucke_feld(double *a, int n) {
    int i;
    int start;
    if(n > 20){
        start = n -10;
    }else{
        n = 1;
    }
    printf("Feld beginnt:\n");
    for(i=start; i<=n; i++) {
        printf("Pos[%d] ist %.12lf\n", i, a[i]);
    }
    printf("Ende.\n");
}

//Erstellt gleichzeitig auch das Feld
double *fuelle_feld(int n) {
    int i;
    double *a=(double*) malloc((n+1)*sizeof(double));
    long m = 1 << 30;
    for(i=1; i<=n; i++) {
        long z1 = (rand() & 0x7FFF) << 15;
        long z2 = (rand() & 0x7FFF);
        long Z = z1 + z2; //Bessere Zufallszahlen
        a[i]=(double) Z/m;
    }
    return a;
}

int main() {
    for (int i = 1; i <= 10; ++i) {
        //Es wird Speicher in 5 Millionen Schritten reserviert, bis zu 50 Millionen 
        int size = 5000000 * i;
        double *array = malloc((size + 1) * sizeof(double));
        array = fuelle_feld(size);

/* Erst hier wird die Laufzeitmessung für den Merge Sort begonnen,
 * damit nicht die anderen Befehle mit gemessen werden.
 */
        clock_t begin = clock();
        Merge_Sort(array, 1, size);
        clock_t end = clock(); //Ende der Messung

        double time_spent = (double) (end - begin) / CLOCKS_PER_SEC; //Berechnung der Laufzeit von Merge Sort in Sekunden
        printf("%lf\n", time_spent);

        free(array);
    }
    getchar(); //Damit sich das Programm nicht direkt schließt ein getchar()
    return 0;
}

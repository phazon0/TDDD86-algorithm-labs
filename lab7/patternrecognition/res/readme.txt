/**********************************************************************
 *  M�nsterigenk�nning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga k�rtider i sekunder
 *  analys      n�r det k�nns vettigt att v�nta p� hela ber�kningen.
 *              Ge uppskattningar av k�rtiden i �vriga fall.
 *
 **********************************************************************/
    
      N       brute             sortering
 ----------------------------------------
    150       13ms              35ms
    200       41ms              49ms
    300       117ms             55ms
    400       274ms             91ms
    800       1945ms            223ms
   1600       14944ms           651ms
   3200       115931ms          2357ms
   6400       750000ms(Excel)   9730ms
  12800       6800000ms(Excel)  43067ms


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck f�r v�rstafallstiden f�r programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/
Motivering f�r uppskattningar: Vi satt in v�rderna i excel och gjorde en polynomial trendline med grad 4 och sedan anv�nde vi forcast funktionen f�r att f� ut v�rderna.


Brute: Algoritmen loopar igenom nestlade forloopar med djup 4 som g�r igenom alla element i listan d�rmed O(N^4)

Sortering: V�ran sorterar f�r varje element i listan s� n*n*log(n) d� std::sort �r n*log(n)

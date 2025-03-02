/**********************************************************************
 *  Mönsterigenkänning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga körtider i sekunder
 *  analys      när det känns vettigt att vänta på hela beräkningen.
 *              Ge uppskattningar av körtiden i övriga fall.
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
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/
Motivering för uppskattningar: Vi satt in värderna i excel och gjorde en polynomial trendline med grad 4 och sedan använde vi forcast funktionen för att få ut värderna.


Brute: Algoritmen loopar igenom nestlade forloopar med djup 4 som går igenom alla element i listan därmed O(N^4)

Sortering: Våran sorterar för varje element i listan så n*n*log(n) då std::sort är n*log(n)

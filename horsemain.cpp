#include "racing.hpp"
#include <cstdlib>

int main(int argc,char **argv)
{

   int number_of_horses=4; // an o xristis den eisagei girous kai aloga tote tha parei ws default ta 4 aloga kai tous 10 gurous
   int number_of_rounds=10;
   if(argc==3) // an o xristis kathws kanei compile eisagei ektos apo tin .exe balei kai 2 alla noymera tote to prwto tha ginoyn ta number of horses kai to deftero ta number of rounds
   {
      number_of_horses=atoi(argv[1]);
      number_of_rounds=atoi(argv[2]);
   }
   Racing rc(number_of_horses,number_of_rounds);
   rc.display_horses();
   rc.race(); //kalei kai ektelei tin sinartisi race
   rc.display_standings();
   return EXIT_SUCCESS;
}
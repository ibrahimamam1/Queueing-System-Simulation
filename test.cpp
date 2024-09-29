#include "init.hpp"
#include <cstdio>

void testEvents(int n , _EVENT* events) {
  
  for(int i=0; i<n; i++){
    printf(" %d \t\t %lf \t\t %d\n" , i , events[i].time , events[i].type);
  }
}

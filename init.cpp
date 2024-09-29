#include "init.hpp"
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <random>
#include <vector>

void initServer(_SERVER* s) {

  s->state = UP;
  s->serving_status = 0;
}

void initQueue(_SERVER_QUEUE* sq) {
  sq->count = 0;
  sq->new_arrival = false;
}

/*generate an ordered list of random numbers
* using a random_device and the mt_twister
* the distribution is uniform
*/

std::vector<double>generate_random_ordered_numbers(int n , double min_value , double max_value){
  
  std::vector<double>numbers;
  numbers.reserve(n);

  //seed the generator using a random variable
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_real_distribution<>dist(0.0 , 1.0);
  double sum = 0.0;

  for(int i= 0; i < n; i++){
    double r = dist(gen);
    sum += r;
    numbers.push_back(sum);
  }

  for(double& num : numbers) {
    num /= sum;
  }

  // Scale the numbers to be between min_value and max_value
    for (double& num : numbers) {
        num = min_value + num * (max_value - min_value);
    }

    return numbers;

}

/* creates list of events 
* first gets a list of random numbers
* assign them to events and assigns the type of event base on the arrival probability
* arrival probability should be between 0 and 1
*/

_EVENT* initEvents(int n , double departure_probability) {
  int count_arrival = 0;
  int count_departure = 0;
  std::vector<double> random_numbers = generate_random_ordered_numbers(n, 0.0, 1000);
  
  _EVENT* events = (_EVENT*) malloc(n * sizeof(_EVENT));

  for(int i=0; i<n;i++){
    //assign time
    events[i].time = random_numbers[i];

    //assign type;
    
    auto now = std::chrono::system_clock::now();
    auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
    srand(nanos);
    double random_choice = (double)rand() / RAND_MAX; 

    printf("random choice: %lf\n" , random_choice);
    
   
    if(random_choice < departure_probability && count_arrival > count_departure){
      events[i].type = DEPARTURE;
      count_departure++;
    } 
    else{
      events[i].type = ARRIVAL;
      count_arrival++;
    }

  }
  return events;  
}

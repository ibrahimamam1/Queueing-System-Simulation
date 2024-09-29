#ifndef IMPORT_HPP
#define IMPORT_HPP

/* Server
  * The server has a state which can be up or down
  * Up Means the server is working , down means it can service anyone until repaire
  * The server has a serving_status which can be 1 or 0
  */
#include <queue>
enum serverState{DOWN , UP};
enum eventType{ARRIVAL , DEPARTURE};

typedef struct event{

  eventType type; //the type of the event
  double time; //time at which event occurs
}_EVENT;

typedef struct server {
  
  serverState state; //can be up or down 
  int serving_status; // 0 means not serving , 1 means serving someone

}_SERVER;

typedef struct server_queue{
  int count; //Number of people in the queue
  bool new_arrival; //true if a new item that is yet yo be processed is in queue
  std::queue<int>arrival_times;

}_SERVER_QUEUE;


void initServer(_SERVER* s); // initialises n servers
_EVENT* initEvents(int n , double arrival_probability); //creates arrival and departure events
void initQueue(_SERVER_QUEUE* q); //initialises the server queue
void timingRoutine(); //picks next event and update all variables
void reportGenerator(); //Generates a report of the simulation


#endif // !IMPORT_HPP
#define IMPORT_HPP

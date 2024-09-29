#include "init.hpp"
#include <raylib.h>

void eventSelector( double& system_clock ,int& index ,  _EVENT* events , _SERVER& server , _SERVER_QUEUE& sq) {

  _EVENT current_event = events[index];
  
  if(current_event.type == ARRIVAL) {
    if(server.state == UP) {
      
      //server is free and no one is using it;
      if(server.serving_status == 0) {
        server.serving_status = 1;
      }
      else{
        sq.new_arrival = true;
        sq.count++;
        sq.arrival_times.push(current_event.time);
      }//server is not free so we push to the queue
    }
  }
  else if(current_event.type == DEPARTURE) {
    
  }

  system_clock = events[index].time;
  index++;

}

void launch_arrival_animation(int lastx , int radius ,Color color){
  
  double posx = 20 , posy = 400;
  double speed = 5;
  while (posx < lastx ) {
    DrawCircle(posx, posy, radius, color);
    posx += speed;
  }
}



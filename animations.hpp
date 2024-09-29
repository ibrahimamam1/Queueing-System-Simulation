#include <cmath>
#include <vector>
struct animation_state{
  
  float startx ,starty , endx , endy;
  float currentx , currenty;
  float speed;
  bool isActive;
};

std::vector<animation_state>animations;
void startArrivalAnimation(float startx , float starty , float endx , float endy , float speed){

  animation_state newAnimation = {startx , starty , endx , endy,speed,true};

  animations.push_back(newAnimation);

}

void updateAndDrawAnimations(float radius , Color color) {
  for(auto& anim : animations) {
    if(anim.isActive) {
      //update postition
      float dx = anim.endx - anim.currentx;
      float dy = anim.endy - anim.currenty;
      float distance = sqrt( (dx*dx) + (dy*dy) );

      //incomplete
    }
  }
}


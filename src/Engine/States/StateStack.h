#ifndef STATESTACK_H
#define STATESTACK_H


#include <vector>


struct state
{
  int state;
};
typedef struct state state;


class StateStack
{
  public:
    StateStack();

    void init();
    void Update();  // Updates the state at the end of the states vector (top of the stack)
    void Render();  // Render all of the states (maybe unecessary for all?)
    void processAI();  // Won't really need this...
    void clear();
    void push(state s);
    void pop();

  private:
    std::vector<int> states;
};


#endif
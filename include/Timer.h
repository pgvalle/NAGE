#ifndef INCLUDE_TIMER
#define INCLUDE_TIMER

class Timer
{
private:
  float elapsed = 0, timeout = 0;

public:
  bool hasTimedOut() const
  {
    return timeout <= elapsed;
  }

  void update(float delta);
  void reset(float newTimeout = 0);
};

#endif /* INCLUDE_TIMER */

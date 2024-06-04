#include "NAGE.h"

using namespace NAGE;

float timeSeconds()
{
  return 1e-3f * SDL_GetTicks();
}

void Timer::update()
{
  float current, delta;
  current = timeSeconds();
  delta = current - last;

  // not to keep summing elapsed 
  if (elapsed < timeout)
  {
    elapsed += delta;
  }

  last = current;
  return delta;
}

void Timer::reset(float newTimeout)
{
  if (newTimeout)
  {
    timeout = newTimeout;
  }

  elapsed = 0;
  last = timeSeconds();
}

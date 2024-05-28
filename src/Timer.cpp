#include "NAGE.h"

using namespace NAGE;

void Timer::update(float delta)
{
  if (elapsed < timeout)
  {
    elapsed += delta;
  }
}

void Timer::reset(float newTimeout)
{
  elapsed = 0;
  if (newTimeout)
  {
    timeout = newTimeout;
  }
}

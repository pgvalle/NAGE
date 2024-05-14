#include "App.h"

#include <cstdlib>

bool App::pushUserEvent(int code, void *data, size_t dataLen)
{
  SDL_UserEvent event;
  event.type = SDL_USEREVENT;
  event.code = code;

  if (data && dataLen > 0)
  {
    void *copy = malloc(dataLen);
    event.data1 = memcpy(copy, data, dataLen);
  }

  return (bool)SDL_PushEvent((SDL_Event *)&event);
}

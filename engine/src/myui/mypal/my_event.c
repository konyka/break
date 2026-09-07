/**
 * @file my_event.c
 * @brief Cleanup for event payloads with explicit ownership.
 */
#include "mypal/my_event.h"

void my_event_release_payload(my_event_t* event) {
  if (event == NULL || event->type != MY_EVENT_COMMAND ||
      event->u.command.destroy == NULL) {
    return;
  }
  event->u.command.destroy(event->u.command.data);
  event->u.command.data = NULL;
  event->u.command.destroy = NULL;
}

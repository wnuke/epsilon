#include "helpers.h"
#include <ion.h>
extern "C" {
#include "mphalport.h"
}

bool micropython_port_vm_hook_loop() {
  /* This function is called very frequently by the MicroPython engine. We grab
   * this opportunity to interrupt execution and/or refresh the display on
   * platforms that need it. */

  /* Doing too many things here slows down Python execution quite a lot. So we
   * only do things once in a while and return as soon as possible otherwise. */
  static int c = 0;

  c = (c + 1) % 20000;
  if (c != 0) {
    return false;
  }

  // Check if the user asked for an interruption from the keyboard
  return micropython_port_interrupt_if_needed();
}

bool micropython_port_interruptible_msleep(uint32_t delay) {
  uint32_t start = Ion::Timing::millis();
  uint32_t timeSpent = 0;
  while (timeSpent < delay) {
    /* SysTick drifts at each frequency change, so we try not to change the
     * frequency to often -> we look for interruptions every 100 ms. */
    constexpr uint32_t millisPerSleep = 100;
    bool lastLoop = millisPerSleep > delay - timeSpent;
    Ion::Timing::msleep(lastLoop ? delay - timeSpent : millisPerSleep);
    if (!lastLoop && micropython_port_interrupt_if_needed()) {
      return true;
    }
    uint64_t currentMillis = Ion::Timing::millis();
    timeSpent = currentMillis > start ? currentMillis - start : UINT64_MAX - start + currentMillis;
  }
  return false;
}

bool micropython_port_interrupt_if_needed() {
  Ion::Keyboard::State scan = Ion::Keyboard::scan();
  Ion::Keyboard::Key interruptKey = static_cast<Ion::Keyboard::Key>(mp_interrupt_char);
  if (scan.keyDown(interruptKey)) {
    mp_keyboard_interrupt();
    return true;
  }
  return false;
}

int micropython_port_random() {
  return Ion::random();
}

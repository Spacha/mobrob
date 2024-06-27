#ifndef __MOCKS_H__
#define __MOCKS_H__

#include <assert.h>     // gives assert
#include <chrono>       // for sleep
#include <thread>       // for sleep

///////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////

// Pin modes
#define INPUT       0
#define OUTPUT      1

// Digital write states
#define LOW         0
#define HIGH        1

#define PI          3.14159265359

///////////////////////////////////////////////////////////
// Mock state
///////////////////////////////////////////////////////////

typedef struct
{
    int pin_states[16] = {0};
    int pin_pulses[16] = {0};
} mock_state;

mock_state g_mock_state;

///////////////////////////////////////////////////////////
// Support functions
///////////////////////////////////////////////////////////

void reset_mocks()
{
    for (int i = 0; i < 16; i++) { g_mock_state.pin_states[i] = 0; }
    for (int i = 0; i < 16; i++) { g_mock_state.pin_pulses[i] = 0; }
}

bool test_pin(int pin, int expected_state)
{
    return g_mock_state.pin_states[pin] == expected_state;
}

///////////////////////////////////////////////////////////
// Mock functions
///////////////////////////////////////////////////////////

void digitalWrite(int pin, int state)
{
    //printf("Digital write: %d\n", state);
    g_mock_state.pin_states[pin] = state;
}

void analogWrite(int pin, int value)
{
    //printf("Analog write: %d\n", value);
    g_mock_state.pin_states[pin] = value;
}

// NOTE: This is for testing only
void test_set_pulse_width(int pin, int us)
{
    g_mock_state.pin_pulses[pin] = us;
}

int pulseIn(int pin, int value)
{
    (void)value;
    return g_mock_state.pin_pulses[pin];
}

void delay(int ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void delayMicroseconds(int us)
{
    std::this_thread::sleep_for(std::chrono::microseconds(us));
}

#endif /* __MOCKS_H__ */

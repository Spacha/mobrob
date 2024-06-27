#include "test.h"
#include "mocks.h"

// Test targets
#include "../Drive.h"
#include "../sensors/UltrasonicSensor.h"

int main(int argc, char **argv)
{
    printf("+------------------------------------+\n");
    printf("|         MOBROB TEST RUNNER         |\n");
    printf("+------------------------------------+\n\n");

    ///////////////////////////////////////////////////////
    print_test_section("Motor tests");
    reset_mocks();
    ///////////////////////////////////////////////////////

    Motor motor(1, 2, 3);

    print_test_subsection("Motor forward (speed 0.0)");
    motor.drive_forward(0.0);
    TEST(test_pin(1, LOW), "Pin 1 state");
    TEST(test_pin(2, HIGH), "Pin 2 state");
    TEST(test_pin(3, 0), "Pin 3 state");

    print_test_subsection("Motor forward (speed 0.5)");
    motor.drive_forward(0.5);
    TEST(test_pin(1, LOW), "Pin 1 state");
    TEST(test_pin(2, HIGH), "Pin 2 state");
    TEST(test_pin(3, 90), "Pin 3 state");

    print_test_subsection("Motor forward (speed 1.0)");
    motor.drive_forward(1.0);
    TEST(test_pin(1, LOW), "Pin 1 state");
    TEST(test_pin(2, HIGH), "Pin 2 state");
    TEST(test_pin(3, 180), "Pin 3 state");


    print_test_subsection("Motor backward (speed 0.0)");
    motor.drive_backward(0.0);
    TEST(test_pin(1, HIGH), "Pin 1 state");
    TEST(test_pin(2, LOW), "Pin 2 state");
    TEST(test_pin(3, 0), "Pin 3 state");

    print_test_subsection("Motor backward (speed 0.5)");
    motor.drive_backward(0.5);
    TEST(test_pin(1, HIGH), "Pin 1 state");
    TEST(test_pin(2, LOW), "Pin 2 state");
    TEST(test_pin(3, 90), "Pin 3 state");

    print_test_subsection("Motor backward (speed 1.0)");
    motor.drive_backward(1.0);
    TEST(test_pin(1, HIGH), "Pin 1 state");
    TEST(test_pin(2, LOW), "Pin 2 state");
    TEST(test_pin(3, 180), "Pin 3 state");

    print_test_subsection("Motor stop");
    motor.drive_forward(1.0);
    motor.stop();
    TEST(test_pin(1, HIGH), "Pin 1 state");
    TEST(test_pin(2, HIGH), "Pin 2 state");
    TEST(test_pin(3, 0), "Pin 3 state");

    print_test_subsection("Motor stop with brake");
    motor.drive_forward(1.0);
    motor.stop(true);
    TEST(test_pin(1, HIGH), "Pin 1 state");
    TEST(test_pin(2, HIGH), "Pin 2 state");
    TEST(test_pin(3, 255), "Pin 3 state");

    ///////////////////////////////////////////////////////
    print_test_section("Drive tests");
    reset_mocks();
    ///////////////////////////////////////////////////////

    Drive drive(1, 2, 3, 4, 5, 6);

    print_test_subsection("Not moving");
    drive.control(0.0, 0.0);
    TEST(test_pin(1, HIGH), "Pin 1 state");
    TEST(test_pin(2, HIGH), "Pin 2 state");
    TEST(test_pin(3, 0), "Pin 3 state");
    TEST(test_pin(4, HIGH), "Pin 4 state");
    TEST(test_pin(5, HIGH), "Pin 5 state");
    TEST(test_pin(6, 0), "Pin 6 state");

    print_test_subsection("Moving forward fast");
    drive.control(1.0, 1.0);
    TEST(test_pin(1, LOW), "Pin 1 state");
    TEST(test_pin(2, HIGH), "Pin 2 state");
    TEST(test_pin(3, 180), "Pin 3 state");
    TEST(test_pin(4, LOW), "Pin 4 state");
    TEST(test_pin(5, HIGH), "Pin 5 state");
    TEST(test_pin(6, 180), "Pin 6 state");

    print_test_subsection("Moving forward slow");
    drive.control(0.5, 0.5);
    TEST(test_pin(1, LOW), "Pin 1 state");
    TEST(test_pin(2, HIGH), "Pin 2 state");
    TEST(test_pin(3, 90), "Pin 3 state");
    TEST(test_pin(4, LOW), "Pin 4 state");
    TEST(test_pin(5, HIGH), "Pin 5 state");
    TEST(test_pin(6, 90), "Pin 6 state");

    print_test_subsection("Moving backward slow");
    drive.control(-0.5, -0.5);
    TEST(test_pin(1, HIGH), "Pin 1 state");
    TEST(test_pin(2, LOW), "Pin 2 state");
    TEST(test_pin(3, 90), "Pin 3 state");
    TEST(test_pin(4, HIGH), "Pin 4 state");
    TEST(test_pin(5, LOW), "Pin 5 state");
    TEST(test_pin(6, 90), "Pin 6 state");

    print_test_subsection("Turning left in place");
    drive.control(-1.0, 1.0);
    TEST(test_pin(1, HIGH), "Pin 1 state");
    TEST(test_pin(2, LOW), "Pin 2 state");
    TEST(test_pin(3, 180), "Pin 3 state");
    TEST(test_pin(4, LOW), "Pin 4 state");
    TEST(test_pin(5, HIGH), "Pin 5 state");
    TEST(test_pin(6, 180), "Pin 6 state");

    print_test_subsection("Turning right in place");
    drive.control(1.0, -1.0);
    TEST(test_pin(1, LOW), "Pin 1 state");
    TEST(test_pin(2, HIGH), "Pin 2 state");
    TEST(test_pin(3, 180), "Pin 3 state");
    TEST(test_pin(4, HIGH), "Pin 4 state");
    TEST(test_pin(5, LOW), "Pin 5 state");
    TEST(test_pin(6, 180), "Pin 6 state");

    ///////////////////////////////////////////////////////
    print_test_section("Ultrasonic sensor tests");
    reset_mocks();
    ///////////////////////////////////////////////////////

    UltrasonicSensor ut_sensor();

    // 58 us   -> 1.0 cm
    // 580 us  -> 10.0 cm
    // 1160 us -> 20.0 cm
    // 2900 us -> 50.0 cm

    print_test_subsection("Measuring very long distance");

    test_setPulseWidth(1, 10);

    //drive.control(1.0, -1.0);
    TEST(test_pin(1, LOW), "Pin 1 state");

    ///////////////////////////////////////////////////////

    print_separator();
    printf("[OK] All tests passed.\n");
    print_separator();
    reset_mocks();

    return 0;
}

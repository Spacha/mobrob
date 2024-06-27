#include "test.h"
#include "mocks.h"

// Test targets
#include "../Drive.h"
#include "../sensors/UltrasonicSensor.h"
#include "../sensors/IMUSensor.h"

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

    UltrasonicSensor ut_sensor(1, 2);

    // 58 us   -> 1.0 cm
    // 580 us  -> 10.0 cm
    // 1160 us -> 20.0 cm
    // 2900 us -> 50.0 cm
    float distance;

    print_test_subsection("Measuring long distance");
    test_set_pulse_width(2, 2900);    // set 2900 us pulse in echo pin -> 50.0 cm
    distance = ut_sensor.measure_distance();
    TEST(49.0 < distance && distance < 51.0, "Distance value");

    print_test_subsection("Measuring medium distance");
    test_set_pulse_width(2, 580);    // set 580 us pulse in echo pin -> 10.0 cm
    distance = ut_sensor.measure_distance();
    TEST(9.5 < distance && distance < 10.5, "Distance value");

    print_test_subsection("Measuring short distance");
    test_set_pulse_width(2, 58);    // set 58 us pulse in echo pin -> 1.0 cm
    distance = ut_sensor.measure_distance();
    TEST(0.8 < distance && distance < 1.2, "Distance value");

    ///////////////////////////////////////////////////////
    print_test_section("IMU sensor tests");
    reset_mocks();
    ///////////////////////////////////////////////////////

    IMUSensor imu_sensor(1, 2);
    imu_sensor.setup();

    // acceleration.x = 1.2;
    // acceleration.y = -1.0;
    // acceleration.z = 0.0;
    // -> pitch = -atan2(-1.0, sqrt(1.2 * 1.2 + 0.0 * 0.0)) * 180.0 / PI = 39.8055710922652
    // -> roll = -atan2(0.0, sqrt(1.2 * 1.2 + -1.0 * -1.0)) * 180.0 / PI = 0.0
    // temperature = 20.2;
    imu_data_t data;
    imu_sensor.measure_all(&data);

    print_test_subsection("Measuring temperature");
    TEST(TEMP_CALIBRATED(20.1) < data.temperature && data.temperature < TEMP_CALIBRATED(20.3), "Temp value");

    print_test_subsection("Measuring pitch");
    TEST(PITCH_CALIBRATED(38.0) < data.pitch && data.pitch < PITCH_CALIBRATED(40.0), "Pitch value");

    print_test_subsection("Measuring roll");
    TEST(ROLL_CALIBRATED(-0.1) < data.roll && data.roll < ROLL_CALIBRATED(0.1), "Roll value");

    ///////////////////////////////////////////////////////

    print_separator();
    printf("[OK] (%d / %d) tests passed.\n", num_tests(), num_tests());
    print_separator();
    reset_mocks();

    return 0;
}

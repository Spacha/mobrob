#include <iostream>

int g_fake_current_millis = 0;

int millis() {
    return g_fake_current_millis;
}

class TimedTask {
    int m_interval;
    int m_last_update;

public:
    TimedTask(int interval) {
        m_interval = interval;
        m_last_update = 0;
    }

    void update() {
        int current_millis = millis();
        int delta = current_millis - m_last_update;

        if (delta >= m_interval) {
            runTask(delta);
            m_last_update = current_millis;
        }
    }

    virtual void runTask(int delta) = 0;
};

class MeasurementTask : public TimedTask {
public:
    MeasurementTask(int interval) : TimedTask(interval) {};

    void runTask(int delta) {
        std::cout << "runTask was called with delta: " << delta
                  << ". Current millis: " << millis() << std::endl;
    }
};


int main(int argc, char *argv[]) {
    MeasurementTask measurement_task(1000);

    while (1) {
        measurement_task.update();

        g_fake_current_millis++;
    }
}

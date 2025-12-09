#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

// Matt C CSI 370 Final Project
// Simulate input that could come from a USB sensor
// Or an online API
// (In reality, I will likely tie it in to my HomeAssistant and build an ESP32 temp sensor w/ a battery to talk to the motor controller)

int main() {
    int fd = open("/dev/ttyUSB0", O_WRONLY);  // Change to your port
    
    struct termios tty;
    tcgetattr(fd, &tty);
    cfsetospeed(&tty, B9600);
    tcsetattr(fd, TCSANOW, &tty);
    
    std::cout << "Temperature Controller" << std::endl;
    
    float temp;
    while (true) {
        std::cout << "Temp: ";
        std::cin >> temp;
        
        std::string message = "TEMP:" + std::to_string(temp) + "\n";
        write(fd, message.c_str(), message.length());
        
        std::cout << "Sent: " << message;
        if (temp > 75.0) {
            std::cout << "Expect window to open, it's hot.";
        } else if (temp < 60.0) {
            std::cout << "Expect window to close, it's cold.";
        } else {
            std::cout << "No action; comfortable temperature.";
        }
        std::cout << "\n";
    }
    
    close(fd);
    return 0;
}
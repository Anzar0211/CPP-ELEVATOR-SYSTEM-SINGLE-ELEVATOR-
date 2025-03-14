

#include <iostream>
#include <queue>
#include <set>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

class Elevator
{
private:
    int currentFloor;
    bool isMoving;
    bool isStopButtonPressed;
    bool isDoorOpen;
    bool iskeepDoorOpenButtonPressed;
    bool isDoorCloseButtonPressed;
    bool isAlarmButtonPressed;
    queue<int> requestQueue;
    set<int> requestSet;

public:
    Elevator()
    {
        currentFloor = 0;
        isMoving = false;
        isStopButtonPressed = false;
        isAlarmButtonPressed = false;
        isDoorOpen = false;
        iskeepDoorOpenButtonPressed = false;
        isDoorCloseButtonPressed = false;
    }

    void requestFloor(int floor)
    {
        if (floor < -1 || floor > 4)
        { // Fixed condition to allow valid floors
            cout << "Invalid floor request" << endl;
            return;
        }
        if (requestSet.find(floor) == requestSet.end())
        {
            requestQueue.push(floor);
            requestSet.insert(floor);
            cout << "Floor " << floor << " Requested" << endl;
        }
        else
        {
            cout << "Floor " << floor << " already requested" << endl;
        }
    }

    void callElevator(int floor)
    {
        if (floor < -1 || floor > 4)
        {
            cout << "Invalid floor request" << endl;
            return;
        }
        requestFloor(floor);
        cout << "Elevator called at floor " << floor << endl;
    }

    void stopElevator()
    {
        isStopButtonPressed = true;
        isMoving = false;
        cout << "Emergency Stop Button pressed. Elevator halted at floor " << currentFloor << endl;
    }

    void resetStop()
    {
        isStopButtonPressed = false;
        cout << "Emergency Stop Button reset" << endl;
    }

    void ringBell()
    {
        cout << "Alarm Bell Ringing" << endl;
    }

    void keepDoorOpen(bool status)
    {
        iskeepDoorOpenButtonPressed = status;
        if (status)
        {
            cout << "Door will be kept open" << endl;
            isDoorOpen = true; // Ensure door stays open
        }
        else
        {
            cout << "Door will be closed after 3 seconds" << endl;
            sleep_for(seconds(3));
            closeDoor();
        }
    }

    void openDoor()
    {
        if (isDoorOpen)
            return;
        if (isDoorCloseButtonPressed)
        {
            cout << "Door close button is pressed, cannot open now" << endl;
            return;
        }
        isDoorOpen = true;
        cout << "Door Opened" << endl;
    }

    void closeDoor()
    {
        if (!isDoorOpen)
            return;
        if (iskeepDoorOpenButtonPressed)
        {
            cout << "Door will remain open as per request" << endl;
            return;
        }
        isDoorOpen = false;
        cout << "Elevator Door Closed" << endl;
    }

    void doorSensorActivated()
    {
        if (isDoorOpen)
        {
            cout << "Door Sensor Activated..OBSTRUCTION DETECTED!! Keeping door open." << endl;
            keepDoorOpen(true);
        }
    }

    void displayStatus()
    {
        cout << "\n==== Elevator Status ====" << endl;
        cout << "Current Floor: " << currentFloor << endl;
        cout << "Elevator is Moving: " << (isMoving ? "Yes" : "No") << endl;
        cout << "Door Open: " << (isDoorOpen ? "Yes" : "No") << endl;
        cout << "Stop Button Pressed: " << (isStopButtonPressed ? "Yes" : "No") << endl;
        cout << "Alarm Button Pressed: " << (isAlarmButtonPressed ? "Yes" : "No") << endl;
        cout << "Keep Door Open Button Pressed: " << (iskeepDoorOpenButtonPressed ? "Yes" : "No") << endl;
        cout << "==========================\n"
             << endl;
    }

    void moveElevator()
    {
        while (!requestQueue.empty())
        {
            if (isStopButtonPressed)
            {
                cout << "Emergency stop button pressed, elevator halted." << endl;
                return;
            }
            int nextFloor = requestQueue.front();
            requestQueue.pop();
            requestSet.erase(nextFloor);
            cout << "Moving from floor " << currentFloor << " to floor " << nextFloor << endl;
            isMoving = true;

            while (currentFloor != nextFloor)
            {
                sleep_for(seconds(1));
                if (currentFloor < nextFloor)
                {
                    currentFloor++;
                }
                else
                {
                    currentFloor--;
                }
                cout << "Elevator at " << currentFloor << endl;
            }
            isMoving = false;
            openDoor();
            if (!iskeepDoorOpenButtonPressed)
            {
                sleep_for(seconds(3));
                closeDoor();
            }
        }
    }
};

int main()
{
    Elevator elevator;
    int choice, floor;

    while (true)
    {
        cout << "\nElevator System Menu" << endl;
        cout << "1. Request Floor from inside the Elevator" << endl;
        cout << "2. Call Elevator from outside the Elevator" << endl;
        cout << "3. Move Elevator" << endl;
        cout << "4. Activate Stop" << endl;
        cout << "5. Reset Stop" << endl;
        cout << "6. Ring Alarm Bell" << endl;
        cout << "7. Keep Door Open" << endl;
        cout << "8. Close Door" << endl;
        cout << "9. Door Sensor Activated" << endl;
        cout << "10. Display Status" << endl;
        cout << "11. Exit" << endl;
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        { // Handle invalid input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number." << endl;
            continue;
        }

        switch (choice)
        {
        case 1:
            cout << "Enter floor number (-1 to 4): ";
            if (!(cin >> floor))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a valid floor number." << endl;
                break;
            }
            elevator.requestFloor(floor);
            break;
        case 2:
            cout << "Enter calling floor number (-1 to 4): ";
            if (!(cin >> floor))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a valid floor number." << endl;
                break;
            }
            elevator.callElevator(floor);
            break;
        case 3:
            elevator.moveElevator();
            break;
        case 4:
            elevator.stopElevator();
            break;
        case 5:
            elevator.resetStop();
            break;
        case 6:
            elevator.ringBell();
            break;
        case 7:
            elevator.keepDoorOpen(true);
            break;
        case 8:
            elevator.closeDoor();
            break;
        case 9:
            elevator.doorSensorActivated();
            break;
        case 10:
            elevator.displayStatus();
            break;
        case 11:
            cout << "Exiting Elevator System..." << endl;
            return 0;
        default:
            cout << "Invalid choice, please try again." << endl;
        }
    }
}

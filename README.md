# Elevator Simulation System

## Overview
This is a C++ console-based Elevator Simulation System that models the behavior of an elevator. It allows users to request floors, call the elevator, control doors, activate emergency stops, and view the system's status.

## Features
- Request a floor from inside the elevator
- Call the elevator from outside
- Move the elevator between floors
- Activate and reset emergency stops
- Ring an alarm bell
- Keep doors open or close them manually
- Detect obstructions using a door sensor
- Display current elevator status

## Usage Instructions
### Compilation
To compile the program, use the following command:
```sh
 g++ elevator.cpp -o elevator -pthread
```
### Running the Program
Run the compiled executable:
```sh
./elevator
```

## Floor Constraints
The elevator operates between floors **-1 to 4**. Invalid floor requests are rejected.

## Menu Options
```
1. Request Floor from inside the Elevator
2. Call Elevator from outside the Elevator
3. Move Elevator
4. Activate Stop
5. Reset Stop
6. Ring Alarm Bell
7. Keep Door Open
8. Close Door
9. Door Sensor Activated
10. Display Status
11. Exit
```

## Sample Run Output
```
Elevator System Menu
1. Request Floor from inside the Elevator
2. Call Elevator from outside the Elevator
3. Move Elevator
4. Activate Stop
5. Reset Stop
6. Ring Alarm Bell
7. Keep Door Open
8. Close Door
9. Door Sensor Activated
10. Display Status
11. Exit
Enter your choice: 1
Enter floor number: 3
Floor 3 Requested

Enter your choice: 3
Moving from floor 0 to floor 3
Elevator at 1
Elevator at 2
Elevator at 3
Door Opened
Door will be closed after 3 seconds
Elevator Door Closed
```

## Error Handling
- Prevents duplicate floor requests
- Detects invalid floor selections
- Handles emergency stop scenarios
- Simulates door obstruction handling

## Future Enhancements
- Add a graphical user interface (GUI)
- Improve multi-threading for concurrent requests
- Implement an AI-based request optimization system

## License
This project is open-source and available for modification and distribution.


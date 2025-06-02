# TRAIN_TICKET_BOOKING
Train Ticket Booking System 🚂
Welcome to the Train Ticket Booking System, a robust C-based console application inspired by ConfirmTkt! This project simulates a railway reservation system with features like user authentication, ticket booking, cancellation, PNR status checking, and employee-restricted passenger details access. Whether you're a developer looking to explore a modular C project or a railway enthusiast, this system offers a glimpse into the mechanics of online ticket booking.
✨ Features

User Management:

Register and log in with secure credentials stored in users.txt.
Supports up to 100 users.


Ticket Booking:

Book tickets for General or Tatkal quotas, with a maximum of 4 passengers for Tatkal (IRCTC-compliant).
Generates unique PNRs for each booking.
Checks seat availability and supports waitlist bookings with a simplified prediction model.


Cancellation & Refunds:

Cancel tickets with refund logic: full refund for waitlisted tickets, partial for confirmed tickets.
Simulates Ticket Deposit Receipt (TDR) filing for cancellations.


PNR Status & Waitlist Prediction:

Check PNR status to view ticket details (train, passengers, quota, status).
Predicts waitlist confirmation chances based on seat availability.


Train Schedule:

View available trains, their names, and seat availability (up to 50 trains).


Employee Access:

Restricted mode for railway employees (login: railway, password: admin123) to view passenger details by PNR.
Ensures sensitive data access is secure.


Logging:

General event logs in logs.txt for all bookings and cancellations.
Detailed per-booking logs in PNR<PNR>.txt files (e.g., PNR123456789.txt) for traceability.


ConfirmTkt-Inspired Features:

Tatkal booking restrictions.
Free cancellation for waitlisted tickets.
Modular design for easy extension (e.g., add passenger names or alternate trains).



📂 Project Structure
train-ticket-booking/
├── main.c           # Entry point with user menu
├── user.h           # User management header
├── user.c           # User registration and login logic
├── train.h          # Train data header
├── train.c          # Train schedule and seat management
├── ticket.h         # Ticket operations header
├── ticket.c         # Booking, cancellation, PNR status, and passenger details
├── logger.h         # Logging header
├── logger.c         # General and PNR-specific logging
├── utils.h          # Utility functions header
├── utils.c          # PNR generation and other utilities
├── users.txt        # Stores user credentials
├── trains.txt       # Stores train data
├── tickets.txt      # Stores ticket data
├── logs.txt         # General event logs
├── PNR<PNR>.txt     # Individual booking logs (generated dynamically)
└── README.md        # This file

🛠️ Setup Instructions
Prerequisites

Compiler: GCC or any C compiler (e.g., MinGW for Windows, clang for macOS).
Operating System: Linux, macOS, or Windows (with a compatible compiler).
Disk Space: Ensure write permissions in the project directory for file operations.

Compilation

Clone the repository:git clone https://github.com/<your-username>/train-ticket-booking.git
cd train-ticket-booking


Compile the code:gcc -o train_booking main.c user.c train.c ticket.c logger.c utils.c



Running the Program

Execute the compiled binary:./train_booking


Follow the interactive menu to:
Register/login as a user.
Book or cancel tickets.
Check PNR status or train schedules.
Log in as a railway employee (railway/admin123) to view passenger details.



File Outputs

users.txt: Stores usernames and passwords.
trains.txt: Initializes with a sample train (Train No: 12345, Express, 100 seats).
tickets.txt: Stores ticket details (PNR, username, train, passengers, quota, status).
logs.txt: Logs all events with timestamps.
PNR<PNR>.txt: Created for each booking with detailed information.

🚀 Usage

Register & Login:

Choose option 1 to register (e.g., username: testuser, password: test123).
Choose option 2 to log in.


Book a Ticket:

Select option 3, enter train number (e.g., 12345), number of passengers (1–4 for Tatkal), and quota (General/Tatkal).
Receive a PNR and check PNR<PNR>.txt for booking details.


Cancel a Ticket:

Select option 4, enter the PNR, and confirm cancellation (full refund for waitlisted tickets).


Check PNR Status:

Select option 5, enter the PNR to view ticket details and waitlist prediction.


View Train Schedule:

Select option 6 to see available trains and seats.


Railway Employee Access:

Select option 7, log in with railway/admin123, and enter a PNR to view ticket and passenger details.



🎯 Example Run
=== Train Ticket Booking System ===
1. Register
2. Login
3. Book Ticket
4. Cancel Ticket
5. Check PNR Status
6. View Train Schedule
7. Railway Employee Login
8. Exit
Enter choice: 2
Enter username: testuser
Enter password: test123
Login successful!

=== Train Ticket Booking System ===
Enter choice: 3
Enter train number: 12345
Enter number of passengers (max 4 for Tatkal): 2
Enter quota (General/Tatkal): General
Booking confirmed! PNR: 123456789

=== Train Ticket Booking System ===
Enter choice: 7
Enter employee username: railway
Enter employee password: admin123
Employee login successful!
Enter PNR number to view passengers: 123456789
PNR: 123456789, Train: 12345, Number of Passengers: 2, Quota: General, Status: Confirmed
Passenger Details: [Simulated - 2 passengers booked]

🔧 Extensibility

Add Passenger Names: Modify the Ticket struct to include an array or linked list for passenger names, and update book_ticket to collect them.
Database Integration: Replace file-based storage with MySQL/PostgreSQL for scalability.
Advanced Waitlist Prediction: Integrate machine learning for realistic waitlist confirmation predictions, like ConfirmTkt.
GUI/Web Interface: Extend with a GUI (e.g., GTK) or web interface (e.g., C CGI) for better UX.
Alternate Trains: Add logic to suggest alternate trains or boarding points, mimicking ConfirmTkt’s feature.

🐛 Limitations

Passenger Details: Currently simulates passenger details (only number of passengers). Extend to store names and other details.
Security: Passwords are stored in plain text; use hashing (e.g., SHA-256) for production.
PNR Generation: Uses rand(), which may not guarantee uniqueness. Consider timestamp-based PNRs.
Scalability: Fixed-size arrays (MAX_USERS, MAX_TRAINS, MAX_TICKETS) limit capacity. Use dynamic data structures (e.g., linked lists) for larger systems.
No Real-Time Data: Lacks live train status or payment integration. Use railway APIs for production.

🤝 Contributing
We welcome contributions to enhance this project! To contribute:

Fork the repository.
Create a feature branch (git checkout -b feature/YourFeature).
Commit your changes (git commit -m "Add YourFeature").
Push to the branch (git push origin feature/YourFeature).
Open a pull request.

Please ensure your code follows C99 standards and includes comments for clarity.
📜 License
This project is licensed under the MIT License. See the LICENSE file for details.
🙌 Acknowledgments

Inspired by ConfirmTkt’s seamless railway booking experience.
Built with ❤️ for developers and railway enthusiasts.

Star this repository if you find it useful! For questions or suggestions, open an issue or contact me at <your-email>. Happy booking! 🚆

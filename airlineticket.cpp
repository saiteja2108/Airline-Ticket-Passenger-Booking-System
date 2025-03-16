// #include <iostream>
// #include <vector>
// #include <string>
// #include <iomanip>
// #include <algorithm>
// #include <limits>
// #include <chrono>
// #include <sstream>
// #include <fstream>
// #include <map>
// #include <conio.h> // For getch()

// using namespace std;

// struct Passenger {
//     string name;
//     string phoneNumber;
//     string email;
// };

// struct Flight {
//     string flightNumber;
//     string source;
//     string destination;
//     double price;
//     string stopVia;
//     vector<string> availableSeats;
// };

// struct Ticket {
//     int ticketNumber;
//     Passenger passenger;
//     string flightNumber;
//     string source;
//     string destination;
//     string date;
//     string time;
//     double price;
//     string seatNumber;
//     string status;
// };

// vector<Flight> flights;
// vector<Ticket> tickets;
// map<string, vector<string> > bookedSeats;
// int ticketCounter = 1000;

// int generateTicketNumber() {
//     return ticketCounter++;
// }

// string getPassword() {
//     string password = "";
//     char ch;
//     cout << "Password: ";
//     while ((ch = getch()) != 13) { // 13 is Enter key
//         if (ch == 8 && password.length() > 0) { // 8 is Backspace
//             password.pop_back();
//             cout << "\b \b"; // Erase character from console
//         } else if (ch != 8) {
//             password.push_back(ch);
//             cout << '*'; // Display asterisk for each character
//         }
//     }
//     cout << endl;
//     return password;
// }

// void clearScreen() {
//     system("cls");
// }

// void pauseExecution() {
//     cout << "Press any key to continue...";
//     getch();
// }

// void adminLogin() {
//     string password = getPassword();
//     if (password == "sai123") {
//         clearScreen();
//         cout << "Admin Login Successful!" << endl;
//         char choice;
//         do {
//             cout << "\n1. Add Flight\n2. Exit Admin Panel\nChoice: ";
//             cin >> choice;
//             cin.ignore(numeric_limits<streamsize>::max(), '\n');
//             if (choice == '1') {
//                 Flight newFlight;
//                 cout << "Source: ";
//                 getline(cin, newFlight.source);
//                 cout << "Destination: ";
//                 getline(cin, newFlight.destination);
//                 cout << "Price: ";
//                 cin >> newFlight.price;
//                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
//                 cout << "Stop Via: ";
//                 getline(cin, newFlight.stopVia);
//                 for (char row = 'A'; row <= 'D'; ++row) {
//                     for (int seatNum = 1; seatNum <= 5; ++seatNum) {
//                         newFlight.availableSeats.push_back(string(1, row) + to_string(seatNum));
//                     }
//                 }
//                 flights.push_back(newFlight);
//                 cout << "Flight added!" << endl;
//                 pauseExecution();
//                 clearScreen();
//             }
//         } while (choice != '2');
//     } else {
//         cout << "Access Denied!" << endl;
//         pauseExecution();
//     }
// }

// void userLogin() {
//     clearScreen();
//     cout << "User Dashboard" << endl;
//     char choice;
//     do {
//         cout << "\n1. Book Ticket\n2. Exit User Panel\nChoice: ";
//         cin >> choice;
//         cin.ignore(numeric_limits<streamsize>::max(), '\n');
//         if (choice == '1') {
//             string source, destination;
//             cout << "Source: ";
//             getline(cin, source);
//             cout << "Destination: ";
//             getline(cin, destination);
//             vector<Flight> availableFlights;
//             for (const auto& flight : flights) {
//                 if (flight.source == source && flight.destination == destination) {
//                     availableFlights.push_back(flight);
//                 }
//             }
//             if (availableFlights.empty()) {
//                 cout << "No flights found!" << endl;
//                 pauseExecution();
//                 clearScreen();
//                 continue;
//             }
//             cout << "\nAvailable Flights:\n";
//             for (size_t i = 0; i < availableFlights.size(); ++i) {
//                 cout << i + 1 << ". " << availableFlights[i].source << " -> " << availableFlights[i].destination << " (" << availableFlights[i].stopVia << ") Price: " << availableFlights[i].price << endl;
//             }
//             int flightChoice;
//             cout << "Select Flight: ";
//             cin >> flightChoice;
//             cin.ignore(numeric_limits<streamsize>::max(), '\n');
//             if (flightChoice < 1 || flightChoice > availableFlights.size()) {
//                 cout << "Invalid choice!" << endl;
//                 pauseExecution();
//                 clearScreen();
//                 continue;
//             }
//             Flight selectedFlight = availableFlights[flightChoice - 1];
//             cout << "\nAvailable Seats:\n";
//             for (const auto& seat : selectedFlight.availableSeats) {
//                 cout << seat << " ";
//             }
//             cout << endl;
//             string seatNumber;
//             cout << "Enter Seat Number: ";
//             getline(cin, seatNumber);
//             auto seatIt = find(selectedFlight.availableSeats.begin(), selectedFlight.availableSeats.end(), seatNumber);
//             if (seatIt == selectedFlight.availableSeats.end()) {
//                 cout << "Seat not available!" << endl;
//                 pauseExecution();
//                 clearScreen();
//                 continue;
//             }
//             selectedFlight.availableSeats.erase(seatIt);
//             bookedSeats[selectedFlight.flightNumber].push_back(seatNumber);
//             Ticket newTicket;
//             newTicket.ticketNumber = generateTicketNumber();
//             newTicket.flightNumber = selectedFlight.flightNumber;
//             newTicket.source = source;
//             newTicket.destination = destination;
//             newTicket.price = selectedFlight.price;
//             newTicket.seatNumber = seatNumber;
//             newTicket.status = "Booked";
//             cout << "Passenger Name: ";
//             getline(cin, newTicket.passenger.name);
//             cout << "Phone Number: ";
//             getline(cin, newTicket.passenger.phoneNumber);
//             cout << "Email: ";
//             getline(cin, newTicket.passenger.email);
//             auto now = chrono::system_clock::now();
//             auto in_time_t = chrono::system_clock::to_time_t(now);
//             stringstream ss;
//             ss << put_time(localtime(&in_time_t), "%Y-%m-%d %H:%M");
//             string dateTime = ss.str();
//             newTicket.date = dateTime.substr(0, 10);
//             newTicket.time = dateTime.substr(11, 5);
//             tickets.push_back(newTicket);
//             cout << "Ticket booked!" << endl;
//             pauseExecution();
//             clearScreen();
//         }
//     } while (choice != '2');
// }

// int main() {
//     char choice;
//     do {
//         clearScreen();
//         cout << "===========================" << endl;
//         cout << "      Hawai Jahajh De Ticket" << endl;
//         cout << "===========================" << endl;
//         cout << "\n1. Login as Admin\n2. Login as User\n3. Exit\nChoice: ";
//         cin >> choice;
//         cin.ignore(numeric_limits<streamsize>::max(), '\n');
//         if (choice == '1') {
//             adminLogin();
//         } else if (choice == '2') {
//             userLogin();
//         }
//     } while (choice != '3');
//     return 0;
// }
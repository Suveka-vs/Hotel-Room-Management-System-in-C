# 🏨 Hotel Room Management System (C Language Project)

## 📌 Project Overview
This is a simple **Hotel Room Management System** developed using the C programming language.  
The system helps manage hotel rooms by allowing users to add rooms, book rooms, cancel bookings, and search room details.

It is designed as a beginner-friendly console application using **structures, arrays, and functions**.

---

## 🎯 Features

- ➕ Add new rooms to the system  
- 📋 Display all rooms with details  
- 🟢 Show only available rooms  
- 🛏️ Book a room with customer details  
- ❌ Cancel existing booking  
- 🔍 Search room by room number  
- 💰 Calculate total booking cost automatically  
- 📊 Track booking status (Available / Booked)  

---

## 🧠 Concepts Used

- Structures (`struct`)  
- Arrays of structures  
- Functions  
- Loops (`for`, `while`)  
- Conditional statements (`if`, `switch`)  
- String handling (`char arrays`)  
- Basic input/output in C  

---

## 🏗️ Project Structure

```c
struct Room {
    int number;
    char type[20];
    char acType[10];
    int price;
    int booked;
    char customer[50];
    int daysBooked;
};

How to Compile and Run
💻 Using GCC Compiler
Step 1: Compile the program
gcc filename.c -o hotel
Step 2: Run the program
./hotel

👉 Windows users:

hotel.exe

Menu Options
=== Hotel Room Management System ===
1. Add Room
2. Display Rooms
3. Book Room
4. Cancel Booking
5. Search Room
6. Exit


Sample Workflow
Add room details (room number, type, AC type, price)
View available rooms
Book a room with customer name and days
System calculates total cost automatically
Cancel booking if needed
Search room details anytime

Example Output
Room 101 successfully booked for Rahul for 2 days.
Total amount = 3000

Limitations
Data is stored only in memory (not saved to file/database)
Maximum 100 rooms supported
Uses gets() which is outdated (Turbo C compatibility)

Future Improvements
File handling for permanent storage
Login system (admin/user)
GUI version using C++
Online booking system

Author
Name: Suveka V S
Language: C Programming
Project Type: Console Application (Beginner Level)

Note

This project is made for learning purposes to understand:

Data structures in C
Real-world problem solving
Basic system design concepts



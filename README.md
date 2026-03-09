# Library Management System (C++)

## Overview

The Library Management System is a console-based application developed in C++ that helps manage basic library operations such as maintaining book records, managing student records, issuing books, and handling book returns. The system uses Object-Oriented Programming (OOP) principles and file handling to store and retrieve data efficiently.

## Features

* Create, display, modify, and delete **book records**
* Create, display, modify, and delete **student records**
* Issue books to students
* Deposit books with automatic **fine calculation for overdue returns**
* **Persistent data storage** using CSV files (`book.csv` and `student.csv`)
* Fast data lookup using **hash tables (`unordered_map`)**
* Sorted display of books and students
* Input validation for improved user interaction

## Technologies Used

* **C++**
* Object-Oriented Programming (OOP)
* File Handling (`fstream`)
* CSV Data Storage
* STL Containers (`unordered_map`, `vector`)
* Algorithms (`sort`)

## File Structure

```
Library-Management-System
│
├── main.cpp
├── book.csv
├── student.csv
└── README.md
```

## How the System Works

### Book Management

* Add new books to the system
* View all books or search for a specific book
* Modify book details
* Delete book records

### Student Management

* Register new students
* View all student records
* Search for a specific student
* Update student information
* Delete student records

### Book Issue and Return

* Students can issue one book at a time
* Book return system calculates fines automatically if the book is returned after **15 days**

## How to Run the Program

1. Clone the repository

```
git clone https://github.com/MaitriJani30/Library-Management-System.git
```

2. Navigate to the project folder

```
cd Library-Management-System
```

3. Compile the program

```
g++ main.cpp -o library
```

4. Run the program

```
./library
```

## Data Storage

The system stores data using CSV files:

* **book.csv** – Stores book records
* **student.csv** – Stores student records

These files ensure that data persists even after the program closes.

## Author

**Maitri Jani**

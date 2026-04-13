# Vending Machine Simulator (C++)

## Description
This program simulates a vending machine system that allows users to interact through both an **Admin Panel** and a **Customer Menu**. The program tracks item prices, inventory, and total sales using 2D arrays and file input/output.

---

## Features
- Customer can purchase items from multiple categories
- Tracks:
  - Items sold
  - Remaining stock
  - Total sales
- Admin panel allows:
  - Viewing sales summary
  - Viewing inventory
  - Exporting a full machine report to a `.txt` file
- Uses formatted output for clean and readable reports

---

## Program Structure

### Main Function
- Loads data from:
  - `VendingStockPrices.txt`
  - `VendingProducts.txt`
- Initializes arrays for:
  - Prices
  - Stock
  - Items sold
  - Product names
- Controls the main menu using a loop and switch statement

---

### Admin Menu
Provides access to:
- Sales Summary (`salesReport`)
- Inventory Summary (`inventoryReport`)
- Machine Report (`machineReport`)

Each function uses nested loops to iterate through all items and display formatted data.

---

### Customer Menu
- Allows the user to select a category
- Opens a submenu for item selection
- Updates:
  - `itemsSold`
  - `stock`
  - Total purchase amount (using a pointer)

---

### Item Functions
Each category (chips, candy, drinks, gum, cookies) has its own function that:
- Displays item options
- Validates user input
- Updates arrays when a purchase is made

---

### Machine Report
- Writes a full report to `MachineReport.txt`
- Includes:
  - Total items sold
  - Sales by item
  - Remaining stock
- Also prints the same report to the console

---

## How to Run

1. Place the following files in the same directory:
   - `VendingSim.cpp`
   - `VendingStockPrices.txt`
   - `VendingProducts.txt`

2. Compile and run the program in your IDE or using a compiler.

3. Use the menu:
   - `1` → Admin Panel  
   - `2` → Customer Menu  
   - `3` → Shut Down  

---

## File Dependencies

### VendingStockPrices.txt
- Contains:
  - Prices (float values)
  - Stock amounts (integer values)

### VendingProducts.txt
- Contains:
  - Category names
  - Two item options per category

---

## Key Concepts Demonstrated
- 2D Arrays
- File Input/Output (`ifstream`, `ofstream`)
- Functions and modular programming
- Pointers (for tracking total purchase amount)
- Input validation
- Nested loops for structured data processing

---

## Conclusion
This project demonstrates how a real-world system such as a vending machine can be modeled using arrays, functions, and file handling. It highlights how data is tracked and updated across multiple structures throughout program execution.

---

## Author
Lion Trejo  
Course: CSCE A201  
Date: April 2026

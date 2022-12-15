# Disaster-and-Emergency-Aid-management

## Use case

When disaster hits a nation, the most urgent task is to be able to provide the people affected with what they need as quickly and as efficiently possible.
Your job for this project is to prepare an application that manages the list of items needed to be shipped to the area. The application should be able to keep track of the quantity of each item needed, the number of items on hand, shipping the items and storing the data in a file for future use. 

The types of items needed to be shipped in this situation are divided into two main categories; 

- Non-Perishable products, such as blankets and tents, that have no expiry date. We refer to these types of products as Items.
- Perishable products, such as food and medicine, that have an expiry date. We refer to these products as Perishables. 

To accomplish this task we need to create several classes to encapsulate the problem and provide a solution for this application. 

## Compiling and Testing Your Program

All your code should be compiled using this command on `matrix`:

```bash
g++ -Wall -std=c++11 -g -o ms file1.cpp file2.cpp ...
```

- `-Wall`: the compiler will report all warnings
- `-std=c++11`: the code will be compiled using the C++11 standard
- `-g`: the executable file will contain debugging symbols, allowing *valgrind* to create better reports
- `-o ms`: the compiled application will be named `ms`

After compiling and testing your code, run your program as following to check for possible memory leaks (assuming your executable name is `ms`):

```bash
valgrind -s --leak-check=full ms
```

To check the output, use a program that can compare text files.  Search online for such a program for your platform, or use *diff* available on `matrix`.


## Test


#### Tester program
```C++
/* ------------------------------------------------------
Final project Milestone 56
Filename: main56.cpp
Version 1.0
Author: Fardad Soleimanloo   2022-04-01
Revision History
-----------------------------------------------------------
Date          Reason
-----------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include "AidMan.h"
#include "Utils.h"
using namespace sdds;
using namespace std;

void copyfile(const char* to, const char* from);
void displayFile(const char* file);

int main() {
   copyfile("data.dat", "data56.dat");
   ut.testMode();
   AidMan().run();
   displayFile("data.dat");
   cout << endl << "------------------------------------------------" << endl;
   displayFile("shippingOrder.txt");
   return 0;
}

void displayFile(const char* file) {
   ifstream in(file);
   char ch;
   cout << "File: " << file << endl;
   while (in.get(ch)) cout << ch;
}

void copyfile(const char* to, const char* from) {
   std::ifstream in(from);
   std::ofstream out(to);
   char ch;
   while (in.get(ch)) out.put(ch);
}

```
#### Test Data
```text
7
data.dat
6
1
<ENTER>
0
```
#### Expected Output
```text
Aid Management System
Date: 2022/03/31
Data file: No file
---------------------------------
1- List Items
2- Add Item
3- Remove Item
4- Update Quantity
5- Sort
6- Ship Items
7- New/Open Aid Database
---------------------------------
0- Exit
> 7

****New/Open Aid Database****
Enter file name: data.dat
6 records loaded!

Aid Management System
Date: 2022/03/31
Data file: data.dat
---------------------------------
1- List Items
2- Add Item
3- Remove Item
4- Update Quantity
5- Sort
6- Ship Items
7- New/Open Aid Database
---------------------------------
0- Exit
> 6

****Ship Items****
Shipping Order for 3 times saved!

Aid Management System
Date: 2022/03/31
Data file: data.dat
---------------------------------
1- List Items
2- Add Item
3- Remove Item
4- Update Quantity
5- Sort
6- Ship Items
7- New/Open Aid Database
---------------------------------
0- Exit
> 1

****List Items****
 ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry
-----+-------+-------------------------------------+------+------+---------+-----------
   1 | 45678 | Sleeping Bags                       |  100 |  200 |   65.66 |
   2 | 44444 | Flash lights                        |  399 |  400 |   65.66 |
   3 | 12345 | Baby Formula                        |  145 |  200 |   33.99 | 2022/12/12
-----+-------+-------------------------------------+------+------+---------+-----------
Enter row number to display details or <ENTER> to continue:
> 

Aid Management System
Date: 2022/03/31
Data file: data.dat
---------------------------------
1- List Items
2- Add Item
3- Remove Item
4- Update Quantity
5- Sort
6- Ship Items
7- New/Open Aid Database
---------------------------------
0- Exit
> 0
Exiting Program!
File: data.dat
45678	Sleeping Bags	100	200	65.66
44444	Flash lights	399	400	65.66
12345	Baby Formula	145	200	33.99		221212

------------------------------------------------
File: shippingOrder.txt
Shipping Order, Date: 2022/03/31
 ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry
-----+-------+-------------------------------------+------+------+---------+-----------
   1 | 12113 | Hydrogen peroxide 100ml bottles     |  300 |  300 |    3.99 |*2023/11/11
   2 | 56789 | Tents and Blankets and pillows Tent | 2000 | 2000 |   65.66 |
   3 | 11223 | Enfamil A+                          |   38 |   38 |   38.99 |*2022/11/11
-----+-------+-------------------------------------+------+------+---------+-----------
```


Overview
This project is a small E-Commerce interface built by a group. The data is stored in a MySQL database on a Zeus Linux Server. The system utilizes C API to connect to the MySQL server. The main functionalities of the system include Admin operations, product search, managing shopping cart, and generating a purchase statement.

Main Menu
Admin
Search for Products
My Shopping Cart
Quit

Sub Menu – Admin
Insert Product Info
Delete Product Info
Delete Product
Delete Product Item
Display the List of Products
Display Number of Products (Page at a time)
Display Product Details (Page at a time)
List of Products (Example)
Laptop
Attributes: Brand name, Processor Brand, Processor model, Operating system, Ram, Price, Storage Capacity, Condition (New, Refurbished, used, Open-box), Number of items, etc.
Camera
Phone
Watch
Refrigerator
Laundry Washer
Laundry Dryer
Microwave
...
...
Sub-Menu - Search
Searchable Items:

Laptop
...
...
Select the item: ______

Search Criteria:

Brand: {apple, ibm, dell, ...}
Condition: {new, used, ...}
Operating System: {Mac, Windows, Linux, Chrome, ...}
Processor Brand: {Intel, Power PC, A1, M1, ...}
Sort by: Price High to Low / Low to High
Display Search Result
sql
Copy code
Search: Searching for Laptop
Brand: Apple
Condition: New
Operating System: Mac
Processor Brand: Intel

-----------------------------------
Display Search Result
1. Mackbook Pro {some detail} $1299.00
2. Dell {detail description} $790.00
3. HP {detail description} $899.00

Add to the cart: {1,2}
Shopping Cart Menu
Display What Is on the Shopping Cart
Submit to Make a Purchase
6% sales tax is added.
Generate a Statement
Statement is saved as a text file.
Implementation Details
The system is implemented using C language and the MySQL C API to interact with the MySQL database. The user interface allows administrators to manage products, users to search for products based on specific criteria, add items to their cart, and make purchases. The system also handles generating purchase statements and applies appropriate taxes.

For the code implementation and detailed usage, please refer to the source code files in the repository.

How to Use
Clone the repository to your local machine.
Compile the C files using an appropriate compiler.
Ensure MySQL server is running.
Run the executable file to start the E-Commerce interface.
Follow the on-screen instructions to navigate through the system.
Feel free to contribute, report issues, or suggest improvements to enhance the functionality of this E-Commerce interface.

Happy Shopping! 🛒

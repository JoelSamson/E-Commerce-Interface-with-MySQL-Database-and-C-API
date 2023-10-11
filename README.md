# E-Commerce Interface with MySQL Database and C API

## Overview

This collaborative project aims to create a user-friendly E-Commerce interface. The system stores its data in a MySQL database hosted on a Zeus Linux Server. The communication between the system and the database is facilitated by the MySQL C API. The core functionalities of the system include administrative operations, product search, managing shopping carts, and generating purchase statements.

## Main Menu

- **Admin**
- **Search for Products**
- **My Shopping Cart**
- **Quit**

  ![image](https://github.com/JoelSamson/E-commerce-System-C/assets/55976489/7b0de6d2-fe6d-4612-84d0-6d1bb699888d)


### Sub Menu – Admin

- **Insert Product Info**
- **Delete Product Info**
  - Delete Product
  - Delete Product Item
- **Display the List of Products**
  - Display Number of Products
  - Display Product Details

### Product Categories

- **Refrigerator**
- **Phone**
- **Watch**
- **Microwave**
- **Laundry Washer**
- **Laundry Dryer**
- **Camera**
- **Laptop**

![image](https://github.com/JoelSamson/E-commerce-System-C/assets/55976489/27d77ae4-4a26-43c3-9183-1ed632eb4723)


### Sub-Menu - Search

**Searchable Items:**

- **Refrigerator**
- **Phone**
- **Watch**
- **Microwave**
- **Laundry Washer**
- **Laundry Dryer**
- **Camera**
- **Laptop**
  
**Select the item:** ______

**Search Criteria:**

- **Brand:** {apple, ibm, dell, ...}
- **Condition:** {new, used, ...}
- **Operating System:** {Mac, Windows, Linux, Chrome, ...}
- **Processor Brand:** {Intel, Power PC, A1, M1, ...}
- **Sort by:** Price High to Low / Low to High

#### Display Search Result

```
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
```

## Cart Menu

- **Add to the cart:** {1,2}
- **Display What Is on the Shopping Cart**
- **Submit to Make a Purchase**
  - 6% sales tax is added.
- **Generate a Statement**
  - Statement is saved as a text file.

## Database Schema

### Revised Table Creation Commands:

1. **Refrigerator Table:**

   ```sql
   CREATE TABLE Refrigerator (
     brand_name VARCHAR(10) NOT NULL,
     model_name VARCHAR(10) NOT NULL,
     capacity_cubic_feet DECIMAL(10, 2),
     color VARCHAR(20) DEFAULT 'Not specified',
     price DECIMAL(10, 2),
     PRIMARY KEY (brand_name, model_name)
   );
   ```

2. **Phone Table:**

   ```sql
   CREATE TABLE Phone (
     brand_name VARCHAR(10) NOT NULL,
     model_name VARCHAR(10) NOT NULL,
     operating_system VARCHAR(10),
     storage_capacity_gb DECIMAL(5, 2),
     price DECIMAL(10, 2),
     PRIMARY KEY (brand_name, model_name)
   );
   ```

3. **Watch Table:**

   ```sql
   CREATE TABLE Watch (
     brand_name VARCHAR(10) NOT NULL,
     model_name VARCHAR(10) NOT NULL,
     type VARCHAR(10) NOT NULL,
     water_resistant BOOLEAN,
     color VARCHAR(20) DEFAULT 'Not specified',
     price DECIMAL(10, 2),
     PRIMARY KEY (brand_name, model_name)
   );
   ```

4. **Microwave Table:**

   ```sql
   CREATE TABLE Microwave (
     brand_name VARCHAR(10) NOT NULL,
     model_name VARCHAR(10) NOT NULL,
     capacity_cubic_feet DECIMAL(10, 2),
     material VARCHAR(20) DEFAULT 'Not specified',
     voltage_watts INT DEFAULT 0,
     energy_use INT DEFAULT 0,
     color VARCHAR(20) DEFAULT 'Not specified',
     price DECIMAL(10, 2),
     PRIMARY KEY (brand_name, model_name)
   );
   ```

5. **Laundry Washer Table:**

   ```sql
   CREATE TABLE Laundry_Washer (
     brand_name VARCHAR(10) NOT NULL,
     model_name VARCHAR(10) NOT NULL,
     access_location VARCHAR(20) DEFAULT 'Not specified',
     rpm INT DEFAULT 0,
     capacity_cubic_feet DECIMAL(10, 2) DEFAULT 0.00,
     material VARCHAR(20) DEFAULT 'Not specified',
     voltage_watts INT DEFAULT 0,
     energy_use INT DEFAULT 0,
     color VARCHAR(20) DEFAULT 'Not specified',
     price DECIMAL(10, 2),
     PRIMARY KEY (brand_name, model_name)
   );
   ```

6. **Laundry Dryer Table:**

   ```sql
   CREATE TABLE Laundry_Dryer (
     brand_name VARCHAR(10) NOT NULL,
     model_name VARCHAR(10) NOT NULL,
     access_location VARCHAR(20) DEFAULT 'Not specified',
     rpm INT DEFAULT 0,
     capacity_cubic_feet DECIMAL(10, 2) DEFAULT 0.00,
     material VARCHAR(20) DEFAULT 'Not specified',
     voltage_watts INT DEFAULT 0,
     energy_use INT DEFAULT 0,
     color VARCHAR(20) DEFAULT 'Not specified',
     price DECIMAL(10, 2),
     PRIMARY KEY (brand_name, model_name)
   );
   ```

7. **Camera Table:**

   ```sql
   CREATE TABLE Camera (
     brand_name VARCHAR(10) NOT NULL,
     model_name VARCHAR(10) NOT NULL,
     resolution_megapixels INT DEFAULT 0,
     lens_type VARCHAR(10),
     price DECIMAL(10, 2),
     PRIMARY KEY (brand_name, model_name)
   );
   ```

8. **Laptop Table:**

   ```sql
   CREATE TABLE Laptop (
     brand_name VARCHAR(10) NOT NULL,
     model_name VARCHAR(10) NOT NULL,
     processor_brand VARCHAR(10),
     operating_system VARCHAR(10),
     ram_gb INT DEFAULT 0,
     storage_capacity_gb DECIMAL(5, 2),
     price DECIMAL(10, 2),
     PRIMARY KEY (brand_name, model_name)
   );
   ```

   ![image](https://github.com/JoelSamson/E-commerce-System-C/assets/55976489/57f91d4d-b403-4b84-a940-b8ea3f7b0f24)


By ensuring unique table names, appropriate primary keys, and suitable column names and data types, the database schema is structured to accommodate various product categories.

## Implementation Details

The system is implemented using the C language and the MySQL C API to interact with the MySQL database. The user interface enables administrators to manage products, while users can search for products, add items to their cart, and make purchases. The system also handles generating purchase statements and applies appropriate taxes.

For detailed code implementation, refer to the source code files in the repository. Access to the MySQL C API was provided by the University of George Mason.


## How to Use

1. Clone the repository to your local machine.
2. Compile the C files using an appropriate compiler:

   ```bash
   gcc -Wall -o a.out *.c $(mysql_config --cflags --libs)
   ```

   **Note:** The password to the MySQL server is not hardcoded in the code for security reasons.

3. Ensure the MySQL server is running.
4. Run the executable file to start the E-Commerce interface.
5. Follow the on-screen instructions to navigate through the system.

Contributions, issue reports, and suggestions for improvement are welcome to enhance the functionality of this E-Commerce interface.

**Happy Shopping!** 🛒

DROP TABLE if exists Orders_Unnormalized;

CREATE TABLE Orders_Unnormalized (
    OrderID INT,
    OrderDate DATE,
    CustomerID INT,
    CustomerName VARCHAR(100),
    CustomerPhone VARCHAR(20),
    CustomerAddress VARCHAR(255),

    Product1ID INT,
    Product1Name VARCHAR(100),
    Product1Price DECIMAL(10,2),
    Product1Qty INT,

    Product2ID INT,
    Product2Name VARCHAR(100),
    Product2Price DECIMAL(10,2),
    Product2Qty INT,

    Product3ID INT,
    Product3Name VARCHAR(100),
    Product3Price DECIMAL(10,2),
    Product3Qty INT,

    PaymentMethod VARCHAR(50),
    PaymentStatus VARCHAR(50)
);

INSERT INTO Orders_Unnormalized VALUES
(1001, '2026-01-05', 1, 'Cosimo Piovasco', '01711111111', 'Dhaka',
101, 'Laptop', 75000.00, 1,
201, 'Mouse', 500.00, 2,
301, 'Keyboard', 1200.00, 1,
'Credit Card', 'Paid'),

(1002, '2026-01-06', 2, 'Marcovaldo Rossi', '01822222222', 'Chittagong',
102, 'Smartphone', 32000.00, 1,
202, 'Charger', 800.00, 1,
NULL, NULL, NULL, NULL,
'Bkash', 'Paid'),

(1003, '2026-01-07', 3, 'Qfwfq Narrator', '01933333333', 'Sylhet',
103, 'Tablet', 28000.00, 1,
203, 'Headphones', 1500.00, 1,
302, 'USB Cable', 300.00, 3,
'Cash', 'Pending'),

(1004, '2026-01-08', 4, 'Palomar Observer', '01644444444', 'Rajshahi',
104, 'Monitor', 12000.00, 2,
NULL, NULL, NULL, NULL,
NULL, NULL, NULL, NULL,
'Debit Card', 'Paid'),

(1005, '2026-01-09', 5, 'Ludmilla Reader', '01555555555', 'Khulna',
105, 'Printer', 15000.00, 1,
204, 'Ink Cartridge', 2500.00, 2,
NULL, NULL, NULL, NULL,
'Bkash', 'Paid'),

(1006, '2026-01-10', 6, 'Silas Flannery', '01466666666', 'Dhaka',
106, 'Router', 3500.00, 1,
205, 'LAN Cable', 400.00, 5,
303, 'Power Bank', 1800.00, 1,
'Credit Card', 'Failed'),

(1007, '2026-01-11', 7, 'Agilulf Knight', '01377777777', 'Barisal',
107, 'Camera', 42000.00, 1,
206, 'SD Card', 900.00, 2,
NULL, NULL, NULL, NULL,
'Cash', 'Paid'),

(1008, '2026-01-12', 8, 'Rambaldo Soldier', '01288888888', 'Comilla',
108, 'Speaker', 2200.00, 2,
207, 'Bluetooth Adapter', 600.00, 1,
304, 'Microphone', 1500.00, 1,
'Bkash', 'Pending'),

(1009, '2026-01-13', 9, 'Bradamante Warrior', '01199999999', 'Dhaka',
109, 'Gaming Chair', 9500.00, 1,
NULL, NULL, NULL, NULL,
NULL, NULL, NULL, NULL,
'Credit Card', 'Paid'),

(1010, '2026-01-14', 10, 'Viola Rondo', '01700000000', 'Mymensingh',
110, 'External HDD', 6500.00, 1,
208, 'USB Hub', 700.00, 1,
305, 'Laptop Stand', 1100.00, 1,
'Debit Card', 'Paid'),

(1011, '2026-01-15', 11, 'Amerigo Ormea', '01911112222', 'Sylhet',
103, 'Tablet', 28000.00, 1,
NULL, NULL, NULL, NULL,
NULL, NULL, NULL, NULL,
'Cash', 'Paid'),

(1012, '2026-01-16', 12, 'Ottavia Resident', '01812345678', 'Dhaka',
111, 'Smartwatch', 8500.00, 1,
209, 'Watch Strap', 400.00, 2,
NULL, NULL, NULL, NULL,
'Bkash', 'Paid'),

(1013, '2026-01-17', 13, 'Leonia Citizen', '01987654321', 'Rangpur',
112, 'Projector', 27000.00, 1,
210, 'HDMI Cable', 500.00, 2,
306, 'Extension Board', 1200.00, 1,
'Credit Card', 'Pending'),

(1014, '2026-01-18', 14, 'Zenobia Dreamer', '01611223344', 'Dhaka',
113, 'Desk Lamp', 1500.00, 2,
NULL, NULL, NULL, NULL,
NULL, NULL, NULL, NULL,
'Cash', 'Paid'),

(1015, '2026-01-19', 15, 'Isidora Traveler', '01566778899', 'Jessore',
114, 'Graphics Card', 45000.00, 1,
211, 'Cooling Fan', 800.00, 3,
NULL, NULL, NULL, NULL,
'Debit Card', 'Failed'),

(1016, '2026-01-20', 16, 'Anastasia Merchant', '01499887766', 'Dhaka',
115, 'SSD', 9000.00, 1,
212, 'SATA Cable', 200.00, 2,
307, 'PC Case', 3500.00, 1,
'Bkash', 'Paid');

 
SELECT * FROM Orders_Unnormalized;




-- Task 1
-- 1) Repeating columns
-- 2) Lots of null VALUES
-- 3) Data repitation
-- 4) Cannot add new product

-- Task 2
Drop table if exists Orders_1NF;

create table Orders_1NF (
  OrderID INT,
  OrderDate DATE,
  CustomerId INT,
  CustomerName VARCHAR(100),
  CustomerPhone VARCHAR(20),
  CustomerAddress VARCHAR(255),
  ProductID INT,
  ProductName VARCHAR(100),
  ProductPrice Decimal(10,2),
  ProductQty INT,
  PaymentMethod VARCHAR(50),
  PaymentStatus VARCHAR(50),
  primary key (OrderID, ProductID)
);

insert into Orders_1NF
select OrderID, OrderDate, CustomerId, CustomerName, CustomerPhone, CustomerAddress,
       Product2ID, Product2Name, Product2Price, Product2Qty, PaymentMethod, PaymentStatus
from Orders_Unnormalized
where Product2ID is not NULL
union all
select OrderID, OrderDate, CustomerId, CustomerName, CustomerPhone, CustomerAddress,
       Product1ID, Product1Name, Product1Price, Product1Qty, PaymentMethod, PaymentStatus
from Orders_Unnormalized
where Product1ID is not NULL
union all
select OrderID, OrderDate, CustomerId, CustomerName, CustomerPhone, CustomerAddress,
       Product3ID, Product3Name, Product3Price, Product3Qty, PaymentMethod, PaymentStatus
from Orders_Unnormalized
where Product3ID is not NULL;

select * from Orders_1NF order by OrderID, ProductID;

--task 3
DROP TABLE IF EXISTS Customers_2NF CASCADE;
CREATE TABLE Customers_2NF (
    CustomerID      INT PRIMARY KEY,
    CustomerName    VARCHAR(100),
    CustomerPhone   VARCHAR(20),
    CustomerAddress VARCHAR(255)
);

INSERT INTO Customers_2NF
SELECT DISTINCT CustomerID, CustomerName, CustomerPhone, CustomerAddress
FROM Orders_1NF;

DROP TABLE IF EXISTS Products_2NF CASCADE;
CREATE TABLE Products_2NF (
    ProductID    INT PRIMARY KEY,
    ProductName  VARCHAR(100),
    ProductPrice DECIMAL(10,2)
);

INSERT INTO Products_2NF
SELECT DISTINCT ProductID, ProductName, ProductPrice
FROM Orders_1NF;

DROP TABLE IF EXISTS Orders_2NF CASCADE;
CREATE TABLE Orders_2NF (
    OrderID       INT PRIMARY KEY,
    OrderDate     DATE,
    CustomerID    INT REFERENCES Customers_2NF(CustomerID),
    PaymentMethod VARCHAR(50),
    PaymentStatus VARCHAR(50)
);

INSERT INTO Orders_2NF
SELECT DISTINCT OrderID, OrderDate, CustomerID, PaymentMethod, PaymentStatus
FROM Orders_1NF;

DROP TABLE IF EXISTS OrderItems_2NF CASCADE;
CREATE TABLE OrderItems_2NF (
    OrderID    INT REFERENCES Orders_2NF(OrderID),
    ProductID  INT REFERENCES Products_2NF(ProductID),
    ProductQty INT,
    PRIMARY KEY (OrderID, ProductID)
);

INSERT INTO OrderItems_2NF
SELECT DISTINCT OrderID, ProductID, ProductQty
FROM Orders_1NF;

SELECT * FROM Customers_2NF ORDER BY CustomerID;
SELECT * FROM Products_2NF   ORDER BY ProductID;
SELECT * FROM Orders_2NF     ORDER BY OrderID;
SELECT * FROM OrderItems_2NF ORDER BY OrderID, ProductID;

--task 4
DROP TABLE IF EXISTS PaymentMethods_3NF CASCADE;
CREATE TABLE PaymentMethods_3NF (
    PaymentMethodID   SERIAL PRIMARY KEY,
    PaymentMethodName VARCHAR(50) UNIQUE NOT NULL
);

INSERT INTO PaymentMethods_3NF (PaymentMethodName)
SELECT DISTINCT PaymentMethod FROM Orders_2NF WHERE PaymentMethod IS NOT NULL;

DROP TABLE IF EXISTS Payments_3NF CASCADE;
CREATE TABLE Payments_3NF (
    PaymentID       SERIAL PRIMARY KEY,
    OrderID         INT UNIQUE, 
    PaymentMethodID INT REFERENCES PaymentMethods_3NF(PaymentMethodID),
    PaymentStatus   VARCHAR(50)
);

INSERT INTO Payments_3NF (OrderID, PaymentMethodID, PaymentStatus)
SELECT o.OrderID,
       pm.PaymentMethodID,
       o.PaymentStatus
FROM Orders_2NF o
JOIN PaymentMethods_3NF pm ON pm.PaymentMethodName = o.PaymentMethod;


DROP TABLE IF EXISTS Customers CASCADE;
DROP TABLE IF EXISTS Products  CASCADE;
DROP TABLE IF EXISTS Orders    CASCADE;
DROP TABLE IF EXISTS OrderItems CASCADE;
DROP TABLE IF EXISTS Payments  CASCADE;
DROP TABLE IF EXISTS PaymentMethods CASCADE;

CREATE TABLE Customers (
    CustomerID      INT PRIMARY KEY,
    CustomerName    VARCHAR(100)  NOT NULL,
    CustomerPhone   VARCHAR(20),
    CustomerAddress VARCHAR(255)
);

CREATE TABLE Products (
    ProductID    INT PRIMARY KEY,
    ProductName  VARCHAR(100)    NOT NULL,
    ProductPrice DECIMAL(10,2)   NOT NULL
);

CREATE TABLE Orders (
    OrderID    INT PRIMARY KEY,
    OrderDate  DATE NOT NULL,
    CustomerID INT  NOT NULL REFERENCES Customers(CustomerID)
);

CREATE TABLE OrderItems (
    OrderID    INT            NOT NULL REFERENCES Orders(OrderID),
    ProductID  INT            NOT NULL REFERENCES Products(ProductID),
    ProductQty INT            NOT NULL CHECK (ProductQty > 0),
    PRIMARY KEY (OrderID, ProductID)
);

CREATE TABLE PaymentMethods (
    PaymentMethodID   SERIAL PRIMARY KEY,
    PaymentMethodName VARCHAR(50) UNIQUE NOT NULL
);

CREATE TABLE Payments (
    PaymentID       SERIAL PRIMARY KEY,
    OrderID         INT UNIQUE NOT NULL REFERENCES Orders(OrderID),
    PaymentMethodID INT        NOT NULL REFERENCES PaymentMethods(PaymentMethodID),
    PaymentStatus   VARCHAR(50) NOT NULL
);


INSERT INTO Customers SELECT * FROM Customers_2NF;
INSERT INTO Products  SELECT * FROM Products_2NF;

INSERT INTO Orders
SELECT DISTINCT OrderID, OrderDate, CustomerID FROM Orders_2NF;

INSERT INTO OrderItems
SELECT OrderID, ProductID, ProductQty FROM OrderItems_2NF;

INSERT INTO PaymentMethods (PaymentMethodName)
SELECT DISTINCT PaymentMethod FROM Orders_2NF WHERE PaymentMethod IS NOT NULL;

INSERT INTO Payments (OrderID, PaymentMethodID, PaymentStatus)
SELECT o.OrderID, pm.PaymentMethodID, o.PaymentStatus
FROM Orders_2NF o
JOIN PaymentMethods pm ON pm.PaymentMethodName = o.PaymentMethod;


SELECT * FROM Customers    ORDER BY CustomerID;
SELECT * FROM Products     ORDER BY ProductID;
SELECT * FROM Orders       ORDER BY OrderID;
SELECT * FROM OrderItems   ORDER BY OrderID, ProductID;
SELECT * FROM PaymentMethods;
SELECT * FROM Payments     ORDER BY OrderID;


--task5
/*
  An INSERT anomaly occurs when new information cannot be added to the database without including unrelated data. For example, a new product cannot be recorded unless it is attached to an order. This means you cannot store ProductID = 999, “SSD Enclosure,” priced at ৳800 unless someone actually places an order for it, because there is no way to store product information independently. Similarly, a new customer cannot be saved unless they place an order at the same time, since customer details exist only within order records.
  An UPDATE anomaly happens when the same data is stored in multiple rows and must be updated in all of them to maintain consistency. For instance, if the price of a Laptop (ProductID = 101) changes from 75,000 to 80,000, every row containing that laptop must be updated. If even one row is missed, the database becomes inconsistent. Likewise, if a customer changes their phone number, every order record associated with that customer must be updated.
  A DELETE anomaly occurs when deleting a record unintentionally removes additional important information. For example, if the only order placed by CustomerID = 11 (Amerigo Ormea, OrderID = 1011) is deleted, all information about that customer—such as name, phone number, and address—is permanently lost because customer data exists only within order records. Similarly, deleting OrderID = 1004, which is the only order containing the Monitor (ProductID = 104), would remove the only record showing that the Monitor product ever existed.
*/
































/* =========================
   Task 1 & 2: Sales Transactions
   ========================= */

DROP TABLE IF EXISTS sales_transactions CASCADE;

CREATE TABLE sales_transactions (
    transaction_id INT PRIMARY KEY,
    transaction_date DATE NOT NULL,
    customer_id INT NOT NULL,
    product_id INT NOT NULL,
    category VARCHAR(50) NOT NULL,
    subcategory VARCHAR(50),
    region VARCHAR(50) NOT NULL,
    country VARCHAR(50) NOT NULL,
    city VARCHAR(100),
    quantity INT NOT NULL,
    unit_price DECIMAL(10,2) NOT NULL,
    discount_percent DECIMAL(5,2) DEFAULT 0,
    tax_rate DECIMAL(5,2) DEFAULT 0,
    shipping_cost DECIMAL(10,2) DEFAULT 0,
    payment_method VARCHAR(30),
    salesperson_id INT
);

INSERT INTO sales_transactions VALUES
(1, '2024-01-15', 101, 501, 'Electronics', 'Laptops', 'North America', 'USA', 'New York', 2, 1200.00, 10.00, 8.50, 25.00, 'Credit Card', 201),
(2, '2024-01-15', 102, 502, 'Electronics', 'Phones', 'North America', 'USA', 'Los Angeles', 1, 800.00, 5.00, 8.50, 15.00, 'PayPal', 201),
(3, '2024-01-16', 103, 503, 'Clothing', 'Shirts', 'Europe', 'UK', 'London', 3, 45.00, 15.00, 20.00, 10.00, 'Credit Card', 202),
(4, '2024-01-16', 104, 504, 'Electronics', 'Tablets', 'Asia', 'Japan', 'Tokyo', 1, 650.00, 8.00, 10.00, 30.00, 'Bank Transfer', 203),
(5, '2024-01-17', 105, 505, 'Clothing', 'Pants', 'North America', 'Canada', 'Toronto', 2, 60.00, 12.00, 13.00, 8.00, 'Credit Card', 201),
(6, '2024-02-01', 106, 506, 'Home & Garden', 'Furniture', 'Europe', 'Germany', 'Berlin', 1, 450.00, 5.00, 19.00, 50.00, 'Credit Card', 202),
(7, '2024-02-05', 107, 507, 'Electronics', 'Laptops', 'Asia', 'China', 'Shanghai', 3, 1100.00, 12.00, 13.00, 40.00, 'WeChat Pay', 203),
(8, '2024-02-10', 108, 508, 'Clothing', 'Jackets', 'North America', 'USA', 'Chicago', 1, 120.00, 20.00, 8.50, 12.00, 'PayPal', 201);


/* =========================
   Task 3: Customer Data
   ========================= */

DROP TABLE IF EXISTS customer_data CASCADE;

CREATE TABLE customer_data (
    customer_id INT PRIMARY KEY,
    full_name VARCHAR(200) NOT NULL,
    email VARCHAR(200) NOT NULL,
    phone_number VARCHAR(50),
    address VARCHAR(300),
    postal_code VARCHAR(20),
    registration_date DATE,
    username VARCHAR(100),
    notes TEXT,
    tax_id VARCHAR(50)
);

INSERT INTO customer_data VALUES
(1, 'Mr. John A. Smith', 'john.smith@example.com', '+1-555-123-4567', '123 Main St, Apt 4B', '10001', '2023-01-15', 'jsmith2023', 'Prefers email contact', 'SSN:123-45-6789'),
(2, 'Mary O''Brien-Jones', 'mary.obrien@company.co.uk', '+44-20-7123-4567', '45 Oxford Road', 'SW1A 1AA', '2023-02-20', 'mobrien_uk', NULL, 'VAT:GB123456789'),
(3, 'Dr. Robert Chen, PhD', 'r.chen@university.edu', '555.987.6543', '789 University Ave', '94105-1234', '2023-03-10', 'dr_chen_phd', 'Academic discount applied', NULL),
(4, 'Mrs. Sarah Martinez-Lopez', 'smartinez2024@gmail.com', '(555) 246-8135', '321 Elm Street', '75001', '2024-01-05', 'sarah_ml_2024', 'VIP customer since 2020', 'EIN:12-3456789'),
(5, 'James T. Kirk Jr.', 'james.kirk.jr@enterprise.com', '+1 555 CALL-NOW', 'Starfleet HQ', 'NCC-1701', '2023-12-25', 'captain_kirk', 'Boldly going...', NULL),
(6, 'Invalid Email User', 'notanemail', '123456', 'No Address', 'ABC', '2024-01-01', 'bad_data', 'Test record with bad data', NULL),
(7, 'Anna-Maria Müller', 'a.mueller@example.de', '+49-30-12345678', 'Berliner Straße 100', '10115', '2023-06-15', 'amueller_de', NULL, 'TAXID:DE123456789'),
(8, '李明', 'liming@example.cn', '86-10-1234-5678', 'Beijing Road 88', '100000', '2023-08-20', 'liming_cn', 'Chinese customer', 'USCI:91110000123456789X');
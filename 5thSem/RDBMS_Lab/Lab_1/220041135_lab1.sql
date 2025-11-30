DROP TABLE IF EXISTS Employee;
DROP TABLE IF EXISTS Branch;

CREATE TABLE Branch (
    BID SERIAL PRIMARY KEY,
    Name VARCHAR(50) UNIQUE,
    Location VARCHAR(50)
);

CREATE TABLE Employee (
    EID SERIAL PRIMARY KEY,
    Name VARCHAR(50),
    Salary NUMERIC(10,2),
    Branch INTEGER REFERENCES Branch(BID)
);

INSERT INTO Branch (Name, Location)
VALUES
('A', 'Dhaka'),
('B', 'Chittagong'),
('C', 'Dhaka'),
('D', 'Rajshahi');

INSERT INTO Employee (Name, Salary, Branch)
VALUES
('Tasnif Emran', 60000, 1),
('Rahim', 55000, 1),
('Karim', 52000, 1),
('Farzana', 65000, 1),
('Nadia', 48000, 1),
('Sabbir', 40000, 2),
('Lamia', 42000, 2),
('Hasib', 53000, 3),
('Arif', 50000, 3),
('Sadia', 54000, 3),
('Jannat', 39000, 4),
('Mamun', 45000, 4);

-- SELECT * FROM Branch;

-- SELECT * FROM Employee;

-- 2(a)
SELECT COUNT(*) 
FROM Employee 
WHERE Branch = (SELECT BID FROM Branch WHERE Name = 'A')
AND Salary> (SELECT AVG(Salary) FROM Employee);

--2(b)
SELECT b.Name
FROM Branch b
JOIN Employee e ON b.BID = e.Branch
WHERE e.Name = 'Tasnif Emran';

-- 2(c)
SELECT b.Location, COUNT(e.EID) AS total_employees
FROM Employee e
JOIN Branch b ON b.BID = e.Branch
GROUP BY b.Location
ORDER BY total_employees DESC;

-- Table t1
CREATE TABLE t1 (
    id SERIAL PRIMARY KEY,
    date_str VARCHAR(50)  -- e.g., '2015-08-20', 'Date: 2009/01/15'
);

-- Sales table
CREATE TABLE sales (
    department VARCHAR(50),
    amount     NUMERIC
);

-- Order details table
CREATE TABLE order_details (
    department VARCHAR(50),
    product    VARCHAR(50),
    sales      NUMERIC
);

-- Employees table
CREATE TABLE employees (
    emp_id      SERIAL PRIMARY KEY,
    name        VARCHAR(100),
    department  VARCHAR(50),
    designation VARCHAR(50),
    hire_date   DATE
);

-- Sample Data
INSERT INTO t1 (date_str) VALUES ('2008-03-15'),('2010-07-22'),('2015-11-01'),('1999-05-30'),('2023-01-10');

INSERT INTO sales VALUES ('HR',500),('HR',800),('IT',700),('IT',600),('Finance',1300),('Finance',200);

INSERT INTO order_details VALUES
('HR','PenDrive',300),('HR','Laptop',800),
('IT','Monitor',600),('IT','Keyboard',700),
('Finance','Tablet',900),('Finance','Phone',600);

INSERT INTO employees (name, department, designation, hire_date) VALUES
('Alice',  'IT',      'Manager',   '2005-03-12'),
('Bob',    'HR',      'Analyst',   '2012-07-19'),
('Carol',  'Finance', 'Developer', '2018-11-05'),
('Dave',   'IT',      'Developer', '2009-06-23'),
('Eve',    'HR',      'Manager',   '2021-01-15');

--task1
select * from t1
where cast(regexp_replace(date_str, '.*(\d{4}).*', '\1') as INTEGER) >= 2010;

--task2
DO $$
DECLARE
    rec RECORD;
    extracted_year int;
BEGIN
    for rec in
        select * from t1
    LOOP
        extracted_year := cast(regexp_replace(rec.date_str, '.*(\d{4}).*', '\1') as INTEGER);
        RAISE NOTICE 'Extracted Year: %' , extracted_year;
    end LOOP;
end $$;

--task3
select * from sales
where amount >1200
group by department, amount;

--task4
DO $$
DECLARE
    rec RECORD;
    dp varchar;
BEGIN
    for rec in
        select * from sales
        where amount >1000
        group by department, amount
    LOOP
       dp := rec.department;
        raise notice 'Required department: %', dp;
    end LOOP;
end $$;

--task5
select department, product, sum(sales) as subtotals
from order_details
GROUP BY ROLLUP(department, product)
order by department nulls last, product nulls last;

--task6
DO $$
DECLARE
    dept    VARCHAR(50);
    prod    VARCHAR(50);
    total   NUMERIC;
BEGIN
    FOR dept, prod, total IN
        SELECT
            department,
            product,
            SUM(sales)
        FROM order_details
        GROUP BY ROLLUP(department, product)
        ORDER BY department NULLS LAST, product NULLS LAST
    LOOP
        RAISE NOTICE 'Department: %, Product: %, Subtotal: %',
            COALESCE(dept, '*** GRAND TOTAL ***'),
            COALESCE(prod, '-- Subtotal --'),
            total;
    END LOOP;
END;
$$;

--task7
select 
    department, designation 
from employees
group by CUBE(department, designation)
order by department nulls last, designation nulls last;

--task8
SELECT
    emp_id,
    name,
    TO_CHAR(hire_date, 'DD-MM-YYYY') AS formatted_hire_date
FROM employees;

--task9
DO $$
DECLARE
    earliest date;
    latest date;
    difference int;
BEGIN
    select min(hire_date) into earliest from employees;
    select max(hire_date) into latest from employees;
    difference := extract(year from latest) - extract(year from earliest);
    raise notice 'difference: %', difference;
END $$;
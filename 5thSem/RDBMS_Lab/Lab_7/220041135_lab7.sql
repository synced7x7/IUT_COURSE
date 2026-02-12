DROP TABLE IF EXISTS t1;
CREATE TABLE t1 (data VARCHAR(50));

INSERT INTO t1 VALUES ('FALL 2014');
INSERT INTO t1 VALUES ('2014 CODE-B');
INSERT INTO t1 VALUES ('CODE-A 2014 CODE-D');
INSERT INTO t1 VALUES ('ADSHLHSALK');
INSERT INTO t1 VALUES ('FALL 2004');
INSERT INTO t1 VALUES ('SPRING 2010');
INSERT INTO t1 VALUES ('WINTER 2020');

DROP TABLE IF EXISTS employees;
CREATE TABLE employees (
    employee_id INTEGER,
    department VARCHAR(50),
    designation VARCHAR(50),
    hire_date DATE
);

INSERT INTO employees VALUES 
    (1, 'Sales', 'Manager', '2005-02-15'),
    (2, 'Sales', 'Manager', '2007-01-21'),
    (3, 'Human Resources', 'Assistant', '2010-05-10'),
    (4, 'IT', 'Developer', '2015-03-12'),
    (5, 'IT', 'Manager', '2008-11-20');

DROP TABLE IF EXISTS order_details;
CREATE TABLE order_details (
    order_id INTEGER,
    department VARCHAR(50),
    sales NUMERIC
);

INSERT INTO order_details VALUES 
    (1, 'Clothing', 500),
    (2, 'Clothing', 600),
    (3, 'Electronics', 1500),
    (4, 'Electronics', 1200),
    (5, 'Furniture', 1300),
    (6, 'Furniture', 1600);


--Task 1
select * 
from t1 
where (substring(data from '\d{4}'))::INTEGER >= 2010;

--Task 2
DO $$
DECLARE
    row_data VARCHAR(50);
    extracted_year VARCHAR(4);
BEGIN
    FOR row_data IN SELECT data FROM t1 LOOP
        extracted_year := SUBSTRING(row_data FROM '\d{4}');
        
        IF extracted_year IS NOT NULL THEN
            RAISE NOTICE 'Data: %, Year: %', row_data, extracted_year;
        ELSE
            RAISE NOTICE 'Data: %, Year: No year found', row_data;
        END IF;
    END LOOP;
END $$;


DROP TABLE IF EXISTS employee;

--TASK 1
CREATE TABLE employee (
    id SERIAL PRIMARY KEY,
    name TEXT,
    salary NUMERIC,
    designation TEXT
);

INSERT INTO employee (name, salary, designation) VALUES
('A', 28000, 'manager'),
('B', 35000, 'manager'),
('C', 25000, 'assistant manager'),
('D', 22000, 'assistant manager'),
('E', 18000, 'assistant manager');

DO $$
DECLARE 
	affected_rows INTEGER;
BEGIN
	UPDATE employee
	SET salary = salary * 1.10
	WHERE designation = 'manager'
	AND salary < 30000;

	GET DIAGNOSTICS affected_rows = ROW_COUNT;
	RAISE NOTICE 'Manager rows updated: %', affected_rows;

    UPDATE employee
    SET salary = salary * 0.90
    WHERE designation = 'assistant manager'
    AND salary > 20000;

	GET DIAGNOSTICS affected_rows = ROW_COUNT;
    RAISE NOTICE 'Assistant Manager rows updated: %', affected_rows;

END;
$$;


--TASK 2
DROP TABLE IF EXISTS transactions;

CREATE TABLE transactions (
    user_id INT,
    amount NUMERIC,
    t_date DATE
);

DROP TABLE IF EXISTS loan_type;

CREATE TABLE loan_type (
    scheme INT,
    installment_number INT,
    charge NUMERIC,
    min_trans NUMERIC
);

INSERT INTO loan_type VALUES
(1, 30, 0.05, 2000000),
(2, 20, 0.10, 1000000),
(3, 15, 0.15, 500000);

INSERT INTO transactions VALUES
(1, 600000, CURRENT_DATE),
(1, 500000, CURRENT_DATE),
(1, 300000, CURRENT_DATE),
(2, 600000, CURRENT_DATE),
(2, 500000, CURRENT_DATE),
(2, 300000, CURRENT_DATE),
(3, 600000, CURRENT_DATE),
(3, 500000, CURRENT_DATE),
(3, 300000, CURRENT_DATE);

CREATE OR REPLACE FUNCTION find_loan_scheme(p_user INT)
RETURNS INT AS $$
DECLARE 
	total_trans NUMERIC;
	rec RECORD;
BEGIN
	SELECT SUM(amount) INTO total_trans
	FROM transactions
	WHERE user_id = p_user;

	FOR rec IN
		SELECT * FROM loan_type ORDER BY min_trans DESC
	LOOP
		IF total_trans >= rec.min_trans THEN
			RETURN rec.scheme;
		END IF;
	END LOOP;

	RETURN NULL;
END;
$$ LANGUAGE plpgsql;

SELECT find_loan_scheme(1);

--TASK 3
DROP TABLE IF EXISTS customer;
CREATE TABLE customer (
    ssn INT PRIMARY KEY,
    name TEXT,
    surname TEXT,
    phonenum TEXT,
    plan INT
);

DROP TABLE IF EXISTS pricingplan;
CREATE TABLE pricingplan (
    code INT PRIMARY KEY,
    connectionfee NUMERIC,
    pricepersecond NUMERIC
);

DROP TABLE IF EXISTS phonecall;
CREATE TABLE phonecall (
    ssn INT,
    call_date DATE,
    call_time TIME,
    callednum TEXT,
    seconds INT
);

DROP TABLE IF EXISTS bill;
CREATE TABLE bill (
    ssn INT,
    month INT,
    year INT,
    amount NUMERIC
);

--task 3.1
CREATE OR REPLACE FUNCTION init_bill()
RETURNS TRIGGER AS $$
BEGIN
	INSERT INTO bill VALUES 
	(NEW.ssn, EXTRACT(MONTH FROM CURRENT_DATE),
	EXTRACT(YEAR FROM CURRENT_DATE), 0);
	RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER bill_init_trigger
AFTER INSERT ON customer
FOR EACH ROW
EXECUTE FUNCTION init_bill();

INSERT INTO customer (ssn, name, surname, phonenum, plan)
VALUES (1001, 'Rahim', 'Ahmed', '01711111111', 1);
INSERT INTO customer (ssn, name, surname, phonenum, plan)
VALUES (1002, 'Tasnif', 'Emran', '01636362669', 1);

SELECT * FROM bill;

--task 3.2
INSERT INTO pricingplan (code, connectionfee, pricepersecond) VALUES
(1, 50, 0.20),
(2, 75, 0.35),
(3, 100, 0.50);

CREATE OR REPLACE FUNCTION update_bill()
RETURNS TRIGGER AS $$
DECLARE 
	rate NUMERIC;
BEGIN
	SELECT pricepersecond INTO rate 
	FROM pricingplan
	WHERE code = (SELECT plan FROM customer WHERE ssn = NEW.ssn);

	UPDATE bill
	SET amount = amount + (rate  * NEW.seconds)
	WHERE ssn = NEW.ssn;

	RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER bill_update_trigger
AFTER INSERT ON phonecall
FOR EACH ROW
EXECUTE FUNCTION update_bill();

INSERT INTO phonecall
(ssn, call_date, call_time, callednum, seconds)
VALUES
(1001, CURRENT_DATE, CURRENT_TIME, '01899999999', 120);

SELECT * FROM bill WHERE ssn = 1001;


--task 4.1
CREATE TABLE student (
    id VARCHAR(20),
    admission_date DATE,
    department CHAR(1),
    program CHAR(1),
    section CHAR(1)
);

CREATE SEQUENCE student_seq START 1;


CREATE OR REPLACE FUNCTION gen_id(adm DATE, d CHAR, p CHAR, s CHAR)
RETURNS VARCHAR AS $$
DECLARE
    yy TEXT;
    seq TEXT;
BEGIN
    yy := TO_CHAR(adm, 'YY');
    seq := LPAD(nextval('public.student_seq')::TEXT, 2, '0');
    RETURN yy || '00' || d || p || s || seq;
END;
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION student_id_trigger()
RETURNS TRIGGER AS $$
BEGIN
    NEW.id := gen_id(NEW.admission_date, NEW.department, NEW.program, NEW.section);
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER student_insert_trigger
BEFORE INSERT ON student
FOR EACH ROW
EXECUTE FUNCTION student_id_trigger();

CREATE TABLE accounts (
    id INT,
    name TEXT,
    acccode INT,
    balance NUMERIC,
    lastdateofinterest DATE
);

CREATE TABLE accountproperties (
    id INT,
    name TEXT,
    interestrate NUMERIC,
    gp INT
);

CREATE OR REPLACE PROCEDURE update_interest()
LANGUAGE plpgsql
AS $$
DECLARE
    rec RECORD;
    days_diff INT;
BEGIN
    FOR rec IN
        SELECT a.id, a.balance, a.lastdateofinterest,
               p.interestrate, p.gp
        FROM accounts a
        JOIN accountproperties p ON a.acccode = p.id
    LOOP
        days_diff := CURRENT_DATE - rec.lastdateofinterest;

        IF (rec.gp = 1 AND days_diff >= 1) OR
           (rec.gp = 2 AND days_diff >= 30) OR
           (rec.gp = 3 AND days_diff >= 365) THEN

            UPDATE accounts
            SET balance = balance + (balance * rec.interestrate / 100),
                lastdateofinterest = CURRENT_DATE
            WHERE id = rec.id;
        END IF;
    END LOOP;
END;
$$;

CALL update_interest();


DROP TABLE IF EXISTS employees;
CREATE TABLE employees (
	emp_id SERIAL PRIMARY KEY,
	name TEXT,
	salary INTEGER,
	dept_id INTEGER
);

INSERT INTO employees (name, salary, dept_id) VALUES
('Alice', 60000, 10),
('Bob', 45000, 20),
('Charlie', 55000, 20),
('David', 40000, 30);


-- task1 --
DO $$
DECLARE
	cur_emp CURSOR FOR SELECT emp_id, name, salary FROM employees WHERE salary > 50000;
	r RECORD;
BEGIN
	OPEN cur_emp;
	LOOP
		FETCH cur_emp INTO r;
		EXIT WHEN NOT FOUND;
		RAISE NOTICE 'Employee: %, Salary: %', r.name, r.salary;
	END LOOP;
	CLOSE cur_emp;
END;
$$;

-- task2 --
DO $$
DECLARE
	 cur_update CURSOR FOR SELECT emp_id, salary FROM employees WHERE dept_id = 20 FOR UPDATE; 
	 --without for update it is in read only mode
	r RECORD;
BEGIN
	OPEN cur_update;
	LOOP
		FETCH cur_update INTO r;
		EXIT WHEN NOT FOUND;

		UPDATE employees
		SET salary = salary*1.10
		WHERE CURRENT OF cur_update; --CURRENT means where the cursor is currently pointing
	END LOOP;
	CLOSE cur_update;
END;
$$;

SELECT * FROM employees;


-- task3 --
DROP TABLE IF EXISTS students;
CREATE TABLE students (
    student_id SERIAL PRIMARY KEY,
    name TEXT,
    created_at TIMESTAMP
);

CREATE OR REPLACE FUNCTION set_created_at()
RETURNS TRIGGER LANGUAGE plpgsql AS
$$
BEGIN 
	NEW.created_at := CURRENT_TIMESTAMP;
	RETURN NEW;
END;
$$;

CREATE TRIGGER trg_set_created_at
BEFORE INSERT ON students
FOR EACH ROW 
EXECUTE FUNCTION set_created_at();

INSERT INTO students(name) VALUES ('Tasnif');
INSERT INTO students(name) VALUES ('Labonno');
SELECT * FROM students;

-- task 4 --
DROP TABLE IF EXISTS emp_audit;
CREATE TABLE emp_audit (
    emp_id INTEGER,
    inserted_at TIMESTAMP
);

CREATE OR REPLACE FUNCTION emp_audit_insert()
RETURNS TRIGGER LANGUAGE plpgsql AS
$$
BEGIN
    INSERT INTO emp_audit(emp_id, inserted_at)
    VALUES (NEW.emp_id, CURRENT_TIMESTAMP);
    RETURN NEW;
END;
$$;

CREATE TRIGGER trg_emp_audit
AFTER INSERT ON employees
FOR EACH ROW
EXECUTE FUNCTION emp_audit_insert();

INSERT INTO employees(name, salary, dept_id) VALUES ('Eve', 70000, 10);
SELECT * FROM emp_audit;




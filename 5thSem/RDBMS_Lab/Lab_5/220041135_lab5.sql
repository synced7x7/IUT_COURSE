--task1
CREATE TABLE IF NOT EXISTS project_tasks (
    task_id VARCHAR(10) PRIMARY KEY,
    task_name VARCHAR(100) NOT NULL,
    depends_on VARCHAR(10),
    duration_days INT NOT NULL
);

INSERT INTO project_tasks (task_id, task_name, depends_on, duration_days) VALUES
(T1, Setup Environment, NULL, 2),
(T2, Design Database, T1, 3),
(T3, Develop Backend, T2, 5),
(T4, Develop Frontend, T2, 4),
(T5, Integrate Backend, T3, 2),
(T6, Integrate Frontend, T4, 2),
(T7, Final Testing, T5, 3),
(T7, Final Testing, T6, 3);

WITH RECURSIVE task_dependencies AS (
    SELECT 
        task_id,
        depends_on
    FROM project_tasks
    WHERE depends_on IS NOT NULL
    
    UNION
    
    SELECT 
        td.task_id,
        pt.depends_on
    FROM task_dependencies td
    JOIN project_tasks pt ON td.depends_on = pt.task_id
    WHERE pt.depends_on IS NOT NULL
)
SELECT 
    task_id,
    depends_on
FROM task_dependencies
ORDER BY task_id, depends_on;

--task2
CREATE TABLE IF NOT EXISTS employee_ranking (
    emp_id INT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    department VARCHAR(50) NOT NULL,
    salary DECIMAL(10, 2) NOT NULL
);

INSERT INTO employee_ranking (emp_id, name, department, salary) VALUES
(1, Hasan, IT, 80000),
(2, Tania, IT, 75000),
(3, Riad, HR, 60000),
(4, Mitu, HR, 60000);

SELECT 
    emp_id,
    name,
    department,
    salary,
    DENSE_RANK() OVER (PARTITION BY department ORDER BY salary DESC) AS dept_rank
FROM employee
ORDER BY department, salary DESC;

--task3
CREATE TABLE IF NOT EXISTS employee_salary (
    emp_id INT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    salary DECIMAL(10, 2) NOT NULL
);

INSERT INTO employee_salary (emp_id, name, salary) VALUES
(1, Ayan, 40000),
(2, Bithi, 45000),
(3, Chayan, 43000),
(4, Danish, 47000),
(5, Elina, 42000),
(6, Farhan, 48000),
(7, Gita, 46000),
(8, Hasan, 44000),
(9, Iqbal, 41000),
(10, Joya, 45000);

SELECT 
    emp_id,
    name,
    salary,
    salary - LAG(salary) OVER (ORDER BY salary) AS salary_difference
FROM employee
ORDER BY salary;

--task4
CREATE TABLE IF NOT EXISTS employee_hierarchy (
    emp_id INT PRIMARY KEY,
    emp_name VARCHAR(100) NOT NULL,
    manager_id INT,
    department VARCHAR(50) NOT NULL
);

INSERT INTO employee_hierarchy (emp_id, emp_name, manager_id, department) VALUES
(1, Rahim, NULL, Admin),
(2, Karim, 1, IT),
(3, Salma, 1, Finance),
(4, Anika, 2, IT),
(5, Fahim, 2, IT),
(6, Rafi, 3, Finance),
(7, Nusrat, NULL, HR),
(8, Imran, 7, HR),
(9, Tithi, 8, HR);

WITH RECURSIVE hierarchy AS (
    SELECT 
        emp_id,
        emp_name,
        manager_id,
        department,
        1 AS level,
        CAST(emp_id AS VARCHAR(100)) AS path
    FROM employee
    WHERE manager_id IS NULL
    
    UNION ALL
    
    SELECT 
        e.emp_id,
        e.emp_name,
        e.manager_id,
        e.department,
        h.level + 1,
        h.path || ',' || CAST(e.emp_id AS VARCHAR(100))
    FROM employee e
    JOIN hierarchy h ON e.manager_id = h.emp_id
),
subordinates AS (
    SELECT 
        h1.emp_id,
        COUNT(h2.emp_id) AS total_subordinates
    FROM hierarchy h1
    LEFT JOIN hierarchy h2 ON h2.path LIKE h1.path || ',%'
    GROUP BY h1.emp_id
)
SELECT 
    h.emp_id,
    h.emp_name,
    h.manager_id,
    h.level,
    s.total_subordinates
FROM hierarchy h
JOIN subordinates s ON h.emp_id = s.emp_id
ORDER BY h.level, h.emp_id;

DROP TABLE IF EXISTS project_tasks;
DROP TABLE IF EXISTS employee_ranking;
DROP TABLE IF EXISTS employee_salary;
DROP TABLE IF EXISTS employee_hierarchy;
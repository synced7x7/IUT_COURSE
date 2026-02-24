--task1
CREATE TABLE IF NOT EXISTS project_tasks (
    task_id VARCHAR(10) PRIMARY KEY,
    task_name VARCHAR(100) NOT NULL,
    depends_on VARCHAR(10),
    duration_days INT NOT NULL
);

INSERT INTO project_tasks (task_id, task_name, depends_on, duration_days) VALUES
('T1', 'Setup Environment', NULL, 2),
('T2', 'Design Database', 'T1', 3),
('T3', 'Develop Backend', 'T2', 5),
('T4', 'Develop Frontend', 'T2', 4),
('T5', 'Integrate Backend', 'T3', 2),
('T6', 'Integrate Frontend', 'T4', 2),
('T7', 'Final Testing', 'T5', 3),
('T8', 'Final Testing', 'T6', 3);

With RECURSIVE task_dep as (
    select task_id, depends_on 
    from project_tasks
    where depends_on is not NULL

    UNION

    select td.task_id, pt.depends_on
    from task_dep td 
    join project_tasks pt on td.depends_on = pt.task_id
    where pt.depends_on is not NULL
)
select task_id, depends_on
from task_dep
order by task_id, depends_on;

--task2
CREATE TABLE IF NOT EXISTS employee_ranking (
    emp_id INT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    department VARCHAR(50) NOT NULL,
    salary DECIMAL(10, 2) NOT NULL
);

INSERT INTO employee_ranking (emp_id, name, department, salary) VALUES
(1, 'Hasan', 'IT', 80000),
(2, 'Tania', 'IT', 75000),
(3, 'Riad', 'HR', 60000),
(4, 'Mitu', 'HR', 60000);

select 
    emp_id, 
    name, 
    department, 
    salary,
    dense_rank() over (partition by department order by salary desc) as Dept_Rank
from employee_ranking
order by department, salary desc;

--task3
CREATE TABLE IF NOT EXISTS employee_salary (
    emp_id INT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    salary DECIMAL(10, 2) NOT NULL
);

INSERT INTO employee_salary (emp_id, name, salary) VALUES
(1, 'Ayan', 40000),
(2, 'Bithi', 45000),
(3, 'Chayan', 43000),
(4, 'Danish', 47000),
(5, 'Elina', 42000),
(6, 'Farhan', 48000),
(7, 'Gita', 46000),
(8, 'Hasan', 44000),
(9, 'Iqbal', 41000),
(10, 'Joya', 45000);

select emp_id, 
    name, 
    salary,
    salary - lag(salary) over(order by salary) as Salary_Difference
from employee_salary;

--task4 
CREATE TABLE IF NOT EXISTS employee_hierarchy (
    emp_id INT PRIMARY KEY,
    emp_name VARCHAR(100) NOT NULL,
    manager_id INT,
    department VARCHAR(50) NOT NULL
);

INSERT INTO employee_hierarchy (emp_id, emp_name, manager_id, department) VALUES
(1, 'Rahim', NULL, 'Admin'),
(2, 'Karim', 1, 'IT'),
(3, 'Salma', 1, 'Finance'),
(4, 'Anika', 2, 'IT'),
(5, 'Fahim', 2, 'IT'),
(6, 'Rafi', 3, 'Finance'),
(7, 'Nusrat', NULL, 'HR'),
(8, 'Imran', 7, 'HR'),
(9, 'Tithi', 8, 'HR');

WITH RECURSIVE emp_dep as (
    select 
        emp_id, 
        emp_name,
        manager_id,
        department, 
        1 as level,
        cast(emp_id as TEXT) as path
    from employee_hierarchy
    where manager_id is NULL

    UNION

    select 
        e.emp_id,
        e.emp_name,
        e.manager_id,
        e.department,
        h.level + 1,
        h.path || ',' || cast(e.emp_id as TEXT)
    from employee_hierarchy e 
    join emp_dep h on e.manager_id = h.emp_id
),
subordinates as (
    select 
        h1.emp_id, 
        count(h2.emp_id) as total_subordinates
    from emp_dep h1
    left join emp_dep h2 on h2.path like h1.path || ',%'
    group by h1.emp_id
)
select 
    h.emp_id,
    h.emp_name,
    h.department,
    h.manager_id, 
    h.level,
    h.path,
    s.total_subordinates
FROM emp_dep h
JOIN subordinates s ON h.emp_id = s.emp_id
ORDER BY h.level, h.emp_id;



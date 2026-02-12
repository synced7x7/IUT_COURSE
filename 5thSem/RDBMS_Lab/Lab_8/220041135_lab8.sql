--task 1.1
select
	region,
	country,
	city,
	SUM(quantity * unit_price * (1 - discount_percent/100)) AS total_revenue
From sales_transactions
group by rollup(region, country, city)
order by region, country, city;

--task 1.2
select 
	category,
	subcategory,
	region,
	SUM(quantity * unit_price * (1 - discount_percent/100)) AS total_revenue
from sales_transactions
group by cube(category, subcategory, region)
order by category, subcategory, region;

--task 2.1
select 
	transaction_id,
	TO_CHAR(transaction_date, 'Day, DD Month YYYY') as formatted_transaction_date
from sales_transactions
order by transaction_id;

--task 2.2
select 
	to_char(transaction_date, 'Mon-YYYY') as month_year,
	SUM(quantity * unit_price * (1 - discount_percent/100)) AS total_revenue
from sales_transactions
group by to_char(transaction_date, 'Mon-YYYY')
order by to_char(transaction_date, 'Mon-YYYY');

--task 2.3
select 
	transaction_id,
	transaction_date,
	(transaction_date + INTERVAL '12 months')::DATE AS warranty_expiry_date
from sales_transactions
where category = 'Electronics'
order by transaction_id;

--task 2.4
select 
	transaction_id,
	transaction_date,
	DATE '2024-03-01'- transaction_date AS days_since_transaction
from sales_transactions;

--task 2.5
select 
	transaction_id,
	transaction_date
from sales_transactions
WHERE transaction_date  < DATE '2024-03-01' - INTERVAL '30 days';

	
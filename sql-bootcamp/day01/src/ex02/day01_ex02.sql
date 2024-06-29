SELECT t1.pizza_name AS pizza_name FROM menu AS t1
UNION
SELECT t2.pizza_name AS pizza_name FROM menu AS t2
ORDER BY pizza_name DESC;
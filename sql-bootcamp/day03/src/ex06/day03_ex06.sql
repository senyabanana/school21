WITH t1 AS
(SELECT m.pizza_name AS pizza_name, pi.name AS pizzeria_name1,
m.price AS price, pi.id
FROM menu AS m
INNER JOIN pizzeria AS pi
ON m.pizzeria_id = pi.id),
t2 AS
(SELECT m.pizza_name AS pizza_name, pi.name AS pizzeria_name2,
m.price AS price, pi.id
FROM menu AS m
INNER JOIN pizzeria AS pi
ON m.pizzeria_id = pi.id)
SELECT t1.pizza_name, t1.pizzeria_name1, t2.pizzeria_name2, t1.price
FROM t1
INNER JOIN t2
ON t1.pizza_name = t2.pizza_name AND t1.price = t2.price
WHERE t1.id > t2.id
ORDER BY 1;
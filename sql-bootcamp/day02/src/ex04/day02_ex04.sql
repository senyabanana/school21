SELECT m.pizza_name AS pizza_name,
pi.name AS pizzeria_name,
m.price AS price
FROM menu AS m
INNER JOIN pizzeria AS pi
ON m.pizzeria_id = pi.id
WHERE m.pizza_name IN ('mushroom pizza', 'pepperoni pizza')
ORDER BY 1, 2;
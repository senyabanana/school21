SELECT m2.pizza_name, m2.price, pi.name
FROM
(SELECT m.id
FROM menu AS m
EXCEPT
SELECT po.menu_id
FROM person_order AS po) AS m1
INNER JOIN menu m2
ON m1.id = m2.id
INNER JOIN pizzeria pi
ON m2.pizzeria_id = pi.id
ORDER BY 1, 2;
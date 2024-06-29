SELECT m.pizza_name, pi.name AS pizzeria_name
FROM menu AS m
INNER JOIN pizzeria AS pi
ON m.pizzeria_id = pi.id
INNER JOIN person_order AS po
ON m.id = po.menu_id
INNER JOIN person AS p
ON po.person_id = p.id
WHERE p.name IN ('Denis', 'Anna')
ORDER BY 1, 2;
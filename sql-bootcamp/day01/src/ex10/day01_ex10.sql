SELECT p.name AS person_name,
m.pizza_name AS pizza_name,
pi.name AS pizzeria_name
FROM person_order po
INNER JOIN person p
ON p.id = po.person_id
INNER JOIN menu m
ON m.id = po.menu_id
INNER JOIN pizzeria pi
ON pi.id = m.pizzeria_id
ORDER BY person_name, pizza_name, pizzeria_name;
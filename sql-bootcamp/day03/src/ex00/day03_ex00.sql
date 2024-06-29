SELECT m.pizza_name, m.price,
pi.name AS pizzeria_name, pv.visit_date
FROM menu m
INNER JOIN pizzeria AS pi
ON m.pizzeria_id = pi.id
INNER JOIN person_visits AS pv
ON pi.id = pv.pizzeria_id
INNER JOIN person AS p
ON pv.person_id = p.id
WHERE p.name = 'Kate' AND m.price BETWEEN 800 AND 1000
ORDER BY 1, 2, 3;
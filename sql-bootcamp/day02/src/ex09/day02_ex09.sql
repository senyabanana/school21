SELECT p.name
FROM person AS p
INNER JOIN person_order AS po
ON p.id = po.person_id
INNER JOIN menu AS m
ON po.menu_id = m.id
WHERE p.gender = 'female' AND m.pizza_name = 'pepperoni pizza'
INTERSECT
SELECT p2.name
FROM person AS p2
INNER JOIN person_order AS po2
ON p2.id = po2.person_id
INNER JOIN menu AS m2
ON po2.menu_id = m2.id
WHERE p2.gender = 'female' AND m2.pizza_name = 'cheese pizza'
ORDER BY 1;
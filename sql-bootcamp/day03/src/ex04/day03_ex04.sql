(SELECT pi.name AS pizzeria_name
FROM pizzeria pi
INNER JOIN menu AS m
ON pi.id = m.pizzeria_id
INNER JOIN person_order AS po
ON m.id = po.menu_id
INNER JOIN person AS p
ON po.person_id = p.id
WHERE p.gender = 'female'
EXCEPT
SELECT pi.name AS pizzeria_name
FROM pizzeria pi
INNER JOIN menu AS m
ON pi.id = m.pizzeria_id
INNER JOIN person_order AS po
ON m.id = po.menu_id
INNER JOIN person AS p
ON po.person_id = p.id
WHERE p.gender = 'male')
UNION
(SELECT pi.name AS pizzeria_name
FROM pizzeria pi
INNER JOIN menu AS m
ON pi.id = m.pizzeria_id
INNER JOIN person_order AS po
ON m.id = po.menu_id
INNER JOIN person AS p
ON po.person_id = p.id
WHERE p.gender = 'male'
EXCEPT
SELECT pi.name AS pizzeria_name
FROM pizzeria pi
INNER JOIN menu AS m
ON pi.id = m.pizzeria_id
INNER JOIN person_order AS po
ON m.id = po.menu_id
INNER JOIN person AS p
ON po.person_id = p.id
WHERE p.gender = 'female')
ORDER BY 1;
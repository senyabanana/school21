SELECT p.name
FROM person AS p
INNER JOIN person_order AS po
ON p.id = po.person_id
INNER JOIN menu AS m
ON po.menu_id = m.id
INNER JOIN pizzeria AS pi
ON m.pizzeria_id = pi.id
WHERE p.address IN ('Moscow', 'Samara') AND p.gender = 'male'
AND m.pizza_name IN ('pepperoni pizza', 'mushroom pizza')
ORDER BY 1 DESC;
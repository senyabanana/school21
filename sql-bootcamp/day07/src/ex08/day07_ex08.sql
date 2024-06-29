SELECT p.address,
       pi.name,
       count(*) AS count_of_orders
FROM person_order AS po
INNER JOIN person AS p ON po.person_id = p.id
INNER JOIN menu AS m ON po.menu_id = m.id
INNER JOIN pizzeria AS pi ON m.pizzeria_id = pi.id
GROUP BY 1, 2
ORDER BY 1, 2;
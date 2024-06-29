WITH order_table AS
(SELECT pi.name AS name, count(person_id), 'order' AS action_type
FROM person_order AS po
INNER JOIN menu AS m ON po.menu_id = m.id
INNER JOIN pizzeria AS pi ON m.pizzeria_id = pi.id
GROUP BY name
ORDER BY 3, 2 DESC LIMIT 3),
visit_table AS
(SELECT pi.name AS name, count(person_id), 'visit' AS action_type
FROM person_visits AS pv
INNER JOIN pizzeria AS pi ON pv.pizzeria_id = pi.id
GROUP BY name
ORDER BY 3, 2 DESC LIMIT 3)
SELECT * FROM order_table
UNION
SELECT * FROM visit_table
ORDER BY 3, 2 DESC;
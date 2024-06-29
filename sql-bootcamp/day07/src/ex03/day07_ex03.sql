WITH order_table AS
(SELECT pi.name AS name, count(person_id) AS count, 'order' AS action_type
FROM person_order AS po
INNER JOIN menu AS m ON po.menu_id = m.id
INNER JOIN pizzeria AS pi ON m.pizzeria_id = pi.id
GROUP BY name
ORDER BY 2 DESC),
visit_table AS
(SELECT pi.name AS name, count(person_id) AS count, 'visit' AS action_type
FROM person_visits AS pv
INNER JOIN pizzeria AS pi ON pv.pizzeria_id = pi.id
GROUP BY name
ORDER BY 2 DESC),
all_table AS
(SELECT * FROM order_table
UNION
SELECT * FROM visit_table
ORDER BY 2 DESC)
SELECT name, sum(count) AS total_count FROM all_table
GROUP BY name
ORDER BY 2 DESC, 1;
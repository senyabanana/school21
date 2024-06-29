SELECT pi.name,
       count(pizzeria_id) AS count_of_orders,
       round(avg(m.price), 2) AS average_price,
       max(m.price) AS max_price,
       min(m.price) AS min_price
FROM person_order AS po
INNER JOIN menu AS m ON po.menu_id = m.id
INNER JOIN pizzeria AS pi ON m.pizzeria_id = pi.id
GROUP BY name
ORDER BY 1;
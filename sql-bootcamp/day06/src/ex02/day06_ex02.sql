SELECT p.name,
       m.pizza_name,
       m.price,
       (m.price - m.price * pd.discount / 100) AS discount_price,
       pi.name AS pizzeria_name
FROM person_order AS po
INNER JOIN menu AS m ON po.menu_id = m.id
INNER JOIN person AS p ON po.person_id = p.id
INNER JOIN person_discounts AS pd ON p.id = pd.person_id
AND m.pizzeria_id = pd.pizzeria_id
INNER JOIN pizzeria AS pi ON pd.pizzeria_id = pi.id
ORDER BY 1, 2;


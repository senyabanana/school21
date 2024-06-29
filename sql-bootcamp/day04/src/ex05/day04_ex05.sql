CREATE VIEW v_price_with_discount AS
SELECT p.name, m.pizza_name, m.price,
round(price - price * 0.1) AS discount_price
FROM menu AS m
INNER JOIN person_order AS po ON m.id = po.menu_id
INNER JOIN person AS p ON po.person_id = p.id
ORDER BY 1, 2;
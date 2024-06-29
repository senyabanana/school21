SELECT po.order_date, concat(p.name || ' (age:' || p.age || ')') AS person_information
FROM person_order AS po
NATURAL JOIN (SELECT p.id AS person_id, p.name, p.age FROM person AS p) AS p
ORDER BY order_date, person_information;
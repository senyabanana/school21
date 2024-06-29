SELECT po.order_date, concat(p.name || ' (age:' || p.age || ')') AS person_information
FROM person_order AS po
INNER JOIN person p
ON p.id = po.person_id
ORDER BY order_date, person_information;
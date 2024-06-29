SELECT DISTINCT p.name
FROM person_order AS po
INNER JOIN person AS p ON po.person_id = p.id
ORDER BY 1;
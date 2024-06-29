SELECT m.id
FROM menu AS m
EXCEPT
SELECT po.menu_id
FROM person_order AS po
ORDER BY 1;
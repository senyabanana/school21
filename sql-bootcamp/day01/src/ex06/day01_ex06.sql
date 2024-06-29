SELECT po.order_date AS action_date, p.name AS person_name FROM person_order AS po
INNER JOIN person AS p
ON p.id = po.person_id
INTERSECT
SELECT pv.visit_date AS action_date, p2.name AS person_name FROM person_visits AS pv
INNER JOIN  person AS p2
ON p2.id = pv.person_id
ORDER BY action_date, person_name DESC;
SELECT p.name, count(person_id) AS count_of_visits
FROM person_visits AS pv
INNER JOIN person AS p ON pv.person_id = p.id
GROUP BY name
HAVING count(person_id) > 3;
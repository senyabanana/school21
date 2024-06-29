SELECT distance AS total_cost,
       concat('{' || route || ',' || last_point || '}') AS tour
FROM tsp
WHERE last_point = 'A'
AND distance = (SELECT min(distance) FROM tsp WHERE length(route) = 7 AND last_point = 'A')
ORDER BY 1, 2;
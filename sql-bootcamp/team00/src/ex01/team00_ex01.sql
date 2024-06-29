SELECT distance AS total_cost,
       concat('{' || route || ',' || last_point || '}') AS tour
FROM tsp
WHERE last_point = 'A' AND length(route) = 7
ORDER BY 1, 2;
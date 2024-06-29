SET enable_seqscan =off;
EXPLAIN ANALYZE
SELECT m.pizza_name, pi.name FROM menu AS m
INNER JOIN pizzeria AS pi ON m.pizzeria_id = pi.id;
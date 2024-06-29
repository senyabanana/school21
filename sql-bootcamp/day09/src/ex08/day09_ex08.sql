CREATE OR REPLACE FUNCTION fnc_fibonacci(in pstop integer DEFAULT 10)
RETURNS SETOF integer AS
$$
    WITH RECURSIVE fib(a, b) AS
    (VALUES (0, 1)
     UNION ALL
     SELECT greatest(a, b), a + b AS a FROM fib
     WHERE b < pstop)
     SELECT a FROM fib;
$$
LANGUAGE sql;

SELECT * FROM fnc_fibonacci(100);
SELECT * FROM fnc_fibonacci();
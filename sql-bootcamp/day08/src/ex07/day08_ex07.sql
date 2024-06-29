--Session #1
BEGIN;
UPDATE pizzeria SET rating = 2 WHERE name = 'DoDo Pizza';
UPDATE pizzeria SET rating = 2 WHERE name = 'Dominos';
COMMIT;

--Session #2
BEGIN;
UPDATE pizzeria SET rating = 1 WHERE name = 'Dominos';
UPDATE pizzeria SET rating = 1 WHERE name = 'DoDo Pizza';
COMMIT;
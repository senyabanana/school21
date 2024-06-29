CREATE TABLE ways (
    point1 varchar NOT NULL,
    point2 varchar NOT NULL,
    cost integer NOT NULL
);

INSERT INTO ways (point1, point2, cost)
VALUES ('A', 'B', 10);

INSERT INTO ways (point1, point2, cost)
VALUES ('A', 'C', 15);

INSERT INTO ways (point1, point2, cost)
VALUES ('A', 'D', 20);

INSERT INTO ways (point1, point2, cost)
VALUES ('B', 'A', 10);

INSERT INTO ways (point1, point2, cost)
VALUES ('B', 'C', 35);

INSERT INTO ways (point1, point2, cost)
VALUES ('B', 'D', 25);

INSERT INTO ways (point1, point2, cost)
VALUES ('C', 'A', 15);

INSERT INTO ways (point1, point2, cost)
VALUES ('C', 'B', 35);

INSERT INTO ways (point1, point2, cost)
VALUES ('C', 'D', 30);

INSERT INTO ways (point1, point2, cost)
VALUES ('D', 'A', 20);

INSERT INTO ways (point1, point2, cost)
VALUES ('D', 'B', 25);

INSERT INTO ways (point1, point2, cost)
VALUES ('D', 'C', 30);

CREATE VIEW tsp As
WITH RECURSIVE journey AS
(SELECT w.point1 AS route,
        w.point2 AS last_point,
        w.cost AS distance
FROM ways AS w
WHERE w.point1 = 'A'
UNION
SELECT previous.route || ',' || previous.last_point AS route,
       current.point2 AS last_point,
       current.cost + previous.distance AS distance
FROM ways AS current
INNER JOIN journey AS previous ON current.point1 = previous.last_point
WHERE previous.route NOT LIKE '%' || previous.last_point || '%')
SELECT * FROM journey;

-- SELECT * FROM ways;
-- SELECT * FROM tsp;
-- DROP TABLE ways;
-- DROP VIEW tsp;
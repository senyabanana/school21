INSERT INTO currency(id, name, rate_to_usd, updated)
VALUES(100, 'EUR', 0.85, '2022-01-01 13:29');
INSERT INTO currency(id, name, rate_to_usd, updated)
VALUES(100, 'EUR', 0.79, '2022-01-08 13:29');

WITH current_cource AS
    (SELECT b.user_id,
            b.money,
            b.updated AS balance_update,
            c.name AS currency_name,
            c.rate_to_usd,
            c.updated AS currency_update
    FROM balance AS b
    INNER JOIN currency AS c ON b.currency_id = c.id),
    balance_greater_or_equal_currency AS
    (SELECT cc.user_id AS id,
            cc.currency_name,
            cc.money,
            cc.balance_update,
            min(cc.balance_update - cc.currency_update) AS difference
    FROM current_cource AS cc
    WHERE cc.balance_update >= cc.currency_update
    GROUP BY 1, 2, 3, 4),
    balance_less_or_equal_currency AS
    (SELECT cc.user_id AS id,
            cc.currency_name,
            cc.money,
            cc.balance_update,
            max(cc.balance_update - cc.currency_update) AS difference
    FROM current_cource AS cc
    WHERE cc.balance_update <= cc.currency_update
    GROUP BY 1, 2, 3, 4),
    full_filter AS
    (SELECT le.id,
            le.currency_name,
            le.money,
            le.balance_update,
            coalesce(ge.difference, le.difference) AS new_difference
    FROM balance_greater_or_equal_currency AS ge
    FULL JOIN balance_less_or_equal_currency AS le ON ge.id = le.id
    AND ge.currency_name = le.currency_name
    AND ge.money = le.money AND ge.balance_update = le.balance_update)

SELECT coalesce(u.name, 'not defined') AS name,
       coalesce(u.lastname, 'not defined') AS lastname,
       ff.currency_name,
       ff.money * c.rate_to_usd AS currency_in_usd
FROM full_filter AS ff
LEFT JOIN "user" AS u ON ff.id = u.id
LEFT JOIN currency AS c ON ff.new_difference = (ff.balance_update - c.updated)
AND ff.currency_name = c.name
ORDER BY 1 DESC, 2, 3;
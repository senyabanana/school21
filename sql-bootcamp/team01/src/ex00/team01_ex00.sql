WITH user_balance AS
         (SELECT coalesce(u.name, 'not defined')     AS name,
                 coalesce(u.lastname, 'not defined') AS lastname,
                 b.type,
                 sum(b.money)                        AS volume,
                 b.currency_id
          FROM "user" AS u
                   FULL OUTER JOIN balance AS b ON u.id = b.user_id
          GROUP BY 3, 2, 1, 5),
     max_date AS
         (SELECT id,
                 max(updated) AS last_update
          FROM currency
          GROUP BY id),
     table_currency AS
         (SELECT c2.id,
                 c2.name,
                 c2.rate_to_usd,
                 md.last_update
          FROM max_date AS md
                   JOIN currency AS c2 ON md.last_update = c2.updated AND md.id = c2.id)

SELECT ub.name,
       ub.lastname,
       ub.type,
       ub.volume,
       coalesce(tc.name, 'not defined')        AS currency_name,
       coalesce(tc.rate_to_usd, 1)             AS last_rate_to_usd,
       ub.volume * coalesce(tc.rate_to_usd, 1) AS total_volume_in_usd
FROM user_balance AS ub
         FULL JOIN table_currency AS tc ON ub.currency_id = tc.id
ORDER BY 1 DESC, 2, 3;


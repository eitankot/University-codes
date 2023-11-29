with running_count(edate, nofparties) as (select edate, count(pname) from running group by edate)
select edate, kno
from running_count natural join election
where nofparties >= all (select nofparties from running_count)
;
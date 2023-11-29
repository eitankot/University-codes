select distinct pname
from  votes v natural join election e natural join city c
group by pname, nofvotes
having count(*)<=all
(
	select count(*)
	from votes natural join election natural join city c
	where kno= 3 and not exists(
	select region
	from votes natural join election natural join city c
	where pname=v.pname and region='hills'
	)
)
;

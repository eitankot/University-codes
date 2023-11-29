select distinct pname,region, nofvotes
from  votes v natural join city c natural join election e
where kno = 3
group by kno,pname, region, nofvotes
;
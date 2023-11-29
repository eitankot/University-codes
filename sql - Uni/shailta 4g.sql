select r1.pname, r2.pname
from running r1, running r2
where r1.edate = r2.edate and r1.pname < r2.pname
group by r1.pname, r2.pname
having count(r1.edate) = (
	select count(*) 
	from running 
	where pname=r1.pname)
	   and count(r1.edate) = (select count(*) 
							  from running 
							  where pname=r2.pname)
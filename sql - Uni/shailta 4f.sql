with maxvotes(votes) as (
	select max(totalvotes) 
	from running natural join election 
	where kno=3)
select pname
from running natural join election, maxvotes
where kno=3 and totalvotes < maxvotes.votes and 
	totalvotes >= all 
	(select totalvotes 
	from running natural join election 
	where totalvotes < maxvotes.votes and kno=3)
select distinct c.cname, c.region 
from  votes v natural join city c
where cid NOT IN
(select cid
 from votes v natural join city c
 where	pname='life party' and  nofvotes>0);
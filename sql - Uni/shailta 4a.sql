select pname, cname
from  votes v natural join city c
where cname='ryde end' and  v.nofvotes>0 and v.edate='2020-03-02'
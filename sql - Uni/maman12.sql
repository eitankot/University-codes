SET datestyle = ISO, DMY;

drop table if exists votes  ;
drop table  if exists running ;
drop table  if exists city ;
drop table  if exists party ;
drop table  if exists election ;

-- ex a

create table election
(edate date, kno int, primary key(edate));

create table party
(pname char(20), symbol char(5), primary key(pname));

create table running
(edate date ,pname char(20), chid numeric(5,0),
totalvotes int default 0,
primary key(edate,pname),
foreign key(edate) references election,
foreign key(pname) references party);
 
create table city
(cid numeric(5,0) ,cname varchar(20), region varchar(20),
primary key(cid));
 
 
create table votes
(cid numeric(5,0) ,edate date,pname char(20), nofvotes int check (nofvotes > 0),
primary key(cid, edate ,pname),
foreign key(cid) references city,
foreign key(edate) references election,
foreign key(pname) references party);
 
-- ex b

create function trig() returns trigger as $$
declare
	votesadded integer;
begin
	votesadded := new.nofvotes;
	if TG_OP='UPDATE' then 
		votesadded := votesadded - old.nofvotes;
	end if;
	update running
		set totalvotes = totalvotes + votesadded
		where edate = new.edate and pname = new.pname;
	return new;
end; $$ language plpgsql;

create trigger T1
after insert or update
on votes
for each row
execute procedure trig();

-- ex c 
 
insert into election values 
('9.4.2019', 1),
('17.9.2019', 2),
('2.3.2020', 3),
('23.3.2021', 4),
('1.11.2022', 5);


insert into party values
('nature party', 'np'), ('science group', 'sg'), ('life party', 'lp'),
('art group', 'ag'), ('lost group','lg');


insert into city values
(22, 'ryde end', 'north'), (77, 'east strat', 'south'), (33, 'grandetu', 'center'),
(88, 'royalpre', 'hills'), (11, 'carlpa', 'hills'), (44, 'lommont', 'north'),
(66, 'grand sen', 'south'),(99, 'kingo haven', 'hills') ,(55, 'el munds', 'south');

insert into running values
('9.4.2019', 'nature party', 12345),
('2.3.2020', 'nature party',55555),

('9.4.2019', 'life party', 54321),
('2.3.2020', 'life party', 54321),

('9.4.2019', 'lost group', 34567),
('17.9.2019', 'lost group', 76543),

('17.9.2019', 'art group', 67890),

('2.3.2020', 'science group', 90876);

insert into votes values
(22, '2.3.2020', 'nature party', 100), (22, '2.3.2020', 'science group', 30),
(22, '2.3.2020', 'life party', 500),

(77, '2.3.2020', 'nature party', 300),
(77, '2.3.2020', 'science group', 150), (77, '2.3.2020', 'life party', 25),

(33, '2.3.2020', 'nature party', 13), (33, '2.3.2020', 'science group', 740),
(33, '2.3.2020', 'life party', 670),

(33, '17.9.2019', 'lost group', 600), (22, '17.9.2019', 'lost group', 400),
(33, '17.9.2019', 'art group', 100), (22, '17.9.2019', 'art group', 1000),

(22, '9.4.2019', 'nature party', 500), (22, '9.4.2019', 'lost group', 400),
(22, '9.4.2019', 'art group', 190),

(11, '9.4.2019', 'nature party', 191), (11, '9.4.2019', 'lost group', 1500),
(11, '9.4.2019', 'art group', 600), (99, '9.4.2019', 'life party', 600);


-- ex d1

select pname, cname
from  votes v natural join city c
where cname='ryde end' and  v.nofvotes>0 and v.edate='2020-03-02';

-- ex d2

select distinct pname,region, nofvotes
from  votes v natural join city c natural join election e
where kno = 3
group by kno,pname, region, nofvotes
;

-- ex d3

select distinct c.cname, c.region 
from  votes v natural join city c
where cid NOT IN
(select cid
 from votes v natural join city c
 where	pname='life party' and  nofvotes>0);
 
-- ex d4

with running_count(edate, nofparties) as (select edate, count(pname) from running group by edate)
select edate, kno
from running_count natural join election
where nofparties >= all (select nofparties from running_count)
;

-- ex d5

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

-- ex d6

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
	where totalvotes < maxvotes.votes and kno=3);

-- ex d7
select r1.pname, r2.pname
from running r1, running r2
where r1.edate = r2.edate and r1.pname < r2.pname
group by r1.pname, r2.pname
having count(r1.edate) = (
	select count(*) from running where pname=r1.pname)
	   and count(r1.edate) = (select count(*) from running where pname=r2.pname);
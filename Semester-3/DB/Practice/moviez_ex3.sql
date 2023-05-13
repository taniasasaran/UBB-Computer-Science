use ex_3_practic;

create table Actors(
	aid int primary key,
	aname varchar(40),
	ranking int
);

create table Companies(
	cid int primary key,
	cname varchar(30)
);

create table Directors(
	did int primary key,
	dname varchar(30),
	noawards int
);

create table Movies(
	mid int primary key,
	mname varchar(30),
	dor varchar(10),
	cid int foreign key references Companies(cid),
	did int foreign key references Directors(did)
);

create table Productions(
	pid int primary key,
	title varchar(40),
	mid int foreign key references Movies(mid)
);

create table ActorsProduction(
	aid int foreign key references Actors(aid),
	pid int foreign key references Productions(pid),
	entrym time,
	primary key (aid, pid)
);

insert into Actors values
(1, 'Vin Diesel', 100),
(2, 'Emma Stone', 20),
(3, 'Michael Scott', 100),
(4, 'Dwight Scrute', 70),
(5, 'Mircea Bravo', 50)

insert into Companies values
(1, 'Walt Disney'), (2,'Netflix'), (3, 'HBO')

insert into Directors values
(1, 'Director1', 10), (2, 'Director 2', 15), (3, 'Director 3', 100)

insert into Movies (mid, mname, dor, cid, did) values
(1, 'offic', '2009-01-02',2,3),
(2, 'iute si nervos', '2020-09-01', 3,2),
(3, 'mirciulica', '2022-10-07', 1,1)

insert into Productions (pid, title, mid) values
(1, 'offic 1', 1),
(2, 'offic 2', 1),
(3, 'fastfurios 3', 2),
(4, 'fastfurios 4', 2),
(5, 'fastfurios 5', 2),
(6, 'mirciulica filmul', 3)

insert into ActorsProduction (aid, pid, entrym) values
(3,1,'00:00'),
(4,1,'04:09'),
(1,1,'00:00'),
(1,2,'00:00'),
(1,3,'00:00'),
(1,4,'00:00'),
(1,5,'00:00'),
(1,6,'00:00'),
(5,6,'00:10')



create or alter proc addActorToProduction(@aid int, @pid int, @entrym time) as
begin
	insert into ActorsProduction values
	(@aid, @pid, @entrym)
end
select * from ActorsProduction
exec addActorToProduction 2,5,'00:30:13'

create or alter view showNameActorsAllProductions as
	select A.aname
	from Actors A
	where A.aid in 
		( select aid
		from ActorsProduction AP
		where AP.aid = A.aid and 
			(select count(*) from Productions) = 
					(select count(*)
					from ActorsProduction EP where EP.aid=AP.aid)
					)

create or alter view showNameActorsAllProductions2 as
	select A.aname
	from Actors A
	where A.aid in 
		( select aid
		from ActorsProduction AP
		group by aid
		having count(*) = (select count(*) from Productions)
		)

select * from showNameActorsAllProductions
select * from showNameActorsAllProductions2

create or alter function newMoviesWithAtLeastPproductions(@p int) returns table as return
select * 
from Movies
where dor > '2018-01-01' and mid in 
  (	select mid
	from Productions
	group by mid
	having count(*)>=@p )
		

select * from newMoviesWithAtLeastPproductions(2)
use ex_5_practic;
--1
create table Animals(
	aid int primary key,
	aname varchar(40),
	dob date
);

create table Food(
	fid int primary key,
	fname varchar(40),
);

create table Visitors(
	vid int primary key,
	vname varchar(40),
	vage int
);

create table Zoos(
	zid int primary key,
	adname varchar(40),
	zname varchar(40),
); 

create table Visits(
	vizid int primary key,
	vday int,
	price int,
	vid int foreign key references Visitors(vid),
	zid int foreign key references Zoos(zid)
);

create table AnimalZoos(
	aid int foreign key references Animals(aid),
	zid int foreign key references Zoos(zid),
	primary key (aid,zid)
);

create table AnimalFood(
	aid int foreign key references Animals(aid),
	fid int foreign key references Food(fid),
	primary key (aid,fid),
	qty int
);

insert into Animals (aid,aname,dob) values
(1,'Urs','1999-01-03'),
(2,'Ursoaica','1999-01-02'),
(3,'Lup','1999-01-04'),
(4,'Lupaoica','1999-01-05'),
(5,'Pitzi Pitzi Iepuroaica','1999-01-06')

insert into Food (fid,fname) values
(1,'Morcomv'),
(2,'Smeora'),
(3,'Om!'),
(4,'carnitz');
insert into Visitors (vid,vname,vage) values
(1,'Unu',23),
(2,'Altu',19),
(3,'Ala',30),
(4,'Celalalt',2);
insert into Zoos(zid,zname,adname) values
(1,'Baia Mare','Chereches'),
(2,'Cluj','Emil BOOOC'),
(3,'Papucesti','Ala cu papucii'),
(4,'Puleni','Primaru Pulos');
insert into Visits (vizid,vid,zid,vday,price)values
(1,1,4,5,10),
(2,2,2,3,10),
(3,3,2,7,10),
(4,4,1,8,10);
insert into AnimalZoos(aid,zid) values
(1,1),
(2,1),
(3,2),
(4,3),
(2,4);
insert into AnimalFood (aid,fid,qty) values
(1,1,10),
(2,2,10),
(3,3,10),
(4,3,10),
(4,4,10);

--2
create or alter proc DeletAnimalFood(@aid int) as
begin
	delete 
	from AnimalFood
	where aid=@aid
end
select * from AnimalFood
exec DeletAnimalFood 4;

--3
create or alter view UnpopularZoo as
select *
from Zoos
where zid in (
select zid
from Visits
group by zid
having count(*)= (select top 1 count(zid) from Visits group by zid order by count(zid) ASC)
)
select * from UnpopularZoo;

--4
create or alter function NAnimals(@n int) returns table as return
select vid
from Visits
where zid in (
	select zid
	from AnimalZoos
	group by zid
	having count(*)>=@n
)

select * from NAnimals(2);
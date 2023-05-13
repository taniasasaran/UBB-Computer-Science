use ex_2_practic;
--1
drop table WamanBuyShoe;
drop table IsInShop;
drop table Women;
drop table PresentationShops;
drop table Shoes;
drop table ShoeModels;

create table ShoeModels(
	mid int primary key,
	mname varchar(20),
	season int
);
create table Shoes(
	shid int primary key,
	price int,
	mid int foreign key references ShoeModels(mid)
);
create table PresentationShops(
	psid int primary key,
	pname varchar(30),
	city varchar(30)
);

create table Women(
	wid int primary key,
	wname varchar(40),
	amount int -- of money
);

create table IsInShop(
	psid int foreign key references PresentationShops(psid),
	shid int foreign key references Shoes(shid),
    primary key (psid,shid),
	qty int
);

create table WamanBuyShoe(
	wid int foreign key references Women(wid),
	shid int foreign key references Shoes(shid),
    primary key (wid,shid),
	qty int, --of shoes
	amount int --of money spent
);
insert into ShoeModels (mid, mname, season) values
(1, 'papuci', 4),
(2, 'slapi', 2),
(3, 'sneakers', 1),
(4, 'cizme', 3),
(5, 'sandale', 2)

insert into Shoes (shid, price, mid) values
(1, 15, 2),
(2, 30, 1),
(3, 45, 1),
(4, 100, 4),
(5, 250, 3),
(6, 40, 2),
(7, 60, 5),
(8, 300, 5)

insert into PresentationShops (psid, pname, city) values
(1, 'magazin', 'Baia Mareee'),
(2, 'alt magazin', 'un fel de baie'),
(3, 'intresporturi', 'Clugi'),
(4, 'Clujana', 'nu Cluj'),
(5, 'Vagabond', 'provincie')

insert into Women (wid, wname, amount) values
(1, 'Tania', 5000000),
(2, 'Sorana', 7000000),
(3, 'Raresa', 30000),
(4, 'Jonela', 700)

insert into IsInShop (psid, shid, qty) values
(3,5,2), (3,6,1), (4,4,4), (1,2,3)

insert into WamanBuyShoe (wid, shid, qty, amount) values
(1,7,1,737),(1,8,1,727),(2,5,2,500),(3,3,1,45),(4,6,3,7472),(3,7,1,60)

--2
create or alter proc add_shoe_to_shop(@shid int, @psid int,@qty int) as
begin
	insert into IsInShop(psid,shid,qty) values
	(@psid,@shid,@qty)
end
select * from IsInShop
exec add_shoe_to_shop 3,1,2 ;

--3  YOU CANNOT CREATE VIEWS THAT HAVE PARAMETERS MS SABINA FOR CRYING OUT LOUD YOU SHOULD KNOW BETTER
create or alter function HasBoughtModel(@mid int) returns table as return
select * 
from Women W
where 2<=(
select sum(qty)
from WamanBuyShoe
	where shid in (
	select shid
	from Shoes
	where mid=@mid and wid=W.wid))
select * from HasBoughtModel(1);

--4
create or alter function MoreThanTShoes(@t int) returns table as return
select *
from Shoes S
where @t<=(
select sum(qty)
from IsInShop I
where S.shid= I.shid
)
select * from MoreThanTShoes(2);


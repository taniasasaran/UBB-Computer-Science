use ex_4_practic;

--1
create table CakeTypes(
	tid int primary key,
	tname varchar(20),
	descr varchar(250)
);

create table Cakes(
	cake_id int primary key,
	cake_name varchar(20),
	shape varchar (10),
	cake_weight float,
	price int,
	tid int foreign key references CakeTypes(tid)
);
create table Orders(
	order_id int primary key,
	dop date
);

create table Chefs(
	chef_id int primary key,
	chef_name varchar(40),
	gender varchar(100),
	dob date
);

create table OrderCakes(
	order_id int foreign key references Orders(order_id),
	cake_id int foreign key references Cakes(cake_id),
	qty int
);

create table ChefCakes(
	chef_id int foreign key references Chefs(chef_id),
	cake_id int foreign key references Cakes(cake_id),
);

insert into CakeTypes(tid,tname,descr) values 
(1,'Onomastik','Fuarte asa'),
(2,'Nonta','Cu di tate cat un turn'),
(3,'Parastas','Negru caco ndoleantele condimente'),
(4,'Office','Polotically correct, transparent ca sa nu se supere nimeni cand vede o culoare');

insert into Cakes(cake_id,cake_name,cake_weight,shape,price,tid) values 
(1,'Tolt din flisca',14,'rotond',12,2),
(2,'Tort diplomat?',23,'strident',23,1),
(3,'Cizkek',32,'trionghi',54,4),
(4,'Coliba',41,'ascutit',49,3);

insert into Orders (order_id,dop) values 
(1,'2022-12-29'),
(2,'1999-01-01'),
(3,'1861-03-24'),
(4,'2002-02-20');

insert into Chefs (chef_id,chef_name,gender,dob) values 
(1,'Dragonitza Ninja','astrogastropastopanbifluidtransteraparasex','2040-10-10'),
(2,'Sorin Bontea vena','mascoolin','1980-01-02'),
(3,'Catalin Scarlatescu cox','masckulin','1980-01-03'),
(4,'Florin Dumitrescu freza','mascoleano','1980-01-04');

insert into OrderCakes (order_id,cake_id,qty) values 
(1,1,1),
(2,2,2),
(3,3,3),
(4,2,4),
(4,3,5);

insert into ChefCakes (chef_id,cake_id) values 
(4,1),
(4,2),
(4,3),
(4,4),
(2,1),
(3,2);

--2
create or alter proc AddToOrder(@oid int, @cname varchar(20), @p int) as
begin
	declare @found int
	declare @cid int
	set @cid=(select cake_id from Cakes where cake_name=@cname)
	set @found=(select qty from OrderCakes where order_id=@oid and cake_id=@cid)
	
	if @found is not null 
		update OrderCakes
		set qty=@p
		where order_id=@oid and cake_id=@cid
	else
		insert into OrderCakes (order_id,cake_id,qty) values (@oid,@cid,@p)
end

select* from OrderCakes;
exec AddToOrder 4, 'Tort diplomat?', 6;
exec AddToOrder 1, 'Tort diplomat?', 3;

--3
create or alter function ChefsKnow() returns table as return
select chef_name
from Chefs C
where C.chef_id in (
	select chef_id
	from ChefCakes
	group by chef_id
	having count(*) = (select count(*) from Cakes)
)

select * from ChefsKnow();



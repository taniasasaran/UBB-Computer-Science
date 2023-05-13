use actual_practic;


--1 b
--2 e
--3 d

create table Stores(
	store_id int primary key,
	store_adr varchar(30),
	country varchar(30),
	phone char(10)
);

create table Customers(
	c_name varchar(50) primary key,
	email varchar(30) unique,
	nationality varchar(30),
	dob date
);

create table Employees(
	e_name varchar(50) primary key,
	store_id int foreign key references Stores(store_id),
	dob date
);

create table Products(
	p_name varchar(50) primary key,
	description varchar(300) ,
	price int
);

create table Orders(
	order_id int primary key,
	c_name varchar(50) foreign key references Customers(c_name),
	doo date,
);
create table OrdersProducts(
	order_id int foreign key references Orders(order_id),
	p_name varchar(50) foreign key references Products(p_name),
	qty int,
);

create table StoresProducts(
	store_id int foreign key references Stores(store_id),
	p_name varchar(50) foreign key references Products(p_name)	
);

insert into Stores values
(1,'Address1','Country1','07siceva'),
(2,'Address2','Country2','07sialtca'),
(3,'Address3','Country3','07sinuiu');

insert into Customers values
('Customer1','Email1','Nationality1','1999-11-14'),
('Customer2','Email2','Nationality2','1999-12-15'),
('Customer3','Email3','Nationality3','1999-01-16');

insert into Employees values
('Employee1',1,'2000-10-10'),
('Employee2',3,'2001-09-11'),
('Employee3',2,'2002-08-12');

insert into Products values
('Product1','Description1',100),
('Product2','Description2',200),
('Product3','Description3',300);

insert into Orders values
(1,'Customer2','2022-11-15'),
(2,'Customer1','2022-12-11'),
(3,'Customer3','2022-01-12');

insert into OrdersProducts values
(1,'Product3',3),
(2,'Product1',6),
(2,'Product2',2);

insert into StoresProducts values
(1,'Product1'),
(3,'Product1'),
(2,'Product1'),
(3,'Product3');
drop table StoresProducts
select* from StoresProducts


create or alter proc addUppOrder(@oid int,@pn varchar(50),@qty int) as
begin
	declare @found int = (select count(*) from OrdersProducts where order_id=@oid and p_name=@pn)
	if @found=0
		insert into OrdersProducts (order_id,p_name,qty) values
		(@oid,@pn,@qty)
	else
		update OrdersProducts
		set qty=@qty
		where order_id=@oid and p_name=@pn
end



create or alter view popularProducts as
select p_name
from StoresProducts
group by p_name
having count(*)=(select count(*) from Stores)

create or alter function customersBoughtMoreThan(@R int) returns table as return
select count(*)
From Customers
where c_name in
( select c_name
from Orders O
having @R<(
select sum(price*qty) 
from
(
(select p_name,qty
from OrdersProducts OP
where O.order_id=OP.order_id) A
inner join
(select p_name,price
from Products P) B
on A.p_name=B.p_name 
)
))

use ex1_practic;
drop table TRANSACTIONS;
drop table ATMS;
drop table BANK_ACCOUNTS;
drop table CUSTOMERS; 

create table CUSTOMERS(
	cid int primary key, 
	cname varchar(50),
	dob date
);

create table BANK_ACCOUNTS(
	iban char(20) primary key,
	balance float default 0,
	cid int foreign key references CUSTOMERS(cid)	
);
create table CARDS(
	number char(16) primary key,
	cvv char(3),
	iban char(20) foreign key references BANK_ACCOUNTS(iban)
);
create table ATMS(
	atmid int primary key,
	place varchar(70)
);

create table TRANSACTIONS(
	atmid int foreign key references ATMS(atmid),
	card_number char(16) foreign key references CARDS(number),
	ammount int,
	dtot smalldatetime
);

insert into CUSTOMERS (cid, cname, dob) VALUES
(1,'JOHANNES KRAMP','1395-12-12'),-- un taietor de lemne renumit din padurea inalta din KROMPFEL
(2,'BAIAZID','1389-10-28'), -- un turc saormar cu planuri marete, subestimat de sa moara familia lui
(3,'EMHIL BOKANKUS','1391-1-24'), -- un gnom pantofar de renume cu un istoric nebanuit
(4,'BUNU SANDU','1380-5-15'); -- batran atotstiutor, dornic de a aduce pacea in sufletul oricui 

insert into BANK_ACCOUNTS (iban, balance, cid) VALUES
('2424242', 50000, 1),
('43534', 6500, 1),
('161616', 50000, 2),
('16161623', 30000, 3),
('7362243', 57000, 4)

insert into CARDS (number, cvv, iban) VALUES
('254343455', 234, '43534'),
('11111111', 234, '2424242'),
('22222222', 456, '161616'),
('11111112', 235, '2424242');

insert into ATMS (atmid, place) VALUES
(1,'PAPUCEEESTI?'),
(2,'La dracu in ciorba'),
(3,'In padurea minciunilor');

insert into TRANSACTIONS (atmid, card_number, ammount, dtot) VALUES
(1, 11111111, 1600, '1900-01-01 00:00:00'),
(3, 11111111, 200, '1989-01-01 00:00:00'),
(2, 22222222, 1900, '1908-01-01 00:00:00'),
(1, 22222222, 150, '1968-01-01 00:00:00'),
(3, 254343455, 960, '2003-01-01 00:00:00');
create or alter proc delete_transactions(@card_number int) as
begin
	--declare @card = select * from CARDS where number=@card_number; cant hold this kind of stuff, only ints and so on
	delete from TRANSACTIONS where card_number=@card_number;
end
exec delete_transactions 254343455;
select * from TRANSACTIONS;

create or alter view used_cards as
	select distinct card_number
	from TRANSACTIONS;

select*
from used_cards;

create or alter function lets_see_the_spenders()
returns Table as return
select C.number, C.cvv
from CARDS C
where (
select SUM(ammount)
from TRANSACTIONS T
where T.card_number=C.number
) > 2000;

select * from lets_see_the_spenders();




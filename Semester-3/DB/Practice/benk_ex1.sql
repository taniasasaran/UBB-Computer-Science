use benk
drop table TRANSACTIONS
drop table ATMS
drop table CARDS
drop table BANKACCOUNTS
drop table CUSTOMERS

create table CUSTOMERS(
	cid int primary key,
	name varchar(40),
	dob date
);

create table BANKACCOUNTS(
	iban int primary key,
	balance float default 0,
	cid int not null,
	constraint fk_cid FOREIGN KEY (cid) REFERENCES CUSTOMERS(cid) on delete cascade
);

create table CARDS(
	number int primary key,
	cvv int,
	iban int not null,
	constraint fk_iban FOREIGN KEY (iban) REFERENCES BANKACCOUNTS(iban) on delete cascade
)

create table ATMS(
	atmid int primary key,
	address varchar(100)
)

create table TRANSACTIONS(
	atmid int,
	constraint fk_atmid FOREIGN KEY (atmid) REFERENCES ATMS(atmid) on delete cascade,
	cardnumber int,
	constraint fk_cardnumber FOREIGN KEY (cardnumber) REFERENCES CARDS(number) on delete cascade,
	amount int,
	date_time smalldatetime,
	constraint pk_trans PRIMARY KEY (atmid, cardnumber, date_time)
)

insert into CUSTOMERS (cid, name, dob) values
(1,'Tania','2002-05-24'),
(2,'Rares','2002-06-16'),
(3,'Haurentiu','1987-09-03'),
(4,'Izolatia','1990-01-31')

insert into BANKACCOUNTS (iban,balance,cid) values
(2424242, 50000, 1),
(43534, 6500, 1),
(161616, 50000, 2),
(7362243, 57000, 4)

insert into CARDS (number, cvv, iban) values  
(254343455, 234, 43534),
(11111111, 234, 2424242),
(22222222, 456, 161616),
(11111112, 235, 2424242)

insert into ATMS (atmid, address) values
(1, 'elobelo'),
(2, 'ciau'),
(3, 'salit'),
(4, 'ateme')

insert into TRANSACTIONS (atmid, cardnumber, amount, date_time) values
(1, 11111111, 1600, '1900-01-01 00:00:00'),
(3, 11111111, 200, '1989-01-01 00:00:00'),
(2, 22222222, 1900, '1908-01-01 00:00:00'),
(1, 22222222, 150, '1968-01-01 00:00:00'),
(4, 11111112, 1900, '1906-01-01 00:00:00'),
(3, 254343455, 960, '2003-01-01 00:00:00')



create or alter proc uspDeleteTransactionsCard(@CardNumber int) as
begin
	DELETE FROM TRANSACTIONS WHERE cardnumber = @CardNumber
end

create or alter view cardsUsedInAllTransactions as
	select distinct cardnumber from TRANSACTIONS


create or alter function ufListCardsSumGreaterThan2000()
returns Table as return
	select C.number, C.cvv
	from Cards C
	where 2000 < (
		select sum(T.amount)
		from TRANSACTIONS T
		where T.cardnumber = C.number
	)

select * from TRANSACTIONS
exec uspDeleteTransactionsCard 254343455

select * from cardsUsedInAllTransactions

select * from ufListCardsSumGreaterThan2000 ()
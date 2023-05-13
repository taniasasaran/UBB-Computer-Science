use ex_6_practic_but_its_5_actually;
create table TrainType(
	ttid int primary key,
	descr varchar(200)
);

create table Train(
	tid int primary key,
	ttid int foreign key references TrainType(ttid),
	tname varchar(30)
);

create table Stations(
	sname varchar(30) primary key
);

create table Routess(
	rname varchar(30) primary key,
	tid int foreign key references Train(tid),

);

create table RouteStation(
	rname varchar(30) foreign key references Routess(rname),
	sname varchar(30) foreign key references Stations(sname),
	arrival time,
	departure time
);

create or alter proc adduppRS(@rname varchar(30),@sname varchar(30),@arrival time, @departure time) as
begin
	declare @found int = 0
	set @found=(select count(*) from RouteStation where sname=@sname and rname=@rname)
	
	if @found=0
		insert into RouteStation (rname,sname,arrival,departure) values
		(@rname,@sname,@arrival,@departure)
	else
		update RouteStation 
		set arrival=@arrival 
		set departure=@departure
		where sname=@sname and rname=@rname;

end

create or alter view allStarNoStation as
select rname
from RouteStation
group by rname
having count(*)=(select count(*)from Stations);


create or alter function stationsR(@R int) returns table as return
select name 
from RouteStation
group by station
having count(*)>@R;


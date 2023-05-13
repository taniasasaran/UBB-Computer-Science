use [database-lab5];

CREATE TABLE TA (
	aid int PRIMARY KEY,    --policestationID
	a2 int UNIQUE,          --zipcode
	x int
)

CREATE TABLE TB (
	bid int PRIMARY KEY,   --cnp
	b2 int,                --age
	x int
)

CREATE TABLE TC (         
	cid int PRIMARY KEY,
	aid int,
	bid int,
	CONSTRAINT FK_aid FOREIGN KEY(aid) REFERENCES TA(aid) ON DELETE CASCADE,
	CONSTRAINT FK_bid FOREIGN KEY(bid) REFERENCES TB(bid) ON DELETE CASCADE
)

create or alter procedure addValuesToTA (@rows int) as
    while @rows > 0 begin
        insert into TA(aid,a2,x) values
            (@rows, @rows*10, @rows%240)
        set @rows = @rows - 1
    end

create or alter procedure addValuesToTB (@rows int) as
    while @rows > 0 begin
        insert into TB(bid,b2,x) values
            (@rows, @rows%2, @rows%70)
        set @rows = @rows - 1
    end

create or alter procedure addValuesToTC (@rows int) as
    declare @aid int
    declare @bid int
    while @rows > 0 begin
		set @aid = (select top 1 aid from TA order by NEWID())
        set @bid = (select top 1 bid from TB order by NEWID())
        insert into TC(cid,aid,bid) values(@rows, @aid, @bid)
        set @rows = @rows - 1
    end

delete from TC
delete from TB
delete from TA
exec addValuesToTA 10000
exec addValuesToTB 12000
exec addValuesToTC 40000  --5:35

select * from TA order by aid -- Clustered Index Scan
select * from TA where aid=10 -- Clustered Index Seek

create nonclustered index index1 on TA(x)
drop index index1 on Ta

select x from Ta order by x -- Nonclustered Index Scan
select aid, x from Ta where x = 100 -- Nonclustered Index Seek
select x from Ta where aid = 500 -- Key Lookup

create or alter procedure run_where_query as
    declare @startTime datetime2
    declare @endTime datetime2	
	set @startTime = SYSDATETIME()
	select * from Tb where b2 = 0 
	set @endTime = SYSDATETIME()
	print CONVERT(VARCHAR, @endTime)+' '+CONVERT(VARCHAR,@startTime)

drop index index2 on TB
exec run_where_query  -- Clustered Index Scan 0.2 cost

create nonclustered index index2 on TB(b2) include (bid, x) 
exec run_where_query  -- Nonclustered Index Seek 0.1 cost

create or alter view view1 as
    select top 1000 T1.x, T2.b2
    from Tc T3 join Ta T1 on T3.aid = T1.aid join Tb T2 on T3.bid = T2.bid
    where T2.b2 >= 0 and T1.x < 150

create or alter procedure select_view as
    declare @startTime datetime2
    declare @endTime datetime2	
	set @startTime = SYSDATETIME()
	select * from view1
	set @endTime = SYSDATETIME()
	print CONVERT(VARCHAR, @endTime)+' '+CONVERT(VARCHAR,@startTime)

exec select_view    --0.01 with indexes

drop index index2 on TB
drop index index1 on Ta
exec select_view    --0.05 without indexes

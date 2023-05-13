use BouquetStore

exec addToTables 'Bouquet'
exec addToTables 'Occasion'

create or alter view getBouquetsFromOccasion as
    select B.bouquet_name, B.bouquet_id
        from Bouquet B inner join Occasion O on O.occasion_id = B.occasion_id

exec addToViews 'getBouquetsFromOccasion'
exec addToTests 'test2'
exec connectTableToTest 'Bouquet', 'test2', 1200, 2
exec connectTableToTest 'Occasion', 'test2', 600, 1
exec connectViewToTest 'getBouquetsFromOccasion', 'test2'

create or alter procedure populateTableOccasion (@rows int) as
    while @rows > 0 begin
        insert into Occasion(name,florist_id) values
            ('Name', (select top 1 florist_id from Florist order by newid()))
        set @rows = @rows - 1
    end
go
create or alter  procedure populateTableBouquet(@rows int) as
    while @rows > 0 begin
        insert into Bouquet(bouquet_name, occasion_id,price) values
            ('BouquetName',(select top 1 occasion_id from Occasion order by newid()),@rows)
        set @rows = @rows - 1
    end
go
execute runTest 'test2'


select * from TestRuns


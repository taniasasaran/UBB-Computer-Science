use BouquetStore

exec addToTables 'Flower'

create or alter view getPriceGroups as
    select price, count(*) as number_of_flowers
    from Flower
    group by price

exec addToViews 'getPriceGroups'
exec addToTests 'test1'
exec connectTableToTest 'Flower', 'test1', 1000, 1
exec connectViewToTest 'getPriceGroups', 'test1'

create or alter procedure populateTableFlower (@rows int) as
    while @rows > 0 begin
        insert into Flower(flower_id, flower_name, color, country_of_origin, price, quantity)  values (@rows, 'Name', 'red', 'Testing', floor(rand()*100), floor(rand()*100))
        set @rows = @rows-1
    end
go
execute runTest 'test1'

select * from TestRuns


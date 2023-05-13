use BouquetStore

exec addToTables 'AccessoryRecipe'


create or alter view getNumberAccessoriesOfEachOccasion as
    select O.name, O.occasion_id, count(*) as 'count'
    from AccessoryRecipe AR inner join Bouquet B on B.bouquet_id = AR.bouquet_id
	                        inner join Occasion O on O.occasion_id = B.occasion_id
							group by O.occasion_id, O.name


exec addToViews 'getNumberAccessoriesOfEachOccasion'
exec addToTests 'test3'
exec connectTableToTest 'AccessoryRecipe', 'test3', 100, 3
exec connectTableToTest 'Bouquet', 'test3', 100, 2
exec connectTableToTest 'Occasion', 'test3', 100, 1
exec connectViewToTest 'getNumberAccessoriesOfEachOccasion', 'test3'

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

create or alter procedure populateTableAccessoryRecipe (@rows int) as
	IF @rows > (SELECT COUNT(*) FROM Accessory) * (SELECT COUNT(*) FROM Bouquet) BEGIN
		print 'Too many entities requested'	
	END
	DECLARE populateCursor CURSOR SCROLL FOR
		SELECT A.accessory_id, B.bouquet_id
		FROM Accessory A CROSS JOIN Bouquet B
	DECLARE @aId INT
	DECLARE @bId INT
	OPEN populateCursor
	WHILE @rows > 0 BEGIN 
		FETCH FROM populateCursor INTO @aId, @bId
		INSERT INTO AccessoryRecipe VALUES(@aId, @bId, @rows)
		SET @rows = @rows - 1
	END
	CLOSE populateCursor
	DEALLOCATE populateCursor;
go

exec runTest 'test3'


select * from TestRuns

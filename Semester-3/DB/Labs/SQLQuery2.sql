use BouquetStore
go

CREATE OR ALTER PROCEDURE changeFlowerCountryOfOrigin100 AS
BEGIN
	ALTER TABLE Flower 
	ALTER COLUMN country_of_origin VARCHAR(100) 
	PRINT 'ALTER TABLE Flower CountryOfOrigin FROM varchar20 TO varchar100';
END
GO

CREATE OR ALTER PROCEDURE changeFlowerCountryOfOrigin30 AS
BEGIN
	ALTER TABLE Flower 
	ALTER COLUMN country_of_origin VARCHAR(30)  
	PRINT 'ALTER TABLE Flower CountryOfOrigin FROM varchar100 TO varchar20';
END
GO


CREATE or ALTER PROCEDURE addCityToCustomer AS
	ALTER TABLE Customer ADD city VARCHAR(50);
GO

CREATE or ALTER PROCEDURE removeCityToCustomer AS
	ALTER TABLE Customer DROP COLUMN city;
GO



CREATE or ALTER PROCEDURE addDefaultToFlowerColor AS
	ALTER TABLE Flower ADD CONSTRAINT COLOR_DEFAULT DEFAULT('multicolor') FOR color;
GO

CREATE or ALTER PROCEDURE dropDefaultToFlowerColor AS
	ALTER TABLE Flower DROP CONSTRAINT COLOR_DEFAULT; 
GO

CREATE or ALTER PROCEDURE createSuccessfulFlorists AS
	CREATE TABLE SuccessfulFlorists(
		florist_id INT NOT NULL,
		florist_name VARCHAR(200) NOT NULL,
		shop_id INT NOT NULL,
		amount int NOT NULL,
		CONSTRAINT SuccessfulFlorists_PRIMARY_KEY PRIMARY KEY (florist_id, shop_id) 
	); GO

CREATE or ALTER PROCEDURE dropSuccessfulFlorists AS
	DROP TABLE SuccessfulFlorists;
GO

CREATE or ALTER PROCEDURE addAmountToSuccessfulFloristsPrimaryKeyConstraint AS
BEGIN
	ALTER TABLE SuccessfulFlorists
		DROP CONSTRAINT SuccessfulFlorists_PRIMARY_KEY
	ALTER TABLE SuccessfulFlorists
		ADD CONSTRAINT SuccessfulFlorists_PRIMARY_KEY PRIMARY KEY (florist_id, shop_id, amount);
END
GO

CREATE or ALTER PROCEDURE removeAmountToSuccessfulFloristsPrimaryKeyConstraint AS
BEGIN
	ALTER TABLE SuccessfulFlorists
		DROP CONSTRAINT SuccessfulFlorists_PRIMARY_KEY
	ALTER TABLE SuccessfulFlorists
		ADD CONSTRAINT SuccessfulFlorists_PRIMARY_KEY PRIMARY KEY (florist_id, shop_id);
END
GO

CREATE or ALTER PROCEDURE addSuccessfulFloristsForeignKeyConstraint AS
	ALTER TABLE SuccessfulFlorists ADD CONSTRAINT SuccessfulFlorists_FLORISTID_FOREIGN_KEY FOREIGN KEY(florist_id) REFERENCES Florist(florist_id);
GO	

CREATE or ALTER PROCEDURE removeSuccessfulFloristsForeignKeyConstraint AS
	ALTER TABLE SuccessfulFlorists DROP CONSTRAINT SuccessfulFlorists_FLORISTID_FOREIGN_KEY;
GO

CREATE or ALTER PROCEDURE addShopCandidateKey AS
	ALTER TABLE Shop ADD CONSTRAINT SHOP_CANDIDATE_KEY UNIQUE (shop_name, shop_address);
GO

CREATE or ALTER PROCEDURE removeShopCandidateKey AS
	ALTER TABLE Shop DROP CONSTRAINT SHOP_CANDIDATE_KEY;
GO

CREATE TABLE VERSION_TABLE(
	version int,
	PRIMARY KEY(version)
);
INSERT INTO VERSION_TABLE VALUES(1);

drop TABLE PROCEDURES_TABLE

CREATE TABLE PROCEDURES_TABLE(
	fromVersion INT,
	toVersion INT,
	nameProc VARCHAR(255),
	PRIMARY KEY(fromVersion, toVersion)
);
	
INSERT INTO PROCEDURES_TABLE VALUES (1, 2, 'changeFlowerCountryOfOrigin100');
INSERT INTO PROCEDURES_TABLE VALUES (2, 1, 'changeFlowerCountryOfOrigin30');
INSERT INTO PROCEDURES_TABLE VALUES (2, 3, 'addCityToCustomer');
INSERT INTO PROCEDURES_TABLE VALUES (3, 2, 'removeCityToCustomer');
INSERT INTO PROCEDURES_TABLE VALUES (3, 4, 'addDefaultToFlowerColor');
INSERT INTO PROCEDURES_TABLE VALUES (4, 3, 'dropDefaultToFlowerColor');
INSERT INTO PROCEDURES_TABLE VALUES (4, 5, 'createSuccessfulFlorists');
INSERT INTO PROCEDURES_TABLE VALUES (5, 4, 'dropSuccessfulFlorists');
INSERT INTO PROCEDURES_TABLE VALUES (5, 6, 'addAmountToSuccessfulFloristsPrimaryKeyConstraint');
INSERT INTO PROCEDURES_TABLE VALUES (6, 5, 'removeAmountToSuccessfulFloristsPrimaryKeyConstraint');
INSERT INTO PROCEDURES_TABLE VALUES (6, 7, 'addSuccessfulFloristsForeignKeyConstraint');
INSERT INTO PROCEDURES_TABLE VALUES (7, 6, 'removeSuccessfulFloristsForeignKeyConstraint');
INSERT INTO PROCEDURES_TABLE VALUES (7, 8, 'addShopCandidateKey');
INSERT INTO PROCEDURES_TABLE VALUES (8, 7, 'removeShopCandidateKey');



CREATE PROCEDURE goToVersion(@newVersion INT) AS
	DECLARE @curr int
	DECLARE @procedureName varchar(255)
	SELECT @curr=version FROM VERSION_TABLE
	IF @newVersion > (SELECT max(toVersion) FROM PROCEDURES_TABLE)
		RAISERROR ('Version does not exist', 10, 1)
	
	IF @newVersion < (SELECT min(fromVersion) FROM PROCEDURES_TABLE)
		RAISERROR ('Version does not exist', 10, 1)
	
	WHILE @curr < @newVersion BEGIN
		SELECT @procedureName=nameProc FROM PROCEDURES_TABLE WHERE @curr=fromVersion AND @curr+1=toVersion
		EXEC (@procedureName)
		SET @curr=@curr+1
		UPDATE VERSION_TABLE SET version=@curr
	END
	
	WHILE @curr > @newVersion BEGIN
		SELECT @procedureName=nameProc FROM PROCEDURES_TABLE WHERE @curr=fromVersion AND @curr-1=toVersion
		EXEC (@procedureName)
		SET @curr=@curr-1
		UPDATE VERSION_TABLE SET version=@curr
	END; 

 
EXEC goToVersion 8 

EXEC goToVersion 3;

Select * FROM VERSION_TABLE

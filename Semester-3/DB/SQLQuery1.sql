use BouquetStore;

CREATE TABLE Customer(
	customer_id int NOT NULL IDENTITY,
	PRIMARY KEY(customer_id),
	first_name VARCHAR(30) DEFAULT 'UNKNOWN',
	last_name VARCHAR(30) DEFAULT 'UNKNOWN',
	age int DEFAULT 0,
	gender VARCHAR(20) DEFAULT 'UNCERTAIN',
	budget int DEFAULT 0
);

CREATE TABLE Florist(
	florist_id int NOT NULL IDENTITY,
	PRIMARY KEY(florist_id),
	first_name VARCHAR(30) DEFAULT 'UNKNOWN',
	last_name VARCHAR(30) DEFAULT 'UNKNOWN',
	age int DEFAULT 18,
	CONSTRAINT Age_Constraint CHECK (age>=18),
	gender VARCHAR(20) DEFAULT 'UNCERTAIN',
	salary int DEFAULT 2500
);

CREATE TABLE Occasion(
	name VARCHAR(50) DEFAULT NULL,
	occasion_id int NOT NULL IDENTITY,
	PRIMARY KEY(occasion_id),
	florist_id int DEFAULT NULL,
	FOREIGN KEY(florist_id) REFERENCES Florist(florist_id) ON DELETE SET NULL
);

CREATE TABLE FlowerStore(
	flower_store_id int NOT NULL,
	PRIMARY KEY(flower_store_id),
	flower_store_name VARCHAR(100) DEFAULT 'MAGAZIN'
);

CREATE TABLE Flower(
	flower_id int NOT NULL,
	PRIMARY KEY(flower_id),
	flower_name varchar(100) DEFAULT 'FLOARE',
	color varchar(20),
	country_of_origin varchar(30),
	price int DEFAULT 0,
	quantity int DEFAULT 0
);

CREATE TABLE FlowerStoreOrder(
	flower_id int NOT NULL,
	FOREIGN KEY(flower_id) REFERENCES Flower(flower_id) ON DELETE CASCADE,
	flower_store_id int NOT NULL,
	FOREIGN KEY(flower_store_id) REFERENCES FlowerStore(flower_store_id) ON DELETE CASCADE,
	order_date date NOT NULL,
	PRIMARY KEY(flower_id,flower_store_id,order_date),
	quantity int DEFAULT 1,
	CONSTRAINT FlowerOrderQuantity_Constraint CHECK (quantity>0)
);

CREATE TABLE AccessoriesStore(
	accessories_store_id int NOT NULL,
	PRIMARY KEY(accessories_store_id),
	accessories_store_name VARCHAR(100) DEFAULT 'MAGAZIN'
);

CREATE TABLE Accessory(
	accessory_id int NOT NULL,
	PRIMARY KEY(accessory_id),
	accessory_name varchar(100) DEFAULT 'DECOR',
	color varchar(20) DEFAULT 'TRANSPARENT',
	price int DEFAULT 0,
	quantity int DEFAULT 0
);

CREATE TABLE AccessoriesStoreOrder(
	accessory_id int NOT NULL,
	FOREIGN KEY(accessory_id) REFERENCES Accessory(accessory_id) ON DELETE CASCADE,
	accessories_store_id int NOT NULL,
	order_date date NOT NULL,
	FOREIGN KEY(accessories_store_id) REFERENCES AccessoriesStore(accessories_store_id) ON DELETE CASCADE,
	PRIMARY KEY(accessory_id,accessories_store_id,order_date),	
	quantity int DEFAULT 1,
	CONSTRAINT AccessoriesOrderQuantity_Constraint CHECK (quantity>0)
);

CREATE TABLE Bouquet(
	bouquet_id int NOT NULL IDENTITY,
	PRIMARY KEY(bouquet_id),
	bouquet_name VARCHAR(100) DEFAULT 'BUCHET',
	occasion_id int,
	FOREIGN KEY(occasion_id) REFERENCES Occasion(occasion_id) ON DELETE SET NULL,
	price int NOT NULL DEFAULT 0
);

CREATE TABLE FlowerRecipe(
	flower_id int NOT NULL,
	FOREIGN KEY(flower_id) REFERENCES Flower(flower_id) ON DELETE CASCADE,
	bouquet_id int NOT NULL, 
	FOREIGN KEY(bouquet_id) REFERENCES Bouquet(bouquet_id) ON DELETE CASCADE,
	PRIMARY KEY(flower_id, bouquet_id),
	number_of_flowers int DEFAULT 1,
	CONSTRAINT FlowerRecipeQuantity_Constraint CHECK (number_of_flowers>0)
);

CREATE TABLE AccessoryRecipe(
	accessory_id int NOT NULL,
	FOREIGN KEY(accessory_id) REFERENCES Accessory(accessory_id) ON DELETE CASCADE,
	bouquet_id int NOT NULL, 
	FOREIGN KEY(bouquet_id) REFERENCES Bouquet(bouquet_id) ON DELETE CASCADE,
	PRIMARY KEY(accessory_id, bouquet_id),
	number_of_accessories int DEFAULT 1,
	CONSTRAINT AccessoriesRecipeQuantity_Constraint CHECK (number_of_accessories>0)
);

CREATE TABLE Shop(
	shop_id int NOT NULL PRIMARY KEY,
	shop_name VARCHAR(50) DEFAULT 'UNKNOWN',
	area int DEFAULT 0,
	city VARCHAR(50) DEFAULT 'UNKNOWN',
	shop_address VARCHAR(100),
	opening_hours TIME,
	closing_hours TIME,
	CONSTRAINT Time_Constraint CHECK (opening_hours<closing_hours)
);
ALTER TABLE Shop ALTER COLUMN shop_name VARCHAR(50) NOT NULL;
ALTER TABLE Shop ALTER COLUMN shop_address VARCHAR(200) NOT NULL;

CREATE TABLE Cashier(
	cashier_id int NOT NULL IDENTITY,
	PRIMARY KEY(cashier_id),
	shop_id int DEFAULT NULL,
	FOREIGN KEY(shop_id) REFERENCES Shop(shop_id) ON DELETE SET NULL,
	first_name VARCHAR(30) DEFAULT 'UNKNOWN',
	last_name VARCHAR(30) DEFAULT 'UNKNOWN',
	age int DEFAULT 0,
	CONSTRAINT Age16_Constraint CHECK (age>=16),
	gender VARCHAR(20) DEFAULT 'UNCERTAIN',
	salary int DEFAULT 2500
);

CREATE TABLE BouquetOrder(
	customer_id int NOT NULL,
	cashier_id int NOT NULL,
	bouquet_id int NOT NULL,
	order_date smalldatetime NOT NULL,
	quantity int DEFAULT 1,
	CONSTRAINT BouquetOrderQuantity_Constraint CHECK (quantity>0),
	FOREIGN KEY(bouquet_id) REFERENCES Bouquet(bouquet_id) ON DELETE CASCADE,
	FOREIGN KEY(customer_id) REFERENCES Customer(customer_id) ON DELETE CASCADE,
	FOREIGN KEY(cashier_id) REFERENCES Cashier(cashier_id) ON DELETE CASCADE,
	PRIMARY KEY(bouquet_id, cashier_id, customer_id, order_date)
);

INSERT INTO Customer (first_name, last_name, age, gender, budget) VALUES 
('Angela','Martin',24,'female',100),
('Andrei','Filip',19,'male',250),
('Sorana','Pop',20,'female',120),
('Dan','Andreicut',51,'male',50),
('Rares','Descas',20,'male',150),
('Eliza','Casapopol',28,'female',200);

INSERT INTO Customer (first_name, last_name, age, budget) VALUES 
('Timothy','Jimothy',17, 80);

INSERT INTO FlowerStore (flower_store_id, flower_store_name) VALUES
(3264,'Holland Flowers'),
(6352,'Flora Center'),
(8341,'Fresco');

INSERT INTO FlowerStore (flower_store_id, flower_store_name) VALUES
(5326,NULL);

INSERT INTO Flower (flower_id, flower_name, color, country_of_origin, price, quantity) VALUES
(1,'rose','red','Romania',8,30),
(2,'rose','yellow','Romania',9,20),
(3,'tulip','black','The Netherlands',7,10),
(4,'tulip','yellow','The Netherlands',6,20),
(5,'tulip','purple','The Netherlands',6,20),
(6,'fresia','pink','Spain',6,30),
(7,'fresia','purple','Italy',6,20),
(8,'fresia','yellow','Spain',6,15),
(9,'peony','pink','Romania',10,20),
(10,'gerbera','orange','Germany',5,40);

INSERT INTO FlowerStoreOrder(flower_store_id, flower_id,quantity,order_date) VALUES
(3264,4,10,'2020-05-05'),
(3264,3,20,'2021-09-12'),
(6352,1,15,'2021-09-12');

INSERT INTO FlowerStoreOrder (flower_store_id, flower_id,quantity,order_date) VALUES
(9743,6,10,'2001-12-09');

INSERT INTO Florist(first_name,last_name,age,gender,salary) VALUES
('Mariana','Alupei',40,'female',2600),
('Tiberiu','Trifoi',50,'male',2600),
('Ileana','Marincas',47,'female',2600),
('Cristina','Enache',31,'female',3100),
('Liviu','Partan',39,'male',3100);

UPDATE Florist
SET age = 30
WHERE florist_id = 4

INSERT INTO Occasion(name,florist_id) VALUES
('romantic',1),
('aniversare',NULL),
('sezon',3),
('lux',4),
('eveniment special',5),
('funerar',2);

INSERT INTO Bouquet (bouquet_name, occasion_id,price) VALUES
('Red Passion',1,200),
('Autumn Vibes',3,100),
('Coroana',6,90),
('lamultsean',2,50),
('Exotic Love',1,100);

INSERT INTO FlowerRecipe(flower_id,bouquet_id,number_of_flowers) VALUES
(10,3,14),
(1,1,25),
(2,2,3),
(4,2,5),
(8,2,2),
(10,2,3);

INSERT INTO Accessory (accessory_id,accessory_name,color,price,quantity) VALUES
(1,'pamblica','red',3,60),
(2,'plastic foil','transparent',2,100),
(3,'parsley','green',1,50),
(4,'panglica','yellow',3,60),
(5,'sponge box','red',7,10);

INSERT INTO AccessoryRecipe (accessory_id,bouquet_id,number_of_accessories) VALUES
(1,1,1),
(1,2,1),
(2,3,3),
(3,2,6),
(3,4,3),
(5,2,1);

INSERT INTO Cashier (first_name, last_name, age, gender, salary) VALUES
('Ana','Rednic',19,'female',1700),
('Andrei','Petrescu',16,'male',1200),
('Mirela','Vaida',40,'CEEEE',100000000),
('Aurel','Pintea',59,'male',1700);

INSERT INTO BouquetOrder (customer_id,cashier_id,bouquet_id,order_date,quantity) VALUES
(5,3,1,'2022-05-24 15:18:32',1),
(4,2,2,'2021-09-14 07:40:38',2);

UPDATE Customer
SET age = 55
WHERE last_name LIKE 'A%'
select * from Customer

UPDATE Flower 
SET price = price+1
select * from Flower

UPDATE FlowerStore
SET flower_store_name = 'Magnolia'
WHERE flower_store_id = 8341 OR flower_store_name IS NULL
select * from FlowerStore

DELETE FROM Flower
WHERE flower_id = 3 OR flower_id BETWEEN 40 AND 50
select * from FlowerStoreOrder

DELETE FROM Customer
WHERE gender NOT IN ('female','male')
select * from Customer

--a---------------------------------------------------------------------------------------------------------
SELECT DISTINCT B.bouquet_name, B.price, B.occasion_id  --select bouquets which cost more than 100 or those that are for a romantic occasion
FROM Bouquet B
WHERE B.price >= 100 UNION SELECT B.bouquet_name, B.price, B.occasion_id
						   FROM Bouquet B
						   WHERE B.occasion_id = 1

SELECT DISTINCT F.flower_id, F.flower_name, F.color, F.quantity, F.price --select flowers which are in short supply or cost less than 6
FROM Flower F
WHERE F.quantity <= 15 OR F.price <= 6
--b---------------------------------------------------------------------------------------------------------
SELECT F.flower_name, F.color, F.country_of_origin --select flowers from romania, spain or italy
FROM Flower F
WHERE F.country_of_origin IN ('Romania','Spain','Italy')

SELECT DISTINCT F.flower_name, F.color, F.price   --select flowers which are yellow and cost 6
FROM Flower F
WHERE F.price=6 INTERSECT SELECT F.flower_name, F.color, F.price
						  FROM Flower F
						  WHERE F.color='yellow'
--c---------------------------------------------------------------------------------------------------------
SELECT A.accessory_name, A.price, A.quantity  --select accs which are in short supply but cost more than 2
FROM Accessory A
WHERE A.quantity<100 EXCEPT SELECT A.accessory_name, A.price, A.quantity
						  FROM Accessory A
						  WHERE A.price>2 

SELECT C.first_name+' '+C.last_name AS 'NAME', C.age AS 'AGE'  --select cashiers which have more than 18 years and did not sell anything in 2022
FROM Cashier C
WHERE C.age>=18 AND C.cashier_id NOT IN (SELECT O.cashier_id FROM BouquetOrder O WHERE YEAR(O.order_date) = 2022)
--d---------------------------------------------------------------------------------------------------------
--display all the flowers used for each bouquet 
SELECT B.bouquet_name, F.flower_name, F.color FROM Flower F right JOIN FlowerRecipe R ON F.flower_id = R.flower_id right JOIN Bouquet B ON B.bouquet_id = R.bouquet_id
--display all the accs used for each bouquet
SELECT B.bouquet_name, A.accessory_name, A.color FROM Accessory A RIGHT JOIN AccessoryRecipe R ON A.accessory_id = R.accessory_id RIGHT JOIN Bouquet B ON B.bouquet_id = R.bouquet_id
--display the sells of each cashier with name, bouquetid and date
SELECT C.first_name, C.last_name, O.bouquet_id, O.order_date FROM Cashier C FULL OUTER JOIN BouquetOrder O ON O.cashier_id = C.cashier_id
--display the salary given to florist foar each occasion
SELECT O.name, F.salary, F.first_name, F.last_name FROM Occasion O LEFT JOIN Florist F ON O.florist_id = F.florist_id
--display all the details of an order
SELECT C.first_name+' '+C.last_name AS 'Cashier name', O.order_date AS 'Order date', B.price*O.quantity AS 'Amount' ,B.bouquet_name AS 'Bouquet name', U.first_name+' '+U.last_name AS 'Customer name' 
FROM Cashier C INNER JOIN BouquetOrder O ON O.cashier_id = C.cashier_id INNER JOIN Bouquet B ON B.bouquet_id = O.bouquet_id INNER JOIN Customer U ON U.customer_id = O.customer_id
--e---------------------------------------------------------------------------------------------------------
SELECT DISTINCT F.flower_name, F.color, F.quantity  --display the details of the flowers in short supply or which ar used in the bouquet with id=2
FROM Flower F
WHERE F.quantity < 20 OR F.flower_id IN
							(SELECT R.flower_id
							FROM FlowerRecipe R
							WHERE R.bouquet_id = 2)

SELECT DISTINCT F.flower_name, F.color, F.quantity  --display the details of the flowers which are used in the bouquets sold in 2021
FROM Flower F
WHERE F.flower_id IN
	(SELECT R.flower_id
	FROM FlowerRecipe R
	WHERE R.bouquet_id IN 
		(SELECT O.bouquet_id
		FROM BouquetOrder O
		WHERE YEAR(O.order_date) = 2021)) 
--f---------------------------------------------------------------------------------------------------------
SELECT A.accessory_name, A.color, A.quantity  --display accs details of the ones used in bouquet with id=2
FROM Accessory A 
WHERE EXISTS   (SELECT * 
				FROM AccessoryRecipe AR 
				WHERE AR.bouquet_id = 2 AND A.accessory_id = AR.accessory_id)

SELECT C.first_name+' '+C.last_name AS 'NAME', C.age AS 'AGE'  --display the customers name and age that have bought something in the last 2 years
FROM Customer C
WHERE EXISTS   (SELECT *
				FROM BouquetOrder O
				WHERE O.customer_id = C.customer_id AND YEAR(O.order_date)>=2021)
--g---------------------------------------------------------------------------------------------------------
SELECT C.*   --display the details of the cashiers which have sold something in 2021
FROM Cashier C INNER JOIN  (SELECT * FROM BouquetOrder O
							WHERE YEAR(O.order_date) = 2021 ) Y
ON Y.cashier_id = C.cashier_id

SELECT Q.order_date, Q.quantity, Q.flower_id   --display the orderdate, quantity and flower id of the orders of more than 10 items
FROM (SELECT * FROM FlowerStoreOrder O WHERE O.quantity>10) Q 
--h---------------------------------------------------------------------------------------------------------
SELECT F.country_of_origin, COUNT(*) AS 'COUNT', SUM(F.quantity) AS 'SUM OF QUANTITY'
FROM Flower F
GROUP BY F.country_of_origin
HAVING COUNT(*)>1
ORDER BY COUNT(*) DESC, SUM(F.quantity) ASC  --display and sort the countries by the number of flower types the have and the quantities of flowers

SELECT TOP 3 B.occasion_id, AVG(B.price) AS 'AVG PRICE', MAX(B.price) AS 'MAX PRICE', MIN(B.price) AS 'MIN PRICE'
FROM Bouquet B
GROUP BY B.occasion_id
ORDER BY AVG(B.price) DESC   --display the average price of bouquets in each occasion, sort desc, top 3

SELECT C.gender, AVG(C.age) AS 'AVG AGE', AVG(C.budget) AS 'AVG BUDGET'  
FROM Customer C
GROUP BY C.gender
HAVING AVG(C.age) IN (SELECT F.age FROM Florist F)
ORDER BY AVG(C.budget)  -- display the average age and budget for each gender having the avg age in the ages of the florists, order by avg budget

SELECT TOP 3 F.price, COUNT(*) AS 'COUNT'  --display the count and prices of the flowers which cost more than 6, are more than 1 item and order by price desc TOP 3
FROM Flower F
WHERE F.price >= 6
GROUP BY F.price
HAVING 1 <=  (SELECT COUNT(*)
			FROM Flower F2
			WHERE F2.price = F.price)
ORDER BY COUNT(*) DESC, F.price ASC
--i---------------------------------------------------------------------------------------------------------
SELECT F.flower_id, F.flower_name, F.color
FROM Flower F
WHERE F.flower_id <> ALL (SELECT O.flower_id FROM FlowerStoreOrder O)

SELECT F.flower_id, F.flower_name, F.color  --display flowers not used in the orders
FROM Flower F
WHERE F.flower_id NOT IN (SELECT O.flower_id FROM FlowerStoreOrder O)

SELECT C.first_name, C.last_name
FROM Cashier C
WHERE C.last_name <> ALL(SELECT C.last_name FROM Cashier C INNER JOIN BouquetOrder O ON O.cashier_id = C.cashier_id)

SELECT C.first_name, C.last_name --select the cashiers which have not sold something
FROM Cashier C
WHERE C.last_name NOT IN (SELECT C.last_name FROM Cashier C INNER JOIN BouquetOrder O ON O.cashier_id = C.cashier_id)

SELECT A.accessory_name, A.color, A.price  --select the accs more expensive than any of the flowers
FROM Accessory A
WHERE A.price > ANY (SELECT F.price FROM Flower F)

SELECT A.accessory_name, A.color, A.price
FROM Accessory A
WHERE A.price > (SELECT MIN(F.price) FROM Flower F)

SELECT C.first_name, C.last_name, C.salary  --select the cashiers paid less than any of the florists
FROM Cashier C
WHERE C.salary < ANY (SELECT F.salary FROM Florist F)

SELECT C.first_name, C.last_name, C.salary
FROM Cashier C
WHERE C.salary < (SELECT MAX(F.salary) FROM Florist F)



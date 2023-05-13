create table recipe (
    recipeID    int          not null primary key AUTO_INCREMENT,
    rauthor     varchar(100) not null,
    rname       varchar(100) not null,
    rtype       varchar(100) not null,
    ringredients varchar(100) not null,
    rinstructions varchar(100) not null,
    rimage      varchar(100) not null
);
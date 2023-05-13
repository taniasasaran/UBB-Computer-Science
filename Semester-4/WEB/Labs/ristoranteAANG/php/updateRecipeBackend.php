<?php
header("Access-Control-Allow-Headers: *");
header("Access-Control-Allow-Origin: *");
require_once "utils/configuration.php";
global $connection;
if (isset($_POST['name']) && !empty(trim($_POST['name']))) {
    $recipeID = $_POST['id'];
    $name = $_POST['name'];
    $type = $_POST['type'];
    $author = $_POST['author'];
    $ingredients = $_POST['ingredients'];
    $instructions = $_POST['instructions'];
    $image = $_POST['image'];
    $sql_query = "UPDATE recipe SET `rname` = ?, `rtype` = ?, `rauthor` = ?, `ringredients` = ?, `rinstructions` = ?, `rimage`= ? WHERE `recipeID` = ?";
    $stmt = mysqli_prepare($connection, $sql_query);
    mysqli_stmt_bind_param($stmt, "ssssssi", $name, $type, $author, $ingredients, $instructions, $image, $recipeID);
    mysqli_stmt_execute($stmt);
    $stmt->close();
    $connection->close();
    echo '<script type="text/javascript">window.location.href = "showRecipes.php?type=&name=";</script>';
} else {
    $postdata = file_get_contents("php://input");
    $request = json_decode($postdata);
    $recipeID = $request->id;
    $name = $request->name;
    $type = $request->type;
    $author = $request->author;
    $ingredients = $request->ingredients;
    $instructions = $request->instructions;
    $image = $request->image;

    $sql_query = "UPDATE recipe SET `rname` = ?, `rtype` = ?, `rauthor` = ?, `ringredients` = ?, `rinstructions` = ?, `rimage`= ? WHERE `recipeID` = ?";
    $stmt = mysqli_prepare($connection, $sql_query);
    mysqli_stmt_bind_param($stmt, "ssssssi", $name, $type, $author, $ingredients, $instructions, $image, $recipeID);
    mysqli_stmt_execute($stmt);
    $stmt->close();
    $connection->close();
    echo '<script type="text/javascript">window.location.href = "showRecipes.html";</script>';
}
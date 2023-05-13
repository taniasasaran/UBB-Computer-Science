<?php
header("Access-Control-Allow-Headers: *");
header("Access-Control-Allow-Origin: *");
require_once "utils/configuration.php";
global $connection;
if (isset($_POST['name']) && !empty(trim($_POST['name']))) {
    $name = $_POST['name'];
    $type = $_POST['type'];
    $author = $_POST['author'];
    $ingredients = $_POST['ingredients'];
    $instructions = $_POST['instructions'];
    $image = $_POST['image'];
    $sql_query = "INSERT INTO recipe (`rname`, `rtype`, `rauthor`, `ringredients`, `rinstructions`, `rimage`) VALUES (?,?,?, ?, ?, ?)";
    $stmt = mysqli_prepare($connection, $sql_query);
    mysqli_stmt_bind_param($stmt, "ssssss", $name, $type, $author, $ingredients, $instructions, $image);
    mysqli_stmt_execute($stmt);
    $stmt->close();
    $connection->close();
    echo '<script type="text/javascript">window.location.href = "showRecipes.html";</script>';
} else {
    $postdata = file_get_contents("php://input");
    $request = json_decode($postdata);
    $name = $request->name;
    $type = $request->type;
    $author = $request->author;
    $ingredients = $request->ingredients;
    $instructions = $request->instructions;
    $image = $request->image;
    $sql_query = "INSERT INTO recipe (`rname`, `rtype`, `rauthor`, `ringredients`, `rinstructions`, `rimage`) VALUES (?,?,?, ?, ?, ?)";
    $stmt = mysqli_prepare($connection, $sql_query);
    mysqli_stmt_bind_param($stmt, "ssssss", $name, $type, $author, $ingredients, $instructions, $image);
    mysqli_stmt_execute($stmt);
    $stmt->close();
    $connection->close();
    echo '<script type="text/javascript">window.location.href = "showRecipes.html";</script>';
}
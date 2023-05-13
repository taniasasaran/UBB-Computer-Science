<?php
header("Access-Control-Allow-Headers: *");
header("Access-Control-Allow-Origin: *");
require_once "utils/configuration.php";
global $connection;
if (isset($_POST['id']) && !empty(trim($_POST['id']))) {
    $id = $_POST['id'];
    $sql_query = "DELETE FROM recipe WHERE `recipeID` = ?";
    $stmt = mysqli_prepare($connection, $sql_query);
    mysqli_stmt_bind_param($stmt, "i", $id);
    mysqli_stmt_execute($stmt);
    $stmt->close();
    $connection->close();
    echo '<script type="text/javascript">window.location.href = "showRecipes.html";</script>';
} else {
    $postdata = file_get_contents("php://input");
    $request = json_decode($postdata);
    $id = $request->id;
    $sql_query = "DELETE FROM recipe WHERE `recipeID` = ?";
    $stmt = mysqli_prepare($connection, $sql_query);
    mysqli_stmt_bind_param($stmt, "i", $id);
    mysqli_stmt_execute($stmt);
    $stmt->close();
    $connection->close();
    echo '<script type="text/javascript">window.location.href = "showRecipes.html";</script>';
}
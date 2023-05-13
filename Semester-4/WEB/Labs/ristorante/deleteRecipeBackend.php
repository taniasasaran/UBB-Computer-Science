<?php
require_once "utils/configuration.php";
$id = $_POST['id'];
$sql_query = "DELETE FROM recipe WHERE `recipeID` = ?";

$stmt = mysqli_prepare($connection, $sql_query);
mysqli_stmt_bind_param($stmt, "i", $id);
mysqli_stmt_execute($stmt);
$stmt->close();
$connection->close();
echo '<script type="text/javascript">window.location.href = "showRecipes.html";</script>';
?>
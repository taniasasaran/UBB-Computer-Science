<?php
require_once "utils/configuration.php";
$name = $_POST['name'];
$type = $_POST['type'];
if ($name == "" || $type == ""):
    $connection->close();
    echo '<script type="text/javascript">window.location.href = "addRecipe.html";
    window.alert("Recipe name and type cannot be empty!"); 
    </script>';
else:
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
endif;
?>
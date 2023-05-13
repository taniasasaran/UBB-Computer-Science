<?php
require_once "utils/configuration.php";
$recipeID = $_POST['id'];
$name = $_POST['name'];
$type = $_POST['type'];
if ($name == "" || $type == ""):
    $connection->close();
    echo '<script type="text/javascript">window.location.href = "updateRecipe.php?id='.$recipeID.'";
    window.alert("Recipe name and type cannot be empty!"); 
    </script>';
else:
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
    echo '<script type="text/javascript">window.location.href = "showRecipes.html";</script>';
endif;
?>



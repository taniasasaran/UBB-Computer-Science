<?php
require_once "utils/configuration.php";
global $connection;
$id = "";
$name = "";
$type = "";
$author = "";
$ingredients = "";
$instructions = "";
$image = "";
$id = trim($_GET['id']);
$sql_query = "select * from recipe where recipeID = $id;";
$result = mysqli_query($connection, $sql_query);
if ($result) {
    $number_of_rows = mysqli_num_rows($result);
    if ($number_of_rows == 1) {
        $row = mysqli_fetch_array($result);
        $name = $row['rname'];
        $type = $row['rtype'];
        $author = $row['rauthor'];
        $ingredients = $row['ringredients'];
        $instructions = $row['rinstructions'];
        $image = $row['rimage'];
    } else {
        die("Incorrect recipe id");
    }
} else {
    die("Oops! Something went wrong and your recipe cannot be updated! Please try again later.");
}
mysqli_close($connection);
?>

<html lang="en">

<head>
    <meta charset="UTF-8">
    <title>Update Recipe</title>
    <style>
        <?php include "addRecipe.css" ?>
    </style>
</head>

<body>
<div class="container">
    <h1>Update Recipe</h1>
    <p><b>Please fill this form and submit to update the recipe in the database.</b></p>

    <form action="updateRecipeBackend.php" method="post">
        <input type="hidden" name="id" value="<?php echo trim($_GET['id']); ?>">
        <input type="text" name="name" placeholder="Name:" value="<?php echo $name ?>"> <br>
        <input type="text" name="type" placeholder="Type:" value="<?php echo $type ?>"> <br>
        <input type="text" name="author" placeholder="Author:" value="<?php echo $author ?>"> <br>
        <input type="text" name="ingredients" placeholder="Ingredients:" value="<?php echo $ingredients ?>"> <br>
        <input type="text" name="instructions" placeholder="Instructions:" value="<?php echo $instructions ?>"> <br>
        <input type="text" name="image" placeholder="Image:" value="<?php echo $image ?>"> <br>
        <div class="button_container">
            <button type="submit" onClick="window.location.href='showRecipes.html'">Update Recipe</button>
            <button type="reset" onClick="window.location.href='showRecipes.html'">Cancel</button>
        </div>
    </form>
</div>
</body>

</html>
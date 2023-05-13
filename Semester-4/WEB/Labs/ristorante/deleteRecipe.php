<!DOCTYPE html>

<html lang="en">

<head>
    <meta charset="UTF-8">
    <title>Delete Recipe</title>
    <link rel="stylesheet" type="text/css" href="deleteRecipe.css">
</head>

<body>
<div class="container">
    <h1>Delete Recipe</h1>
    <p><b>Are you sure you want to delete this recipe?</b></p>

    <form action="deleteRecipeBackend.php" method="post">
        <input type="hidden" name="id" id="id" value="<?php echo trim($_GET['id']); ?>">
        <div class="button_container">
            <button type="submit" class="yes" onclick="window.location.href='showRecipes.html'">Yes</button>
            <button type="reset" class="no" onclick="window.location.href='showRecipes.html'">No</button>
        </div>
    </form>

</div>
</body>

</html>
<?php
header("Access-Control-Allow-Origin: *");
require_once "utils/configuration.php";
$sql_query = "SELECT * FROM recipe;";
global $connection;
$result = mysqli_query($connection, $sql_query);

if ($result) {
    $number_of_rows = mysqli_num_rows($result);
    $requested_recipes = array();
    $type = $_GET["type"];
    $name = $_GET["name"];
    for ($i = 0; $i < $number_of_rows; $i++) {
        $row = mysqli_fetch_array($result);
        if (str_contains($row["rname"], $name) && str_contains($row["rtype"], $type))
            array_push($requested_recipes, array(
                "recipeID" => (int)$row['recipeID'],
                "rname" => $row['rname'],
                "rtype" => $row['rtype'],
                "rauthor" => $row['rauthor'],
                "ringredients" => $row['ringredients'],
                "rinstructions" => $row['rinstructions'],
                "rimage" => $row['rimage']));
    }
    mysqli_free_result($result);
    echo json_encode($requested_recipes);
}
mysqli_close($connection);
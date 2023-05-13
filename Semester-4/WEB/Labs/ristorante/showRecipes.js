$((function () {
    function refresh() {
        let type = $("#type")
        let name = $("#name")
        $.getJSON("showRecipes.php", {type: type.val(), name: name.val()}, function (json) {
            $("tbody tr").remove()
            json.forEach(function (thing) {
                $("tbody").append(`<tr>
                                <td>${thing[1]}</td>
                                <td>${thing[2]}</td>
                                <td>${thing[3]}</td>
                                <td>${thing[4]}</td>
                                <td>${thing[5]}</td>
                                <td>${thing[6]}</td>
                                <td>
                                    <a href=updateRecipe.php?id=${thing[0]}>Update</a>
                                    <br>
                                    <a href=deleteRecipe.php?id=${thing[0]}>Delete</a>
                                    <br>
                                </td>
                               </tr>`)
            })
        })

    }

    $("#type, #name").on("input", function () {
        refresh()
    })

    refresh()
}));
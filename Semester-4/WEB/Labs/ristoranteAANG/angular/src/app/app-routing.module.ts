import {NgModule} from '@angular/core';
import {RouterModule, Routes} from '@angular/router';
import { ShowRecipesComponent } from './show-recipes/show-recipes.component';
import { DeleteRecipeComponent } from './delete-recipe/delete-recipe.component';
import { AddRecipeComponent } from './add-recipe/add-recipe.component';
import { UpdateRecipeComponent } from './update-recipe/update-recipe.component';

const routes: Routes = [
  {path: '', redirectTo: '/showRecipes', pathMatch: 'full'},
  {path: 'showRecipes', component: ShowRecipesComponent},
  {path: 'deleteRecipe', component: DeleteRecipeComponent},
  {path: 'addRecipe', component: AddRecipeComponent},
  {path: 'updateRecipe', component: UpdateRecipeComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule {
}